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

#include "ogs-dbi.h"
#include "context.h"

static nrf_context_t self;

int __nrf_log_domain;

static int context_initiaized = 0;

void nrf_context_init(void)
{
    ogs_assert(context_initiaized == 0);

    /* Initialize NRF context */
    memset(&self, 0, sizeof(nrf_context_t));

    ogs_log_install_domain(&__ogs_dbi_domain, "dbi", ogs_core()->log.level);
    ogs_log_install_domain(&__ogs_sbi_domain, "sbi", ogs_core()->log.level);
    ogs_log_install_domain(&__nrf_log_domain, "nrf", ogs_core()->log.level);

    ogs_thread_mutex_init(&self.db_lock);

    context_initiaized = 1;
}

void nrf_context_final(void)
{
    ogs_assert(context_initiaized == 1);

    ogs_thread_mutex_destroy(&self.db_lock);

    context_initiaized = 0;
}

nrf_context_t *nrf_self(void)
{
    return &self;
}

static int nrf_context_prepare(void)
{
    return OGS_OK;
}

static int nrf_context_validation(void)
{
    return OGS_OK;
}

int nrf_context_parse_config(void)
{
    int rv;

    rv = nrf_context_prepare();
    if (rv != OGS_OK) return rv;

    rv = nrf_context_validation();
    if (rv != OGS_OK) return rv;

    return OGS_OK;
}

int nrf_db_init()
{
    int rv;

    rv = ogs_mongoc_init(ogs_config()->db_uri);
    if (rv != OGS_OK) return rv;

    if (ogs_mongoc()->client && ogs_mongoc()->name) {
        self.NFProfileCollection = mongoc_client_get_collection(
            ogs_mongoc()->client, ogs_mongoc()->name, "NFProfile");
        ogs_assert(self.NFProfileCollection);
    }

    return OGS_OK;
}

int nrf_db_final()
{
    if (self.NFProfileCollection) {
        mongoc_collection_destroy(self.NFProfileCollection);
    }

    ogs_mongoc_final();

    return OGS_OK;
}