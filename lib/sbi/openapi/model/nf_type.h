/*
 * nf_type.h
 *
 *
 */

#ifndef _ogs_sbi_nf_type_H_
#define _ogs_sbi_nf_type_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { ogs_sbi_nf_type_NULL = 0, ogs_sbi_nf_type_NRF, ogs_sbi_nf_type_UDM, ogs_sbi_nf_type_AMF, ogs_sbi_nf_type_SMF, ogs_sbi_nf_type_AUSF, ogs_sbi_nf_type_NEF, ogs_sbi_nf_type_PCF, ogs_sbi_nf_type_SMSF, ogs_sbi_nf_type_NSSF, ogs_sbi_nf_type_UDR, ogs_sbi_nf_type_LMF, ogs_sbi_nf_type_GMLC, ogs_sbi_nf_type_5G_EIR, ogs_sbi_nf_type_SEPP, ogs_sbi_nf_type_UPF, ogs_sbi_nf_type_N3IWF, ogs_sbi_nf_type_AF, ogs_sbi_nf_type_UDSF, ogs_sbi_nf_type_BSF, ogs_sbi_nf_type_CHF, ogs_sbi_nf_type_NWDAF } ogs_sbi_nf_type_e;

char* ogs_sbi_nf_type_ToString(ogs_sbi_nf_type_e nf_type);

ogs_sbi_nf_type_e ogs_sbi_nf_type_FromString(char* nf_type);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_nf_type_H_ */

