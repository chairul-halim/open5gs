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

#include "ogs-sbi.h"

#if 0
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
    static int aptr;
    const char *me = cls;
    struct MHD_Response *response;
    int ret;

    (void) url;               /* Unused. Silent compiler warning. */
    (void) version;           /* Unused. Silent compiler warning. */
    (void) upload_data;       /* Unused. Silent compiler warning. */
    (void) upload_data_size;  /* Unused. Silent compiler warning. */

    if (0 != strcmp (method, "GET"))
        return MHD_NO;              /* unexpected method */
    if (&aptr != *ptr) {
        /* do never respond on first call */
        *ptr = &aptr;
        return MHD_YES;
    }
    *ptr = NULL;                  /* reset when done */
    response = MHD_create_response_from_buffer (strlen (me),
    (void *)me,
    MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response (connection,
            MHD_HTTP_OK,
            response);
    MHD_destroy_response (response);

    return ret;
}

int ogs_mhd_server(void)
{
    struct MHD_Daemon *d;
    fd_set rs;
    fd_set ws;
    fd_set es;
    MHD_socket max;

    /* initialize PRNG */
    d = MHD_start_daemon(MHD_USE_ERROR_LOG,
                        8080,
                        NULL, NULL,
                        &ahc_echo, PAGE,
                        MHD_OPTION_END);
    if (NULL == d)
        return 1;
    while (1) {
        max = 0;
        FD_ZERO(&rs);
        FD_ZERO(&ws);
        FD_ZERO(&es);
        if (MHD_YES != MHD_get_fdset (d, &rs, &ws, &es, &max))
            break; /* fatal internal error */

        if (-1 == select (max + 1, &rs, &ws, &es, NULL)) {
        if (EINTR != errno)
            abort ();
        }
        MHD_run (d);
    }
    MHD_stop_daemon (d);
    return 0;
}
#endif
