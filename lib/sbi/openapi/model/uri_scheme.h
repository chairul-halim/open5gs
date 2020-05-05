/*
 * uri_scheme.h
 *
 *
 */

#ifndef _ogs_sbi_uri_scheme_H_
#define _ogs_sbi_uri_scheme_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_uri_scheme_s ogs_sbi_uri_scheme_t;
typedef struct ogs_sbi_uri_scheme_s {
} ogs_sbi_uri_scheme_t;

ogs_sbi_uri_scheme_t *ogs_sbi_uri_scheme_create(
    );
void ogs_sbi_uri_scheme_free(ogs_sbi_uri_scheme_t *uri_scheme);
ogs_sbi_uri_scheme_t *ogs_sbi_uri_scheme_parseFromJSON(cJSON *uri_schemeJSON);
cJSON *ogs_sbi_uri_scheme_convertToJSON(ogs_sbi_uri_scheme_t *uri_scheme);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_uri_scheme_H_ */

