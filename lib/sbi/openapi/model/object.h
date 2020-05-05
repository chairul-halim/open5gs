#ifndef OGS_SBI_OBJECT_H
#define OGS_SBI_OBJECT_H

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_object_s {
    void *temporary;
} ogs_sbi_object_t;

ogs_sbi_object_t *ogs_sbi_object_create(void);

void ogs_sbi_object_free(ogs_sbi_object_t *object);

ogs_sbi_object_t *ogs_sbi_object_parseFromJSON(cJSON *objectJSON);

cJSON *ogs_sbi_object_convertToJSON(ogs_sbi_object_t *object);

#ifdef __cplusplus
}
#endif

#endif /* OGS_SBI_OBJECT_H */
