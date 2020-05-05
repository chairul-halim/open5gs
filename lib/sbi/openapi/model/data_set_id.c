
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "data_set_id.h"

ogs_sbi_data_set_id_t *ogs_sbi_data_set_id_create(
    )
{
    ogs_sbi_data_set_id_t *data_set_id_local_var = ogs_malloc(sizeof(ogs_sbi_data_set_id_t));
    if (!data_set_id_local_var) {
        return NULL;
    }

    return data_set_id_local_var;
}

void ogs_sbi_data_set_id_free(ogs_sbi_data_set_id_t *data_set_id)
{
    if (NULL == data_set_id) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(data_set_id);
}

cJSON *ogs_sbi_data_set_id_convertToJSON(ogs_sbi_data_set_id_t *data_set_id)
{
    cJSON *item = cJSON_CreateObject();
    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_data_set_id_t *ogs_sbi_data_set_id_parseFromJSON(cJSON *data_set_idJSON)
{
    ogs_sbi_data_set_id_t *data_set_id_local_var = NULL;
    data_set_id_local_var = ogs_sbi_data_set_id_create (
        );

    return data_set_id_local_var;
end:
    return NULL;
}

