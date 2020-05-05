
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "atsss_capability.h"

ogs_sbi_atsss_capability_t *ogs_sbi_atsss_capability_create(
    int atsss_ll,
    int mptcp
    )
{
    ogs_sbi_atsss_capability_t *atsss_capability_local_var = ogs_malloc(sizeof(ogs_sbi_atsss_capability_t));
    if (!atsss_capability_local_var) {
        return NULL;
    }
    atsss_capability_local_var->atsss_ll = atsss_ll;
    atsss_capability_local_var->mptcp = mptcp;

    return atsss_capability_local_var;
}

void ogs_sbi_atsss_capability_free(ogs_sbi_atsss_capability_t *atsss_capability)
{
    if (NULL == atsss_capability) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(atsss_capability);
}

cJSON *ogs_sbi_atsss_capability_convertToJSON(ogs_sbi_atsss_capability_t *atsss_capability)
{
    cJSON *item = cJSON_CreateObject();
    if (atsss_capability->atsss_ll) {
        if (cJSON_AddBoolToObject(item, "atsssLL", atsss_capability->atsss_ll) == NULL) {
            goto fail;
        }
    }

    if (atsss_capability->mptcp) {
        if (cJSON_AddBoolToObject(item, "mptcp", atsss_capability->mptcp) == NULL) {
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

ogs_sbi_atsss_capability_t *ogs_sbi_atsss_capability_parseFromJSON(cJSON *atsss_capabilityJSON)
{
    ogs_sbi_atsss_capability_t *atsss_capability_local_var = NULL;
    cJSON *atsss_ll = cJSON_GetObjectItemCaseSensitive(atsss_capabilityJSON, "atsssLL");

    if (atsss_ll) {
        if (!cJSON_IsBool(atsss_ll)) {
            goto end;
        }
    }

    cJSON *mptcp = cJSON_GetObjectItemCaseSensitive(atsss_capabilityJSON, "mptcp");

    if (mptcp) {
        if (!cJSON_IsBool(mptcp)) {
            goto end;
        }
    }

    atsss_capability_local_var = ogs_sbi_atsss_capability_create (
        atsss_ll ? atsss_ll->valueint : 0,
        mptcp ? mptcp->valueint : 0
        );

    return atsss_capability_local_var;
end:
    return NULL;
}

