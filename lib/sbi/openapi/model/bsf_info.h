/*
 * bsf_info.h
 *
 *
 */

#ifndef _ogs_sbi_bsf_info_H_
#define _ogs_sbi_bsf_info_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "ipv4_address_range.h"
#include "ipv6_prefix_range.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_bsf_info_s ogs_sbi_bsf_info_t;
typedef struct ogs_sbi_bsf_info_s {
    ogs_sbi_list_t *dnn_list;
    ogs_sbi_list_t *ip_domain_list;
    ogs_sbi_list_t *ipv4_address_ranges;
    ogs_sbi_list_t *ipv6_prefix_ranges;
} ogs_sbi_bsf_info_t;

ogs_sbi_bsf_info_t *ogs_sbi_bsf_info_create(
    ogs_sbi_list_t *dnn_list,
    ogs_sbi_list_t *ip_domain_list,
    ogs_sbi_list_t *ipv4_address_ranges,
    ogs_sbi_list_t *ipv6_prefix_ranges
    );
void ogs_sbi_bsf_info_free(ogs_sbi_bsf_info_t *bsf_info);
ogs_sbi_bsf_info_t *ogs_sbi_bsf_info_parseFromJSON(cJSON *bsf_infoJSON);
cJSON *ogs_sbi_bsf_info_convertToJSON(ogs_sbi_bsf_info_t *bsf_info);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_bsf_info_H_ */

