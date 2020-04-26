#include "chsm.h"
#include "cstack.h"
#include "stdio.h"
#include "cutil.h"

static void chsm_change_state(chsm_module_t* module, chsm_state_t* src, chsm_state_t* dst);

bool chsm_module_proc(chsm_module_t* module, chsm_evt_t* evt){
    if(!module || !evt) return false;
    bool ret = false;
    chsm_state_t* curState = module->curState;

    while(curState){
        for(int i = 0; i < curState->matrixCount; i++){
            if(evt->evtId == curState->matrix[i].evtId && (!curState->matrix[i].condFunc || curState->matrix[i].condFunc(evt))){
                if(curState->matrix[i].procFunc)
                    ret = curState->matrix[i].procFunc(evt);

                if(curState->matrix[i].dstState){
                    chsm_change_state(module, curState, curState->matrix[i].dstState);
                }
                if(ret) return ret;
            }
        }

        curState = curState->parentState;
    }

    return ret;
}

void chsm_change_state(chsm_module_t* module, chsm_state_t* src, chsm_state_t* dst){
    cStack srcStack;
    cStack dstStack;
    chsm_state_t* temp;

    cstack_init(&srcStack);
    cstack_init(&dstStack);

    temp = src;
    while(temp != NULL){
        cstack_push(&srcStack, temp);
        temp = temp->parentState;
    }
    
    temp = dst;
    while(temp != NULL){
        cstack_push(&dstStack, temp);
        temp = temp->parentState;
    }

    while(cstack_peek(&srcStack) == cstack_peek(&dstStack) && cstack_size(&srcStack) != 0){
        cstack_pop(&srcStack);
        cstack_pop(&dstStack);
    }

    temp = src;

    if(cstack_size(&srcStack) != 0){
        temp = src;
        chsm_state_t* top = (chsm_state_t*)cstack_peek(&srcStack);
        
        while(temp){
            temp->exitFunc();
            if(temp == top){
                break;
            }else{
                temp = temp->parentState;
            }
        }
    }

    while(temp = (chsm_state_t*)cstack_pop(&dstStack)){
        module->curState = temp;
        temp->entryFunc();
    }
    
    cstack_deinit(&srcStack);
    cstack_deinit(&dstStack);
}

bool chsm_module_post(chsm_module_t* module, chsm_evt_t* evt){
    chsm_module_proc(module, evt);
}