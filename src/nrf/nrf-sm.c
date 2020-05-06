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
#include "sbi-path.h"
#include "nrf-sm.h"

void nrf_state_initial(ogs_fsm_t *s, nrf_event_t *e)
{
    nrf_sm_debug(e);

    ogs_assert(s);

    OGS_FSM_TRAN(s, &nrf_state_operational);
}

void nrf_state_final(ogs_fsm_t *s, nrf_event_t *e)
{
    nrf_sm_debug(e);

    ogs_assert(s);
}

void nrf_state_operational(ogs_fsm_t *s, nrf_event_t *e)
{
    int rv;
#if 0
    ogs_pkbuf_t *recvbuf = NULL;

    ogs_pfcp_message_t pfcp_message;
    ogs_pfcp_node_t *node = NULL;
    ogs_pfcp_xact_t *xact = NULL;
#endif

    nrf_sm_debug(e);

    ogs_assert(s);

    switch (e->id) {
    case OGS_FSM_ENTRY_SIG:
        rv = nrf_sbi_open();
        if (rv != OGS_OK) {
            ogs_fatal("Can't establish SBI path");
        }
#if 0
        ogs_list_for_each(&ogs_pfcp_self()->n4_list, node) {
            nrf_event_t e;
            e.pfcp_node = node;

            ogs_fsm_create(&node->sm,
                    nrf_pfcp_state_initial, nrf_pfcp_state_final);
            ogs_fsm_init(&node->sm, &e);
        }
#endif
        break;
    case OGS_FSM_EXIT_SIG:
#if 0
        ogs_list_for_each(&ogs_pfcp_self()->n4_list, node) {
            nrf_event_t e;
            e.pfcp_node = node;

            ogs_fsm_fini(&node->sm, &e);
            ogs_fsm_delete(&node->sm);
        }

#endif
        nrf_sbi_close();
        break;
    case NRF_EVT_SBI_MESSAGE:
        ogs_assert(e);
        ogs_assert(e->server.connection);
        {
            const char *me = "<html><head><title>libmicrohttpd demo</title></head><body>libmicrohttpd demo</body></html>";

            ogs_sbi_server_send_response(
                    e->server.connection, (void*)me, strlen(me));
        }

#if 0
        ogs_assert(e);
        recvbuf = e->pkbuf;
        ogs_assert(recvbuf);
        node = e->pfcp_node;
        ogs_assert(node);

        if (ogs_pfcp_parse_msg(&pfcp_message, recvbuf) != OGS_OK) {
            ogs_error("ogs_pfcp_parse_msg() failed");
            ogs_pkbuf_free(recvbuf);
            break;
        }

        rv = ogs_pfcp_xact_receive(node, &pfcp_message.h, &xact);
        if (rv != OGS_OK) {
            ogs_pkbuf_free(recvbuf);
            break;
        }

        e->pfcp_message = &pfcp_message;
        e->pfcp_xact = xact;
        ogs_fsm_dispatch(&node->sm, e);
        if (OGS_FSM_CHECK(&node->sm, nrf_pfcp_state_exception)) {
            ogs_error("PFCP state machine exception");
            break;
        }

        ogs_pkbuf_free(recvbuf);
#endif
        break;
    default:
        ogs_error("No handler for event %s", nrf_event_get_name(e));
        break;
    }
}
