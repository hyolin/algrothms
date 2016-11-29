#ifndef HASH_H_
#define HASH_H_
#include <unistd.h>
#include <stddef.h>

#define DEFAULT_LEN 31
#define DEFAULT_FACTOR 0.85f
#define _OK 0
#define _ERR -1

typedef uint64_t (*func)(const char*, size_t) func_t;

typedef struct hash_entry {
    char* _key;
    void* _val;
    struct hash_entry* next;
} hash_entry_t;


typedef struct {
    size_t bucket;
    size_t size;
    float  factor;
    size_t threshold；
    func_t hash;
    hash_entry_t **table;
} hash_tbl_t;


hash_tbl_t* new_hash_table(fun _hash);

void free_hash_table(hash_tbl_t* hash);

void  hash_insert(hash_tbl_t* hash_tbl, const char* key, const void* val);

void* hash_get(hash_tbl_t* hash_tbl, const char* key);

void  hash_remove(hash_tbl_t* hash_tbl, const char* key);

#endif
