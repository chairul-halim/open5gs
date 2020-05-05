
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "patch_item.h"

ogs_sbi_patch_item_t *ogs_sbi_patch_item_create(
    ogs_sbi_patch_operation_t *op,
    char *path,
    char *from,
    char *value
    )
{
    ogs_sbi_patch_item_t *patch_item_local_var = ogs_malloc(sizeof(ogs_sbi_patch_item_t));
    if (!patch_item_local_var) {
        return NULL;
    }
    patch_item_local_var->op = op;
    patch_item_local_var->path = path;
    patch_item_local_var->from = from;
    patch_item_local_var->value = value;

    return patch_item_local_var;
}

void ogs_sbi_patch_item_free(ogs_sbi_patch_item_t *patch_item)
{
    if (NULL == patch_item) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_sbi_patch_operation_free(patch_item->op);
    ogs_free(patch_item->path);
    ogs_free(patch_item->from);
    ogs_free(patch_item->value);
    ogs_free(patch_item);
}

cJSON *ogs_sbi_patch_item_convertToJSON(ogs_sbi_patch_item_t *patch_item)
{
    cJSON *item = cJSON_CreateObject();
    if (!patch_item->op) {
        goto fail;
    }
    cJSON *op_local_JSON = ogs_sbi_patch_operation_convertToJSON(patch_item->op);
    if (op_local_JSON == NULL) {
        goto fail;
    }
    cJSON_AddItemToObject(item, "op", op_local_JSON);
    if (item->child == NULL) {
        goto fail;
    }

    if (!patch_item->path) {
        goto fail;
    }
    if (cJSON_AddStringToObject(item, "path", patch_item->path) == NULL) {
        goto fail;
    }

    if (patch_item->from) {
        if (cJSON_AddStringToObject(item, "from", patch_item->from) == NULL) {
            goto fail;
        }
    }

    if (patch_item->value) {
        if (cJSON_AddStringToObject(item, "value", patch_item->value) == NULL) {
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

ogs_sbi_patch_item_t *ogs_sbi_patch_item_parseFromJSON(cJSON *patch_itemJSON)
{
    ogs_sbi_patch_item_t *patch_item_local_var = NULL;
    cJSON *op = cJSON_GetObjectItemCaseSensitive(patch_itemJSON, "op");
    if (!op) {
        goto end;
    }

    ogs_sbi_patch_operation_t *op_local_nonprim = NULL;

    op_local_nonprim = ogs_sbi_patch_operation_parseFromJSON(op);

    cJSON *path = cJSON_GetObjectItemCaseSensitive(patch_itemJSON, "path");
    if (!path) {
        goto end;
    }


    if (!cJSON_IsString(path))
    {
        goto end;
    }

    cJSON *from = cJSON_GetObjectItemCaseSensitive(patch_itemJSON, "from");

    if (from) {
        if (!cJSON_IsString(from))
        {
            goto end;
        }
    }

    cJSON *value = cJSON_GetObjectItemCaseSensitive(patch_itemJSON, "value");

    if (value) {
        if (!cJSON_IsString(value))
        {
            goto end;
        }
    }

    patch_item_local_var = ogs_sbi_patch_item_create (
        op_local_nonprim,
        ogs_strdup(path->valuestring),
        from ? ogs_strdup(from->valuestring) : NULL,
        value ? ogs_strdup(value->valuestring) : NULL
        );

    return patch_item_local_var;
end:
    return NULL;
}

