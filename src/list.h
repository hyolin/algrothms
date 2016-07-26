/*************************************************************************
	> File Name: list.h
	> Author: hyolin
	> Created Time: Wed 14 Jan 2015 08:15:49 PM CST
 ************************************************************************/

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef int(*fun_com)(const void *, const void *);
typedef void(*func_des)(void *);

/**Define a structure for linked list elements*/
typedef struct ListNode_
{
    void *data;
    struct ListNode_ *next;
} ListNode;

/**Define a structure for linked lists*/
typedef struct List_ 
{
    int size;
    func_com *compare;
    func_des *destroy;
    ListNode *head;
    ListNode *tail;
} List;

/**List Interface*/
int list_init(List **list, func_com *compare, func_des *destroy);
void list_destroy(List *list);
/**Insert success return 0,failure return -1*/
int  list_ins_next(List *list, ListNode *element, const void *data);

/**Remove success return 0, failure return -1*/
int  list_rm_next(List *list, ListNode *element, void **data);

ListNode* list_search(const List *list, const void *data, ListNode **prev);

/**return the size of list*/
#define list_size(list)(list)->size
/**return the head of list*/
#define list_head(list)(list)->head
/**return the tail of list*/
#define list_tail(list)(list)->tail
#define list_is_head(list, element)((element) ==(list)->head ?1 : 0))
#define list_is_tail(element)((element)->next == NULL ? 1 : 0)
#define list_data(element)((element)->data)
#define list_next(element)((element)->next)

#endif

