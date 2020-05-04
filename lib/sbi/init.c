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

#include "mhd/ulfius.h"

#define PREFIX "/test"
#define PREFIXJSON "/testjson"
#define PREFIXCOOKIE "/testcookie"

#define PROXY_DEST "https://www.wikipedia.org"

int __ogs_sbi_domain;

static struct _u_instance instance;

char *print_map(const struct _u_map *map)
{
    char *line, *to_return = NULL;
    const char **keys, *value;
    int len, i;
    if (map != NULL) {
        keys = u_map_enum_keys(map);
        for (i = 0; keys[i] != NULL; i++) {
            value = u_map_get(map, keys[i]);
            len = snprintf(NULL, 0, "key is %s, value is %s", keys[i], value);
            line = o_malloc((len+1)*sizeof(char));
            snprintf(line, (len+1), "key is %s, value is %s", keys[i], value);
            if (to_return != NULL) {
                len = ogs_strlen(to_return) + ogs_strlen(line) + 1;
                to_return = o_realloc(to_return, (len+1)*sizeof(char));
                if (ogs_strlen(to_return) > 0) {
                    strcat(to_return, "\n");
                }
            } else {
                to_return = o_malloc((ogs_strlen(line) + 1)*sizeof(char));
                to_return[0] = 0;
            }
            strcat(to_return, line);
            o_free(line);
        }
        return to_return;
    } else {
        return NULL;
    }
}

int callback_get_test (const struct _u_request * request,
        struct _u_response * response, void * user_data) {
  ulfius_set_string_body_response(response, 200, "Hello World!");
  return U_CALLBACK_CONTINUE;
}

/**
 * Callback function that put an empty response and a status 200
 */
int callback_get_empty_response (const struct _u_request * request,
        struct _u_response * response, void * user_data) {
  return U_CALLBACK_CONTINUE;
}


int callback_post_test (const struct _u_request * request,
        struct _u_response * response, void * user_data)
{
    char *post_params = print_map(request->map_post_body);
    char *response_body = msprintf("Hello World!\n%s", post_params);
    ulfius_set_string_body_response(response, 200, response_body);
    o_free(response_body);
    o_free(post_params);

    return U_CALLBACK_CONTINUE;
}

int callback_all_test_foo(const struct _u_request *request,
        struct _u_response *response, void *user_data) {
    char *url_params = print_map(request->map_url);
    char *headers = print_map(request->map_header);
    char *cookies = print_map(request->map_cookie);
    char *post_params = print_map(request->map_post_body);

    char *response_body = msprintf("Hello World!\n\n  method is %s\n  "
        "url is %s\n\n  parameters from the url are \n%s\n\n  "
        "cookies are \n%s\n\n  headers are \n%s\n\n  "
        "post parameters are \n%s\n\n  user data is %s\n\n"
        "client address is %s\n\n",
        request->http_verb, request->http_url, url_params,
        cookies, headers, post_params, (char *)user_data,
        inet_ntoa(((struct sockaddr_in *)request->client_address)->sin_addr));
    ulfius_set_string_body_response(response, 200, response_body);
    o_free(url_params);
    o_free(headers);
    o_free(cookies);
    o_free(post_params);
    o_free(response_body);
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

    ulfius_add_endpoint_by_val(&instance, "GET", PREFIX,
            NULL, 0, &callback_get_test, NULL);
    ulfius_add_endpoint_by_val(&instance, "GET", PREFIX,
            "/empty", 0, &callback_get_empty_response, NULL);
    ulfius_add_endpoint_by_val(&instance, "GET", PREFIX,
            "/multiple/:multiple/:multiple/:not_multiple", 0,
            &callback_all_test_foo, NULL);
    ulfius_add_endpoint_by_val(&instance, "POST", PREFIX,
            NULL, 0, &callback_post_test, NULL);
    ulfius_add_endpoint_by_val(&instance, "GET", PREFIX,
            "/param/:foo", 0, &callback_all_test_foo, "user data 1");
    ulfius_add_endpoint_by_val(&instance, "POST", PREFIX,
            "/param/:foo", 0, &callback_all_test_foo, "user data 2");

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
