/*
 * tai.h
 *
 *
 */

#ifndef _ogs_sbi_tai_H_
#define _ogs_sbi_tai_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "plmn_id.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_tai_s ogs_sbi_tai_t;
typedef struct ogs_sbi_tai_s {
    struct ogs_sbi_plmn_id_s *plmn_id;
    char *tac;
} ogs_sbi_tai_t;

ogs_sbi_tai_t *ogs_sbi_tai_create(
    ogs_sbi_plmn_id_t *plmn_id,
    char *tac
    );
void ogs_sbi_tai_free(ogs_sbi_tai_t *tai);
ogs_sbi_tai_t *ogs_sbi_tai_parseFromJSON(cJSON *taiJSON);
cJSON *ogs_sbi_tai_convertToJSON(ogs_sbi_tai_t *tai);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_tai_H_ */

