/*************************************************************************
	> File Name: hash.c
	> Author: hyolin 
	> Created Time: Mon 19 Jan 2015 02:19:03 PM CST
 ************************************************************************/
#include "hash.h"

/* hashtbl_init */ 
int hashtbl_init(HashTbl *htbl, int buckets,
					unsigned int(*hash_func)(const void *key),
					int(*compare)(const void *key1, const void *key2), 
					void(*destroy)(void *data))
{
	htbl->lists = NULL;
	/* Allocate the space for the hash table */
	if((htbl->lists =(List*)
                malloc(buckets*sizeof(List))) == NULL) {
		printf("hashtbl_init malloc error ");
		return -1;
	}
	htbl->buckets = buckets;

	int  i = 0;
	for(i = 0; i < buckets; i++)
		list_init(htbl->lists+i, compare, destroy);

	htbl->hash_func = hash_func;
	htbl->compare = compare;
	htbl->destroy = destroy;
	htbl->size = 0;

	return 0;
}

/* hashtbl_destroy */
void hashtbl_destroy(HashTbl *htbl)
{
	int i = 0;
	/* Destroy each bucket */
	for(i = 0; i < htbl->buckets; i++)
		htbl->destroy(htbl->lists+i);
	if(htbl->lists != NULL)
		free(htbl->lists);
	htbl->lists = NULL;

	memset(htbl, 0, sizeof(HashTbl));

	return;
}

/* hashtbl_insert */
int hashtbl_insert(HashTbl *htbl, const void *data)
{
	unsigned int bucket;
	void	*tmp =(void*)data;

	/* Do nothing if the data is already in the table */
	if(hashtbl_search(htbl,&tmp))
		return 1;
	/* hash the  key */
	bucket = htbl->hash_func(data) % htbl->buckets;

	int ret;
	if((ret = list_ins_next(htbl->lists+bucket, NULL, data)) == 0)
		htbl->size++;
	return ret;
}

/* hash_remove */
int hash_remove(HashTbl *htbl, void **data)
{
	ListNode	*element, *prev;
	unsigned int bucket;
	bucket = htbl->hash_func(*data) % htbl->buckets;

	if(!list_search(htbl->lists+bucket, *data, prev)) {
		printf("hash_remove error for data is not exist in the table");
		return -1;
	}
	
	if(list_rm_next(htbl->lists+bucket, prev, data) != 0) {
		printf("hash_remove error for list_rm_next error");
		return -1;
	}
	htbl->size--;

	return 0;
}

/* hashtbl_search */
int hashtbl_search(const HashTbl *htbl, void **data)
{
	unsigned int bucket;
	bucket = htbl->hash_func(*data) % htbl->buckets;

	ListNode *element;
	if((element = list_search(htbl->lists+bucket, *data, NULL)) == NULL) {
		printf("hashtbl_search :data is't exist in the table");
		return 0;
	}

	*data = list_data(element);
	return 1;
}
