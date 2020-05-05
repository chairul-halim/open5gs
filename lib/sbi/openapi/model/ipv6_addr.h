/*
 * ipv6_addr.h
 *
 *
 */

#ifndef _ogs_sbi_ipv6_addr_H_
#define _ogs_sbi_ipv6_addr_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_ipv6_addr_s ogs_sbi_ipv6_addr_t;
typedef struct ogs_sbi_ipv6_addr_s {
} ogs_sbi_ipv6_addr_t;

ogs_sbi_ipv6_addr_t *ogs_sbi_ipv6_addr_create(
    );
void ogs_sbi_ipv6_addr_free(ogs_sbi_ipv6_addr_t *ipv6_addr);
ogs_sbi_ipv6_addr_t *ogs_sbi_ipv6_addr_parseFromJSON(cJSON *ipv6_addrJSON);
cJSON *ogs_sbi_ipv6_addr_convertToJSON(ogs_sbi_ipv6_addr_t *ipv6_addr);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_ipv6_addr_H_ */

