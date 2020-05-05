/*
 * service_name.h
 *
 *
 */

#ifndef _ogs_sbi_service_name_H_
#define _ogs_sbi_service_name_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_service_name_s ogs_sbi_service_name_t;
typedef struct ogs_sbi_service_name_s {
} ogs_sbi_service_name_t;

ogs_sbi_service_name_t *ogs_sbi_service_name_create(
    );
void ogs_sbi_service_name_free(ogs_sbi_service_name_t *service_name);
ogs_sbi_service_name_t *ogs_sbi_service_name_parseFromJSON(cJSON *service_nameJSON);
cJSON *ogs_sbi_service_name_convertToJSON(ogs_sbi_service_name_t *service_name);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_service_name_H_ */

