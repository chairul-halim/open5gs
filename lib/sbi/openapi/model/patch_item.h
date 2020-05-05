/*
 * patch_item.h
 *
 *
 */

#ifndef _ogs_sbi_patch_item_H_
#define _ogs_sbi_patch_item_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "patch_operation.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_patch_item_s ogs_sbi_patch_item_t;
typedef struct ogs_sbi_patch_item_s {
    struct ogs_sbi_patch_operation_s *op;
    char *path;
    char *from;
    char *value;
} ogs_sbi_patch_item_t;

ogs_sbi_patch_item_t *ogs_sbi_patch_item_create(
    ogs_sbi_patch_operation_t *op,
    char *path,
    char *from,
    char *value
    );
void ogs_sbi_patch_item_free(ogs_sbi_patch_item_t *patch_item);
ogs_sbi_patch_item_t *ogs_sbi_patch_item_parseFromJSON(cJSON *patch_itemJSON);
cJSON *ogs_sbi_patch_item_convertToJSON(ogs_sbi_patch_item_t *patch_item);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_patch_item_H_ */

