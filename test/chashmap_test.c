#include "stdio.h"
#include "stdlib.h"
#include "chashmap.h"
#include "assert.h"
#include "cutil.h"

const static char* values[] = {
    "this is string 0.",
    "this is string 1.",
    "this is string 2.",
    "this is string 3.",
    "this is string 4.",
    "this is string 5.",
    "this is string 6.",
    "this is string 7.",
    "this is string 8.",
    "this is string 9.",
    "this is string 10.",
    "this is string 11.",
    "this is string 12.",
    "this is string 13.",
    "this is string 14.",
    "this is string 15.",
    "this is string 16.",
    "this is string 17.",
    "this is string 18.",
    "this is string 19.",
    "this is string 20.",
    "this is string 21.",
    "this is string 22.",
    "this is string 23.",
    "this is string 24.",
    "this is string 25.",
    "this is string 26.",
    "this is string 27.",
    "this is string 28.",
    "this is string 29.",
    "this is string 30.",
    "this is string 31.",
    "this is string 32.",
    "this is string 33.",
    "this is string 34.",
    "this is string 35.",
    "this is string 36.",
    "this is string 37.",
    "this is string 38.",
    "this is string 39.",
    "this is string 40.",
    "this is string 41.",
    "this is string 42.",
    "this is string 43.",
    "this is string 44.",
    "this is string 45.",
    "this is string 46.",
    "this is string 47.",
    "this is string 48.",
    "this is string 49.",
    "this is string 50."
};

int hash_func_int(void* key){
    return (int)key;
}

int compare_key_int(void* a, void* b){
    return (int)a - (int)b;
}

int hash_func_int2(void* key){
    int num = (int)key;
    int ret = 0;

    if(num >= 0 && num < 15){
        return 0;
    }else if(num >=15 && num < 30){
        return 1;
    }else if(num >= 30 && num < 45){
        return 2;
    }else{
        return 5;
    }
}

int loop_func_print(Entry* entry, int row, int column){
    if(column == 0) cutil_logd("row[%d]:", row);

    if(entry == NULL){
        cutil_logd("null.\n");
    }else{
        cutil_logd("%d->", (int)(entry->key));
    }
    return 0;
}

int loop_func_print2(Entry* entry, int row, int column){
    if(entry) cutil_logd("%d:%s\n", (int)(entry->key), (char*)(entry->value));
    return 0;
}

/* Check size */
int chashmap_test1(){
    cHashMap map;
    chash_map_init(&map, 0, hash_func_int, compare_key_int);
    assert(map.size == CHASH_MAP_SIZE_MIN);
    chash_map_deinit(&map);
    assert(map.table == NULL);
}

/* Check size */
int chashmap_test2(){
    cHashMap map;
    chash_map_init(&map, 17, hash_func_int, compare_key_int);
    assert(map.size == 32);
    chash_map_deinit(&map);
    assert(map.table == NULL);
}

/* Check size */
int chashmap_test3(){
    cHashMap map;
    chash_map_init(&map, 127, hash_func_int, compare_key_int);
    assert(map.size == 128);
    chash_map_deinit(&map);
    assert(map.table == NULL);
}

/* Check size */
int chashmap_test4(){
    cHashMap map;
    chash_map_init(&map, 256, hash_func_int, compare_key_int);
    assert(map.size == 256);
    chash_map_deinit(&map);
    assert(map.table == NULL);
}

/* Check put, resize,get,remove */
int chashmap_test5(){
    cHashMap map;
    chash_map_init(&map, 16, hash_func_int, compare_key_int);
    assert(map.size == 16);

    for(int i = 0; i < 13; i++){
        chash_map_put(&map, (void*)i, (void*)values[i]);
    }
    assert(map.size == 32);

    for(int i = 13; i < 25; i++){
        chash_map_put(&map, (void*)i, (void*)values[i]);
    }
    assert(map.size == 64);
    for(int i = 25; i < 50; i++){
        chash_map_put(&map, (void*)i, (void*)values[i]);
    }
    chash_map_deinit(&map);
    assert(map.table == NULL);
}

/* Check put, resize,get,remove */
int chashmap_test6(){
    cHashMap map;
    chash_map_init(&map, 16, hash_func_int, compare_key_int);
    assert(map.size == 16);
    
    for(int i = 0; i < 13; i++){
        chash_map_put(&map, (void*)i, (void*)values[i]);
    }
    assert(map.size == 32);

    for(int i = 13; i < 25; i++){
        chash_map_put(&map, (void*)i, (void*)values[i]);
    }
    assert(map.size == 64);
    for(int i = 25; i < 50; i++){
        chash_map_put(&map, (void*)i, (void*)values[i]);
    }

    for(int i = 0; i < 50; i++){
        int cmp = strcmp(values[i], (char*)chash_map_get(&map, i));
        assert(cmp == 0);
    }

    for(int i = 0; i < 50; i++){
        chash_map_remove(&map, (void*)i);
    }
    assert(map.used == 0);

    chash_map_deinit(&map);
    assert(map.table == NULL);
}

/* Check put, resize,get,remove */
int chashmap_test7(){
    cHashMap map;
    chash_map_init(&map, 16, hash_func_int, compare_key_int);
    assert(map.size == 16);

    for(int i = 0; i < 50; i++){
        chash_map_put(&map, (void*)i, (void*)values[i]);
    }

    char* anwser = "0:this is string 0.1:this is string 1.2:this is string 2.3:this is string 3.4:this is string 4.5:this is string 5.6:this is string 6.7:this is string 7.8:this is string 8.9:this is string 9.10:this is string 10.11:this is string 11.12:this is string 12.13:this is string 13.14:this is string 14.15:this is string 15.16:this is string 16.17:this is string 17.18:this is string 18.19:this is string 19.20:this is string 20.21:this is string 21.22:this is string 22.23:this is string 23.24:this is string 24.25:this is string 25.26:this is string 26.27:this is string 27.28:this is string 28.29:this is string 29.30:this is string 30.31:this is string 31.32:this is string 32.33:this is string 33.34:this is string 34.35:this is string 35.36:this is string 36.37:this is string 37.38:this is string 38.39:this is string 39.40:this is string 40.41:this is string 41.42:this is string 42.43:this is string 43.44:this is string 44.45:this is string 45.46:this is string 46.47:this is string 47.48:this is string 48.49:this is string 49.";
    char str[2048] = {0};
    memset(str, 0, sizeof(str));
    Entry* iter = chash_map_iterator_begin(&map);

    while(iter != chash_map_iterator_end(&map)){
        char numStr[5] = {0};
        sprintf(numStr, "%d", ((int)iter->key));
        strcat(str, numStr);
        strcat(str, ":");
        strcat(str, (char*)iter->value);
        iter = chash_map_iterator_next(&map, iter);
    }

    assert(strcmp(str, anwser) == 0);

    chash_map_deinit(&map);
    assert(map.table == NULL);
}

/* Check put, resize,get,remove */
int chashmap_test8(){
    cHashMap map;
    chash_map_init(&map, 16, hash_func_int, compare_key_int);
    assert(map.size == 16);

    for(int i = 0; i < 16; i++){
        for(int j = i; j < 50; j += 16){
            chash_map_put(&map, (void*)j, (void*)values[j]);
        }
    }

    for(int i = 0; i < 50; i++){
        int cmp = strcmp(values[i], (char*)chash_map_get(&map, (void*)i));
        assert(cmp == 0);
    }

    chash_map_deinit(&map);
    assert(map.table == NULL);
}


/* Check put, resize,get,remove */
int chashmap_test9(){
    cHashMap map;
    chash_map_init(&map, 16, hash_func_int, compare_key_int);
    assert(map.size == 16);

    for(int i = 0; i < 12; i++){
        for(int j = i; j < 50; j += 16){
            chash_map_put(&map, (void*)j, (void*)values[j]);
        }
    }
    
    for(int i = 0; i < 12; i++){
        for(int j = i; j < 50; j += 16){
            chash_map_put(&map, (void*)j, (void*)values[j]);
        }
    }

    chash_map_remove(&map, (void*)0);
    chash_map_remove(&map, (void*)16);
    chash_map_remove(&map, (void*)32);
    chash_map_remove(&map, (void*)48);

    assert(NULL == chash_map_get(&map, (void*)0));
    assert(NULL == chash_map_get(&map, (void*)16));
    assert(NULL == chash_map_get(&map, (void*)32));
    assert(NULL == chash_map_get(&map, (void*)48));

    assert(map.used == 11);

    for(int i = 1; i < 12; i++){
        for(int j = i; j < 50; j += 16){
            int cmp = strcmp(values[j], (char*)chash_map_get(&map, (void*)j));
            assert(cmp == 0);
        }
    }
    
    for(int i = 0; i < 16; i++){
        for(int j = i; j < 50; j += 16){
            chash_map_remove(&map, (void*)j);
            assert(NULL == chash_map_get(&map, (void*)j));
        }
    }

    assert(NULL == chash_map_iterator_begin(&map));

    chash_map_deinit(&map);
    assert(map.table == NULL);
}

typedef int (*test_func_t)();

test_func_t testSet[] = {
    chashmap_test1,
    chashmap_test2,
    chashmap_test3,
    chashmap_test4,
    chashmap_test5,
    chashmap_test6,
    chashmap_test7,
    chashmap_test8,
    chashmap_test9,
};

int chashmap_test(){
    for(int i = 0; i < sizeof(testSet)/sizeof(test_func_t); i++){
        cutil_logd("run test %d...\n", i);
        testSet[i]();
    }
    return 0;
}