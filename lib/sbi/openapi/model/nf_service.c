
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "nf_service.h"

ogs_sbi_nf_service_t *ogs_sbi_nf_service_create(
    char *service_instance_id,
    ogs_sbi_service_name_t *service_name,
    ogs_sbi_list_t *versions,
    ogs_sbi_uri_scheme_t *scheme,
    ogs_sbi_nf_service_status_t *nf_service_status,
    char *fqdn,
    char *inter_plmn_fqdn,
    ogs_sbi_list_t *ip_end_points,
    char *api_prefix,
    ogs_sbi_list_t *default_notification_subscriptions,
    ogs_sbi_list_t *allowed_plmns,
    ogs_sbi_list_t *allowed_nf_types,
    ogs_sbi_list_t *allowed_nf_domains,
    ogs_sbi_list_t *allowed_nssais,
    int priority,
    int capacity,
    int load,
    char *recovery_time,
    ogs_sbi_chf_service_info_t *chf_service_info,
    char *supported_features
    )
{
    ogs_sbi_nf_service_t *nf_service_local_var = ogs_malloc(sizeof(ogs_sbi_nf_service_t));
    if (!nf_service_local_var) {
        return NULL;
    }
    nf_service_local_var->service_instance_id = service_instance_id;
    nf_service_local_var->service_name = service_name;
    nf_service_local_var->versions = versions;
    nf_service_local_var->scheme = scheme;
    nf_service_local_var->nf_service_status = nf_service_status;
    nf_service_local_var->fqdn = fqdn;
    nf_service_local_var->inter_plmn_fqdn = inter_plmn_fqdn;
    nf_service_local_var->ip_end_points = ip_end_points;
    nf_service_local_var->api_prefix = api_prefix;
    nf_service_local_var->default_notification_subscriptions = default_notification_subscriptions;
    nf_service_local_var->allowed_plmns = allowed_plmns;
    nf_service_local_var->allowed_nf_types = allowed_nf_types;
    nf_service_local_var->allowed_nf_domains = allowed_nf_domains;
    nf_service_local_var->allowed_nssais = allowed_nssais;
    nf_service_local_var->priority = priority;
    nf_service_local_var->capacity = capacity;
    nf_service_local_var->load = load;
    nf_service_local_var->recovery_time = recovery_time;
    nf_service_local_var->chf_service_info = chf_service_info;
    nf_service_local_var->supported_features = supported_features;

    return nf_service_local_var;
}

void ogs_sbi_nf_service_free(ogs_sbi_nf_service_t *nf_service)
{
    if (NULL == nf_service) {
        return;
    }
    ogs_sbi_lnode_t *node;
    ogs_free(nf_service->service_instance_id);
    ogs_sbi_service_name_free(nf_service->service_name);
    ogs_sbi_list_for_each(node, nf_service->versions) {
        ogs_sbi_nf_service_version_free(node->data);
    }
    ogs_sbi_list_free(nf_service->versions);
    ogs_sbi_uri_scheme_free(nf_service->scheme);
    ogs_sbi_nf_service_status_free(nf_service->nf_service_status);
    ogs_free(nf_service->fqdn);
    ogs_free(nf_service->inter_plmn_fqdn);
    ogs_sbi_list_for_each(node, nf_service->ip_end_points) {
        ogs_sbi_ip_end_point_free(node->data);
    }
    ogs_sbi_list_free(nf_service->ip_end_points);
    ogs_free(nf_service->api_prefix);
    ogs_sbi_list_for_each(node, nf_service->default_notification_subscriptions) {
        ogs_sbi_default_notification_subscription_free(node->data);
    }
    ogs_sbi_list_free(nf_service->default_notification_subscriptions);
    ogs_sbi_list_for_each(node, nf_service->allowed_plmns) {
        ogs_sbi_plmn_id_free(node->data);
    }
    ogs_sbi_list_free(nf_service->allowed_plmns);
    ogs_sbi_list_free(nf_service->allowed_nf_types);
    ogs_sbi_list_for_each(node, nf_service->allowed_nf_domains) {
        ogs_free(node->data);
    }
    ogs_sbi_list_free(nf_service->allowed_nf_domains);
    ogs_sbi_list_for_each(node, nf_service->allowed_nssais) {
        ogs_sbi_snssai_free(node->data);
    }
    ogs_sbi_list_free(nf_service->allowed_nssais);
    ogs_free(nf_service->recovery_time);
    ogs_sbi_chf_service_info_free(nf_service->chf_service_info);
    ogs_free(nf_service->supported_features);
    ogs_free(nf_service);
}

cJSON *ogs_sbi_nf_service_convertToJSON(ogs_sbi_nf_service_t *nf_service)
{
    cJSON *item = cJSON_CreateObject();
    if (!nf_service->service_instance_id) {
        goto fail;
    }
    if (cJSON_AddStringToObject(item, "serviceInstanceId", nf_service->service_instance_id) == NULL) {
        goto fail;
    }

    if (!nf_service->service_name) {
        goto fail;
    }
    cJSON *service_name_local_JSON = ogs_sbi_service_name_convertToJSON(nf_service->service_name);
    if (service_name_local_JSON == NULL) {
        goto fail;
    }
    cJSON_AddItemToObject(item, "serviceName", service_name_local_JSON);
    if (item->child == NULL) {
        goto fail;
    }

    if (!nf_service->versions) {
        goto fail;
    }
    cJSON *versions = cJSON_AddArrayToObject(item, "versions");
    if (versions == NULL) {
        goto fail;
    }

    ogs_sbi_lnode_t *versions_node;
    if (nf_service->versions) {
        ogs_sbi_list_for_each(versions_node, nf_service->versions) {
            cJSON *itemLocal = ogs_sbi_nf_service_version_convertToJSON(versions_node->data);
            if (itemLocal == NULL) {
                goto fail;
            }
            cJSON_AddItemToArray(versions, itemLocal);
        }
    }

    if (!nf_service->scheme) {
        goto fail;
    }
    cJSON *scheme_local_JSON = ogs_sbi_uri_scheme_convertToJSON(nf_service->scheme);
    if (scheme_local_JSON == NULL) {
        goto fail;
    }
    cJSON_AddItemToObject(item, "scheme", scheme_local_JSON);
    if (item->child == NULL) {
        goto fail;
    }

    if (!nf_service->nf_service_status) {
        goto fail;
    }
    cJSON *nf_service_status_local_JSON = ogs_sbi_nf_service_status_convertToJSON(nf_service->nf_service_status);
    if (nf_service_status_local_JSON == NULL) {
        goto fail;
    }
    cJSON_AddItemToObject(item, "nfServiceStatus", nf_service_status_local_JSON);
    if (item->child == NULL) {
        goto fail;
    }

    if (nf_service->fqdn) {
        if (cJSON_AddStringToObject(item, "fqdn", nf_service->fqdn) == NULL) {
            goto fail;
        }
    }

    if (nf_service->inter_plmn_fqdn) {
        if (cJSON_AddStringToObject(item, "interPlmnFqdn", nf_service->inter_plmn_fqdn) == NULL) {
            goto fail;
        }
    }

    if (nf_service->ip_end_points) {
        cJSON *ip_end_points = cJSON_AddArrayToObject(item, "ipEndPoints");
        if (ip_end_points == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *ip_end_points_node;
        if (nf_service->ip_end_points) {
            ogs_sbi_list_for_each(ip_end_points_node, nf_service->ip_end_points) {
                cJSON *itemLocal = ogs_sbi_ip_end_point_convertToJSON(ip_end_points_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(ip_end_points, itemLocal);
            }
        }
    }

    if (nf_service->api_prefix) {
        if (cJSON_AddStringToObject(item, "apiPrefix", nf_service->api_prefix) == NULL) {
            goto fail;
        }
    }

    if (nf_service->default_notification_subscriptions) {
        cJSON *default_notification_subscriptions = cJSON_AddArrayToObject(item, "defaultNotificationSubscriptions");
        if (default_notification_subscriptions == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *default_notification_subscriptions_node;
        if (nf_service->default_notification_subscriptions) {
            ogs_sbi_list_for_each(default_notification_subscriptions_node, nf_service->default_notification_subscriptions) {
                cJSON *itemLocal = ogs_sbi_default_notification_subscription_convertToJSON(default_notification_subscriptions_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(default_notification_subscriptions, itemLocal);
            }
        }
    }

    if (nf_service->allowed_plmns) {
        cJSON *allowed_plmns = cJSON_AddArrayToObject(item, "allowedPlmns");
        if (allowed_plmns == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *allowed_plmns_node;
        if (nf_service->allowed_plmns) {
            ogs_sbi_list_for_each(allowed_plmns_node, nf_service->allowed_plmns) {
                cJSON *itemLocal = ogs_sbi_plmn_id_convertToJSON(allowed_plmns_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(allowed_plmns, itemLocal);
            }
        }
    }

    if (nf_service->allowed_nf_types) {
        cJSON *allowed_nf_types = cJSON_AddArrayToObject(item, "allowedNfTypes");
        if (allowed_nf_types == NULL) {
            goto fail;
        }
        ogs_sbi_lnode_t *allowed_nf_types_node;
        ogs_sbi_list_for_each(allowed_nf_types_node, nf_service->allowed_nf_types) {
            if (cJSON_AddStringToObject(allowed_nf_types, "", ogs_sbi_nf_type_ToString((ogs_sbi_nf_type_e)allowed_nf_types_node->data)) == NULL) {
                goto fail;
            }
        }
    }

    if (nf_service->allowed_nf_domains) {
        cJSON *allowed_nf_domains = cJSON_AddArrayToObject(item, "allowedNfDomains");
        if (allowed_nf_domains == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *allowed_nf_domains_node;
        ogs_sbi_list_for_each(allowed_nf_domains_node, nf_service->allowed_nf_domains) {
            if (cJSON_AddStringToObject(allowed_nf_domains, "", (char*)allowed_nf_domains_node->data) == NULL) {
                goto fail;
            }
        }
    }

    if (nf_service->allowed_nssais) {
        cJSON *allowed_nssais = cJSON_AddArrayToObject(item, "allowedNssais");
        if (allowed_nssais == NULL) {
            goto fail;
        }

        ogs_sbi_lnode_t *allowed_nssais_node;
        if (nf_service->allowed_nssais) {
            ogs_sbi_list_for_each(allowed_nssais_node, nf_service->allowed_nssais) {
                cJSON *itemLocal = ogs_sbi_snssai_convertToJSON(allowed_nssais_node->data);
                if (itemLocal == NULL) {
                    goto fail;
                }
                cJSON_AddItemToArray(allowed_nssais, itemLocal);
            }
        }
    }

    if (nf_service->priority) {
        if (cJSON_AddNumberToObject(item, "priority", nf_service->priority) == NULL) {
            goto fail;
        }
    }

    if (nf_service->capacity) {
        if (cJSON_AddNumberToObject(item, "capacity", nf_service->capacity) == NULL) {
            goto fail;
        }
    }

    if (nf_service->load) {
        if (cJSON_AddNumberToObject(item, "load", nf_service->load) == NULL) {
            goto fail;
        }
    }

    if (nf_service->recovery_time) {
        if (cJSON_AddStringToObject(item, "recoveryTime", nf_service->recovery_time) == NULL) {
            goto fail;
        }
    }

    if (nf_service->chf_service_info) {
        cJSON *chf_service_info_local_JSON = ogs_sbi_chf_service_info_convertToJSON(nf_service->chf_service_info);
        if (chf_service_info_local_JSON == NULL) {
            goto fail;
        }
        cJSON_AddItemToObject(item, "chfServiceInfo", chf_service_info_local_JSON);
        if (item->child == NULL) {
            goto fail;
        }
    }

    if (nf_service->supported_features) {
        if (cJSON_AddStringToObject(item, "supportedFeatures", nf_service->supported_features) == NULL) {
            goto fail;
        }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

ogs_sbi_nf_service_t *ogs_sbi_nf_service_parseFromJSON(cJSON *nf_serviceJSON)
{
    ogs_sbi_nf_service_t *nf_service_local_var = NULL;
    cJSON *service_instance_id = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "serviceInstanceId");
    if (!service_instance_id) {
        goto end;
    }


    if (!cJSON_IsString(service_instance_id))
    {
        goto end;
    }

    cJSON *service_name = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "serviceName");
    if (!service_name) {
        goto end;
    }

    ogs_sbi_service_name_t *service_name_local_nonprim = NULL;

    service_name_local_nonprim = ogs_sbi_service_name_parseFromJSON(service_name);

    cJSON *versions = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "versions");
    if (!versions) {
        goto end;
    }

    ogs_sbi_list_t *versionsList;

    cJSON *versions_local_nonprimitive;
    if (!cJSON_IsArray(versions)) {
        goto end;
    }

    versionsList = ogs_sbi_list_create();

    cJSON_ArrayForEach(versions_local_nonprimitive,versions ) {
        if (!cJSON_IsObject(versions_local_nonprimitive)) {
            goto end;
        }
        ogs_sbi_nf_service_version_t *versionsItem = ogs_sbi_nf_service_version_parseFromJSON(versions_local_nonprimitive);

        ogs_sbi_list_add(versionsList, versionsItem);
    }

    cJSON *scheme = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "scheme");
    if (!scheme) {
        goto end;
    }

    ogs_sbi_uri_scheme_t *scheme_local_nonprim = NULL;

    scheme_local_nonprim = ogs_sbi_uri_scheme_parseFromJSON(scheme);

    cJSON *nf_service_status = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "nfServiceStatus");
    if (!nf_service_status) {
        goto end;
    }

    ogs_sbi_nf_service_status_t *nf_service_status_local_nonprim = NULL;

    nf_service_status_local_nonprim = ogs_sbi_nf_service_status_parseFromJSON(nf_service_status);

    cJSON *fqdn = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "fqdn");

    if (fqdn) {
        if (!cJSON_IsString(fqdn))
        {
            goto end;
        }
    }

    cJSON *inter_plmn_fqdn = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "interPlmnFqdn");

    if (inter_plmn_fqdn) {
        if (!cJSON_IsString(inter_plmn_fqdn))
        {
            goto end;
        }
    }

    cJSON *ip_end_points = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "ipEndPoints");

    ogs_sbi_list_t *ip_end_pointsList;
    if (ip_end_points) {
        cJSON *ip_end_points_local_nonprimitive;
        if (!cJSON_IsArray(ip_end_points)) {
            goto end;
        }

        ip_end_pointsList = ogs_sbi_list_create();

        cJSON_ArrayForEach(ip_end_points_local_nonprimitive,ip_end_points ) {
            if (!cJSON_IsObject(ip_end_points_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_ip_end_point_t *ip_end_pointsItem = ogs_sbi_ip_end_point_parseFromJSON(ip_end_points_local_nonprimitive);

            ogs_sbi_list_add(ip_end_pointsList, ip_end_pointsItem);
        }
    }

    cJSON *api_prefix = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "apiPrefix");

    if (api_prefix) {
        if (!cJSON_IsString(api_prefix))
        {
            goto end;
        }
    }

    cJSON *default_notification_subscriptions = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "defaultNotificationSubscriptions");

    ogs_sbi_list_t *default_notification_subscriptionsList;
    if (default_notification_subscriptions) {
        cJSON *default_notification_subscriptions_local_nonprimitive;
        if (!cJSON_IsArray(default_notification_subscriptions)) {
            goto end;
        }

        default_notification_subscriptionsList = ogs_sbi_list_create();

        cJSON_ArrayForEach(default_notification_subscriptions_local_nonprimitive,default_notification_subscriptions ) {
            if (!cJSON_IsObject(default_notification_subscriptions_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_default_notification_subscription_t *default_notification_subscriptionsItem = ogs_sbi_default_notification_subscription_parseFromJSON(default_notification_subscriptions_local_nonprimitive);

            ogs_sbi_list_add(default_notification_subscriptionsList, default_notification_subscriptionsItem);
        }
    }

    cJSON *allowed_plmns = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "allowedPlmns");

    ogs_sbi_list_t *allowed_plmnsList;
    if (allowed_plmns) {
        cJSON *allowed_plmns_local_nonprimitive;
        if (!cJSON_IsArray(allowed_plmns)) {
            goto end;
        }

        allowed_plmnsList = ogs_sbi_list_create();

        cJSON_ArrayForEach(allowed_plmns_local_nonprimitive,allowed_plmns ) {
            if (!cJSON_IsObject(allowed_plmns_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_plmn_id_t *allowed_plmnsItem = ogs_sbi_plmn_id_parseFromJSON(allowed_plmns_local_nonprimitive);

            ogs_sbi_list_add(allowed_plmnsList, allowed_plmnsItem);
        }
    }

    cJSON *allowed_nf_types = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "allowedNfTypes");

    ogs_sbi_list_t *allowed_nf_typesList;
    if (allowed_nf_types) {
        cJSON *allowed_nf_types_local_nonprimitive;
        if (!cJSON_IsArray(allowed_nf_types)) {
            goto end;
        }

        allowed_nf_typesList = ogs_sbi_list_create();

        cJSON_ArrayForEach(allowed_nf_types_local_nonprimitive, allowed_nf_types ) {
            if (!cJSON_IsString(allowed_nf_types_local_nonprimitive)) {
                goto end;
            }

            ogs_sbi_list_add(allowed_nf_typesList, (void *)ogs_sbi_nf_type_FromString(allowed_nf_types_local_nonprimitive->valuestring));
        }
    }

    cJSON *allowed_nf_domains = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "allowedNfDomains");

    ogs_sbi_list_t *allowed_nf_domainsList;
    if (allowed_nf_domains) {
        cJSON *allowed_nf_domains_local;
        if (!cJSON_IsArray(allowed_nf_domains)) {
            goto end;
        }
        allowed_nf_domainsList = ogs_sbi_list_create();

        cJSON_ArrayForEach(allowed_nf_domains_local, allowed_nf_domains) {
            if (!cJSON_IsString(allowed_nf_domains_local)) {
                goto end;
            }
            ogs_sbi_list_add(allowed_nf_domainsList, ogs_strdup(allowed_nf_domains_local->valuestring));
        }
    }

    cJSON *allowed_nssais = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "allowedNssais");

    ogs_sbi_list_t *allowed_nssaisList;
    if (allowed_nssais) {
        cJSON *allowed_nssais_local_nonprimitive;
        if (!cJSON_IsArray(allowed_nssais)) {
            goto end;
        }

        allowed_nssaisList = ogs_sbi_list_create();

        cJSON_ArrayForEach(allowed_nssais_local_nonprimitive,allowed_nssais ) {
            if (!cJSON_IsObject(allowed_nssais_local_nonprimitive)) {
                goto end;
            }
            ogs_sbi_snssai_t *allowed_nssaisItem = ogs_sbi_snssai_parseFromJSON(allowed_nssais_local_nonprimitive);

            ogs_sbi_list_add(allowed_nssaisList, allowed_nssaisItem);
        }
    }

    cJSON *priority = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "priority");

    if (priority) {
        if (!cJSON_IsNumber(priority)) {
            goto end;
        }
    }

    cJSON *capacity = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "capacity");

    if (capacity) {
        if (!cJSON_IsNumber(capacity)) {
            goto end;
        }
    }

    cJSON *load = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "load");

    if (load) {
        if (!cJSON_IsNumber(load)) {
            goto end;
        }
    }

    cJSON *recovery_time = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "recoveryTime");

    if (recovery_time) {
        if (!cJSON_IsString(recovery_time)) {
            goto end;
        }
    }

    cJSON *chf_service_info = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "chfServiceInfo");

    ogs_sbi_chf_service_info_t *chf_service_info_local_nonprim = NULL;
    if (chf_service_info) {
        chf_service_info_local_nonprim = ogs_sbi_chf_service_info_parseFromJSON(chf_service_info);
    }

    cJSON *supported_features = cJSON_GetObjectItemCaseSensitive(nf_serviceJSON, "supportedFeatures");

    if (supported_features) {
        if (!cJSON_IsString(supported_features))
        {
            goto end;
        }
    }

    nf_service_local_var = ogs_sbi_nf_service_create (
        ogs_strdup(service_instance_id->valuestring),
        service_name_local_nonprim,
        versionsList,
        scheme_local_nonprim,
        nf_service_status_local_nonprim,
        fqdn ? ogs_strdup(fqdn->valuestring) : NULL,
        inter_plmn_fqdn ? ogs_strdup(inter_plmn_fqdn->valuestring) : NULL,
        ip_end_points ? ip_end_pointsList : NULL,
        api_prefix ? ogs_strdup(api_prefix->valuestring) : NULL,
        default_notification_subscriptions ? default_notification_subscriptionsList : NULL,
        allowed_plmns ? allowed_plmnsList : NULL,
        allowed_nf_types ? allowed_nf_typesList : NULL,
        allowed_nf_domains ? allowed_nf_domainsList : NULL,
        allowed_nssais ? allowed_nssaisList : NULL,
        priority ? priority->valuedouble : 0,
        capacity ? capacity->valuedouble : 0,
        load ? load->valuedouble : 0,
        recovery_time ? ogs_strdup(recovery_time->valuestring) : NULL,
        chf_service_info ? chf_service_info_local_nonprim : NULL,
        supported_features ? ogs_strdup(supported_features->valuestring) : NULL
        );

    return nf_service_local_var;
end:
    return NULL;
}

