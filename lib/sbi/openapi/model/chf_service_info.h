/*
 * chf_service_info.h
 *
 *
 */

#ifndef _ogs_sbi_chf_service_info_H_
#define _ogs_sbi_chf_service_info_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_chf_service_info_s ogs_sbi_chf_service_info_t;
typedef struct ogs_sbi_chf_service_info_s {
    char *primary_chf_service_instance;
    char *secondary_chf_service_instance;
} ogs_sbi_chf_service_info_t;

ogs_sbi_chf_service_info_t *ogs_sbi_chf_service_info_create(
    char *primary_chf_service_instance,
    char *secondary_chf_service_instance
    );
void ogs_sbi_chf_service_info_free(ogs_sbi_chf_service_info_t *chf_service_info);
ogs_sbi_chf_service_info_t *ogs_sbi_chf_service_info_parseFromJSON(cJSON *chf_service_infoJSON);
cJSON *ogs_sbi_chf_service_info_convertToJSON(ogs_sbi_chf_service_info_t *chf_service_info);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_chf_service_info_H_ */

