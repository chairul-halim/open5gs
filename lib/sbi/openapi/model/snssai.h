/*
 * snssai.h
 *
 *
 */

#ifndef _ogs_sbi_snssai_H_
#define _ogs_sbi_snssai_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_snssai_s ogs_sbi_snssai_t;
typedef struct ogs_sbi_snssai_s {
    int sst;
    char *sd;
} ogs_sbi_snssai_t;

ogs_sbi_snssai_t *ogs_sbi_snssai_create(
    int sst,
    char *sd
    );
void ogs_sbi_snssai_free(ogs_sbi_snssai_t *snssai);
ogs_sbi_snssai_t *ogs_sbi_snssai_parseFromJSON(cJSON *snssaiJSON);
cJSON *ogs_sbi_snssai_convertToJSON(ogs_sbi_snssai_t *snssai);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_snssai_H_ */

