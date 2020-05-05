
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "chf_info.h"

ogs_sbi_chf_info_t *ogs_sbi_chf_info_create(
    ogs_sbi_list_t *supi_range_list,
    ogs_sbi_list_t *gpsi_range_list,
    ogs_sbi_list_t *plmn_range_list
    )
{
    ogs_sbi_chf_info_t *chf_info_local_var = ogs_malloc(sizeof(ogs_sbi_chf_info_t));
    if (!chf_info_local_var) {
        return NULL;
    }
    chf_info_local_var->supi_range_list = supi_range_list;
    chf_info_local_var->gpsi_range_list = gpsi_range_list;
    chf_info_local_var->plmn_range_list = plmn_range_list;

    return chf_info_local_var;
}

void ogs_sbi_chf_info_free(ogs_sbi_chf_info_t *chf_info)
{
    if (NULL == chf_info) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_sbi_list_for_each(node, chf_info->supi_range_list) {
        ogs_sbi_supi_range_free(node->data);
    }
    ogs_sbi_list_free(chf_info->supi_range_list);
    ogs_sbi_list_for_each(node, chf_info->gpsi_range_list) {
        ogs_sbi_identity_range_free(node->data);
    }
    ogs_sbi_list_free(chf_info->gpsi_range_list);
    ogs_sbi_list_for_each(node, chf_info->plmn_range_list) {
        ogs_sbi_plmn_range_free(node->data);
    }
    ogs_sbi_list_free(chf_info->plmn_range_list);
    ogs_free(chf_info);
}

cJSON *ogs_sbi_chf_info_convertToJSON(ogs_sbi_chf_info_t *chf_info)
{
    cJSON *item = cJSON_CreateObject();
    if (chf_info->supi_range_list) {
        cJSON *supi_range_list = cJSON_AddArrayToObject(item, "supiRangeList");
        if (supi_range_list == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *supi_range_list_node;
        if (chf_info->supi_range_list) {
            ogs_sbi_list_for_each(supi_range_list_node, chf_info->supi_range_list) {
                cJSON *itemLocal = ogs_sbi_supi_range_convertToJSON(supi_range_list_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(supi_range_list, itemLocal);
            }
        }
    }

    if (chf_info->gpsi_range_list) {
        cJSON *gpsi_range_list = cJSON_AddArrayToObject(item, "gpsiRangeList");
        if (gpsi_range_list == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *gpsi_range_list_node;
        if (chf_info->gpsi_range_list) {
            ogs_sbi_list_for_each(gpsi_range_list_node, chf_info->gpsi_range_list) {
                cJSON *itemLocal = ogs_sbi_identity_range_convertToJSON(gpsi_range_list_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(gpsi_range_list, itemLocal);
            }
        }
    }

    if (chf_info->plmn_range_list) {
        cJSON *plmn_range_list = cJSON_AddArrayToObject(item, "plmnRangeList");
        if (plmn_range_list == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *plmn_range_list_node;
        if (chf_info->plmn_range_list) {
            ogs_sbi_list_for_each(plmn_range_list_node, chf_info->plmn_range_list) {
                cJSON *itemLocal = ogs_sbi_plmn_range_convertToJSON(plmn_range_list_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(plmn_range_list, itemLocal);
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

ogs_sbi_chf_info_t *ogs_sbi_chf_info_parseFromJSON(cJSON *chf_infoJSON)
{
    ogs_sbi_chf_info_t *chf_info_local_var = NULL;
    cJSON *supi_range_list = cJSON_GetObjectItemCaseSensitive(chf_infoJSON, "supiRangeList");

    ogs_sbi_list_t *supi_range_listList;
    if (supi_range_list) {
        cJSON *supi_range_list_local_nonprimitive;
        if (!cJSON_IsArray(supi_range_list)) {
            goto end;
        }

        supi_range_listList = ogs_sbi_list_create();

        cJSON_ArrayForEach(supi_range_list_local_nonprimitive,supi_range_list ) {
            if (!cJSON_IsObject(supi_range_list_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_supi_range_t *supi_range_listItem = ogs_sbi_supi_range_parseFromJSON(supi_range_list_local_nonprimitive);

            ogs_sbi_list_add(supi_range_listList, supi_range_listItem);
        }
    }

    cJSON *gpsi_range_list = cJSON_GetObjectItemCaseSensitive(chf_infoJSON, "gpsiRangeList");

    ogs_sbi_list_t *gpsi_range_listList;
    if (gpsi_range_list) {
        cJSON *gpsi_range_list_local_nonprimitive;
        if (!cJSON_IsArray(gpsi_range_list)) {
            goto end;
        }

        gpsi_range_listList = ogs_sbi_list_create();

        cJSON_ArrayForEach(gpsi_range_list_local_nonprimitive,gpsi_range_list ) {
            if (!cJSON_IsObject(gpsi_range_list_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_identity_range_t *gpsi_range_listItem = ogs_sbi_identity_range_parseFromJSON(gpsi_range_list_local_nonprimitive);

            ogs_sbi_list_add(gpsi_range_listList, gpsi_range_listItem);
        }
    }

    cJSON *plmn_range_list = cJSON_GetObjectItemCaseSensitive(chf_infoJSON, "plmnRangeList");

    ogs_sbi_list_t *plmn_range_listList;
    if (plmn_range_list) {
        cJSON *plmn_range_list_local_nonprimitive;
        if (!cJSON_IsArray(plmn_range_list)) {
            goto end;
        }

        plmn_range_listList = ogs_sbi_list_create();

        cJSON_ArrayForEach(plmn_range_list_local_nonprimitive,plmn_range_list ) {
            if (!cJSON_IsObject(plmn_range_list_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_plmn_range_t *plmn_range_listItem = ogs_sbi_plmn_range_parseFromJSON(plmn_range_list_local_nonprimitive);

            ogs_sbi_list_add(plmn_range_listList, plmn_range_listItem);
        }
    }

    chf_info_local_var = ogs_sbi_chf_info_create (
        supi_range_list ? supi_range_listList : NULL,
        gpsi_range_list ? gpsi_range_listList : NULL,
        plmn_range_list ? plmn_range_listList : NULL
        );

    return chf_info_local_var;
end:
    return NULL;
}

