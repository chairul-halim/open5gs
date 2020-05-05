
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "notif_condition.h"

ogs_sbi_notif_condition_t *ogs_sbi_notif_condition_create(
    ogs_sbi_list_t *monitored_attributes,
    ogs_sbi_list_t *unmonitored_attributes
    )
{
    ogs_sbi_notif_condition_t *notif_condition_local_var = ogs_malloc(sizeof(ogs_sbi_notif_condition_t));
    if (!notif_condition_local_var) {
        return NULL;
    }
    notif_condition_local_var->monitored_attributes = monitored_attributes;
    notif_condition_local_var->unmonitored_attributes = unmonitored_attributes;

    return notif_condition_local_var;
}

void ogs_sbi_notif_condition_free(ogs_sbi_notif_condition_t *notif_condition)
{
    if (NULL == notif_condition) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_sbi_list_for_each(node, notif_condition->monitored_attributes) {
        ogs_free(node->data);
    }
    ogs_sbi_list_free(notif_condition->monitored_attributes);
    ogs_sbi_list_for_each(node, notif_condition->unmonitored_attributes) {
        ogs_free(node->data);
    }
    ogs_sbi_list_free(notif_condition->unmonitored_attributes);
    ogs_free(notif_condition);
}

cJSON *ogs_sbi_notif_condition_convertToJSON(ogs_sbi_notif_condition_t *notif_condition)
{
    cJSON *item = cJSON_CreateObject();
    if (notif_condition->monitored_attributes) {
        cJSON *monitored_attributes = cJSON_AddArrayToObject(item, "monitoredAttributes");
        if (monitored_attributes == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *monitored_attributes_node;
        ogs_sbi_list_for_each(monitored_attributes_node, notif_condition->monitored_attributes) {
            if (cJSON_AddStringToObject(monitored_attributes, "", (char*)monitored_attributes_node->data) == NULL) {
                goto fail;
            }
        }
    }

    if (notif_condition->unmonitored_attributes) {
        cJSON *unmonitored_attributes = cJSON_AddArrayToObject(item, "unmonitoredAttributes");
        if (unmonitored_attributes == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *unmonitored_attributes_node;
        ogs_sbi_list_for_each(unmonitored_attributes_node, notif_condition->unmonitored_attributes) {
            if (cJSON_AddStringToObject(unmonitored_attributes, "", (char*)unmonitored_attributes_node->data) == NULL) {
                goto fail;
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

ogs_sbi_notif_condition_t *ogs_sbi_notif_condition_parseFromJSON(cJSON *notif_conditionJSON)
{
    ogs_sbi_notif_condition_t *notif_condition_local_var = NULL;
    cJSON *monitored_attributes = cJSON_GetObjectItemCaseSensitive(notif_conditionJSON, "monitoredAttributes");

    ogs_sbi_list_t *monitored_attributesList;
    if (monitored_attributes) {
        cJSON *monitored_attributes_local;
        if (!cJSON_IsArray(monitored_attributes)) {
            goto end;
        }
        monitored_attributesList = ogs_sbi_list_create();

        cJSON_ArrayForEach(monitored_attributes_local, monitored_attributes) {
            if (!cJSON_IsString(monitored_attributes_local)) {
                goto end;
            }
            ogs_sbi_list_add(monitored_attributesList, ogs_strdup(monitored_attributes_local->valuestring));
        }
    }

    cJSON *unmonitored_attributes = cJSON_GetObjectItemCaseSensitive(notif_conditionJSON, "unmonitoredAttributes");

    ogs_sbi_list_t *unmonitored_attributesList;
    if (unmonitored_attributes) {
        cJSON *unmonitored_attributes_local;
        if (!cJSON_IsArray(unmonitored_attributes)) {
            goto end;
        }
        unmonitored_attributesList = ogs_sbi_list_create();

        cJSON_ArrayForEach(unmonitored_attributes_local, unmonitored_attributes) {
            if (!cJSON_IsString(unmonitored_attributes_local)) {
                goto end;
            }
            ogs_sbi_list_add(unmonitored_attributesList, ogs_strdup(unmonitored_attributes_local->valuestring));
        }
    }

    notif_condition_local_var = ogs_sbi_notif_condition_create (
        monitored_attributes ? monitored_attributesList : NULL,
        unmonitored_attributes ? unmonitored_attributesList : NULL
        );

    return notif_condition_local_var;
end:
    return NULL;
}

