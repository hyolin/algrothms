/*************************************************************************
	> File Name: double_list.h
	> Author: hyolin 
	> Created Time: Thu 15 Jan 2015 06:00:29 PM CST
 ************************************************************************/

/*Double list */
#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>

/* Ddefine a structure for double-linked list elements */
typedef struct DListNode_
{
	void	*data;
	struct DListNode_  *prev;
	struct DListNode_  *next;
} DListNode;

typedef struct DList_ 
{
	int size;
	//int (*match)(const void *key1, const void *key2);
	int (*destroy)(void *data);
	DListNode *head;
	DListNode *tail;
} DList;

/* Public Interface */
void    dlist_init(DList *list, void (*destroy)(void *data));
void dlist_destroy(DList *list);
int dlist_ins_next(DList *list, DListNode *element, const void *data);
int dlist_ins_prev(DList *list, DListNode *element, const void *data);
int   dlist_remove(DList *list, DListNode *element, void **data);

DListNode* dlist_search(DList *list, const void *data, 
                       int (*compare)(const void *key1, const void *key2));

#define dlist_size(list)		((list)->size)
#define dlist_head(list)		((list)->head)
#define dlist_tail(list)		((list)->tail)
#define dlist_is_head(element)	((element)->prev == NULL ? 1 : 0)
#define dlist_is_tail(element)	((element)->next == NULL ? 1 : 0)

#define dlist_data(element)	  ((element)->data)
#define dlist_prev(element)   ((element)->prev)
#define dlist_next(element)   ((element)->next)

#endif //
