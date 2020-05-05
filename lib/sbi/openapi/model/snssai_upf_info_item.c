
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "snssai_upf_info_item.h"

ogs_sbi_snssai_upf_info_item_t *ogs_sbi_snssai_upf_info_item_create(
    ogs_sbi_snssai_t *s_nssai,
    ogs_sbi_list_t *dnn_upf_info_list
    )
{
    ogs_sbi_snssai_upf_info_item_t *snssai_upf_info_item_local_var = ogs_malloc(sizeof(ogs_sbi_snssai_upf_info_item_t));
    if (!snssai_upf_info_item_local_var) {
        return NULL;
    }
    snssai_upf_info_item_local_var->s_nssai = s_nssai;
    snssai_upf_info_item_local_var->dnn_upf_info_list = dnn_upf_info_list;

    return snssai_upf_info_item_local_var;
}

void ogs_sbi_snssai_upf_info_item_free(ogs_sbi_snssai_upf_info_item_t *snssai_upf_info_item)
{
    if (NULL == snssai_upf_info_item) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_sbi_snssai_free(snssai_upf_info_item->s_nssai);
    ogs_sbi_list_for_each(node, snssai_upf_info_item->dnn_upf_info_list) {
        ogs_sbi_dnn_upf_info_item_free(node->data);
    }
    ogs_sbi_list_free(snssai_upf_info_item->dnn_upf_info_list);
    ogs_free(snssai_upf_info_item);
}

cJSON *ogs_sbi_snssai_upf_info_item_convertToJSON(ogs_sbi_snssai_upf_info_item_t *snssai_upf_info_item)
{
    cJSON *item = cJSON_CreateObject();
    if (!snssai_upf_info_item->s_nssai) {
        goto fail;
    }
    cJSON *s_nssai_local_JSON = ogs_sbi_snssai_convertToJSON(snssai_upf_info_item->s_nssai);
    if (s_nssai_local_JSON == NULL) {
        goto fail;
    }
    cJSON_AddItemToObject(item, "sNssai", s_nssai_local_JSON);
    if (item->child == NULL) {
        goto fail;
    }

    if (!snssai_upf_info_item->dnn_upf_info_list) {
        goto fail;
    }
    cJSON *dnn_upf_info_list = cJSON_AddArrayToObject(item, "dnnUpfInfoList");
    if (dnn_upf_info_list == NULL) {
        goto fail;
    }

    ogs_sbi_lnode_t *dnn_upf_info_list_node;
    if (snssai_upf_info_item->dnn_upf_info_list) {
        ogs_sbi_list_for_each(dnn_upf_info_list_node, snssai_upf_info_item->dnn_upf_info_list) {
            cJSON *itemLocal = ogs_sbi_dnn_upf_info_item_convertToJSON(dnn_upf_info_list_node->data);
            if (itemLocal == NULL) {
                goto fail;
            }
            cJSON_AddItemToArray(dnn_upf_info_list, itemLocal);
        }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_snssai_upf_info_item_t *ogs_sbi_snssai_upf_info_item_parseFromJSON(cJSON *snssai_upf_info_itemJSON)
{
    ogs_sbi_snssai_upf_info_item_t *snssai_upf_info_item_local_var = NULL;
    cJSON *s_nssai = cJSON_GetObjectItemCaseSensitive(snssai_upf_info_itemJSON, "sNssai");
    if (!s_nssai) {
        goto end;
    }

    ogs_sbi_snssai_t *s_nssai_local_nonprim = NULL;

    s_nssai_local_nonprim = ogs_sbi_snssai_parseFromJSON(s_nssai);

    cJSON *dnn_upf_info_list = cJSON_GetObjectItemCaseSensitive(snssai_upf_info_itemJSON, "dnnUpfInfoList");
    if (!dnn_upf_info_list) {
        goto end;
    }

    ogs_sbi_list_t *dnn_upf_info_listList;

    cJSON *dnn_upf_info_list_local_nonprimitive;
    if (!cJSON_IsArray(dnn_upf_info_list)) {
        goto end;
    }

    dnn_upf_info_listList = ogs_sbi_list_create();

    cJSON_ArrayForEach(dnn_upf_info_list_local_nonprimitive,dnn_upf_info_list ) {
        if (!cJSON_IsObject(dnn_upf_info_list_local_nonprimitive)) {
            goto end;
        }
        ogs_sbi_dnn_upf_info_item_t *dnn_upf_info_listItem = ogs_sbi_dnn_upf_info_item_parseFromJSON(dnn_upf_info_list_local_nonprimitive);

        ogs_sbi_list_add(dnn_upf_info_listList, dnn_upf_info_listItem);
    }

    snssai_upf_info_item_local_var = ogs_sbi_snssai_upf_info_item_create (
        s_nssai_local_nonprim,
        dnn_upf_info_listList
        );

    return snssai_upf_info_item_local_var;
end:
    return NULL;
}

