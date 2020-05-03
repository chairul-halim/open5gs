
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "nf_status.h"

char* ogs_sbi_nf_status_ToString(ogs_sbi_nf_status_e nf_status)
{
    char *nf_statusArray[] =  { "NULL", "REGISTERED", "SUSPENDED", "UNDISCOVERABLE" };
    return nf_statusArray[nf_status];
}

ogs_sbi_nf_status_e ogs_sbi_nf_status_FromString(char* nf_status)
{
    int stringToReturn = 0;
    char *nf_statusArray[] =  { "NULL", "REGISTERED", "SUSPENDED", "UNDISCOVERABLE" };
    size_t sizeofArray = sizeof(nf_statusArray) / sizeof(nf_statusArray[0]);
    while (stringToReturn < sizeofArray) {
        if (strcmp(nf_status, nf_statusArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
    return 0;
}

