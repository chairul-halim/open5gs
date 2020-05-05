
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "amf_cond.h"

ogs_sbi_amf_cond_t *ogs_sbi_amf_cond_create(
    char *amf_set_id,
    char *amf_region_id
    )
{
    ogs_sbi_amf_cond_t *amf_cond_local_var = ogs_malloc(sizeof(ogs_sbi_amf_cond_t));
    if (!amf_cond_local_var) {
        return NULL;
    }
    amf_cond_local_var->amf_set_id = amf_set_id;
    amf_cond_local_var->amf_region_id = amf_region_id;

    return amf_cond_local_var;
}

void ogs_sbi_amf_cond_free(ogs_sbi_amf_cond_t *amf_cond)
{
    if (NULL == amf_cond) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(amf_cond->amf_set_id);
    ogs_free(amf_cond->amf_region_id);
    ogs_free(amf_cond);
}

cJSON *ogs_sbi_amf_cond_convertToJSON(ogs_sbi_amf_cond_t *amf_cond)
{
    cJSON *item = cJSON_CreateObject();
    if (amf_cond->amf_set_id) {
        if (cJSON_AddStringToObject(item, "amfSetId", amf_cond->amf_set_id) == NULL) {
            goto fail;
        }
    }

    if (amf_cond->amf_region_id) {
        if (cJSON_AddStringToObject(item, "amfRegionId", amf_cond->amf_region_id) == NULL) {
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

ogs_sbi_amf_cond_t *ogs_sbi_amf_cond_parseFromJSON(cJSON *amf_condJSON)
{
    ogs_sbi_amf_cond_t *amf_cond_local_var = NULL;
    cJSON *amf_set_id = cJSON_GetObjectItemCaseSensitive(amf_condJSON, "amfSetId");

    if (amf_set_id) {
        if (!cJSON_IsString(amf_set_id))
        {
            goto end;
        }
    }

    cJSON *amf_region_id = cJSON_GetObjectItemCaseSensitive(amf_condJSON, "amfRegionId");

    if (amf_region_id) {
        if (!cJSON_IsString(amf_region_id))
        {
            goto end;
        }
    }

    amf_cond_local_var = ogs_sbi_amf_cond_create (
        amf_set_id ? ogs_strdup(amf_set_id->valuestring) : NULL,
        amf_region_id ? ogs_strdup(amf_region_id->valuestring) : NULL
        );

    return amf_cond_local_var;
end:
    return NULL;
}

