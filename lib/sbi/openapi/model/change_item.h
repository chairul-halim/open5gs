/*
 * change_item.h
 *
 *
 */

#ifndef _ogs_sbi_change_item_H_
#define _ogs_sbi_change_item_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "change_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_change_item_s ogs_sbi_change_item_t;
typedef struct ogs_sbi_change_item_s {
    struct ogs_sbi_change_type_s *op;
    char *path;
    char *from;
    char *orig_value;
    char *new_value;
} ogs_sbi_change_item_t;

ogs_sbi_change_item_t *ogs_sbi_change_item_create(
    ogs_sbi_change_type_t *op,
    char *path,
    char *from,
    char *orig_value,
    char *new_value
    );
void ogs_sbi_change_item_free(ogs_sbi_change_item_t *change_item);
ogs_sbi_change_item_t *ogs_sbi_change_item_parseFromJSON(cJSON *change_itemJSON);
cJSON *ogs_sbi_change_item_convertToJSON(ogs_sbi_change_item_t *change_item);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_change_item_H_ */

