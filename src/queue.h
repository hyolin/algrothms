/*************************************************************************
	> File Name: queue.h
	> Author: hyolin
	> Created Time: Sat 17 Jan 2015 03:47:13 PM CST
 ************************************************************************/
#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

#include "list.h"

typedef List Queue;

/* Public Interface of Queue */
void	queue_init(Queue *queue, void (*destroy)(void *data));
void queue_destroy(Queue *queue);
int	 queue_enqueue(Queue *queue, const void *data);
int  queue_dequeue(Queue *queue, void **data);
int		queue_size(Queue *queue);

/***********************************************************
#define queue_init list_init
#define queue_destroy list_destroy
#define queue_size list_size
***********************************************************/
#endif //#
