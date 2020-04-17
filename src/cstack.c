#include "cstack.h"
#include "stdio.h"

int cstack_init(cStack* stack){
    if(!stack)  return RET_ERR_NULL_POINTER;
    return clist_init(&stack->list);
}

int cstack_deinit(cStack* stack){
    if(!stack)  return RET_ERR_NULL_POINTER;
    return clist_deinit(&stack->list);
}

int cstack_push(cStack* stack, void* value){
    if(!stack)  return RET_ERR_NULL_POINTER;
    return clist_add_head(&stack->list, value);
}

void* cstack_pop(cStack* stack){
    if(!stack)  return NULL;

    void* pret = cstack_peek(stack);

    clist_remove_head(&stack->list);
    
    return pret;
}

void* cstack_peek(cStack* stack){
    if(!stack)  return NULL;

    return stack->list.head == NULL ? NULL : stack->list.head->value;
}

int cstack_size(cStack* stack){
    return clist_size(&stack->list);
}

int cstack_is_empty(cStack* stack){
    return cstack_size(stack) == 0;
}