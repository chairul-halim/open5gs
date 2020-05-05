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

#include "sbi-path.h"
#include "context.h"
#include "event.h"
#include "microhttpd.h"

#define PAGE \
  "<html><head><title>libmicrohttpd demo</title></head><body>libmicrohttpd demo</body></html>"

static int sbi_recv_cb(void *data)
{
    nrf_event_t *e = NULL;
    int rv;

    struct MHD_Connection *connection = NULL;
    const char *me = PAGE;
    struct MHD_Response *response;
    int ret;

    connection = data;
    ogs_assert(connection);

    e = nrf_event_new(NRF_EVT_SBI_MESSAGE);
    ogs_assert(e);
    e->connection = connection;

    ogs_fatal("sbi_recv_cb");
    rv = ogs_queue_push(nrf_self()->queue, e);
    if (rv != OGS_OK) {
        ogs_error("ogs_queue_push() failed:%d", (int)rv);
        nrf_event_free(e);
        return OGS_ERROR;
    }

    return OGS_OK;
}

int nrf_sbi_open(void)
{
    ogs_sbi_server_add(NULL, sbi_recv_cb);

    return OGS_OK;
}

void nrf_sbi_close(void)
{
    ogs_sbi_server_remove_all();
}
