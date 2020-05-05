/*
 * amf_info.h
 *
 *
 */

#ifndef _ogs_sbi_amf_info_H_
#define _ogs_sbi_amf_info_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "guami.h"
#include "n2_interface_amf_info.h"
#include "tai.h"
#include "tai_range.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_amf_info_s ogs_sbi_amf_info_t;
typedef struct ogs_sbi_amf_info_s {
    char *amf_set_id;
    char *amf_region_id;
    ogs_sbi_list_t *guami_list;
    ogs_sbi_list_t *tai_list;
    ogs_sbi_list_t *tai_range_list;
    ogs_sbi_list_t *backup_info_amf_failure;
    ogs_sbi_list_t *backup_info_amf_removal;
    struct ogs_sbi_n2_interface_amf_info_s *n2_interface_amf_info;
} ogs_sbi_amf_info_t;

ogs_sbi_amf_info_t *ogs_sbi_amf_info_create(
    char *amf_set_id,
    char *amf_region_id,
    ogs_sbi_list_t *guami_list,
    ogs_sbi_list_t *tai_list,
    ogs_sbi_list_t *tai_range_list,
    ogs_sbi_list_t *backup_info_amf_failure,
    ogs_sbi_list_t *backup_info_amf_removal,
    ogs_sbi_n2_interface_amf_info_t *n2_interface_amf_info
    );
void ogs_sbi_amf_info_free(ogs_sbi_amf_info_t *amf_info);
ogs_sbi_amf_info_t *ogs_sbi_amf_info_parseFromJSON(cJSON *amf_infoJSON);
cJSON *ogs_sbi_amf_info_convertToJSON(ogs_sbi_amf_info_t *amf_info);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_amf_info_H_ */

