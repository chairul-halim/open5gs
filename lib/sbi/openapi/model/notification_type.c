
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "notification_type.h"

ogs_sbi_notification_type_t *ogs_sbi_notification_type_create(
    )
{
    ogs_sbi_notification_type_t *notification_type_local_var = ogs_malloc(sizeof(ogs_sbi_notification_type_t));
    if (!notification_type_local_var) {
        return NULL;
    }

    return notification_type_local_var;
}

void ogs_sbi_notification_type_free(ogs_sbi_notification_type_t *notification_type)
{
    if (NULL == notification_type) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(notification_type);
}

cJSON *ogs_sbi_notification_type_convertToJSON(ogs_sbi_notification_type_t *notification_type)
{
    cJSON *item = cJSON_CreateObject();
    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_notification_type_t *ogs_sbi_notification_type_parseFromJSON(cJSON *notification_typeJSON)
{
    ogs_sbi_notification_type_t *notification_type_local_var = NULL;
    notification_type_local_var = ogs_sbi_notification_type_create (
        );

    return notification_type_local_var;
end:
    return NULL;
}

