
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "change_type.h"

ogs_sbi_change_type_t *ogs_sbi_change_type_create(
    )
{
    ogs_sbi_change_type_t *change_type_local_var = ogs_malloc(sizeof(ogs_sbi_change_type_t));
    if (!change_type_local_var) {
        return NULL;
    }

    return change_type_local_var;
}

void ogs_sbi_change_type_free(ogs_sbi_change_type_t *change_type)
{
    if (NULL == change_type) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(change_type);
}

cJSON *ogs_sbi_change_type_convertToJSON(ogs_sbi_change_type_t *change_type)
{
    cJSON *item = cJSON_CreateObject();
    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_change_type_t *ogs_sbi_change_type_parseFromJSON(cJSON *change_typeJSON)
{
    ogs_sbi_change_type_t *change_type_local_var = NULL;
    change_type_local_var = ogs_sbi_change_type_create (
        );

    return change_type_local_var;
end:
    return NULL;
}

