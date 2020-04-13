#include "clist.h"
#include "stdio.h"


void printList(cList* list){
    cListNode* p = *list;
    while(p){
        printf("%d,", (int)(p->value));
        p = p->next;
    }
    printf("\n");
}

int clist_cond_test(cListNode* node, void* args){
    //printf("%s,%d\n", __FUNCTION__, (int)(node->value));
    if(((int)(node->value)) == (int)args){
        return 1;
    }else{
        return 0;
    }
}

void clist_test(){
    cList list;

    clist_init(&list);

    for(int i = 0; i < 10; i++){
        clist_add_head(&list, (void*)i);
    }

    printList(&list);
    clist_reverse(&list);

    printList(&list);
    
    clist_remove_cond(&list, clist_cond_test, (void*)5);
    printList(&list);

    clist_deinit(&list);
}