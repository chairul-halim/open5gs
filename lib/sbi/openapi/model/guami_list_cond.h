/*
 * guami_list_cond.h
 *
 *
 */

#ifndef _ogs_sbi_guami_list_cond_H_
#define _ogs_sbi_guami_list_cond_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "guami.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_guami_list_cond_s ogs_sbi_guami_list_cond_t;
typedef struct ogs_sbi_guami_list_cond_s {
    ogs_sbi_list_t *guami_list;
} ogs_sbi_guami_list_cond_t;

ogs_sbi_guami_list_cond_t *ogs_sbi_guami_list_cond_create(
    ogs_sbi_list_t *guami_list
    );
void ogs_sbi_guami_list_cond_free(ogs_sbi_guami_list_cond_t *guami_list_cond);
ogs_sbi_guami_list_cond_t *ogs_sbi_guami_list_cond_parseFromJSON(cJSON *guami_list_condJSON);
cJSON *ogs_sbi_guami_list_cond_convertToJSON(ogs_sbi_guami_list_cond_t *guami_list_cond);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_guami_list_cond_H_ */

