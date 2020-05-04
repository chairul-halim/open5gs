#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/list.h"
static ogs_sbi_lnode_t *listEntry_create(void *data)
{
    ogs_sbi_lnode_t *created = ogs_malloc(sizeof(ogs_sbi_lnode_t));

    if (created == NULL) {
        // TODO Malloc Failure
        return NULL;
    }
    created->data = data;

    return created;
}

void ogs_sbi_lnode_free(ogs_sbi_lnode_t *listEntry, void *additionalData)
{
    ogs_free(listEntry);
}

void ogs_sbi_lnode_print(ogs_sbi_lnode_t *listEntry, void *additionalData)
{
    printf("%i\n", *((int *) (listEntry->data)));
}

ogs_sbi_list_t *ogs_sbi_list_create(void)
{
    ogs_sbi_list_t *createdList = ogs_malloc(sizeof(ogs_sbi_list_t));

    if (createdList == NULL) {
        // TODO Malloc Failure
        return NULL;
    }
    createdList->first = NULL;
    createdList->last = NULL;
    createdList->count = 0;

    return createdList;
}

void ogs_sbi_list_iterate_forward(ogs_sbi_list_t *list,
                                  void (*operationToPerform)(
                                      ogs_sbi_lnode_t *, void *callbackFunctionUsedData),
                                  void *additionalDataNeededForCallbackFunction)
{
    ogs_sbi_lnode_t *current = list->first;
    ogs_sbi_lnode_t *next;

    if (current == NULL) {
        return;
    }

    next = current->next;

    operationToPerform(current, additionalDataNeededForCallbackFunction);
    current = next;

    while (current != NULL) {
        next = current->next;
        operationToPerform(current, additionalDataNeededForCallbackFunction);
        current = next;
    }
}

void ogs_sbi_list_iterate_backward(ogs_sbi_list_t *list,
                                   void (*operationToPerform)(
                                       ogs_sbi_lnode_t *, void *callbackFunctionUsedData),
                                   void *additionalDataNeededForCallbackFunction)
{
    ogs_sbi_lnode_t *current = list->last;
    ogs_sbi_lnode_t *next = current->prev;

    if (current == NULL) {
        return;
    }

    operationToPerform(current, additionalDataNeededForCallbackFunction);
    current = next;

    while (current != NULL) {
        next = current->prev;
        operationToPerform(current, additionalDataNeededForCallbackFunction);
        current = next;
    }
}

void ogs_sbi_list_free(ogs_sbi_list_t *list)
{
    if (list) {
        ogs_sbi_list_iterate_forward(list, ogs_sbi_lnode_free, NULL);
        ogs_free(list);
    }
}

void ogs_sbi_list_add(ogs_sbi_list_t *list, void *dataToAddInList)
{
    ogs_sbi_lnode_t *newListEntry = listEntry_create(dataToAddInList);
    if (newListEntry == NULL) {
        // TODO Malloc Failure
        return;
    }
    if (list->first == NULL) {
        list->first = newListEntry;
        list->last = newListEntry;

        newListEntry->prev = NULL;
        newListEntry->next = NULL;

        list->count++;

        return;
    }

    list->last->next = newListEntry;
    newListEntry->prev = list->last;
    newListEntry->next = NULL;
    list->last = newListEntry;

    list->count++;
}

void ogs_sbi_list_remove(ogs_sbi_list_t *list, ogs_sbi_lnode_t *elementToRemove)
{
    ogs_sbi_lnode_t *elementBeforeElementToRemove = elementToRemove->prev;
    ogs_sbi_lnode_t *elementAfterElementToRemove = elementToRemove->next;

    if (elementBeforeElementToRemove != NULL) {
        elementBeforeElementToRemove->next = elementAfterElementToRemove;
    } else {
        list->first = elementAfterElementToRemove;
    }

    if (elementAfterElementToRemove != NULL) {
        elementAfterElementToRemove->prev = elementBeforeElementToRemove;
    } else {
        list->last = elementBeforeElementToRemove;
    }

    ogs_sbi_lnode_free(elementToRemove, NULL);

    list->count--;
}

ogs_sbi_lnode_t *ogs_sbi_list_find(ogs_sbi_list_t *list, long indexOfElement)
{
    ogs_sbi_lnode_t *current;
    int i;

    if ((list->count / 2) > indexOfElement) {
        current = list->first;

        for(i = 0; i < indexOfElement; i++) {
            current = current->next;
        }

        return current;
    } else {
        current = list->last;

        for(i = 1; i < (list->count - indexOfElement); i++) {
            current = current->prev;
        }

        return current;
    }
}