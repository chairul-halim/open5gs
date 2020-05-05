/*
 * dnn_smf_info_item.h
 *
 *
 */

#ifndef _ogs_sbi_dnn_smf_info_item_H_
#define _ogs_sbi_dnn_smf_info_item_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_dnn_smf_info_item_s ogs_sbi_dnn_smf_info_item_t;
typedef struct ogs_sbi_dnn_smf_info_item_s {
    char *dnn;
} ogs_sbi_dnn_smf_info_item_t;

ogs_sbi_dnn_smf_info_item_t *ogs_sbi_dnn_smf_info_item_create(
    char *dnn
    );
void ogs_sbi_dnn_smf_info_item_free(ogs_sbi_dnn_smf_info_item_t *dnn_smf_info_item);
ogs_sbi_dnn_smf_info_item_t *ogs_sbi_dnn_smf_info_item_parseFromJSON(cJSON *dnn_smf_info_itemJSON);
cJSON *ogs_sbi_dnn_smf_info_item_convertToJSON(ogs_sbi_dnn_smf_info_item_t *dnn_smf_info_item);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_dnn_smf_info_item_H_ */

