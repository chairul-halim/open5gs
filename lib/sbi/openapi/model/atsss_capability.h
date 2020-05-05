/*
 * atsss_capability.h
 *
 *
 */

#ifndef _ogs_sbi_atsss_capability_H_
#define _ogs_sbi_atsss_capability_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_atsss_capability_s ogs_sbi_atsss_capability_t;
typedef struct ogs_sbi_atsss_capability_s {
    int atsss_ll;
    int mptcp;
} ogs_sbi_atsss_capability_t;

ogs_sbi_atsss_capability_t *ogs_sbi_atsss_capability_create(
    int atsss_ll,
    int mptcp
    );
void ogs_sbi_atsss_capability_free(ogs_sbi_atsss_capability_t *atsss_capability);
ogs_sbi_atsss_capability_t *ogs_sbi_atsss_capability_parseFromJSON(cJSON *atsss_capabilityJSON);
cJSON *ogs_sbi_atsss_capability_convertToJSON(ogs_sbi_atsss_capability_t *atsss_capability);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_atsss_capability_H_ */

