/*
 * nf_status.h
 *
 *
 */

#ifndef _ogs_sbi_nf_status_H_
#define _ogs_sbi_nf_status_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { ogs_sbi_nf_status_NULL = 0, ogs_sbi_nf_status_REGISTERED, ogs_sbi_nf_status_SUSPENDED, ogs_sbi_nf_status_UNDISCOVERABLE } ogs_sbi_nf_status_e;

char* ogs_sbi_nf_status_ToString(ogs_sbi_nf_status_e nf_status);

ogs_sbi_nf_status_e ogs_sbi_nf_status_FromString(char* nf_status);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_nf_status_H_ */

