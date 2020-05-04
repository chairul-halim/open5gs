#include <stdlib.h>
#include <string.h>
#include "../include/keyValuePair.h"

ogs_sbi_map_t *ogs_sbi_map_create(char *key, void *value)
{
    ogs_sbi_map_t *ogs_sbi_map =  ogs_malloc(sizeof(ogs_sbi_map_t));
    ogs_sbi_map->key = key;
    ogs_sbi_map->value = value;
    return ogs_sbi_map;
}

ogs_sbi_map_t *ogs_sbi_map_create_allocate(char *key, double value)
{
    double* boolpointer = ogs_malloc(sizeof(value));
    memcpy(boolpointer, &value, sizeof(value));
    return ogs_sbi_map_create(key, boolpointer);
}

void ogs_sbi_map_free(ogs_sbi_map_t *ogs_sbi_map)
{
    ogs_free(ogs_sbi_map);
}