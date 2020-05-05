/*
 * inline_response_200.h
 *
 *
 */

#ifndef _ogs_sbi_inline_response_200_H_
#define _ogs_sbi_inline_response_200_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "links_value_schema.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_inline_response_200_s ogs_sbi_inline_response_200_t;
typedef struct ogs_sbi_inline_response_200_s {
    ogs_sbi_list_t* _links;
} ogs_sbi_inline_response_200_t;

ogs_sbi_inline_response_200_t *ogs_sbi_inline_response_200_create(
    ogs_sbi_list_t* _links
    );
void ogs_sbi_inline_response_200_free(ogs_sbi_inline_response_200_t *inline_response_200);
ogs_sbi_inline_response_200_t *ogs_sbi_inline_response_200_parseFromJSON(cJSON *inline_response_200JSON);
cJSON *ogs_sbi_inline_response_200_convertToJSON(ogs_sbi_inline_response_200_t *inline_response_200);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_inline_response_200_H_ */

