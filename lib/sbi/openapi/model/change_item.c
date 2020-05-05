
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "change_item.h"

ogs_sbi_change_item_t *ogs_sbi_change_item_create(
    ogs_sbi_change_type_t *op,
    char *path,
    char *from,
    char *orig_value,
    char *new_value
    )
{
    ogs_sbi_change_item_t *change_item_local_var = ogs_malloc(sizeof(ogs_sbi_change_item_t));
    if (!change_item_local_var) {
        return NULL;
    }
    change_item_local_var->op = op;
    change_item_local_var->path = path;
    change_item_local_var->from = from;
    change_item_local_var->orig_value = orig_value;
    change_item_local_var->new_value = new_value;

    return change_item_local_var;
}

void ogs_sbi_change_item_free(ogs_sbi_change_item_t *change_item)
{
    if (NULL == change_item) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_sbi_change_type_free(change_item->op);
    ogs_free(change_item->path);
    ogs_free(change_item->from);
    ogs_free(change_item->orig_value);
    ogs_free(change_item->new_value);
    ogs_free(change_item);
}

cJSON *ogs_sbi_change_item_convertToJSON(ogs_sbi_change_item_t *change_item)
{
    cJSON *item = cJSON_CreateObject();
    if (!change_item->op) {
        goto fail;
    }
    cJSON *op_local_JSON = ogs_sbi_change_type_convertToJSON(change_item->op);
    if (op_local_JSON == NULL) {
        goto fail;
    }
    cJSON_AddItemToObject(item, "op", op_local_JSON);
    if (item->child == NULL) {
        goto fail;
    }

    if (!change_item->path) {
        goto fail;
    }
    if (cJSON_AddStringToObject(item, "path", change_item->path) == NULL) {
        goto fail;
    }

    if (change_item->from) {
        if (cJSON_AddStringToObject(item, "from", change_item->from) == NULL) {
            goto fail;
        }
    }

    if (change_item->orig_value) {
        if (cJSON_AddStringToObject(item, "origValue", change_item->orig_value) == NULL) {
            goto fail;
        }
    }

    if (change_item->new_value) {
        if (cJSON_AddStringToObject(item, "newValue", change_item->new_value) == NULL) {
            goto fail;
        }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_change_item_t *ogs_sbi_change_item_parseFromJSON(cJSON *change_itemJSON)
{
    ogs_sbi_change_item_t *change_item_local_var = NULL;
    cJSON *op = cJSON_GetObjectItemCaseSensitive(change_itemJSON, "op");
    if (!op) {
        goto end;
    }

    ogs_sbi_change_type_t *op_local_nonprim = NULL;

    op_local_nonprim = ogs_sbi_change_type_parseFromJSON(op);

    cJSON *path = cJSON_GetObjectItemCaseSensitive(change_itemJSON, "path");
    if (!path) {
        goto end;
    }


    if (!cJSON_IsString(path))
    {
        goto end;
    }

    cJSON *from = cJSON_GetObjectItemCaseSensitive(change_itemJSON, "from");

    if (from) {
        if (!cJSON_IsString(from))
        {
            goto end;
        }
    }

    cJSON *orig_value = cJSON_GetObjectItemCaseSensitive(change_itemJSON, "origValue");

    if (orig_value) {
        if (!cJSON_IsString(orig_value))
        {
            goto end;
        }
    }

    cJSON *new_value = cJSON_GetObjectItemCaseSensitive(change_itemJSON, "newValue");

    if (new_value) {
        if (!cJSON_IsString(new_value))
        {
            goto end;
        }
    }

    change_item_local_var = ogs_sbi_change_item_create (
        op_local_nonprim,
        ogs_strdup(path->valuestring),
        from ? ogs_strdup(from->valuestring) : NULL,
        orig_value ? ogs_strdup(orig_value->valuestring) : NULL,
        new_value ? ogs_strdup(new_value->valuestring) : NULL
        );

    return change_item_local_var;
end:
    return NULL;
}

