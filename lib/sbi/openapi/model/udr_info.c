
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "udr_info.h"

ogs_sbi_udr_info_t *ogs_sbi_udr_info_create(
    char *group_id,
    ogs_sbi_list_t *supi_ranges,
    ogs_sbi_list_t *gpsi_ranges,
    ogs_sbi_list_t *external_group_identifiers_ranges,
    ogs_sbi_list_t *supported_data_sets
    )
{
    ogs_sbi_udr_info_t *udr_info_local_var = ogs_malloc(sizeof(ogs_sbi_udr_info_t));
    if (!udr_info_local_var) {
        return NULL;
    }
    udr_info_local_var->group_id = group_id;
    udr_info_local_var->supi_ranges = supi_ranges;
    udr_info_local_var->gpsi_ranges = gpsi_ranges;
    udr_info_local_var->external_group_identifiers_ranges = external_group_identifiers_ranges;
    udr_info_local_var->supported_data_sets = supported_data_sets;

    return udr_info_local_var;
}

void ogs_sbi_udr_info_free(ogs_sbi_udr_info_t *udr_info)
{
    if (NULL == udr_info) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(udr_info->group_id);
    ogs_sbi_list_for_each(node, udr_info->supi_ranges) {
        ogs_sbi_supi_range_free(node->data);
    }
    ogs_sbi_list_free(udr_info->supi_ranges);
    ogs_sbi_list_for_each(node, udr_info->gpsi_ranges) {
        ogs_sbi_identity_range_free(node->data);
    }
    ogs_sbi_list_free(udr_info->gpsi_ranges);
    ogs_sbi_list_for_each(node, udr_info->external_group_identifiers_ranges) {
        ogs_sbi_identity_range_free(node->data);
    }
    ogs_sbi_list_free(udr_info->external_group_identifiers_ranges);
    ogs_sbi_list_for_each(node, udr_info->supported_data_sets) {
        ogs_sbi_data_set_id_free(node->data);
    }
    ogs_sbi_list_free(udr_info->supported_data_sets);
    ogs_free(udr_info);
}

cJSON *ogs_sbi_udr_info_convertToJSON(ogs_sbi_udr_info_t *udr_info)
{
    cJSON *item = cJSON_CreateObject();
    if (udr_info->group_id) {
        if (cJSON_AddStringToObject(item, "groupId", udr_info->group_id) == NULL) {
            goto fail;
        }
    }

    if (udr_info->supi_ranges) {
        cJSON *supi_ranges = cJSON_AddArrayToObject(item, "supiRanges");
        if (supi_ranges == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *supi_ranges_node;
        if (udr_info->supi_ranges) {
            ogs_sbi_list_for_each(supi_ranges_node, udr_info->supi_ranges) {
                cJSON *itemLocal = ogs_sbi_supi_range_convertToJSON(supi_ranges_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(supi_ranges, itemLocal);
            }
        }
    }

    if (udr_info->gpsi_ranges) {
        cJSON *gpsi_ranges = cJSON_AddArrayToObject(item, "gpsiRanges");
        if (gpsi_ranges == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *gpsi_ranges_node;
        if (udr_info->gpsi_ranges) {
            ogs_sbi_list_for_each(gpsi_ranges_node, udr_info->gpsi_ranges) {
                cJSON *itemLocal = ogs_sbi_identity_range_convertToJSON(gpsi_ranges_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(gpsi_ranges, itemLocal);
            }
        }
    }

    if (udr_info->external_group_identifiers_ranges) {
        cJSON *external_group_identifiers_ranges = cJSON_AddArrayToObject(item, "externalGroupIdentifiersRanges");
        if (external_group_identifiers_ranges == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *external_group_identifiers_ranges_node;
        if (udr_info->external_group_identifiers_ranges) {
            ogs_sbi_list_for_each(external_group_identifiers_ranges_node, udr_info->external_group_identifiers_ranges) {
                cJSON *itemLocal = ogs_sbi_identity_range_convertToJSON(external_group_identifiers_ranges_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(external_group_identifiers_ranges, itemLocal);
            }
        }
    }

    if (udr_info->supported_data_sets) {
        cJSON *supported_data_sets = cJSON_AddArrayToObject(item, "supportedDataSets");
        if (supported_data_sets == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *supported_data_sets_node;
        if (udr_info->supported_data_sets) {
            ogs_sbi_list_for_each(supported_data_sets_node, udr_info->supported_data_sets) {
                cJSON *itemLocal = ogs_sbi_data_set_id_convertToJSON(supported_data_sets_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(supported_data_sets, itemLocal);
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

ogs_sbi_udr_info_t *ogs_sbi_udr_info_parseFromJSON(cJSON *udr_infoJSON)
{
    ogs_sbi_udr_info_t *udr_info_local_var = NULL;
    cJSON *group_id = cJSON_GetObjectItemCaseSensitive(udr_infoJSON, "groupId");

    if (group_id) {
        if (!cJSON_IsString(group_id))
        {
            goto end;
        }
    }

    cJSON *supi_ranges = cJSON_GetObjectItemCaseSensitive(udr_infoJSON, "supiRanges");

    ogs_sbi_list_t *supi_rangesList;
    if (supi_ranges) {
        cJSON *supi_ranges_local_nonprimitive;
        if (!cJSON_IsArray(supi_ranges)) {
            goto end;
        }

        supi_rangesList = ogs_sbi_list_create();

        cJSON_ArrayForEach(supi_ranges_local_nonprimitive,supi_ranges ) {
            if (!cJSON_IsObject(supi_ranges_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_supi_range_t *supi_rangesItem = ogs_sbi_supi_range_parseFromJSON(supi_ranges_local_nonprimitive);

            ogs_sbi_list_add(supi_rangesList, supi_rangesItem);
        }
    }

    cJSON *gpsi_ranges = cJSON_GetObjectItemCaseSensitive(udr_infoJSON, "gpsiRanges");

    ogs_sbi_list_t *gpsi_rangesList;
    if (gpsi_ranges) {
        cJSON *gpsi_ranges_local_nonprimitive;
        if (!cJSON_IsArray(gpsi_ranges)) {
            goto end;
        }

        gpsi_rangesList = ogs_sbi_list_create();

        cJSON_ArrayForEach(gpsi_ranges_local_nonprimitive,gpsi_ranges ) {
            if (!cJSON_IsObject(gpsi_ranges_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_identity_range_t *gpsi_rangesItem = ogs_sbi_identity_range_parseFromJSON(gpsi_ranges_local_nonprimitive);

            ogs_sbi_list_add(gpsi_rangesList, gpsi_rangesItem);
        }
    }

    cJSON *external_group_identifiers_ranges = cJSON_GetObjectItemCaseSensitive(udr_infoJSON, "externalGroupIdentifiersRanges");

    ogs_sbi_list_t *external_group_identifiers_rangesList;
    if (external_group_identifiers_ranges) {
        cJSON *external_group_identifiers_ranges_local_nonprimitive;
        if (!cJSON_IsArray(external_group_identifiers_ranges)) {
            goto end;
        }

        external_group_identifiers_rangesList = ogs_sbi_list_create();

        cJSON_ArrayForEach(external_group_identifiers_ranges_local_nonprimitive,external_group_identifiers_ranges ) {
            if (!cJSON_IsObject(external_group_identifiers_ranges_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_identity_range_t *external_group_identifiers_rangesItem = ogs_sbi_identity_range_parseFromJSON(external_group_identifiers_ranges_local_nonprimitive);

            ogs_sbi_list_add(external_group_identifiers_rangesList, external_group_identifiers_rangesItem);
        }
    }

    cJSON *supported_data_sets = cJSON_GetObjectItemCaseSensitive(udr_infoJSON, "supportedDataSets");

    ogs_sbi_list_t *supported_data_setsList;
    if (supported_data_sets) {
        cJSON *supported_data_sets_local_nonprimitive;
        if (!cJSON_IsArray(supported_data_sets)) {
            goto end;
        }

        supported_data_setsList = ogs_sbi_list_create();

        cJSON_ArrayForEach(supported_data_sets_local_nonprimitive,supported_data_sets ) {
            if (!cJSON_IsObject(supported_data_sets_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_data_set_id_t *supported_data_setsItem = ogs_sbi_data_set_id_parseFromJSON(supported_data_sets_local_nonprimitive);

            ogs_sbi_list_add(supported_data_setsList, supported_data_setsItem);
        }
    }

    udr_info_local_var = ogs_sbi_udr_info_create (
        group_id ? ogs_strdup(group_id->valuestring) : NULL,
        supi_ranges ? supi_rangesList : NULL,
        gpsi_ranges ? gpsi_rangesList : NULL,
        external_group_identifiers_ranges ? external_group_identifiers_rangesList : NULL,
        supported_data_sets ? supported_data_setsList : NULL
        );

    return udr_info_local_var;
end:
    return NULL;
}

