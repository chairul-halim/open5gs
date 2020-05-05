/*
 * n2_interface_amf_info.h
 *
 *
 */

#ifndef _ogs_sbi_n2_interface_amf_info_H_
#define _ogs_sbi_n2_interface_amf_info_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "ipv6_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_n2_interface_amf_info_s ogs_sbi_n2_interface_amf_info_t;
typedef struct ogs_sbi_n2_interface_amf_info_s {
    ogs_sbi_list_t *ipv4_endpoint_address;
    ogs_sbi_list_t *ipv6_endpoint_address;
    char *amf_name;
} ogs_sbi_n2_interface_amf_info_t;

ogs_sbi_n2_interface_amf_info_t *ogs_sbi_n2_interface_amf_info_create(
    ogs_sbi_list_t *ipv4_endpoint_address,
    ogs_sbi_list_t *ipv6_endpoint_address,
    char *amf_name
    );
void ogs_sbi_n2_interface_amf_info_free(ogs_sbi_n2_interface_amf_info_t *n2_interface_amf_info);
ogs_sbi_n2_interface_amf_info_t *ogs_sbi_n2_interface_amf_info_parseFromJSON(cJSON *n2_interface_amf_infoJSON);
cJSON *ogs_sbi_n2_interface_amf_info_convertToJSON(ogs_sbi_n2_interface_amf_info_t *n2_interface_amf_info);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_n2_interface_amf_info_H_ */

