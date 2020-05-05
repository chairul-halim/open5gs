/*
 * notification_event_type.h
 *
 *
 */

#ifndef _ogs_sbi_notification_event_type_H_
#define _ogs_sbi_notification_event_type_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_notification_event_type_s ogs_sbi_notification_event_type_t;
typedef struct ogs_sbi_notification_event_type_s {
} ogs_sbi_notification_event_type_t;

ogs_sbi_notification_event_type_t *ogs_sbi_notification_event_type_create(
    );
void ogs_sbi_notification_event_type_free(ogs_sbi_notification_event_type_t *notification_event_type);
ogs_sbi_notification_event_type_t *ogs_sbi_notification_event_type_parseFromJSON(cJSON *notification_event_typeJSON);
cJSON *ogs_sbi_notification_event_type_convertToJSON(ogs_sbi_notification_event_type_t *notification_event_type);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_notification_event_type_H_ */

