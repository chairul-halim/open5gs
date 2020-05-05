
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "invalid_param.h"

ogs_sbi_invalid_param_t *ogs_sbi_invalid_param_create(
    char *param,
    char *reason
    )
{
    ogs_sbi_invalid_param_t *invalid_param_local_var = ogs_malloc(sizeof(ogs_sbi_invalid_param_t));
    if (!invalid_param_local_var) {
        return NULL;
    }
    invalid_param_local_var->param = param;
    invalid_param_local_var->reason = reason;

    return invalid_param_local_var;
}

void ogs_sbi_invalid_param_free(ogs_sbi_invalid_param_t *invalid_param)
{
    if (NULL == invalid_param) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(invalid_param->param);
    ogs_free(invalid_param->reason);
    ogs_free(invalid_param);
}

cJSON *ogs_sbi_invalid_param_convertToJSON(ogs_sbi_invalid_param_t *invalid_param)
{
    cJSON *item = cJSON_CreateObject();
    if (!invalid_param->param) {
        goto fail;
    }
    if (cJSON_AddStringToObject(item, "param", invalid_param->param) == NULL) {
        goto fail;
    }

    if (invalid_param->reason) {
        if (cJSON_AddStringToObject(item, "reason", invalid_param->reason) == NULL) {
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

ogs_sbi_invalid_param_t *ogs_sbi_invalid_param_parseFromJSON(cJSON *invalid_paramJSON)
{
    ogs_sbi_invalid_param_t *invalid_param_local_var = NULL;
    cJSON *param = cJSON_GetObjectItemCaseSensitive(invalid_paramJSON, "param");
    if (!param) {
        goto end;
    }


    if (!cJSON_IsString(param))
    {
        goto end;
    }

    cJSON *reason = cJSON_GetObjectItemCaseSensitive(invalid_paramJSON, "reason");

    if (reason) {
        if (!cJSON_IsString(reason))
        {
            goto end;
        }
    }

    invalid_param_local_var = ogs_sbi_invalid_param_create (
        ogs_strdup(param->valuestring),
        reason ? ogs_strdup(reason->valuestring) : NULL
        );

    return invalid_param_local_var;
end:
    return NULL;
}

