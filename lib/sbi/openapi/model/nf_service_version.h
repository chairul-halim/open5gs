/*
 * nf_service_version.h
 *
 *
 */

#ifndef _ogs_sbi_nf_service_version_H_
#define _ogs_sbi_nf_service_version_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_nf_service_version_s ogs_sbi_nf_service_version_t;
typedef struct ogs_sbi_nf_service_version_s {
    char *api_version_in_uri;
    char *api_full_version;
    char *expiry;
} ogs_sbi_nf_service_version_t;

ogs_sbi_nf_service_version_t *ogs_sbi_nf_service_version_create(
    char *api_version_in_uri,
    char *api_full_version,
    char *expiry
    );
void ogs_sbi_nf_service_version_free(ogs_sbi_nf_service_version_t *nf_service_version);
ogs_sbi_nf_service_version_t *ogs_sbi_nf_service_version_parseFromJSON(cJSON *nf_service_versionJSON);
cJSON *ogs_sbi_nf_service_version_convertToJSON(ogs_sbi_nf_service_version_t *nf_service_version);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_nf_service_version_H_ */

