/*
 * amf_cond.h
 *
 *
 */

#ifndef _ogs_sbi_amf_cond_H_
#define _ogs_sbi_amf_cond_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_amf_cond_s ogs_sbi_amf_cond_t;
typedef struct ogs_sbi_amf_cond_s {
    char *amf_set_id;
    char *amf_region_id;
} ogs_sbi_amf_cond_t;

ogs_sbi_amf_cond_t *ogs_sbi_amf_cond_create(
    char *amf_set_id,
    char *amf_region_id
    );
void ogs_sbi_amf_cond_free(ogs_sbi_amf_cond_t *amf_cond);
ogs_sbi_amf_cond_t *ogs_sbi_amf_cond_parseFromJSON(cJSON *amf_condJSON);
cJSON *ogs_sbi_amf_cond_convertToJSON(ogs_sbi_amf_cond_t *amf_cond);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_amf_cond_H_ */

