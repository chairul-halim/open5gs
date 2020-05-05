/*
 * tai_range.h
 *
 *
 */

#ifndef _ogs_sbi_tai_range_H_
#define _ogs_sbi_tai_range_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "plmn_id.h"
#include "tac_range.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_tai_range_s ogs_sbi_tai_range_t;
typedef struct ogs_sbi_tai_range_s {
    struct ogs_sbi_plmn_id_s *plmn_id;
    ogs_sbi_list_t *tac_range_list;
} ogs_sbi_tai_range_t;

ogs_sbi_tai_range_t *ogs_sbi_tai_range_create(
    ogs_sbi_plmn_id_t *plmn_id,
    ogs_sbi_list_t *tac_range_list
    );
void ogs_sbi_tai_range_free(ogs_sbi_tai_range_t *tai_range);
ogs_sbi_tai_range_t *ogs_sbi_tai_range_parseFromJSON(cJSON *tai_rangeJSON);
cJSON *ogs_sbi_tai_range_convertToJSON(ogs_sbi_tai_range_t *tai_range);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_tai_range_H_ */

