/*
 * network_slice_cond.h
 *
 *
 */

#ifndef _ogs_sbi_network_slice_cond_H_
#define _ogs_sbi_network_slice_cond_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "snssai.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_network_slice_cond_s ogs_sbi_network_slice_cond_t;
typedef struct ogs_sbi_network_slice_cond_s {
    ogs_sbi_list_t *snssai_list;
    ogs_sbi_list_t *nsi_list;
} ogs_sbi_network_slice_cond_t;

ogs_sbi_network_slice_cond_t *ogs_sbi_network_slice_cond_create(
    ogs_sbi_list_t *snssai_list,
    ogs_sbi_list_t *nsi_list
    );
void ogs_sbi_network_slice_cond_free(ogs_sbi_network_slice_cond_t *network_slice_cond);
ogs_sbi_network_slice_cond_t *ogs_sbi_network_slice_cond_parseFromJSON(cJSON *network_slice_condJSON);
cJSON *ogs_sbi_network_slice_cond_convertToJSON(ogs_sbi_network_slice_cond_t *network_slice_cond);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_network_slice_cond_H_ */

