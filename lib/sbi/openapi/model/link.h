/*
 * link.h
 *
 *
 */

#ifndef _ogs_sbi_link_H_
#define _ogs_sbi_link_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_link_s ogs_sbi_link_t;
typedef struct ogs_sbi_link_s {
    char *href;
} ogs_sbi_link_t;

ogs_sbi_link_t *ogs_sbi_link_create(
    char *href
    );
void ogs_sbi_link_free(ogs_sbi_link_t *link);
ogs_sbi_link_t *ogs_sbi_link_parseFromJSON(cJSON *linkJSON);
cJSON *ogs_sbi_link_convertToJSON(ogs_sbi_link_t *link);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_link_H_ */

