
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bsf_info.h"

ogs_sbi_bsf_info_t *ogs_sbi_bsf_info_create(
    ogs_sbi_list_t *dnn_list,
    ogs_sbi_list_t *ip_domain_list,
    ogs_sbi_list_t *ipv4_address_ranges,
    ogs_sbi_list_t *ipv6_prefix_ranges
    )
{
    ogs_sbi_bsf_info_t *bsf_info_local_var = ogs_malloc(sizeof(ogs_sbi_bsf_info_t));
    if (!bsf_info_local_var) {
        return NULL;
    }
    bsf_info_local_var->dnn_list = dnn_list;
    bsf_info_local_var->ip_domain_list = ip_domain_list;
    bsf_info_local_var->ipv4_address_ranges = ipv4_address_ranges;
    bsf_info_local_var->ipv6_prefix_ranges = ipv6_prefix_ranges;

    return bsf_info_local_var;
}

void ogs_sbi_bsf_info_free(ogs_sbi_bsf_info_t *bsf_info)
{
    if (NULL == bsf_info) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_sbi_list_for_each(node, bsf_info->dnn_list) {
        ogs_free(node->data);
    }
    ogs_sbi_list_free(bsf_info->dnn_list);
    ogs_sbi_list_for_each(node, bsf_info->ip_domain_list) {
        ogs_free(node->data);
    }
    ogs_sbi_list_free(bsf_info->ip_domain_list);
    ogs_sbi_list_for_each(node, bsf_info->ipv4_address_ranges) {
        ogs_sbi_ipv4_address_range_free(node->data);
    }
    ogs_sbi_list_free(bsf_info->ipv4_address_ranges);
    ogs_sbi_list_for_each(node, bsf_info->ipv6_prefix_ranges) {
        ogs_sbi_ipv6_prefix_range_free(node->data);
    }
    ogs_sbi_list_free(bsf_info->ipv6_prefix_ranges);
    ogs_free(bsf_info);
}

cJSON *ogs_sbi_bsf_info_convertToJSON(ogs_sbi_bsf_info_t *bsf_info)
{
    cJSON *item = cJSON_CreateObject();
    if (bsf_info->dnn_list) {
        cJSON *dnn_list = cJSON_AddArrayToObject(item, "dnnList");
        if (dnn_list == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *dnn_list_node;
        ogs_sbi_list_for_each(dnn_list_node, bsf_info->dnn_list) {
            if (cJSON_AddStringToObject(dnn_list, "", (char*)dnn_list_node->data) == NULL) {
                goto fail;
            }
        }
    }

    if (bsf_info->ip_domain_list) {
        cJSON *ip_domain_list = cJSON_AddArrayToObject(item, "ipDomainList");
        if (ip_domain_list == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *ip_domain_list_node;
        ogs_sbi_list_for_each(ip_domain_list_node, bsf_info->ip_domain_list) {
            if (cJSON_AddStringToObject(ip_domain_list, "", (char*)ip_domain_list_node->data) == NULL) {
                goto fail;
            }
        }
    }

    if (bsf_info->ipv4_address_ranges) {
        cJSON *ipv4_address_ranges = cJSON_AddArrayToObject(item, "ipv4AddressRanges");
        if (ipv4_address_ranges == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *ipv4_address_ranges_node;
        if (bsf_info->ipv4_address_ranges) {
            ogs_sbi_list_for_each(ipv4_address_ranges_node, bsf_info->ipv4_address_ranges) {
                cJSON *itemLocal = ogs_sbi_ipv4_address_range_convertToJSON(ipv4_address_ranges_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(ipv4_address_ranges, itemLocal);
            }
        }
    }

    if (bsf_info->ipv6_prefix_ranges) {
        cJSON *ipv6_prefix_ranges = cJSON_AddArrayToObject(item, "ipv6PrefixRanges");
        if (ipv6_prefix_ranges == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *ipv6_prefix_ranges_node;
        if (bsf_info->ipv6_prefix_ranges) {
            ogs_sbi_list_for_each(ipv6_prefix_ranges_node, bsf_info->ipv6_prefix_ranges) {
                cJSON *itemLocal = ogs_sbi_ipv6_prefix_range_convertToJSON(ipv6_prefix_ranges_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(ipv6_prefix_ranges, itemLocal);
            }
        }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_bsf_info_t *ogs_sbi_bsf_info_parseFromJSON(cJSON *bsf_infoJSON)
{
    ogs_sbi_bsf_info_t *bsf_info_local_var = NULL;
    cJSON *dnn_list = cJSON_GetObjectItemCaseSensitive(bsf_infoJSON, "dnnList");

    ogs_sbi_list_t *dnn_listList;
    if (dnn_list) {
        cJSON *dnn_list_local;
        if (!cJSON_IsArray(dnn_list)) {
            goto end;
        }
        dnn_listList = ogs_sbi_list_create();

        cJSON_ArrayForEach(dnn_list_local, dnn_list) {
            if (!cJSON_IsString(dnn_list_local)) {
                goto end;
            }
            ogs_sbi_list_add(dnn_listList, ogs_strdup(dnn_list_local->valuestring));
        }
    }

    cJSON *ip_domain_list = cJSON_GetObjectItemCaseSensitive(bsf_infoJSON, "ipDomainList");

    ogs_sbi_list_t *ip_domain_listList;
    if (ip_domain_list) {
        cJSON *ip_domain_list_local;
        if (!cJSON_IsArray(ip_domain_list)) {
            goto end;
        }
        ip_domain_listList = ogs_sbi_list_create();

        cJSON_ArrayForEach(ip_domain_list_local, ip_domain_list) {
            if (!cJSON_IsString(ip_domain_list_local)) {
                goto end;
            }
            ogs_sbi_list_add(ip_domain_listList, ogs_strdup(ip_domain_list_local->valuestring));
        }
    }

    cJSON *ipv4_address_ranges = cJSON_GetObjectItemCaseSensitive(bsf_infoJSON, "ipv4AddressRanges");

    ogs_sbi_list_t *ipv4_address_rangesList;
    if (ipv4_address_ranges) {
        cJSON *ipv4_address_ranges_local_nonprimitive;
        if (!cJSON_IsArray(ipv4_address_ranges)) {
            goto end;
        }

        ipv4_address_rangesList = ogs_sbi_list_create();

        cJSON_ArrayForEach(ipv4_address_ranges_local_nonprimitive,ipv4_address_ranges ) {
            if (!cJSON_IsObject(ipv4_address_ranges_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_ipv4_address_range_t *ipv4_address_rangesItem = ogs_sbi_ipv4_address_range_parseFromJSON(ipv4_address_ranges_local_nonprimitive);

            ogs_sbi_list_add(ipv4_address_rangesList, ipv4_address_rangesItem);
        }
    }

    cJSON *ipv6_prefix_ranges = cJSON_GetObjectItemCaseSensitive(bsf_infoJSON, "ipv6PrefixRanges");

    ogs_sbi_list_t *ipv6_prefix_rangesList;
    if (ipv6_prefix_ranges) {
        cJSON *ipv6_prefix_ranges_local_nonprimitive;
        if (!cJSON_IsArray(ipv6_prefix_ranges)) {
            goto end;
        }

        ipv6_prefix_rangesList = ogs_sbi_list_create();

        cJSON_ArrayForEach(ipv6_prefix_ranges_local_nonprimitive,ipv6_prefix_ranges ) {
            if (!cJSON_IsObject(ipv6_prefix_ranges_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_ipv6_prefix_range_t *ipv6_prefix_rangesItem = ogs_sbi_ipv6_prefix_range_parseFromJSON(ipv6_prefix_ranges_local_nonprimitive);

            ogs_sbi_list_add(ipv6_prefix_rangesList, ipv6_prefix_rangesItem);
        }
    }

    bsf_info_local_var = ogs_sbi_bsf_info_create (
        dnn_list ? dnn_listList : NULL,
        ip_domain_list ? ip_domain_listList : NULL,
        ipv4_address_ranges ? ipv4_address_rangesList : NULL,
        ipv6_prefix_ranges ? ipv6_prefix_rangesList : NULL
        );

    return bsf_info_local_var;
end:
    return NULL;
}

