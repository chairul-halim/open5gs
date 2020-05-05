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

#include "context.h"
#include "event.h"
#include "nrf-sm.h"

#include "microhttpd.h"

#define PAGE \
  "<html><head><title>libmicrohttpd demo</title></head><body>libmicrohttpd demo</body></html>"

static int
ahc_echo (void *cls,
          struct MHD_Connection *connection,
          const char *url,
          const char *method,
          const char *version,
          const char *upload_data,
          size_t *upload_data_size,
          void **ptr)
{
    const char *me = cls;
    struct MHD_Response *response;
    int ret;

    (void) url;               /* Unused. Silent compiler warning. */
    (void) version;           /* Unused. Silent compiler warning. */
    (void) upload_data;       /* Unused. Silent compiler warning. */
    (void) upload_data_size;  /* Unused. Silent compiler warning. */

    if (0 != strcmp (method, "GET"))
        return MHD_NO;              /* unexpected method */
    response = MHD_create_response_from_buffer (strlen (me),
    (void *)me,
    MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response (connection,
            MHD_HTTP_OK,
            response);
    MHD_destroy_response (response);

    return ret;
}

int ogs_mhd_server(void);
static struct MHD_Daemon *d;

static void mhd_recv_cb(short when, ogs_socket_t fd, void *data)
{
    struct MHD_Daemon *mhd = data;

    ogs_assert(mhd);
    ogs_fatal("mhd_recv_cb = %p, %d", mhd, fd);
    MHD_run(mhd);
}

static void
notify_connection_cb(void *cls,
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

            poll = ogs_pollset_add(nrf_self()->pollset,
                    OGS_POLLIN, connect_fd, mhd_recv_cb, mhd);
            ogs_assert(poll);
            *socket_context = poll;
            break;
        case MHD_CONNECTION_NOTIFY_CLOSED:
            poll = *socket_context;
            ogs_pollset_remove(poll);
            break;
    }
}


static ogs_poll_t *g_poll = NULL;

int ogs_mhd_server(void)
{
    const union MHD_DaemonInfo *info;

    /* initialize PRNG */
    d = MHD_start_daemon(1,
                    8080,
                    NULL, NULL,
                    &ahc_echo, (void*)PAGE,
                    MHD_OPTION_NOTIFY_CONNECTION, &notify_connection_cb, NULL,
                    MHD_OPTION_END);
    if (NULL == d)
        return 1;

    info = MHD_get_daemon_info(d, MHD_DAEMON_INFO_LISTEN_FD);
    if (info == NULL)
        return 1;

    g_poll = ogs_pollset_add(nrf_self()->pollset,
            OGS_POLLIN, info->listen_fd, mhd_recv_cb, d);

    return 0;
}

static ogs_thread_t *thread;
static void nrf_main(void *data);
static int initialized = 0;

int nrf_initialize()
{
    int rv;

    nrf_context_init();
    nrf_event_init();

    rv = nrf_context_parse_config();
    if (rv != OGS_OK) return rv;

    rv = ogs_log_config_domain(
            ogs_config()->logger.domain, ogs_config()->logger.level);
    if (rv != OGS_OK) return rv;

    rv = nrf_db_init();
    if (rv != OGS_OK) return rv;

    rv = ogs_sbi_init(8080);
    if (rv != OGS_OK) return OGS_ERROR;

    ogs_mhd_server();

    thread = ogs_thread_create(nrf_main, NULL);
    if (!thread) return OGS_ERROR;

    initialized = 1;

    return OGS_OK;
}

void nrf_terminate(void)
{
    if (!initialized) return;

    MHD_stop_daemon(d);

    ogs_pollset_remove(g_poll);

    nrf_event_term();

    ogs_thread_destroy(thread);

    ogs_sbi_final();
    nrf_db_final();

    nrf_context_final();
    nrf_event_final();
}

static void nrf_main(void *data)
{
    ogs_fsm_t nrf_sm;
    int rv;

    ogs_fsm_create(&nrf_sm, nrf_state_initial, nrf_state_final);
    ogs_fsm_init(&nrf_sm, 0);

    for ( ;; ) {
        ogs_pollset_poll(nrf_self()->pollset,
                ogs_timer_mgr_next(nrf_self()->timer_mgr));

        /* Process the MESSAGE FIRST.
         *
         * For example, if UE Context Release Complete is received,
         * the MME_TIMER_UE_CONTEXT_RELEASE is first stopped */
        for ( ;; ) {
            nrf_event_t *e = NULL;

            rv = ogs_queue_trypop(nrf_self()->queue, (void**)&e);
            ogs_assert(rv != OGS_ERROR);

            if (rv == OGS_DONE)
                goto done;

            if (rv == OGS_RETRY)
                break;

            ogs_assert(e);
            ogs_fsm_dispatch(&nrf_sm, e);
            nrf_event_free(e);
        }

        ogs_timer_mgr_expire(nrf_self()->timer_mgr);

        /* AND THEN, process the TIMER. */
        for ( ;; ) {
            nrf_event_t *e = NULL;

            rv = ogs_queue_trypop(nrf_self()->queue, (void**)&e);
            ogs_assert(rv != OGS_ERROR);

            if (rv == OGS_DONE)
                goto done;

            if (rv == OGS_RETRY)
                break;

            ogs_assert(e);
            ogs_fsm_dispatch(&nrf_sm, e);
            nrf_event_free(e);
        }
    }
done:

    ogs_fsm_fini(&nrf_sm, 0);
    ogs_fsm_delete(&nrf_sm);
}
