
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "guami_list_cond.h"

ogs_sbi_guami_list_cond_t *ogs_sbi_guami_list_cond_create(
    ogs_sbi_list_t *guami_list
    )
{
    ogs_sbi_guami_list_cond_t *guami_list_cond_local_var = ogs_malloc(sizeof(ogs_sbi_guami_list_cond_t));
    if (!guami_list_cond_local_var) {
        return NULL;
    }
    guami_list_cond_local_var->guami_list = guami_list;

    return guami_list_cond_local_var;
}

void ogs_sbi_guami_list_cond_free(ogs_sbi_guami_list_cond_t *guami_list_cond)
{
    if (NULL == guami_list_cond) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_sbi_list_for_each(node, guami_list_cond->guami_list) {
        ogs_sbi_guami_free(node->data);
    }
    ogs_sbi_list_free(guami_list_cond->guami_list);
    ogs_free(guami_list_cond);
}

cJSON *ogs_sbi_guami_list_cond_convertToJSON(ogs_sbi_guami_list_cond_t *guami_list_cond)
{
    cJSON *item = cJSON_CreateObject();
    if (!guami_list_cond->guami_list) {
        goto fail;
    }
    cJSON *guami_list = cJSON_AddArrayToObject(item, "guamiList");
    if (guami_list == NULL) {
        goto fail;
    }

    ogs_sbi_lnode_t *guami_list_node;
    if (guami_list_cond->guami_list) {
        ogs_sbi_list_for_each(guami_list_node, guami_list_cond->guami_list) {
            cJSON *itemLocal = ogs_sbi_guami_convertToJSON(guami_list_node->data);
            if (itemLocal == NULL) {
                goto fail;
            }
            cJSON_AddItemToArray(guami_list, itemLocal);
        }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_guami_list_cond_t *ogs_sbi_guami_list_cond_parseFromJSON(cJSON *guami_list_condJSON)
{
    ogs_sbi_guami_list_cond_t *guami_list_cond_local_var = NULL;
    cJSON *guami_list = cJSON_GetObjectItemCaseSensitive(guami_list_condJSON, "guamiList");
    if (!guami_list) {
        goto end;
    }

    ogs_sbi_list_t *guami_listList;

    cJSON *guami_list_local_nonprimitive;
    if (!cJSON_IsArray(guami_list)) {
        goto end;
    }

    guami_listList = ogs_sbi_list_create();

    cJSON_ArrayForEach(guami_list_local_nonprimitive,guami_list ) {
        if (!cJSON_IsObject(guami_list_local_nonprimitive)) {
            goto end;
        }
        ogs_sbi_guami_t *guami_listItem = ogs_sbi_guami_parseFromJSON(guami_list_local_nonprimitive);

        ogs_sbi_list_add(guami_listList, guami_listItem);
    }

    guami_list_cond_local_var = ogs_sbi_guami_list_cond_create (
        guami_listList
        );

    return guami_list_cond_local_var;
end:
    return NULL;
}

