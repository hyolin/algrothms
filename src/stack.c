/*************************************************************************
	> File Name: stack.c
	> Author: hyolin
	> Created Time: Fri 16 Jan 2015 07:22:00 PM CST
 ************************************************************************/
#include "stack.h"

int stack_push (Stack *stack, const void *data)
{
    /* Push the data into the stack */
    return list_ins_next(stack, NULL, data);
}

int stack_pop (Stack *stack, void **data)
{
    /* Pop data from the stack */
    return list_rm_next(stack, NULL, data);
}
