
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "transport_protocol.h"

ogs_sbi_transport_protocol_t *ogs_sbi_transport_protocol_create(
    )
{
    ogs_sbi_transport_protocol_t *transport_protocol_local_var = ogs_malloc(sizeof(ogs_sbi_transport_protocol_t));
    if (!transport_protocol_local_var) {
        return NULL;
    }

    return transport_protocol_local_var;
}

void ogs_sbi_transport_protocol_free(ogs_sbi_transport_protocol_t *transport_protocol)
{
    if (NULL == transport_protocol) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(transport_protocol);
}

cJSON *ogs_sbi_transport_protocol_convertToJSON(ogs_sbi_transport_protocol_t *transport_protocol)
{
    cJSON *item = cJSON_CreateObject();
    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_transport_protocol_t *ogs_sbi_transport_protocol_parseFromJSON(cJSON *transport_protocolJSON)
{
    ogs_sbi_transport_protocol_t *transport_protocol_local_var = NULL;
    transport_protocol_local_var = ogs_sbi_transport_protocol_create (
        );

    return transport_protocol_local_var;
end:
    return NULL;
}

