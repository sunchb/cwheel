#include "stdlib.h"
#include "clist.h"
#include "cutil.h"

static cListNode* clist_reverse_sub(cListNode* node);

int clist_init(cList* list){
    if(!list) return RET_ERR_NULL_POINTER;

    *list = NULL;

    return RET_OK;
}

int clist_deinit(cList* list){
    if(!list) return RET_ERR_NULL_POINTER;

    while(*list != NULL){
        clist_remove_head(list);
    }

    return RET_OK;
}

int clist_add_head(cList* list, void* value){
    if(!list) return RET_ERR_NULL_POINTER;

    cListNode* pNode = (cListNode*)cutil_malloc(sizeof(cListNode));
    if(!pNode) return RET_ERR_MEM;

    pNode->next = *list;
    pNode->value = value;
    *list = pNode;
    return RET_OK;
}

int clist_remove_head(cList* list){
    if(!list) return RET_ERR_NULL_POINTER;

    if(*list == NULL) return RET_OK;

    cListNode* pTemp = *list;
    *list = (*list)->next;
    cutil_free(pTemp);
    return RET_OK;
}

int clist_reverse(cList* list){
    if(!list) return RET_ERR_NULL_POINTER;
    *list = clist_reverse_sub(*list);
    return RET_OK;
}

cListNode* clist_reverse_sub(cListNode* node){
    if(node == NULL || node->next == NULL) return node;

    cListNode* pTemp = clist_reverse_sub(node->next);
    node->next->next = node;
    node->next = NULL;
    return pTemp;
}

int clist_remove_forward(cList* list, int index){
    if(!list) return RET_ERR_NULL_POINTER;

    cListNode tempNode;
    tempNode.next = *list;
    
    cListNode* pre = &tempNode;

    while(pre->next){
        if(index == 0){
            cListNode* p = pre->next;
            pre->next = pre->next->next;
            cutil_free(p);
            break;
        }
        index--;
        pre = pre->next;
    }

    *list = tempNode.next;
    return RET_OK;
}

int clist_remove_reverse(cList* list, int index){
    if(!list) return RET_ERR_NULL_POINTER;

    cListNode tempNode;
    tempNode.next = *list;
    
    cListNode* pre = &tempNode;
    cListNode* p2 = *list;
    while(p2){
        if(index < 0){
            pre = pre->next;
        }else{
            index--;
        }
        p2 = p2->next;
    }

    if(index < 0){
        cListNode* p = pre->next;
        pre->next = pre->next->next;
        cutil_free(p);
    }

    *list = tempNode.next;
    return RET_OK;
}

int clist_remove_cond(cList* list, clist_cond_func_t condFunc, void* args){
    if(!list) return RET_ERR_NULL_POINTER;

    cListNode tempNode;
    tempNode.next = *list;
    
    cListNode* pre = &tempNode;

    while(pre->next){
        if(condFunc(pre->next, args)){
            cListNode* p = pre->next;
            pre->next = pre->next->next;
            cutil_free(p);
        }else{
            pre = pre->next;
        }
    }

    *list = tempNode.next;
    return RET_OK;
}

cListNode* clist_find_cond(cList* list, clist_cond_func_t condFunc, void* args){
    if(!list) return NULL;

    cListNode* node = *list;
    while(node){
        if(condFunc(node, args)){
            return node;
        }
        node = node->next;
    }

    return NULL;
}