
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "service_name.h"

ogs_sbi_service_name_t *ogs_sbi_service_name_create(
    )
{
    ogs_sbi_service_name_t *service_name_local_var = ogs_malloc(sizeof(ogs_sbi_service_name_t));
    if (!service_name_local_var) {
        return NULL;
    }

    return service_name_local_var;
}

void ogs_sbi_service_name_free(ogs_sbi_service_name_t *service_name)
{
    if (NULL == service_name) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(service_name);
}

cJSON *ogs_sbi_service_name_convertToJSON(ogs_sbi_service_name_t *service_name)
{
    cJSON *item = cJSON_CreateObject();
    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_service_name_t *ogs_sbi_service_name_parseFromJSON(cJSON *service_nameJSON)
{
    ogs_sbi_service_name_t *service_name_local_var = NULL;
    service_name_local_var = ogs_sbi_service_name_create (
        );

    return service_name_local_var;
end:
    return NULL;
}

