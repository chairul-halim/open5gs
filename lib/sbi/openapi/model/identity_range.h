/*
 * identity_range.h
 *
 *
 */

#ifndef _ogs_sbi_identity_range_H_
#define _ogs_sbi_identity_range_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_identity_range_s ogs_sbi_identity_range_t;
typedef struct ogs_sbi_identity_range_s {
    char *start;
    char *end;
    char *pattern;
} ogs_sbi_identity_range_t;

ogs_sbi_identity_range_t *ogs_sbi_identity_range_create(
    char *start,
    char *end,
    char *pattern
    );
void ogs_sbi_identity_range_free(ogs_sbi_identity_range_t *identity_range);
ogs_sbi_identity_range_t *ogs_sbi_identity_range_parseFromJSON(cJSON *identity_rangeJSON);
cJSON *ogs_sbi_identity_range_convertToJSON(ogs_sbi_identity_range_t *identity_range);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_identity_range_H_ */

