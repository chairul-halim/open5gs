/*
 * nf_group_cond.h
 *
 *
 */

#ifndef _ogs_sbi_nf_group_cond_H_
#define _ogs_sbi_nf_group_cond_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_nf_group_cond_s ogs_sbi_nf_group_cond_t;
typedef enum { ogs_sbi_nf_group_cond_NFTYPE_NULL = 0, ogs_sbi_nf_group_cond_NFTYPE_UDM, ogs_sbi_nf_group_cond_NFTYPE_AUSF, ogs_sbi_nf_group_cond_NFTYPE_UDR, ogs_sbi_nf_group_cond_NFTYPE_PCF } ogs_sbi_nf_group_cond_nf_type_e;

char* ogs_sbi_nf_group_cond_nf_type_ToString(ogs_sbi_nf_group_cond_nf_type_e nf_type);

ogs_sbi_nf_group_cond_nf_type_e ogs_sbi_nf_group_cond_nf_type_FromString(char* nf_type);
typedef struct ogs_sbi_nf_group_cond_s {
    ogs_sbi_nf_group_cond_nf_type_e nf_type;
    char *nf_group_id;
} ogs_sbi_nf_group_cond_t;

ogs_sbi_nf_group_cond_t *ogs_sbi_nf_group_cond_create(
    ogs_sbi_nf_group_cond_nf_type_e nf_type,
    char *nf_group_id
    );
void ogs_sbi_nf_group_cond_free(ogs_sbi_nf_group_cond_t *nf_group_cond);
ogs_sbi_nf_group_cond_t *ogs_sbi_nf_group_cond_parseFromJSON(cJSON *nf_group_condJSON);
cJSON *ogs_sbi_nf_group_cond_convertToJSON(ogs_sbi_nf_group_cond_t *nf_group_cond);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_nf_group_cond_H_ */

