#include "cstack.h"
#include "assert.h"
#include "string.h"
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

int cstack_test0(){
    assert(cstack_init(NULL)  == RET_ERR_NULL_POINTER);
    assert(cstack_deinit(NULL)  == RET_ERR_NULL_POINTER);
    assert(cstack_push(NULL, values[0]) == RET_ERR_NULL_POINTER);
    assert(cstack_pop(NULL) == NULL);
    assert(cstack_peek(NULL) == NULL);
    assert(cstack_size(NULL) == 0);
    assert(cstack_is_empty(NULL) == 1);
}

int cstack_test1(){
    cStack stack;
    cstack_init(&stack);
    assert(cstack_is_empty(&stack) == 1);

    for(int i = 0; i < 50; i++){
        cstack_push(&stack, values[i]);
    }
    assert(cstack_size(&stack) == 50);
    assert(cstack_is_empty(&stack) == 0);

    for(int i = 49; i >= 0; i--){
        int cmp = strcmp(values[i], cstack_peek(&stack));
        assert(cmp == 0);
        
        cmp = strcmp(values[i], cstack_pop(&stack));
        assert(cmp == 0);
        
        assert(cstack_size(&stack) == i);
    }

    assert(cstack_size(&stack) == 0);
    assert(cstack_is_empty(&stack) == 1);
    assert(cstack_peek(&stack) == NULL);

    cstack_deinit(&stack);
}


typedef int (*test_func_t)();

test_func_t stackTestSet[] = {
    cstack_test0,
    cstack_test1,
};

int cstack_test(){
    for(int i = 0; i < sizeof(stackTestSet)/sizeof(test_func_t); i++){
        cutil_logd("run test %d...\n", i);
        stackTestSet[i]();
    }
    return 0;
}