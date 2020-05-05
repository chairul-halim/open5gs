/*
 * upf_info.h
 *
 *
 */

#ifndef _ogs_sbi_upf_info_H_
#define _ogs_sbi_upf_info_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "atsss_capability.h"
#include "interface_upf_info_item.h"
#include "pdu_session_type.h"
#include "snssai_upf_info_item.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_upf_info_s ogs_sbi_upf_info_t;
typedef struct ogs_sbi_upf_info_s {
    ogs_sbi_list_t *s_nssai_upf_info_list;
    ogs_sbi_list_t *smf_serving_area;
    ogs_sbi_list_t *interface_upf_info_list;
    int iwk_eps_ind;
    ogs_sbi_list_t *pdu_session_types;
    struct ogs_sbi_atsss_capability_s *atsss_capability;
    int ue_ip_addr_ind;
} ogs_sbi_upf_info_t;

ogs_sbi_upf_info_t *ogs_sbi_upf_info_create(
    ogs_sbi_list_t *s_nssai_upf_info_list,
    ogs_sbi_list_t *smf_serving_area,
    ogs_sbi_list_t *interface_upf_info_list,
    int iwk_eps_ind,
    ogs_sbi_list_t *pdu_session_types,
    ogs_sbi_atsss_capability_t *atsss_capability,
    int ue_ip_addr_ind
    );
void ogs_sbi_upf_info_free(ogs_sbi_upf_info_t *upf_info);
ogs_sbi_upf_info_t *ogs_sbi_upf_info_parseFromJSON(cJSON *upf_infoJSON);
cJSON *ogs_sbi_upf_info_convertToJSON(ogs_sbi_upf_info_t *upf_info);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_upf_info_H_ */

