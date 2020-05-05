
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "nwdaf_info.h"

ogs_sbi_nwdaf_info_t *ogs_sbi_nwdaf_info_create(
    ogs_sbi_list_t *event_ids,
    ogs_sbi_list_t *nwdaf_events,
    ogs_sbi_list_t *tai_list,
    ogs_sbi_list_t *tai_range_list
    )
{
    ogs_sbi_nwdaf_info_t *nwdaf_info_local_var = ogs_malloc(sizeof(ogs_sbi_nwdaf_info_t));
    if (!nwdaf_info_local_var) {
        return NULL;
    }
    nwdaf_info_local_var->event_ids = event_ids;
    nwdaf_info_local_var->nwdaf_events = nwdaf_events;
    nwdaf_info_local_var->tai_list = tai_list;
    nwdaf_info_local_var->tai_range_list = tai_range_list;

    return nwdaf_info_local_var;
}

void ogs_sbi_nwdaf_info_free(ogs_sbi_nwdaf_info_t *nwdaf_info)
{
    if (NULL == nwdaf_info) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_sbi_list_for_each(node, nwdaf_info->event_ids) {
        ogs_sbi_event_id_free(node->data);
    }
    ogs_sbi_list_free(nwdaf_info->event_ids);
    ogs_sbi_list_for_each(node, nwdaf_info->nwdaf_events) {
        ogs_sbi_nwdaf_event_free(node->data);
    }
    ogs_sbi_list_free(nwdaf_info->nwdaf_events);
    ogs_sbi_list_for_each(node, nwdaf_info->tai_list) {
        ogs_sbi_tai_free(node->data);
    }
    ogs_sbi_list_free(nwdaf_info->tai_list);
    ogs_sbi_list_for_each(node, nwdaf_info->tai_range_list) {
        ogs_sbi_tai_range_free(node->data);
    }
    ogs_sbi_list_free(nwdaf_info->tai_range_list);
    ogs_free(nwdaf_info);
}

cJSON *ogs_sbi_nwdaf_info_convertToJSON(ogs_sbi_nwdaf_info_t *nwdaf_info)
{
    cJSON *item = cJSON_CreateObject();
    if (nwdaf_info->event_ids) {
        cJSON *event_ids = cJSON_AddArrayToObject(item, "eventIds");
        if (event_ids == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *event_ids_node;
        if (nwdaf_info->event_ids) {
            ogs_sbi_list_for_each(event_ids_node, nwdaf_info->event_ids) {
                cJSON *itemLocal = ogs_sbi_event_id_convertToJSON(event_ids_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(event_ids, itemLocal);
            }
        }
    }

    if (nwdaf_info->nwdaf_events) {
        cJSON *nwdaf_events = cJSON_AddArrayToObject(item, "nwdafEvents");
        if (nwdaf_events == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *nwdaf_events_node;
        if (nwdaf_info->nwdaf_events) {
            ogs_sbi_list_for_each(nwdaf_events_node, nwdaf_info->nwdaf_events) {
                cJSON *itemLocal = ogs_sbi_nwdaf_event_convertToJSON(nwdaf_events_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(nwdaf_events, itemLocal);
            }
        }
    }

    if (nwdaf_info->tai_list) {
        cJSON *tai_list = cJSON_AddArrayToObject(item, "taiList");
        if (tai_list == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *tai_list_node;
        if (nwdaf_info->tai_list) {
            ogs_sbi_list_for_each(tai_list_node, nwdaf_info->tai_list) {
                cJSON *itemLocal = ogs_sbi_tai_convertToJSON(tai_list_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(tai_list, itemLocal);
            }
        }
    }

    if (nwdaf_info->tai_range_list) {
        cJSON *tai_range_list = cJSON_AddArrayToObject(item, "taiRangeList");
        if (tai_range_list == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *tai_range_list_node;
        if (nwdaf_info->tai_range_list) {
            ogs_sbi_list_for_each(tai_range_list_node, nwdaf_info->tai_range_list) {
                cJSON *itemLocal = ogs_sbi_tai_range_convertToJSON(tai_range_list_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(tai_range_list, itemLocal);
            }
        }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_nwdaf_info_t *ogs_sbi_nwdaf_info_parseFromJSON(cJSON *nwdaf_infoJSON)
{
    ogs_sbi_nwdaf_info_t *nwdaf_info_local_var = NULL;
    cJSON *event_ids = cJSON_GetObjectItemCaseSensitive(nwdaf_infoJSON, "eventIds");

    ogs_sbi_list_t *event_idsList;
    if (event_ids) {
        cJSON *event_ids_local_nonprimitive;
        if (!cJSON_IsArray(event_ids)) {
            goto end;
        }

        event_idsList = ogs_sbi_list_create();

        cJSON_ArrayForEach(event_ids_local_nonprimitive,event_ids ) {
            if (!cJSON_IsObject(event_ids_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_event_id_t *event_idsItem = ogs_sbi_event_id_parseFromJSON(event_ids_local_nonprimitive);

            ogs_sbi_list_add(event_idsList, event_idsItem);
        }
    }

    cJSON *nwdaf_events = cJSON_GetObjectItemCaseSensitive(nwdaf_infoJSON, "nwdafEvents");

    ogs_sbi_list_t *nwdaf_eventsList;
    if (nwdaf_events) {
        cJSON *nwdaf_events_local_nonprimitive;
        if (!cJSON_IsArray(nwdaf_events)) {
            goto end;
        }

        nwdaf_eventsList = ogs_sbi_list_create();

        cJSON_ArrayForEach(nwdaf_events_local_nonprimitive,nwdaf_events ) {
            if (!cJSON_IsObject(nwdaf_events_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_nwdaf_event_t *nwdaf_eventsItem = ogs_sbi_nwdaf_event_parseFromJSON(nwdaf_events_local_nonprimitive);

            ogs_sbi_list_add(nwdaf_eventsList, nwdaf_eventsItem);
        }
    }

    cJSON *tai_list = cJSON_GetObjectItemCaseSensitive(nwdaf_infoJSON, "taiList");

    ogs_sbi_list_t *tai_listList;
    if (tai_list) {
        cJSON *tai_list_local_nonprimitive;
        if (!cJSON_IsArray(tai_list)) {
            goto end;
        }

        tai_listList = ogs_sbi_list_create();

        cJSON_ArrayForEach(tai_list_local_nonprimitive,tai_list ) {
            if (!cJSON_IsObject(tai_list_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_tai_t *tai_listItem = ogs_sbi_tai_parseFromJSON(tai_list_local_nonprimitive);

            ogs_sbi_list_add(tai_listList, tai_listItem);
        }
    }

    cJSON *tai_range_list = cJSON_GetObjectItemCaseSensitive(nwdaf_infoJSON, "taiRangeList");

    ogs_sbi_list_t *tai_range_listList;
    if (tai_range_list) {
        cJSON *tai_range_list_local_nonprimitive;
        if (!cJSON_IsArray(tai_range_list)) {
            goto end;
        }

        tai_range_listList = ogs_sbi_list_create();

        cJSON_ArrayForEach(tai_range_list_local_nonprimitive,tai_range_list ) {
            if (!cJSON_IsObject(tai_range_list_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_tai_range_t *tai_range_listItem = ogs_sbi_tai_range_parseFromJSON(tai_range_list_local_nonprimitive);

            ogs_sbi_list_add(tai_range_listList, tai_range_listItem);
        }
    }

    nwdaf_info_local_var = ogs_sbi_nwdaf_info_create (
        event_ids ? event_idsList : NULL,
        nwdaf_events ? nwdaf_eventsList : NULL,
        tai_list ? tai_listList : NULL,
        tai_range_list ? tai_range_listList : NULL
        );

    return nwdaf_info_local_var;
end:
    return NULL;
}

