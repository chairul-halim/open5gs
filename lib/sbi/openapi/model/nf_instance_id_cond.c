
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "nf_instance_id_cond.h"

ogs_sbi_nf_instance_id_cond_t *ogs_sbi_nf_instance_id_cond_create(
    char *nf_instance_id
    )
{
    ogs_sbi_nf_instance_id_cond_t *nf_instance_id_cond_local_var = ogs_malloc(sizeof(ogs_sbi_nf_instance_id_cond_t));
    if (!nf_instance_id_cond_local_var) {
        return NULL;
    }
    nf_instance_id_cond_local_var->nf_instance_id = nf_instance_id;

    return nf_instance_id_cond_local_var;
}

void ogs_sbi_nf_instance_id_cond_free(ogs_sbi_nf_instance_id_cond_t *nf_instance_id_cond)
{
    if (NULL == nf_instance_id_cond) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(nf_instance_id_cond->nf_instance_id);
    ogs_free(nf_instance_id_cond);
}

cJSON *ogs_sbi_nf_instance_id_cond_convertToJSON(ogs_sbi_nf_instance_id_cond_t *nf_instance_id_cond)
{
    cJSON *item = cJSON_CreateObject();
    if (!nf_instance_id_cond->nf_instance_id) {
        goto fail;
    }
    if (cJSON_AddStringToObject(item, "nfInstanceId", nf_instance_id_cond->nf_instance_id) == NULL) {
        goto fail;
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_nf_instance_id_cond_t *ogs_sbi_nf_instance_id_cond_parseFromJSON(cJSON *nf_instance_id_condJSON)
{
    ogs_sbi_nf_instance_id_cond_t *nf_instance_id_cond_local_var = NULL;
    cJSON *nf_instance_id = cJSON_GetObjectItemCaseSensitive(nf_instance_id_condJSON, "nfInstanceId");
    if (!nf_instance_id) {
        goto end;
    }


    if (!cJSON_IsString(nf_instance_id))
    {
        goto end;
    }

    nf_instance_id_cond_local_var = ogs_sbi_nf_instance_id_cond_create (
        ogs_strdup(nf_instance_id->valuestring)
        );

    return nf_instance_id_cond_local_var;
end:
    return NULL;
}

