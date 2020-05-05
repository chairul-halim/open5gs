
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "network_slice_cond.h"

ogs_sbi_network_slice_cond_t *ogs_sbi_network_slice_cond_create(
    ogs_sbi_list_t *snssai_list,
    ogs_sbi_list_t *nsi_list
    )
{
    ogs_sbi_network_slice_cond_t *network_slice_cond_local_var = ogs_malloc(sizeof(ogs_sbi_network_slice_cond_t));
    if (!network_slice_cond_local_var) {
        return NULL;
    }
    network_slice_cond_local_var->snssai_list = snssai_list;
    network_slice_cond_local_var->nsi_list = nsi_list;

    return network_slice_cond_local_var;
}

void ogs_sbi_network_slice_cond_free(ogs_sbi_network_slice_cond_t *network_slice_cond)
{
    if (NULL == network_slice_cond) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_sbi_list_for_each(node, network_slice_cond->snssai_list) {
        ogs_sbi_snssai_free(node->data);
    }
    ogs_sbi_list_free(network_slice_cond->snssai_list);
    ogs_sbi_list_for_each(node, network_slice_cond->nsi_list) {
        ogs_free(node->data);
    }
    ogs_sbi_list_free(network_slice_cond->nsi_list);
    ogs_free(network_slice_cond);
}

cJSON *ogs_sbi_network_slice_cond_convertToJSON(ogs_sbi_network_slice_cond_t *network_slice_cond)
{
    cJSON *item = cJSON_CreateObject();
    if (!network_slice_cond->snssai_list) {
        goto fail;
    }
    cJSON *snssai_list = cJSON_AddArrayToObject(item, "snssaiList");
    if (snssai_list == NULL) {
        goto fail;
    }

    ogs_sbi_lnode_t *snssai_list_node;
    if (network_slice_cond->snssai_list) {
        ogs_sbi_list_for_each(snssai_list_node, network_slice_cond->snssai_list) {
            cJSON *itemLocal = ogs_sbi_snssai_convertToJSON(snssai_list_node->data);
            if (itemLocal == NULL) {
                goto fail;
            }
            cJSON_AddItemToArray(snssai_list, itemLocal);
        }
    }

    if (network_slice_cond->nsi_list) {
        cJSON *nsi_list = cJSON_AddArrayToObject(item, "nsiList");
        if (nsi_list == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *nsi_list_node;
        ogs_sbi_list_for_each(nsi_list_node, network_slice_cond->nsi_list) {
            if (cJSON_AddStringToObject(nsi_list, "", (char*)nsi_list_node->data) == NULL) {
                goto fail;
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

ogs_sbi_network_slice_cond_t *ogs_sbi_network_slice_cond_parseFromJSON(cJSON *network_slice_condJSON)
{
    ogs_sbi_network_slice_cond_t *network_slice_cond_local_var = NULL;
    cJSON *snssai_list = cJSON_GetObjectItemCaseSensitive(network_slice_condJSON, "snssaiList");
    if (!snssai_list) {
        goto end;
    }

    ogs_sbi_list_t *snssai_listList;

    cJSON *snssai_list_local_nonprimitive;
    if (!cJSON_IsArray(snssai_list)) {
        goto end;
    }

    snssai_listList = ogs_sbi_list_create();

    cJSON_ArrayForEach(snssai_list_local_nonprimitive,snssai_list ) {
        if (!cJSON_IsObject(snssai_list_local_nonprimitive)) {
            goto end;
        }
        ogs_sbi_snssai_t *snssai_listItem = ogs_sbi_snssai_parseFromJSON(snssai_list_local_nonprimitive);

        ogs_sbi_list_add(snssai_listList, snssai_listItem);
    }

    cJSON *nsi_list = cJSON_GetObjectItemCaseSensitive(network_slice_condJSON, "nsiList");

    ogs_sbi_list_t *nsi_listList;
    if (nsi_list) {
        cJSON *nsi_list_local;
        if (!cJSON_IsArray(nsi_list)) {
            goto end;
        }
        nsi_listList = ogs_sbi_list_create();

        cJSON_ArrayForEach(nsi_list_local, nsi_list) {
            if (!cJSON_IsString(nsi_list_local)) {
                goto end;
            }
            ogs_sbi_list_add(nsi_listList, ogs_strdup(nsi_list_local->valuestring));
        }
    }

    network_slice_cond_local_var = ogs_sbi_network_slice_cond_create (
        snssai_listList,
        nsi_list ? nsi_listList : NULL
        );

    return network_slice_cond_local_var;
end:
    return NULL;
}

