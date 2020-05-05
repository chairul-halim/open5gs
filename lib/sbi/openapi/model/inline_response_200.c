
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "inline_response_200.h"

ogs_sbi_inline_response_200_t *ogs_sbi_inline_response_200_create(
    ogs_sbi_list_t* _links
    )
{
    ogs_sbi_inline_response_200_t *inline_response_200_local_var = ogs_malloc(sizeof(ogs_sbi_inline_response_200_t));
    if (!inline_response_200_local_var) {
        return NULL;
    }
    inline_response_200_local_var->_links = _links;

    return inline_response_200_local_var;
}

void ogs_sbi_inline_response_200_free(ogs_sbi_inline_response_200_t *inline_response_200)
{
    if (NULL == inline_response_200) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_sbi_list_for_each(node, inline_response_200->_links) {
        ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)node->data;
        ogs_sbi_links_value_schema_free(localKeyValue->value);
        ogs_free(localKeyValue);
    }
    ogs_sbi_list_free(inline_response_200->_links);
    ogs_free(inline_response_200);
}

cJSON *ogs_sbi_inline_response_200_convertToJSON(ogs_sbi_inline_response_200_t *inline_response_200)
{
    cJSON *item = cJSON_CreateObject();
    if (inline_response_200->_links) {
        cJSON *_links = cJSON_AddObjectToObject(item, "_links");
        if (_links == NULL) {
            goto fail;
        }
        cJSON *localMapObject = _links;
        ogs_sbi_lnode_t *_links_node;
        if (inline_response_200->_links) {
            ogs_sbi_list_for_each(_links_node, inline_response_200->_links) {
                ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)_links_node->data;
                cJSON *itemLocal = ogs_sbi_links_value_schema_convertToJSON(localKeyValue->value);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToObject(_links, localKeyValue->key, itemLocal);
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

ogs_sbi_inline_response_200_t *ogs_sbi_inline_response_200_parseFromJSON(cJSON *inline_response_200JSON)
{
    ogs_sbi_inline_response_200_t *inline_response_200_local_var = NULL;
    cJSON *_links = cJSON_GetObjectItemCaseSensitive(inline_response_200JSON, "_links");

    ogs_sbi_list_t *_linksList;
    if (_links) {
        cJSON *_links_local_map;
        if (!cJSON_IsObject(_links)) {
            goto end;
        }
        _linksList = ogs_sbi_list_create();
        ogs_sbi_map_t *localMapKeyPair = NULL;
        cJSON_ArrayForEach(_links_local_map, _links) {
            cJSON *localMapObject = _links_local_map;
            if (!cJSON_IsObject(_links_local_map)) {
                goto end;
            }
            localMapKeyPair = ogs_sbi_map_create(
                localMapObject->string, ogs_sbi_links_value_schema_parseFromJSON(localMapObject));
            ogs_sbi_list_add(_linksList, localMapKeyPair);
        }
    }

    inline_response_200_local_var = ogs_sbi_inline_response_200_create (
        _links ? _linksList : NULL
        );

    return inline_response_200_local_var;
end:
    return NULL;
}

