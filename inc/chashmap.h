#ifndef _CASH_MAP_
#define _CASH_MAP_

#ifdef __cplusplus
extern "C" {
#endif

#include "cdef.h"


#define CHASH_MAP_SIZE_MIN       (16)
#define CHASH_MAP_SIZE_MAX       (0x40000000)
//#define CHASH_MAP_SIZE_MAX       (32)

typedef struct Entry {
    void*               key;
    void*               value;
    struct Entry*       next;
    int                 hash;
} Entry;

/**
 * @brief function type of calculate hash value.
 *
 * @param key: key.
 * 
 * @return hash code
 *
 */
typedef int (*hash_func_t)(void* key);

/**
 * @brief function type of key cooperation.
 *
 * @param a: key to be compared.
 * @param b: key to be compared.
 * 
 * @return 0:a==b, positive:a>b, negative:a < b
 *
 */
typedef int (*compare_key_t)(void* a, void* b);

/**
 * @brief function type of iterative processing entries. args type of chash_map_loop_all,chash_map_loop.
 *
 * @param entry: entry.
 * @param row: row number in entry table.
 * @param column: column number in entry list.
 * 
 * @return 0:continue loop, 1:end loop and return cur entry.
 *
 */
typedef int (*loop_func_t)(Entry* entry, int row, int column);

typedef struct cHashMap {
    int                 size;               /* size of Entry table. */
    int                 used;               /* used of Entry table */
    hash_func_t         pHashFunc;          /* function of calculate hash value */
    compare_key_t       pCompareKeyFunc;    /* function of key cooperation */
    Entry**             table;              /* Entry table */
    int                 loadFactorNume;     /* Denominator of factor */
    int                 loadFactorDeno;     /* numerator of factor */
}cHashMap;

/**
 * @brief Initialization function.
 *
 * @param map: map to be operated.
 * @param size: initial size of entry table. 2^n.
 * @param hashFunc: function of calculate hash value.
 * @param pCompareKeyFunc: function of key cooperation.
 * 
 * @return RET_OK on success, otherwise on error.
 *
 */
int chash_map_init(cHashMap* map, int size, hash_func_t hashFunc, compare_key_t pCompareKeyFunc);

/**
 * @brief Deinitialization function.
 *
 * @param map: map to be operated.
 *
 * @return RET_OK on success, otherwise on error.
 * 
 */
int chash_map_deinit(cHashMap* map);

/**
 * @brief put value function.
 *
 * @param map: map to be operated.
 * @param key: key.
 * @param value: value
 * 
 * @return RET_OK on success, otherwise on error.
 *
 */
int chash_map_put(cHashMap* map, void* key, void* value);

/**
 * @brief get value function.
 *
 * @param map: map to be operated.
 * @param key: key.
 * 
 * @return RET_OK on success, otherwise on error.
 *
 */
void* chash_map_get(cHashMap* map, void* key);

/**
 * @brief remove function.
 *
 * @param map: map to be operated.
 * @param key: key.
 * 
 * @return NULL on not found, otherwise return non-null.
 *
 */
int chash_map_remove(cHashMap* map, void* key);


/**
 * @brief get begin iterator.
 *
 * @param map: map to be operated.
 * 
 * @return begin entry. null when map is empty.
 *
 */
Entry* chash_map_iterator_begin(cHashMap* map);

/**
 * @brief get next iterator.
 *
 * @param map: map to be operated.
 * @param cur: current entry.
 * 
 * @return next entry. null when cur is last.
 *
 */
Entry* chash_map_iterator_next(cHashMap* map, Entry* cur);

/**
 * @brief get end iterator.
 *
 * @param map: map to be operated.
 * 
 * @return NULL.
 *
 */
Entry* chash_map_iterator_end(cHashMap* map);

#ifdef __cplusplus
}
#endif

#endif