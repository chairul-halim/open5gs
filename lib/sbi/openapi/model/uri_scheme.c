
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "uri_scheme.h"

ogs_sbi_uri_scheme_t *ogs_sbi_uri_scheme_create(
    )
{
    ogs_sbi_uri_scheme_t *uri_scheme_local_var = ogs_malloc(sizeof(ogs_sbi_uri_scheme_t));
    if (!uri_scheme_local_var) {
        return NULL;
    }

    return uri_scheme_local_var;
}

void ogs_sbi_uri_scheme_free(ogs_sbi_uri_scheme_t *uri_scheme)
{
    if (NULL == uri_scheme) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(uri_scheme);
}

cJSON *ogs_sbi_uri_scheme_convertToJSON(ogs_sbi_uri_scheme_t *uri_scheme)
{
    cJSON *item = cJSON_CreateObject();
    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_uri_scheme_t *ogs_sbi_uri_scheme_parseFromJSON(cJSON *uri_schemeJSON)
{
    ogs_sbi_uri_scheme_t *uri_scheme_local_var = NULL;
    uri_scheme_local_var = ogs_sbi_uri_scheme_create (
        );

    return uri_scheme_local_var;
end:
    return NULL;
}

