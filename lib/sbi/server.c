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

#include "app/ogs-app.h"
#include "ogs-sbi.h"

static OGS_POOL(ogs_sbi_server_pool, ogs_sbi_server_t);

static int server_initialized = 0;

void ogs_sbi_server_init(void)
{
    ogs_assert(server_initialized == 0);

    ogs_pool_init(&ogs_sbi_server_pool, ogs_config()->pool.sbi);

    server_initialized = 1;
}

void ogs_sbi_server_final(void)
{
    ogs_assert(server_initialized == 1);

    ogs_pool_final(&ogs_sbi_server_pool);

    server_initialized = 0;
}

ogs_sbi_server_t *ogs_sbi_server_add(
        ogs_sockaddr_t *addr, void (*cb)(void *data), void *data)
{
    ogs_sbi_server_t *node = NULL;

    ogs_assert(addr);

    ogs_pool_alloc(&ogs_sbi_server_pool, &node);
    ogs_assert(node);
    memset(node, 0, sizeof(ogs_sbi_server_t));

    ogs_list_add(&ogs_sbi_self()->server_list, node);

    return node;
}

void ogs_sbi_server_remove(ogs_sbi_server_t *node)
{
    ogs_assert(node);

    ogs_list_remove(&ogs_sbi_self()->server_list, node);
    ogs_pool_free(&ogs_sbi_server_pool, node);
}

void ogs_sbi_server_remove_all(void)
{
    ogs_sbi_server_t *node = NULL, *next_node = NULL;

    ogs_list_for_each_safe(&ogs_sbi_self()->server_list, next_node, node)
        ogs_sbi_server_remove(node);
}
