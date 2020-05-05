
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "notification_event_type.h"

ogs_sbi_notification_event_type_t *ogs_sbi_notification_event_type_create(
    )
{
    ogs_sbi_notification_event_type_t *notification_event_type_local_var = ogs_malloc(sizeof(ogs_sbi_notification_event_type_t));
    if (!notification_event_type_local_var) {
        return NULL;
    }

    return notification_event_type_local_var;
}

void ogs_sbi_notification_event_type_free(ogs_sbi_notification_event_type_t *notification_event_type)
{
    if (NULL == notification_event_type) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(notification_event_type);
}

cJSON *ogs_sbi_notification_event_type_convertToJSON(ogs_sbi_notification_event_type_t *notification_event_type)
{
    cJSON *item = cJSON_CreateObject();
    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_notification_event_type_t *ogs_sbi_notification_event_type_parseFromJSON(cJSON *notification_event_typeJSON)
{
    ogs_sbi_notification_event_type_t *notification_event_type_local_var = NULL;
    notification_event_type_local_var = ogs_sbi_notification_event_type_create (
        );

    return notification_event_type_local_var;
end:
    return NULL;
}

