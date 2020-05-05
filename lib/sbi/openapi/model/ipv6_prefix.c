
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ipv6_prefix.h"

ogs_sbi_ipv6_prefix_t *ogs_sbi_ipv6_prefix_create(
    )
{
    ogs_sbi_ipv6_prefix_t *ipv6_prefix_local_var = ogs_malloc(sizeof(ogs_sbi_ipv6_prefix_t));
    if (!ipv6_prefix_local_var) {
        return NULL;
    }

    return ipv6_prefix_local_var;
}

void ogs_sbi_ipv6_prefix_free(ogs_sbi_ipv6_prefix_t *ipv6_prefix)
{
    if (NULL == ipv6_prefix) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(ipv6_prefix);
}

cJSON *ogs_sbi_ipv6_prefix_convertToJSON(ogs_sbi_ipv6_prefix_t *ipv6_prefix)
{
    cJSON *item = cJSON_CreateObject();
    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_ipv6_prefix_t *ogs_sbi_ipv6_prefix_parseFromJSON(cJSON *ipv6_prefixJSON)
{
    ogs_sbi_ipv6_prefix_t *ipv6_prefix_local_var = NULL;
    ipv6_prefix_local_var = ogs_sbi_ipv6_prefix_create (
        );

    return ipv6_prefix_local_var;
end:
    return NULL;
}

