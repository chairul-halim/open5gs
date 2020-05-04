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

static int initialized = 0;

int nrf_initialize()
{
    int rv;

    nrf_context_init();

    rv = nrf_context_parse_config();
    if (rv != OGS_OK) return rv;

    rv = ogs_log_config_domain(
            ogs_config()->logger.domain, ogs_config()->logger.level);
    if (rv != OGS_OK) return rv;

    rv = nrf_db_init();
    if (rv != OGS_OK) return rv;

    rv = ogs_sbi_init(8080);
    if (rv != OGS_OK) return OGS_ERROR;

    initialized = 1;

    return OGS_OK;
}

void nrf_terminate(void)
{
    if (!initialized) return;

    ogs_sbi_final();
    nrf_db_final();

    nrf_context_final();
}
