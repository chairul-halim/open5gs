/*
 * nwdaf_event.h
 *
 * Possible values are - SLICE_LOAD_LEVEL: Indicates that the event subscribed is load level information of Network Slice instance - NETWORK_PERFORMANCE: Indicates that the event subscribed is network performance information. - NF_LOAD: Indicates that the event subscribed is load level and status of one or several Network Functions. - SERVICE_EXPERIENCE: Indicates that the event subscribed is service experience. - UE_MOBILITY: Indicates that the event subscribed is UE mobility information. - UE_COMMUNICATION: Indicates that the event subscribed is UE communication information. - QOS_SUSTAINABILITY: Indicates that the event subscribed is QoS sustainability. - ABNORMAL_BEHAVIOUR: Indicates that the event subscribed is abnormal behaviour. - USER_DATA_CONGESTION: Indicates that the event subscribed is user data congestion information.
 */

#ifndef _ogs_sbi_nwdaf_event_H_
#define _ogs_sbi_nwdaf_event_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_nwdaf_event_s ogs_sbi_nwdaf_event_t;
typedef struct ogs_sbi_nwdaf_event_s {
} ogs_sbi_nwdaf_event_t;

ogs_sbi_nwdaf_event_t *ogs_sbi_nwdaf_event_create(
    );
void ogs_sbi_nwdaf_event_free(ogs_sbi_nwdaf_event_t *nwdaf_event);
ogs_sbi_nwdaf_event_t *ogs_sbi_nwdaf_event_parseFromJSON(cJSON *nwdaf_eventJSON);
cJSON *ogs_sbi_nwdaf_event_convertToJSON(ogs_sbi_nwdaf_event_t *nwdaf_event);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_nwdaf_event_H_ */

