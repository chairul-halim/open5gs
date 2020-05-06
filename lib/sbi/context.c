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

int __ogs_sbi_domain;

static ogs_sbi_context_t self;

static int context_initialized = 0;

void ogs_sbi_context_init(ogs_pollset_t *pollset)
{
    ogs_assert(context_initialized == 0);

    /* Initialize SMF context */
    memset(&self, 0, sizeof(ogs_sbi_context_t));

    ogs_assert(pollset);
    self.pollset = pollset;

    ogs_log_install_domain(&__ogs_sbi_domain, "sbi", ogs_core()->log.level);
    ogs_sbi_server_init();

    context_initialized = 1;
}

void ogs_sbi_context_final(void)
{
    ogs_assert(context_initialized == 1);

    ogs_sbi_server_final();

    context_initialized = 0;
}

ogs_sbi_context_t *ogs_sbi_self(void)
{
    return &self;
}

static int ogs_sbi_context_prepare(void)
{
    self.http_port = OGS_SBI_HTTP_PORT;
    self.https_port = OGS_SBI_HTTPS_PORT;

    return OGS_OK;
}

static int ogs_sbi_context_validation(const char *local)
{
#if 0
    if (ogs_list_first(&self.server_list) == NULL) {
        ogs_error("No %s.sbi: in '%s'", local, ogs_config()->file);
        return OGS_ERROR;
    }
#endif

    return OGS_OK;
}

int ogs_sbi_context_parse_config(const char *local, const char *remote)
{
    int rv;
    yaml_document_t *document = NULL;
#if 0
    ogs_yaml_iter_t root_iter;
#endif

    document = ogs_config()->document;
    ogs_assert(document);

    rv = ogs_sbi_context_prepare();
    if (rv != OGS_OK) return rv;

#if 0
    ogs_yaml_iter_init(&root_iter, document);
    while (ogs_yaml_iter_next(&root_iter)) {
        const char *root_key = ogs_yaml_iter_key(&root_iter);
        ogs_assert(root_key);
        if (!strcmp(root_key, local)) {
            ogs_yaml_iter_t local_iter;
            ogs_yaml_iter_recurse(&root_iter, &local_iter);
            while (ogs_yaml_iter_next(&local_iter)) {
                const char *local_key = ogs_yaml_iter_key(&local_iter);
                ogs_assert(local_key);
                if (!strcmp(local_key, "sbi")) {
                    ogs_yaml_iter_t sbi_array, sbi_iter;
                    ogs_yaml_iter_recurse(&local_iter, &sbi_array);
                    do {
                        int family = AF_UNSPEC;
                        int i, num = 0;
                        const char *hostname[OGS_MAX_NUM_OF_HOSTNAME];
                        uint16_t port = self.sbi_port;
                        const char *dev = NULL;
                        ogs_sockaddr_t *addr = NULL;

                        if (ogs_yaml_iter_type(&sbi_array) ==
                                YAML_MAPPING_NODE) {
                            memcpy(&sbi_iter, &sbi_array,
                                    sizeof(ogs_yaml_iter_t));
                        } else if (ogs_yaml_iter_type(&sbi_array) ==
                            YAML_SEQUENCE_NODE) {
                            if (!ogs_yaml_iter_next(&sbi_array))
                                break;
                            ogs_yaml_iter_recurse(&sbi_array, &sbi_iter);
                        } else if (ogs_yaml_iter_type(&sbi_array) ==
                            YAML_SCALAR_NODE) {
                            break;
                        } else
                            ogs_assert_if_reached();

                        while (ogs_yaml_iter_next(&sbi_iter)) {
                            const char *sbi_key =
                                ogs_yaml_iter_key(&sbi_iter);
                            ogs_assert(sbi_key);
                            if (!strcmp(sbi_key, "family")) {
                                const char *v = ogs_yaml_iter_value(&sbi_iter);
                                if (v) family = atoi(v);
                                if (family != AF_UNSPEC &&
                                    family != AF_INET && family != AF_INET6) {
                                    ogs_warn("Ignore family(%d) : "
                                        "AF_UNSPEC(%d), "
                                        "AF_INET(%d), AF_INET6(%d) ", 
                                        family, AF_UNSPEC, AF_INET, AF_INET6);
                                    family = AF_UNSPEC;
                                }
                            } else if (!strcmp(sbi_key, "addr") ||
                                    !strcmp(sbi_key, "name")) {
                                ogs_yaml_iter_t hostname_iter;
                                ogs_yaml_iter_recurse(&sbi_iter,
                                        &hostname_iter);
                                ogs_assert(ogs_yaml_iter_type(&hostname_iter) !=
                                    YAML_MAPPING_NODE);

                                do {
                                    if (ogs_yaml_iter_type(&hostname_iter) ==
                                            YAML_SEQUENCE_NODE) {
                                        if (!ogs_yaml_iter_next(
                                                    &hostname_iter))
                                            break;
                                    }

                                    ogs_assert(num <= OGS_MAX_NUM_OF_HOSTNAME);
                                    hostname[num++] = 
                                        ogs_yaml_iter_value(&hostname_iter);
                                } while (
                                    ogs_yaml_iter_type(&hostname_iter) ==
                                        YAML_SEQUENCE_NODE);
                            } else if (!strcmp(sbi_key, "port")) {
                                const char *v = ogs_yaml_iter_value(&sbi_iter);
                                if (v) {
                                    port = atoi(v);
                                    self.sbi_port = port;
                                }
                            } else if (!strcmp(sbi_key, "dev")) {
                                dev = ogs_yaml_iter_value(&sbi_iter);
                            } else if (!strcmp(sbi_key, "apn")) {
                                /* Skip */
                            } else
                                ogs_warn("unknown key `%s`", sbi_key);
                        }

                        addr = NULL;
                        for (i = 0; i < num; i++) {
                            rv = ogs_addaddrinfo(&addr,
                                    family, hostname[i], port, 0);
                            ogs_assert(rv == OGS_OK);
                        }

                        if (addr) {
                            if (ogs_config()->parameter.no_ipv4 == 0)
                                ogs_socknode_add(
                                        &self.sbi_list, AF_INET, addr);
                            if (ogs_config()->parameter.no_ipv6 == 0)
                                ogs_socknode_add(
                                        &self.sbi_list6, AF_INET6, addr);
                            ogs_freeaddrinfo(addr);
                        }

                        if (dev) {
                            rv = ogs_socknode_probe(
                                    ogs_config()->parameter.no_ipv4 ?
                                        NULL : &self.sbi_list,
                                    ogs_config()->parameter.no_ipv6 ?
                                        NULL : &self.sbi_list6,
                                    dev, self.sbi_port);
                            ogs_assert(rv == OGS_OK);
                        }

                    } while (ogs_yaml_iter_type(&sbi_array) ==
                            YAML_SEQUENCE_NODE);

                    if (ogs_list_first(&self.sbi_list) == NULL &&
                        ogs_list_first(&self.sbi_list6) == NULL) {
                        rv = ogs_socknode_probe(
                                ogs_config()->parameter.no_ipv4 ?
                                    NULL : &self.sbi_list,
                                ogs_config()->parameter.no_ipv6 ?
                                    NULL : &self.sbi_list6,
                                NULL, self.sbi_port);
                        ogs_assert(rv == OGS_OK);
                    }
                } else if (!strcmp(local_key, "pdn")) {
                    ogs_yaml_iter_t pdn_array, pdn_iter;
                    ogs_yaml_iter_recurse(&local_iter, &pdn_array);

                    do {
                        ogs_sbi_subnet_t *subnet = NULL;
                        const char *ipstr = NULL;
                        const char *mask_or_numbits = NULL;
                        const char *apn = NULL;
                        const char *dev = self.tun_ifname;
                        const char *low[MAX_NUM_OF_SUBNET_RANGE];
                        const char *high[MAX_NUM_OF_SUBNET_RANGE];
                        int i, num = 0;

                        if (ogs_yaml_iter_type(&pdn_array) ==
                                YAML_MAPPING_NODE) {
                            memcpy(&pdn_iter, &pdn_array,
                                    sizeof(ogs_yaml_iter_t));
                        } else if (ogs_yaml_iter_type(&pdn_array) ==
                                YAML_SEQUENCE_NODE) {
                            if (!ogs_yaml_iter_next(&pdn_array))
                                break;
                            ogs_yaml_iter_recurse(&pdn_array, &pdn_iter);
                        } else if (ogs_yaml_iter_type(&pdn_array) ==
                                YAML_SCALAR_NODE) {
                            break;
                        } else
                            ogs_assert_if_reached();

                        while (ogs_yaml_iter_next(&pdn_iter)) {
                            const char *pdn_key = ogs_yaml_iter_key(&pdn_iter);
                            ogs_assert(pdn_key);
                            if (!strcmp(pdn_key, "addr")) {
                                char *v =
                                    (char *)ogs_yaml_iter_value(&pdn_iter);
                                if (v) {
                                    ipstr = (const char *)strsep(&v, "/");
                                    if (ipstr) {
                                        mask_or_numbits = (const char *)v;
                                    }
                                }
                            } else if (!strcmp(pdn_key, "apn")) {
                                apn = ogs_yaml_iter_value(&pdn_iter);
                            } else if (!strcmp(pdn_key, "dev")) {
                                dev = ogs_yaml_iter_value(&pdn_iter);
                            } else if (!strcmp(pdn_key, "range")) {
                                ogs_yaml_iter_t range_iter;
                                ogs_yaml_iter_recurse(&pdn_iter, &range_iter);
                                ogs_assert(ogs_yaml_iter_type(&range_iter) !=
                                    YAML_MAPPING_NODE);
                                do {
                                    char *v = NULL;

                                    if (ogs_yaml_iter_type(&range_iter) ==
                                            YAML_SEQUENCE_NODE) {
                                        if (!ogs_yaml_iter_next(&range_iter))
                                            break;
                                    }

                                    v = (char *)
                                        ogs_yaml_iter_value(&range_iter);
                                    if (v) {
                                        ogs_assert(num <=
                                                MAX_NUM_OF_SUBNET_RANGE);
                                        low[num] =
                                            (const char *)strsep(&v, "-");
                                        if (low[num] && strlen(low[num]) == 0)
                                            low[num] = NULL;

                                        high[num] = (const char *)v;
                                        if (high[num] && strlen(high[num]) == 0)
                                            high[num] = NULL;
                                    }

                                    if (low[num] || high[num]) num++;
                                } while (
                                    ogs_yaml_iter_type(&range_iter) ==
                                    YAML_SEQUENCE_NODE);
                            } else
                                ogs_warn("unknown key `%s`", pdn_key);
                        }

                        subnet = ogs_sbi_subnet_add(
                                ipstr, mask_or_numbits, apn, dev);
                        ogs_assert(subnet);

                        subnet->num_of_range = num;
                        for (i = 0; i < subnet->num_of_range; i++) {
                            subnet->range[i].low = low[i];
                            subnet->range[i].high = high[i];
                        }

                    } while (ogs_yaml_iter_type(&pdn_array) ==
                            YAML_SEQUENCE_NODE);

                    if (ogs_list_first(&self.subnet_list) == NULL) {
                        /* The followings are default configuration
                         * if no PDN configration */
                        ogs_sbi_subnet_t *subnet = NULL;

#if defined(__linux)
                        /*
                         * On Linux, we can use a persitent tun/tap interface
                         * which has already been setup. As such,
                         * we do not need to get the IP address
                         * from configuration.
                         *
                         * If there is no APN and TUN mapping,
                         * the default subnet is added with `ogstun` name
                         */
                        subnet = ogs_sbi_subnet_add(
                                NULL, NULL, NULL, self.tun_ifname);
                        ogs_assert(subnet);
#else
                        /*
                         * On MacOSX/FreeBSD, There is no persitent tun/tap
                         * interface, TUN IP address is required.
                         * The default configuration is same as below.
                         *
                         *   pdn:
                         *     - addr: 10.45.0.1/16
                         *     - addr: cafe::1/64
                         */
                        subnet = ogs_sbi_subnet_add(
                                "10.45.0.1", "16", NULL, self.tun_ifname);
                        ogs_assert(subnet);
                        subnet = ogs_sbi_subnet_add(
                                "cafe::1", "64", NULL, self.tun_ifname);
                        ogs_assert(subnet);
#endif
                    }
                }
            }
        } else if (!strcmp(root_key, remote)) {
            ogs_yaml_iter_t remote_iter;
            ogs_yaml_iter_recurse(&root_iter, &remote_iter);
            while (ogs_yaml_iter_next(&remote_iter)) {
                const char *remote_key = ogs_yaml_iter_key(&remote_iter);
                ogs_assert(remote_key);
                if (!strcmp(remote_key, "sbi")) {
                    ogs_yaml_iter_t sbi_array, sbi_iter;
                    ogs_yaml_iter_recurse(&remote_iter, &sbi_array);
                    do {
                        ogs_sbi_server_t *node = NULL;
                        ogs_sockaddr_t *addr = NULL;
                        int family = AF_UNSPEC;
                        int i, num = 0;
                        const char *hostname[OGS_MAX_NUM_OF_HOSTNAME];
                        uint16_t port = self.sbi_port;
                        uint16_t tac[OGS_MAX_NUM_OF_TAI] = {0,};
                        uint8_t num_of_tac = 0;

                        if (ogs_yaml_iter_type(&sbi_array) ==
                                YAML_MAPPING_NODE) {
                            memcpy(&sbi_iter, &sbi_array,
                                    sizeof(ogs_yaml_iter_t));
                        } else if (ogs_yaml_iter_type(&sbi_array) ==
                            YAML_SEQUENCE_NODE) {
                            if (!ogs_yaml_iter_next(&sbi_array))
                                break;
                            ogs_yaml_iter_recurse(&sbi_array, &sbi_iter);
                        } else if (ogs_yaml_iter_type(&sbi_array) ==
                                YAML_SCALAR_NODE) {
                            break;
                        } else
                            ogs_assert_if_reached();

                        while (ogs_yaml_iter_next(&sbi_iter)) {
                            const char *sbi_key =
                                ogs_yaml_iter_key(&sbi_iter);
                            ogs_assert(sbi_key);
                            if (!strcmp(sbi_key, "family")) {
                                const char *v = ogs_yaml_iter_value(&sbi_iter);
                                if (v) family = atoi(v);
                                if (family != AF_UNSPEC &&
                                    family != AF_INET && family != AF_INET6) {
                                    ogs_warn("Ignore family(%d) : "
                                        "AF_UNSPEC(%d), "
                                        "AF_INET(%d), AF_INET6(%d) ", 
                                        family, AF_UNSPEC, AF_INET, AF_INET6);
                                    family = AF_UNSPEC;
                                }
                            } else if (!strcmp(sbi_key, "addr") ||
                                    !strcmp(sbi_key, "name")) {
                                ogs_yaml_iter_t hostname_iter;
                                ogs_yaml_iter_recurse(&sbi_iter,
                                        &hostname_iter);
                                ogs_assert(ogs_yaml_iter_type(&hostname_iter) !=
                                    YAML_MAPPING_NODE);

                                do {
                                    if (ogs_yaml_iter_type(&hostname_iter) ==
                                            YAML_SEQUENCE_NODE) {
                                        if (!ogs_yaml_iter_next(&hostname_iter))
                                            break;
                                    }

                                    ogs_assert(num <= OGS_MAX_NUM_OF_HOSTNAME);
                                    hostname[num++] = 
                                        ogs_yaml_iter_value(&hostname_iter);
                                } while (
                                    ogs_yaml_iter_type(&hostname_iter) ==
                                        YAML_SEQUENCE_NODE);
                            } else if (!strcmp(sbi_key, "port")) {
                                const char *v = ogs_yaml_iter_value(&sbi_iter);
                                if (v) port = atoi(v);
                            } else if (!strcmp(sbi_key, "tac")) {
                                ogs_yaml_iter_t tac_iter;
                                ogs_yaml_iter_recurse(&sbi_iter, &tac_iter);
                                ogs_assert(ogs_yaml_iter_type(&tac_iter) !=
                                    YAML_MAPPING_NODE);

                                do {
                                    const char *v = NULL;

                                    ogs_assert(num_of_tac <=
                                            OGS_MAX_NUM_OF_TAI);
                                    if (ogs_yaml_iter_type(&tac_iter) ==
                                            YAML_SEQUENCE_NODE) {
                                        if (!ogs_yaml_iter_next(&tac_iter))
                                            break;
                                    }

                                    v = ogs_yaml_iter_value(&tac_iter);
                                    if (v) {
                                        tac[num_of_tac] = atoi(v);
                                        num_of_tac++;
                                    }
                                } while (
                                    ogs_yaml_iter_type(&tac_iter) ==
                                        YAML_SEQUENCE_NODE);
                            } else
                                ogs_warn("unknown key `%s`", sbi_key);
                        }

                        addr = NULL;
                        for (i = 0; i < num; i++) {
                            rv = ogs_addaddrinfo(&addr,
                                    family, hostname[i], port, 0);
                            ogs_assert(rv == OGS_OK);
                        }

                        ogs_filter_ip_version(&addr,
                                ogs_config()->parameter.no_ipv4,
                                ogs_config()->parameter.no_ipv6,
                                ogs_config()->parameter.prefer_ipv4);

                        node = ogs_sbi_server_new(addr);
                        ogs_assert(node);
                        ogs_list_add(&self.n4_list, node);

                        node->num_of_tac = num_of_tac;
                        if (num_of_tac != 0)
                            memcpy(node->tac, tac, sizeof(node->tac));

                    } while (ogs_yaml_iter_type(&sbi_array) ==
                            YAML_SEQUENCE_NODE);
                }
            }
        }
    }
#endif

    rv = ogs_sbi_context_validation(local);
    if (rv != OGS_OK) return rv;

    return OGS_OK;
}
