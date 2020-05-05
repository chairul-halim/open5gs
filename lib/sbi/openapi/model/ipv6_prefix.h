/*
 * ipv6_prefix.h
 *
 *
 */

#ifndef _ogs_sbi_ipv6_prefix_H_
#define _ogs_sbi_ipv6_prefix_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_ipv6_prefix_s ogs_sbi_ipv6_prefix_t;
typedef struct ogs_sbi_ipv6_prefix_s {
} ogs_sbi_ipv6_prefix_t;

ogs_sbi_ipv6_prefix_t *ogs_sbi_ipv6_prefix_create(
    );
void ogs_sbi_ipv6_prefix_free(ogs_sbi_ipv6_prefix_t *ipv6_prefix);
ogs_sbi_ipv6_prefix_t *ogs_sbi_ipv6_prefix_parseFromJSON(cJSON *ipv6_prefixJSON);
cJSON *ogs_sbi_ipv6_prefix_convertToJSON(ogs_sbi_ipv6_prefix_t *ipv6_prefix);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_ipv6_prefix_H_ */

