/*
 * nf_service.h
 *
 *
 */

#ifndef _ogs_sbi_nf_service_H_
#define _ogs_sbi_nf_service_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "chf_service_info.h"
#include "default_notification_subscription.h"
#include "ip_end_point.h"
#include "nf_service_status.h"
#include "nf_service_version.h"
#include "nf_type.h"
#include "plmn_id.h"
#include "service_name.h"
#include "snssai.h"
#include "uri_scheme.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_nf_service_s ogs_sbi_nf_service_t;
typedef struct ogs_sbi_nf_service_s {
    char *service_instance_id;
    struct ogs_sbi_service_name_s *service_name;
    ogs_sbi_list_t *versions;
    struct ogs_sbi_uri_scheme_s *scheme;
    struct ogs_sbi_nf_service_status_s *nf_service_status;
    char *fqdn;
    char *inter_plmn_fqdn;
    ogs_sbi_list_t *ip_end_points;
    char *api_prefix;
    ogs_sbi_list_t *default_notification_subscriptions;
    ogs_sbi_list_t *allowed_plmns;
    ogs_sbi_list_t *allowed_nf_types;
    ogs_sbi_list_t *allowed_nf_domains;
    ogs_sbi_list_t *allowed_nssais;
    int priority;
    int capacity;
    int load;
    char *recovery_time;
    struct ogs_sbi_chf_service_info_s *chf_service_info;
    char *supported_features;
} ogs_sbi_nf_service_t;

ogs_sbi_nf_service_t *ogs_sbi_nf_service_create(
    char *service_instance_id,
    ogs_sbi_service_name_t *service_name,
    ogs_sbi_list_t *versions,
    ogs_sbi_uri_scheme_t *scheme,
    ogs_sbi_nf_service_status_t *nf_service_status,
    char *fqdn,
    char *inter_plmn_fqdn,
    ogs_sbi_list_t *ip_end_points,
    char *api_prefix,
    ogs_sbi_list_t *default_notification_subscriptions,
    ogs_sbi_list_t *allowed_plmns,
    ogs_sbi_list_t *allowed_nf_types,
    ogs_sbi_list_t *allowed_nf_domains,
    ogs_sbi_list_t *allowed_nssais,
    int priority,
    int capacity,
    int load,
    char *recovery_time,
    ogs_sbi_chf_service_info_t *chf_service_info,
    char *supported_features
    );
void ogs_sbi_nf_service_free(ogs_sbi_nf_service_t *nf_service);
ogs_sbi_nf_service_t *ogs_sbi_nf_service_parseFromJSON(cJSON *nf_serviceJSON);
cJSON *ogs_sbi_nf_service_convertToJSON(ogs_sbi_nf_service_t *nf_service);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_nf_service_H_ */

