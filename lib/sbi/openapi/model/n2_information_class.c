
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "n2_information_class.h"

ogs_sbi_n2_information_class_t *ogs_sbi_n2_information_class_create(
    )
{
    ogs_sbi_n2_information_class_t *n2_information_class_local_var = ogs_malloc(sizeof(ogs_sbi_n2_information_class_t));
    if (!n2_information_class_local_var) {
        return NULL;
    }

    return n2_information_class_local_var;
}

void ogs_sbi_n2_information_class_free(ogs_sbi_n2_information_class_t *n2_information_class)
{
    if (NULL == n2_information_class) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(n2_information_class);
}

cJSON *ogs_sbi_n2_information_class_convertToJSON(ogs_sbi_n2_information_class_t *n2_information_class)
{
    cJSON *item = cJSON_CreateObject();
    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_n2_information_class_t *ogs_sbi_n2_information_class_parseFromJSON(cJSON *n2_information_classJSON)
{
    ogs_sbi_n2_information_class_t *n2_information_class_local_var = NULL;
    n2_information_class_local_var = ogs_sbi_n2_information_class_create (
        );

    return n2_information_class_local_var;
end:
    return NULL;
}

