
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "problem_details.h"

ogs_sbi_problem_details_t *ogs_sbi_problem_details_create(
    char *type,
    char *title,
    int status,
    char *detail,
    char *instance,
    char *cause,
    ogs_sbi_list_t *invalid_params,
    char *supported_features
    )
{
    ogs_sbi_problem_details_t *problem_details_local_var = ogs_malloc(sizeof(ogs_sbi_problem_details_t));
    if (!problem_details_local_var) {
        return NULL;
    }
    problem_details_local_var->type = type;
    problem_details_local_var->title = title;
    problem_details_local_var->status = status;
    problem_details_local_var->detail = detail;
    problem_details_local_var->instance = instance;
    problem_details_local_var->cause = cause;
    problem_details_local_var->invalid_params = invalid_params;
    problem_details_local_var->supported_features = supported_features;

    return problem_details_local_var;
}

void ogs_sbi_problem_details_free(ogs_sbi_problem_details_t *problem_details)
{
    if (NULL == problem_details) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(problem_details->type);
    ogs_free(problem_details->title);
    ogs_free(problem_details->detail);
    ogs_free(problem_details->instance);
    ogs_free(problem_details->cause);
    ogs_sbi_list_for_each(node, problem_details->invalid_params) {
        ogs_sbi_invalid_param_free(node->data);
    }
    ogs_sbi_list_free(problem_details->invalid_params);
    ogs_free(problem_details->supported_features);
    ogs_free(problem_details);
}

cJSON *ogs_sbi_problem_details_convertToJSON(ogs_sbi_problem_details_t *problem_details)
{
    cJSON *item = cJSON_CreateObject();
    if (problem_details->type) {
        if (cJSON_AddStringToObject(item, "type", problem_details->type) == NULL) {
            goto fail;
        }
    }

    if (problem_details->title) {
        if (cJSON_AddStringToObject(item, "title", problem_details->title) == NULL) {
            goto fail;
        }
    }

    if (problem_details->status) {
        if (cJSON_AddNumberToObject(item, "status", problem_details->status) == NULL) {
            goto fail;
        }
    }

    if (problem_details->detail) {
        if (cJSON_AddStringToObject(item, "detail", problem_details->detail) == NULL) {
            goto fail;
        }
    }

    if (problem_details->instance) {
        if (cJSON_AddStringToObject(item, "instance", problem_details->instance) == NULL) {
            goto fail;
        }
    }

    if (problem_details->cause) {
        if (cJSON_AddStringToObject(item, "cause", problem_details->cause) == NULL) {
            goto fail;
        }
    }

    if (problem_details->invalid_params) {
        cJSON *invalid_params = cJSON_AddArrayToObject(item, "invalidParams");
        if (invalid_params == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *invalid_params_node;
        if (problem_details->invalid_params) {
            ogs_sbi_list_for_each(invalid_params_node, problem_details->invalid_params) {
                cJSON *itemLocal = ogs_sbi_invalid_param_convertToJSON(invalid_params_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(invalid_params, itemLocal);
            }
        }
    }

    if (problem_details->supported_features) {
        if (cJSON_AddStringToObject(item, "supportedFeatures", problem_details->supported_features) == NULL) {
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

ogs_sbi_problem_details_t *ogs_sbi_problem_details_parseFromJSON(cJSON *problem_detailsJSON)
{
    ogs_sbi_problem_details_t *problem_details_local_var = NULL;
    cJSON *type = cJSON_GetObjectItemCaseSensitive(problem_detailsJSON, "type");

    if (type) {
        if (!cJSON_IsString(type))
        {
            goto end;
        }
    }

    cJSON *title = cJSON_GetObjectItemCaseSensitive(problem_detailsJSON, "title");

    if (title) {
        if (!cJSON_IsString(title))
        {
            goto end;
        }
    }

    cJSON *status = cJSON_GetObjectItemCaseSensitive(problem_detailsJSON, "status");

    if (status) {
        if (!cJSON_IsNumber(status)) {
            goto end;
        }
    }

    cJSON *detail = cJSON_GetObjectItemCaseSensitive(problem_detailsJSON, "detail");

    if (detail) {
        if (!cJSON_IsString(detail))
        {
            goto end;
        }
    }

    cJSON *instance = cJSON_GetObjectItemCaseSensitive(problem_detailsJSON, "instance");

    if (instance) {
        if (!cJSON_IsString(instance))
        {
            goto end;
        }
    }

    cJSON *cause = cJSON_GetObjectItemCaseSensitive(problem_detailsJSON, "cause");

    if (cause) {
        if (!cJSON_IsString(cause))
        {
            goto end;
        }
    }

    cJSON *invalid_params = cJSON_GetObjectItemCaseSensitive(problem_detailsJSON, "invalidParams");

    ogs_sbi_list_t *invalid_paramsList;
    if (invalid_params) {
        cJSON *invalid_params_local_nonprimitive;
        if (!cJSON_IsArray(invalid_params)) {
            goto end;
        }

        invalid_paramsList = ogs_sbi_list_create();

        cJSON_ArrayForEach(invalid_params_local_nonprimitive,invalid_params ) {
            if (!cJSON_IsObject(invalid_params_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_invalid_param_t *invalid_paramsItem = ogs_sbi_invalid_param_parseFromJSON(invalid_params_local_nonprimitive);

            ogs_sbi_list_add(invalid_paramsList, invalid_paramsItem);
        }
    }

    cJSON *supported_features = cJSON_GetObjectItemCaseSensitive(problem_detailsJSON, "supportedFeatures");

    if (supported_features) {
        if (!cJSON_IsString(supported_features))
        {
            goto end;
        }
    }

    problem_details_local_var = ogs_sbi_problem_details_create (
        type ? ogs_strdup(type->valuestring) : NULL,
        title ? ogs_strdup(title->valuestring) : NULL,
        status ? status->valuedouble : 0,
        detail ? ogs_strdup(detail->valuestring) : NULL,
        instance ? ogs_strdup(instance->valuestring) : NULL,
        cause ? ogs_strdup(cause->valuestring) : NULL,
        invalid_params ? invalid_paramsList : NULL,
        supported_features ? ogs_strdup(supported_features->valuestring) : NULL
        );

    return problem_details_local_var;
end:
    return NULL;
}

