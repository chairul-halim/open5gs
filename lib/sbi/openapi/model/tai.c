
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tai.h"

ogs_sbi_tai_t *ogs_sbi_tai_create(
    ogs_sbi_plmn_id_t *plmn_id,
    char *tac
    )
{
    ogs_sbi_tai_t *tai_local_var = ogs_malloc(sizeof(ogs_sbi_tai_t));
    if (!tai_local_var) {
        return NULL;
    }
    tai_local_var->plmn_id = plmn_id;
    tai_local_var->tac = tac;

    return tai_local_var;
}

void ogs_sbi_tai_free(ogs_sbi_tai_t *tai)
{
    if (NULL == tai) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_sbi_plmn_id_free(tai->plmn_id);
    ogs_free(tai->tac);
    ogs_free(tai);
}

cJSON *ogs_sbi_tai_convertToJSON(ogs_sbi_tai_t *tai)
{
    cJSON *item = cJSON_CreateObject();
    if (!tai->plmn_id) {
        goto fail;
    }
    cJSON *plmn_id_local_JSON = ogs_sbi_plmn_id_convertToJSON(tai->plmn_id);
    if (plmn_id_local_JSON == NULL) {
        goto fail;
    }
    cJSON_AddItemToObject(item, "plmnId", plmn_id_local_JSON);
    if (item->child == NULL) {
        goto fail;
    }

    if (!tai->tac) {
        goto fail;
    }
    if (cJSON_AddStringToObject(item, "tac", tai->tac) == NULL) {
        goto fail;
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_tai_t *ogs_sbi_tai_parseFromJSON(cJSON *taiJSON)
{
    ogs_sbi_tai_t *tai_local_var = NULL;
    cJSON *plmn_id = cJSON_GetObjectItemCaseSensitive(taiJSON, "plmnId");
    if (!plmn_id) {
        goto end;
    }

    ogs_sbi_plmn_id_t *plmn_id_local_nonprim = NULL;

    plmn_id_local_nonprim = ogs_sbi_plmn_id_parseFromJSON(plmn_id);

    cJSON *tac = cJSON_GetObjectItemCaseSensitive(taiJSON, "tac");
    if (!tac) {
        goto end;
    }


    if (!cJSON_IsString(tac))
    {
        goto end;
    }

    tai_local_var = ogs_sbi_tai_create (
        plmn_id_local_nonprim,
        ogs_strdup(tac->valuestring)
        );

    return tai_local_var;
end:
    return NULL;
}

