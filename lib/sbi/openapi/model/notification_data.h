/*
 * notification_data.h
 *
 *
 */

#ifndef _ogs_sbi_notification_data_H_
#define _ogs_sbi_notification_data_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "change_item.h"
#include "nf_profile.h"
#include "notification_event_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_notification_data_s ogs_sbi_notification_data_t;
typedef struct ogs_sbi_notification_data_s {
    struct ogs_sbi_notification_event_type_s *event;
    char *nf_instance_uri;
    struct ogs_sbi_nf_profile_s *nf_profile;
    ogs_sbi_list_t *profile_changes;
} ogs_sbi_notification_data_t;

ogs_sbi_notification_data_t *ogs_sbi_notification_data_create(
    ogs_sbi_notification_event_type_t *event,
    char *nf_instance_uri,
    ogs_sbi_nf_profile_t *nf_profile,
    ogs_sbi_list_t *profile_changes
    );
void ogs_sbi_notification_data_free(ogs_sbi_notification_data_t *notification_data);
ogs_sbi_notification_data_t *ogs_sbi_notification_data_parseFromJSON(cJSON *notification_dataJSON);
cJSON *ogs_sbi_notification_data_convertToJSON(ogs_sbi_notification_data_t *notification_data);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_notification_data_H_ */

