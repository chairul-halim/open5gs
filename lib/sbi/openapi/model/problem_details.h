/*
 * problem_details.h
 *
 *
 */

#ifndef _ogs_sbi_problem_details_H_
#define _ogs_sbi_problem_details_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "invalid_param.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_problem_details_s ogs_sbi_problem_details_t;
typedef struct ogs_sbi_problem_details_s {
    char *type;
    char *title;
    int status;
    char *detail;
    char *instance;
    char *cause;
    ogs_sbi_list_t *invalid_params;
    char *supported_features;
} ogs_sbi_problem_details_t;

ogs_sbi_problem_details_t *ogs_sbi_problem_details_create(
    char *type,
    char *title,
    int status,
    char *detail,
    char *instance,
    char *cause,
    ogs_sbi_list_t *invalid_params,
    char *supported_features
    );
void ogs_sbi_problem_details_free(ogs_sbi_problem_details_t *problem_details);
ogs_sbi_problem_details_t *ogs_sbi_problem_details_parseFromJSON(cJSON *problem_detailsJSON);
cJSON *ogs_sbi_problem_details_convertToJSON(ogs_sbi_problem_details_t *problem_details);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_problem_details_H_ */

