#include "stdio.h"
#include "chashmap.h"

int hash_func_int(void* key){
    return (int)key;
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

int compare_key_int(void* a, void* b){
    return (int)a - (int)b;
}

int loop_func_print(Entry* entry, int row, int column){
    if(column == 0) printf("row[%d]:", row);

    if(entry == NULL){
        printf("null.\n");
    }else{
        printf("%d->", (int)(entry->key));
    }
    return 0;
}

int loop_func_print2(Entry* entry, int row, int column){
    if(entry) printf("%d:%s\n", (int)(entry->key), (char*)(entry->value));
    return 0;
}

int chashmap_test(){
    cHashMap map;
    //chash_map_init(&map, 16, hash_func_int2, compare_key_int);
    chash_map_init(&map, 16, hash_func_int, compare_key_int);

    const char* values[] = {
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

    for(int i = 0; i < 50; i++){
        cash_map_put(&map, (void*)i, (void*)values[i]);
    }

    printf("used:%d/%d\n", map.used, map.size);
    chash_map_remove(&map, (void*)129);
    printf("used:%d/%d\n", map.used, map.size);
    chash_map_remove(&map, (void*)126);
    printf("used:%d/%d\n", map.used, map.size);
    chash_map_remove(&map, (void*)1);
    printf("used:%d/%d\n", map.used, map.size);
    
    chash_map_loop_all(&map, loop_func_print);
    chash_map_loop(&map, loop_func_print2);


    Entry* iter = cash_map_iterator_begin(&map);

    while(iter != NULL){
        printf("Iter:%d\n", (int)(iter->key));
        iter = cash_map_iterator_next(&map, iter);
    }

    cash_map_deinit(&map);

    return 0;
}