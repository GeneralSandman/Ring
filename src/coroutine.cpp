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

    init_coroutine_entry_func_local_variable(rvm,
                                             co,
                                             callee_object,
                                             callee_function,
                                             0);
    // callinfo->caller_stack_base = co->runtime_stack->top_index;

    if (RING_DEBUG_TRACE_COROUTINE_SCHED == 1) {
        printf_witch_yellow("[RING_DEBUG::trace_coroutine_sched] [create::] co_id:%llu\n", co->co_id);
    }


    // step-3: 初始化匿名函数的局部变量

    return co;
}

void init_coroutine_entry_func_local_variable(Ring_VirtualMachine* rvm,
                                              RingCoroutine*       co,
                                              RVM_ClassObject*     callee_object,
                                              RVM_Function*        function,
                                              unsigned int         argument_list_size) {
    // return;
    // 如果launch后边还跟着别的参数，那么，还应该将别的参数copy到 目标协程栈中
    // e.g.  launch(func_, func_arg1, func_arg2, func_arg3);
    // 需要将 func_arg1/func_arg2/func_arg3 copy到目标协程栈中
    // 用于初始化目标协程入口函数中的参数

    RVM_TypeSpecifier*   type_specifier            = nullptr;
    RVM_ClassDefinition* rvm_class_definition      = nullptr;
    RVM_ClassObject*     class_ob                  = nullptr;
    RVM_String*          string                    = nullptr;
    unsigned int         alloc_size                = 0;

    unsigned int         stack_argument_list_index = 0; // arguments list's absolute index in stack.
    unsigned int         block_local_var_offset    = 0;

    if (callee_object != nullptr) {
        // 不支持 launch(obj.method) 这种调用方式
        // TODO: error-report
        return;
    }

    for (unsigned int i = 0; i < function->local_variable_size;
         i++, block_local_var_offset++) {

        type_specifier = function->local_variable_list[i].type_specifier;

        // TODO: 后续抽象成宏
        switch (type_specifier->kind) {
        case RING_BASIC_TYPE_BOOL:
            co->runtime_stack->data[co->runtime_stack->top_index + block_local_var_offset].type         = RVM_VALUE_TYPE_BOOL;
            co->runtime_stack->data[co->runtime_stack->top_index + block_local_var_offset].u.bool_value = RVM_FALSE;
            break;

        case RING_BASIC_TYPE_INT:
            co->runtime_stack->data[co->runtime_stack->top_index + block_local_var_offset].type        = RVM_VALUE_TYPE_INT;
            co->runtime_stack->data[co->runtime_stack->top_index + block_local_var_offset].u.int_value = 0;
            break;

        case RING_BASIC_TYPE_INT64:
            co->runtime_stack->data[co->runtime_stack->top_index + block_local_var_offset].type          = RVM_VALUE_TYPE_INT64;
            co->runtime_stack->data[co->runtime_stack->top_index + block_local_var_offset].u.int64_value = 0;
            break;

        case RING_BASIC_TYPE_DOUBLE:
            co->runtime_stack->data[co->runtime_stack->top_index + block_local_var_offset].type           = RVM_VALUE_TYPE_DOUBLE;
            co->runtime_stack->data[co->runtime_stack->top_index + block_local_var_offset].u.double_value = 0.0;
            break;

        case RING_BASIC_TYPE_STRING:
            string     = new_string(rvm);
            alloc_size = init_string(rvm, string, ROUND_UP8(1));
            rvm_heap_list_add_object(rvm, (RVM_GC_Object*)string);
            rvm_heap_alloc_size_incr(rvm, alloc_size);
            co->runtime_stack->data[co->runtime_stack->top_index + block_local_var_offset].type           = RVM_VALUE_TYPE_STRING;
            co->runtime_stack->data[co->runtime_stack->top_index + block_local_var_offset].u.string_value = string;
            break;

        case RING_BASIC_TYPE_CLASS:
            rvm_class_definition                                                                            = &(rvm->class_list[type_specifier->u.class_def_index]);
            class_ob                                                                                        = rvm_new_class_object(rvm, rvm_class_definition);
            co->runtime_stack->data[co->runtime_stack->top_index + block_local_var_offset].type             = RVM_VALUE_TYPE_CLASS_OB;
            co->runtime_stack->data[co->runtime_stack->top_index + block_local_var_offset].u.class_ob_value = class_ob;
            break;

        default: break;
        }
    }

    co->runtime_stack->top_index += function->local_variable_size;
}

/*
 * resume_coroutine
 * @co_id: Which coroutine to resume
 */
int resume_coroutine(Ring_VirtualMachine* rvm,
                     CO_ID                target_co_id,
                     RVM_ClassObject** caller_object, RVM_Function** caller_function,
                     RVM_ClassObject* callee_object, RVM_Function* callee_function) {

    RingCoroutine* curr_co   = rvm->current_coroutine;

    RingCoroutine* target_co = coroutine_map[target_co_id];
    if (target_co == nullptr) {
        // TODO: error-report
        return -1;
    }
    if (target_co->status == CO_STAT_DEAD) {
        return -1;
    }
    if (target_co->co_id == curr_co->co_id) {
        // TODO: error-report
        // 不能自己唤醒自己
        return -1;
    }

    // 第一次被调度
    if (target_co->status == CO_STAT_INIT) {
        *caller_object   = target_co->call_info->callee_object;
        *caller_function = target_co->call_info->callee_function;
    }


    // 协程上下文切换
    curr_co->status    = CO_STAT_SUSPENDED;

    target_co->p_co_id = curr_co->co_id;
    target_co->status  = CO_STAT_RUNNING;
    target_co->call_info->pc += 1;

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

    RingCoroutine* curr_co      = rvm->current_coroutine;

    CO_ID          target_co_id = curr_co->p_co_id;
    RingCoroutine* target_co    = coroutine_map[target_co_id];
    if (target_co == nullptr) {
        // TODO: error-report
        printf("yield_coroutine error\n");
        return -1;
    }


    // 协程上下文切换
    curr_co->status          = CO_STAT_SUSPENDED;

    target_co->last_run_time = time(nullptr); // TODO: ns
    target_co->status        = CO_STAT_RUNNING;
    target_co->call_info->pc += 1;

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

    CO_ID          curr_co_id = rvm->current_coroutine->co_id;
    RingCoroutine* curr_co    = rvm->current_coroutine;
    if (curr_co_id == 0) {
        // RootCoroutine finish
        // do nothing
        // TODO: 但是还得要销毁资源
        return 0;
    }

    CO_ID          target_co_id = curr_co->p_co_id;
    RingCoroutine* target_co    = coroutine_map[target_co_id];
    if (target_co == nullptr) {
        // TODO: error-report
        printf("parent coroutine not found p_co_id:%llu\n", target_co_id);
        return -1;
    }


    // 上下文切换
    curr_co->status          = CO_STAT_DEAD;

    target_co->last_run_time = time(nullptr); // TODO: ns
    target_co->status        = CO_STAT_RUNNING;
    target_co->call_info->pc += 1;

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