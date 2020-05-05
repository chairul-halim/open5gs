
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "patch_operation.h"

ogs_sbi_patch_operation_t *ogs_sbi_patch_operation_create(
    )
{
    ogs_sbi_patch_operation_t *patch_operation_local_var = ogs_malloc(sizeof(ogs_sbi_patch_operation_t));
    if (!patch_operation_local_var) {
        return NULL;
    }

    return patch_operation_local_var;
}

void ogs_sbi_patch_operation_free(ogs_sbi_patch_operation_t *patch_operation)
{
    if (NULL == patch_operation) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(patch_operation);
}

cJSON *ogs_sbi_patch_operation_convertToJSON(ogs_sbi_patch_operation_t *patch_operation)
{
    cJSON *item = cJSON_CreateObject();
    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_patch_operation_t *ogs_sbi_patch_operation_parseFromJSON(cJSON *patch_operationJSON)
{
    ogs_sbi_patch_operation_t *patch_operation_local_var = NULL;
    patch_operation_local_var = ogs_sbi_patch_operation_create (
        );

    return patch_operation_local_var;
end:
    return NULL;
}

