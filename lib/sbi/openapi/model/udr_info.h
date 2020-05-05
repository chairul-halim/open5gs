/*
 * udr_info.h
 *
 *
 */

#ifndef _ogs_sbi_udr_info_H_
#define _ogs_sbi_udr_info_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "data_set_id.h"
#include "identity_range.h"
#include "supi_range.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_udr_info_s ogs_sbi_udr_info_t;
typedef struct ogs_sbi_udr_info_s {
    char *group_id;
    ogs_sbi_list_t *supi_ranges;
    ogs_sbi_list_t *gpsi_ranges;
    ogs_sbi_list_t *external_group_identifiers_ranges;
    ogs_sbi_list_t *supported_data_sets;
} ogs_sbi_udr_info_t;

ogs_sbi_udr_info_t *ogs_sbi_udr_info_create(
    char *group_id,
    ogs_sbi_list_t *supi_ranges,
    ogs_sbi_list_t *gpsi_ranges,
    ogs_sbi_list_t *external_group_identifiers_ranges,
    ogs_sbi_list_t *supported_data_sets
    );
void ogs_sbi_udr_info_free(ogs_sbi_udr_info_t *udr_info);
ogs_sbi_udr_info_t *ogs_sbi_udr_info_parseFromJSON(cJSON *udr_infoJSON);
cJSON *ogs_sbi_udr_info_convertToJSON(ogs_sbi_udr_info_t *udr_info);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_udr_info_H_ */

