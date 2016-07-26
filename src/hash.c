/*************************************************************************
	> File Name: hash.c
	> Author: hyolin 
	> Created Time: Mon 19 Jan 2015 02:19:03 PM CST
 ************************************************************************/
#include <stdint.h>
#include <ctype.h>
#include "hash.h"

static uint32_t __hash_seed = 5381;

/** Thomas wang's hash function */
unsigned int _hash_int_func(unsigned int key)
{
    key += ~(key << 15);
    key ^= (key >> 10);
    key += (key << 3);
    key ^= (key >> 6);
    key += ~(key << 11);
    key ^= (key >> 16);
    return key;
}


unsigned int _hash_case_func(const unsigned char *buf, int len)
{
    unsigned int hash = (unsigned int) __hash_seed;
    while (len--) {
        hash = ((hash << 5) + hash + tolower(*buf++));
    }
    return hash;
}
/** Murmurhash2 by Austin Appleby */
unsigned int _hash_murmur_func(const void *key, len)
{
    uint32_t seed = __hash_seed;
    const uint32_t m = 0x5bd1e995;
    const int r = 24;

    uint32_t h = seed ^ len;
    /** Max 4 byte into hash */
    const unsigned char *data = (const unsigned char *) key;
    while (len > 4) {
        uint32_t k = *(uint32_t *)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    /** handle last few bytes */
    switch (len) {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0]; h *= m;
    }

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return (unsigned int h);
}

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
