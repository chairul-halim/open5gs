
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pcf_info.h"

ogs_sbi_pcf_info_t *ogs_sbi_pcf_info_create(
    char *group_id,
    ogs_sbi_list_t *dnn_list,
    ogs_sbi_list_t *supi_ranges,
    ogs_sbi_list_t *gpsi_ranges,
    char *rx_diam_host,
    char *rx_diam_realm
    )
{
    ogs_sbi_pcf_info_t *pcf_info_local_var = ogs_malloc(sizeof(ogs_sbi_pcf_info_t));
    if (!pcf_info_local_var) {
        return NULL;
    }
    pcf_info_local_var->group_id = group_id;
    pcf_info_local_var->dnn_list = dnn_list;
    pcf_info_local_var->supi_ranges = supi_ranges;
    pcf_info_local_var->gpsi_ranges = gpsi_ranges;
    pcf_info_local_var->rx_diam_host = rx_diam_host;
    pcf_info_local_var->rx_diam_realm = rx_diam_realm;

    return pcf_info_local_var;
}

void ogs_sbi_pcf_info_free(ogs_sbi_pcf_info_t *pcf_info)
{
    if (NULL == pcf_info) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(pcf_info->group_id);
    ogs_sbi_list_for_each(node, pcf_info->dnn_list) {
        ogs_free(node->data);
    }
    ogs_sbi_list_free(pcf_info->dnn_list);
    ogs_sbi_list_for_each(node, pcf_info->supi_ranges) {
        ogs_sbi_supi_range_free(node->data);
    }
    ogs_sbi_list_free(pcf_info->supi_ranges);
    ogs_sbi_list_for_each(node, pcf_info->gpsi_ranges) {
        ogs_sbi_identity_range_free(node->data);
    }
    ogs_sbi_list_free(pcf_info->gpsi_ranges);
    ogs_free(pcf_info->rx_diam_host);
    ogs_free(pcf_info->rx_diam_realm);
    ogs_free(pcf_info);
}

cJSON *ogs_sbi_pcf_info_convertToJSON(ogs_sbi_pcf_info_t *pcf_info)
{
    cJSON *item = cJSON_CreateObject();
    if (pcf_info->group_id) {
        if (cJSON_AddStringToObject(item, "groupId", pcf_info->group_id) == NULL) {
            goto fail;
        }
    }

    if (pcf_info->dnn_list) {
        cJSON *dnn_list = cJSON_AddArrayToObject(item, "dnnList");
        if (dnn_list == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *dnn_list_node;
        ogs_sbi_list_for_each(dnn_list_node, pcf_info->dnn_list) {
            if (cJSON_AddStringToObject(dnn_list, "", (char*)dnn_list_node->data) == NULL) {
                goto fail;
            }
        }
    }

    if (pcf_info->supi_ranges) {
        cJSON *supi_ranges = cJSON_AddArrayToObject(item, "supiRanges");
        if (supi_ranges == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *supi_ranges_node;
        if (pcf_info->supi_ranges) {
            ogs_sbi_list_for_each(supi_ranges_node, pcf_info->supi_ranges) {
                cJSON *itemLocal = ogs_sbi_supi_range_convertToJSON(supi_ranges_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(supi_ranges, itemLocal);
            }
        }
    }

    if (pcf_info->gpsi_ranges) {
        cJSON *gpsi_ranges = cJSON_AddArrayToObject(item, "gpsiRanges");
        if (gpsi_ranges == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *gpsi_ranges_node;
        if (pcf_info->gpsi_ranges) {
            ogs_sbi_list_for_each(gpsi_ranges_node, pcf_info->gpsi_ranges) {
                cJSON *itemLocal = ogs_sbi_identity_range_convertToJSON(gpsi_ranges_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(gpsi_ranges, itemLocal);
            }
        }
    }

    if (pcf_info->rx_diam_host) {
        if (cJSON_AddStringToObject(item, "rxDiamHost", pcf_info->rx_diam_host) == NULL) {
            goto fail;
        }
    }

    if (pcf_info->rx_diam_realm) {
        if (cJSON_AddStringToObject(item, "rxDiamRealm", pcf_info->rx_diam_realm) == NULL) {
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

ogs_sbi_pcf_info_t *ogs_sbi_pcf_info_parseFromJSON(cJSON *pcf_infoJSON)
{
    ogs_sbi_pcf_info_t *pcf_info_local_var = NULL;
    cJSON *group_id = cJSON_GetObjectItemCaseSensitive(pcf_infoJSON, "groupId");

    if (group_id) {
        if (!cJSON_IsString(group_id))
        {
            goto end;
        }
    }

    cJSON *dnn_list = cJSON_GetObjectItemCaseSensitive(pcf_infoJSON, "dnnList");

    ogs_sbi_list_t *dnn_listList;
    if (dnn_list) {
        cJSON *dnn_list_local;
        if (!cJSON_IsArray(dnn_list)) {
            goto end;
        }
        dnn_listList = ogs_sbi_list_create();

        cJSON_ArrayForEach(dnn_list_local, dnn_list) {
            if (!cJSON_IsString(dnn_list_local)) {
                goto end;
            }
            ogs_sbi_list_add(dnn_listList, ogs_strdup(dnn_list_local->valuestring));
        }
    }

    cJSON *supi_ranges = cJSON_GetObjectItemCaseSensitive(pcf_infoJSON, "supiRanges");

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

    cJSON *gpsi_ranges = cJSON_GetObjectItemCaseSensitive(pcf_infoJSON, "gpsiRanges");

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

    cJSON *rx_diam_host = cJSON_GetObjectItemCaseSensitive(pcf_infoJSON, "rxDiamHost");

    if (rx_diam_host) {
        if (!cJSON_IsString(rx_diam_host))
        {
            goto end;
        }
    }

    cJSON *rx_diam_realm = cJSON_GetObjectItemCaseSensitive(pcf_infoJSON, "rxDiamRealm");

    if (rx_diam_realm) {
        if (!cJSON_IsString(rx_diam_realm))
        {
            goto end;
        }
    }

    pcf_info_local_var = ogs_sbi_pcf_info_create (
        group_id ? ogs_strdup(group_id->valuestring) : NULL,
        dnn_list ? dnn_listList : NULL,
        supi_ranges ? supi_rangesList : NULL,
        gpsi_ranges ? gpsi_rangesList : NULL,
        rx_diam_host ? ogs_strdup(rx_diam_host->valuestring) : NULL,
        rx_diam_realm ? ogs_strdup(rx_diam_realm->valuestring) : NULL
        );

    return pcf_info_local_var;
end:
    return NULL;
}

