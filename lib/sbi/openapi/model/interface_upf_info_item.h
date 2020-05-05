/*
 * interface_upf_info_item.h
 *
 *
 */

#ifndef _ogs_sbi_interface_upf_info_item_H_
#define _ogs_sbi_interface_upf_info_item_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "ipv6_addr.h"
#include "up_interface_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_interface_upf_info_item_s ogs_sbi_interface_upf_info_item_t;
typedef struct ogs_sbi_interface_upf_info_item_s {
    struct ogs_sbi_up_interface_type_s *interface_type;
    ogs_sbi_list_t *ipv4_endpoint_addresses;
    ogs_sbi_list_t *ipv6_endpoint_addresses;
    char *endpoint_fqdn;
    char *network_instance;
} ogs_sbi_interface_upf_info_item_t;

ogs_sbi_interface_upf_info_item_t *ogs_sbi_interface_upf_info_item_create(
    ogs_sbi_up_interface_type_t *interface_type,
    ogs_sbi_list_t *ipv4_endpoint_addresses,
    ogs_sbi_list_t *ipv6_endpoint_addresses,
    char *endpoint_fqdn,
    char *network_instance
    );
void ogs_sbi_interface_upf_info_item_free(ogs_sbi_interface_upf_info_item_t *interface_upf_info_item);
ogs_sbi_interface_upf_info_item_t *ogs_sbi_interface_upf_info_item_parseFromJSON(cJSON *interface_upf_info_itemJSON);
cJSON *ogs_sbi_interface_upf_info_item_convertToJSON(ogs_sbi_interface_upf_info_item_t *interface_upf_info_item);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_interface_upf_info_item_H_ */

