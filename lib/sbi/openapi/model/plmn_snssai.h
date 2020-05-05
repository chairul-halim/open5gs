/*
 * plmn_snssai.h
 *
 *
 */

#ifndef _ogs_sbi_plmn_snssai_H_
#define _ogs_sbi_plmn_snssai_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "plmn_id.h"
#include "snssai.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_plmn_snssai_s ogs_sbi_plmn_snssai_t;
typedef struct ogs_sbi_plmn_snssai_s {
    struct ogs_sbi_plmn_id_s *plmn_id;
    ogs_sbi_list_t *s_nssai_list;
} ogs_sbi_plmn_snssai_t;

ogs_sbi_plmn_snssai_t *ogs_sbi_plmn_snssai_create(
    ogs_sbi_plmn_id_t *plmn_id,
    ogs_sbi_list_t *s_nssai_list
    );
void ogs_sbi_plmn_snssai_free(ogs_sbi_plmn_snssai_t *plmn_snssai);
ogs_sbi_plmn_snssai_t *ogs_sbi_plmn_snssai_parseFromJSON(cJSON *plmn_snssaiJSON);
cJSON *ogs_sbi_plmn_snssai_convertToJSON(ogs_sbi_plmn_snssai_t *plmn_snssai);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_plmn_snssai_H_ */

