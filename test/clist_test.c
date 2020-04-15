#include "clist.h"
#include "stdio.h"
#include "cutil.h"
#include "assert.h"

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

int clist_test0(){
    clist_init(NULL);
    clist_deinit(NULL);
    clist_remove_head(NULL);
    clist_reverse(NULL);
    clist_add_head(NULL, NULL);
    clist_remove(NULL, NULL);
    clist_remove_cond(NULL, NULL, NULL);
    clist_find_cond(NULL, NULL, NULL);
    assert(clist_size(NULL) == 0);
}

int clist_test1(){
    cList list;

    clist_init(&list);
    assert(list.head == NULL);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[i]);
    }
    assert(clist_size(&list) == 50);

    cList temp = list;
    for(int i = 0; i < 50; i++){
        assert(temp.head->value == values[49 - i]);
        temp.head = temp.head->next;
    }

    clist_reverse(&list);
    assert(clist_size(&list) == 50);

    temp = list;
    for(int i = 0; i < 50; i++){
        assert(temp.head->value == values[i]);
        temp.head = temp.head->next;
    }

    for(int i = 0; i < 51; i++){
        clist_remove_head(&list);
    }
    assert(clist_size(&list) == 0);

    assert(list.head == NULL);

    clist_deinit(&list);

    return 0;
}

int clist_test2(){
    cList list;

    clist_init(&list);
    assert(list.head == NULL);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[i]);
    }
    assert(clist_size(&list) == 50);

    cList temp = list;
    for(int i = 0; i < 50; i++){
        assert(temp.head->value == values[49 - i]);
        temp.head = temp.head->next;
    }
    assert(temp.head == NULL);

    clist_remove(&list, 0);
    assert(clist_size(&list) == 49);
    temp = list;
    for(int i = 1; i < 50; i++){
        assert(temp.head->value == values[49 - i]);
        temp.head = temp.head->next;
    }
    assert(temp.head == NULL);
    
    clist_remove(&list, 0);
    assert(clist_size(&list) == 48);
    temp = list;
    for(int i = 2; i < 50; i++){
        assert(temp.head->value == values[49 - i]);
        temp.head = temp.head->next;
    }
    assert(temp.head == NULL);

    
    clist_remove(&list, list.size-1);
    assert(clist_size(&list) == 47);
    temp = list;
    for(int i = 2; i < 49; i++){
        assert(temp.head->value == values[49 - i]);
        temp.head = temp.head->next;
    }
    assert(temp.head == NULL);

    // temp = list;
    // while(temp){
    //     printf("%s\n", (char*)temp.head->value);
    //     temp.head = temp.head->next;
    // }
    
    cListNode* anwser = list.head->next;
    clist_remove(&list, 0);
    assert(clist_size(&list) == 46);
    temp = list;
    for(int i = 3; i < 49; i++){
        assert(temp.head->value == values[49 - i]);
        temp.head = temp.head->next;
    }
    assert(temp.head == NULL);
    assert(list.head == anwser);

    clist_deinit(&list);

    return 0;
}

int clist_test3(){
    cList list;

    clist_init(&list);
    assert(list.head == NULL);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[i]);
    }
    assert(clist_size(&list) == 50);

    assert(clist_remove(&list, 50) == RET_ERR_INDEX);
    clist_remove(&list, 49);
    clist_remove(&list, 48);
    clist_remove(&list, 47);
    clist_remove(&list, 46);
    assert(clist_size(&list) == 46);

    cList temp = list;
    for(int i = 0; i < 46; i++){
        assert(temp.head->value == values[49 - i]);
        temp.head = temp.head->next;
    }
    assert(temp.head == NULL);

    clist_deinit(&list);

    return 0;
}

int test_list_cond_func(cListNode* node, void* args){
    if(strcmp((char*)node->value, (char*)args) == 0){
        return 1;
    }else{
        return 0;
    }
}

int clist_test4(){
    cList list;

    clist_init(&list);
    assert(list.head == NULL);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[i]);
    }
    assert(clist_size(&list) == 50);

    clist_reverse(&list);
    assert(clist_size(&list) == 50);

    clist_remove_cond(&list, test_list_cond_func, "this is string 50.");
    assert(clist_size(&list) == 50);

    cList temp = list;
    for(int i = 0; i < 50; i++){
        assert(temp.head->value == values[i]);
        temp.head = temp.head->next;
    }
    assert(temp.head == NULL);


    clist_remove_cond(&list, test_list_cond_func, "this is string 49.");
    assert(clist_size(&list) == 49);
    
    temp = list;
    for(int i = 0; i < 49; i++){
        assert(temp.head->value == values[i]);
        temp.head = temp.head->next;
    }
    assert(temp.head == NULL);

    
    clist_remove_cond(&list, test_list_cond_func, "this is string 0.");
    clist_remove_cond(&list, test_list_cond_func, "this is string 1.");
    clist_remove_cond(&list, test_list_cond_func, "this is string 2.");
    clist_remove_cond(&list, test_list_cond_func, "this is string 3.");
    assert(clist_size(&list) == 45);
    
    temp = list;
    for(int i = 4; i < 49; i++){
        assert(temp.head->value == values[i]);
        temp.head = temp.head->next;
    }
    assert(temp.head == NULL);

    clist_deinit(&list);

    return 0;
}

int clist_test5(){
    cList list;

    clist_init(&list);
    assert(list.head == NULL);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[i]);
    }
    assert(clist_size(&list) == 50);

    clist_reverse(&list);
    assert(clist_size(&list) == 50);

    assert(clist_find_cond(&list, test_list_cond_func, "abc") == NULL);

    cListNode* node = clist_find_cond(&list, test_list_cond_func, "this is string 3.");

    assert(strcmp((char*)node->value, "this is string 3.") == 0);
    assert(clist_size(&list) == 50);

    clist_deinit(&list);

    return 0;
}

int clist_test6(){
    assert(clist_is_empty(NULL) == 1);

    cList list;

    clist_init(&list);
    assert(list.head == NULL);
    

    assert(clist_is_empty(&list) == 1);
    clist_add_head(&list, values[0]);
    assert(clist_is_empty(&list) == 0);
    clist_deinit(&list);

    return 0;
}

int clist_test7(){

    cList list;
    clist_init(&list);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[i]);
    }

    assert(clist_get(NULL, 50) == NULL);
    assert(clist_get(&list, 50) == NULL);
    assert(clist_get(&list, 100) == NULL);

    for(int i = 0; i < 50; i++){
        int cmp = strcmp((char*)clist_get(&list, i), values[49 - i]);
        assert(cmp == 0);
    }

    clist_deinit(&list);

    return 0;
}

int clist_test8(){
    
    assert(clist_set(NULL, 0, values[0]) == RET_ERR_NULL_POINTER);

    cList list;
    clist_init(&list);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[i]);
    }

    assert(clist_set(&list, 100, values[0]) == RET_ERR_INDEX);
    assert(clist_set(&list, 50, values[0]) == RET_ERR_INDEX);

    for(int i = 0; i < 50; i++){
        clist_set(&list, i, values[i]);
    }

    for(int i = 0; i < 50; i++){
        int cmp = strcmp((char*)clist_get(&list, i), values[i]);
        assert(cmp == 0);
    }

    clist_deinit(&list);

    return 0;
}

int clist_test9(){
    cList list;
    clist_init(&list);

    for(int i = 0; i < 40; i++){
        clist_add_head(&list, values[i]);
    }

    for(int i = 0; i < 40; i++){
        assert(clist_contains(&list, values[i], NULL) == 1);
    }

    for(int i = 40; i < 50; i++){
        assert(clist_contains(&list, values[i], NULL) == 0);
    }

    clist_deinit(&list);

    return 0;
}

int clist_test10(){
    assert(clist_add(NULL, 0, values[10]) == RET_ERR_NULL_POINTER);

    cList list;
    clist_init(&list);

    assert(clist_add(&list, 10, values[10]) == RET_ERR_INDEX);
    
    for(int i = 0; i < 50; i++){
        assert(clist_add(&list, i, values[i]) == RET_OK);
    }
    assert(clist_size(&list) == 50);

    for(int i = 0; i < 50; i++){
        int cmp = strcmp((char*)clist_get(&list, i), values[i]);
        assert(cmp == 0);
    }

    clist_deinit(&list);
    return 0;
}

int clist_test11(){
    cList list;
    clist_init(&list);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[i]);
    }

    for(int i = 0; i < 50; i++){
        clist_remove_object(&list, values[i]);
    }

    assert(clist_size(&list) == 0);

    clist_deinit(&list);

    return 0;
}

int clist_test12(){
    cList list;
    clist_init(&list);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[i]);
    }

    clist_reverse(&list);

    for(int i = 0; i < 50; i++){
        assert(clist_last_index_of(&list, values[i], NULL) == i);
    }

    for(int i = 0; i < 50; i++){
        assert(clist_index_of(&list, values[i], NULL) == i);
    }

    clist_deinit(&list);

    return 0;
}

int clist_test13(){
    cList list;
    clist_init(&list);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[0]);
    }

    clist_reverse(&list);
    
    assert(clist_last_index_of(&list, values[0], NULL) == 49);
    assert(clist_last_index_of(&list, values[1], NULL) == -1);
    assert(clist_last_index_of(&list, values[2], NULL) == -1);
    assert(clist_index_of(&list, values[1], NULL) == -1);
    assert(clist_index_of(&list, values[2], NULL) == -1);

    clist_deinit(&list);

    return 0;
}

int clist_test14(){
    cList list;
    clist_init(&list);
    cList listDst;
    clist_init(&listDst);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[i]);
    }

    clist_reverse(&list);
    
    assert(clist_sub_list(NULL, &listDst, 0, list.size) == RET_ERR_NULL_POINTER);
    assert(clist_sub_list(&list, NULL, 0, list.size) == RET_ERR_NULL_POINTER);
    
    assert(clist_sub_list(&list, &listDst, 100, list.size) == RET_ERR_INDEX);
    assert(clist_sub_list(&list, &listDst, 10, 0) == RET_ERR_INDEX);
    assert(clist_sub_list(&list, &listDst, 10, 100) == RET_ERR_INDEX);

    clist_deinit(&list);
    clist_deinit(&listDst);

    return 0;
}

int clist_test15(){
    cList list;
    clist_init(&list);
    cList listDst;
    clist_init(&listDst);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[i]);
    }

    clist_reverse(&list);
    
    assert(clist_sub_list(&list, &listDst, 0, list.size) == RET_OK);

    assert(clist_size(&listDst) == 50);

    for(int i = 0; i < 50; i++){
        int cmp = strcmp((char*)clist_get(&listDst, i), values[i]);
        assert(cmp == 0);
    }

    clist_deinit(&list);
    clist_deinit(&listDst);

    return 0;
}

int clist_test16(){
    cList list;
    clist_init(&list);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[i]);
    }

    int size = 0;
    void** ppArray = clist_to_array(&list, &size);

    assert(ppArray != NULL);
    assert(size == 50);

    for(int i = 0; i < 50; i++){
        assert(ppArray[i] == values[49 - i]);
    }

    cutil_free(ppArray);

    
    assert(clist_to_array(&list, NULL) == NULL);
    assert(clist_to_array(NULL, &size) == NULL);
    assert(size == 0);
    assert(clist_to_array(NULL, NULL) == NULL);

    clist_deinit(&list);
    return 0;
}

int clist_test17(){
    cList list;
    clist_init(&list);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[i]);
    }

    assert(clist_index_of(NULL, values[0], NULL) == -1);
    assert(clist_index_of(&list, "abc", NULL) == -1);

    clist_deinit(&list);
    return 0;
}

int clist_test18(){
    cList list;
    clist_init(&list);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[i]);
    }

    assert(clist_index_of(NULL, values[0], NULL) == -1);
    assert(clist_index_of(&list, "abc", NULL) == -1);

    clist_deinit(&list);
    return 0;
}


typedef int (*test_func_t)();

test_func_t listTestSet[] = {
    clist_test0,
    clist_test1,
    clist_test2,
    clist_test3,
    clist_test4,
    clist_test5,
    clist_test6,
    clist_test7,
    clist_test8,
    clist_test9,
    clist_test10,
    clist_test11,
    clist_test12,
    clist_test13,
    clist_test14,
    clist_test15,
    clist_test16,
    clist_test17,
    clist_test18,
};

void clist_test(){
    for(int i = 0; i < sizeof(listTestSet)/sizeof(test_func_t); i++){
        cutil_logd("run test %d...\n", i);
        listTestSet[i]();
    }
}