
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "n1_message_class.h"

ogs_sbi_n1_message_class_t *ogs_sbi_n1_message_class_create(
    )
{
    ogs_sbi_n1_message_class_t *n1_message_class_local_var = ogs_malloc(sizeof(ogs_sbi_n1_message_class_t));
    if (!n1_message_class_local_var) {
        return NULL;
    }

    return n1_message_class_local_var;
}

void ogs_sbi_n1_message_class_free(ogs_sbi_n1_message_class_t *n1_message_class)
{
    if (NULL == n1_message_class) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(n1_message_class);
}

cJSON *ogs_sbi_n1_message_class_convertToJSON(ogs_sbi_n1_message_class_t *n1_message_class)
{
    cJSON *item = cJSON_CreateObject();
    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_n1_message_class_t *ogs_sbi_n1_message_class_parseFromJSON(cJSON *n1_message_classJSON)
{
    ogs_sbi_n1_message_class_t *n1_message_class_local_var = NULL;
    n1_message_class_local_var = ogs_sbi_n1_message_class_create (
        );

    return n1_message_class_local_var;
end:
    return NULL;
}

