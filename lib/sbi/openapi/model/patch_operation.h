/*
 * patch_operation.h
 *
 *
 */

#ifndef _ogs_sbi_patch_operation_H_
#define _ogs_sbi_patch_operation_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_patch_operation_s ogs_sbi_patch_operation_t;
typedef struct ogs_sbi_patch_operation_s {
} ogs_sbi_patch_operation_t;

ogs_sbi_patch_operation_t *ogs_sbi_patch_operation_create(
    );
void ogs_sbi_patch_operation_free(ogs_sbi_patch_operation_t *patch_operation);
ogs_sbi_patch_operation_t *ogs_sbi_patch_operation_parseFromJSON(cJSON *patch_operationJSON);
cJSON *ogs_sbi_patch_operation_convertToJSON(ogs_sbi_patch_operation_t *patch_operation);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_patch_operation_H_ */

