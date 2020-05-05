
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tai_range.h"

ogs_sbi_tai_range_t *ogs_sbi_tai_range_create(
    ogs_sbi_plmn_id_t *plmn_id,
    ogs_sbi_list_t *tac_range_list
    )
{
    ogs_sbi_tai_range_t *tai_range_local_var = ogs_malloc(sizeof(ogs_sbi_tai_range_t));
    if (!tai_range_local_var) {
        return NULL;
    }
    tai_range_local_var->plmn_id = plmn_id;
    tai_range_local_var->tac_range_list = tac_range_list;

    return tai_range_local_var;
}

void ogs_sbi_tai_range_free(ogs_sbi_tai_range_t *tai_range)
{
    if (NULL == tai_range) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_sbi_plmn_id_free(tai_range->plmn_id);
    ogs_sbi_list_for_each(node, tai_range->tac_range_list) {
        ogs_sbi_tac_range_free(node->data);
    }
    ogs_sbi_list_free(tai_range->tac_range_list);
    ogs_free(tai_range);
}

cJSON *ogs_sbi_tai_range_convertToJSON(ogs_sbi_tai_range_t *tai_range)
{
    cJSON *item = cJSON_CreateObject();
    if (!tai_range->plmn_id) {
        goto fail;
    }
    cJSON *plmn_id_local_JSON = ogs_sbi_plmn_id_convertToJSON(tai_range->plmn_id);
    if (plmn_id_local_JSON == NULL) {
        goto fail;
    }
    cJSON_AddItemToObject(item, "plmnId", plmn_id_local_JSON);
    if (item->child == NULL) {
        goto fail;
    }

    if (!tai_range->tac_range_list) {
        goto fail;
    }
    cJSON *tac_range_list = cJSON_AddArrayToObject(item, "tacRangeList");
    if (tac_range_list == NULL) {
        goto fail;
    }

    ogs_sbi_lnode_t *tac_range_list_node;
    if (tai_range->tac_range_list) {
        ogs_sbi_list_for_each(tac_range_list_node, tai_range->tac_range_list) {
            cJSON *itemLocal = ogs_sbi_tac_range_convertToJSON(tac_range_list_node->data);
            if (itemLocal == NULL) {
                goto fail;
            }
            cJSON_AddItemToArray(tac_range_list, itemLocal);
        }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_tai_range_t *ogs_sbi_tai_range_parseFromJSON(cJSON *tai_rangeJSON)
{
    ogs_sbi_tai_range_t *tai_range_local_var = NULL;
    cJSON *plmn_id = cJSON_GetObjectItemCaseSensitive(tai_rangeJSON, "plmnId");
    if (!plmn_id) {
        goto end;
    }

    ogs_sbi_plmn_id_t *plmn_id_local_nonprim = NULL;

    plmn_id_local_nonprim = ogs_sbi_plmn_id_parseFromJSON(plmn_id);

    cJSON *tac_range_list = cJSON_GetObjectItemCaseSensitive(tai_rangeJSON, "tacRangeList");
    if (!tac_range_list) {
        goto end;
    }

    ogs_sbi_list_t *tac_range_listList;

    cJSON *tac_range_list_local_nonprimitive;
    if (!cJSON_IsArray(tac_range_list)) {
        goto end;
    }

    tac_range_listList = ogs_sbi_list_create();

    cJSON_ArrayForEach(tac_range_list_local_nonprimitive,tac_range_list ) {
        if (!cJSON_IsObject(tac_range_list_local_nonprimitive)) {
            goto end;
        }
        ogs_sbi_tac_range_t *tac_range_listItem = ogs_sbi_tac_range_parseFromJSON(tac_range_list_local_nonprimitive);

        ogs_sbi_list_add(tac_range_listList, tac_range_listItem);
    }

    tai_range_local_var = ogs_sbi_tai_range_create (
        plmn_id_local_nonprim,
        tac_range_listList
        );

    return tai_range_local_var;
end:
    return NULL;
}

