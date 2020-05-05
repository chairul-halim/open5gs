
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "amf_info.h"

ogs_sbi_amf_info_t *ogs_sbi_amf_info_create(
    char *amf_set_id,
    char *amf_region_id,
    ogs_sbi_list_t *guami_list,
    ogs_sbi_list_t *tai_list,
    ogs_sbi_list_t *tai_range_list,
    ogs_sbi_list_t *backup_info_amf_failure,
    ogs_sbi_list_t *backup_info_amf_removal,
    ogs_sbi_n2_interface_amf_info_t *n2_interface_amf_info
    )
{
    ogs_sbi_amf_info_t *amf_info_local_var = ogs_malloc(sizeof(ogs_sbi_amf_info_t));
    if (!amf_info_local_var) {
        return NULL;
    }
    amf_info_local_var->amf_set_id = amf_set_id;
    amf_info_local_var->amf_region_id = amf_region_id;
    amf_info_local_var->guami_list = guami_list;
    amf_info_local_var->tai_list = tai_list;
    amf_info_local_var->tai_range_list = tai_range_list;
    amf_info_local_var->backup_info_amf_failure = backup_info_amf_failure;
    amf_info_local_var->backup_info_amf_removal = backup_info_amf_removal;
    amf_info_local_var->n2_interface_amf_info = n2_interface_amf_info;

    return amf_info_local_var;
}

void ogs_sbi_amf_info_free(ogs_sbi_amf_info_t *amf_info)
{
    if (NULL == amf_info) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(amf_info->amf_set_id);
    ogs_free(amf_info->amf_region_id);
    ogs_sbi_list_for_each(node, amf_info->guami_list) {
        ogs_sbi_guami_free(node->data);
    }
    ogs_sbi_list_free(amf_info->guami_list);
    ogs_sbi_list_for_each(node, amf_info->tai_list) {
        ogs_sbi_tai_free(node->data);
    }
    ogs_sbi_list_free(amf_info->tai_list);
    ogs_sbi_list_for_each(node, amf_info->tai_range_list) {
        ogs_sbi_tai_range_free(node->data);
    }
    ogs_sbi_list_free(amf_info->tai_range_list);
    ogs_sbi_list_for_each(node, amf_info->backup_info_amf_failure) {
        ogs_sbi_guami_free(node->data);
    }
    ogs_sbi_list_free(amf_info->backup_info_amf_failure);
    ogs_sbi_list_for_each(node, amf_info->backup_info_amf_removal) {
        ogs_sbi_guami_free(node->data);
    }
    ogs_sbi_list_free(amf_info->backup_info_amf_removal);
    ogs_sbi_n2_interface_amf_info_free(amf_info->n2_interface_amf_info);
    ogs_free(amf_info);
}

cJSON *ogs_sbi_amf_info_convertToJSON(ogs_sbi_amf_info_t *amf_info)
{
    cJSON *item = cJSON_CreateObject();
    if (!amf_info->amf_set_id) {
        goto fail;
    }
    if (cJSON_AddStringToObject(item, "amfSetId", amf_info->amf_set_id) == NULL) {
        goto fail;
    }

    if (!amf_info->amf_region_id) {
        goto fail;
    }
    if (cJSON_AddStringToObject(item, "amfRegionId", amf_info->amf_region_id) == NULL) {
        goto fail;
    }

    if (!amf_info->guami_list) {
        goto fail;
    }
    cJSON *guami_list = cJSON_AddArrayToObject(item, "guamiList");
    if (guami_list == NULL) {
        goto fail;
    }

    ogs_sbi_lnode_t *guami_list_node;
    if (amf_info->guami_list) {
        ogs_sbi_list_for_each(guami_list_node, amf_info->guami_list) {
            cJSON *itemLocal = ogs_sbi_guami_convertToJSON(guami_list_node->data);
            if (itemLocal == NULL) {
                goto fail;
            }
            cJSON_AddItemToArray(guami_list, itemLocal);
        }
    }

    if (amf_info->tai_list) {
        cJSON *tai_list = cJSON_AddArrayToObject(item, "taiList");
        if (tai_list == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *tai_list_node;
        if (amf_info->tai_list) {
            ogs_sbi_list_for_each(tai_list_node, amf_info->tai_list) {
                cJSON *itemLocal = ogs_sbi_tai_convertToJSON(tai_list_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(tai_list, itemLocal);
            }
        }
    }

    if (amf_info->tai_range_list) {
        cJSON *tai_range_list = cJSON_AddArrayToObject(item, "taiRangeList");
        if (tai_range_list == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *tai_range_list_node;
        if (amf_info->tai_range_list) {
            ogs_sbi_list_for_each(tai_range_list_node, amf_info->tai_range_list) {
                cJSON *itemLocal = ogs_sbi_tai_range_convertToJSON(tai_range_list_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(tai_range_list, itemLocal);
            }
        }
    }

    if (amf_info->backup_info_amf_failure) {
        cJSON *backup_info_amf_failure = cJSON_AddArrayToObject(item, "backupInfoAmfFailure");
        if (backup_info_amf_failure == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *backup_info_amf_failure_node;
        if (amf_info->backup_info_amf_failure) {
            ogs_sbi_list_for_each(backup_info_amf_failure_node, amf_info->backup_info_amf_failure) {
                cJSON *itemLocal = ogs_sbi_guami_convertToJSON(backup_info_amf_failure_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(backup_info_amf_failure, itemLocal);
            }
        }
    }

    if (amf_info->backup_info_amf_removal) {
        cJSON *backup_info_amf_removal = cJSON_AddArrayToObject(item, "backupInfoAmfRemoval");
        if (backup_info_amf_removal == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *backup_info_amf_removal_node;
        if (amf_info->backup_info_amf_removal) {
            ogs_sbi_list_for_each(backup_info_amf_removal_node, amf_info->backup_info_amf_removal) {
                cJSON *itemLocal = ogs_sbi_guami_convertToJSON(backup_info_amf_removal_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(backup_info_amf_removal, itemLocal);
            }
        }
    }

    if (amf_info->n2_interface_amf_info) {
        cJSON *n2_interface_amf_info_local_JSON = ogs_sbi_n2_interface_amf_info_convertToJSON(amf_info->n2_interface_amf_info);
        if (n2_interface_amf_info_local_JSON == NULL) {
            goto fail;
        }
        cJSON_AddItemToObject(item, "n2InterfaceAmfInfo", n2_interface_amf_info_local_JSON);
        if (item->child == NULL) {
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

ogs_sbi_amf_info_t *ogs_sbi_amf_info_parseFromJSON(cJSON *amf_infoJSON)
{
    ogs_sbi_amf_info_t *amf_info_local_var = NULL;
    cJSON *amf_set_id = cJSON_GetObjectItemCaseSensitive(amf_infoJSON, "amfSetId");
    if (!amf_set_id) {
        goto end;
    }


    if (!cJSON_IsString(amf_set_id))
    {
        goto end;
    }

    cJSON *amf_region_id = cJSON_GetObjectItemCaseSensitive(amf_infoJSON, "amfRegionId");
    if (!amf_region_id) {
        goto end;
    }


    if (!cJSON_IsString(amf_region_id))
    {
        goto end;
    }

    cJSON *guami_list = cJSON_GetObjectItemCaseSensitive(amf_infoJSON, "guamiList");
    if (!guami_list) {
        goto end;
    }

    ogs_sbi_list_t *guami_listList;

    cJSON *guami_list_local_nonprimitive;
    if (!cJSON_IsArray(guami_list)) {
        goto end;
    }

    guami_listList = ogs_sbi_list_create();

    cJSON_ArrayForEach(guami_list_local_nonprimitive,guami_list ) {
        if (!cJSON_IsObject(guami_list_local_nonprimitive)) {
            goto end;
        }
        ogs_sbi_guami_t *guami_listItem = ogs_sbi_guami_parseFromJSON(guami_list_local_nonprimitive);

        ogs_sbi_list_add(guami_listList, guami_listItem);
    }

    cJSON *tai_list = cJSON_GetObjectItemCaseSensitive(amf_infoJSON, "taiList");

    ogs_sbi_list_t *tai_listList;
    if (tai_list) {
        cJSON *tai_list_local_nonprimitive;
        if (!cJSON_IsArray(tai_list)) {
            goto end;
        }

        tai_listList = ogs_sbi_list_create();

        cJSON_ArrayForEach(tai_list_local_nonprimitive,tai_list ) {
            if (!cJSON_IsObject(tai_list_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_tai_t *tai_listItem = ogs_sbi_tai_parseFromJSON(tai_list_local_nonprimitive);

            ogs_sbi_list_add(tai_listList, tai_listItem);
        }
    }

    cJSON *tai_range_list = cJSON_GetObjectItemCaseSensitive(amf_infoJSON, "taiRangeList");

    ogs_sbi_list_t *tai_range_listList;
    if (tai_range_list) {
        cJSON *tai_range_list_local_nonprimitive;
        if (!cJSON_IsArray(tai_range_list)) {
            goto end;
        }

        tai_range_listList = ogs_sbi_list_create();

        cJSON_ArrayForEach(tai_range_list_local_nonprimitive,tai_range_list ) {
            if (!cJSON_IsObject(tai_range_list_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_tai_range_t *tai_range_listItem = ogs_sbi_tai_range_parseFromJSON(tai_range_list_local_nonprimitive);

            ogs_sbi_list_add(tai_range_listList, tai_range_listItem);
        }
    }

    cJSON *backup_info_amf_failure = cJSON_GetObjectItemCaseSensitive(amf_infoJSON, "backupInfoAmfFailure");

    ogs_sbi_list_t *backup_info_amf_failureList;
    if (backup_info_amf_failure) {
        cJSON *backup_info_amf_failure_local_nonprimitive;
        if (!cJSON_IsArray(backup_info_amf_failure)) {
            goto end;
        }

        backup_info_amf_failureList = ogs_sbi_list_create();

        cJSON_ArrayForEach(backup_info_amf_failure_local_nonprimitive,backup_info_amf_failure ) {
            if (!cJSON_IsObject(backup_info_amf_failure_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_guami_t *backup_info_amf_failureItem = ogs_sbi_guami_parseFromJSON(backup_info_amf_failure_local_nonprimitive);

            ogs_sbi_list_add(backup_info_amf_failureList, backup_info_amf_failureItem);
        }
    }

    cJSON *backup_info_amf_removal = cJSON_GetObjectItemCaseSensitive(amf_infoJSON, "backupInfoAmfRemoval");

    ogs_sbi_list_t *backup_info_amf_removalList;
    if (backup_info_amf_removal) {
        cJSON *backup_info_amf_removal_local_nonprimitive;
        if (!cJSON_IsArray(backup_info_amf_removal)) {
            goto end;
        }

        backup_info_amf_removalList = ogs_sbi_list_create();

        cJSON_ArrayForEach(backup_info_amf_removal_local_nonprimitive,backup_info_amf_removal ) {
            if (!cJSON_IsObject(backup_info_amf_removal_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_guami_t *backup_info_amf_removalItem = ogs_sbi_guami_parseFromJSON(backup_info_amf_removal_local_nonprimitive);

            ogs_sbi_list_add(backup_info_amf_removalList, backup_info_amf_removalItem);
        }
    }

    cJSON *n2_interface_amf_info = cJSON_GetObjectItemCaseSensitive(amf_infoJSON, "n2InterfaceAmfInfo");

    ogs_sbi_n2_interface_amf_info_t *n2_interface_amf_info_local_nonprim = NULL;
    if (n2_interface_amf_info) {
        n2_interface_amf_info_local_nonprim = ogs_sbi_n2_interface_amf_info_parseFromJSON(n2_interface_amf_info);
    }

    amf_info_local_var = ogs_sbi_amf_info_create (
        ogs_strdup(amf_set_id->valuestring),
        ogs_strdup(amf_region_id->valuestring),
        guami_listList,
        tai_list ? tai_listList : NULL,
        tai_range_list ? tai_range_listList : NULL,
        backup_info_amf_failure ? backup_info_amf_failureList : NULL,
        backup_info_amf_removal ? backup_info_amf_removalList : NULL,
        n2_interface_amf_info ? n2_interface_amf_info_local_nonprim : NULL
        );

    return amf_info_local_var;
end:
    return NULL;
}

