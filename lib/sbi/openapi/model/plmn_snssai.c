
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "plmn_snssai.h"

ogs_sbi_plmn_snssai_t *ogs_sbi_plmn_snssai_create(
    ogs_sbi_plmn_id_t *plmn_id,
    ogs_sbi_list_t *s_nssai_list
    )
{
    ogs_sbi_plmn_snssai_t *plmn_snssai_local_var = ogs_malloc(sizeof(ogs_sbi_plmn_snssai_t));
    if (!plmn_snssai_local_var) {
        return NULL;
    }
    plmn_snssai_local_var->plmn_id = plmn_id;
    plmn_snssai_local_var->s_nssai_list = s_nssai_list;

    return plmn_snssai_local_var;
}

void ogs_sbi_plmn_snssai_free(ogs_sbi_plmn_snssai_t *plmn_snssai)
{
    if (NULL == plmn_snssai) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_sbi_plmn_id_free(plmn_snssai->plmn_id);
    ogs_sbi_list_for_each(node, plmn_snssai->s_nssai_list) {
        ogs_sbi_snssai_free(node->data);
    }
    ogs_sbi_list_free(plmn_snssai->s_nssai_list);
    ogs_free(plmn_snssai);
}

cJSON *ogs_sbi_plmn_snssai_convertToJSON(ogs_sbi_plmn_snssai_t *plmn_snssai)
{
    cJSON *item = cJSON_CreateObject();
    if (!plmn_snssai->plmn_id) {
        goto fail;
    }
    cJSON *plmn_id_local_JSON = ogs_sbi_plmn_id_convertToJSON(plmn_snssai->plmn_id);
    if (plmn_id_local_JSON == NULL) {
        goto fail;
    }
    cJSON_AddItemToObject(item, "plmnId", plmn_id_local_JSON);
    if (item->child == NULL) {
        goto fail;
    }

    if (!plmn_snssai->s_nssai_list) {
        goto fail;
    }
    cJSON *s_nssai_list = cJSON_AddArrayToObject(item, "sNssaiList");
    if (s_nssai_list == NULL) {
        goto fail;
    }

    ogs_sbi_lnode_t *s_nssai_list_node;
    if (plmn_snssai->s_nssai_list) {
        ogs_sbi_list_for_each(s_nssai_list_node, plmn_snssai->s_nssai_list) {
            cJSON *itemLocal = ogs_sbi_snssai_convertToJSON(s_nssai_list_node->data);
            if (itemLocal == NULL) {
                goto fail;
            }
            cJSON_AddItemToArray(s_nssai_list, itemLocal);
        }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_plmn_snssai_t *ogs_sbi_plmn_snssai_parseFromJSON(cJSON *plmn_snssaiJSON)
{
    ogs_sbi_plmn_snssai_t *plmn_snssai_local_var = NULL;
    cJSON *plmn_id = cJSON_GetObjectItemCaseSensitive(plmn_snssaiJSON, "plmnId");
    if (!plmn_id) {
        goto end;
    }

    ogs_sbi_plmn_id_t *plmn_id_local_nonprim = NULL;

    plmn_id_local_nonprim = ogs_sbi_plmn_id_parseFromJSON(plmn_id);

    cJSON *s_nssai_list = cJSON_GetObjectItemCaseSensitive(plmn_snssaiJSON, "sNssaiList");
    if (!s_nssai_list) {
        goto end;
    }

    ogs_sbi_list_t *s_nssai_listList;

    cJSON *s_nssai_list_local_nonprimitive;
    if (!cJSON_IsArray(s_nssai_list)) {
        goto end;
    }

    s_nssai_listList = ogs_sbi_list_create();

    cJSON_ArrayForEach(s_nssai_list_local_nonprimitive,s_nssai_list ) {
        if (!cJSON_IsObject(s_nssai_list_local_nonprimitive)) {
            goto end;
        }
        ogs_sbi_snssai_t *s_nssai_listItem = ogs_sbi_snssai_parseFromJSON(s_nssai_list_local_nonprimitive);

        ogs_sbi_list_add(s_nssai_listList, s_nssai_listItem);
    }

    plmn_snssai_local_var = ogs_sbi_plmn_snssai_create (
        plmn_id_local_nonprim,
        s_nssai_listList
        );

    return plmn_snssai_local_var;
end:
    return NULL;
}

