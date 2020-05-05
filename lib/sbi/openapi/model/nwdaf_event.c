
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "nwdaf_event.h"

ogs_sbi_nwdaf_event_t *ogs_sbi_nwdaf_event_create(
    )
{
    ogs_sbi_nwdaf_event_t *nwdaf_event_local_var = ogs_malloc(sizeof(ogs_sbi_nwdaf_event_t));
    if (!nwdaf_event_local_var) {
        return NULL;
    }

    return nwdaf_event_local_var;
}

void ogs_sbi_nwdaf_event_free(ogs_sbi_nwdaf_event_t *nwdaf_event)
{
    if (NULL == nwdaf_event) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(nwdaf_event);
}

cJSON *ogs_sbi_nwdaf_event_convertToJSON(ogs_sbi_nwdaf_event_t *nwdaf_event)
{
    cJSON *item = cJSON_CreateObject();
    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_nwdaf_event_t *ogs_sbi_nwdaf_event_parseFromJSON(cJSON *nwdaf_eventJSON)
{
    ogs_sbi_nwdaf_event_t *nwdaf_event_local_var = NULL;
    nwdaf_event_local_var = ogs_sbi_nwdaf_event_create (
        );

    return nwdaf_event_local_var;
end:
    return NULL;
}

