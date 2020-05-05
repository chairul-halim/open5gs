
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "links_value_schema.h"

ogs_sbi_links_value_schema_t *ogs_sbi_links_value_schema_create(
    char *href
    )
{
    ogs_sbi_links_value_schema_t *links_value_schema_local_var = ogs_malloc(sizeof(ogs_sbi_links_value_schema_t));
    if (!links_value_schema_local_var) {
        return NULL;
    }
    links_value_schema_local_var->href = href;

    return links_value_schema_local_var;
}

void ogs_sbi_links_value_schema_free(ogs_sbi_links_value_schema_t *links_value_schema)
{
    if (NULL == links_value_schema) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(links_value_schema->href);
    ogs_free(links_value_schema);
}

cJSON *ogs_sbi_links_value_schema_convertToJSON(ogs_sbi_links_value_schema_t *links_value_schema)
{
    cJSON *item = cJSON_CreateObject();
    if (links_value_schema->href) {
        if (cJSON_AddStringToObject(item, "href", links_value_schema->href) == NULL) {
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

ogs_sbi_links_value_schema_t *ogs_sbi_links_value_schema_parseFromJSON(cJSON *links_value_schemaJSON)
{
    ogs_sbi_links_value_schema_t *links_value_schema_local_var = NULL;
    cJSON *href = cJSON_GetObjectItemCaseSensitive(links_value_schemaJSON, "href");

    if (href) {
        if (!cJSON_IsString(href))
        {
            goto end;
        }
    }

    links_value_schema_local_var = ogs_sbi_links_value_schema_create (
        href ? ogs_strdup(href->valuestring) : NULL
        );

    return links_value_schema_local_var;
end:
    return NULL;
}

