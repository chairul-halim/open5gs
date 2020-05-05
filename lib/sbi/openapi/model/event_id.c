
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "event_id.h"

ogs_sbi_event_id_t *ogs_sbi_event_id_create(
    )
{
    ogs_sbi_event_id_t *event_id_local_var = ogs_malloc(sizeof(ogs_sbi_event_id_t));
    if (!event_id_local_var) {
        return NULL;
    }

    return event_id_local_var;
}

void ogs_sbi_event_id_free(ogs_sbi_event_id_t *event_id)
{
    if (NULL == event_id) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(event_id);
}

cJSON *ogs_sbi_event_id_convertToJSON(ogs_sbi_event_id_t *event_id)
{
    cJSON *item = cJSON_CreateObject();
    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_event_id_t *ogs_sbi_event_id_parseFromJSON(cJSON *event_idJSON)
{
    ogs_sbi_event_id_t *event_id_local_var = NULL;
    event_id_local_var = ogs_sbi_event_id_create (
        );

    return event_id_local_var;
end:
    return NULL;
}

