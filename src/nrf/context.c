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

static nrf_context_t self;

int __nrf_log_domain;

static int context_initiaized = 0;

void nrf_context_init(void)
{
    ogs_assert(context_initiaized == 0);

    /* Initialize NRF context */
    memset(&self, 0, sizeof(nrf_context_t));

    ogs_log_install_domain(&__nrf_log_domain, "nrf", ogs_core()->log.level);

    context_initiaized = 1;
}

void nrf_context_final(void)
{
    ogs_assert(context_initiaized == 1);

    context_initiaized = 0;
}

nrf_context_t *nrf_self(void)
{
    return &self;
}
