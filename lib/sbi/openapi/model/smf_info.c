
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "smf_info.h"

ogs_sbi_smf_info_t *ogs_sbi_smf_info_create(
    ogs_sbi_list_t *s_nssai_smf_info_list,
    ogs_sbi_list_t *tai_list,
    ogs_sbi_list_t *tai_range_list,
    char *pgw_fqdn,
    ogs_sbi_list_t *access_type
    )
{
    ogs_sbi_smf_info_t *smf_info_local_var = ogs_malloc(sizeof(ogs_sbi_smf_info_t));
    if (!smf_info_local_var) {
        return NULL;
    }
    smf_info_local_var->s_nssai_smf_info_list = s_nssai_smf_info_list;
    smf_info_local_var->tai_list = tai_list;
    smf_info_local_var->tai_range_list = tai_range_list;
    smf_info_local_var->pgw_fqdn = pgw_fqdn;
    smf_info_local_var->access_type = access_type;

    return smf_info_local_var;
}

void ogs_sbi_smf_info_free(ogs_sbi_smf_info_t *smf_info)
{
    if (NULL == smf_info) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_sbi_list_for_each(node, smf_info->s_nssai_smf_info_list) {
        ogs_sbi_snssai_smf_info_item_free(node->data);
    }
    ogs_sbi_list_free(smf_info->s_nssai_smf_info_list);
    ogs_sbi_list_for_each(node, smf_info->tai_list) {
        ogs_sbi_tai_free(node->data);
    }
    ogs_sbi_list_free(smf_info->tai_list);
    ogs_sbi_list_for_each(node, smf_info->tai_range_list) {
        ogs_sbi_tai_range_free(node->data);
    }
    ogs_sbi_list_free(smf_info->tai_range_list);
    ogs_free(smf_info->pgw_fqdn);
    ogs_sbi_list_free(smf_info->access_type);
    ogs_free(smf_info);
}

cJSON *ogs_sbi_smf_info_convertToJSON(ogs_sbi_smf_info_t *smf_info)
{
    cJSON *item = cJSON_CreateObject();
    if (!smf_info->s_nssai_smf_info_list) {
        goto fail;
    }
    cJSON *s_nssai_smf_info_list = cJSON_AddArrayToObject(item, "sNssaiSmfInfoList");
    if (s_nssai_smf_info_list == NULL) {
        goto fail;
    }

    ogs_sbi_lnode_t *s_nssai_smf_info_list_node;
    if (smf_info->s_nssai_smf_info_list) {
        ogs_sbi_list_for_each(s_nssai_smf_info_list_node, smf_info->s_nssai_smf_info_list) {
            cJSON *itemLocal = ogs_sbi_snssai_smf_info_item_convertToJSON(s_nssai_smf_info_list_node->data);
            if (itemLocal == NULL) {
                goto fail;
            }
            cJSON_AddItemToArray(s_nssai_smf_info_list, itemLocal);
        }
    }

    if (smf_info->tai_list) {
        cJSON *tai_list = cJSON_AddArrayToObject(item, "taiList");
        if (tai_list == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *tai_list_node;
        if (smf_info->tai_list) {
            ogs_sbi_list_for_each(tai_list_node, smf_info->tai_list) {
                cJSON *itemLocal = ogs_sbi_tai_convertToJSON(tai_list_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(tai_list, itemLocal);
            }
        }
    }

    if (smf_info->tai_range_list) {
        cJSON *tai_range_list = cJSON_AddArrayToObject(item, "taiRangeList");
        if (tai_range_list == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *tai_range_list_node;
        if (smf_info->tai_range_list) {
            ogs_sbi_list_for_each(tai_range_list_node, smf_info->tai_range_list) {
                cJSON *itemLocal = ogs_sbi_tai_range_convertToJSON(tai_range_list_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(tai_range_list, itemLocal);
            }
        }
    }

    if (smf_info->pgw_fqdn) {
        if (cJSON_AddStringToObject(item, "pgwFqdn", smf_info->pgw_fqdn) == NULL) {
            goto fail;
        }
    }

    if (smf_info->access_type) {
        cJSON *access_type = cJSON_AddArrayToObject(item, "accessType");
        if (access_type == NULL) {
            goto fail;
        }
        ogs_sbi_lnode_t *access_type_node;
        ogs_sbi_list_for_each(access_type_node, smf_info->access_type) {
            if (cJSON_AddStringToObject(access_type, "", ogs_sbi_access_type_ToString((ogs_sbi_access_type_e)access_type_node->data)) == NULL) {
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

ogs_sbi_smf_info_t *ogs_sbi_smf_info_parseFromJSON(cJSON *smf_infoJSON)
{
    ogs_sbi_smf_info_t *smf_info_local_var = NULL;
    cJSON *s_nssai_smf_info_list = cJSON_GetObjectItemCaseSensitive(smf_infoJSON, "sNssaiSmfInfoList");
    if (!s_nssai_smf_info_list) {
        goto end;
    }

    ogs_sbi_list_t *s_nssai_smf_info_listList;

    cJSON *s_nssai_smf_info_list_local_nonprimitive;
    if (!cJSON_IsArray(s_nssai_smf_info_list)) {
        goto end;
    }

    s_nssai_smf_info_listList = ogs_sbi_list_create();

    cJSON_ArrayForEach(s_nssai_smf_info_list_local_nonprimitive,s_nssai_smf_info_list ) {
        if (!cJSON_IsObject(s_nssai_smf_info_list_local_nonprimitive)) {
            goto end;
        }
        ogs_sbi_snssai_smf_info_item_t *s_nssai_smf_info_listItem = ogs_sbi_snssai_smf_info_item_parseFromJSON(s_nssai_smf_info_list_local_nonprimitive);

        ogs_sbi_list_add(s_nssai_smf_info_listList, s_nssai_smf_info_listItem);
    }

    cJSON *tai_list = cJSON_GetObjectItemCaseSensitive(smf_infoJSON, "taiList");

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

    cJSON *tai_range_list = cJSON_GetObjectItemCaseSensitive(smf_infoJSON, "taiRangeList");

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

    cJSON *pgw_fqdn = cJSON_GetObjectItemCaseSensitive(smf_infoJSON, "pgwFqdn");

    if (pgw_fqdn) {
        if (!cJSON_IsString(pgw_fqdn))
        {
            goto end;
        }
    }

    cJSON *access_type = cJSON_GetObjectItemCaseSensitive(smf_infoJSON, "accessType");

    ogs_sbi_list_t *access_typeList;
    if (access_type) {
        cJSON *access_type_local_nonprimitive;
        if (!cJSON_IsArray(access_type)) {
            goto end;
        }

        access_typeList = ogs_sbi_list_create();

        cJSON_ArrayForEach(access_type_local_nonprimitive, access_type ) {
            if (!cJSON_IsString(access_type_local_nonprimitive)) {
                goto end;
            }

            ogs_sbi_list_add(access_typeList, (void *)ogs_sbi_access_type_FromString(access_type_local_nonprimitive->valuestring));
        }
    }

    smf_info_local_var = ogs_sbi_smf_info_create (
        s_nssai_smf_info_listList,
        tai_list ? tai_listList : NULL,
        tai_range_list ? tai_range_listList : NULL,
        pgw_fqdn ? ogs_strdup(pgw_fqdn->valuestring) : NULL,
        access_type ? access_typeList : NULL
        );

    return smf_info_local_var;
end:
    return NULL;
}

