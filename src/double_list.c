/*************************************************************************
	> File Name: double_list.c
	> Author: hyolin
	> Created Time: Thu 15 Jan 2015 07:03:15 PM CST
 ************************************************************************/
#include <stdio.h>
#include <string.h>

#include "double_list.h"

void dlist_init(DList *list, void (*destroy)(void *data))
{
    /* Initialize the double list */
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;

    return;
}

void dlist_destroy(DList *list)
{
    /* Destroy the double list */
    void    *data;
    while(dlist_size(list) != 0) {
        if (dlist_remove(list, dlist_tail(list), (void **)&data) == 0 && 
            list->destroy != NULL) {
            list->destroy(data);
        }
    }

    memset(list, 0, sizeof(DList));
    return;
}

int dlist_ins_next(DList *list, DListNode *element, const void *data)
{
    DListNode * newNode = NULL;
    /* Don't allow the null element unless the list is empty*/
    if (element == NULL && dlist_size(list) != 0)
        return -1;

    if ((newNode = (DListNode*)malloc(sizeof(DListNode))) == NULL) {
        printf("dlist_ins_next malloc error");
        return -2;
    }

    newNode->data = data;
    if (dlist_size(list) == 0) {
        list->tail = (list->head = newNode);
        list->head->prev = (list->head->next = NULL);
    } else {
        newNode->next = element->next;
        newNode->prev = element;
        if (element->next == NULL)
            list->tail = newNode;
        else
            element->next->prev = newNode;
        element->next = newNode;
    }

    list->size++;
    return 0;
}

int dlist_ins_prev(DList *list, DListNode *element, const void *data)
{
    DListNode *newNode = NULL;

    if (element == NULL && dlist_size(list) != 0)
        return -1;

    if ((newNode = (DListNode*)malloc(sizeof(DListNode))) == NULL) {
        printf("dlist_ins_prev malloc error");
        return -2;
    }
    newNode->data = data;

    if (dlist_size(list) == 0) {
        list->head = (list->tail = newNode);
        list->head->prev = (list->head->next = NULL);
        //list->tail->prev = (list->tail->next = NULL);
    } else {
        newNode->prev = element->prev;
        newNode->next = element;

        if (element->prev == NULL)
            list->head = newNode;
        else
            element->prev->next = newNode;
        element->prev = newNode;
    }

    list->size++;
    return 0;
}

int dlist_remove(DList *list, DListNode *element, void **data)
{
    if (dlist_size(list) == 0 || element == NULL) {
        printf("dlist_remove error for dlist_size(list) = 0 || element = NULL");
        return -1;
    }

    *data = element->data;
    
    if (dlist_head(list) == element) {
        list->head = element->next;
        if (list->head == NULL)
            list->tail = NULL;
        else
            element->next->prev = list->head;

    } else {
        element->prev->next = element->next;
        if (element->next == NULL)
            list->tail = element->prev;
        else
            element->next->prev = element->prev;
    }

    free(element);
    list->size--;

    return 0;
}

DListNode* dlist_search(DList *list, const void *data,
		int (*compare)(const void *key1, const void *key2))
{
    DListNode *pNode = list->head;
    while (pNode) {
        if (compare(pNode->data, data) == 0)
            break;
        pNode = pNode->next;
    }
    return pNode;
}
