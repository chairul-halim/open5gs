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

#ifndef NRF_EVENT_H
#define NRF_EVENT_H

#include "ogs-core.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    NRF_EVT_BASE = OGS_FSM_USER_SIG,

    NRF_EVT_SBI_MESSAGE,

    NRF_EVT_TOP,

} nrf_event_e;

typedef struct nrf_event_s {
    int id;
    struct {
        void *connection;
    } server;
} nrf_event_t;

void nrf_event_init(void);
void nrf_event_term(void);
void nrf_event_final(void);

nrf_event_t *nrf_event_new(nrf_event_e id);
void nrf_event_free(nrf_event_t *e);

const char *nrf_event_get_name(nrf_event_t *e);

#ifdef __cplusplus
}
#endif

#endif /* NRF_EVENT_H */
