/*
 * guami.h
 *
 *
 */

#ifndef _ogs_sbi_guami_H_
#define _ogs_sbi_guami_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "plmn_id.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_guami_s ogs_sbi_guami_t;
typedef struct ogs_sbi_guami_s {
    struct ogs_sbi_plmn_id_s *plmn_id;
    char *amf_id;
} ogs_sbi_guami_t;

ogs_sbi_guami_t *ogs_sbi_guami_create(
    ogs_sbi_plmn_id_t *plmn_id,
    char *amf_id
    );
void ogs_sbi_guami_free(ogs_sbi_guami_t *guami);
ogs_sbi_guami_t *ogs_sbi_guami_parseFromJSON(cJSON *guamiJSON);
cJSON *ogs_sbi_guami_convertToJSON(ogs_sbi_guami_t *guami);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_guami_H_ */

