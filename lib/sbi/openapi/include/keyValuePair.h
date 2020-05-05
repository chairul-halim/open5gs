#ifndef OGS_SBI_MAP_H
#define OGS_SBI_MAP_H

#include "ogs-core.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_map_s {
    char *key;
    void *value;
} ogs_sbi_map_t;

ogs_sbi_map_t *ogs_sbi_map_create(char *key, void *value);

ogs_sbi_map_t *ogs_sbi_map_create_allocate(char *key, double value);

void ogs_sbi_map_free(ogs_sbi_map_t *ogs_sbi_map);

#ifdef __cplusplus
}
#endif

#endif /* OGS_SBI_MAP_H */
