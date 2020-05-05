/*
 * nwdaf_info.h
 *
 *
 */

#ifndef _ogs_sbi_nwdaf_info_H_
#define _ogs_sbi_nwdaf_info_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "event_id.h"
#include "nwdaf_event.h"
#include "tai.h"
#include "tai_range.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_nwdaf_info_s ogs_sbi_nwdaf_info_t;
typedef struct ogs_sbi_nwdaf_info_s {
    ogs_sbi_list_t *event_ids;
    ogs_sbi_list_t *nwdaf_events;
    ogs_sbi_list_t *tai_list;
    ogs_sbi_list_t *tai_range_list;
} ogs_sbi_nwdaf_info_t;

ogs_sbi_nwdaf_info_t *ogs_sbi_nwdaf_info_create(
    ogs_sbi_list_t *event_ids,
    ogs_sbi_list_t *nwdaf_events,
    ogs_sbi_list_t *tai_list,
    ogs_sbi_list_t *tai_range_list
    );
void ogs_sbi_nwdaf_info_free(ogs_sbi_nwdaf_info_t *nwdaf_info);
ogs_sbi_nwdaf_info_t *ogs_sbi_nwdaf_info_parseFromJSON(cJSON *nwdaf_infoJSON);
cJSON *ogs_sbi_nwdaf_info_convertToJSON(ogs_sbi_nwdaf_info_t *nwdaf_info);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_nwdaf_info_H_ */

