/*
 * default_notification_subscription.h
 *
 *
 */

#ifndef _ogs_sbi_default_notification_subscription_H_
#define _ogs_sbi_default_notification_subscription_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "n1_message_class.h"
#include "n2_information_class.h"
#include "notification_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ogs_sbi_default_notification_subscription_s ogs_sbi_default_notification_subscription_t;
typedef struct ogs_sbi_default_notification_subscription_s {
    struct ogs_sbi_notification_type_s *notification_type;
    char *callback_uri;
    struct ogs_sbi_n1_message_class_s *n1_message_class;
    struct ogs_sbi_n2_information_class_s *n2_information_class;
} ogs_sbi_default_notification_subscription_t;

ogs_sbi_default_notification_subscription_t *ogs_sbi_default_notification_subscription_create(
    ogs_sbi_notification_type_t *notification_type,
    char *callback_uri,
    ogs_sbi_n1_message_class_t *n1_message_class,
    ogs_sbi_n2_information_class_t *n2_information_class
    );
void ogs_sbi_default_notification_subscription_free(ogs_sbi_default_notification_subscription_t *default_notification_subscription);
ogs_sbi_default_notification_subscription_t *ogs_sbi_default_notification_subscription_parseFromJSON(cJSON *default_notification_subscriptionJSON);
cJSON *ogs_sbi_default_notification_subscription_convertToJSON(ogs_sbi_default_notification_subscription_t *default_notification_subscription);

#ifdef __cplusplus
}
#endif

#endif /* _ogs_sbi_default_notification_subscription_H_ */

