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

#ifndef SMF_TIMER_H
#define SMF_TIMER_H

#include "ogs-core.h"

#ifdef __cplusplus
extern "C" {
#endif

/* forward declaration */
typedef enum {
    SMF_TIMER_BASE = 0,

    SMF_TIMER_ASSOCIATION,
    SMF_TIMER_HEARTBEAT,

    MAX_NUM_OF_SMF_TIMER,

} smf_timer_e;

typedef struct smf_timer_cfg_s {
    int max_count;
    ogs_time_t duration;
} smf_timer_cfg_t;

smf_timer_cfg_t *smf_timer_cfg(smf_timer_e id);

const char *smf_timer_get_name(smf_timer_e id);

void smf_timer_association(void *data);
void smf_timer_heartbeat(void *data);

#ifdef __cplusplus
}
#endif

#endif /* SMF_TIMER_H */
