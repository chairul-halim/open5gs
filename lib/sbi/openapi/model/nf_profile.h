/*
 * nf_profile.h
 *
 *
 */

#ifndef _ogs_sbi_nf_profile_H_
#define _ogs_sbi_nf_profile_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "amf_info.h"
#include "ausf_info.h"
#include "bsf_info.h"
#include "chf_info.h"
#include "default_notification_subscription.h"
#include "ipv6_addr.h"
#include "nf_service.h"
#include "nf_status.h"
#include "nf_type.h"
#include "nrf_info.h"
#include "nwdaf_info.h"
#include "object.h"
#include "pcf_info.h"
#include "plmn_id.h"
#include "plmn_snssai.h"
#include "smf_info.h"
#include "snssai.h"
#include "udm_info.h"
#include "udr_info.h"
#include "upf_info.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_nf_profile_s ogs_sbi_nf_profile_t;
typedef struct ogs_sbi_nf_profile_s {
    char *nf_instance_id;
    char *nf_instance_name;
    ogs_sbi_nf_type_e nf_type;
    ogs_sbi_nf_status_e nf_status;
    int heart_beat_timer;
    ogs_sbi_list_t *plmn_list;
    ogs_sbi_list_t *s_nssais;
    ogs_sbi_list_t *per_plmn_snssai_list;
    ogs_sbi_list_t *nsi_list;
    char *fqdn;
    char *inter_plmn_fqdn;
    ogs_sbi_list_t *ipv4_addresses;
    ogs_sbi_list_t *ipv6_addresses;
    ogs_sbi_list_t *allowed_plmns;
    ogs_sbi_list_t *allowed_nf_types;
    ogs_sbi_list_t *allowed_nf_domains;
    ogs_sbi_list_t *allowed_nssais;
    int priority;
    int capacity;
    int load;
    char *locality;
    struct ogs_sbi_udr_info_s *udr_info;
    ogs_sbi_list_t *udr_info_ext;
    struct ogs_sbi_udm_info_s *udm_info;
    ogs_sbi_list_t *udm_info_ext;
    struct ogs_sbi_ausf_info_s *ausf_info;
    ogs_sbi_list_t *ausf_info_ext;
    struct ogs_sbi_amf_info_s *amf_info;
    ogs_sbi_list_t *amf_info_ext;
    struct ogs_sbi_smf_info_s *smf_info;
    ogs_sbi_list_t *smf_info_ext;
    struct ogs_sbi_upf_info_s *upf_info;
    ogs_sbi_list_t *upf_info_ext;
    struct ogs_sbi_pcf_info_s *pcf_info;
    ogs_sbi_list_t *pcf_info_ext;
    struct ogs_sbi_bsf_info_s *bsf_info;
    ogs_sbi_list_t *bsf_info_ext;
    struct ogs_sbi_chf_info_s *chf_info;
    ogs_sbi_list_t *chf_info_ext;
    struct ogs_sbi_nrf_info_s *nrf_info;
    struct ogs_sbi_nwdaf_info_s *nwdaf_info;
    ogs_sbi_object_t *custom_info;
    char *recovery_time;
    int nf_service_persistence;
    ogs_sbi_list_t *nf_services;
    int nf_profile_changes_support_ind;
    int nf_profile_changes_ind;
    ogs_sbi_list_t *default_notification_subscriptions;
} ogs_sbi_nf_profile_t;

ogs_sbi_nf_profile_t *ogs_sbi_nf_profile_create(
    char *nf_instance_id,
    char *nf_instance_name,
    ogs_sbi_nf_type_e nf_type,
    ogs_sbi_nf_status_e nf_status,
    int heart_beat_timer,
    ogs_sbi_list_t *plmn_list,
    ogs_sbi_list_t *s_nssais,
    ogs_sbi_list_t *per_plmn_snssai_list,
    ogs_sbi_list_t *nsi_list,
    char *fqdn,
    char *inter_plmn_fqdn,
    ogs_sbi_list_t *ipv4_addresses,
    ogs_sbi_list_t *ipv6_addresses,
    ogs_sbi_list_t *allowed_plmns,
    ogs_sbi_list_t *allowed_nf_types,
    ogs_sbi_list_t *allowed_nf_domains,
    ogs_sbi_list_t *allowed_nssais,
    int priority,
    int capacity,
    int load,
    char *locality,
    ogs_sbi_udr_info_t *udr_info,
    ogs_sbi_list_t *udr_info_ext,
    ogs_sbi_udm_info_t *udm_info,
    ogs_sbi_list_t *udm_info_ext,
    ogs_sbi_ausf_info_t *ausf_info,
    ogs_sbi_list_t *ausf_info_ext,
    ogs_sbi_amf_info_t *amf_info,
    ogs_sbi_list_t *amf_info_ext,
    ogs_sbi_smf_info_t *smf_info,
    ogs_sbi_list_t *smf_info_ext,
    ogs_sbi_upf_info_t *upf_info,
    ogs_sbi_list_t *upf_info_ext,
    ogs_sbi_pcf_info_t *pcf_info,
    ogs_sbi_list_t *pcf_info_ext,
    ogs_sbi_bsf_info_t *bsf_info,
    ogs_sbi_list_t *bsf_info_ext,
    ogs_sbi_chf_info_t *chf_info,
    ogs_sbi_list_t *chf_info_ext,
    ogs_sbi_nrf_info_t *nrf_info,
    ogs_sbi_nwdaf_info_t *nwdaf_info,
    ogs_sbi_object_t *custom_info,
    char *recovery_time,
    int nf_service_persistence,
    ogs_sbi_list_t *nf_services,
    int nf_profile_changes_support_ind,
    int nf_profile_changes_ind,
    ogs_sbi_list_t *default_notification_subscriptions
    );
void ogs_sbi_nf_profile_free(ogs_sbi_nf_profile_t *nf_profile);
ogs_sbi_nf_profile_t *ogs_sbi_nf_profile_parseFromJSON(cJSON *nf_profileJSON);
cJSON *ogs_sbi_nf_profile_convertToJSON(ogs_sbi_nf_profile_t *nf_profile);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_nf_profile_H_ */

