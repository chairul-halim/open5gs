/*
 * nf_service_status.h
 *
 *
 */

#ifndef _ogs_sbi_nf_service_status_H_
#define _ogs_sbi_nf_service_status_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_nf_service_status_s ogs_sbi_nf_service_status_t;
typedef struct ogs_sbi_nf_service_status_s {
} ogs_sbi_nf_service_status_t;

ogs_sbi_nf_service_status_t *ogs_sbi_nf_service_status_create(
    );
void ogs_sbi_nf_service_status_free(ogs_sbi_nf_service_status_t *nf_service_status);
ogs_sbi_nf_service_status_t *ogs_sbi_nf_service_status_parseFromJSON(cJSON *nf_service_statusJSON);
cJSON *ogs_sbi_nf_service_status_convertToJSON(ogs_sbi_nf_service_status_t *nf_service_status);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_nf_service_status_H_ */

