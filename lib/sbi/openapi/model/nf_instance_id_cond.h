/*
 * nf_instance_id_cond.h
 *
 *
 */

#ifndef _ogs_sbi_nf_instance_id_cond_H_
#define _ogs_sbi_nf_instance_id_cond_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_nf_instance_id_cond_s ogs_sbi_nf_instance_id_cond_t;
typedef struct ogs_sbi_nf_instance_id_cond_s {
    char *nf_instance_id;
} ogs_sbi_nf_instance_id_cond_t;

ogs_sbi_nf_instance_id_cond_t *ogs_sbi_nf_instance_id_cond_create(
    char *nf_instance_id
    );
void ogs_sbi_nf_instance_id_cond_free(ogs_sbi_nf_instance_id_cond_t *nf_instance_id_cond);
ogs_sbi_nf_instance_id_cond_t *ogs_sbi_nf_instance_id_cond_parseFromJSON(cJSON *nf_instance_id_condJSON);
cJSON *ogs_sbi_nf_instance_id_cond_convertToJSON(ogs_sbi_nf_instance_id_cond_t *nf_instance_id_cond);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_nf_instance_id_cond_H_ */

