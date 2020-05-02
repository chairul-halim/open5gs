/*
 * plmn_id.h
 *
 *
 */

#ifndef _plmn_id_H_
#define _plmn_id_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

typedef struct plmn_id_t plmn_id_t;
typedef struct plmn_id_t {
    char *mcc;
    char *mnc;
} plmn_id_t;

plmn_id_t *plmn_id_create(
    char *mcc,
    char *mnc
    );
void plmn_id_free(plmn_id_t *plmn_id);
plmn_id_t *plmn_id_parseFromJSON(cJSON *plmn_idJSON);
cJSON *plmn_id_convertToJSON(plmn_id_t *plmn_id);
#endif /* _plmn_id_H_ */

