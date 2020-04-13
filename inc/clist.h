#ifndef _CLIST_
#define _CLIST_

#ifdef __cplusplus
extern "C" {
#endif

#include "cdef.h"

typedef struct cListNode {
    void*               value;
    struct cListNode*   next;
}cListNode, *cList;

typedef int (*clist_cond_func_t)(cListNode* node, void* args);

int clist_init(cList* list);
int clist_deinit(cList* list);
int clist_add_head(cList* list, void* value);
int clist_remove_head(cList* list);
int clist_reverse(cList* list);
int clist_remove_forward(cList* list, int index);
int clist_remove_reverse(cList* list, int index);
int clist_remove_cond(cList* list, clist_cond_func_t condFunc, void* args);
cListNode* clist_find_cond(cList* list, clist_cond_func_t condFunc, void* args);

#ifdef __cplusplus
}
#endif

#endif