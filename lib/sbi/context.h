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

#if !defined(OGS_SBI_INSIDE) && !defined(OGS_SBI_COMPILATION)
#error "This header cannot be included directly."
#endif

#ifndef OGS_SBI_CONTEXT_H
#define OGS_SBI_CONTEXT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_server_s {
    ogs_lnode_t     lnode;          /* A node of list_t */

    void (*cb)(void*);              /* callback function */
    void *data;                     /* callback argument */

    void            *mhd;           /* MHD instance */
    ogs_poll_t      *poll;          /* MHD server poll */
} ogs_sbi_server_t;

typedef struct ogs_sbi_context_s {
    ogs_queue_t     *queue;         /* Queue for processing UPF control */
    ogs_timer_mgr_t *timer_mgr;     /* Timer Manager */
    ogs_pollset_t   *pollset;       /* Poll Set for I/O Multiplexing */

    uint32_t        http_port;      /* SBI HTTP local port */
    uint32_t        https_port;     /* SBI HTTPS local port */

    ogs_list_t      server_list;                /* SBI Server list */
    OGS_POOL(server_pool, ogs_sbi_server_t);    /* SBI server pool */

} ogs_sbi_context_t;

void ogs_sbi_context_init(
    ogs_queue_t *queue, ogs_timer_mgr_t *timer_mgr, ogs_pollset_t *pollset);
void ogs_sbi_context_final(void);
ogs_sbi_context_t *ogs_sbi_self(void);
int ogs_sbi_context_parse_config(const char *local, const char *remote);

#ifdef __cplusplus
}
#endif

#endif /* OGS_SBI_CONTEXT_H */
