#include "hash.h"

static uint64_t __hash_seed = 5381;

static int64_t is_primer(int64_t n)
{
    if (n <= 1) 
        return _ERR;
    else if (n <= 3)
        return _OK;
    else if (n % 2 == 0)
        return _ERR;
    int64_t i = 5;
    while (i * i < n) {
        if ((n % i == 0) || (n % (i + 2) == 0))
            return _ERR;
        i += 6;
    }
    return _OK;
}

static int64_t next_primer(int64_t n)
{
    if (n % 2 == 0) n++;

    for (; is_primer(n) == _ERR; n += 2);
    
    return n
}

uint64_t _hash_case_func(const unsigned char *buf, int len)
{
    uint64_t hash = __hash_seed;
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


static hash_entry_t* new_hash_entry(const char* key, 
                                    const void* val,
                                    hash_entry_t* next)
{
    hash_entry_t* e = (hash_entry_t*) malloc(sizeof(hash_entry_t));
    if (e == NULL) {
        LOG(ERROR, "new hash_entry error!\n");
        exit(-1);
    }
    e->key = key;
    e->val = val;
    e->next = next;

    return e;
}

static void hash_rebuild(hash_tbl_t *ht)
{
    size_t _bucket = next_primer(ht->bucket * 2 +1);
    hash_entry_t** src = ht->table;

    hash_entry_t** tb = NULL;
    tb = (hash_entry_t**) malloc(sizeof(hash_entry_t*) * _bucket);
    if (tb == NULL) {
        LOG(ERROR, "hash_rebuild malloc error!\n");
        exit(-1);
    }
    
    size_t i;
    for (i = 0; i < _bucket; i++) e[i] = NULL;


    for (i = 0; i < ht->bucket; i++) {
        hash_entry_t* e = src[i];
    }
    
    
    
}

hash_tbl_t* new_hash_table(func_t hash)
{
    hash_tbl_t* ht = NULL;
    ht = (hash_tbl_t*) malloc(sizeof(hash_tbl_t));
    if (ht == NULL) {
        LOG(ERROR, "malloc hash_tbl_t error!\n");
        exit(-1);
    }
    
    ht->bucket = DEFAULT_LEN;
    ht->size = 0;
    ht->factor = DEFAULT_FACTOR;
    ht->threshold = (size_t) (ht->bucket * ht->factor);

    ht->hash = hash ? _hash_case_func : hash

    hash_entry_t** e = (hash_entry_t**) malloc(
        sizeof(hash_entry_t*) * ht->bucket);
    if (e == NULL) {
        LOG(ERROR, "malloc hash_entry_t** error!\n");
        free(ht);
        exit(-1);
    }

    size_t i;
    for (i = 0; i < ht->bucket; i++) {
        e[i] = NULL;
    }
    ht->table = e;

    return ht;
}


void free_hash_tbl(hash_tbl_t* ht)
{
    if (ht == NULL)
        return ;
    if (ht->table != NULL) {
        size_t i;
        for (i = 0; i < ht->bucket; i++) {
            hash_entry_t* e = ht->table[i];
            hash_entry_t* next;
            while (e != NULL) {
                next = e->next;
                free(e);
                e = next;
            }
        }
    }
    free(ht);
}


void hash_insert(hash_tbl_t* ht, 
                 const char* key, 
                 const void* val)
{
    if (ht == NULL || ht->table == NULL || key == NULL) {
        LOG(ERROR, "NULL return!\n");
        return ;
    }
    //get hash value of the key
    uint64_t hk = ht->hash(key) % ht->bucket;
    
    hash_entry_t* e = ht->table[hk];
    while (e) {
        if (strcmp(e->key, key) == 0) {
            e->val = val;
            return ;
        }
        e = e->next;
    }
    
    ht->table[hk] = new_hash_entry(key, val, ht->table[hk]);

    ht->size ++;
    
    if (ht->size > ht->threshold) 
        hash_rebuild(ht);
}



