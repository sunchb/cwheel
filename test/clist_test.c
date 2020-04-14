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
    clist_remove_forward(NULL, NULL);
    clist_remove_reverse(NULL, NULL);
    clist_remove_cond(NULL, NULL, NULL);
    clist_find_cond(NULL, NULL, NULL);
}

int clist_test1(){
    cList list;

    clist_init(&list);
    assert(list == NULL);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[i]);
    }

    cList temp = list;
    for(int i = 0; i < 50; i++){
        assert(temp->value == values[49 - i]);
        temp = temp->next;
    }

    clist_reverse(&list);

    temp = list;
    for(int i = 0; i < 50; i++){
        assert(temp->value == values[i]);
        temp = temp->next;
    }

    for(int i = 0; i < 50; i++){
        clist_remove_head(&list);
    }

    assert(list == NULL);

    clist_deinit(&list);

    return 0;
}

int clist_test2(){
    cList list;

    clist_init(&list);
    assert(list == NULL);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[i]);
    }

    cList temp = list;
    for(int i = 0; i < 50; i++){
        assert(temp->value == values[49 - i]);
        temp = temp->next;
    }
    assert(temp == NULL);

    clist_remove_forward(&list, 0);
    temp = list;
    for(int i = 1; i < 50; i++){
        assert(temp->value == values[49 - i]);
        temp = temp->next;
    }
    assert(temp == NULL);
    
    clist_remove_forward(&list, 0);
    temp = list;
    for(int i = 2; i < 50; i++){
        assert(temp->value == values[49 - i]);
        temp = temp->next;
    }
    assert(temp == NULL);

    
    clist_remove_reverse(&list, 0);
    temp = list;
    for(int i = 2; i < 49; i++){
        assert(temp->value == values[49 - i]);
        temp = temp->next;
    }
    assert(temp == NULL);

    // temp = list;
    // while(temp){
    //     printf("%s\n", (char*)temp->value);
    //     temp = temp->next;
    // }
    
    cList anwser = list->next;
    clist_remove_reverse(&list, 46);
    temp = list;
    for(int i = 3; i < 49; i++){
        assert(temp->value == values[49 - i]);
        temp = temp->next;
    }
    assert(temp == NULL);
    assert(list == anwser);

    clist_deinit(&list);

    return 0;
}

int clist_test3(){
    cList list;

    clist_init(&list);
    assert(list == NULL);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[i]);
    }

    clist_remove_forward(&list, 49);
    clist_remove_forward(&list, 48);
    clist_remove_forward(&list, 47);
    clist_remove_forward(&list, 46);

    cList temp = list;
    for(int i = 0; i < 46; i++){
        assert(temp->value == values[49 - i]);
        temp = temp->next;
    }
    assert(temp == NULL);

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
    assert(list == NULL);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[i]);
    }

    clist_reverse(&list);

    clist_remove_cond(&list, test_list_cond_func, "this is string 50.");

    cList temp = list;
    for(int i = 0; i < 50; i++){
        assert(temp->value == values[i]);
        temp = temp->next;
    }
    assert(temp == NULL);


    clist_remove_cond(&list, test_list_cond_func, "this is string 49.");
    
    temp = list;
    for(int i = 0; i < 49; i++){
        assert(temp->value == values[i]);
        temp = temp->next;
    }
    assert(temp == NULL);

    
    clist_remove_cond(&list, test_list_cond_func, "this is string 0.");
    clist_remove_cond(&list, test_list_cond_func, "this is string 1.");
    clist_remove_cond(&list, test_list_cond_func, "this is string 2.");
    clist_remove_cond(&list, test_list_cond_func, "this is string 3.");
    
    temp = list;
    for(int i = 4; i < 49; i++){
        assert(temp->value == values[i]);
        temp = temp->next;
    }
    assert(temp == NULL);

    clist_deinit(&list);

    return 0;
}

int clist_test5(){
    cList list;

    clist_init(&list);
    assert(list == NULL);

    for(int i = 0; i < 50; i++){
        clist_add_head(&list, values[i]);
    }

    clist_reverse(&list);

    assert(clist_find_cond(&list, test_list_cond_func, "abc") == NULL);

    cListNode* node = clist_find_cond(&list, test_list_cond_func, "this is string 3.");
    assert(strcmp((void*)node->value, "this is string 3.") == 0);

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
};

void clist_test(){
    for(int i = 0; i < sizeof(listTestSet)/sizeof(test_func_t); i++){
        cutil_logd("run test %d...\n", i);
        listTestSet[i]();
    }
}