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

#include "ulfius.h"

int __ogs_sbi_domain;

static struct _u_instance instance;

int callback_hello_world(const struct _u_request * request,
        struct _u_response * response, void * user_data)
{
    ulfius_set_string_body_response(response, 200, "Hello World!");
    return U_CALLBACK_CONTINUE;
}

int ogs_sbi_init(uint16_t port)
{
    int rv;

    rv = ulfius_init_instance(&instance, port, NULL, NULL);
    if (rv != OGS_OK) {
        ogs_error("ulfius_init_instance(%d) failed", port);
        return OGS_ERROR;
    }

    ulfius_add_endpoint_by_val(&instance,
            "GET", "/helloworld", NULL, 0, &callback_hello_world, NULL);

    rv = ulfius_start_framework(&instance);
    if (rv != OGS_OK) {
        ogs_error("ulfius_start_framework(%d) failed", port);
        return OGS_ERROR;
    }

    return OGS_OK;
}

void ogs_sbi_final(void)
{
    int rv;
    rv = ulfius_stop_framework(&instance);
    if (rv != OGS_OK)
        ogs_error("ulfius_stop_framework failed");

    ulfius_clean_instance(&instance);
}
