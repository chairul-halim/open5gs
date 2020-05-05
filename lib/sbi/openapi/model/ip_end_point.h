/*
 * ip_end_point.h
 *
 *
 */

#ifndef _ogs_sbi_ip_end_point_H_
#define _ogs_sbi_ip_end_point_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "ipv6_addr.h"
#include "transport_protocol.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_ip_end_point_s ogs_sbi_ip_end_point_t;
typedef struct ogs_sbi_ip_end_point_s {
    char *ipv4_address;
    struct ogs_sbi_ipv6_addr_s *ipv6_address;
    struct ogs_sbi_transport_protocol_s *transport;
    int port;
} ogs_sbi_ip_end_point_t;

ogs_sbi_ip_end_point_t *ogs_sbi_ip_end_point_create(
    char *ipv4_address,
    ogs_sbi_ipv6_addr_t *ipv6_address,
    ogs_sbi_transport_protocol_t *transport,
    int port
    );
void ogs_sbi_ip_end_point_free(ogs_sbi_ip_end_point_t *ip_end_point);
ogs_sbi_ip_end_point_t *ogs_sbi_ip_end_point_parseFromJSON(cJSON *ip_end_pointJSON);
cJSON *ogs_sbi_ip_end_point_convertToJSON(ogs_sbi_ip_end_point_t *ip_end_point);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_ip_end_point_H_ */

