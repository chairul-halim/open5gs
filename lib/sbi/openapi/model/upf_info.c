
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "upf_info.h"

ogs_sbi_upf_info_t *ogs_sbi_upf_info_create(
    ogs_sbi_list_t *s_nssai_upf_info_list,
    ogs_sbi_list_t *smf_serving_area,
    ogs_sbi_list_t *interface_upf_info_list,
    int iwk_eps_ind,
    ogs_sbi_list_t *pdu_session_types,
    ogs_sbi_atsss_capability_t *atsss_capability,
    int ue_ip_addr_ind
    )
{
    ogs_sbi_upf_info_t *upf_info_local_var = ogs_malloc(sizeof(ogs_sbi_upf_info_t));
    if (!upf_info_local_var) {
        return NULL;
    }
    upf_info_local_var->s_nssai_upf_info_list = s_nssai_upf_info_list;
    upf_info_local_var->smf_serving_area = smf_serving_area;
    upf_info_local_var->interface_upf_info_list = interface_upf_info_list;
    upf_info_local_var->iwk_eps_ind = iwk_eps_ind;
    upf_info_local_var->pdu_session_types = pdu_session_types;
    upf_info_local_var->atsss_capability = atsss_capability;
    upf_info_local_var->ue_ip_addr_ind = ue_ip_addr_ind;

    return upf_info_local_var;
}

void ogs_sbi_upf_info_free(ogs_sbi_upf_info_t *upf_info)
{
    if (NULL == upf_info) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_sbi_list_for_each(node, upf_info->s_nssai_upf_info_list) {
        ogs_sbi_snssai_upf_info_item_free(node->data);
    }
    ogs_sbi_list_free(upf_info->s_nssai_upf_info_list);
    ogs_sbi_list_for_each(node, upf_info->smf_serving_area) {
        ogs_free(node->data);
    }
    ogs_sbi_list_free(upf_info->smf_serving_area);
    ogs_sbi_list_for_each(node, upf_info->interface_upf_info_list) {
        ogs_sbi_interface_upf_info_item_free(node->data);
    }
    ogs_sbi_list_free(upf_info->interface_upf_info_list);
    ogs_sbi_list_for_each(node, upf_info->pdu_session_types) {
        ogs_sbi_pdu_session_type_free(node->data);
    }
    ogs_sbi_list_free(upf_info->pdu_session_types);
    ogs_sbi_atsss_capability_free(upf_info->atsss_capability);
    ogs_free(upf_info);
}

cJSON *ogs_sbi_upf_info_convertToJSON(ogs_sbi_upf_info_t *upf_info)
{
    cJSON *item = cJSON_CreateObject();
    if (!upf_info->s_nssai_upf_info_list) {
        goto fail;
    }
    cJSON *s_nssai_upf_info_list = cJSON_AddArrayToObject(item, "sNssaiUpfInfoList");
    if (s_nssai_upf_info_list == NULL) {
        goto fail;
    }

    ogs_sbi_lnode_t *s_nssai_upf_info_list_node;
    if (upf_info->s_nssai_upf_info_list) {
        ogs_sbi_list_for_each(s_nssai_upf_info_list_node, upf_info->s_nssai_upf_info_list) {
            cJSON *itemLocal = ogs_sbi_snssai_upf_info_item_convertToJSON(s_nssai_upf_info_list_node->data);
            if (itemLocal == NULL) {
                goto fail;
            }
            cJSON_AddItemToArray(s_nssai_upf_info_list, itemLocal);
        }
    }

    if (upf_info->smf_serving_area) {
        cJSON *smf_serving_area = cJSON_AddArrayToObject(item, "smfServingArea");
        if (smf_serving_area == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *smf_serving_area_node;
        ogs_sbi_list_for_each(smf_serving_area_node, upf_info->smf_serving_area) {
            if (cJSON_AddStringToObject(smf_serving_area, "", (char*)smf_serving_area_node->data) == NULL) {
                goto fail;
            }
        }
    }

    if (upf_info->interface_upf_info_list) {
        cJSON *interface_upf_info_list = cJSON_AddArrayToObject(item, "interfaceUpfInfoList");
        if (interface_upf_info_list == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *interface_upf_info_list_node;
        if (upf_info->interface_upf_info_list) {
            ogs_sbi_list_for_each(interface_upf_info_list_node, upf_info->interface_upf_info_list) {
                cJSON *itemLocal = ogs_sbi_interface_upf_info_item_convertToJSON(interface_upf_info_list_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(interface_upf_info_list, itemLocal);
            }
        }
    }

    if (upf_info->iwk_eps_ind) {
        if (cJSON_AddBoolToObject(item, "iwkEpsInd", upf_info->iwk_eps_ind) == NULL) {
            goto fail;
        }
    }

    if (upf_info->pdu_session_types) {
        cJSON *pdu_session_types = cJSON_AddArrayToObject(item, "pduSessionTypes");
        if (pdu_session_types == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *pdu_session_types_node;
        if (upf_info->pdu_session_types) {
            ogs_sbi_list_for_each(pdu_session_types_node, upf_info->pdu_session_types) {
                cJSON *itemLocal = ogs_sbi_pdu_session_type_convertToJSON(pdu_session_types_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(pdu_session_types, itemLocal);
            }
        }
    }

    if (upf_info->atsss_capability) {
        cJSON *atsss_capability_local_JSON = ogs_sbi_atsss_capability_convertToJSON(upf_info->atsss_capability);
        if (atsss_capability_local_JSON == NULL) {
            goto fail;
        }
        cJSON_AddItemToObject(item, "atsssCapability", atsss_capability_local_JSON);
        if (item->child == NULL) {
            goto fail;
        }
    }

    if (upf_info->ue_ip_addr_ind) {
        if (cJSON_AddBoolToObject(item, "ueIpAddrInd", upf_info->ue_ip_addr_ind) == NULL) {
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

ogs_sbi_upf_info_t *ogs_sbi_upf_info_parseFromJSON(cJSON *upf_infoJSON)
{
    ogs_sbi_upf_info_t *upf_info_local_var = NULL;
    cJSON *s_nssai_upf_info_list = cJSON_GetObjectItemCaseSensitive(upf_infoJSON, "sNssaiUpfInfoList");
    if (!s_nssai_upf_info_list) {
        goto end;
    }

    ogs_sbi_list_t *s_nssai_upf_info_listList;

    cJSON *s_nssai_upf_info_list_local_nonprimitive;
    if (!cJSON_IsArray(s_nssai_upf_info_list)) {
        goto end;
    }

    s_nssai_upf_info_listList = ogs_sbi_list_create();

    cJSON_ArrayForEach(s_nssai_upf_info_list_local_nonprimitive,s_nssai_upf_info_list ) {
        if (!cJSON_IsObject(s_nssai_upf_info_list_local_nonprimitive)) {
            goto end;
        }
        ogs_sbi_snssai_upf_info_item_t *s_nssai_upf_info_listItem = ogs_sbi_snssai_upf_info_item_parseFromJSON(s_nssai_upf_info_list_local_nonprimitive);

        ogs_sbi_list_add(s_nssai_upf_info_listList, s_nssai_upf_info_listItem);
    }

    cJSON *smf_serving_area = cJSON_GetObjectItemCaseSensitive(upf_infoJSON, "smfServingArea");

    ogs_sbi_list_t *smf_serving_areaList;
    if (smf_serving_area) {
        cJSON *smf_serving_area_local;
        if (!cJSON_IsArray(smf_serving_area)) {
            goto end;
        }
        smf_serving_areaList = ogs_sbi_list_create();

        cJSON_ArrayForEach(smf_serving_area_local, smf_serving_area) {
            if (!cJSON_IsString(smf_serving_area_local)) {
                goto end;
            }
            ogs_sbi_list_add(smf_serving_areaList, ogs_strdup(smf_serving_area_local->valuestring));
        }
    }

    cJSON *interface_upf_info_list = cJSON_GetObjectItemCaseSensitive(upf_infoJSON, "interfaceUpfInfoList");

    ogs_sbi_list_t *interface_upf_info_listList;
    if (interface_upf_info_list) {
        cJSON *interface_upf_info_list_local_nonprimitive;
        if (!cJSON_IsArray(interface_upf_info_list)) {
            goto end;
        }

        interface_upf_info_listList = ogs_sbi_list_create();

        cJSON_ArrayForEach(interface_upf_info_list_local_nonprimitive,interface_upf_info_list ) {
            if (!cJSON_IsObject(interface_upf_info_list_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_interface_upf_info_item_t *interface_upf_info_listItem = ogs_sbi_interface_upf_info_item_parseFromJSON(interface_upf_info_list_local_nonprimitive);

            ogs_sbi_list_add(interface_upf_info_listList, interface_upf_info_listItem);
        }
    }

    cJSON *iwk_eps_ind = cJSON_GetObjectItemCaseSensitive(upf_infoJSON, "iwkEpsInd");

    if (iwk_eps_ind) {
        if (!cJSON_IsBool(iwk_eps_ind)) {
            goto end;
        }
    }

    cJSON *pdu_session_types = cJSON_GetObjectItemCaseSensitive(upf_infoJSON, "pduSessionTypes");

    ogs_sbi_list_t *pdu_session_typesList;
    if (pdu_session_types) {
        cJSON *pdu_session_types_local_nonprimitive;
        if (!cJSON_IsArray(pdu_session_types)) {
            goto end;
        }

        pdu_session_typesList = ogs_sbi_list_create();

        cJSON_ArrayForEach(pdu_session_types_local_nonprimitive,pdu_session_types ) {
            if (!cJSON_IsObject(pdu_session_types_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_pdu_session_type_t *pdu_session_typesItem = ogs_sbi_pdu_session_type_parseFromJSON(pdu_session_types_local_nonprimitive);

            ogs_sbi_list_add(pdu_session_typesList, pdu_session_typesItem);
        }
    }

    cJSON *atsss_capability = cJSON_GetObjectItemCaseSensitive(upf_infoJSON, "atsssCapability");

    ogs_sbi_atsss_capability_t *atsss_capability_local_nonprim = NULL;
    if (atsss_capability) {
        atsss_capability_local_nonprim = ogs_sbi_atsss_capability_parseFromJSON(atsss_capability);
    }

    cJSON *ue_ip_addr_ind = cJSON_GetObjectItemCaseSensitive(upf_infoJSON, "ueIpAddrInd");

    if (ue_ip_addr_ind) {
        if (!cJSON_IsBool(ue_ip_addr_ind)) {
            goto end;
        }
    }

    upf_info_local_var = ogs_sbi_upf_info_create (
        s_nssai_upf_info_listList,
        smf_serving_area ? smf_serving_areaList : NULL,
        interface_upf_info_list ? interface_upf_info_listList : NULL,
        iwk_eps_ind ? iwk_eps_ind->valueint : 0,
        pdu_session_types ? pdu_session_typesList : NULL,
        atsss_capability ? atsss_capability_local_nonprim : NULL,
        ue_ip_addr_ind ? ue_ip_addr_ind->valueint : 0
        );

    return upf_info_local_var;
end:
    return NULL;
}

