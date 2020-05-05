
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "chf_service_info.h"

ogs_sbi_chf_service_info_t *ogs_sbi_chf_service_info_create(
    char *primary_chf_service_instance,
    char *secondary_chf_service_instance
    )
{
    ogs_sbi_chf_service_info_t *chf_service_info_local_var = ogs_malloc(sizeof(ogs_sbi_chf_service_info_t));
    if (!chf_service_info_local_var) {
        return NULL;
    }
    chf_service_info_local_var->primary_chf_service_instance = primary_chf_service_instance;
    chf_service_info_local_var->secondary_chf_service_instance = secondary_chf_service_instance;

    return chf_service_info_local_var;
}

void ogs_sbi_chf_service_info_free(ogs_sbi_chf_service_info_t *chf_service_info)
{
    if (NULL == chf_service_info) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(chf_service_info->primary_chf_service_instance);
    ogs_free(chf_service_info->secondary_chf_service_instance);
    ogs_free(chf_service_info);
}

cJSON *ogs_sbi_chf_service_info_convertToJSON(ogs_sbi_chf_service_info_t *chf_service_info)
{
    cJSON *item = cJSON_CreateObject();
    if (chf_service_info->primary_chf_service_instance) {
        if (cJSON_AddStringToObject(item, "primaryChfServiceInstance", chf_service_info->primary_chf_service_instance) == NULL) {
            goto fail;
        }
    }

    if (chf_service_info->secondary_chf_service_instance) {
        if (cJSON_AddStringToObject(item, "secondaryChfServiceInstance", chf_service_info->secondary_chf_service_instance) == NULL) {
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

ogs_sbi_chf_service_info_t *ogs_sbi_chf_service_info_parseFromJSON(cJSON *chf_service_infoJSON)
{
    ogs_sbi_chf_service_info_t *chf_service_info_local_var = NULL;
    cJSON *primary_chf_service_instance = cJSON_GetObjectItemCaseSensitive(chf_service_infoJSON, "primaryChfServiceInstance");

    if (primary_chf_service_instance) {
        if (!cJSON_IsString(primary_chf_service_instance))
        {
            goto end;
        }
    }

    cJSON *secondary_chf_service_instance = cJSON_GetObjectItemCaseSensitive(chf_service_infoJSON, "secondaryChfServiceInstance");

    if (secondary_chf_service_instance) {
        if (!cJSON_IsString(secondary_chf_service_instance))
        {
            goto end;
        }
    }

    chf_service_info_local_var = ogs_sbi_chf_service_info_create (
        primary_chf_service_instance ? ogs_strdup(primary_chf_service_instance->valuestring) : NULL,
        secondary_chf_service_instance ? ogs_strdup(secondary_chf_service_instance->valuestring) : NULL
        );

    return chf_service_info_local_var;
end:
    return NULL;
}

