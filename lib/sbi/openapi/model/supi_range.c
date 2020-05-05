
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "supi_range.h"

ogs_sbi_supi_range_t *ogs_sbi_supi_range_create(
    char *start,
    char *end,
    char *pattern
    )
{
    ogs_sbi_supi_range_t *supi_range_local_var = ogs_malloc(sizeof(ogs_sbi_supi_range_t));
    if (!supi_range_local_var) {
        return NULL;
    }
    supi_range_local_var->start = start;
    supi_range_local_var->end = end;
    supi_range_local_var->pattern = pattern;

    return supi_range_local_var;
}

void ogs_sbi_supi_range_free(ogs_sbi_supi_range_t *supi_range)
{
    if (NULL == supi_range) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(supi_range->start);
    ogs_free(supi_range->end);
    ogs_free(supi_range->pattern);
    ogs_free(supi_range);
}

cJSON *ogs_sbi_supi_range_convertToJSON(ogs_sbi_supi_range_t *supi_range)
{
    cJSON *item = cJSON_CreateObject();
    if (supi_range->start) {
        if (cJSON_AddStringToObject(item, "start", supi_range->start) == NULL) {
            goto fail;
        }
    }

    if (supi_range->end) {
        if (cJSON_AddStringToObject(item, "end", supi_range->end) == NULL) {
            goto fail;
        }
    }

    if (supi_range->pattern) {
        if (cJSON_AddStringToObject(item, "pattern", supi_range->pattern) == NULL) {
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

ogs_sbi_supi_range_t *ogs_sbi_supi_range_parseFromJSON(cJSON *supi_rangeJSON)
{
    ogs_sbi_supi_range_t *supi_range_local_var = NULL;
    cJSON *start = cJSON_GetObjectItemCaseSensitive(supi_rangeJSON, "start");

    if (start) {
        if (!cJSON_IsString(start))
        {
            goto end;
        }
    }

    cJSON *end = cJSON_GetObjectItemCaseSensitive(supi_rangeJSON, "end");

    if (end) {
        if (!cJSON_IsString(end))
        {
            goto end;
        }
    }

    cJSON *pattern = cJSON_GetObjectItemCaseSensitive(supi_rangeJSON, "pattern");

    if (pattern) {
        if (!cJSON_IsString(pattern))
        {
            goto end;
        }
    }

    supi_range_local_var = ogs_sbi_supi_range_create (
        start ? ogs_strdup(start->valuestring) : NULL,
        end ? ogs_strdup(end->valuestring) : NULL,
        pattern ? ogs_strdup(pattern->valuestring) : NULL
        );

    return supi_range_local_var;
end:
    return NULL;
}

