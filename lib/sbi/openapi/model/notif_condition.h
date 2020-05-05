/*
 * notif_condition.h
 *
 *
 */

#ifndef _ogs_sbi_notif_condition_H_
#define _ogs_sbi_notif_condition_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_notif_condition_s ogs_sbi_notif_condition_t;
typedef struct ogs_sbi_notif_condition_s {
    ogs_sbi_list_t *monitored_attributes;
    ogs_sbi_list_t *unmonitored_attributes;
} ogs_sbi_notif_condition_t;

ogs_sbi_notif_condition_t *ogs_sbi_notif_condition_create(
    ogs_sbi_list_t *monitored_attributes,
    ogs_sbi_list_t *unmonitored_attributes
    );
void ogs_sbi_notif_condition_free(ogs_sbi_notif_condition_t *notif_condition);
ogs_sbi_notif_condition_t *ogs_sbi_notif_condition_parseFromJSON(cJSON *notif_conditionJSON);
cJSON *ogs_sbi_notif_condition_convertToJSON(ogs_sbi_notif_condition_t *notif_condition);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_notif_condition_H_ */

