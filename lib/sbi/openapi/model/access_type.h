/*
 * access_type.h
 *
 *
 */

#ifndef _ogs_sbi_access_type_H_
#define _ogs_sbi_access_type_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { ogs_sbi_access_type_NULL = 0, ogs_sbi_access_type_3GPP_ACCESS, ogs_sbi_access_type_NON_3GPP_ACCESS } ogs_sbi_access_type_e;

char* ogs_sbi_access_type_ToString(ogs_sbi_access_type_e access_type);

ogs_sbi_access_type_e ogs_sbi_access_type_FromString(char* access_type);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_access_type_H_ */

