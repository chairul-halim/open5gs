/*
 * Copyright (C) 2019 by Sukchan Lee <acetcom@gmail.com>
 *
 * This file is part of Open5GS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "ogs-app.h"
#include "ogs-sbi.h"
#include "microhttpd.h"

typedef struct request_s {
    char                    *content;
    size_t                  content_length;
    bool                    suspended;
} request_t;

typedef struct connection_s {
    ogs_lnode_t             lnode;

    struct MHD_Connection   *connection;
    ogs_sbi_server_t        *server;
} connection_t;

OGS_LIST(server_list);
OGS_POOL(server_pool, ogs_sbi_server_t);
OGS_POOL(request_pool, request_t);
OGS_POOL(connection_pool, connection_t);

static void mhd_run(short when, ogs_socket_t fd, void *data);
static void mhd_notify_connection_cb(void *cls,
        struct MHD_Connection *connection,
        void **socket_context,
        enum MHD_ConnectionNotificationCode toe);
static int access_handler(
        void *cls,
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        const char *upload_data,
        size_t *upload_data_size,
        void **con_cls);
static void notify_completed(
        void *cls,
        struct MHD_Connection *connection,
        void **con_cls,
        enum MHD_RequestTerminationCode toe);

void ogs_sbi_server_init(void)
{
    ogs_list_init(&server_list);
    ogs_pool_init(&server_pool, ogs_config()->pool.sbi);

    ogs_pool_init(&request_pool, 512); /* FIXME */
    ogs_pool_init(&connection_pool, 512); /* FIXME */
}
void ogs_sbi_server_final(void)
{
    ogs_pool_final(&server_pool);
    ogs_pool_final(&request_pool);
    ogs_pool_final(&connection_pool);
}

static request_t *request_new(void)
{
    request_t *req = NULL;

    ogs_pool_alloc(&request_pool, &req);
    ogs_assert(req);
    memset(req, 0, sizeof(request_t));

    return req;
}

static void request_free(request_t *req)
{
    ogs_pool_free(&request_pool, req);
}

static connection_t *connection_add(ogs_sbi_server_t *server,
        struct MHD_Connection *connection)
{
    connection_t *conn = NULL;

    ogs_assert(server);
    ogs_assert(connection);

    ogs_pool_alloc(&connection_pool, &conn);
    ogs_assert(conn);
    memset(conn, 0, sizeof(connection_t));

    conn->connection = connection;
    conn->server = server;

    ogs_list_add(&server->suspended_conn_list, conn);

    return conn;
}

static void connection_remove(connection_t *conn)
{
    ogs_sbi_server_t *server = NULL;

    ogs_assert(conn);
    server = conn->server;
    ogs_assert(server);

    ogs_list_remove(&server->suspended_conn_list, conn);
    ogs_pool_free(&connection_pool, conn);
}

static void connection_remove_all(ogs_sbi_server_t *server)
{
    connection_t *conn = NULL, *next_conn = NULL;

    ogs_assert(server);

    ogs_list_for_each_safe(&server->suspended_conn_list, next_conn, conn)
        connection_remove(conn);
}

ogs_sbi_server_t *ogs_sbi_server_add(
        ogs_sockaddr_t *addr, int (*cb)(void *data))
{
    const union MHD_DaemonInfo *info = NULL;
    ogs_sbi_server_t *server = NULL;

    ogs_pool_alloc(&server_pool, &server);
    ogs_assert(server);
    memset(server, 0, sizeof(ogs_sbi_server_t));

    /* Initialize Suspended MHD Connection List */
    ogs_list_init(&server->suspended_conn_list);

    /* Setup callback function */
    server->cb = cb;

    server->mhd = MHD_start_daemon(
#if MHD_VERSION >= 0x00095300
                MHD_ALLOW_SUSPEND_RESUME,
#elif MHD_VERSION >= 0x00093400
                MHD_USE_SUSPEND_RESUME,
#else
                MHD_USE_PIPE_FOR_SHUTDOWN,
#endif
                8080,
                NULL, NULL,
                access_handler, server,
                MHD_OPTION_NOTIFY_COMPLETED, notify_completed, server,
                MHD_OPTION_NOTIFY_CONNECTION, &mhd_notify_connection_cb, NULL,
                MHD_OPTION_END);
    if (!server->mhd) {
        ogs_error("Cannot start SBI server");
        return NULL;
    }

    info = MHD_get_daemon_info(server->mhd, MHD_DAEMON_INFO_LISTEN_FD);
    ogs_assert(info);

    server->poll = ogs_pollset_add(ogs_sbi_self()->pollset,
            OGS_POLLIN, info->listen_fd, mhd_run, server->mhd);
    ogs_assert(server->poll);

    ogs_list_add(&server_list, server);

    return server;
}

void ogs_sbi_server_remove(ogs_sbi_server_t *server)
{
    ogs_assert(server);

    ogs_list_remove(&server_list, server);

    ogs_assert(server->poll);
    ogs_pollset_remove(server->poll);

    connection_remove_all(server);

    ogs_assert(server->mhd);
    MHD_stop_daemon(server->mhd);

    ogs_pool_free(&server_pool, server);
}

void ogs_sbi_server_remove_all(void)
{
    ogs_sbi_server_t *server = NULL, *next_server = NULL;

    ogs_list_for_each_safe(&server_list, next_server, server)
        ogs_sbi_server_remove(server);
}

static void mhd_run(short when, ogs_socket_t fd, void *data)
{
    struct MHD_Daemon *mhd = data;

    ogs_assert(mhd);
    ogs_fatal("mhd_run = %p, %d", mhd, fd);
    MHD_run(mhd);
}

static void mhd_notify_connection_cb(void *cls,
        struct MHD_Connection *connection,
        void **socket_context,
        enum MHD_ConnectionNotificationCode toe)
{
    struct MHD_Daemon *mhd = NULL;
    MHD_socket connect_fd = INVALID_SOCKET;

    const union MHD_ConnectionInfo *info = NULL;
    ogs_poll_t *poll = NULL;

    switch (toe) {
        case MHD_CONNECTION_NOTIFY_STARTED:
            info = MHD_get_connection_info(
                    connection, MHD_CONNECTION_INFO_DAEMON);
            ogs_assert(info);
            mhd = info->daemon;
            ogs_assert(mhd);

            info = MHD_get_connection_info(
                    connection, MHD_CONNECTION_INFO_CONNECTION_FD);
            ogs_assert(info);
            connect_fd = info->connect_fd;
            ogs_assert(connect_fd != INVALID_SOCKET);

            poll = ogs_pollset_add(ogs_sbi_self()->pollset,
                    OGS_POLLIN|OGS_POLLOUT, connect_fd, mhd_run, mhd);
            ogs_assert(poll);
            *socket_context = poll;
            break;
        case MHD_CONNECTION_NOTIFY_CLOSED:
            poll = *socket_context;
            ogs_pollset_remove(poll);
            break;
    }
}

static int access_handler(
        void *cls,
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        const char *upload_data,
        size_t *upload_data_size,
        void **con_cls)
{
    ogs_sbi_server_t *server = NULL;
    request_t *req = NULL;

    server = cls;
    ogs_assert(server);

    req = *con_cls;

    if (req && req->suspended)
        return MHD_YES;

    if (!req) {
        req = request_new();
        ogs_assert(req);
        *con_cls = req;

        /* Handle Content-Length Transfer-Encoding */
        
        MHD_suspend_connection(connection);
        req->suspended = true;

        connection_add(server, connection);

        if (server->cb(connection) != OGS_OK) {
            ogs_error("server callback error");
            return MHD_NO;
        }

        return MHD_YES;
    }

    if (*upload_data_size != 0) {
        size_t offset = 0;

        if (req->content == NULL) {
            req->content_length = *upload_data_size;
            req->content = (char*)ogs_malloc(req->content_length + 1);
            ogs_assert(req->content);
        } else {
            offset = req->content_length;
            req->content_length += *upload_data_size;
            req->content = (char *)ogs_realloc(
                    req->content, req->content_length + 1);
            ogs_assert(req->content);
        }

        memcpy(req->content + offset, upload_data, *upload_data_size);
        req->content[req->content_length] = '\0';
        *upload_data_size = 0;

        return MHD_YES;
    }

    MHD_suspend_connection(connection);
    req->suspended = true;

    connection_add(server, connection);

    if (server->cb(connection) != OGS_OK) {
        ogs_error("server callback error");
        return MHD_NO;
    }

    return MHD_YES;
}

static void notify_completed(
        void *cls,
        struct MHD_Connection *connection,
        void **con_cls,
        enum MHD_RequestTerminationCode toe)
{
    request_t *req = *con_cls;
    ogs_assert(req);
    request_free(req);
}
