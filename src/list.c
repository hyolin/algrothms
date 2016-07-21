/*************************************************************************
    > File Name: list.c
    > Author: hyolin
    > Created Time: Wed 14 Jan 2015 09:34:33 PM CST
 ************************************************************************/
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

 #include "list.h"

/*Initialize the list*/
int list_init (List **list, func_com *compare, func_des *destroy)
{
	int ret = 0;
	*list = NULL;
	if ((*list = (List*)malloc(sizeof(List))) == NULL)
	{
		ret = -1;
		printf("%s %s %dfailure for malloc error: %d\n",__FILE__, __func__, __LINE__, ret);
		return ret;
	}
    (*list)->size = 0;
    (*list)->compare = compare;
    (*list)->destroy = destroy;
    (*list)->head = NULL;
    (*list)->tail = NULL;
    
    return ret;
}

/*list_destroy*/
void list_destroy (List *list)
{
    void    *data;
    while (list_size (list) > 0)
    {
        if (list_rm_next(list, NULL, (void **)&data) == 0 && list->destroy
            != NULL)
        {
            list->destroy(data);//call a user-defined function to free dynamically data
        }
    }

    //memset(list, 0, sizeof(list));
	if (list != NULL)
		free(list);

    return;
}

/**list_ins_next*/
int list_ins_next (List *list, ListNode *element, const void *data)
{
	int ret = 0;

	if (list == NULL || data == NULL)
	{
		ret = -1;
		printf("%s %s %d list == NULL || data == NULL %d\n",__FILE__, __func__, __LINE__, ret);
		return ret;
	}
    ListNode    *newNode;

    /* Allocate storage for the element */
    if ((newNode = (ListNode *)malloc(sizeof(newNode))) == NULL)
    {
		ret = -2;
        printf("%s %s %d malloc error : %d\n", __FILE__, __func__, __LINE__, ret);
        return ret;
    }

    /* Insert the element into the list */
    newNode->data = (void *)data;
    if (element == NULL)
    {
        /* Handle the head of the list */
        if (list_size(list) == 0)
            list->tail = newNode;

        newNode->next = list->head;
        list->head = newNode;
    }
    else {
        if (element->next == NULL)
            list->tail = newNode;

        newNode->next = element->next;
        element->next = newNode;
    }
    /*Adjust the size of the list */
    list->size++;

    return ret;
}
   
/* list_rm_next */
int list_rm_next (List *list, ListNode *element, void **data)
{
	int ret = 0;
    ListNode    *oldNode;
    /* Don't allow remove from an empty list */
    if (list == NULL || list_size(list) == 0)
    {
		ret = -1;
        printf("%s %s %d failure  %d",__FILE__, __func__, __LINE__, ret);
        return ret;
    }

    if (element == NULL)
    {
        *data = list->head->data;
        oldNode = list->head;
        list->head = list->head->next;

        if (list_size(list) == 1)
            list->tail = NULL;
    }
    else {
        if (element->next == NULL)
        {

			ret = -2;
			printf("%s %s %d failure: element next is empty %d",__FILE__, __func__, __LINE__, ret);
            return ret;
        }

        oldNode = element->next;
        *data = oldNode->data;
        element->next = element->next->next;
        
        if (element->next ==NULL)
            list->tail = element;    
    }

    free(oldNode);
    list->size--;

    return ret;
}

/* list_search */
ListNode* list_search (const List *list, const void *data, ListNode **prev/*,
						int (*compare)(const void *key1, const void *key2)*/)
{
	int ret = 0;
	if (list == NULL || data == NULL)
	{
		ret = -1;
		printf("%s %s %d failure: list ==  NULL or data == NULL %d",__FILE__, __func__, __LINE__, ret);
		return ret;
	}
    /** Return the data of the list node */
    ListNode *element = list_head(list);
	*prev = NULL;

    while (element)
    {
        if (list->compare(element->data, data) == 0)
            break;
		prev = element;
        element = element->next;
    }
	/* 
	 for (; element != NULL; element = list_next(element))
	 {
		if (compare(list_data(element) == 0))
			break;
		prev = element;
	 }
	 */
    return element;
}


