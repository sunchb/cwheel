#include "stdlib.h"
#include "clist.h"
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

    cListNode* pNode = (cListNode*)malloc(sizeof(cListNode));
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
    free(pTemp);
    return RET_OK;
}

int clist_reverse(cList* list){
    if(!list) return RET_ERR_NULL_POINTER;
    *list = clist_reverse_sub(*list);
    return RET_OK;
}

int clist_remove(cList* list, int index){
    if(index >= 0){
        return clist_remove_forward(list, index);
    }else{
        return clist_remove_reverse(list, -index);
    }
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
    cListNode* node = tempNode.next;

    while(node){
        if(index == 0){
            pre->next = node->next;
            free(node);
            break;
        }
        index--;
        pre = node;
        node = node->next;
    }

    *list = tempNode.next;
    return RET_OK;
}

int clist_remove_reverse(cList* list, int index){
    if(!list) return RET_ERR_NULL_POINTER;

    cListNode tempNode;
    tempNode.next = *list;
    
    cListNode* pre = &tempNode;
    cListNode* node = tempNode.next;

    while(node){
        if(index < 0){
            pre = pre->next;
        }else{
            index--;
        }
        node = node->next;
    }

    if(index < 0){
        node = pre->next;
        pre->next = node->next;
        free(node);
    }

    *list = tempNode.next;
    return RET_OK;
}

int clist_remove_cond(cList* list, clist_cond_func_t condFunc, void* args){
    if(!list) return RET_ERR_NULL_POINTER;

    cListNode tempNode;
    tempNode.next = *list;
    
    cListNode* pre = &tempNode;
    cListNode* node = tempNode.next;

    while(node){
        if(condFunc(node, args)){
            pre->next = node->next;
            free(node);
            break;
        }
        pre = node;
        node = node->next;
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