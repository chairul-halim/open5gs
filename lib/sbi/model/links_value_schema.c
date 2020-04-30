#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "links_value_schema.h"



links_value_schema_t *links_value_schema_create(
    char *href
    ) {
    links_value_schema_t *links_value_schema_local_var = malloc(sizeof(links_value_schema_t));
    if (!links_value_schema_local_var) {
        return NULL;
    }
    links_value_schema_local_var->href = href;

    return links_value_schema_local_var;
}


void links_value_schema_free(links_value_schema_t *links_value_schema) {
    if(NULL == links_value_schema){
        return ;
    }
    listEntry_t *listEntry;
    free(links_value_schema->href);
    free(links_value_schema);
}

cJSON *links_value_schema_convertToJSON(links_value_schema_t *links_value_schema) {
    cJSON *item = cJSON_CreateObject();

    // links_value_schema->href
    if(links_value_schema->href) { 
    if(cJSON_AddStringToObject(item, "href", links_value_schema->href) == NULL) {
    goto fail; //String
    }
     } 

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

links_value_schema_t *links_value_schema_parseFromJSON(cJSON *links_value_schemaJSON){

    links_value_schema_t *links_value_schema_local_var = NULL;

    // links_value_schema->href
    cJSON *href = cJSON_GetObjectItemCaseSensitive(links_value_schemaJSON, "href");
    if (href) { 
    if(!cJSON_IsString(href))
    {
    goto end; //String
    }
    }


    links_value_schema_local_var = links_value_schema_create (
        href ? strdup(href->valuestring) : NULL
        );

    return links_value_schema_local_var;
end:
    return NULL;

}
