
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "nf_service_version.h"

ogs_sbi_nf_service_version_t *ogs_sbi_nf_service_version_create(
    char *api_version_in_uri,
    char *api_full_version,
    char *expiry
    )
{
    ogs_sbi_nf_service_version_t *nf_service_version_local_var = ogs_malloc(sizeof(ogs_sbi_nf_service_version_t));
    if (!nf_service_version_local_var) {
        return NULL;
    }
    nf_service_version_local_var->api_version_in_uri = api_version_in_uri;
    nf_service_version_local_var->api_full_version = api_full_version;
    nf_service_version_local_var->expiry = expiry;

    return nf_service_version_local_var;
}

void ogs_sbi_nf_service_version_free(ogs_sbi_nf_service_version_t *nf_service_version)
{
    if (NULL == nf_service_version) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(nf_service_version->api_version_in_uri);
    ogs_free(nf_service_version->api_full_version);
    ogs_free(nf_service_version->expiry);
    ogs_free(nf_service_version);
}

cJSON *ogs_sbi_nf_service_version_convertToJSON(ogs_sbi_nf_service_version_t *nf_service_version)
{
    cJSON *item = cJSON_CreateObject();
    if (!nf_service_version->api_version_in_uri) {
        goto fail;
    }
    if (cJSON_AddStringToObject(item, "apiVersionInUri", nf_service_version->api_version_in_uri) == NULL) {
        goto fail;
    }

    if (!nf_service_version->api_full_version) {
        goto fail;
    }
    if (cJSON_AddStringToObject(item, "apiFullVersion", nf_service_version->api_full_version) == NULL) {
        goto fail;
    }

    if (nf_service_version->expiry) {
        if (cJSON_AddStringToObject(item, "expiry", nf_service_version->expiry) == NULL) {
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

ogs_sbi_nf_service_version_t *ogs_sbi_nf_service_version_parseFromJSON(cJSON *nf_service_versionJSON)
{
    ogs_sbi_nf_service_version_t *nf_service_version_local_var = NULL;
    cJSON *api_version_in_uri = cJSON_GetObjectItemCaseSensitive(nf_service_versionJSON, "apiVersionInUri");
    if (!api_version_in_uri) {
        goto end;
    }


    if (!cJSON_IsString(api_version_in_uri))
    {
        goto end;
    }

    cJSON *api_full_version = cJSON_GetObjectItemCaseSensitive(nf_service_versionJSON, "apiFullVersion");
    if (!api_full_version) {
        goto end;
    }


    if (!cJSON_IsString(api_full_version))
    {
        goto end;
    }

    cJSON *expiry = cJSON_GetObjectItemCaseSensitive(nf_service_versionJSON, "expiry");

    if (expiry) {
        if (!cJSON_IsString(expiry)) {
            goto end;
        }
    }

    nf_service_version_local_var = ogs_sbi_nf_service_version_create (
        ogs_strdup(api_version_in_uri->valuestring),
        ogs_strdup(api_full_version->valuestring),
        expiry ? ogs_strdup(expiry->valuestring) : NULL
        );

    return nf_service_version_local_var;
end:
    return NULL;
}

