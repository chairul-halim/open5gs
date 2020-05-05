
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "nf_service_status.h"

ogs_sbi_nf_service_status_t *ogs_sbi_nf_service_status_create(
    )
{
    ogs_sbi_nf_service_status_t *nf_service_status_local_var = ogs_malloc(sizeof(ogs_sbi_nf_service_status_t));
    if (!nf_service_status_local_var) {
        return NULL;
    }

    return nf_service_status_local_var;
}

void ogs_sbi_nf_service_status_free(ogs_sbi_nf_service_status_t *nf_service_status)
{
    if (NULL == nf_service_status) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(nf_service_status);
}

cJSON *ogs_sbi_nf_service_status_convertToJSON(ogs_sbi_nf_service_status_t *nf_service_status)
{
    cJSON *item = cJSON_CreateObject();
    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_nf_service_status_t *ogs_sbi_nf_service_status_parseFromJSON(cJSON *nf_service_statusJSON)
{
    ogs_sbi_nf_service_status_t *nf_service_status_local_var = NULL;
    nf_service_status_local_var = ogs_sbi_nf_service_status_create (
        );

    return nf_service_status_local_var;
end:
    return NULL;
}

