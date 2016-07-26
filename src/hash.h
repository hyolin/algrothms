/*************************************************************************
	> File Name: hash.h
	> Author: hyolin 
	> Created Time: Mon 19 Jan 2015 01:15:17 PM CST
 ************************************************************************/
#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <string.h>
#include "list.h"

/* structure of chained  hash tables */
typedef struct HashTbl_ {
	int				buckets;
	unsigned int	(*hash_func)(const void *key);
	int				(*compare)(const void *key1, const void *key2);
	void			(*destroy)(void *data);

	int		size;
	List	*lists;
} HashTbl;

/* Public interface */
int		hashtbl_init(HashTbl *htbl, int buckets, 
			unsigned int(*hash_func)(const void *key),
			int(*compare)(const void *key1, const void *key2), void(*destroy)(void *data));
void	hashtbl_destroy(HashTbl *htbl);
int		hashtbl_insert(HashTbl *htbl, const void *data);
int		hashtbl_remove(HashTbl *htbl, void **data);
int 	hashtbl_search(const HashTbl *htbl, void **data);

#define hashtbl_size(htbl)((htbl)->size)
#endif
