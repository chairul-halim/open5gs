/*
 * data_set_id.h
 *
 *
 */

#ifndef _ogs_sbi_data_set_id_H_
#define _ogs_sbi_data_set_id_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_data_set_id_s ogs_sbi_data_set_id_t;
typedef struct ogs_sbi_data_set_id_s {
} ogs_sbi_data_set_id_t;

ogs_sbi_data_set_id_t *ogs_sbi_data_set_id_create(
    );
void ogs_sbi_data_set_id_free(ogs_sbi_data_set_id_t *data_set_id);
ogs_sbi_data_set_id_t *ogs_sbi_data_set_id_parseFromJSON(cJSON *data_set_idJSON);
cJSON *ogs_sbi_data_set_id_convertToJSON(ogs_sbi_data_set_id_t *data_set_id);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_data_set_id_H_ */

