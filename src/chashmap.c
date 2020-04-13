#include "chashmap.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

static void chash_map_release_memory(cHashMap* map);
static void chash_map_release_memory_entry_list(Entry* list);
static Entry* chash_map_find_in_entry(cHashMap* map, Entry* list, void* key);
static Entry* chash_map_alloc_entry(void* key, void* value, int hash, Entry* next);
static Entry* chash_map_remove_entry_by_key(cHashMap* map, Entry* list, void* key);
static int chash_map_resize(cHashMap* map);
static int chash_map_hash_to_index(int hash, int size);
static int chash_map_round_size(int size);

#define CHASH_MAP_SIZE_MIN       (16)
#define CHASH_MAP_SIZE_MAX       (0x40000000)
//#define CHASH_MAP_SIZE_MAX       (32)

int chash_map_init(cHashMap* map, int size, hash_func_t hashFunc, compare_key_t pCompareKeyFunc){
    if(map == NULL) return RET_ERR_NULL_POINTER;

    size = chash_map_round_size(size);
    printf("size=%d\n", size);

    map->table = (Entry**)malloc(sizeof(Entry*) * size);

    if(map->table == NULL) return RET_ERR_MEM;

    memset(map->table, 0, sizeof(Entry*) * size);
    map->size = size;
    map->used = 0;
    map->pHashFunc = hashFunc;
    map->pCompareKeyFunc = pCompareKeyFunc;
    /* set load factor = 0.75(3/4) */
    map->loadFactorDeno = 4;
    map->loadFactorNume = 3;

    return RET_OK;
}

int cash_map_deinit(cHashMap* map){
    if(map == NULL) return RET_ERR_NULL_POINTER;

    /* release res */
    chash_map_release_memory(map);
    free(map->table);
    map->table = NULL;
    map->pHashFunc = NULL;
    map->size = 0;
    map->used = 0;
    return RET_OK;
}

int cash_map_put(cHashMap* map, void* key, void* value){
    if(map == NULL) return RET_ERR_NULL_POINTER;

    int hash = map->pHashFunc(key);
    int index = chash_map_hash_to_index(hash, map->size);

    if(map->table[index] == NULL){
        map->table[index] = chash_map_alloc_entry(key, value, hash, NULL);
        
        if(map->table[index] == NULL){
            return RET_ERR_MEM;
        }

        map->used++;

        if(map->used * map->loadFactorDeno > map->size * map->loadFactorNume){
            chash_map_resize(map);
        } 
    } else {
        //find key and update
        Entry* pFoundEntry = chash_map_find_in_entry(map, map->table[index], key);
        if(pFoundEntry == NULL){
            //insert head
            map->table[index] = chash_map_alloc_entry(key, value, hash, map->table[index]);

            if(map->table[index] == NULL){
                return RET_ERR_MEM;
            }
        }else{
            pFoundEntry->value = value;
        }
    }

    return RET_OK;
}

void* cash_map_get(cHashMap* map, void* key){
    if(map == NULL) return NULL;

    void* pRet = NULL;

    int index = chash_map_hash_to_index(map->pHashFunc(key), map->size);
    if(map->table[index] != NULL){
        Entry* pFoundEntry = chash_map_find_in_entry(map, map->table[index], key);

        if(pFoundEntry){
            pRet = pFoundEntry->value;
        }
    }

    return pRet;
}

int chash_map_remove(cHashMap* map, void* key){
    if(map == NULL) return RET_ERR_NULL_POINTER;

    int index = chash_map_hash_to_index(map->pHashFunc(key), map->size);

    if(map->table[index] == NULL) return RET_OK;

    map->table[index] = chash_map_remove_entry_by_key(map, map->table[index], key);

    if(map->table[index] == NULL) map->used--;

    return RET_OK;
}

Entry* chash_map_loop_all(cHashMap* map, loop_func_t func){
    Entry* pRet = NULL;
    if(map == NULL) return pRet;

    for(int i = 0; i < map->size; i++){
        int entryIndex = 0;
        Entry* list = map->table[i];
        while(list != NULL){
            if(func(list, i, entryIndex++)) {
                pRet = list;
                break;
            }
            list = list->next;
        }
        func(list, i, entryIndex++);
    }
    return pRet;
}

Entry* chash_map_loop(cHashMap* map, loop_func_t func){
    Entry* pRet = NULL;
    if(map == NULL) return pRet;

    for(int i = 0; i < map->size; i++){
        int entryIndex = 0;
        Entry* list = map->table[i];
        while(list != NULL){
            if(func(list, i, entryIndex++)) {
                pRet = list;
                break;
            }
            list = list->next;
        }
    }

    return pRet;
}

Entry* cash_map_iterator_begin(cHashMap* map){
    for(int i = 0; i < map->size; i++){
        if(map->table[i]) return map->table[i];
    }
    return NULL;
}

Entry* cash_map_iterator_next(cHashMap* map, Entry* cur){

    if(!map || !cur) return NULL;

    if(cur->next != NULL)   return cur->next;

    int entryRow = chash_map_hash_to_index(cur->hash, map->size);
    
    for(int i = entryRow + 1; i < map->size; i++){
        if(map->table[i]) return map->table[i];
    }

    return NULL;
}

Entry* cash_map_iterator_end(cHashMap* map){
    return NULL;
}

static Entry* chash_map_alloc_entry(void* key, void* value, int hash, Entry* next){
    Entry* pRet = (Entry*)malloc(sizeof(Entry));

    if(pRet == NULL){
        printf("Memory error on %s line %d.", __FUNCTION__, __LINE__);
    }

    pRet->key = key;
    pRet->value = value;
    pRet->hash = hash;
    pRet->next = next;

    return pRet;
}

static Entry* chash_map_find_in_entry(cHashMap* map, Entry* list, void* key){
    while(list != NULL){
        if(map->pCompareKeyFunc(list->key, key) == 0){
            break;
        }
        list = list->next;
    }

    return list;
}

static void chash_map_release_memory_entry_list(Entry* list){
    while(list != NULL){
        Entry* next = list->next;
        free(list);
        list = next;
    }
}

static void chash_map_release_memory(cHashMap* map){
    if(map == NULL) return;

    for(int i = 0; i < map->size; i++){
        chash_map_release_memory_entry_list(map->table[i]);
        map->table[i] = NULL;
    }
}

static Entry* chash_map_remove_entry_by_key(cHashMap* map, Entry* list, void* key){
    Entry* pre = NULL;
    Entry* pret = list;

    while(list != NULL){
        if(map->pCompareKeyFunc(list->key, key) == 0){
            if(pre == NULL){
                pret = list->next;
            }else{
                pre->next = list->next;
            }
            free(list);
            break;
        }
        pre = list;
        list = list->next;
    }

    return pret;
}

static int chash_map_resize(cHashMap* map){
    printf("resize cur:(%d/%d)\n", map->used, map->size);

    if(map->size > (CHASH_MAP_SIZE_MAX >> 1)){
        printf("Unable resize because map size(%d) already maximum.\n", map->size);
        return RET_OK;
    }

    int newSize = map->size * 2;
    int newUsed = 0;
    Entry** pNewTable = (Entry**)malloc(sizeof(Entry*) * newSize);

    if(pNewTable == NULL){
        printf("Memory error on %s line %d.", __FUNCTION__, __LINE__);
        return RET_ERR_MEM;
    }

    memset(pNewTable, 0, sizeof(Entry*) * newSize);

    for(int i = 0; i < map->size; i++){
        Entry* list = map->table[i];
        while(list != NULL){
            
            int index = chash_map_hash_to_index(list->hash, newSize);

            if(pNewTable[index] == NULL){
                newUsed++;
            }

            list->next = pNewTable[index];
            pNewTable[index] = list;

            list = list->next;
        }
    }

    free(map->table);
    map->table = pNewTable;
    map->size = newSize;
    map->used = newUsed;
    return RET_OK;
}

static int chash_map_hash_to_index(int hash, int size){
    return hash & (size - 1);
}

static int chash_map_round_size(int size){
    if(size & size - 1){
        //不是2的n次方
        long long temp = 0x02;
        while(size >>= 1) temp <<= 1;

        size = temp > CHASH_MAP_SIZE_MAX ? CHASH_MAP_SIZE_MAX : temp;
    }

    if(size > CHASH_MAP_SIZE_MAX) size = CHASH_MAP_SIZE_MAX;
    if(size < CHASH_MAP_SIZE_MIN) size = CHASH_MAP_SIZE_MIN;

    return size;
}