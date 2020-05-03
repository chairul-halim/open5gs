/*
 * change_type.h
 *
 *
 */

#ifndef _ogs_sbi_change_type_H_
#define _ogs_sbi_change_type_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_change_type_s ogs_sbi_change_type_t;
typedef struct ogs_sbi_change_type_s {
} ogs_sbi_change_type_t;

ogs_sbi_change_type_t *ogs_sbi_change_type_create(
    );
void ogs_sbi_change_type_free(ogs_sbi_change_type_t *change_type);
ogs_sbi_change_type_t *ogs_sbi_change_type_parseFromJSON(cJSON *change_typeJSON);
cJSON *ogs_sbi_change_type_convertToJSON(ogs_sbi_change_type_t *change_type);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_change_type_H_ */

