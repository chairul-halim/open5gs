/*
 * service_name_cond.h
 *
 *
 */

#ifndef _ogs_sbi_service_name_cond_H_
#define _ogs_sbi_service_name_cond_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "service_name.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_service_name_cond_s ogs_sbi_service_name_cond_t;
typedef struct ogs_sbi_service_name_cond_s {
    struct ogs_sbi_service_name_s *service_name;
} ogs_sbi_service_name_cond_t;

ogs_sbi_service_name_cond_t *ogs_sbi_service_name_cond_create(
    ogs_sbi_service_name_t *service_name
    );
void ogs_sbi_service_name_cond_free(ogs_sbi_service_name_cond_t *service_name_cond);
ogs_sbi_service_name_cond_t *ogs_sbi_service_name_cond_parseFromJSON(cJSON *service_name_condJSON);
cJSON *ogs_sbi_service_name_cond_convertToJSON(ogs_sbi_service_name_cond_t *service_name_cond);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_service_name_cond_H_ */

