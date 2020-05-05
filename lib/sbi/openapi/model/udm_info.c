
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "udm_info.h"

ogs_sbi_udm_info_t *ogs_sbi_udm_info_create(
    char *group_id,
    ogs_sbi_list_t *supi_ranges,
    ogs_sbi_list_t *gpsi_ranges,
    ogs_sbi_list_t *external_group_identifiers_ranges,
    ogs_sbi_list_t *routing_indicators
    )
{
    ogs_sbi_udm_info_t *udm_info_local_var = ogs_malloc(sizeof(ogs_sbi_udm_info_t));
    if (!udm_info_local_var) {
        return NULL;
    }
    udm_info_local_var->group_id = group_id;
    udm_info_local_var->supi_ranges = supi_ranges;
    udm_info_local_var->gpsi_ranges = gpsi_ranges;
    udm_info_local_var->external_group_identifiers_ranges = external_group_identifiers_ranges;
    udm_info_local_var->routing_indicators = routing_indicators;

    return udm_info_local_var;
}

void ogs_sbi_udm_info_free(ogs_sbi_udm_info_t *udm_info)
{
    if (NULL == udm_info) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(udm_info->group_id);
    ogs_sbi_list_for_each(node, udm_info->supi_ranges) {
        ogs_sbi_supi_range_free(node->data);
    }
    ogs_sbi_list_free(udm_info->supi_ranges);
    ogs_sbi_list_for_each(node, udm_info->gpsi_ranges) {
        ogs_sbi_identity_range_free(node->data);
    }
    ogs_sbi_list_free(udm_info->gpsi_ranges);
    ogs_sbi_list_for_each(node, udm_info->external_group_identifiers_ranges) {
        ogs_sbi_identity_range_free(node->data);
    }
    ogs_sbi_list_free(udm_info->external_group_identifiers_ranges);
    ogs_sbi_list_for_each(node, udm_info->routing_indicators) {
        ogs_free(node->data);
    }
    ogs_sbi_list_free(udm_info->routing_indicators);
    ogs_free(udm_info);
}

cJSON *ogs_sbi_udm_info_convertToJSON(ogs_sbi_udm_info_t *udm_info)
{
    cJSON *item = cJSON_CreateObject();
    if (udm_info->group_id) {
        if (cJSON_AddStringToObject(item, "groupId", udm_info->group_id) == NULL) {
            goto fail;
        }
    }

    if (udm_info->supi_ranges) {
        cJSON *supi_ranges = cJSON_AddArrayToObject(item, "supiRanges");
        if (supi_ranges == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *supi_ranges_node;
        if (udm_info->supi_ranges) {
            ogs_sbi_list_for_each(supi_ranges_node, udm_info->supi_ranges) {
                cJSON *itemLocal = ogs_sbi_supi_range_convertToJSON(supi_ranges_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(supi_ranges, itemLocal);
            }
        }
    }

    if (udm_info->gpsi_ranges) {
        cJSON *gpsi_ranges = cJSON_AddArrayToObject(item, "gpsiRanges");
        if (gpsi_ranges == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *gpsi_ranges_node;
        if (udm_info->gpsi_ranges) {
            ogs_sbi_list_for_each(gpsi_ranges_node, udm_info->gpsi_ranges) {
                cJSON *itemLocal = ogs_sbi_identity_range_convertToJSON(gpsi_ranges_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(gpsi_ranges, itemLocal);
            }
        }
    }

    if (udm_info->external_group_identifiers_ranges) {
        cJSON *external_group_identifiers_ranges = cJSON_AddArrayToObject(item, "externalGroupIdentifiersRanges");
        if (external_group_identifiers_ranges == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *external_group_identifiers_ranges_node;
        if (udm_info->external_group_identifiers_ranges) {
            ogs_sbi_list_for_each(external_group_identifiers_ranges_node, udm_info->external_group_identifiers_ranges) {
                cJSON *itemLocal = ogs_sbi_identity_range_convertToJSON(external_group_identifiers_ranges_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(external_group_identifiers_ranges, itemLocal);
            }
        }
    }

    if (udm_info->routing_indicators) {
        cJSON *routing_indicators = cJSON_AddArrayToObject(item, "routingIndicators");
        if (routing_indicators == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *routing_indicators_node;
        ogs_sbi_list_for_each(routing_indicators_node, udm_info->routing_indicators) {
            if (cJSON_AddStringToObject(routing_indicators, "", (char*)routing_indicators_node->data) == NULL) {
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

ogs_sbi_udm_info_t *ogs_sbi_udm_info_parseFromJSON(cJSON *udm_infoJSON)
{
    ogs_sbi_udm_info_t *udm_info_local_var = NULL;
    cJSON *group_id = cJSON_GetObjectItemCaseSensitive(udm_infoJSON, "groupId");

    if (group_id) {
        if (!cJSON_IsString(group_id))
        {
            goto end;
        }
    }

    cJSON *supi_ranges = cJSON_GetObjectItemCaseSensitive(udm_infoJSON, "supiRanges");

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

    cJSON *gpsi_ranges = cJSON_GetObjectItemCaseSensitive(udm_infoJSON, "gpsiRanges");

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

    cJSON *external_group_identifiers_ranges = cJSON_GetObjectItemCaseSensitive(udm_infoJSON, "externalGroupIdentifiersRanges");

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

    cJSON *routing_indicators = cJSON_GetObjectItemCaseSensitive(udm_infoJSON, "routingIndicators");

    ogs_sbi_list_t *routing_indicatorsList;
    if (routing_indicators) {
        cJSON *routing_indicators_local;
        if (!cJSON_IsArray(routing_indicators)) {
            goto end;
        }
        routing_indicatorsList = ogs_sbi_list_create();

        cJSON_ArrayForEach(routing_indicators_local, routing_indicators) {
            if (!cJSON_IsString(routing_indicators_local)) {
                goto end;
            }
            ogs_sbi_list_add(routing_indicatorsList, ogs_strdup(routing_indicators_local->valuestring));
        }
    }

    udm_info_local_var = ogs_sbi_udm_info_create (
        group_id ? ogs_strdup(group_id->valuestring) : NULL,
        supi_ranges ? supi_rangesList : NULL,
        gpsi_ranges ? gpsi_rangesList : NULL,
        external_group_identifiers_ranges ? external_group_identifiers_rangesList : NULL,
        routing_indicators ? routing_indicatorsList : NULL
        );

    return udm_info_local_var;
end:
    return NULL;
}

