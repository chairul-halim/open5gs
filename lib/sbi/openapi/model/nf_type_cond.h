/*
 * nf_type_cond.h
 *
 *
 */

#ifndef _ogs_sbi_nf_type_cond_H_
#define _ogs_sbi_nf_type_cond_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "nf_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_nf_type_cond_s ogs_sbi_nf_type_cond_t;
typedef struct ogs_sbi_nf_type_cond_s {
    ogs_sbi_nf_type_e nf_type;
} ogs_sbi_nf_type_cond_t;

ogs_sbi_nf_type_cond_t *ogs_sbi_nf_type_cond_create(
    ogs_sbi_nf_type_e nf_type
    );
void ogs_sbi_nf_type_cond_free(ogs_sbi_nf_type_cond_t *nf_type_cond);
ogs_sbi_nf_type_cond_t *ogs_sbi_nf_type_cond_parseFromJSON(cJSON *nf_type_condJSON);
cJSON *ogs_sbi_nf_type_cond_convertToJSON(ogs_sbi_nf_type_cond_t *nf_type_cond);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_nf_type_cond_H_ */

