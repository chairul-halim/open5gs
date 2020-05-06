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

#ifndef OGS_SBI_SERVER_H
#define OGS_SBI_SERVER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_server_s {
    ogs_lnode_t     lnode;          /* A node of list_t */

    int             (*cb)(void*);   /* callback handler */

    ogs_list_t      suspended_conn_list; /* MHD suspeconnection list */

    void            *mhd;           /* MHD instance */
    ogs_poll_t      *poll;          /* MHD server poll */
} ogs_sbi_server_t;

void ogs_sbi_server_init(void);
void ogs_sbi_server_final(void);

ogs_sbi_server_t *ogs_sbi_server_add(
        ogs_sockaddr_t *addr, int (*cb)(void *data));
void ogs_sbi_server_remove(ogs_sbi_server_t *server);
void ogs_sbi_server_remove_all(void);

#ifdef __cplusplus
}
#endif

#endif /* OGS_SBI_SERVER_H */
