
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "link.h"

ogs_sbi_link_t *ogs_sbi_link_create(
    char *href
    )
{
    ogs_sbi_link_t *link_local_var = ogs_malloc(sizeof(ogs_sbi_link_t));
    if (!link_local_var) {
        return NULL;
    }
    link_local_var->href = href;

    return link_local_var;
}

void ogs_sbi_link_free(ogs_sbi_link_t *link)
{
    if (NULL == link) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(link->href);
    ogs_free(link);
}

cJSON *ogs_sbi_link_convertToJSON(ogs_sbi_link_t *link)
{
    cJSON *item = cJSON_CreateObject();
    if (link->href) {
        if (cJSON_AddStringToObject(item, "href", link->href) == NULL) {
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

ogs_sbi_link_t *ogs_sbi_link_parseFromJSON(cJSON *linkJSON)
{
    ogs_sbi_link_t *link_local_var = NULL;
    cJSON *href = cJSON_GetObjectItemCaseSensitive(linkJSON, "href");

    if (href) {
        if (!cJSON_IsString(href))
        {
            goto end;
        }
    }

    link_local_var = ogs_sbi_link_create (
        href ? ogs_strdup(href->valuestring) : NULL
        );

    return link_local_var;
end:
    return NULL;
}

