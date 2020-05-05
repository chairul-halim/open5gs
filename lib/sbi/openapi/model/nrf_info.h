/*
 * nrf_info.h
 *
 *
 */

#ifndef _ogs_sbi_nrf_info_H_
#define _ogs_sbi_nrf_info_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "amf_info.h"
#include "ausf_info.h"
#include "bsf_info.h"
#include "chf_info.h"
#include "nwdaf_info.h"
#include "pcf_info.h"
#include "smf_info.h"
#include "udm_info.h"
#include "udr_info.h"
#include "upf_info.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_nrf_info_s ogs_sbi_nrf_info_t;
typedef struct ogs_sbi_nrf_info_s {
    ogs_sbi_list_t* served_udr_info;
    ogs_sbi_list_t* served_udm_info;
    ogs_sbi_list_t* served_ausf_info;
    ogs_sbi_list_t* served_amf_info;
    ogs_sbi_list_t* served_smf_info;
    ogs_sbi_list_t* served_upf_info;
    ogs_sbi_list_t* served_pcf_info;
    ogs_sbi_list_t* served_bsf_info;
    ogs_sbi_list_t* served_chf_info;
    ogs_sbi_list_t* served_nwdaf_info;
} ogs_sbi_nrf_info_t;

ogs_sbi_nrf_info_t *ogs_sbi_nrf_info_create(
    ogs_sbi_list_t* served_udr_info,
    ogs_sbi_list_t* served_udm_info,
    ogs_sbi_list_t* served_ausf_info,
    ogs_sbi_list_t* served_amf_info,
    ogs_sbi_list_t* served_smf_info,
    ogs_sbi_list_t* served_upf_info,
    ogs_sbi_list_t* served_pcf_info,
    ogs_sbi_list_t* served_bsf_info,
    ogs_sbi_list_t* served_chf_info,
    ogs_sbi_list_t* served_nwdaf_info
    );
void ogs_sbi_nrf_info_free(ogs_sbi_nrf_info_t *nrf_info);
ogs_sbi_nrf_info_t *ogs_sbi_nrf_info_parseFromJSON(cJSON *nrf_infoJSON);
cJSON *ogs_sbi_nrf_info_convertToJSON(ogs_sbi_nrf_info_t *nrf_info);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_nrf_info_H_ */

