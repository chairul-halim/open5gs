
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "up_interface_type.h"

ogs_sbi_up_interface_type_t *ogs_sbi_up_interface_type_create(
    )
{
    ogs_sbi_up_interface_type_t *up_interface_type_local_var = ogs_malloc(sizeof(ogs_sbi_up_interface_type_t));
    if (!up_interface_type_local_var) {
        return NULL;
    }

    return up_interface_type_local_var;
}

void ogs_sbi_up_interface_type_free(ogs_sbi_up_interface_type_t *up_interface_type)
{
    if (NULL == up_interface_type) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(up_interface_type);
}

cJSON *ogs_sbi_up_interface_type_convertToJSON(ogs_sbi_up_interface_type_t *up_interface_type)
{
    cJSON *item = cJSON_CreateObject();
    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_up_interface_type_t *ogs_sbi_up_interface_type_parseFromJSON(cJSON *up_interface_typeJSON)
{
    ogs_sbi_up_interface_type_t *up_interface_type_local_var = NULL;
    up_interface_type_local_var = ogs_sbi_up_interface_type_create (
        );

    return up_interface_type_local_var;
end:
    return NULL;
}

