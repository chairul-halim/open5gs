/*
 * ipv6_prefix_range.h
 *
 *
 */

#ifndef _ogs_sbi_ipv6_prefix_range_H_
#define _ogs_sbi_ipv6_prefix_range_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "ipv6_prefix.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_ipv6_prefix_range_s ogs_sbi_ipv6_prefix_range_t;
typedef struct ogs_sbi_ipv6_prefix_range_s {
    struct ogs_sbi_ipv6_prefix_s *start;
    struct ogs_sbi_ipv6_prefix_s *end;
} ogs_sbi_ipv6_prefix_range_t;

ogs_sbi_ipv6_prefix_range_t *ogs_sbi_ipv6_prefix_range_create(
    ogs_sbi_ipv6_prefix_t *start,
    ogs_sbi_ipv6_prefix_t *end
    );
void ogs_sbi_ipv6_prefix_range_free(ogs_sbi_ipv6_prefix_range_t *ipv6_prefix_range);
ogs_sbi_ipv6_prefix_range_t *ogs_sbi_ipv6_prefix_range_parseFromJSON(cJSON *ipv6_prefix_rangeJSON);
cJSON *ogs_sbi_ipv6_prefix_range_convertToJSON(ogs_sbi_ipv6_prefix_range_t *ipv6_prefix_range);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_ipv6_prefix_range_H_ */

