#include "ring.hpp"


extern int RING_DEBUG_TRACE_COROUTINE_SCHED;


//
static std::unordered_map<CO_ID, RingCoroutine*> coroutine_map;

//
// static RingCoroutine* root_coroutine = nullptr;

//
static CO_ID global_coroutine_id = 0;

//
static CO_ID get_next_coroutine_id() {
    return global_coroutine_id++;
}


// FIXME: 这里写的不太好，rvm->executer 有可能还是 nullptr，需要确定初始化时机
// TODO: 这里应该 拆分成 create 和 launch 两个函数，类似于  launch 和 resume 函数
RingCoroutine* launch_root_coroutine(Ring_VirtualMachine* rvm) {
    RingCoroutine* co = (RingCoroutine*)mem_alloc(rvm->meta_pool, sizeof(RingCoroutine));
    co->co_id         = get_next_coroutine_id();
    co->p_co_id       = -1;
    co->last_run_time = -1;
    co->status        = CO_STAT_INIT;
    co->runtime_stack = new_runtime_stack();
    co->call_info     = nullptr;

    // step-1: new and stroe callinfo
    RVM_CallInfo* callinfo         = (RVM_CallInfo*)mem_alloc(rvm->meta_pool, sizeof(RVM_CallInfo));
    callinfo->caller_object        = nullptr;
    callinfo->caller_function      = nullptr;
    callinfo->caller_stack_base    = 0;
    callinfo->callee_object        = nullptr;
    callinfo->callee_function      = nullptr;
    callinfo->callee_argument_size = 0;
    callinfo->code_list            = rvm->executer->bootloader_code_list;
    callinfo->code_size            = rvm->executer->bootloader_code_size;
    callinfo->pc                   = 0;
    callinfo->prev                 = nullptr;
    callinfo->next                 = nullptr;

    co->call_info                  = store_callinfo(co->call_info, callinfo);


    coroutine_map.insert(std::make_pair(co->co_id, co));

    return co;
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
RingCoroutine* launch_coroutine(Ring_VirtualMachine* rvm,
                                RVM_ClassObject** caller_object, RVM_Function** caller_function,
                                RVM_ClassObject* callee_object, RVM_Function* callee_function) {

    RingCoroutine* co = (RingCoroutine*)mem_alloc(rvm->meta_pool, sizeof(RingCoroutine));
    co->co_id         = get_next_coroutine_id();
    co->p_co_id       = VM_CUR_CO->co_id;
    co->last_run_time = -1;
    co->status        = CO_STAT_INIT;
    co->runtime_stack = new_runtime_stack();
    co->call_info     = nullptr;


    // step-1: new and stroe callinfo
    RVM_CallInfo* callinfo         = (RVM_CallInfo*)mem_alloc(rvm->meta_pool, sizeof(RVM_CallInfo));
    callinfo->caller_object        = *caller_object;
    callinfo->caller_function      = *caller_function;
    callinfo->caller_stack_base    = 0;
    callinfo->callee_object        = callee_object;
    callinfo->callee_function      = callee_function;
    callinfo->callee_argument_size = 0;
    callinfo->code_list            = callee_function->u.derive_func->code_list;
    callinfo->code_size            = callee_function->u.derive_func->code_size;
    callinfo->pc                   = -1;
    callinfo->prev                 = nullptr;
    callinfo->next                 = nullptr;

    //
    co->call_info = store_callinfo(co->call_info, callinfo);

    coroutine_map.insert(std::make_pair(co->co_id, co));


    if (RING_DEBUG_TRACE_COROUTINE_SCHED == 1) {
        printf_witch_yellow("[RING_DEBUG::trace_coroutine_sched] [create::] co_id:%llu\n", co->co_id);
    }

    return co;


    // TODO:
    // step-3: 初始化匿名函数的局部变量

    return co;
}

/*
 * resume_coroutine
 * @co_id: Which coroutine to resume
 */
int resume_coroutine(Ring_VirtualMachine* rvm,
                     CO_ID                target_co_id,
                     RVM_ClassObject** caller_object, RVM_Function** caller_function,
                     RVM_ClassObject* callee_object, RVM_Function* callee_function) {
    // 1. get coroutine by coID;
    // 2. 当前协程挂起
    // 3. 目标协程拉起

    // 目标协程记录pid


    RingCoroutine* curr_co   = rvm->current_coroutine;

    RingCoroutine* target_co = coroutine_map[target_co_id];
    if (target_co == nullptr) {
        // TODO: error-report
        return -1;
    }
    if (target_co->status == CO_STAT_DEAD) {
        return -1;
    }

    // 第一次被调度
    if (target_co->status == CO_STAT_INIT) {
        *caller_object   = target_co->call_info->callee_object;
        *caller_function = target_co->call_info->callee_function;
    }


    // step-2: 协程上下文切换
    curr_co->status = CO_STAT_SUSPENDED;

    target_co->call_info->pc += 1;

    target_co->status      = CO_STAT_RUNNING;
    target_co->p_co_id     = curr_co->co_id;
    rvm->current_coroutine = target_co;


    if (RING_DEBUG_TRACE_COROUTINE_SCHED == 1) {
        printf_witch_yellow("[RING_DEBUG::trace_coroutine_sched] [resume::] "
                            "co_id:%lld->%lld\n",
                            curr_co->co_id, target_co->co_id);

        printf_witch_yellow("[RING_DEBUG::trace_coroutine_sched] [resume::  store-old] "
                            "Coroutine{co_id:%lld, status:%d}\n",
                            curr_co->co_id, curr_co->status);
        printf_witch_yellow("[RING_DEBUG::trace_coroutine_sched] [resume::  store-old] "
                            "RuntimeStack{data:%p, top_index:%u, size:%u, capacity:%u}\n",
                            curr_co->runtime_stack->data, curr_co->runtime_stack->top_index, curr_co->runtime_stack->size, curr_co->runtime_stack->capacity);

        printf_witch_yellow("[RING_DEBUG::trace_coroutine_sched] [resume::restore-new] "
                            "Coroutine{co_id:%lld, status:%d}\n",
                            target_co->co_id, target_co->status);
        printf_witch_yellow("[RING_DEBUG::trace_coroutine_sched] [resume::restore-new] "
                            "RuntimeStack{data:%p, top_index:%u, size:%u, capacity:%u}\n",
                            target_co->runtime_stack->data, target_co->runtime_stack->top_index, target_co->runtime_stack->size, target_co->runtime_stack->capacity);
    }

    return 0;
}

/*
 * yield_coroutine
 * @co_id:
 * 协程让出CPU，交出控制权给他的parent
 * 如果 他没有parent，也就是 RootCoroutine，那么没有效果
 * TODO: 完善一下注释
 */
int yield_coroutine(Ring_VirtualMachine* rvm) {
    // 1. get coroutine by coID;
    // 2. set status to CO_STAT_SUSPENDED;
    // 3. save runtime stack;
    // 4. save call info;
    // 5. switch to parent coroutine

    RingCoroutine* curr_co      = rvm->current_coroutine;

    CO_ID          target_co_id = curr_co->p_co_id;
    RingCoroutine* target_co    = coroutine_map[target_co_id];
    if (target_co == nullptr) {
        // TODO: error-report
        printf("yield_coroutine error\n");
        return -1;
    }


    // 上下文切换
    curr_co->status = CO_STAT_SUSPENDED;

    target_co->call_info->pc += 1;

    target_co->status      = CO_STAT_RUNNING;

    rvm->current_coroutine = target_co;


    if (RING_DEBUG_TRACE_COROUTINE_SCHED == 1) {
        printf_witch_yellow("[RING_DEBUG::trace_coroutine_sched] [yield::] "
                            "co_id:%lld<-%lld\n",
                            target_co->co_id, curr_co->co_id);

        printf_witch_yellow("[RING_DEBUG::trace_coroutine_sched] [yield::  store-old] "
                            "Coroutine{co_id:%lld, status:%d}\n",
                            curr_co->co_id, curr_co->status);
        printf_witch_yellow("[RING_DEBUG::trace_coroutine_sched] [yield::  store-old] "
                            "RuntimeStack{data:%p, top_index:%u, size:%u, capacity:%u}\n",
                            curr_co->runtime_stack->data, curr_co->runtime_stack->top_index, curr_co->runtime_stack->size, curr_co->runtime_stack->capacity);

        printf_witch_yellow("[RING_DEBUG::trace_coroutine_sched] [yield::restore-new] "
                            "Coroutine{co_id:%lld, status:%d}\n",
                            target_co->co_id, target_co->status);
        printf_witch_yellow("[RING_DEBUG::trace_coroutine_sched] [yield::restore-new] "
                            "RuntimeStack{data:%p, top_index:%u, size:%u, capacity:%u}\n",
                            target_co->runtime_stack->data, target_co->runtime_stack->top_index, target_co->runtime_stack->size, target_co->runtime_stack->capacity);
    }


    return 0;
}


//
int finish_coroutine(Ring_VirtualMachine* rvm,
                     RVM_ClassObject** caller_object, RVM_Function** caller_function,
                     RVM_Function* callee_function) {


    CO_ID curr_co_id = rvm->current_coroutine->co_id;
    if (curr_co_id == 0) {
        // RootCoroutine finish
        // do nothing
        // TODO: 但是还得要销毁资源
        return 0;
    }


    RingCoroutine* curr_co      = rvm->current_coroutine;

    CO_ID          target_co_id = curr_co->p_co_id;
    RingCoroutine* target_co    = coroutine_map[target_co_id];
    if (target_co == nullptr) {
        // TODO: error-report
        printf("parent coroutine not found p_co_id:%llu\n", target_co_id);
        return -1;
    }


    // 上下文切换
    curr_co->status = CO_STAT_DEAD;


    target_co->call_info->pc += 1;
    target_co->status      = CO_STAT_RUNNING;

    rvm->current_coroutine = target_co;


    if (RING_DEBUG_TRACE_COROUTINE_SCHED == 1) {
        printf_witch_yellow("[RING_DEBUG::trace_coroutine_sched] [dead::] "
                            "co_id:%lld<-%lld\n",
                            target_co->co_id, curr_co->co_id);

        printf_witch_yellow("[RING_DEBUG::trace_coroutine_sched] [dead::    destory] "
                            "Coroutine{co_id:%lld, status:%d}\n",
                            curr_co->co_id, curr_co->status);
        printf_witch_yellow("[RING_DEBUG::trace_coroutine_sched] [dead::    destory] "
                            "RuntimeStack{data:%p, top_index:%u, size:%u, capacity:%u}\n",
                            curr_co->runtime_stack->data, curr_co->runtime_stack->top_index, curr_co->runtime_stack->size, curr_co->runtime_stack->capacity);


        printf_witch_yellow("[RING_DEBUG::trace_coroutine_sched] [dead::restore-new] "
                            "Coroutine{co_id:%lld, status:%d}\n",
                            target_co->co_id, target_co->status);
        printf_witch_yellow("[RING_DEBUG::trace_coroutine_sched] [dead::restore-new] "
                            "RuntimeStack{data:%p, top_index:%u, size:%u, capacity:%u}\n",
                            target_co->runtime_stack->data, target_co->runtime_stack->top_index, target_co->runtime_stack->size, target_co->runtime_stack->capacity);
    }

    coroutine_map.erase(curr_co_id);
    mem_free(rvm->meta_pool, curr_co, sizeof(RingCoroutine));
    // TODO: 复用 runtime_stack


    return 0;
}