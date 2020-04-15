#include "stdlib.h"
#include "assert.h"
#include "clist.h"
#include "cutil.h"

static cListNode* clist_reverse_sub(cListNode* node);
static int clist_get_index(cList* list, void* value, clist_compare_func_t func, int flag);
static int clist_default_compare_func(void* a, void* b);
static int clist_default_cond_func(cListNode* node, void* args);
static cListNode* clist_get_node(cList* list, int index);

int clist_init(cList* list){
    if(!list) return RET_ERR_NULL_POINTER;

    list->head = NULL;
    list->size = 0;

    return RET_OK;
}

int clist_deinit(cList* list){
    if(!list) return RET_ERR_NULL_POINTER;

    while(list->head != NULL){
        clist_remove_head(list);
    }

    return RET_OK;
}

int clist_size(cList* list){
    if(!list) return 0;

    return list->size;
}

int clist_is_empty(cList* list){
    return (!list) || (list->size == 0);
}

int clist_contains(cList* list, void* value, clist_compare_func_t func){
    return clist_get_index(list, value, func, 0) != -1;
}

void* clist_get(cList* list, int index){
    cListNode* p = clist_get_node(list, index);
    return p == NULL ? NULL : p->value;
}

int clist_set(cList* list, int index, void* value){
    if(!list) return RET_ERR_NULL_POINTER;

    if(list->size <= index) return RET_ERR_INDEX;
    
    cListNode* p = clist_get_node(list, index);
    
    if(p != NULL) {
        p->value = value;
    }
    else{
        assert(0);
    }

    return RET_OK;
}

int clist_add_head(cList* list, void* value){
    if(!list) return RET_ERR_NULL_POINTER;

    cListNode* pNode = (cListNode*)cutil_malloc(sizeof(cListNode));
    if(!pNode) return RET_ERR_MEM;

    pNode->next = list->head;
    pNode->value = value;
    list->head = pNode;
    list->size++;
    return RET_OK;
}

int clist_add(cList* list, int index, void* value){
    if(!list) return RET_ERR_NULL_POINTER;

    if(list->size < index) return RET_ERR_INDEX;

    if(index == 0){
        clist_add_head(list, value);
    }else{
        cListNode* p = clist_get_node(list, index - 1);
        if(p){
            cListNode* pNew = (cListNode*)cutil_malloc(sizeof(cListNode));
            pNew->next = p->next;
            pNew->value = value;
            p->next = pNew;
            list->size++;
        }else{
            assert(0);
        }
    }

    return RET_OK;
}

int clist_remove(cList* list, int index){
    if(!list) return RET_ERR_NULL_POINTER;

    if(list->size <= index) return RET_ERR_INDEX;

    if(index == 0){
        clist_remove_head(list);
    }else{
        cListNode* p = clist_get_node(list, index - 1);
        if(p){
            cListNode* pDel = p->next;
            p->next = p->next->next;
            cutil_free(pDel);
            list->size--;
        }else{
            assert(0);
        }
    }

    return RET_OK;
}

int clist_remove_head(cList* list){
    if(!list) return RET_ERR_NULL_POINTER;

    if(list->head == NULL) return RET_OK;

    cListNode* pTemp = list->head;
    list->head = (list->head)->next;
    list->size--;
    cutil_free(pTemp);
    return RET_OK;
}

int clist_remove_object(cList* list, void* object){
    return clist_remove_cond(list, clist_default_cond_func, object);
}

int clist_remove_cond(cList* list, clist_cond_func_t condFunc, void* args){
    if(!list) return RET_ERR_NULL_POINTER;

    if(list->head == NULL) return RET_OK;

    if(condFunc(list->head, args)){
        clist_remove_head(list);
    }else{
        cListNode* node = list->head;
        
        while(node->next){
            if(condFunc(node->next, args)){
                cListNode* pDel = node->next;
                node->next = node->next->next;
                cutil_free(pDel);
                list->size--;
                break;
            }
            node = node->next;
        }
    }
}

cListNode* clist_find_cond(cList* list, clist_cond_func_t condFunc, void* args){
    if(!list) return NULL;

    cListNode* node = list->head;
    while(node){
        if(condFunc(node, args)){
            return node;
        }
        node = node->next;
    }

    return NULL;
}

int clist_index_of(cList* list, void* value, clist_compare_func_t func){
    return clist_get_index(list, value, func, 0);
}

int clist_last_index_of(cList* list, void* value, clist_compare_func_t func){
    return clist_get_index(list, value, func, 1);
}


int clist_sub_list(cList* srcList, cList* dstList, int fromIndex, int toIndex){
    if(!srcList || !dstList) return RET_ERR_NULL_POINTER;

    if(fromIndex > toIndex || toIndex > srcList->size){
        return RET_ERR_INDEX;
    }

    cListNode* p = clist_get_node(srcList, fromIndex);

    while(p && fromIndex < toIndex){
        clist_add_head(dstList, p->value);
        p = p->next;
    }

    clist_reverse(dstList);

    return RET_OK;
}

int clist_reverse(cList* list){
    if(!list) return RET_ERR_NULL_POINTER;
    list->head = clist_reverse_sub(list->head);
    return RET_OK;
}

void** clist_to_array(cList* list, int* size){
    if(!size) return NULL;

    if(!list){
        *size = 0;
        return NULL;
    }

    void** ret = (void**)cutil_malloc(sizeof(void*) * list->size);
    if(ret == NULL){
        *size = 0;
        return NULL;
    }

    cListNode* temp = list->head;
    *size = 0;
    while(temp != NULL){
        ret[(*size)++] = temp->value;
        temp = temp->next;
    }

    return ret;
}

static cListNode* clist_reverse_sub(cListNode* node){
    if(node == NULL || node->next == NULL) return node;

    cListNode* pTemp = clist_reverse_sub(node->next);
    node->next->next = node;
    node->next = NULL;
    return pTemp;
}

static int clist_default_cond_func(cListNode* node, void* args){
    return node->value == args ? 1 : 0;
}

static int clist_default_compare_func(void* a, void* b){
    return a - b;
}

static int clist_get_index(cList* list, void* arg, clist_compare_func_t func, int lastFlag){
    if(!list) return -1;

    if(func == NULL) func = clist_default_compare_func;

    int ret = -1;
    int index = 0;

    cListNode* temp = list->head;
    while(temp != NULL){
        if(func(arg, temp->value) == 0){
            ret = index;
            
            if(lastFlag == 0) break;
        }

        index++;
        temp = temp->next;
    }

    return ret;
}

static cListNode* clist_get_node(cList* list, int index){
    if(!list) return NULL;

    if(list->size <= index) return NULL;

    cListNode* temp = list->head;
    while(temp != NULL){
        if(index == 0){
            return temp;
        }
        index--;
        temp = temp->next;
    }
    assert(0);
    return NULL;
}