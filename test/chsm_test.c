#include "chsm.h"
#include "cutil.h"
#include "stdio.h"

#define TEST_EVT_ID_START       (0x01)
#define TEST_EVT_ID_PAUSE       (0x02)
#define TEST_EVT_ID_STOP        (0x03)
#define TEST_EVT_ID_POWER_ON    (0x04)
#define TEST_EVT_ID_POWER_OFF   (0x05)

extern chsm_state_t stopState;
extern chsm_state_t startState;
extern chsm_state_t pauseState;
extern chsm_state_t startStoppingState;
extern chsm_state_t rootState;

void rootStateEntry();
void rootStateExit();
bool rootStatePowerOnProc(chsm_evt_t* evt);
bool rootStatePowerOffProc(chsm_evt_t* evt);

chsm_matrix_item_t rootStateMatrix[] = {
    {TEST_EVT_ID_POWER_ON, NULL, rootStatePowerOnProc, NULL},
    {TEST_EVT_ID_POWER_OFF, NULL, rootStatePowerOffProc, NULL},
};
 
chsm_state_t rootState = {
    2, rootStateMatrix, rootStateEntry, rootStateExit, NULL, NULL, NULL
};

void stopStateEntry();
void stopStateExit();
bool stopStateStartCond(chsm_evt_t* evt);
bool stopStateStartProc(chsm_evt_t* evt);
bool stopStatePauseCond(chsm_evt_t* evt);
bool stopStatePauseProc(chsm_evt_t* evt);

chsm_matrix_item_t stopStateMatrix[] = {
    {TEST_EVT_ID_START, stopStateStartCond, stopStateStartProc, &startState},
    {TEST_EVT_ID_PAUSE, stopStatePauseCond, stopStatePauseProc, NULL},
};
 
chsm_state_t stopState = {
    2, stopStateMatrix, stopStateEntry, stopStateExit, &rootState, NULL, NULL
};

void startStateEntry();
void startStateExit();
bool startStatePauseCond(chsm_evt_t* evt);
bool startStatePauseProc(chsm_evt_t* evt);
bool startStateStopCond(chsm_evt_t* evt);
bool startStateStopProc(chsm_evt_t* evt);
bool startStateStartProc(chsm_evt_t* evt);

chsm_matrix_item_t startStateMatrix[] = {
    {TEST_EVT_ID_PAUSE, startStatePauseCond, startStatePauseProc, &pauseState},
    {TEST_EVT_ID_STOP, startStateStopCond, startStateStopProc, &startStoppingState},
    {TEST_EVT_ID_START, NULL, startStateStartProc, NULL},
};

chsm_state_t startState = {
    3, startStateMatrix, startStateEntry, startStateExit, &rootState, NULL, NULL
};

void pauseStateEntry();
void pauseStateExit();
bool pauseStateStartCond(chsm_evt_t* evt);
bool pauseStateStartProc(chsm_evt_t* evt);
bool pauseStateStopCond(chsm_evt_t* evt);
bool pauseStateStopProc(chsm_evt_t* evt);

chsm_matrix_item_t pauseStateMatrix[] = {
    {TEST_EVT_ID_START, pauseStateStartCond, pauseStateStartProc, &startState},
    {TEST_EVT_ID_STOP, pauseStateStopCond, pauseStateStopProc, &stopState},
};

chsm_state_t pauseState = {
    2, pauseStateMatrix, pauseStateEntry, pauseStateExit, &rootState, NULL, NULL
};

void startStoppingStateEntry();
void startStoppingStateExit();
bool startStoppingStopCond(chsm_evt_t* evt);
bool startStoppingStopProc(chsm_evt_t* evt);
bool startStoppingStartProc(chsm_evt_t* evt);

chsm_matrix_item_t startStoppingStateMatrix[] = {
    {TEST_EVT_ID_STOP, startStoppingStopCond, startStoppingStopProc, &stopState},
    {TEST_EVT_ID_START, NULL, startStoppingStartProc, NULL},
};

chsm_state_t startStoppingState = {
    2, startStoppingStateMatrix, startStoppingStateEntry, startStoppingStateExit, &startState, NULL, NULL
};

chsm_module_t playerModule = {
    &stopState
};

void chsm_test(){
    chsm_evt_t evt;

    evt.evtId = TEST_EVT_ID_START;
    chsm_module_post(&playerModule, &evt);
    
    evt.evtId = TEST_EVT_ID_PAUSE;
    chsm_module_post(&playerModule, &evt);
    
    evt.evtId = TEST_EVT_ID_START;
    chsm_module_post(&playerModule, &evt);
    
    evt.evtId = TEST_EVT_ID_STOP;
    chsm_module_post(&playerModule, &evt);
    
    evt.evtId = TEST_EVT_ID_START;
    chsm_module_post(&playerModule, &evt);
    
    evt.evtId = TEST_EVT_ID_STOP;
    chsm_module_post(&playerModule, &evt);

    evt.evtId = TEST_EVT_ID_POWER_ON;
    chsm_module_post(&playerModule, &evt);
    
    evt.evtId = TEST_EVT_ID_POWER_OFF;
    chsm_module_post(&playerModule, &evt);

    return;
}

void rootStateEntry(){
    cutil_logd("\n");
}
void rootStateExit(){
    cutil_logd("\n");
}
bool rootStatePowerOnProc(chsm_evt_t* evt){
    cutil_logd("\n");
}
bool rootStatePowerOffProc(chsm_evt_t* evt){
    cutil_logd("\n");
}

void stopStateEntry(){
    cutil_logd("\n");
}
void stopStateExit(){
    cutil_logd("\n");
}
bool stopStateStartCond(chsm_evt_t* evt){
    cutil_logv("\n");
    return true;
}
bool stopStateStartProc(chsm_evt_t* evt){
    cutil_logv("\n");
    return true;
}
bool stopStatePauseCond(chsm_evt_t* evt){
    cutil_logv("\n");
    return true;
}
bool stopStatePauseProc(chsm_evt_t* evt){
    cutil_logv("\n");
    return true;
}

void startStateEntry(){
    cutil_logd("\n");
}

void startStateExit(){
    cutil_logd("\n");
}

bool startStatePauseCond(chsm_evt_t* evt){
    cutil_logv("\n");
    return true;
}

bool startStatePauseProc(chsm_evt_t* evt){
    cutil_logv("\n");
    return true;
}

bool startStateStopCond(chsm_evt_t* evt){
    cutil_logv("\n");
    return true;
}

bool startStateStopProc(chsm_evt_t* evt){
    cutil_logv("\n");
    return true;
}

bool startStateStartProc(chsm_evt_t* evt){
    cutil_logd("\n");
    return true;
}

void pauseStateEntry(){
    cutil_logd("\n");
}

void pauseStateExit(){
    cutil_logd("\n");
}

bool pauseStateStartCond(chsm_evt_t* evt){
    cutil_logv("\n");
    return true;
}

bool pauseStateStartProc(chsm_evt_t* evt){
    cutil_logv("\n");
    return true;
}

bool pauseStateStopCond(chsm_evt_t* evt){
    cutil_logv("\n");
    return true;
}

bool pauseStateStopProc(chsm_evt_t* evt){
    cutil_logv("\n");
    return true;
}


void startStoppingStateEntry(){
    cutil_logd("\n");
    chsm_evt_t evt;
    evt.evtId = TEST_EVT_ID_STOP;
    //chsm_module_post(&playerModule, &evt);
}

void startStoppingStateExit(){
    cutil_logd("\n");
}

bool startStoppingStopCond(chsm_evt_t* evt){
    cutil_logv("\n");
    return true;
}

bool startStoppingStopProc(chsm_evt_t* evt){
    cutil_logv("\n");
    return true;
}

bool startStoppingStartProc(chsm_evt_t* evt){
    cutil_logd("\n");
    return false;
}