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
#include "microhttpd.h"

#define PAGE \
  "<html><head><title>libmicrohttpd demo</title></head><body>libmicrohttpd demo</body></html>"

static int sbi_recv_cb(void *data)
{
    struct MHD_Connection *connection = NULL;
    const char *me = PAGE;
    struct MHD_Response *response;
    int ret;

    connection = data;
    ogs_assert(connection);

    response = MHD_create_response_from_buffer(
            strlen(me), (void *)me, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    if (ret != MHD_YES)
        return OGS_ERROR;

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
