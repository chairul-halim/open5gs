/*
 * transport_protocol.h
 *
 *
 */

#ifndef _ogs_sbi_transport_protocol_H_
#define _ogs_sbi_transport_protocol_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_transport_protocol_s ogs_sbi_transport_protocol_t;
typedef struct ogs_sbi_transport_protocol_s {
} ogs_sbi_transport_protocol_t;

ogs_sbi_transport_protocol_t *ogs_sbi_transport_protocol_create(
    );
void ogs_sbi_transport_protocol_free(ogs_sbi_transport_protocol_t *transport_protocol);
ogs_sbi_transport_protocol_t *ogs_sbi_transport_protocol_parseFromJSON(cJSON *transport_protocolJSON);
cJSON *ogs_sbi_transport_protocol_convertToJSON(ogs_sbi_transport_protocol_t *transport_protocol);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_transport_protocol_H_ */

