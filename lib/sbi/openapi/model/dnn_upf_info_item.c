
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dnn_upf_info_item.h"

ogs_sbi_dnn_upf_info_item_t *ogs_sbi_dnn_upf_info_item_create(
    char *dnn,
    ogs_sbi_list_t *dnai_list,
    ogs_sbi_list_t *pdu_session_types
    )
{
    ogs_sbi_dnn_upf_info_item_t *dnn_upf_info_item_local_var = ogs_malloc(sizeof(ogs_sbi_dnn_upf_info_item_t));
    if (!dnn_upf_info_item_local_var) {
        return NULL;
    }
    dnn_upf_info_item_local_var->dnn = dnn;
    dnn_upf_info_item_local_var->dnai_list = dnai_list;
    dnn_upf_info_item_local_var->pdu_session_types = pdu_session_types;

    return dnn_upf_info_item_local_var;
}

void ogs_sbi_dnn_upf_info_item_free(ogs_sbi_dnn_upf_info_item_t *dnn_upf_info_item)
{
    if (NULL == dnn_upf_info_item) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(dnn_upf_info_item->dnn);
    ogs_sbi_list_for_each(node, dnn_upf_info_item->dnai_list) {
        ogs_free(node->data);
    }
    ogs_sbi_list_free(dnn_upf_info_item->dnai_list);
    ogs_sbi_list_for_each(node, dnn_upf_info_item->pdu_session_types) {
        ogs_sbi_pdu_session_type_free(node->data);
    }
    ogs_sbi_list_free(dnn_upf_info_item->pdu_session_types);
    ogs_free(dnn_upf_info_item);
}

cJSON *ogs_sbi_dnn_upf_info_item_convertToJSON(ogs_sbi_dnn_upf_info_item_t *dnn_upf_info_item)
{
    cJSON *item = cJSON_CreateObject();
    if (!dnn_upf_info_item->dnn) {
        goto fail;
    }
    if (cJSON_AddStringToObject(item, "dnn", dnn_upf_info_item->dnn) == NULL) {
        goto fail;
    }

    if (dnn_upf_info_item->dnai_list) {
        cJSON *dnai_list = cJSON_AddArrayToObject(item, "dnaiList");
        if (dnai_list == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *dnai_list_node;
        ogs_sbi_list_for_each(dnai_list_node, dnn_upf_info_item->dnai_list) {
            if (cJSON_AddStringToObject(dnai_list, "", (char*)dnai_list_node->data) == NULL) {
                goto fail;
            }
        }
    }

    if (dnn_upf_info_item->pdu_session_types) {
        cJSON *pdu_session_types = cJSON_AddArrayToObject(item, "pduSessionTypes");
        if (pdu_session_types == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *pdu_session_types_node;
        if (dnn_upf_info_item->pdu_session_types) {
            ogs_sbi_list_for_each(pdu_session_types_node, dnn_upf_info_item->pdu_session_types) {
                cJSON *itemLocal = ogs_sbi_pdu_session_type_convertToJSON(pdu_session_types_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(pdu_session_types, itemLocal);
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

ogs_sbi_dnn_upf_info_item_t *ogs_sbi_dnn_upf_info_item_parseFromJSON(cJSON *dnn_upf_info_itemJSON)
{
    ogs_sbi_dnn_upf_info_item_t *dnn_upf_info_item_local_var = NULL;
    cJSON *dnn = cJSON_GetObjectItemCaseSensitive(dnn_upf_info_itemJSON, "dnn");
    if (!dnn) {
        goto end;
    }


    if (!cJSON_IsString(dnn))
    {
        goto end;
    }

    cJSON *dnai_list = cJSON_GetObjectItemCaseSensitive(dnn_upf_info_itemJSON, "dnaiList");

    ogs_sbi_list_t *dnai_listList;
    if (dnai_list) {
        cJSON *dnai_list_local;
        if (!cJSON_IsArray(dnai_list)) {
            goto end;
        }
        dnai_listList = ogs_sbi_list_create();

        cJSON_ArrayForEach(dnai_list_local, dnai_list) {
            if (!cJSON_IsString(dnai_list_local)) {
                goto end;
            }
            ogs_sbi_list_add(dnai_listList, ogs_strdup(dnai_list_local->valuestring));
        }
    }

    cJSON *pdu_session_types = cJSON_GetObjectItemCaseSensitive(dnn_upf_info_itemJSON, "pduSessionTypes");

    ogs_sbi_list_t *pdu_session_typesList;
    if (pdu_session_types) {
        cJSON *pdu_session_types_local_nonprimitive;
        if (!cJSON_IsArray(pdu_session_types)) {
            goto end;
        }

        pdu_session_typesList = ogs_sbi_list_create();

        cJSON_ArrayForEach(pdu_session_types_local_nonprimitive,pdu_session_types ) {
            if (!cJSON_IsObject(pdu_session_types_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_pdu_session_type_t *pdu_session_typesItem = ogs_sbi_pdu_session_type_parseFromJSON(pdu_session_types_local_nonprimitive);

            ogs_sbi_list_add(pdu_session_typesList, pdu_session_typesItem);
        }
    }

    dnn_upf_info_item_local_var = ogs_sbi_dnn_upf_info_item_create (
        ogs_strdup(dnn->valuestring),
        dnai_list ? dnai_listList : NULL,
        pdu_session_types ? pdu_session_typesList : NULL
        );

    return dnn_upf_info_item_local_var;
end:
    return NULL;
}

