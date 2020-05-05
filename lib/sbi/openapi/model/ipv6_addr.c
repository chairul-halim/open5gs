
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ipv6_addr.h"

ogs_sbi_ipv6_addr_t *ogs_sbi_ipv6_addr_create(
    )
{
    ogs_sbi_ipv6_addr_t *ipv6_addr_local_var = ogs_malloc(sizeof(ogs_sbi_ipv6_addr_t));
    if (!ipv6_addr_local_var) {
        return NULL;
    }

    return ipv6_addr_local_var;
}

void ogs_sbi_ipv6_addr_free(ogs_sbi_ipv6_addr_t *ipv6_addr)
{
    if (NULL == ipv6_addr) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(ipv6_addr);
}

cJSON *ogs_sbi_ipv6_addr_convertToJSON(ogs_sbi_ipv6_addr_t *ipv6_addr)
{
    cJSON *item = cJSON_CreateObject();
    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_ipv6_addr_t *ogs_sbi_ipv6_addr_parseFromJSON(cJSON *ipv6_addrJSON)
{
    ogs_sbi_ipv6_addr_t *ipv6_addr_local_var = NULL;
    ipv6_addr_local_var = ogs_sbi_ipv6_addr_create (
        );

    return ipv6_addr_local_var;
end:
    return NULL;
}

