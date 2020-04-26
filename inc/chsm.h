#ifndef _CHSM_
#define _CHSM_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef unsigned int chsm_evt_id_t;

typedef struct {
    chsm_evt_id_t               evtId;
    void*                       evtData;
} chsm_evt_t;

typedef bool (*chsm_cond_func_t)(chsm_evt_t* evt);
typedef bool (*chsm_proc_func_t)(chsm_evt_t* evt);
typedef void (*chsm_state_entry_func_t)(void);
typedef void (*chsm_state_exit_func_t)(void);

struct chsm_state_t;

typedef struct {
    chsm_evt_id_t               evtId;
    chsm_cond_func_t            condFunc;
    chsm_proc_func_t            procFunc;
    struct chsm_state_t*        dstState;
} chsm_matrix_item_t;

typedef struct chsm_state_t{
    int                         matrixCount;
    chsm_matrix_item_t*         matrix;
    chsm_state_entry_func_t     entryFunc;
    chsm_state_exit_func_t      exitFunc;
    struct chsm_state_t*        parentState;
    struct chsm_state_t*        nextState;
    struct chsm_state_t*        childState;
} chsm_state_t;

typedef struct {
    chsm_state_t*               curState;
} chsm_module_t;

bool chsm_module_post(chsm_module_t* module, chsm_evt_t* evt);

#ifdef __cplusplus
}
#endif

#endif