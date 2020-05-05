/*
 * links_value_schema.h
 *
 *
 */

#ifndef _ogs_sbi_links_value_schema_H_
#define _ogs_sbi_links_value_schema_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "link.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_links_value_schema_s ogs_sbi_links_value_schema_t;
typedef struct ogs_sbi_links_value_schema_s {
    char *href;
} ogs_sbi_links_value_schema_t;

ogs_sbi_links_value_schema_t *ogs_sbi_links_value_schema_create(
    char *href
    );
void ogs_sbi_links_value_schema_free(ogs_sbi_links_value_schema_t *links_value_schema);
ogs_sbi_links_value_schema_t *ogs_sbi_links_value_schema_parseFromJSON(cJSON *links_value_schemaJSON);
cJSON *ogs_sbi_links_value_schema_convertToJSON(ogs_sbi_links_value_schema_t *links_value_schema);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_links_value_schema_H_ */

