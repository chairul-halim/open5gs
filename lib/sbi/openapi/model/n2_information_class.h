/*
 * n2_information_class.h
 *
 *
 */

#ifndef _ogs_sbi_n2_information_class_H_
#define _ogs_sbi_n2_information_class_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_n2_information_class_s ogs_sbi_n2_information_class_t;
typedef struct ogs_sbi_n2_information_class_s {
} ogs_sbi_n2_information_class_t;

ogs_sbi_n2_information_class_t *ogs_sbi_n2_information_class_create(
    );
void ogs_sbi_n2_information_class_free(ogs_sbi_n2_information_class_t *n2_information_class);
ogs_sbi_n2_information_class_t *ogs_sbi_n2_information_class_parseFromJSON(cJSON *n2_information_classJSON);
cJSON *ogs_sbi_n2_information_class_convertToJSON(ogs_sbi_n2_information_class_t *n2_information_class);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_n2_information_class_H_ */

