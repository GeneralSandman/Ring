#include "ring.hpp"


//
static std::unordered_map<CO_ID, RingCoroutine*> coroutine_map;

//
static RingCoroutine* root_coroutine = nullptr;

//
static CO_ID global_coroutine_id = 0;

//
static CO_ID get_next_coroutine_id() {
    return global_coroutine_id++;
}

//
RingCoroutine* get_current_coroutine(Ring_VirtualMachine* rvm) {
    return rvm->current_coroutine;
}


/*
 * launch_coroutine
 *
 * 创建一个新的协程但不运行
 *
 * runtime_stack: 独占
 * call_info: 独占
 *
 * constant_pool: 共享
 * runtime_static: 共享
 * runtime_heap: 共享
 *
 * meta_pool: 共享
 */
// TODO: 还需要什么参数
CO_ID launch_coroutine(Ring_VirtualMachine* rvm) {
    printf("launch_coroutine\n");

    RingCoroutine* co = (RingCoroutine*)mem_alloc(nullptr, sizeof(RingCoroutine));
    co->id            = get_next_coroutine_id();
    co->pid           = -1;
    co->last_run_time = -1;
    co->status        = CO_STAT_INIT;
    co->runtime_stack = new_runtime_stack();
    co->call_info     = nullptr;
    co->pc            = 0;

    coroutine_map.insert(std::make_pair(co->id, co));

    return co->id;
}

/*
 * resume_coroutine
 * @co_id: Which coroutine to resume
 */
void resume_coroutine(Ring_VirtualMachine* rvm, CO_ID co_id) {
    // 1. get coroutine by coID;
    // 2. 当前协程挂起
    // 3. 目标协程拉起

    // 目标协程记录pid

    if (coroutine_map.end() == coroutine_map.find(co_id)) {
        // not found co_id
        return;
    }

    RingCoroutine* p_co    = get_current_coroutine(rvm);
    RingCoroutine* co      = coroutine_map[co_id];

    co->pid                = p_co->id;
    co->status             = CO_STAT_RUNNING;


    rvm->current_coroutine = co;

    // 直接切换 current_coroutine 即可完成
    //  切换PC
    //  切换栈
    //  切换call_info
}

/*
 * yield_coroutine
 * @co_id:
 * 协程让出CPU，交出控制权给他的parent
 * 如果 他没有parent，也就是 RootCoroutine，那么没有效果
 * TODO: 完善一下注释
 */
void yield_coroutine(Ring_VirtualMachine* rvm) {
    // 1. get coroutine by coID;
    // 2. set status to CO_STAT_SUSPENDED;
    // 3. save runtime stack;
    // 4. save call info;
    // 5. switch to parent coroutine

    RingCoroutine* co   = get_current_coroutine(rvm);

    co->status          = CO_STAT_SUSPENDED;

    CO_ID          pid  = co->pid;
    RingCoroutine* p_co = coroutine_map[pid];
    p_co->status        = CO_STAT_RUNNING;
}


//
void finish_coroutine(Ring_VirtualMachine* rvm, CO_ID co_id) {

    RingCoroutine* co = get_current_coroutine(rvm);

    co->status        = CO_STAT_DEAD;

    CO_ID pid         = co->pid;
}