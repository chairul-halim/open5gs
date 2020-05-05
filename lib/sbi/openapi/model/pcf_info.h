/*
 * pcf_info.h
 *
 *
 */

#ifndef _ogs_sbi_pcf_info_H_
#define _ogs_sbi_pcf_info_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "identity_range.h"
#include "supi_range.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_pcf_info_s ogs_sbi_pcf_info_t;
typedef struct ogs_sbi_pcf_info_s {
    char *group_id;
    ogs_sbi_list_t *dnn_list;
    ogs_sbi_list_t *supi_ranges;
    ogs_sbi_list_t *gpsi_ranges;
    char *rx_diam_host;
    char *rx_diam_realm;
} ogs_sbi_pcf_info_t;

ogs_sbi_pcf_info_t *ogs_sbi_pcf_info_create(
    char *group_id,
    ogs_sbi_list_t *dnn_list,
    ogs_sbi_list_t *supi_ranges,
    ogs_sbi_list_t *gpsi_ranges,
    char *rx_diam_host,
    char *rx_diam_realm
    );
void ogs_sbi_pcf_info_free(ogs_sbi_pcf_info_t *pcf_info);
ogs_sbi_pcf_info_t *ogs_sbi_pcf_info_parseFromJSON(cJSON *pcf_infoJSON);
cJSON *ogs_sbi_pcf_info_convertToJSON(ogs_sbi_pcf_info_t *pcf_info);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_pcf_info_H_ */

