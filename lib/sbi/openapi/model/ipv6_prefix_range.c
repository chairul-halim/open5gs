
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ipv6_prefix_range.h"

ogs_sbi_ipv6_prefix_range_t *ogs_sbi_ipv6_prefix_range_create(
    ogs_sbi_ipv6_prefix_t *start,
    ogs_sbi_ipv6_prefix_t *end
    )
{
    ogs_sbi_ipv6_prefix_range_t *ipv6_prefix_range_local_var = ogs_malloc(sizeof(ogs_sbi_ipv6_prefix_range_t));
    if (!ipv6_prefix_range_local_var) {
        return NULL;
    }
    ipv6_prefix_range_local_var->start = start;
    ipv6_prefix_range_local_var->end = end;

    return ipv6_prefix_range_local_var;
}

void ogs_sbi_ipv6_prefix_range_free(ogs_sbi_ipv6_prefix_range_t *ipv6_prefix_range)
{
    if (NULL == ipv6_prefix_range) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_sbi_ipv6_prefix_free(ipv6_prefix_range->start);
    ogs_sbi_ipv6_prefix_free(ipv6_prefix_range->end);
    ogs_free(ipv6_prefix_range);
}

cJSON *ogs_sbi_ipv6_prefix_range_convertToJSON(ogs_sbi_ipv6_prefix_range_t *ipv6_prefix_range)
{
    cJSON *item = cJSON_CreateObject();
    if (ipv6_prefix_range->start) {
        cJSON *start_local_JSON = ogs_sbi_ipv6_prefix_convertToJSON(ipv6_prefix_range->start);
        if (start_local_JSON == NULL) {
            goto fail;
        }
        cJSON_AddItemToObject(item, "start", start_local_JSON);
        if (item->child == NULL) {
            goto fail;
        }
    }

    if (ipv6_prefix_range->end) {
        cJSON *end_local_JSON = ogs_sbi_ipv6_prefix_convertToJSON(ipv6_prefix_range->end);
        if (end_local_JSON == NULL) {
            goto fail;
        }
        cJSON_AddItemToObject(item, "end", end_local_JSON);
        if (item->child == NULL) {
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

ogs_sbi_ipv6_prefix_range_t *ogs_sbi_ipv6_prefix_range_parseFromJSON(cJSON *ipv6_prefix_rangeJSON)
{
    ogs_sbi_ipv6_prefix_range_t *ipv6_prefix_range_local_var = NULL;
    cJSON *start = cJSON_GetObjectItemCaseSensitive(ipv6_prefix_rangeJSON, "start");

    ogs_sbi_ipv6_prefix_t *start_local_nonprim = NULL;
    if (start) {
        start_local_nonprim = ogs_sbi_ipv6_prefix_parseFromJSON(start);
    }

    cJSON *end = cJSON_GetObjectItemCaseSensitive(ipv6_prefix_rangeJSON, "end");

    ogs_sbi_ipv6_prefix_t *end_local_nonprim = NULL;
    if (end) {
        end_local_nonprim = ogs_sbi_ipv6_prefix_parseFromJSON(end);
    }

    ipv6_prefix_range_local_var = ogs_sbi_ipv6_prefix_range_create (
        start ? start_local_nonprim : NULL,
        end ? end_local_nonprim : NULL
        );

    return ipv6_prefix_range_local_var;
end:
    return NULL;
}

