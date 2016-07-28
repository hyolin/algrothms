/*************************************************************************
	> File Name: queue.c
	> Author: hyolin 
	> Created Time: Sat 17 Jan 2015 04:42:31 PM CST
 ************************************************************************/
#include "queue.h"

/* queue_init */
void queue_init(Queue *queue, void (*destroy)(void *data))
{
	list_init(queue, NULL, destroy);
	return;
}

/* queue_destroy */
void queue_destroy(Queue *queue)
{
	list_destroy(queue);
	return;
}

/* queue_enqueue */
int queue_enqueue(Queue *queue, const void *data)
{
	return list_ins_next(queue, list_tail(queue), data);
}

/* queue_dequeue */
int queue_dequeue(Queue *queue, void **data)
{
	return list_rm_next(queue, NULL, data);
}

/* queue_size */
int queue_size(Queue *queue)
{
	return list_size(queue);
}
