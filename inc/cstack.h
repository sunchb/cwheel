#ifndef _CSTACK_
#define _CSTACK_

#ifdef __cplusplus
extern "C" {
#endif

#include "cdef.h"
#include "clist.h"


typedef struct {
    cList   list;
}cStack;

int cstack_init(cStack* stack);
int cstack_deinit(cStack* stack);
int cstack_push(cStack* stack, void* value);
void* cstack_pop(cStack* stack);
void* cstack_peek(cStack* stack);
int cstack_size(cStack* stack);
int cstack_is_empty(cStack* stack);

#ifdef __cplusplus
}
#endif

#endif