/*
 * chf_info.h
 *
 *
 */

#ifndef _ogs_sbi_chf_info_H_
#define _ogs_sbi_chf_info_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "identity_range.h"
#include "plmn_range.h"
#include "supi_range.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_chf_info_s ogs_sbi_chf_info_t;
typedef struct ogs_sbi_chf_info_s {
    ogs_sbi_list_t *supi_range_list;
    ogs_sbi_list_t *gpsi_range_list;
    ogs_sbi_list_t *plmn_range_list;
} ogs_sbi_chf_info_t;

ogs_sbi_chf_info_t *ogs_sbi_chf_info_create(
    ogs_sbi_list_t *supi_range_list,
    ogs_sbi_list_t *gpsi_range_list,
    ogs_sbi_list_t *plmn_range_list
    );
void ogs_sbi_chf_info_free(ogs_sbi_chf_info_t *chf_info);
ogs_sbi_chf_info_t *ogs_sbi_chf_info_parseFromJSON(cJSON *chf_infoJSON);
cJSON *ogs_sbi_chf_info_convertToJSON(ogs_sbi_chf_info_t *chf_info);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_chf_info_H_ */

