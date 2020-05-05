
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "subscription_data.h"

ogs_sbi_subscription_data_t *ogs_sbi_subscription_data_create(
    char *nf_status_notification_uri,
    char *req_nf_instance_id,
    char *subscription_id,
    char *validity_time,
    ogs_sbi_list_t *req_notif_events,
    ogs_sbi_plmn_id_t *plmn_id,
    ogs_sbi_notif_condition_t *notif_condition,
    ogs_sbi_nf_type_e req_nf_type,
    char *req_nf_fqdn,
    ogs_sbi_list_t *req_snssais
    )
{
    ogs_sbi_subscription_data_t *subscription_data_local_var = ogs_malloc(sizeof(ogs_sbi_subscription_data_t));
    if (!subscription_data_local_var) {
        return NULL;
    }
    subscription_data_local_var->nf_status_notification_uri = nf_status_notification_uri;
    subscription_data_local_var->req_nf_instance_id = req_nf_instance_id;
    subscription_data_local_var->subscription_id = subscription_id;
    subscription_data_local_var->validity_time = validity_time;
    subscription_data_local_var->req_notif_events = req_notif_events;
    subscription_data_local_var->plmn_id = plmn_id;
    subscription_data_local_var->notif_condition = notif_condition;
    subscription_data_local_var->req_nf_type = req_nf_type;
    subscription_data_local_var->req_nf_fqdn = req_nf_fqdn;
    subscription_data_local_var->req_snssais = req_snssais;

    return subscription_data_local_var;
}

void ogs_sbi_subscription_data_free(ogs_sbi_subscription_data_t *subscription_data)
{
    if (NULL == subscription_data) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(subscription_data->nf_status_notification_uri);
    ogs_free(subscription_data->req_nf_instance_id);
    ogs_free(subscription_data->subscription_id);
    ogs_free(subscription_data->validity_time);
    ogs_sbi_list_for_each(node, subscription_data->req_notif_events) {
        ogs_sbi_notification_event_type_free(node->data);
    }
    ogs_sbi_list_free(subscription_data->req_notif_events);
    ogs_sbi_plmn_id_free(subscription_data->plmn_id);
    ogs_sbi_notif_condition_free(subscription_data->notif_condition);
    ogs_free(subscription_data->req_nf_fqdn);
    ogs_sbi_list_for_each(node, subscription_data->req_snssais) {
        ogs_sbi_snssai_free(node->data);
    }
    ogs_sbi_list_free(subscription_data->req_snssais);
    ogs_free(subscription_data);
}

cJSON *ogs_sbi_subscription_data_convertToJSON(ogs_sbi_subscription_data_t *subscription_data)
{
    cJSON *item = cJSON_CreateObject();
    if (!subscription_data->nf_status_notification_uri) {
        goto fail;
    }
    if (cJSON_AddStringToObject(item, "nfStatusNotificationUri", subscription_data->nf_status_notification_uri) == NULL) {
        goto fail;
    }

    if (subscription_data->req_nf_instance_id) {
        if (cJSON_AddStringToObject(item, "reqNfInstanceId", subscription_data->req_nf_instance_id) == NULL) {
            goto fail;
        }
    }

    if (!subscription_data->subscription_id) {
        goto fail;
    }
    if (cJSON_AddStringToObject(item, "subscriptionId", subscription_data->subscription_id) == NULL) {
        goto fail;
    }

    if (subscription_data->validity_time) {
        if (cJSON_AddStringToObject(item, "validityTime", subscription_data->validity_time) == NULL) {
            goto fail;
        }
    }

    if (subscription_data->req_notif_events) {
        cJSON *req_notif_events = cJSON_AddArrayToObject(item, "reqNotifEvents");
        if (req_notif_events == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *req_notif_events_node;
        if (subscription_data->req_notif_events) {
            ogs_sbi_list_for_each(req_notif_events_node, subscription_data->req_notif_events) {
                cJSON *itemLocal = ogs_sbi_notification_event_type_convertToJSON(req_notif_events_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(req_notif_events, itemLocal);
            }
        }
    }

    if (subscription_data->plmn_id) {
        cJSON *plmn_id_local_JSON = ogs_sbi_plmn_id_convertToJSON(subscription_data->plmn_id);
        if (plmn_id_local_JSON == NULL) {
            goto fail;
        }
        cJSON_AddItemToObject(item, "plmnId", plmn_id_local_JSON);
        if (item->child == NULL) {
            goto fail;
        }
    }

    if (subscription_data->notif_condition) {
        cJSON *notif_condition_local_JSON = ogs_sbi_notif_condition_convertToJSON(subscription_data->notif_condition);
        if (notif_condition_local_JSON == NULL) {
            goto fail;
        }
        cJSON_AddItemToObject(item, "notifCondition", notif_condition_local_JSON);
        if (item->child == NULL) {
            goto fail;
        }
    }

    if (subscription_data->req_nf_type) {
        if (cJSON_AddStringToObject(item, "reqNfType", ogs_sbi_nf_type_ToString(subscription_data->req_nf_type)) == NULL) {
            goto fail;
        }
    }

    if (subscription_data->req_nf_fqdn) {
        if (cJSON_AddStringToObject(item, "reqNfFqdn", subscription_data->req_nf_fqdn) == NULL) {
            goto fail;
        }
    }

    if (subscription_data->req_snssais) {
        cJSON *req_snssais = cJSON_AddArrayToObject(item, "reqSnssais");
        if (req_snssais == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *req_snssais_node;
        if (subscription_data->req_snssais) {
            ogs_sbi_list_for_each(req_snssais_node, subscription_data->req_snssais) {
                cJSON *itemLocal = ogs_sbi_snssai_convertToJSON(req_snssais_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(req_snssais, itemLocal);
            }
        }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_subscription_data_t *ogs_sbi_subscription_data_parseFromJSON(cJSON *subscription_dataJSON)
{
    ogs_sbi_subscription_data_t *subscription_data_local_var = NULL;
    cJSON *nf_status_notification_uri = cJSON_GetObjectItemCaseSensitive(subscription_dataJSON, "nfStatusNotificationUri");
    if (!nf_status_notification_uri) {
        goto end;
    }


    if (!cJSON_IsString(nf_status_notification_uri))
    {
        goto end;
    }

    cJSON *req_nf_instance_id = cJSON_GetObjectItemCaseSensitive(subscription_dataJSON, "reqNfInstanceId");

    if (req_nf_instance_id) {
        if (!cJSON_IsString(req_nf_instance_id))
        {
            goto end;
        }
    }

    cJSON *subscription_id = cJSON_GetObjectItemCaseSensitive(subscription_dataJSON, "subscriptionId");
    if (!subscription_id) {
        goto end;
    }


    if (!cJSON_IsString(subscription_id))
    {
        goto end;
    }

    cJSON *validity_time = cJSON_GetObjectItemCaseSensitive(subscription_dataJSON, "validityTime");

    if (validity_time) {
        if (!cJSON_IsString(validity_time)) {
            goto end;
        }
    }

    cJSON *req_notif_events = cJSON_GetObjectItemCaseSensitive(subscription_dataJSON, "reqNotifEvents");

    ogs_sbi_list_t *req_notif_eventsList;
    if (req_notif_events) {
        cJSON *req_notif_events_local_nonprimitive;
        if (!cJSON_IsArray(req_notif_events)) {
            goto end;
        }

        req_notif_eventsList = ogs_sbi_list_create();

        cJSON_ArrayForEach(req_notif_events_local_nonprimitive,req_notif_events ) {
            if (!cJSON_IsObject(req_notif_events_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_notification_event_type_t *req_notif_eventsItem = ogs_sbi_notification_event_type_parseFromJSON(req_notif_events_local_nonprimitive);

            ogs_sbi_list_add(req_notif_eventsList, req_notif_eventsItem);
        }
    }

    cJSON *plmn_id = cJSON_GetObjectItemCaseSensitive(subscription_dataJSON, "plmnId");

    ogs_sbi_plmn_id_t *plmn_id_local_nonprim = NULL;
    if (plmn_id) {
        plmn_id_local_nonprim = ogs_sbi_plmn_id_parseFromJSON(plmn_id);
    }

    cJSON *notif_condition = cJSON_GetObjectItemCaseSensitive(subscription_dataJSON, "notifCondition");

    ogs_sbi_notif_condition_t *notif_condition_local_nonprim = NULL;
    if (notif_condition) {
        notif_condition_local_nonprim = ogs_sbi_notif_condition_parseFromJSON(notif_condition);
    }

    cJSON *req_nf_type = cJSON_GetObjectItemCaseSensitive(subscription_dataJSON, "reqNfType");

    ogs_sbi_nf_type_e req_nf_typeVariable;
    if (req_nf_type) {
        if (!cJSON_IsString(req_nf_type)) {
            goto end;
        }
        req_nf_typeVariable = ogs_sbi_nf_type_FromString(req_nf_type->valuestring);
    }

    cJSON *req_nf_fqdn = cJSON_GetObjectItemCaseSensitive(subscription_dataJSON, "reqNfFqdn");

    if (req_nf_fqdn) {
        if (!cJSON_IsString(req_nf_fqdn))
        {
            goto end;
        }
    }

    cJSON *req_snssais = cJSON_GetObjectItemCaseSensitive(subscription_dataJSON, "reqSnssais");

    ogs_sbi_list_t *req_snssaisList;
    if (req_snssais) {
        cJSON *req_snssais_local_nonprimitive;
        if (!cJSON_IsArray(req_snssais)) {
            goto end;
        }

        req_snssaisList = ogs_sbi_list_create();

        cJSON_ArrayForEach(req_snssais_local_nonprimitive,req_snssais ) {
            if (!cJSON_IsObject(req_snssais_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_snssai_t *req_snssaisItem = ogs_sbi_snssai_parseFromJSON(req_snssais_local_nonprimitive);

            ogs_sbi_list_add(req_snssaisList, req_snssaisItem);
        }
    }

    subscription_data_local_var = ogs_sbi_subscription_data_create (
        ogs_strdup(nf_status_notification_uri->valuestring),
        req_nf_instance_id ? ogs_strdup(req_nf_instance_id->valuestring) : NULL,
        ogs_strdup(subscription_id->valuestring),
        validity_time ? ogs_strdup(validity_time->valuestring) : NULL,
        req_notif_events ? req_notif_eventsList : NULL,
        plmn_id ? plmn_id_local_nonprim : NULL,
        notif_condition ? notif_condition_local_nonprim : NULL,
        req_nf_type ? req_nf_typeVariable : -1,
        req_nf_fqdn ? ogs_strdup(req_nf_fqdn->valuestring) : NULL,
        req_snssais ? req_snssaisList : NULL
        );

    return subscription_data_local_var;
end:
    return NULL;
}

