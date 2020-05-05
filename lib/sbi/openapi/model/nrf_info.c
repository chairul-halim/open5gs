
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "nrf_info.h"

ogs_sbi_nrf_info_t *ogs_sbi_nrf_info_create(
    ogs_sbi_list_t* served_udr_info,
    ogs_sbi_list_t* served_udm_info,
    ogs_sbi_list_t* served_ausf_info,
    ogs_sbi_list_t* served_amf_info,
    ogs_sbi_list_t* served_smf_info,
    ogs_sbi_list_t* served_upf_info,
    ogs_sbi_list_t* served_pcf_info,
    ogs_sbi_list_t* served_bsf_info,
    ogs_sbi_list_t* served_chf_info,
    ogs_sbi_list_t* served_nwdaf_info
    )
{
    ogs_sbi_nrf_info_t *nrf_info_local_var = ogs_malloc(sizeof(ogs_sbi_nrf_info_t));
    if (!nrf_info_local_var) {
        return NULL;
    }
    nrf_info_local_var->served_udr_info = served_udr_info;
    nrf_info_local_var->served_udm_info = served_udm_info;
    nrf_info_local_var->served_ausf_info = served_ausf_info;
    nrf_info_local_var->served_amf_info = served_amf_info;
    nrf_info_local_var->served_smf_info = served_smf_info;
    nrf_info_local_var->served_upf_info = served_upf_info;
    nrf_info_local_var->served_pcf_info = served_pcf_info;
    nrf_info_local_var->served_bsf_info = served_bsf_info;
    nrf_info_local_var->served_chf_info = served_chf_info;
    nrf_info_local_var->served_nwdaf_info = served_nwdaf_info;

    return nrf_info_local_var;
}

void ogs_sbi_nrf_info_free(ogs_sbi_nrf_info_t *nrf_info)
{
    if (NULL == nrf_info) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_sbi_list_for_each(node, nrf_info->served_udr_info) {
        ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)node->data;
        ogs_sbi_udr_info_free(localKeyValue->value);
        ogs_free(localKeyValue);
    }
    ogs_sbi_list_free(nrf_info->served_udr_info);
    ogs_sbi_list_for_each(node, nrf_info->served_udm_info) {
        ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)node->data;
        ogs_sbi_udm_info_free(localKeyValue->value);
        ogs_free(localKeyValue);
    }
    ogs_sbi_list_free(nrf_info->served_udm_info);
    ogs_sbi_list_for_each(node, nrf_info->served_ausf_info) {
        ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)node->data;
        ogs_sbi_ausf_info_free(localKeyValue->value);
        ogs_free(localKeyValue);
    }
    ogs_sbi_list_free(nrf_info->served_ausf_info);
    ogs_sbi_list_for_each(node, nrf_info->served_amf_info) {
        ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)node->data;
        ogs_sbi_amf_info_free(localKeyValue->value);
        ogs_free(localKeyValue);
    }
    ogs_sbi_list_free(nrf_info->served_amf_info);
    ogs_sbi_list_for_each(node, nrf_info->served_smf_info) {
        ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)node->data;
        ogs_sbi_smf_info_free(localKeyValue->value);
        ogs_free(localKeyValue);
    }
    ogs_sbi_list_free(nrf_info->served_smf_info);
    ogs_sbi_list_for_each(node, nrf_info->served_upf_info) {
        ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)node->data;
        ogs_sbi_upf_info_free(localKeyValue->value);
        ogs_free(localKeyValue);
    }
    ogs_sbi_list_free(nrf_info->served_upf_info);
    ogs_sbi_list_for_each(node, nrf_info->served_pcf_info) {
        ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)node->data;
        ogs_sbi_pcf_info_free(localKeyValue->value);
        ogs_free(localKeyValue);
    }
    ogs_sbi_list_free(nrf_info->served_pcf_info);
    ogs_sbi_list_for_each(node, nrf_info->served_bsf_info) {
        ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)node->data;
        ogs_sbi_bsf_info_free(localKeyValue->value);
        ogs_free(localKeyValue);
    }
    ogs_sbi_list_free(nrf_info->served_bsf_info);
    ogs_sbi_list_for_each(node, nrf_info->served_chf_info) {
        ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)node->data;
        ogs_sbi_chf_info_free(localKeyValue->value);
        ogs_free(localKeyValue);
    }
    ogs_sbi_list_free(nrf_info->served_chf_info);
    ogs_sbi_list_for_each(node, nrf_info->served_nwdaf_info) {
        ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)node->data;
        ogs_sbi_nwdaf_info_free(localKeyValue->value);
        ogs_free(localKeyValue);
    }
    ogs_sbi_list_free(nrf_info->served_nwdaf_info);
    ogs_free(nrf_info);
}

cJSON *ogs_sbi_nrf_info_convertToJSON(ogs_sbi_nrf_info_t *nrf_info)
{
    cJSON *item = cJSON_CreateObject();
    if (nrf_info->served_udr_info) {
        cJSON *served_udr_info = cJSON_AddObjectToObject(item, "servedUdrInfo");
        if (served_udr_info == NULL) {
            goto fail;
        }
        cJSON *localMapObject = served_udr_info;
        ogs_sbi_lnode_t *served_udr_info_node;
        if (nrf_info->served_udr_info) {
            ogs_sbi_list_for_each(served_udr_info_node, nrf_info->served_udr_info) {
                ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)served_udr_info_node->data;
                cJSON *itemLocal = ogs_sbi_udr_info_convertToJSON(localKeyValue->value);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToObject(served_udr_info, localKeyValue->key, itemLocal);
            }
        }
    }

    if (nrf_info->served_udm_info) {
        cJSON *served_udm_info = cJSON_AddObjectToObject(item, "servedUdmInfo");
        if (served_udm_info == NULL) {
            goto fail;
        }
        cJSON *localMapObject = served_udm_info;
        ogs_sbi_lnode_t *served_udm_info_node;
        if (nrf_info->served_udm_info) {
            ogs_sbi_list_for_each(served_udm_info_node, nrf_info->served_udm_info) {
                ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)served_udm_info_node->data;
                cJSON *itemLocal = ogs_sbi_udm_info_convertToJSON(localKeyValue->value);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToObject(served_udm_info, localKeyValue->key, itemLocal);
            }
        }
    }

    if (nrf_info->served_ausf_info) {
        cJSON *served_ausf_info = cJSON_AddObjectToObject(item, "servedAusfInfo");
        if (served_ausf_info == NULL) {
            goto fail;
        }
        cJSON *localMapObject = served_ausf_info;
        ogs_sbi_lnode_t *served_ausf_info_node;
        if (nrf_info->served_ausf_info) {
            ogs_sbi_list_for_each(served_ausf_info_node, nrf_info->served_ausf_info) {
                ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)served_ausf_info_node->data;
                cJSON *itemLocal = ogs_sbi_ausf_info_convertToJSON(localKeyValue->value);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToObject(served_ausf_info, localKeyValue->key, itemLocal);
            }
        }
    }

    if (nrf_info->served_amf_info) {
        cJSON *served_amf_info = cJSON_AddObjectToObject(item, "servedAmfInfo");
        if (served_amf_info == NULL) {
            goto fail;
        }
        cJSON *localMapObject = served_amf_info;
        ogs_sbi_lnode_t *served_amf_info_node;
        if (nrf_info->served_amf_info) {
            ogs_sbi_list_for_each(served_amf_info_node, nrf_info->served_amf_info) {
                ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)served_amf_info_node->data;
                cJSON *itemLocal = ogs_sbi_amf_info_convertToJSON(localKeyValue->value);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToObject(served_amf_info, localKeyValue->key, itemLocal);
            }
        }
    }

    if (nrf_info->served_smf_info) {
        cJSON *served_smf_info = cJSON_AddObjectToObject(item, "servedSmfInfo");
        if (served_smf_info == NULL) {
            goto fail;
        }
        cJSON *localMapObject = served_smf_info;
        ogs_sbi_lnode_t *served_smf_info_node;
        if (nrf_info->served_smf_info) {
            ogs_sbi_list_for_each(served_smf_info_node, nrf_info->served_smf_info) {
                ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)served_smf_info_node->data;
                cJSON *itemLocal = ogs_sbi_smf_info_convertToJSON(localKeyValue->value);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToObject(served_smf_info, localKeyValue->key, itemLocal);
            }
        }
    }

    if (nrf_info->served_upf_info) {
        cJSON *served_upf_info = cJSON_AddObjectToObject(item, "servedUpfInfo");
        if (served_upf_info == NULL) {
            goto fail;
        }
        cJSON *localMapObject = served_upf_info;
        ogs_sbi_lnode_t *served_upf_info_node;
        if (nrf_info->served_upf_info) {
            ogs_sbi_list_for_each(served_upf_info_node, nrf_info->served_upf_info) {
                ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)served_upf_info_node->data;
                cJSON *itemLocal = ogs_sbi_upf_info_convertToJSON(localKeyValue->value);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToObject(served_upf_info, localKeyValue->key, itemLocal);
            }
        }
    }

    if (nrf_info->served_pcf_info) {
        cJSON *served_pcf_info = cJSON_AddObjectToObject(item, "servedPcfInfo");
        if (served_pcf_info == NULL) {
            goto fail;
        }
        cJSON *localMapObject = served_pcf_info;
        ogs_sbi_lnode_t *served_pcf_info_node;
        if (nrf_info->served_pcf_info) {
            ogs_sbi_list_for_each(served_pcf_info_node, nrf_info->served_pcf_info) {
                ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)served_pcf_info_node->data;
                cJSON *itemLocal = ogs_sbi_pcf_info_convertToJSON(localKeyValue->value);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToObject(served_pcf_info, localKeyValue->key, itemLocal);
            }
        }
    }

    if (nrf_info->served_bsf_info) {
        cJSON *served_bsf_info = cJSON_AddObjectToObject(item, "servedBsfInfo");
        if (served_bsf_info == NULL) {
            goto fail;
        }
        cJSON *localMapObject = served_bsf_info;
        ogs_sbi_lnode_t *served_bsf_info_node;
        if (nrf_info->served_bsf_info) {
            ogs_sbi_list_for_each(served_bsf_info_node, nrf_info->served_bsf_info) {
                ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)served_bsf_info_node->data;
                cJSON *itemLocal = ogs_sbi_bsf_info_convertToJSON(localKeyValue->value);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToObject(served_bsf_info, localKeyValue->key, itemLocal);
            }
        }
    }

    if (nrf_info->served_chf_info) {
        cJSON *served_chf_info = cJSON_AddObjectToObject(item, "servedChfInfo");
        if (served_chf_info == NULL) {
            goto fail;
        }
        cJSON *localMapObject = served_chf_info;
        ogs_sbi_lnode_t *served_chf_info_node;
        if (nrf_info->served_chf_info) {
            ogs_sbi_list_for_each(served_chf_info_node, nrf_info->served_chf_info) {
                ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)served_chf_info_node->data;
                cJSON *itemLocal = ogs_sbi_chf_info_convertToJSON(localKeyValue->value);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToObject(served_chf_info, localKeyValue->key, itemLocal);
            }
        }
    }

    if (nrf_info->served_nwdaf_info) {
        cJSON *served_nwdaf_info = cJSON_AddObjectToObject(item, "servedNwdafInfo");
        if (served_nwdaf_info == NULL) {
            goto fail;
        }
        cJSON *localMapObject = served_nwdaf_info;
        ogs_sbi_lnode_t *served_nwdaf_info_node;
        if (nrf_info->served_nwdaf_info) {
            ogs_sbi_list_for_each(served_nwdaf_info_node, nrf_info->served_nwdaf_info) {
                ogs_sbi_map_t *localKeyValue = (ogs_sbi_map_t*)served_nwdaf_info_node->data;
                cJSON *itemLocal = ogs_sbi_nwdaf_info_convertToJSON(localKeyValue->value);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToObject(served_nwdaf_info, localKeyValue->key, itemLocal);
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

ogs_sbi_nrf_info_t *ogs_sbi_nrf_info_parseFromJSON(cJSON *nrf_infoJSON)
{
    ogs_sbi_nrf_info_t *nrf_info_local_var = NULL;
    cJSON *served_udr_info = cJSON_GetObjectItemCaseSensitive(nrf_infoJSON, "servedUdrInfo");

    ogs_sbi_list_t *served_udr_infoList;
    if (served_udr_info) {
        cJSON *served_udr_info_local_map;
        if (!cJSON_IsObject(served_udr_info)) {
            goto end;
        }
        served_udr_infoList = ogs_sbi_list_create();
        ogs_sbi_map_t *localMapKeyPair = NULL;
        cJSON_ArrayForEach(served_udr_info_local_map, served_udr_info) {
            cJSON *localMapObject = served_udr_info_local_map;
            if (!cJSON_IsObject(served_udr_info_local_map)) {
                goto end;
            }
            localMapKeyPair = ogs_sbi_map_create(
                localMapObject->string, ogs_sbi_udr_info_parseFromJSON(localMapObject));
            ogs_sbi_list_add(served_udr_infoList, localMapKeyPair);
        }
    }

    cJSON *served_udm_info = cJSON_GetObjectItemCaseSensitive(nrf_infoJSON, "servedUdmInfo");

    ogs_sbi_list_t *served_udm_infoList;
    if (served_udm_info) {
        cJSON *served_udm_info_local_map;
        if (!cJSON_IsObject(served_udm_info)) {
            goto end;
        }
        served_udm_infoList = ogs_sbi_list_create();
        ogs_sbi_map_t *localMapKeyPair = NULL;
        cJSON_ArrayForEach(served_udm_info_local_map, served_udm_info) {
            cJSON *localMapObject = served_udm_info_local_map;
            if (!cJSON_IsObject(served_udm_info_local_map)) {
                goto end;
            }
            localMapKeyPair = ogs_sbi_map_create(
                localMapObject->string, ogs_sbi_udm_info_parseFromJSON(localMapObject));
            ogs_sbi_list_add(served_udm_infoList, localMapKeyPair);
        }
    }

    cJSON *served_ausf_info = cJSON_GetObjectItemCaseSensitive(nrf_infoJSON, "servedAusfInfo");

    ogs_sbi_list_t *served_ausf_infoList;
    if (served_ausf_info) {
        cJSON *served_ausf_info_local_map;
        if (!cJSON_IsObject(served_ausf_info)) {
            goto end;
        }
        served_ausf_infoList = ogs_sbi_list_create();
        ogs_sbi_map_t *localMapKeyPair = NULL;
        cJSON_ArrayForEach(served_ausf_info_local_map, served_ausf_info) {
            cJSON *localMapObject = served_ausf_info_local_map;
            if (!cJSON_IsObject(served_ausf_info_local_map)) {
                goto end;
            }
            localMapKeyPair = ogs_sbi_map_create(
                localMapObject->string, ogs_sbi_ausf_info_parseFromJSON(localMapObject));
            ogs_sbi_list_add(served_ausf_infoList, localMapKeyPair);
        }
    }

    cJSON *served_amf_info = cJSON_GetObjectItemCaseSensitive(nrf_infoJSON, "servedAmfInfo");

    ogs_sbi_list_t *served_amf_infoList;
    if (served_amf_info) {
        cJSON *served_amf_info_local_map;
        if (!cJSON_IsObject(served_amf_info)) {
            goto end;
        }
        served_amf_infoList = ogs_sbi_list_create();
        ogs_sbi_map_t *localMapKeyPair = NULL;
        cJSON_ArrayForEach(served_amf_info_local_map, served_amf_info) {
            cJSON *localMapObject = served_amf_info_local_map;
            if (!cJSON_IsObject(served_amf_info_local_map)) {
                goto end;
            }
            localMapKeyPair = ogs_sbi_map_create(
                localMapObject->string, ogs_sbi_amf_info_parseFromJSON(localMapObject));
            ogs_sbi_list_add(served_amf_infoList, localMapKeyPair);
        }
    }

    cJSON *served_smf_info = cJSON_GetObjectItemCaseSensitive(nrf_infoJSON, "servedSmfInfo");

    ogs_sbi_list_t *served_smf_infoList;
    if (served_smf_info) {
        cJSON *served_smf_info_local_map;
        if (!cJSON_IsObject(served_smf_info)) {
            goto end;
        }
        served_smf_infoList = ogs_sbi_list_create();
        ogs_sbi_map_t *localMapKeyPair = NULL;
        cJSON_ArrayForEach(served_smf_info_local_map, served_smf_info) {
            cJSON *localMapObject = served_smf_info_local_map;
            if (!cJSON_IsObject(served_smf_info_local_map)) {
                goto end;
            }
            localMapKeyPair = ogs_sbi_map_create(
                localMapObject->string, ogs_sbi_smf_info_parseFromJSON(localMapObject));
            ogs_sbi_list_add(served_smf_infoList, localMapKeyPair);
        }
    }

    cJSON *served_upf_info = cJSON_GetObjectItemCaseSensitive(nrf_infoJSON, "servedUpfInfo");

    ogs_sbi_list_t *served_upf_infoList;
    if (served_upf_info) {
        cJSON *served_upf_info_local_map;
        if (!cJSON_IsObject(served_upf_info)) {
            goto end;
        }
        served_upf_infoList = ogs_sbi_list_create();
        ogs_sbi_map_t *localMapKeyPair = NULL;
        cJSON_ArrayForEach(served_upf_info_local_map, served_upf_info) {
            cJSON *localMapObject = served_upf_info_local_map;
            if (!cJSON_IsObject(served_upf_info_local_map)) {
                goto end;
            }
            localMapKeyPair = ogs_sbi_map_create(
                localMapObject->string, ogs_sbi_upf_info_parseFromJSON(localMapObject));
            ogs_sbi_list_add(served_upf_infoList, localMapKeyPair);
        }
    }

    cJSON *served_pcf_info = cJSON_GetObjectItemCaseSensitive(nrf_infoJSON, "servedPcfInfo");

    ogs_sbi_list_t *served_pcf_infoList;
    if (served_pcf_info) {
        cJSON *served_pcf_info_local_map;
        if (!cJSON_IsObject(served_pcf_info)) {
            goto end;
        }
        served_pcf_infoList = ogs_sbi_list_create();
        ogs_sbi_map_t *localMapKeyPair = NULL;
        cJSON_ArrayForEach(served_pcf_info_local_map, served_pcf_info) {
            cJSON *localMapObject = served_pcf_info_local_map;
            if (!cJSON_IsObject(served_pcf_info_local_map)) {
                goto end;
            }
            localMapKeyPair = ogs_sbi_map_create(
                localMapObject->string, ogs_sbi_pcf_info_parseFromJSON(localMapObject));
            ogs_sbi_list_add(served_pcf_infoList, localMapKeyPair);
        }
    }

    cJSON *served_bsf_info = cJSON_GetObjectItemCaseSensitive(nrf_infoJSON, "servedBsfInfo");

    ogs_sbi_list_t *served_bsf_infoList;
    if (served_bsf_info) {
        cJSON *served_bsf_info_local_map;
        if (!cJSON_IsObject(served_bsf_info)) {
            goto end;
        }
        served_bsf_infoList = ogs_sbi_list_create();
        ogs_sbi_map_t *localMapKeyPair = NULL;
        cJSON_ArrayForEach(served_bsf_info_local_map, served_bsf_info) {
            cJSON *localMapObject = served_bsf_info_local_map;
            if (!cJSON_IsObject(served_bsf_info_local_map)) {
                goto end;
            }
            localMapKeyPair = ogs_sbi_map_create(
                localMapObject->string, ogs_sbi_bsf_info_parseFromJSON(localMapObject));
            ogs_sbi_list_add(served_bsf_infoList, localMapKeyPair);
        }
    }

    cJSON *served_chf_info = cJSON_GetObjectItemCaseSensitive(nrf_infoJSON, "servedChfInfo");

    ogs_sbi_list_t *served_chf_infoList;
    if (served_chf_info) {
        cJSON *served_chf_info_local_map;
        if (!cJSON_IsObject(served_chf_info)) {
            goto end;
        }
        served_chf_infoList = ogs_sbi_list_create();
        ogs_sbi_map_t *localMapKeyPair = NULL;
        cJSON_ArrayForEach(served_chf_info_local_map, served_chf_info) {
            cJSON *localMapObject = served_chf_info_local_map;
            if (!cJSON_IsObject(served_chf_info_local_map)) {
                goto end;
            }
            localMapKeyPair = ogs_sbi_map_create(
                localMapObject->string, ogs_sbi_chf_info_parseFromJSON(localMapObject));
            ogs_sbi_list_add(served_chf_infoList, localMapKeyPair);
        }
    }

    cJSON *served_nwdaf_info = cJSON_GetObjectItemCaseSensitive(nrf_infoJSON, "servedNwdafInfo");

    ogs_sbi_list_t *served_nwdaf_infoList;
    if (served_nwdaf_info) {
        cJSON *served_nwdaf_info_local_map;
        if (!cJSON_IsObject(served_nwdaf_info)) {
            goto end;
        }
        served_nwdaf_infoList = ogs_sbi_list_create();
        ogs_sbi_map_t *localMapKeyPair = NULL;
        cJSON_ArrayForEach(served_nwdaf_info_local_map, served_nwdaf_info) {
            cJSON *localMapObject = served_nwdaf_info_local_map;
            if (!cJSON_IsObject(served_nwdaf_info_local_map)) {
                goto end;
            }
            localMapKeyPair = ogs_sbi_map_create(
                localMapObject->string, ogs_sbi_nwdaf_info_parseFromJSON(localMapObject));
            ogs_sbi_list_add(served_nwdaf_infoList, localMapKeyPair);
        }
    }

    nrf_info_local_var = ogs_sbi_nrf_info_create (
        served_udr_info ? served_udr_infoList : NULL,
        served_udm_info ? served_udm_infoList : NULL,
        served_ausf_info ? served_ausf_infoList : NULL,
        served_amf_info ? served_amf_infoList : NULL,
        served_smf_info ? served_smf_infoList : NULL,
        served_upf_info ? served_upf_infoList : NULL,
        served_pcf_info ? served_pcf_infoList : NULL,
        served_bsf_info ? served_bsf_infoList : NULL,
        served_chf_info ? served_chf_infoList : NULL,
        served_nwdaf_info ? served_nwdaf_infoList : NULL
        );

    return nrf_info_local_var;
end:
    return NULL;
}

