
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pdu_session_type.h"

ogs_sbi_pdu_session_type_t *ogs_sbi_pdu_session_type_create(
    )
{
    ogs_sbi_pdu_session_type_t *pdu_session_type_local_var = ogs_malloc(sizeof(ogs_sbi_pdu_session_type_t));
    if (!pdu_session_type_local_var) {
        return NULL;
    }

    return pdu_session_type_local_var;
}

void ogs_sbi_pdu_session_type_free(ogs_sbi_pdu_session_type_t *pdu_session_type)
{
    if (NULL == pdu_session_type) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(pdu_session_type);
}

cJSON *ogs_sbi_pdu_session_type_convertToJSON(ogs_sbi_pdu_session_type_t *pdu_session_type)
{
    cJSON *item = cJSON_CreateObject();
    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_pdu_session_type_t *ogs_sbi_pdu_session_type_parseFromJSON(cJSON *pdu_session_typeJSON)
{
    ogs_sbi_pdu_session_type_t *pdu_session_type_local_var = NULL;
    pdu_session_type_local_var = ogs_sbi_pdu_session_type_create (
        );

    return pdu_session_type_local_var;
end:
    return NULL;
}

