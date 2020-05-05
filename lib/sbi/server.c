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

#include "microhttpd.h"
#include "ogs-sbi.h"

static void mhd_run(short when, ogs_socket_t fd, void *data);
static void mhd_notify_connection_cb(void *cls,
        struct MHD_Connection *connection,
        void **socket_context,
        enum MHD_ConnectionNotificationCode toe);
static int mhd_webservice_dispatch(void *cls,
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        const char *upload_data,
        size_t *upload_data_size,
        void **ptr);

ogs_sbi_server_t *ogs_sbi_server_add(
        ogs_sockaddr_t *addr, int (*cb)(void *data))
{
    const union MHD_DaemonInfo *info = NULL;
    ogs_sbi_server_t *node = NULL;

    ogs_pool_alloc(&ogs_sbi_self()->server_pool, &node);
    ogs_assert(node);
    memset(node, 0, sizeof(ogs_sbi_server_t));

    /* Setup callback function */
    node->cb = cb;

    node->mhd = MHD_start_daemon(
                MHD_ALLOW_SUSPEND_RESUME,
                8080,
                NULL, NULL,
                &mhd_webservice_dispatch, node,
                MHD_OPTION_NOTIFY_CONNECTION, &mhd_notify_connection_cb, NULL,
                MHD_OPTION_END);
    if (!node->mhd) {
        ogs_error("Cannot start SBI server");
        return NULL;
    }

    info = MHD_get_daemon_info(node->mhd, MHD_DAEMON_INFO_LISTEN_FD);
    ogs_assert(info);

    node->poll = ogs_pollset_add(ogs_sbi_self()->pollset,
            OGS_POLLIN, info->listen_fd, mhd_run, node->mhd);
    ogs_assert(node->poll);

    ogs_list_add(&ogs_sbi_self()->server_list, node);

    return node;
}

void ogs_sbi_server_remove(ogs_sbi_server_t *node)
{
    ogs_assert(node);

    ogs_list_remove(&ogs_sbi_self()->server_list, node);

    ogs_assert(node->poll);
    ogs_pollset_remove(node->poll);
    ogs_assert(node->mhd);
    MHD_stop_daemon(node->mhd);

    ogs_pool_free(&ogs_sbi_self()->server_pool, node);
}

void ogs_sbi_server_remove_all(void)
{
    ogs_sbi_server_t *node = NULL, *next_node = NULL;

    ogs_list_for_each_safe(&ogs_sbi_self()->server_list, next_node, node)
        ogs_sbi_server_remove(node);
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

static int mhd_webservice_dispatch(void *cls,
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        const char *upload_data,
        size_t *upload_data_size,
        void **ptr)
{
    ogs_sbi_server_t *node = NULL;

    node = cls;
    ogs_assert(node);

    if (0 != strcmp (method, "GET"))
        return MHD_NO;              /* unexpected method */

    MHD_suspend_connection(connection);
    ogs_fatal("webservice");
    if (node->cb(connection) != OGS_OK)
        return MHD_NO;

    return MHD_YES;
}
