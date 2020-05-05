/*
 * subscription_data.h
 *
 *
 */

#ifndef _ogs_sbi_subscription_data_H_
#define _ogs_sbi_subscription_data_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "nf_type.h"
#include "notif_condition.h"
#include "notification_event_type.h"
#include "plmn_id.h"
#include "snssai.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_subscription_data_s ogs_sbi_subscription_data_t;
typedef struct ogs_sbi_subscription_data_s {
    char *nf_status_notification_uri;
    char *req_nf_instance_id;
    char *subscription_id;
    char *validity_time;
    ogs_sbi_list_t *req_notif_events;
    struct ogs_sbi_plmn_id_s *plmn_id;
    struct ogs_sbi_notif_condition_s *notif_condition;
    ogs_sbi_nf_type_e req_nf_type;
    char *req_nf_fqdn;
    ogs_sbi_list_t *req_snssais;
} ogs_sbi_subscription_data_t;

ogs_sbi_subscription_data_t *ogs_sbi_subscription_data_create(
    char *nf_status_notification_uri,
    char *req_nf_instance_id,
    char *subscription_id,
    char *validity_time,
    ogs_sbi_list_t *req_notif_events,
    ogs_sbi_plmn_id_t *plmn_id,
    ogs_sbi_notif_condition_t *notif_condition,
    ogs_sbi_nf_type_e req_nf_type,
    char *req_nf_fqdn,
    ogs_sbi_list_t *req_snssais
    );
void ogs_sbi_subscription_data_free(ogs_sbi_subscription_data_t *subscription_data);
ogs_sbi_subscription_data_t *ogs_sbi_subscription_data_parseFromJSON(cJSON *subscription_dataJSON);
cJSON *ogs_sbi_subscription_data_convertToJSON(ogs_sbi_subscription_data_t *subscription_data);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_subscription_data_H_ */

