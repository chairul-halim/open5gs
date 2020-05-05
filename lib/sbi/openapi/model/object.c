#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "object.h"

ogs_sbi_object_t *ogs_sbi_object_create(void)
{
    ogs_sbi_object_t *object = ogs_malloc(sizeof(ogs_sbi_object_t));

    return object;
}

void ogs_sbi_object_free(ogs_sbi_object_t *object)
{
    ogs_free (object);
}

cJSON *ogs_sbi_object_convertToJSON(ogs_sbi_object_t *object)
{
    cJSON *item = cJSON_CreateObject();

    return item;
fail:
    cJSON_Delete(item);
    return NULL;
}

ogs_sbi_object_t *ogs_sbi_object_parseFromJSON(cJSON *objectJSON)
{
    ogs_sbi_object_t *object = NULL;

    return object;
end:
    return NULL;
}
