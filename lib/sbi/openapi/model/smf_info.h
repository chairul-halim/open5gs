/*
 * smf_info.h
 *
 *
 */

#ifndef _ogs_sbi_smf_info_H_
#define _ogs_sbi_smf_info_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "access_type.h"
#include "snssai_smf_info_item.h"
#include "tai.h"
#include "tai_range.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_smf_info_s ogs_sbi_smf_info_t;
typedef struct ogs_sbi_smf_info_s {
    ogs_sbi_list_t *s_nssai_smf_info_list;
    ogs_sbi_list_t *tai_list;
    ogs_sbi_list_t *tai_range_list;
    char *pgw_fqdn;
    ogs_sbi_list_t *access_type;
} ogs_sbi_smf_info_t;

ogs_sbi_smf_info_t *ogs_sbi_smf_info_create(
    ogs_sbi_list_t *s_nssai_smf_info_list,
    ogs_sbi_list_t *tai_list,
    ogs_sbi_list_t *tai_range_list,
    char *pgw_fqdn,
    ogs_sbi_list_t *access_type
    );
void ogs_sbi_smf_info_free(ogs_sbi_smf_info_t *smf_info);
ogs_sbi_smf_info_t *ogs_sbi_smf_info_parseFromJSON(cJSON *smf_infoJSON);
cJSON *ogs_sbi_smf_info_convertToJSON(ogs_sbi_smf_info_t *smf_info);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_smf_info_H_ */

