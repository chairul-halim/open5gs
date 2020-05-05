/*
 * invalid_param.h
 *
 *
 */

#ifndef _ogs_sbi_invalid_param_H_
#define _ogs_sbi_invalid_param_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_invalid_param_s ogs_sbi_invalid_param_t;
typedef struct ogs_sbi_invalid_param_s {
    char *param;
    char *reason;
} ogs_sbi_invalid_param_t;

ogs_sbi_invalid_param_t *ogs_sbi_invalid_param_create(
    char *param,
    char *reason
    );
void ogs_sbi_invalid_param_free(ogs_sbi_invalid_param_t *invalid_param);
ogs_sbi_invalid_param_t *ogs_sbi_invalid_param_parseFromJSON(cJSON *invalid_paramJSON);
cJSON *ogs_sbi_invalid_param_convertToJSON(ogs_sbi_invalid_param_t *invalid_param);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_invalid_param_H_ */

