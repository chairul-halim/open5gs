
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "n2_interface_amf_info.h"

ogs_sbi_n2_interface_amf_info_t *ogs_sbi_n2_interface_amf_info_create(
    ogs_sbi_list_t *ipv4_endpoint_address,
    ogs_sbi_list_t *ipv6_endpoint_address,
    char *amf_name
    )
{
    ogs_sbi_n2_interface_amf_info_t *n2_interface_amf_info_local_var = ogs_malloc(sizeof(ogs_sbi_n2_interface_amf_info_t));
    if (!n2_interface_amf_info_local_var) {
        return NULL;
    }
    n2_interface_amf_info_local_var->ipv4_endpoint_address = ipv4_endpoint_address;
    n2_interface_amf_info_local_var->ipv6_endpoint_address = ipv6_endpoint_address;
    n2_interface_amf_info_local_var->amf_name = amf_name;

    return n2_interface_amf_info_local_var;
}

void ogs_sbi_n2_interface_amf_info_free(ogs_sbi_n2_interface_amf_info_t *n2_interface_amf_info)
{
    if (NULL == n2_interface_amf_info) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_sbi_list_for_each(node, n2_interface_amf_info->ipv4_endpoint_address) {
        ogs_free(node->data);
    }
    ogs_sbi_list_free(n2_interface_amf_info->ipv4_endpoint_address);
    ogs_sbi_list_for_each(node, n2_interface_amf_info->ipv6_endpoint_address) {
        ogs_sbi_ipv6_addr_free(node->data);
    }
    ogs_sbi_list_free(n2_interface_amf_info->ipv6_endpoint_address);
    ogs_free(n2_interface_amf_info->amf_name);
    ogs_free(n2_interface_amf_info);
}

cJSON *ogs_sbi_n2_interface_amf_info_convertToJSON(ogs_sbi_n2_interface_amf_info_t *n2_interface_amf_info)
{
    cJSON *item = cJSON_CreateObject();
    if (n2_interface_amf_info->ipv4_endpoint_address) {
        cJSON *ipv4_endpoint_address = cJSON_AddArrayToObject(item, "ipv4EndpointAddress");
        if (ipv4_endpoint_address == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *ipv4_endpoint_address_node;
        ogs_sbi_list_for_each(ipv4_endpoint_address_node, n2_interface_amf_info->ipv4_endpoint_address) {
            if (cJSON_AddStringToObject(ipv4_endpoint_address, "", (char*)ipv4_endpoint_address_node->data) == NULL) {
                goto fail;
            }
        }
    }

    if (n2_interface_amf_info->ipv6_endpoint_address) {
        cJSON *ipv6_endpoint_address = cJSON_AddArrayToObject(item, "ipv6EndpointAddress");
        if (ipv6_endpoint_address == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *ipv6_endpoint_address_node;
        if (n2_interface_amf_info->ipv6_endpoint_address) {
            ogs_sbi_list_for_each(ipv6_endpoint_address_node, n2_interface_amf_info->ipv6_endpoint_address) {
                cJSON *itemLocal = ogs_sbi_ipv6_addr_convertToJSON(ipv6_endpoint_address_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(ipv6_endpoint_address, itemLocal);
            }
        }
    }

    if (n2_interface_amf_info->amf_name) {
        if (cJSON_AddStringToObject(item, "amfName", n2_interface_amf_info->amf_name) == NULL) {
            goto fail;
        }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_n2_interface_amf_info_t *ogs_sbi_n2_interface_amf_info_parseFromJSON(cJSON *n2_interface_amf_infoJSON)
{
    ogs_sbi_n2_interface_amf_info_t *n2_interface_amf_info_local_var = NULL;
    cJSON *ipv4_endpoint_address = cJSON_GetObjectItemCaseSensitive(n2_interface_amf_infoJSON, "ipv4EndpointAddress");

    ogs_sbi_list_t *ipv4_endpoint_addressList;
    if (ipv4_endpoint_address) {
        cJSON *ipv4_endpoint_address_local;
        if (!cJSON_IsArray(ipv4_endpoint_address)) {
            goto end;
        }
        ipv4_endpoint_addressList = ogs_sbi_list_create();

        cJSON_ArrayForEach(ipv4_endpoint_address_local, ipv4_endpoint_address) {
            if (!cJSON_IsString(ipv4_endpoint_address_local)) {
                goto end;
            }
            ogs_sbi_list_add(ipv4_endpoint_addressList, ogs_strdup(ipv4_endpoint_address_local->valuestring));
        }
    }

    cJSON *ipv6_endpoint_address = cJSON_GetObjectItemCaseSensitive(n2_interface_amf_infoJSON, "ipv6EndpointAddress");

    ogs_sbi_list_t *ipv6_endpoint_addressList;
    if (ipv6_endpoint_address) {
        cJSON *ipv6_endpoint_address_local_nonprimitive;
        if (!cJSON_IsArray(ipv6_endpoint_address)) {
            goto end;
        }

        ipv6_endpoint_addressList = ogs_sbi_list_create();

        cJSON_ArrayForEach(ipv6_endpoint_address_local_nonprimitive,ipv6_endpoint_address ) {
            if (!cJSON_IsObject(ipv6_endpoint_address_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_ipv6_addr_t *ipv6_endpoint_addressItem = ogs_sbi_ipv6_addr_parseFromJSON(ipv6_endpoint_address_local_nonprimitive);

            ogs_sbi_list_add(ipv6_endpoint_addressList, ipv6_endpoint_addressItem);
        }
    }

    cJSON *amf_name = cJSON_GetObjectItemCaseSensitive(n2_interface_amf_infoJSON, "amfName");

    if (amf_name) {
        if (!cJSON_IsString(amf_name))
        {
            goto end;
        }
    }

    n2_interface_amf_info_local_var = ogs_sbi_n2_interface_amf_info_create (
        ipv4_endpoint_address ? ipv4_endpoint_addressList : NULL,
        ipv6_endpoint_address ? ipv6_endpoint_addressList : NULL,
        amf_name ? ogs_strdup(amf_name->valuestring) : NULL
        );

    return n2_interface_amf_info_local_var;
end:
    return NULL;
}

