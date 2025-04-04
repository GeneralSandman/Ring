#include "ring.hpp"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>


extern int             RING_DEBUG_TRACE_FUNC_BACKTRACE;
extern int             RING_DEBUG_TRACE_CLOSURE_FREE_VALUE;

extern RVM_Opcode_Info RVM_Opcode_Infos[];


// 通过绝对索引 获取 rvm->current_coroutine->runtime_stack->data 的数据
#define STACK_GET_TYPE_INDEX(index) \
    (VM_CUR_CO_STACK_DATA[(index)].type)
#define STACK_GET_BOOL_INDEX(index) \
    (VM_CUR_CO_STACK_DATA[(index)].u.bool_value)
#define STACK_GET_INT_INDEX(index) \
    (VM_CUR_CO_STACK_DATA[(index)].u.int_value)
#define STACK_GET_INT64_INDEX(index) \
    (VM_CUR_CO_STACK_DATA[(index)].u.int64_value)
#define STACK_GET_DOUBLE_INDEX(index) \
    (VM_CUR_CO_STACK_DATA[(index)].u.double_value)
#define STACK_GET_STRING_INDEX(index) \
    (VM_CUR_CO_STACK_DATA[(index)].u.string_value)
#define STACK_GET_CLASS_OB_INDEX(index) \
    (VM_CUR_CO_STACK_DATA[(index)].u.class_ob_value)
#define STACK_GET_ARRAY_INDEX(index) \
    (VM_CUR_CO_STACK_DATA[(index)].u.array_value)
#define STACK_GET_CLOSURE_INDEX(index) \
    (VM_CUR_CO_STACK_DATA[(index)].u.closure_value)

// 通过栈顶偏移 offset 获取 VM_CUR_CO_STACK_DATA
#define STACK_GET_TYPE_OFFSET(offset) \
    STACK_GET_TYPE_INDEX(VM_CUR_CO_STACK_TOP_INDEX + (offset))
#define STACK_GET_BOOL_OFFSET(offset) \
    STACK_GET_BOOL_INDEX(VM_CUR_CO_STACK_TOP_INDEX + (offset))
#define STACK_GET_INT_OFFSET(offset) \
    STACK_GET_INT_INDEX(VM_CUR_CO_STACK_TOP_INDEX + (offset))
#define STACK_GET_INT64_OFFSET(offset) \
    STACK_GET_INT64_INDEX(VM_CUR_CO_STACK_TOP_INDEX + (offset))
#define STACK_GET_DOUBLE_OFFSET(offset) \
    STACK_GET_DOUBLE_INDEX(VM_CUR_CO_STACK_TOP_INDEX + (offset))
#define STACK_GET_STRING_OFFSET(offset) \
    STACK_GET_STRING_INDEX(VM_CUR_CO_STACK_TOP_INDEX + (offset))
#define STACK_GET_CLASS_OB_OFFSET(offset) \
    STACK_GET_CLASS_OB_INDEX(VM_CUR_CO_STACK_TOP_INDEX + (offset))
#define STACK_GET_ARRAY_OFFSET(offset) \
    STACK_GET_ARRAY_INDEX(VM_CUR_CO_STACK_TOP_INDEX + (offset))
#define STACK_GET_CLOSURE_OFFSET(offset) \
    STACK_GET_CLOSURE_INDEX(VM_CUR_CO_STACK_TOP_INDEX + (offset))


// 通过绝对索引 设置 VM_CUR_CO_STACK_DATA
#define STACK_SET_BOOL_INDEX(index, value)                            \
    VM_CUR_CO_STACK_DATA[(index)].type         = RVM_VALUE_TYPE_BOOL; \
    VM_CUR_CO_STACK_DATA[(index)].u.bool_value = (value);
#define STACK_SET_INT_INDEX(index, value)                           \
    VM_CUR_CO_STACK_DATA[(index)].type        = RVM_VALUE_TYPE_INT; \
    VM_CUR_CO_STACK_DATA[(index)].u.int_value = (value);
#define STACK_SET_INT64_INDEX(index, value)                             \
    VM_CUR_CO_STACK_DATA[(index)].type          = RVM_VALUE_TYPE_INT64; \
    VM_CUR_CO_STACK_DATA[(index)].u.int64_value = (value);
#define STACK_SET_DOUBLE_INDEX(index, value)                              \
    VM_CUR_CO_STACK_DATA[(index)].type           = RVM_VALUE_TYPE_DOUBLE; \
    VM_CUR_CO_STACK_DATA[(index)].u.double_value = (value);
#define STACK_SET_STRING_INDEX(index, value)                              \
    VM_CUR_CO_STACK_DATA[(index)].type           = RVM_VALUE_TYPE_STRING; \
    VM_CUR_CO_STACK_DATA[(index)].u.string_value = (value);
#define STACK_SET_CLASS_OB_INDEX(index, value)                                \
    VM_CUR_CO_STACK_DATA[(index)].type             = RVM_VALUE_TYPE_CLASS_OB; \
    VM_CUR_CO_STACK_DATA[(index)].u.class_ob_value = (value);
#define STACK_SET_ARRAY_INDEX(index, value)                             \
    VM_CUR_CO_STACK_DATA[(index)].type          = RVM_VALUE_TYPE_ARRAY; \
    VM_CUR_CO_STACK_DATA[(index)].u.array_value = (value);
#define STACK_SET_CLOSURE_INDEX(index, value)                               \
    VM_CUR_CO_STACK_DATA[(index)].type            = RVM_VALUE_TYPE_CLOSURE; \
    VM_CUR_CO_STACK_DATA[(index)].u.closure_value = (value);

// 通过栈顶偏移 offset 设置 VM_CUR_CO_STACK_DATA
#define STACK_SET_BOOL_OFFSET(offset, value) \
    STACK_SET_BOOL_INDEX(VM_CUR_CO_STACK_TOP_INDEX + (offset), (value))
#define STACK_SET_INT_OFFSET(offset, value) \
    STACK_SET_INT_INDEX(VM_CUR_CO_STACK_TOP_INDEX + (offset), (value))
#define STACK_SET_INT64_OFFSET(offset, value) \
    STACK_SET_INT64_INDEX(VM_CUR_CO_STACK_TOP_INDEX + (offset), (value))
#define STACK_SET_DOUBLE_OFFSET(offset, value) \
    STACK_SET_DOUBLE_INDEX(VM_CUR_CO_STACK_TOP_INDEX + (offset), (value))
#define STACK_SET_STRING_OFFSET(offset, value) \
    STACK_SET_STRING_INDEX(VM_CUR_CO_STACK_TOP_INDEX + (offset), (value))
#define STACK_SET_CLASS_OB_OFFSET(offset, value) \
    STACK_SET_CLASS_OB_INDEX(VM_CUR_CO_STACK_TOP_INDEX + (offset), (value))
#define STACK_SET_ARRAY_OFFSET(offset, value) \
    STACK_SET_ARRAY_INDEX(VM_CUR_CO_STACK_TOP_INDEX + (offset), (value))
#define STACK_SET_CLOSURE_OFFSET(offset, value) \
    STACK_SET_CLOSURE_INDEX(VM_CUR_CO_STACK_TOP_INDEX + (offset), (value))

#define GET_FREE_VALUE(index)                                                        \
    ((VM_CUR_CO_CALLINFO->curr_closure->free_value_list[(index)].is_recur) ?         \
         (VM_CUR_CO_CALLINFO->curr_closure->free_value_list[(index)].u.recur->u.p) : \
         (VM_CUR_CO_CALLINFO->curr_closure->free_value_list[(index)].u.p))

#define FREE_SET_BOOL_INDEX(index, value) \
    (GET_FREE_VALUE(index))->u.bool_value = (value);
#define FREE_SET_INT_INDEX(index, value) \
    (GET_FREE_VALUE(index))->u.int_value = (value);
#define FREE_SET_INT64_INDEX(index, value) \
    (GET_FREE_VALUE(index))->u.int64_value = (value);
#define FREE_SET_DOUBLE_INDEX(index, value) \
    (GET_FREE_VALUE(index))->u.double_value = (value);
#define FREE_SET_STRING_INDEX(index, value) \
    (GET_FREE_VALUE(index))->u.string_value = (value);
#define FREE_SET_CLASS_OB_INDEX(index, value) \
    (GET_FREE_VALUE(index))->u.class_ob_value = (value);

#define FREE_GET_BOOL_INDEX(index) \
    (GET_FREE_VALUE(index))->u.bool_value;
#define FREE_GET_INT_INDEX(index) \
    (GET_FREE_VALUE(index))->u.int_value;
#define FREE_GET_INT64_INDEX(index) \
    (GET_FREE_VALUE(index))->u.int64_value;
#define FREE_GET_DOUBLE_INDEX(index) \
    (GET_FREE_VALUE(index))->u.double_value;
#define FREE_GET_STRING_INDEX(index) \
    (GET_FREE_VALUE(index))->u.string_value;
#define FREE_GET_CLASS_OB_INDEX(index) \
    (GET_FREE_VALUE(index))->u.class_ob_value;

#define STACK_COPY_INDEX(dst_index, src_index) \
    (VM_CUR_CO_STACK_DATA[(dst_index)] = VM_CUR_CO_STACK_DATA[(src_index)])

#define STACK_COPY_OFFSET(dst_offset, src_offset) \
    STACK_COPY_INDEX(VM_CUR_CO_STACK_TOP_INDEX + (dst_offset), VM_CUR_CO_STACK_TOP_INDEX + (src_offset))


// 通过绝对索引 设置 rvm->runtime_static->data
#define STATIC_SET_BOOL_INDEX(index, value)                     \
    VM_STATIC_DATA[(index)].type         = RVM_VALUE_TYPE_BOOL; \
    VM_STATIC_DATA[(index)].u.bool_value = (value);
#define STATIC_SET_INT_INDEX(index, value)                    \
    VM_STATIC_DATA[(index)].type        = RVM_VALUE_TYPE_INT; \
    VM_STATIC_DATA[(index)].u.int_value = (value);
#define STATIC_SET_INT64_INDEX(index, value)                      \
    VM_STATIC_DATA[(index)].type          = RVM_VALUE_TYPE_INT64; \
    VM_STATIC_DATA[(index)].u.int64_value = (value);
#define STATIC_SET_DOUBLE_INDEX(index, value)                       \
    VM_STATIC_DATA[(index)].type           = RVM_VALUE_TYPE_DOUBLE; \
    VM_STATIC_DATA[(index)].u.double_value = (value);
#define STATIC_SET_STRING_INDEX(index, value)                       \
    VM_STATIC_DATA[(index)].type           = RVM_VALUE_TYPE_STRING; \
    VM_STATIC_DATA[(index)].u.string_value = (value);
#define STATIC_SET_CLASS_OB_INDEX(index, value)                         \
    VM_STATIC_DATA[(index)].type             = RVM_VALUE_TYPE_CLASS_OB; \
    VM_STATIC_DATA[(index)].u.class_ob_value = (value);
#define STATIC_SET_ARRAY_INDEX(index, value)                      \
    VM_STATIC_DATA[(index)].type          = RVM_VALUE_TYPE_ARRAY; \
    VM_STATIC_DATA[(index)].u.array_value = (value);
#define STATIC_SET_CLOSURE_INDEX(index, value)                        \
    VM_STATIC_DATA[(index)].type            = RVM_VALUE_TYPE_CLOSURE; \
    VM_STATIC_DATA[(index)].u.closure_value = (value);


// 从后边获取 1BYTE的操作数
#define OPCODE_GET_1BYTE(p) \
    (((p)[0]))
// 从后边获取 2BYTE的操作数
#define OPCODE_GET_2BYTE(p) \
    (((p)[0] << 8) + (p)[1])
// 把两BYTE的操作数放到后边
#define OPCODE_SET_2BYTE(p, value) \
    (((p)[0] = (value) >> 8), ((p)[1] = value & 0xff))


RVM_RuntimeStack* new_runtime_stack() {
    RVM_RuntimeStack* stack = (RVM_RuntimeStack*)mem_alloc(NULL_MEM_POOL, sizeof(RVM_RuntimeStack));
    stack->top_index        = 0;
    stack->capacity         = 1024 * 1024; // FIXME: 先开辟一个大的空间
    stack->data             = (RVM_Value*)mem_alloc(NULL_MEM_POOL, stack->capacity * sizeof(RVM_Value));
    stack->size             = 0;
    return stack;
}

RVM_RuntimeStatic* new_runtime_static() {
    RVM_RuntimeStatic* runtime_static = (RVM_RuntimeStatic*)mem_alloc(NULL_MEM_POOL, sizeof(RVM_RuntimeStatic));
    runtime_static->data              = nullptr;
    runtime_static->size              = 0;
    return runtime_static;
}

RVM_RuntimeHeap* new_runtime_heap() {
    RVM_RuntimeHeap* runtime_heap = (RVM_RuntimeHeap*)mem_alloc(NULL_MEM_POOL, sizeof(RVM_RuntimeHeap));
    runtime_heap->alloc_size      = 0;
    runtime_heap->list            = nullptr;
    runtime_heap->threshold       = 10;
    return runtime_heap;
}

Ring_VirtualMachine* ring_virtualmachine_create() {
    Ring_VirtualMachine* rvm = (Ring_VirtualMachine*)mem_alloc(NULL_MEM_POOL, sizeof(Ring_VirtualMachine));
    rvm->executer            = nullptr;
    rvm->executer_entry      = nullptr;
    rvm->runtime_static      = new_runtime_static();
    rvm->runtime_heap        = new_runtime_heap();
    rvm->class_list          = nullptr;
    rvm->class_size          = 0;
    rvm->meta_pool           = create_mem_pool((char*)"RVM-Meta-Memory-Pool");
    rvm->data_pool           = create_mem_pool((char*)"RVM-Data-Memory-Pool");
    rvm->debug_config        = nullptr;
    rvm->current_coroutine   = nullptr;

    return rvm;
}

/*
 * 将vmcode加载到vm
 *
 * 1. Set rvm->executer
 * 2. Add static/global variable
 * 3. Init class list
 *
 */
void ring_virtualmachine_load_executer(Ring_VirtualMachine* rvm,
                                       ExecuterEntry*       executer_entry) {

    rvm->executer       = executer_entry->main_package_executer;
    rvm->executer_entry = executer_entry;

    // TODO: 目前只初始化main包的全局变量
    rvm_add_static_variable(rvm->executer, rvm->runtime_static);

    // add classes
    // TODO: 目前只初始化main包的class定义
    rvm->class_list = executer_entry->main_package_executer->class_list;
    rvm->class_size = executer_entry->main_package_executer->class_size;
}


/*
 * 对 vm 进行初始化
 *
 * 1. Init static/global variable
 *
 * 做好执行虚拟机代码的初始化
 * 对全局变量进行初始化
 * 对运行栈做初始化
 *
 */
void ring_virtualmachine_init(Ring_VirtualMachine* rvm) {
    rvm_init_static_variable(rvm, rvm->executer, rvm->runtime_static);

    rvm->current_coroutine = launch_root_coroutine(rvm);
}

/*
 * 将 package 中 所有的 全局变量添加到 runtime_static中
 */
void rvm_add_static_variable(Package_Executer*  executer,
                             RVM_RuntimeStatic* runtime_static) {

    runtime_static->size = executer->global_variable_size;
    runtime_static->data = (RVM_Value*)mem_alloc(NULL_MEM_POOL, runtime_static->size * sizeof(RVM_Value));
}

/*
 * 对全局变量进行初始化
 *
 * 1. TODO: 如果有初始化表达式的话，那就通过表达式来初始化
 * 2. 基础变量类型 通过默认值初始化
 * 3. class 类型 可初始化默认值
 * 4. array 类型 必须手动 new
 *
 */
void rvm_init_static_variable(Ring_VirtualMachine* rvm,
                              Package_Executer*    executer,
                              RVM_RuntimeStatic*   runtime_static) {

    unsigned int         size                 = executer->global_variable_size;
    RVM_Variable*        global_variable_list = executer->global_variable_list;
    RVM_TypeSpecifier*   type_specifier       = nullptr;
    RVM_ClassDefinition* rvm_class_definition = nullptr;
    RVM_String*          string               = nullptr;
    RVM_ClassObject*     class_ob             = nullptr;
    RVM_Array*           array                = nullptr;

    for (unsigned int i = 0; i < size; i++) {
        type_specifier = global_variable_list[i].type_specifier;

        switch (type_specifier->kind) {
        case RING_BASIC_TYPE_BOOL:
            STATIC_SET_BOOL_INDEX(i, RVM_FALSE);
            break;
        case RING_BASIC_TYPE_INT:
            STATIC_SET_INT_INDEX(i, 0);
            break;
        case RING_BASIC_TYPE_INT64:
            STATIC_SET_INT64_INDEX(i, 0);
            break;
        case RING_BASIC_TYPE_DOUBLE:
            STATIC_SET_DOUBLE_INDEX(i, 0.0);
            break;
        case RING_BASIC_TYPE_STRING:
            string = rvm_gc_new_string_meta(rvm);
            rvm_fill_string(rvm, string, ROUND_UP8(1));
            STATIC_SET_STRING_INDEX(i, string);
            break;
        case RING_BASIC_TYPE_CLASS:
            rvm_class_definition = &(rvm->class_list[type_specifier->u.class_def_index]);
            class_ob             = rvm_gc_new_class_ob_meta(rvm);
            rvm_fill_class_ob(rvm, class_ob, rvm_class_definition);
            STATIC_SET_CLASS_OB_INDEX(i, class_ob);
            break;

        case RING_BASIC_TYPE_ARRAY: {
            // 这里没有分配空间, 只分配了一下meta
            RVM_ClassDefinition* sub_class_definition = nullptr;
            RVM_TypeSpecifier*   sub_type_specifier   = type_specifier->u.array_t->sub;
            if (sub_type_specifier->kind == RING_BASIC_TYPE_CLASS) {
                sub_class_definition = &(rvm->class_list[sub_type_specifier->u.class_def_index]);
            }

            array = rvm_gc_new_array_meta(rvm,
                                          RVM_Array_Type(type_specifier->u.array_t->sub->kind), // 这里强制转化一下
                                          sub_class_definition,
                                          type_specifier->u.array_t->dimension);

            STATIC_SET_ARRAY_INDEX(i, array);
        } break;

        default:
            break;
        }
    }
}


/*
 * 运行 ring 字节码
 *
 * 1. 单线程运行
 * 2. 支持比较简单VM调试
 *    编译时打开 DEBUG_RVM_INTERACTIVE, Makefile
 *
 */
int ring_execute_vm_code(Ring_VirtualMachine* rvm) {

    RVM_ConstantPool*    constant_pool_list     = rvm->executer->constant_pool_list;

    unsigned int         runtime_static_index   = 0;
    unsigned int         oper_num               = 0;
    unsigned int         array_size             = 0;
    unsigned int         array_index            = 0;
    unsigned int         package_index          = 0;
    unsigned int         func_index             = 0;
    unsigned int         method_index           = 0;
    unsigned int         class_index            = 0;
    unsigned int         field_index            = 0;
    unsigned int         const_index            = 0;
    unsigned int         argument_list_size     = 0;
    unsigned int         caller_stack_offset    = 0;
    unsigned int         return_value_list_size = 0;
    unsigned int         free_value_index       = 0;

    unsigned int         dst_offset             = 0;
    unsigned int         src_offset             = 0;

    bool                 bool_value             = false;
    int                  int_value              = 0;
    long long            int64_value            = 0;
    double               double_value           = 0;
    RVM_String*          string_value           = nullptr;
    RVM_ClassObject*     class_ob_value         = nullptr;
    RVM_Array*           array_value            = nullptr;
    RVM_Array*           array_c_value          = nullptr;
    RVM_Closure*         closure_value          = nullptr;
    RVM_Function*        anonymous_func         = nullptr;

    RVM_ClassDefinition* rvm_class_definition   = nullptr;
    RingCoroutine*       new_coroutine          = nullptr;
    CO_ID                co_id                  = 0;

    int                  exit_code              = 0;
    RVM_Frame            frame                  = RVM_Frame{};
    RVM_Byte             prev_opcde             = 0;
    RVM_Byte             opcode                 = 0;
    unsigned int         prev_code_line_number  = 0;
    int                  res                    = 0;

    unsigned int         dimension              = 0;
    unsigned int*        dimension_list         = (unsigned int*)mem_alloc(rvm->meta_pool, sizeof(unsigned int) * MAX_DIMENSION_NUM);


    RVM_ClassObject*     caller_class_ob        = nullptr;
    RVM_Function*        caller_function        = nullptr;
    RVM_Closure*         caller_closure         = nullptr;

    RVM_ClassObject*     callee_class_ob        = nullptr;
    RVM_Function*        callee_function        = nullptr;
    RVM_Method*          callee_method          = nullptr;

    RVM_DeferItem*       defer_item             = nullptr;


    for (; VM_CUR_CO_PC < VM_CUR_CO_CODE_SIZE; prev_opcde = opcode) {
        opcode = VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC];

#ifdef DEBUG_RVM_INTERACTIVE
        int debug_rvm_res = 0;
        debug_rvm_res     = debug_rvm_interactive(rvm, VM_CUR_CO_CALLINFO->callee_function, VM_CUR_CO_CODE_LIST, VM_CUR_CO_CODE_SIZE, VM_CUR_CO_PC, VM_CUR_CO_CSB);
        if (debug_rvm_res != 0) {
            goto EXIT;
        }
#endif

        if (rvm->debug_config != nullptr && rvm->debug_config->enable) {
            assert(rvm->debug_config->trace_dispatch != nullptr);

            std::vector<std::pair<std::string, RVM_Value*>> globals;
            std::vector<std::pair<std::string, RVM_Value*>> locals;


            // 2. build globals
            for (int i = 0; i < rvm->executer->global_variable_size; i++) {
                std::pair<std::string, RVM_Value*> global = {
                    std::string(rvm->executer->global_variable_list[i].identifier),
                    &(VM_STATIC_DATA[i]),
                };
                globals.push_back(global);
            }

            // 3. build locals
            if (VM_CUR_CO_CALLINFO != nullptr
                && VM_CUR_CO_CALLINFO->callee_function != nullptr) {
                for (unsigned int i = 0; i < VM_CUR_CO_CALLINFO->callee_function->local_variable_size; i++) {
                    std::pair<std::string, RVM_Value*> local = {
                        std::string(VM_CUR_CO_CALLINFO->callee_function->local_variable_list[i].identifier),
                        &(VM_CUR_CO_STACK_DATA[VM_CUR_CO_CSB + i]),
                    };
                    locals.push_back(local);
                }
            }

            // 4.
            const char* event;
            if (opcode == RVM_CODE_INVOKE_FUNC || opcode == RVM_CODE_INVOKE_METHOD) {
                event = TRACE_EVENT_CALL;
            } else if (opcode == RVM_CODE_FUNCTION_FINISH) {
                event = TRACE_EVENT_RETURN;
            } else if (opcode == RVM_CODE_EXIT) {
                event = TRACE_EVENT_EXIT;
            } else {
                event = TRACE_EVENT_OPCODE;
            }

            if (prev_opcde == RVM_CODE_INVOKE_FUNC
                && str_eq(VM_CUR_CO_CALLINFO->callee_function->identifier, "main")) {
                event = TRACE_EVENT_SAE;
            }


            unsigned int source_line_number = 0;
            if (VM_CUR_CO_CALLINFO != nullptr
                && VM_CUR_CO_CALLINFO->callee_function != nullptr) {
                // TODO: 这里直接通过二分法查找, 这里需要优化一下:
                //       因为Opcode是一行一行运行的, opcode++, 可以用更快的方式找到对应的函数行数
                source_line_number = get_source_line_number_by_pc(VM_CUR_CO_CALLINFO->callee_function, VM_CUR_CO_PC);
            }

            if (source_line_number != 0
                && source_line_number != prev_code_line_number) {
                if (!str_eq(event, TRACE_EVENT_RETURN) && !str_eq(event, TRACE_EVENT_SAE)) {
                    event = TRACE_EVENT_LINE;
                }
                prev_code_line_number = source_line_number;
            }

            //
            frame = RVM_Frame{
                .rvm                = rvm,
                .call_info          = VM_CUR_CO_CALLINFO,
                .next_pc            = VM_CUR_CO_PC,
                .next_opcode        = (RVM_Opcode)opcode,
                .source_line_number = source_line_number,
                .globals            = globals,
                .locals             = locals,
                .event              = event,
            };
            rvm->debug_config->trace_dispatch(&frame, event, "");
        }

        switch (opcode) {
        // push int/int64/double/string const to stack
        case RVM_CODE_PUSH_BOOL:
            STACK_SET_BOOL_OFFSET(0, (RVM_Bool)OPCODE_GET_1BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]));
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 2;
            break;
        case RVM_CODE_PUSH_INT_1BYTE:
            STACK_SET_INT_OFFSET(0, OPCODE_GET_1BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]));
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 2;
            break;
        case RVM_CODE_PUSH_INT_2BYTE:
            STACK_SET_INT_OFFSET(0, OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]));
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_INT:
            const_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_INT_OFFSET(0, constant_pool_list[const_index].u.int_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_INT64:
            const_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_INT64_OFFSET(0, constant_pool_list[const_index].u.int64_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_DOUBLE:
            const_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_DOUBLE_OFFSET(0, constant_pool_list[const_index].u.double_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_STRING:
            const_index  = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            string_value = string_literal_to_rvm_string(rvm, constant_pool_list[const_index].u.string_value);
            STACK_SET_STRING_OFFSET(0, string_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;


        // static
        case RVM_CODE_POP_STATIC_BOOL:
            runtime_static_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STATIC_SET_BOOL_INDEX(runtime_static_index, STACK_GET_BOOL_OFFSET(-1));
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_STATIC_INT:
            runtime_static_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STATIC_SET_INT_INDEX(runtime_static_index, STACK_GET_INT_OFFSET(-1));
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_STATIC_INT64:
            runtime_static_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STATIC_SET_INT64_INDEX(runtime_static_index, STACK_GET_INT64_OFFSET(-1));
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_STATIC_DOUBLE:
            runtime_static_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STATIC_SET_DOUBLE_INDEX(runtime_static_index, STACK_GET_DOUBLE_OFFSET(-1));
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_STATIC_STRING:
            runtime_static_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STATIC_SET_STRING_INDEX(runtime_static_index, STACK_GET_STRING_OFFSET(-1));
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_STATIC_CLASS_OB:
            runtime_static_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STATIC_SET_CLASS_OB_INDEX(runtime_static_index, STACK_GET_CLASS_OB_OFFSET(-1));
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_STATIC_ARRAY:
            runtime_static_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            // This is shallow copy
            // array_value = STACK_GET_OBJECT_OFFSET(rvm, -1);
            // This is deep copy
            array_value = rvm_deep_copy_array(rvm, STACK_GET_ARRAY_OFFSET(-1));
            STATIC_SET_ARRAY_INDEX(runtime_static_index, array_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;

        case RVM_CODE_PUSH_STATIC_BOOL:
            runtime_static_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_BOOL_OFFSET(0, VM_STATIC_DATA[runtime_static_index].u.bool_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_STATIC_INT:
            runtime_static_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_INT_OFFSET(0, VM_STATIC_DATA[runtime_static_index].u.int_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_STATIC_INT64:
            runtime_static_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_INT64_OFFSET(0, VM_STATIC_DATA[runtime_static_index].u.int64_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_STATIC_DOUBLE:
            runtime_static_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_DOUBLE_OFFSET(0, VM_STATIC_DATA[runtime_static_index].u.double_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_STATIC_STRING:
            runtime_static_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_STRING_OFFSET(0, VM_STATIC_DATA[runtime_static_index].u.string_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_STATIC_CLASS_OB:
            runtime_static_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_CLASS_OB_OFFSET(0, VM_STATIC_DATA[runtime_static_index].u.class_ob_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_STATIC_ARRAY:
            runtime_static_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_ARRAY_OFFSET(0, VM_STATIC_DATA[runtime_static_index].u.array_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;


        // stack
        case RVM_CODE_POP_STACK_BOOL:
            caller_stack_offset = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_BOOL_INDEX(
                VM_CUR_CO_CSB + caller_stack_offset,
                STACK_GET_BOOL_OFFSET(-1));
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_STACK_INT:
            caller_stack_offset = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_INT_INDEX(
                VM_CUR_CO_CSB + caller_stack_offset,
                STACK_GET_INT_OFFSET(-1));
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_STACK_INT64:
            caller_stack_offset = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_INT64_INDEX(
                VM_CUR_CO_CSB + caller_stack_offset,
                STACK_GET_INT64_OFFSET(-1));
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_STACK_DOUBLE:
            caller_stack_offset = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_DOUBLE_INDEX(
                VM_CUR_CO_CSB + caller_stack_offset,
                STACK_GET_DOUBLE_OFFSET(-1));
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_STACK_STRING:
            caller_stack_offset = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_STRING_INDEX(
                VM_CUR_CO_CSB + caller_stack_offset,
                STACK_GET_STRING_OFFSET(-1));
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_STACK_CLASS_OB:
            caller_stack_offset = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_CLASS_OB_INDEX(
                VM_CUR_CO_CSB + caller_stack_offset,
                STACK_GET_CLASS_OB_OFFSET(-1));
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_STACK_ARRAY:
            caller_stack_offset = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            // This is shallow copy
            // array_value         = STACK_GET_ARRAY_OFFSET(-1);
            // This is deep copy
            array_value = rvm_deep_copy_array(rvm, STACK_GET_ARRAY_OFFSET(-1));
            STACK_SET_ARRAY_INDEX(
                VM_CUR_CO_CSB + caller_stack_offset,
                array_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_STACK_CLOSURE:
            caller_stack_offset = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            closure_value       = STACK_GET_CLOSURE_OFFSET(-1);
            STACK_SET_CLOSURE_INDEX(
                VM_CUR_CO_CSB + caller_stack_offset,
                closure_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;

        case RVM_CODE_PUSH_STACK_BOOL:
            caller_stack_offset = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_BOOL_OFFSET(0,
                                  STACK_GET_BOOL_INDEX(VM_CUR_CO_CSB + caller_stack_offset));
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_STACK_INT:
            caller_stack_offset = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_INT_OFFSET(0,
                                 STACK_GET_INT_INDEX(VM_CUR_CO_CSB + caller_stack_offset));
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_STACK_INT64:
            caller_stack_offset = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_INT64_OFFSET(0,
                                   STACK_GET_INT64_INDEX(VM_CUR_CO_CSB + caller_stack_offset));
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_STACK_DOUBLE:
            caller_stack_offset = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_DOUBLE_OFFSET(0,
                                    STACK_GET_DOUBLE_INDEX(VM_CUR_CO_CSB + caller_stack_offset));
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_STACK_STRING:
            caller_stack_offset = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_STRING_OFFSET(0,
                                    STACK_GET_STRING_INDEX(VM_CUR_CO_CSB + caller_stack_offset));
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_STACK_CLASS_OB:
            caller_stack_offset = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_CLASS_OB_OFFSET(0,
                                      STACK_GET_CLASS_OB_INDEX(VM_CUR_CO_CSB + caller_stack_offset));
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_STACK_ARRAY:
            caller_stack_offset = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_ARRAY_OFFSET(0,
                                   STACK_GET_ARRAY_INDEX(VM_CUR_CO_CSB + caller_stack_offset));
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_STACK_CLOSURE:
            caller_stack_offset = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_CLOSURE_OFFSET(0,
                                     STACK_GET_CLOSURE_INDEX(VM_CUR_CO_CSB + caller_stack_offset));
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;

        // free-value
        case RVM_CODE_POP_FREE_BOOL:
            free_value_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            bool_value       = STACK_GET_BOOL_OFFSET(-1);
            FREE_SET_BOOL_INDEX(free_value_index, (RVM_Bool)((int)bool_value));

            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_FREE_INT:
            free_value_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            int_value        = STACK_GET_INT_OFFSET(-1);
            FREE_SET_INT_INDEX(free_value_index, int_value);

            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_FREE_INT64:
            free_value_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            int64_value      = STACK_GET_INT64_OFFSET(-1);
            FREE_SET_INT64_INDEX(free_value_index, int64_value);

            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_FREE_DOUBLE:
            free_value_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            double_value     = STACK_GET_DOUBLE_OFFSET(-1);
            FREE_SET_DOUBLE_INDEX(free_value_index, double_value);

            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_FREE_STRING:
            free_value_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            string_value     = STACK_GET_STRING_OFFSET(-1);
            FREE_SET_STRING_INDEX(free_value_index, string_value);

            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_FREE_CLASS_OB:
            free_value_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            class_ob_value   = STACK_GET_CLASS_OB_OFFSET(-1);
            FREE_SET_CLASS_OB_INDEX(free_value_index, class_ob_value);

            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 3;
            break;

        case RVM_CODE_PUSH_FREE_BOOL:
            free_value_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            bool_value       = FREE_GET_BOOL_INDEX(free_value_index);
            STACK_SET_BOOL_OFFSET(0, (RVM_Bool)((int)bool_value));

            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_FREE_INT:
            free_value_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            int_value        = FREE_GET_INT_INDEX(free_value_index);
            STACK_SET_INT_OFFSET(0, int_value);

            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_FREE_INT64:
            free_value_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            int64_value      = FREE_GET_INT64_INDEX(free_value_index);
            STACK_SET_INT64_OFFSET(0, int64_value);

            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_FREE_DOUBLE:
            free_value_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            double_value     = FREE_GET_DOUBLE_INDEX(free_value_index);
            STACK_SET_DOUBLE_OFFSET(0, double_value);

            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_FREE_STRING:
            free_value_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            string_value     = FREE_GET_STRING_INDEX(free_value_index);
            STACK_SET_STRING_OFFSET(0, string_value);

            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_FREE_CLASS_OB:
            free_value_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            class_ob_value   = FREE_GET_CLASS_OB_INDEX(free_value_index);
            STACK_SET_CLASS_OB_OFFSET(0, class_ob_value);

            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;


        // array
        case RVM_CODE_PUSH_ARRAY_A:
            array_c_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index   = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            assert_throw_range(array_index, array_value->length);
            rvm_array_get_array(rvm, array_c_value, array_index, &array_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            STACK_SET_ARRAY_OFFSET(0, array_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_BOOL:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            assert_throw_range(array_index, array_value->length);
            rvm_array_get_bool(rvm, array_value, array_index, &bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            STACK_SET_BOOL_OFFSET(0, (RVM_Bool)((int)bool_value));
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_INT:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            assert_throw_range(array_index, array_value->length);
            rvm_array_get_int(rvm, array_value, array_index, &int_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            STACK_SET_INT_OFFSET(0, int_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_INT64:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            assert_throw_range(array_index, array_value->length);
            rvm_array_get_int64(rvm, array_value, array_index, &int64_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            STACK_SET_INT64_OFFSET(0, int64_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_DOUBLE:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            assert_throw_range(array_index, array_value->length);
            rvm_array_get_double(rvm, array_value, array_index, &double_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            STACK_SET_DOUBLE_OFFSET(0, double_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_STRING:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            assert_throw_range(array_index, array_value->length);
            rvm_array_get_string(rvm, array_value, array_index, &string_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            STACK_SET_STRING_OFFSET(0, string_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_CLASS_OB:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            assert_throw_range(array_index, array_value->length);
            rvm_array_get_class_object(rvm, array_value, array_index, &class_ob_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            STACK_SET_CLASS_OB_OFFSET(0, class_ob_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_CLOSURE:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            assert_throw_range(array_index, array_value->length);
            rvm_array_get_closure(rvm, array_value, array_index, &closure_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            STACK_SET_CLOSURE_OFFSET(0, closure_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 1;
            break;

        case RVM_CODE_POP_ARRAY_A:
            array_c_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index   = STACK_GET_INT_OFFSET(-1);
            array_value   = STACK_GET_ARRAY_OFFSET(-3);
            assert_throw_nil_array(array_value == nullptr);
            assert_throw_range(array_index, array_value->length);
            rvm_array_set_array(rvm, array_c_value, array_index, array_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 3;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_POP_ARRAY_BOOL:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            bool_value  = (bool)STACK_GET_BOOL_OFFSET(-3);
            assert_throw_nil_array(array_value == nullptr);
            assert_throw_range(array_index, array_value->length);
            rvm_array_set_bool(rvm, array_value, array_index, &bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 3;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_POP_ARRAY_INT:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            assert_throw_range(array_index, array_value->length);
            rvm_array_set_int(rvm, array_value, array_index, &STACK_GET_INT_OFFSET(-3));
            VM_CUR_CO_STACK_TOP_INDEX -= 3;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_POP_ARRAY_INT64:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            assert_throw_range(array_index, array_value->length);
            rvm_array_set_int64(rvm, array_value, array_index, &STACK_GET_INT64_OFFSET(-3));
            VM_CUR_CO_STACK_TOP_INDEX -= 3;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_POP_ARRAY_DOUBLE:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            assert_throw_range(array_index, array_value->length);
            rvm_array_set_double(rvm, array_value, array_index, &STACK_GET_DOUBLE_OFFSET(-3));
            VM_CUR_CO_STACK_TOP_INDEX -= 3;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_POP_ARRAY_STRING:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            assert_throw_range(array_index, array_value->length);
            rvm_array_set_string(rvm, array_value, array_index, &STACK_GET_STRING_OFFSET(-3));
            VM_CUR_CO_STACK_TOP_INDEX -= 3;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_POP_ARRAY_CLASS_OB:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            assert_throw_range(array_index, array_value->length);
            rvm_array_set_class_object(rvm, array_value, array_index, &STACK_GET_CLASS_OB_OFFSET(-3));
            VM_CUR_CO_STACK_TOP_INDEX -= 3;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_POP_ARRAY_CLOSURE:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            assert_throw_range(array_index, array_value->length);
            rvm_array_set_closure(rvm, array_value, array_index, &STACK_GET_CLOSURE_OFFSET(-3));
            VM_CUR_CO_STACK_TOP_INDEX -= 3;
            VM_CUR_CO_PC += 1;
            break;


        // array append
        case RVM_CODE_ARRAY_APPEND_BOOL:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            bool_value  = (bool)STACK_GET_BOOL_OFFSET(-1);
            rvm_array_append_bool(rvm, array_value, &bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_ARRAY_APPEND_INT:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            int_value   = STACK_GET_INT_OFFSET(-1);
            rvm_array_append_int(rvm, array_value, &int_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_ARRAY_APPEND_INT64:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            int64_value = STACK_GET_INT64_OFFSET(-1);
            rvm_array_append_int64(rvm, array_value, &int64_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_ARRAY_APPEND_DOUBLE:
            array_value  = STACK_GET_ARRAY_OFFSET(-2);
            double_value = STACK_GET_DOUBLE_OFFSET(-1);
            rvm_array_append_double(rvm, array_value, &double_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_ARRAY_APPEND_STRING:
            array_value  = STACK_GET_ARRAY_OFFSET(-2);
            string_value = STACK_GET_STRING_OFFSET(-1);
            rvm_array_append_string(rvm, array_value, &string_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_ARRAY_APPEND_CLASS_OB:
            array_value    = STACK_GET_ARRAY_OFFSET(-2);
            class_ob_value = STACK_GET_CLASS_OB_OFFSET(-1);
            rvm_array_append_class_object(rvm, array_value, &class_ob_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_ARRAY_APPEND_CLOSURE:
            array_value   = STACK_GET_ARRAY_OFFSET(-2);
            closure_value = STACK_GET_CLOSURE_OFFSET(-1);
            rvm_array_append_closure(rvm, array_value, &closure_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            VM_CUR_CO_PC += 1;
            break;

        // array pop
        case RVM_CODE_ARRAY_POP_BOOL:
            array_value = STACK_GET_ARRAY_OFFSET(-1);
            bool_value  = false;
            assert_throw_nil_array(array_value->length == 0);
            rvm_array_pop_bool(rvm, array_value, &bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            STACK_SET_BOOL_OFFSET(0, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_ARRAY_POP_INT:
            array_value = STACK_GET_ARRAY_OFFSET(-1);
            int_value   = 0;
            assert_throw_nil_array(array_value->length == 0);
            rvm_array_pop_int(rvm, array_value, &int_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            STACK_SET_INT_OFFSET(0, int_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_ARRAY_POP_INT64:
            array_value = STACK_GET_ARRAY_OFFSET(-1);
            int64_value = 0;
            assert_throw_nil_array(array_value->length == 0);
            rvm_array_pop_int64(rvm, array_value, &int64_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            STACK_SET_INT64_OFFSET(0, int64_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_ARRAY_POP_DOUBLE:
            array_value  = STACK_GET_ARRAY_OFFSET(-1);
            double_value = false;
            assert_throw_nil_array(array_value->length == 0);
            rvm_array_pop_double(rvm, array_value, &double_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            STACK_SET_DOUBLE_OFFSET(0, double_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_ARRAY_POP_STRING:
            array_value  = STACK_GET_ARRAY_OFFSET(-1);
            string_value = nullptr;
            assert_throw_nil_array(array_value->length == 0);
            rvm_array_pop_string(rvm, array_value, &string_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            STACK_SET_STRING_OFFSET(0, string_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_ARRAY_POP_CLASS_OB:
            array_value = STACK_GET_ARRAY_OFFSET(-1);
            assert_throw_nil_array(array_value->length == 0);
            rvm_array_pop_class_object(rvm, array_value, &class_ob_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            STACK_SET_CLASS_OB_OFFSET(0, class_ob_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_ARRAY_POP_CLOSURE:
            array_value = STACK_GET_ARRAY_OFFSET(-1);
            assert_throw_nil_array(array_value->length == 0);
            rvm_array_pop_closure(rvm, array_value, &closure_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            STACK_SET_CLOSURE_OFFSET(0, closure_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 1;
            break;


            // array
        case RVM_CODE_NEW_ARRAY_BOOL:
            dimension = OPCODE_GET_1BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            memset(dimension_list, 0, sizeof(unsigned int) * MAX_DIMENSION_NUM);
            for (unsigned int i = 0; i < dimension; i++) {
                dimension_list[dimension - 1 - i] = STACK_GET_INT_OFFSET(-(i + 1));
            }
            VM_CUR_CO_STACK_TOP_INDEX -= dimension;
            array_value = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_BOOL, nullptr);
            STACK_SET_ARRAY_OFFSET(0, array_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 2;
            break;
        case RVM_CODE_NEW_ARRAY_INT:
            dimension = OPCODE_GET_1BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            memset(dimension_list, 0, sizeof(unsigned int) * MAX_DIMENSION_NUM);
            for (unsigned int i = 0; i < dimension; i++) {
                dimension_list[dimension - 1 - i] = STACK_GET_INT_OFFSET(-(i + 1));
            }
            VM_CUR_CO_STACK_TOP_INDEX -= dimension;
            array_value = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_INT, nullptr);
            STACK_SET_ARRAY_OFFSET(0, array_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 2;
            break;
        case RVM_CODE_NEW_ARRAY_INT64:
            dimension = OPCODE_GET_1BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            memset(dimension_list, 0, sizeof(unsigned int) * MAX_DIMENSION_NUM);
            for (unsigned int i = 0; i < dimension; i++) {
                dimension_list[dimension - 1 - i] = STACK_GET_INT_OFFSET(-(i + 1));
            }
            VM_CUR_CO_STACK_TOP_INDEX -= dimension;
            array_value = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_INT64, nullptr);
            STACK_SET_ARRAY_OFFSET(0, array_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 2;
            break;
        case RVM_CODE_NEW_ARRAY_DOUBLE:
            dimension = OPCODE_GET_1BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            memset(dimension_list, 0, sizeof(unsigned int) * MAX_DIMENSION_NUM);
            for (unsigned int i = 0; i < dimension; i++) {
                dimension_list[dimension - 1 - i] = STACK_GET_INT_OFFSET(-(i + 1));
            }
            VM_CUR_CO_STACK_TOP_INDEX -= dimension;
            array_value = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_DOUBLE, nullptr);
            STACK_SET_ARRAY_OFFSET(0, array_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 2;
            break;
        case RVM_CODE_NEW_ARRAY_STRING:
            dimension = OPCODE_GET_1BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            memset(dimension_list, 0, sizeof(unsigned int) * MAX_DIMENSION_NUM);
            for (unsigned int i = 0; i < dimension; i++) {
                dimension_list[dimension - 1 - i] = STACK_GET_INT_OFFSET(-(i + 1));
            }
            VM_CUR_CO_STACK_TOP_INDEX -= dimension;
            array_value = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_STRING, nullptr);
            STACK_SET_ARRAY_OFFSET(0, array_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 2;
            break;
        case RVM_CODE_NEW_ARRAY_CLASS_OB:
            dimension = OPCODE_GET_1BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            memset(dimension_list, 0, sizeof(unsigned int) * MAX_DIMENSION_NUM);
            for (unsigned int i = 0; i < dimension; i++) {
                dimension_list[dimension - 1 - i] = STACK_GET_INT_OFFSET(-(i + 1));
            }
            VM_CUR_CO_STACK_TOP_INDEX -= dimension;

            class_index          = OPCODE_GET_1BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 2]);
            rvm_class_definition = &(rvm->class_list[class_index]);

            array_value          = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_CLASS_OBJECT, rvm_class_definition);
            STACK_SET_ARRAY_OFFSET(0, array_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_NEW_ARRAY_CLOSURE:
            dimension = OPCODE_GET_1BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            memset(dimension_list, 0, sizeof(unsigned int) * MAX_DIMENSION_NUM);
            for (unsigned int i = 0; i < dimension; i++) {
                dimension_list[dimension - 1 - i] = STACK_GET_INT_OFFSET(-(i + 1));
            }
            VM_CUR_CO_STACK_TOP_INDEX -= dimension;
            array_value = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_CLOSURE, nullptr);
            STACK_SET_ARRAY_OFFSET(0, array_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 2;
            break;

        case RVM_CODE_NEW_ARRAY_LITERAL_BOOL:
            array_size  = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            array_value = rvm_new_array_literal_bool(rvm, array_size);
            VM_CUR_CO_STACK_TOP_INDEX -= array_size;
            STACK_SET_ARRAY_OFFSET(0, array_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_NEW_ARRAY_LITERAL_INT:
            array_size  = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            array_value = rvm_new_array_literal_int(rvm, array_size);
            VM_CUR_CO_STACK_TOP_INDEX -= array_size;
            STACK_SET_ARRAY_OFFSET(0, array_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_NEW_ARRAY_LITERAL_INT64:
            array_size  = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            array_value = rvm_new_array_literal_int64(rvm, array_size);
            VM_CUR_CO_STACK_TOP_INDEX -= array_size;
            STACK_SET_ARRAY_OFFSET(0, array_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_NEW_ARRAY_LITERAL_DOUBLE:
            array_size  = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            array_value = rvm_new_array_literal_double(rvm, array_size);
            VM_CUR_CO_STACK_TOP_INDEX -= array_size;
            STACK_SET_ARRAY_OFFSET(0, array_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_NEW_ARRAY_LITERAL_STRING:
            array_size  = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            array_value = rvm_new_array_literal_string(rvm, array_size);
            VM_CUR_CO_STACK_TOP_INDEX -= array_size;
            STACK_SET_ARRAY_OFFSET(0, array_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_NEW_ARRAY_LITERAL_CLASS_OB:
            class_index          = OPCODE_GET_1BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            rvm_class_definition = &(rvm->class_list[class_index]);
            array_size           = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 2]);
            array_value          = rvm_new_array_literal_class_object(rvm, array_size, rvm_class_definition);
            VM_CUR_CO_STACK_TOP_INDEX -= array_size;
            STACK_SET_ARRAY_OFFSET(0, array_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 4;
            break;
        case RVM_CODE_NEW_ARRAY_LITERAL_CLOSURE:
            array_size  = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            array_value = rvm_new_array_literal_closure(rvm, array_size);
            VM_CUR_CO_STACK_TOP_INDEX -= array_size;
            STACK_SET_ARRAY_OFFSET(0, array_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_NEW_ARRAY_LITERAL_A:
            dimension   = OPCODE_GET_1BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            array_size  = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 2]);
            array_value = rvm_new_array_literal_a(rvm, dimension, array_size);
            VM_CUR_CO_STACK_TOP_INDEX -= array_size;
            STACK_SET_ARRAY_OFFSET(0, array_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 4;
            break;


        // range array/string
        case RVM_CODE_FOR_RANGE_ARRAY_A:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            if (array_index >= array_value->length) {
                VM_CUR_CO_PC = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
                break;
            }
            rvm_array_get_array(rvm, array_value, array_index, &array_value);
            // VM_CUR_CO_STACK_TOP_INDEX -= 2; // 与 RVM_CODE_PUSH_ARRAY_A 的不同点 区别
            STACK_SET_ARRAY_OFFSET(0, array_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;

            // increase iter of range
            STACK_GET_INT_OFFSET(-2) += 1;
            break;
        case RVM_CODE_FOR_RANGE_ARRAY_BOOL:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            if (array_index >= array_value->length) {
                VM_CUR_CO_PC = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
                break;
            }
            rvm_array_get_bool(rvm, array_value, array_index, &bool_value);
            // VM_CUR_CO_STACK_TOP_INDEX -= 2; // 与 RVM_CODE_PUSH_ARRAY_BOOL 的不同点 区别
            STACK_SET_BOOL_OFFSET(0, (RVM_Bool)((int)bool_value));
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;

            // increase iter of range
            STACK_GET_INT_OFFSET(-2) += 1;
            break;
        case RVM_CODE_FOR_RANGE_ARRAY_INT:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            if (array_index >= array_value->length) {
                VM_CUR_CO_PC = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
                break;
            }
            rvm_array_get_int(rvm, array_value, array_index, &int_value);
            // VM_CUR_CO_STACK_TOP_INDEX -= 2; // 与 RVM_CODE_PUSH_ARRAY_INT 的不同点 区别
            STACK_SET_INT_OFFSET(0, int_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;

            // increase iter of range
            STACK_GET_INT_OFFSET(-2) += 1;
            break;
        case RVM_CODE_FOR_RANGE_ARRAY_INT64:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            if (array_index >= array_value->length) {
                VM_CUR_CO_PC = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
                break;
            }
            rvm_array_get_int64(rvm, array_value, array_index, &int64_value);
            // VM_CUR_CO_STACK_TOP_INDEX -= 2; // 与 RVM_CODE_PUSH_ARRAY_INT 的不同点 区别
            STACK_SET_INT64_OFFSET(0, int64_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;

            // increase iter of range
            STACK_GET_INT_OFFSET(-2) += 1;
            break;
        case RVM_CODE_FOR_RANGE_ARRAY_DOUBLE:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            if (array_index >= array_value->length) {
                VM_CUR_CO_PC = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
                break;
            }
            rvm_array_get_double(rvm, array_value, array_index, &double_value);
            // VM_CUR_CO_STACK_TOP_INDEX -= 2; // 与 RVM_CODE_PUSH_ARRAY_DOUBLE 的不同点 区别
            STACK_SET_DOUBLE_OFFSET(0, double_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;

            // increase iter of range
            STACK_GET_INT_OFFSET(-2) += 1;
            break;
        case RVM_CODE_FOR_RANGE_ARRAY_STRING:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            if (array_index >= array_value->length) {
                VM_CUR_CO_PC = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
                break;
            }
            rvm_array_get_string(rvm, array_value, array_index, &string_value);
            // VM_CUR_CO_STACK_TOP_INDEX -= 2; // 与 RVM_CODE_PUSH_ARRAY_STRING 的不同点 区别
            STACK_SET_STRING_OFFSET(0, string_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;

            // increase iter of range
            STACK_GET_INT_OFFSET(-2) += 1;
            break;
        case RVM_CODE_FOR_RANGE_ARRAY_CLASS_OB:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            if (array_index >= array_value->length) {
                VM_CUR_CO_PC = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
                break;
            }
            rvm_array_get_class_object(rvm, array_value, array_index, &class_ob_value);
            // VM_CUR_CO_STACK_TOP_INDEX -= 2; // 与 RVM_CODE_PUSH_ARRAY_OBJECT 的不同点 区别
            STACK_SET_CLASS_OB_OFFSET(0, class_ob_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;

            // increase iter of range
            STACK_GET_INT_OFFSET(-2) += 1;
            break;
        case RVM_CODE_FOR_RANGE_ARRAY_CLOSURE:
            array_value = STACK_GET_ARRAY_OFFSET(-2);
            array_index = STACK_GET_INT_OFFSET(-1);
            assert_throw_nil_array(array_value == nullptr);
            if (array_index >= array_value->length) {
                VM_CUR_CO_PC = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
                break;
            }
            rvm_array_get_closure(rvm, array_value, array_index, &closure_value);
            // VM_CUR_CO_STACK_TOP_INDEX -= 2; // 与 RVM_CODE_PUSH_ARRAY_CLOSURE 的不同点 区别
            STACK_SET_CLOSURE_OFFSET(0, closure_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;

            // increase iter of range
            STACK_GET_INT_OFFSET(-2) += 1;
            break;
        case RVM_CODE_FOR_RANGE_STRING:
            break;
        case RVM_CODE_FOR_RANGE_FINISH:
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            VM_CUR_CO_PC += 3;
            break;


        // class
        case RVM_CODE_NEW_CLASS_OB_LITERAL:
            class_index          = OPCODE_GET_1BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            rvm_class_definition = &(rvm->class_list[class_index]);

            class_ob_value       = rvm_gc_new_class_ob_meta(rvm);
            rvm_fill_class_ob(rvm, class_ob_value, rvm_class_definition);
            STACK_SET_CLASS_OB_OFFSET(0, class_ob_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 2;
            break;

        case RVM_CODE_POP_FIELD_BOOL:
            class_ob_value                                       = STACK_GET_CLASS_OB_OFFSET(-1);
            field_index                                          = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            class_ob_value->field_list[field_index].type         = RVM_VALUE_TYPE_BOOL;
            class_ob_value->field_list[field_index].u.bool_value = STACK_GET_BOOL_OFFSET(-2);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_FIELD_INT:
            class_ob_value                                      = STACK_GET_CLASS_OB_OFFSET(-1);
            field_index                                         = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            class_ob_value->field_list[field_index].type        = RVM_VALUE_TYPE_INT;
            class_ob_value->field_list[field_index].u.int_value = STACK_GET_INT_OFFSET(-2);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_FIELD_INT64:
            class_ob_value                                        = STACK_GET_CLASS_OB_OFFSET(-1);
            field_index                                           = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            class_ob_value->field_list[field_index].type          = RVM_VALUE_TYPE_INT64;
            class_ob_value->field_list[field_index].u.int64_value = STACK_GET_INT64_OFFSET(-2);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_FIELD_DOUBLE:
            class_ob_value                                         = STACK_GET_CLASS_OB_OFFSET(-1);
            field_index                                            = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            class_ob_value->field_list[field_index].type           = RVM_VALUE_TYPE_DOUBLE;
            class_ob_value->field_list[field_index].u.double_value = STACK_GET_DOUBLE_OFFSET(-2);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_FIELD_STRING:
            class_ob_value                                         = STACK_GET_CLASS_OB_OFFSET(-1);
            field_index                                            = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            class_ob_value->field_list[field_index].type           = RVM_VALUE_TYPE_STRING;
            class_ob_value->field_list[field_index].u.string_value = STACK_GET_STRING_OFFSET(-2);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_FIELD_CLASS_OB:
            class_ob_value                                           = STACK_GET_CLASS_OB_OFFSET(-1);
            field_index                                              = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            class_ob_value->field_list[field_index].type             = RVM_VALUE_TYPE_CLASS_OB;
            class_ob_value->field_list[field_index].u.class_ob_value = STACK_GET_CLASS_OB_OFFSET(-2);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_FIELD_ARRAY:
            class_ob_value                                        = STACK_GET_CLASS_OB_OFFSET(-1);
            field_index                                           = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            class_ob_value->field_list[field_index].type          = RVM_VALUE_TYPE_ARRAY;
            class_ob_value->field_list[field_index].u.array_value = STACK_GET_ARRAY_OFFSET(-2);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_POP_FIELD_CLOSURE:
            class_ob_value                                          = STACK_GET_CLASS_OB_OFFSET(-1);
            field_index                                             = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            class_ob_value->field_list[field_index].type            = RVM_VALUE_TYPE_CLOSURE;
            class_ob_value->field_list[field_index].u.closure_value = STACK_GET_CLOSURE_OFFSET(-2);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;
            VM_CUR_CO_PC += 3;
            break;

        case RVM_CODE_PUSH_FIELD_BOOL:
            class_ob_value = STACK_GET_CLASS_OB_OFFSET(-1);
            field_index    = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            // TODO:
            // 在 Ring VM 崩溃的时候，应该抛出详细信息，方便编译器的开发者定位问题
            // 是通过宏控制，还是通过ring 执行时命令行控制
            // 通过 ring 执行时 注入环境变量比较优雅，
            // Usage: RVM_COLL_ERR=true ./bin/ring run ./test/000.ring
            // if (class_ob_value == nullptr) {
            //     std::string tmp = format_rvm_call_stack(rvm);
            //     printf("tmp:%s\n", tmp.c_str());
            //     ring_exec_err_report("Runtime Stack:\n%s\n", tmp.c_str());
            // }
            STACK_SET_BOOL_OFFSET(-1, class_ob_value->field_list[field_index].u.bool_value);
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_FIELD_INT:
            class_ob_value = STACK_GET_CLASS_OB_OFFSET(-1);
            field_index    = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_INT_OFFSET(-1, class_ob_value->field_list[field_index].u.int_value);
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_FIELD_INT64:
            class_ob_value = STACK_GET_CLASS_OB_OFFSET(-1);
            field_index    = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_INT64_OFFSET(-1, class_ob_value->field_list[field_index].u.int64_value);
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_FIELD_DOUBLE:
            class_ob_value = STACK_GET_CLASS_OB_OFFSET(-1);
            field_index    = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_DOUBLE_OFFSET(-1, class_ob_value->field_list[field_index].u.double_value);
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_FIELD_STRING:
            class_ob_value = STACK_GET_CLASS_OB_OFFSET(-1);
            field_index    = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_STRING_OFFSET(-1, class_ob_value->field_list[field_index].u.string_value);
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_FIELD_CLASS_OB:
            class_ob_value = STACK_GET_CLASS_OB_OFFSET(-1);
            field_index    = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_CLASS_OB_OFFSET(-1, class_ob_value->field_list[field_index].u.class_ob_value);
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_FIELD_ARRAY:
            class_ob_value = STACK_GET_CLASS_OB_OFFSET(-1);
            field_index    = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_ARRAY_OFFSET(-1, class_ob_value->field_list[field_index].u.array_value);
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_FIELD_CLOSURE:
            class_ob_value = STACK_GET_CLASS_OB_OFFSET(-1);
            field_index    = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_CLOSURE_OFFSET(-1, class_ob_value->field_list[field_index].u.closure_value);
            VM_CUR_CO_PC += 3;
            break;


        // arithmetic
        case RVM_CODE_ADD_INT:
            STACK_GET_INT_OFFSET(-2) = STACK_GET_INT_OFFSET(-2) + STACK_GET_INT_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_ADD_INT64:
            STACK_GET_INT64_OFFSET(-2) = STACK_GET_INT64_OFFSET(-2) + STACK_GET_INT64_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_ADD_DOUBLE:
            STACK_GET_DOUBLE_OFFSET(-2) = STACK_GET_DOUBLE_OFFSET(-2) + STACK_GET_DOUBLE_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;

        case RVM_CODE_SUB_INT:
            STACK_GET_INT_OFFSET(-2) = STACK_GET_INT_OFFSET(-2) - STACK_GET_INT_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_SUB_INT64:
            STACK_GET_INT64_OFFSET(-2) = STACK_GET_INT64_OFFSET(-2) - STACK_GET_INT64_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_SUB_DOUBLE:
            STACK_GET_DOUBLE_OFFSET(-2) = STACK_GET_DOUBLE_OFFSET(-2) - STACK_GET_DOUBLE_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;

        case RVM_CODE_MUL_INT:
            STACK_GET_INT_OFFSET(-2) = STACK_GET_INT_OFFSET(-2) * STACK_GET_INT_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_MUL_INT64:
            STACK_GET_INT64_OFFSET(-2) = STACK_GET_INT64_OFFSET(-2) * STACK_GET_INT64_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_MUL_DOUBLE:
            STACK_GET_DOUBLE_OFFSET(-2) = STACK_GET_DOUBLE_OFFSET(-2) * STACK_GET_DOUBLE_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;

        case RVM_CODE_DIV_INT:
            STACK_GET_INT_OFFSET(-2) = STACK_GET_INT_OFFSET(-2) / STACK_GET_INT_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_DIV_INT64:
            STACK_GET_INT64_OFFSET(-2) = STACK_GET_INT64_OFFSET(-2) / STACK_GET_INT64_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_DIV_DOUBLE:
            STACK_GET_DOUBLE_OFFSET(-2) = STACK_GET_DOUBLE_OFFSET(-2) / STACK_GET_DOUBLE_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;

        case RVM_CODE_MOD_INT:
            STACK_GET_INT_OFFSET(-2) = STACK_GET_INT_OFFSET(-2) % STACK_GET_INT_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_MOD_INT64:
            STACK_GET_INT64_OFFSET(-2) = STACK_GET_INT64_OFFSET(-2) % STACK_GET_INT64_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_MOD_DOUBLE:
            STACK_GET_DOUBLE_OFFSET(-2) = fmod(STACK_GET_DOUBLE_OFFSET(-2), STACK_GET_DOUBLE_OFFSET(-1));
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;

        case RVM_CODE_MINUS_INT:
            STACK_GET_INT_OFFSET(-1) = -STACK_GET_INT_OFFSET(-1);
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_MINUS_INT64:
            STACK_GET_INT64_OFFSET(-1) = -STACK_GET_INT64_OFFSET(-1);
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_MINUS_DOUBLE:
            STACK_GET_DOUBLE_OFFSET(-1) = -STACK_GET_DOUBLE_OFFSET(-1);
            VM_CUR_CO_PC += 1;
            break;

        case RVM_CODE_SELF_INCREASE_INT:
            STACK_GET_INT_OFFSET(-1) += 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_SELF_INCREASE_INT64:
            STACK_GET_INT64_OFFSET(-1) += 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_SELF_INCREASE_DOUBLE:
            STACK_GET_DOUBLE_OFFSET(-1) += 1.0;
            VM_CUR_CO_PC += 1;
            break;

        case RVM_CODE_SELF_DECREASE_INT:
            STACK_GET_INT_OFFSET(-1) -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_SELF_DECREASE_INT64:
            STACK_GET_INT64_OFFSET(-1) -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_SELF_DECREASE_DOUBLE:
            STACK_GET_DOUBLE_OFFSET(-1) -= 1.0;
            VM_CUR_CO_PC += 1;
            break;

        case RVM_CODE_CONCAT:
            string_value = concat_string(rvm, STACK_GET_STRING_OFFSET(-2), STACK_GET_STRING_OFFSET(-1));
            STACK_SET_STRING_OFFSET(-2, string_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_LEN:
            array_value = STACK_GET_ARRAY_OFFSET(-1);
            rvm_array_get_length(rvm, array_value, &int_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            STACK_SET_INT_OFFSET(0, int_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_CAPACITY:
            array_value = STACK_GET_ARRAY_OFFSET(-1);
            rvm_array_get_capacity(rvm, array_value, &int_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            STACK_SET_INT_OFFSET(0, int_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_PUSH_STRING_LEN:
            string_value = STACK_GET_STRING_OFFSET(-1);
            rvm_string_get_length(rvm, string_value, &int_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            STACK_SET_INT_OFFSET(0, int_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_PUSH_STRING_CAPACITY:
            string_value = STACK_GET_STRING_OFFSET(-1);
            rvm_string_get_capacity(rvm, string_value, &int_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            STACK_SET_INT_OFFSET(0, int_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 1;
            break;

        // type cast
        case RVM_CODE_CAST_BOOL_TO_INT:
            STACK_SET_INT_OFFSET(-1, STACK_GET_BOOL_OFFSET(-1));
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_CAST_INT_TO_DOUBLE:
            STACK_SET_DOUBLE_OFFSET(-1, STACK_GET_INT_OFFSET(-1));
            VM_CUR_CO_PC += 1;
            break;

        case RVM_CODE_CAST_INT_TO_BOOL:
            STACK_SET_BOOL_OFFSET(-1, (RVM_Bool)STACK_GET_INT_OFFSET(-1));
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_CAST_DOUBLE_TO_INT:
            STACK_SET_INT_OFFSET(-1, (int)STACK_GET_DOUBLE_OFFSET(-1));
            VM_CUR_CO_PC += 1;
            break;

            // convert
        case RVM_CODE_BOOL_2_STRING:
            bool_value   = STACK_GET_BOOL_OFFSET(-1);
            string_value = rvm_bool_2_string(rvm, bool_value);
            STACK_SET_STRING_OFFSET(-1, string_value);
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_INT_2_STRING:
            int_value    = STACK_GET_INT_OFFSET(-1);
            string_value = rvm_int_2_string(rvm, int_value);
            STACK_SET_STRING_OFFSET(-1, string_value);
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_INT64_2_STRING:
            int64_value  = STACK_GET_INT64_OFFSET(-1);
            string_value = rvm_int64_2_string(rvm, int64_value);
            STACK_SET_STRING_OFFSET(-1, string_value);
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_DOUBLE_2_STRING:
            double_value = STACK_GET_DOUBLE_OFFSET(-1);
            string_value = rvm_double_2_string(rvm, double_value);
            STACK_SET_STRING_OFFSET(-1, string_value);
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_INT_2_INT64:
            int_value = STACK_GET_INT_OFFSET(-1);
            STACK_SET_INT64_OFFSET(-1, int_value);
            VM_CUR_CO_PC += 1;
            break;

        // logical
        case RVM_CODE_LOGICAL_AND:
            bool_value = (STACK_GET_INT_OFFSET(-2) && STACK_GET_INT_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_LOGICAL_OR:
            bool_value = (STACK_GET_INT_OFFSET(-2) || STACK_GET_INT_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_LOGICAL_NOT:
            STACK_GET_INT_OFFSET(-1) = !(STACK_GET_INT_OFFSET(-1));
            VM_CUR_CO_PC += 1;
            break;


        // relational
        case RVM_CODE_RELATIONAL_EQ_INT:
            bool_value = (STACK_GET_INT_OFFSET(-2) == STACK_GET_INT_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_RELATIONAL_EQ_INT64:
            bool_value = (STACK_GET_INT64_OFFSET(-2) == STACK_GET_INT64_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_RELATIONAL_EQ_DOUBLE:
            bool_value = (STACK_GET_DOUBLE_OFFSET(-2) == STACK_GET_DOUBLE_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_RELATIONAL_EQ_STRING:
            bool_value = (rvm_string_cmp(STACK_GET_STRING_OFFSET(-2), STACK_GET_STRING_OFFSET(-1)) == 0);
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;

        case RVM_CODE_RELATIONAL_NE_INT:
            bool_value = (STACK_GET_INT_OFFSET(-2) != STACK_GET_INT_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_RELATIONAL_NE_INT64:
            bool_value = (STACK_GET_INT64_OFFSET(-2) != STACK_GET_INT64_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_RELATIONAL_NE_DOUBLE:
            bool_value = (STACK_GET_DOUBLE_OFFSET(-2) != STACK_GET_DOUBLE_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_RELATIONAL_NE_STRING:
            bool_value = (RVM_Bool)(rvm_string_cmp(STACK_GET_STRING_OFFSET(-2), STACK_GET_STRING_OFFSET(-1)) != 0);
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;

        case RVM_CODE_RELATIONAL_GT_INT:
            bool_value = (STACK_GET_INT_OFFSET(-2) > STACK_GET_INT_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_RELATIONAL_GT_INT64:
            bool_value = (STACK_GET_INT64_OFFSET(-2) > STACK_GET_INT64_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_RELATIONAL_GT_DOUBLE:
            bool_value = (STACK_GET_DOUBLE_OFFSET(-2) > STACK_GET_DOUBLE_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_RELATIONAL_GT_STRING:
            bool_value = (rvm_string_cmp(STACK_GET_STRING_OFFSET(-2), STACK_GET_STRING_OFFSET(-1)) > 0);
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;

        case RVM_CODE_RELATIONAL_GE_INT:
            bool_value = (STACK_GET_INT_OFFSET(-2) >= STACK_GET_INT_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_RELATIONAL_GE_INT64:
            bool_value = (STACK_GET_INT64_OFFSET(-2) >= STACK_GET_INT64_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_RELATIONAL_GE_DOUBLE:
            bool_value = (STACK_GET_DOUBLE_OFFSET(-2) >= STACK_GET_DOUBLE_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_RELATIONAL_GE_STRING:
            bool_value = (rvm_string_cmp(STACK_GET_STRING_OFFSET(-2), STACK_GET_STRING_OFFSET(-1)) >= 0);
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;

        case RVM_CODE_RELATIONAL_LT_INT:
            bool_value = (STACK_GET_INT_OFFSET(-2) < STACK_GET_INT_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_RELATIONAL_LT_INT64:
            bool_value = (STACK_GET_INT64_OFFSET(-2) < STACK_GET_INT64_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_RELATIONAL_LT_DOUBLE:
            bool_value = (STACK_GET_DOUBLE_OFFSET(-2) < STACK_GET_DOUBLE_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_RELATIONAL_LT_STRING:
            bool_value = (rvm_string_cmp(STACK_GET_STRING_OFFSET(-2), STACK_GET_STRING_OFFSET(-1)) < 0);
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;

        case RVM_CODE_RELATIONAL_LE_INT:
            bool_value = (STACK_GET_INT_OFFSET(-2) <= STACK_GET_INT_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_RELATIONAL_LE_INT64:
            bool_value = (STACK_GET_INT64_OFFSET(-2) <= STACK_GET_INT64_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_RELATIONAL_LE_DOUBLE:
            bool_value = (STACK_GET_DOUBLE_OFFSET(-2) <= STACK_GET_DOUBLE_OFFSET(-1));
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_RELATIONAL_LE_STRING:
            bool_value = (rvm_string_cmp(STACK_GET_STRING_OFFSET(-2), STACK_GET_STRING_OFFSET(-1)) <= 0);
            STACK_SET_BOOL_OFFSET(-2, (RVM_Bool)bool_value);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            VM_CUR_CO_PC += 1;
            break;


        // jump
        case RVM_CODE_JUMP:
            VM_CUR_CO_PC = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            break;
        case RVM_CODE_JUMP_IF_FALSE:
            if (!STACK_GET_INT_OFFSET(-1)) {
                VM_CUR_CO_PC = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            } else {
                VM_CUR_CO_PC += 3;
            }
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            break;
        case RVM_CODE_JUMP_IF_TRUE:
            if (STACK_GET_INT_OFFSET(-1)) {
                VM_CUR_CO_PC = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            } else {
                VM_CUR_CO_PC += 3;
            }
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            break;


        // duplicate
        case RVM_CODE_SHALLOW_COPY:
            dst_offset = OPCODE_GET_1BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            src_offset = OPCODE_GET_1BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 2]);
            STACK_COPY_OFFSET(-dst_offset, -src_offset);
            if (dst_offset == 0)
                VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_DEEP_COPY:
            // TODO: 这里有个不足
            // 就是 deep_copy 没有区分数据的类型,
            // 所以说需要进入函数内部进行选择处理 deep_copy, 后续需要进行优化
            dst_offset = OPCODE_GET_1BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            src_offset = OPCODE_GET_1BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 2]);

            if (STACK_GET_TYPE_OFFSET(-src_offset) == RVM_VALUE_TYPE_CLASS_OB) {
                RVM_ClassObject* src_class_object = STACK_GET_CLASS_OB_OFFSET(-src_offset);
                RVM_ClassObject* dst_class_object = nullptr;
                dst_class_object                  = rvm_deep_copy_class_ob(rvm, src_class_object);
                STACK_SET_CLASS_OB_OFFSET(-dst_offset, dst_class_object);
            } else if (STACK_GET_TYPE_OFFSET(-src_offset) == RVM_VALUE_TYPE_ARRAY) {
                RVM_Array* src_array = STACK_GET_ARRAY_OFFSET(-src_offset);
                RVM_Array* dst_array = nullptr;
                dst_array            = rvm_deep_copy_array(rvm, src_array);
                STACK_SET_ARRAY_OFFSET(-dst_offset, dst_array);
            }

            if (dst_offset == 0)
                VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;


        // func
        case RVM_CODE_ARGUMENT_NUM:
            argument_list_size = OPCODE_GET_1BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_INT_OFFSET(0, argument_list_size);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 2;
            break;
        case RVM_CODE_PUSH_FUNC:
            // 这里设计的不太好
            func_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_INT_OFFSET(0, func_index);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_PUSH_METHOD:
            method_index = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            STACK_SET_INT_OFFSET(0, method_index);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;
        case RVM_CODE_INVOKE_FUNC_NATIVE:
            argument_list_size = STACK_GET_INT_OFFSET(-2);
            oper_num           = STACK_GET_INT_OFFSET(-1);
            package_index      = oper_num >> 8;
            func_index         = oper_num & 0XFF;
            VM_CUR_CO_STACK_TOP_INDEX -= 2;

            callee_function = &(rvm->executer_entry->package_executer_list[package_index]->function_list[func_index]);
            assert(callee_function->type == RVM_FUNCTION_TYPE_NATIVE);

            invoke_native_function(rvm,
                                   callee_function,
                                   argument_list_size);
            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_INVOKE_FUNC:
            argument_list_size = STACK_GET_INT_OFFSET(-2);
            oper_num           = STACK_GET_INT_OFFSET(-1);
            package_index      = oper_num >> 8;
            func_index         = oper_num & 0XFF;
            VM_CUR_CO_STACK_TOP_INDEX -= 2;

            callee_function = &(rvm->executer_entry->package_executer_list[package_index]->function_list[func_index]);
            assert(callee_function->type == RVM_FUNCTION_TYPE_DERIVE);

            invoke_derive_function(rvm,
                                   &caller_class_ob, &caller_function, &caller_closure,
                                   nullptr, callee_function, nullptr,
                                   argument_list_size,
                                   false);

            break;
        case RVM_CODE_INVOKE_CLOSURE:
            argument_list_size = STACK_GET_INT_OFFSET(-2);
            closure_value      = STACK_GET_CLOSURE_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;

            assert_throw_nil_closure(closure_value == nullptr);

            invoke_derive_function(rvm,
                                   &caller_class_ob, &caller_function, &caller_closure,
                                   nullptr, closure_value->anonymous_func, closure_value,
                                   argument_list_size,
                                   false);

            break;
        case RVM_CODE_INVOKE_METHOD:

            argument_list_size = STACK_GET_INT_OFFSET(-3);
            callee_class_ob    = STACK_GET_CLASS_OB_OFFSET(-2);
            method_index       = STACK_GET_INT_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 3;

            // 每个对象的成员变量 是单独存储的
            // 但是 method 没必要单独存储, 在 class_definition 中就可以, 通过指针寻找 class_definition
            // 需要将 class_object 赋值给 self 变量
            // TODO: 但是这里, gc会释放么, 让 invoke_derive_function变得不合法
            callee_method   = &(callee_class_ob->class_ref->method_list[method_index]);
            callee_function = callee_method->rvm_function;

            invoke_derive_function(rvm,
                                   &caller_class_ob, &caller_function, &caller_closure,
                                   callee_class_ob, callee_function, nullptr,
                                   argument_list_size,
                                   false);
            break;
        case RVM_CODE_RETURN:
            return_value_list_size = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            VM_CUR_CO_PC += 3;
            [[fallthrough]]; // make g++ happy
        case RVM_CODE_FUNCTION_FINISH:
            derive_function_finish(rvm,
                                   &caller_class_ob, &caller_function, &caller_closure,
                                   nullptr,
                                   return_value_list_size);
            return_value_list_size = 0;
            break;
        case RVM_CODE_EXIT:
            oper_num  = STACK_GET_INT_OFFSET(-1);
            exit_code = oper_num;
            goto EXIT;
            break;

        // closure
        case RVM_CODE_NEW_CLOSURE:
            const_index    = OPCODE_GET_2BYTE(&VM_CUR_CO_CODE_LIST[VM_CUR_CO_PC + 1]);
            anonymous_func = constant_pool_list[const_index].u.anonymous_func_value;
            closure_value  = new_closure(rvm, caller_function, caller_closure, anonymous_func);
            STACK_SET_CLOSURE_OFFSET(0, closure_value);
            VM_CUR_CO_STACK_TOP_INDEX += 1;
            VM_CUR_CO_PC += 3;
            break;

        // defer
        case RVM_CODE_PUSH_DEFER:
            argument_list_size = STACK_GET_INT_OFFSET(-2);
            closure_value      = STACK_GET_CLOSURE_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;

            defer_item = new_defer_item(rvm, closure_value, argument_list_size);
            coroutine_push_defer_item(rvm, defer_item);

            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_POP_DEFER:
            if (VM_CUR_CO->defer_list_size != 0) {

                RVM_DeferItem* defer_item = coroutine_pop_defer_item(rvm);
                fill_defer_item_argument_stack(rvm, defer_item);

                if (defer_item != nullptr) {
                    // RVM_Value*   argument_list      = defer_item->argument_list;
                    unsigned int argument_list_size = defer_item->argument_size;
                    RVM_Closure* closure_value      = defer_item->closure;

                    // 这里直接调用会有个问题
                    // closure return的时候找不到返回地址
                    // 没有办法继续执行,
                    // 因为不是在 虚拟机中的的 switch中调用的 invoke_derive_function
                    invoke_derive_function(rvm,
                                           &caller_class_ob, &caller_function, &caller_closure,
                                           nullptr, closure_value->anonymous_func, closure_value,
                                           argument_list_size,
                                           true);
                }
            } else {
                VM_CUR_CO_PC += 1;
            }
            break;


        // coroutine
        case RVM_CODE_LAUNCH:
            argument_list_size = STACK_GET_INT_OFFSET(-2);
            oper_num           = STACK_GET_INT_OFFSET(-1);
            package_index      = oper_num >> 8;
            func_index         = oper_num & 0XFF;
            VM_CUR_CO_STACK_TOP_INDEX -= 2;

            callee_function = &(rvm->executer_entry->package_executer_list[package_index]->function_list[func_index]);
            assert(callee_function->type == RVM_FUNCTION_TYPE_DERIVE);

            new_coroutine = launch_coroutine(rvm,
                                             &caller_class_ob, &caller_function, &caller_closure,
                                             nullptr, callee_function, nullptr,
                                             argument_list_size);
            // destory arguments after copy it to new coroutine
            VM_CUR_CO_STACK_TOP_INDEX -= argument_list_size;

            STACK_SET_INT64_OFFSET(0, new_coroutine->co_id);
            VM_CUR_CO_STACK_TOP_INDEX += 1;

            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_LAUNCH_CLOSURE:
            argument_list_size = STACK_GET_INT_OFFSET(-2);
            closure_value      = STACK_GET_CLOSURE_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 2;

            assert_throw_nil_closure(closure_value == nullptr);

            new_coroutine = launch_coroutine(rvm,
                                             &caller_class_ob, &caller_function, &caller_closure,
                                             nullptr, closure_value->anonymous_func, closure_value,
                                             argument_list_size);
            // destory arguments after copy it to new coroutine
            VM_CUR_CO_STACK_TOP_INDEX -= argument_list_size;

            STACK_SET_INT64_OFFSET(0, new_coroutine->co_id);
            VM_CUR_CO_STACK_TOP_INDEX += 1;

            VM_CUR_CO_PC += 1;
            break;
        case RVM_CODE_LAUNCH_METHOD:
            argument_list_size = STACK_GET_INT_OFFSET(-3);
            callee_class_ob    = STACK_GET_CLASS_OB_OFFSET(-2);
            method_index       = STACK_GET_INT_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 3;


            // 每个对象的成员变量 是单独存储的
            // 但是 method 没必要单独存储, 在 class_definition 中就可以, 通过指针寻找 class_definition
            // 需要将 class_object 赋值给 self 变量
            // TODO: 但是这里, gc会释放么, 让 invoke_derive_function变得不合法
            callee_method   = &(callee_class_ob->class_ref->method_list[method_index]);
            callee_function = callee_method->rvm_function;
            assert(callee_function->type == RVM_FUNCTION_TYPE_DERIVE);

            new_coroutine = launch_coroutine(rvm,
                                             &caller_class_ob, &caller_function, &caller_closure,
                                             callee_class_ob, callee_function, nullptr,
                                             argument_list_size);
            // destory arguments after copy it to new coroutine
            VM_CUR_CO_STACK_TOP_INDEX -= argument_list_size;

            STACK_SET_INT64_OFFSET(0, new_coroutine->co_id);
            VM_CUR_CO_STACK_TOP_INDEX += 1;

            VM_CUR_CO_PC += 1;
            break;

        case RVM_CODE_RESUME:
            co_id = STACK_GET_INT64_OFFSET(-1);
            VM_CUR_CO_STACK_TOP_INDEX -= 1;
            res = resume_coroutine(rvm,
                                   co_id,
                                   &caller_class_ob, &caller_function,
                                   nullptr, nullptr);
            if (res != 0) {
                VM_CUR_CO_PC += 1;
            }
            break;
        case RVM_CODE_YIELD:
            // yield
            res = yield_coroutine(rvm);
            if (res != 0) {
                VM_CUR_CO_PC += 1;
            }
            break;


        default:
            throw_invalid_opcode(opcode, VM_CUR_CO_PC);
            break;
        }
    }


EXIT:

    destory_mem_pool(rvm->meta_pool);
    // destory_mem_pool(rvm->data_pool);

    return exit_code;
}


void invoke_native_function(Ring_VirtualMachine* rvm,
                            RVM_Function*        function,
                            unsigned int         argument_list_size) {

    RVM_Value           ret;

    int                 return_list_count = function->u.native_func->return_list_count;
    RVM_NativeFuncProc* native_func_proc  = function->u.native_func->func_proc;
    RVM_Value*          args              = nullptr;

    //
    args = &VM_CUR_CO_STACK_DATA[VM_CUR_CO_STACK_TOP_INDEX - argument_list_size];

    ret  = native_func_proc(rvm, argument_list_size, args);


    // 销毁 argument
    VM_CUR_CO_STACK_TOP_INDEX -= argument_list_size;

    // TODO: 需要补齐一个 return 指令
    //       如何在这里处理 return 多返回值的问题
    if (return_list_count == 0) {
    } else if (return_list_count == 1) {
        VM_CUR_CO_STACK_DATA[VM_CUR_CO_STACK_TOP_INDEX++] = ret;
    } else {
        ring_error_report("native function return value count > 1");
    }
}

/*
 * invoke_derive_function
 *
 * 1. store call info
 *      call info: - caller_function
 *                 - caller_pc
 *                 - callee_stack_base
 * 2. expan runtime stack
 * 3. change
 *          caller_function
 *          vm code_list
 *          vm code_size
 *          pc
 *          caller_stack_base
 * 3. change vm code to callee
 * 4. change pc
 *
 * callee_object 是 callee_function的 所属对象
 *
 * callee_object == nullptr:
 *      -> 是 function调用
 * callee_object != nullptr:
 *      -> 是method调用
 *
 *
 * invoke_by_defer 是否有defer发起的
 */
void invoke_derive_function(Ring_VirtualMachine* rvm,
                            RVM_ClassObject** caller_object, RVM_Function** caller_function, RVM_Closure** caller_closure,
                            RVM_ClassObject* callee_object, RVM_Function* callee_function, RVM_Closure* callee_closure,
                            unsigned int argument_list_size,
                            bool         invoke_by_defer) {

    RVM_CallInfo* callinfo         = (RVM_CallInfo*)mem_alloc(rvm->meta_pool, sizeof(RVM_CallInfo));
    callinfo->caller_object        = *caller_object;
    callinfo->caller_function      = *caller_function;
    callinfo->caller_closure       = *caller_closure;
    callinfo->caller_stack_base    = VM_CUR_CO_STACK_TOP_INDEX;
    callinfo->caller_is_defer      = invoke_by_defer;
    callinfo->callee_object        = callee_object;
    callinfo->callee_function      = callee_function;
    callinfo->callee_closure       = callee_closure;
    callinfo->callee_argument_size = argument_list_size;
    callinfo->curr_closure         = callee_closure;
    callinfo->code_list            = callee_function->u.derive_func->code_list;
    callinfo->code_size            = callee_function->u.derive_func->code_size;
    callinfo->pc                   = 0;
    callinfo->prev                 = nullptr;
    callinfo->next                 = nullptr;


    if (RING_DEBUG_TRACE_FUNC_BACKTRACE) {
        std::string prefix     = "[RING_DEBUG::trace_func_backtrace] [invoke_func::]";
        std::string callinfo_s = sprintf_string("CallInfo{\n"
                                                "\tcaller_object:%p,\n"
                                                "\tcaller_function:%s,\n"
                                                "\tcaller_closure:%p,\n"
                                                "\tcaller_stack_base:%u,\n"
                                                "\tcallee_object:%p,\n"
                                                "\tcallee_function:%s,\n"
                                                "\tcallee_closure:%p,\n"
                                                "\tcallee_argument_size:%u\n"
                                                "}\n",
                                                callinfo->caller_object, callinfo->caller_function != nullptr ? callinfo->caller_function->identifier : "", callinfo->caller_closure, callinfo->caller_stack_base, callinfo->callee_object, callinfo->callee_function != nullptr ? callinfo->callee_function->identifier : "", callinfo->callee_closure, callinfo->callee_argument_size);

        printf_witch_red("%s %s", prefix.c_str(), callinfo_s.c_str());
    }

    // 函数上下文切换
    VM_CUR_CO_CALLINFO = store_callinfo(VM_CUR_CO_CALLINFO, callinfo);


    init_derive_function_local_variable(rvm, callee_object, callee_function, argument_list_size);


    if (callee_closure == nullptr && callee_function->free_value_size) {
        // 初始化一个闭包

        RVM_Closure* closure     = rvm_gc_new_closure_meta(rvm);
        closure->anonymous_func  = callee_function;
        closure->free_value_size = callee_function->free_value_size;
        closure->free_value_list = (RVM_FreeValue*)mem_alloc(rvm->data_pool,
                                                             closure->free_value_size * sizeof(RVM_FreeValue));

        // printf("[Debug][New Closure]init free-value function(%p) closure(%p), free_value_size:%u\n",
        //        callee_function, closure,
        //        callee_function->free_value_size);

        for (unsigned int i = 0; i < callee_function->free_value_size; i++) {

            if (callee_function->free_value_list[i].is_curr_local) {
                unsigned int index                   = callee_function->free_value_list[i].u.curr_local_index;

                closure->free_value_list[i].is_recur = false;
                closure->free_value_list[i].u.p      = &(VM_CUR_CO_STACK_DATA[VM_CUR_CO_CSB + index]);
                closure->free_value_list[i].is_open  = true;
                closure->free_value_list[i].c_value  = RVM_Value{};

            } else {
                // 其实走不到这个逻辑
                assert(caller_closure != nullptr);
                unsigned int index = callee_function->free_value_list[i].u.out_free_value_index;

                // 通过调用链向上递归查找, 知道找到直接指向的agent
                RVM_FreeValue* parent = &((*caller_closure)->free_value_list[index]);
                while (parent->is_recur) {
                    parent = parent->u.recur;
                }
                closure->free_value_list[i].is_recur = true;
                closure->free_value_list[i].u.recur  = parent;
            }
        }

        callee_closure = closure;

        if (RING_DEBUG_TRACE_CLOSURE_FREE_VALUE) {
#ifdef DEBUG_TRACE_CLOSURE_FREE_VALUE
            debug_generate_closure_dot_file(closure);
#endif
        }
    }

    // FIXME: 需要优化这种写法
    // 需要重新绑定值
    if (callee_closure != nullptr) {

        for (unsigned int i = 0; i < callee_function->free_value_size; i++) {
            // 需要重新绑定值
            if (callee_function->free_value_list[i].is_curr_local) {
                unsigned int index                          = callee_function->free_value_list[i].u.curr_local_index;

                callee_closure->free_value_list[i].is_recur = false;
                callee_closure->free_value_list[i].u.p      = &(VM_CUR_CO_STACK_DATA[VM_CUR_CO_CSB + index]);
                callee_closure->free_value_list[i].is_open  = true;
                callee_closure->free_value_list[i].c_value  = RVM_Value{};
            }
        }
    }

    callinfo->callee_closure = callee_closure;

    // 更新外层
    *caller_object   = callee_object;
    *caller_function = callee_function;
    *caller_closure  = callee_closure;

    // 注意，在函数调用还未完成时，argument 其实是没有被释放的
    // 这里延后释放，代码逻辑简化了，但是栈空间有浪费
}

void derive_function_return(Ring_VirtualMachine* rvm,
                            RVM_Function** caller_function, RVM_Function* callee_function,
                            unsigned int return_list_size) {
    debug_exec_info_with_white("\t");
}

/*
 * derive_function_finish
 *
 * 1. restore call info
 *      call info: caller_pc
 * 3. change vm code to callee
 * 4. change pc
 * 5. close all free-value
 *
 * */
void derive_function_finish(Ring_VirtualMachine* rvm,
                            RVM_ClassObject** caller_object, RVM_Function** caller_function, RVM_Closure** caller_closure,
                            RVM_Function* callee_function,
                            unsigned int  return_value_list_size) {

    // FIXME:
    // 不应该直接操作 VM_CUR_CO_STACK_TOP_INDEX
    // 应该根据 VM_CUR_CO_STACK_TOP_INDEX 来进行操作

    unsigned int old_return_value_list_index;

    old_return_value_list_index = VM_CUR_CO_STACK_TOP_INDEX - return_value_list_size;


    RVM_CallInfo* callinfo      = nullptr;
    callinfo                    = restore_callinfo(&VM_CUR_CO_CALLINFO);

    if (RING_DEBUG_TRACE_FUNC_BACKTRACE) {
        std::string prefix     = "[RING_DEBUG::trace_func_backtrace] [finish_func::]";
        std::string callinfo_s = sprintf_string("CallInfo{\n"
                                                "\tcaller_object:%p,\n"
                                                "\tcaller_function:%s,\n"
                                                "\tcaller_closure:%p,\n"
                                                "\tcaller_stack_base:%u,\n"
                                                "\tcallee_object:%p,\n"
                                                "\tcallee_function:%s,\n"
                                                "\tcallee_closure:%p,\n"
                                                "\tcallee_argument_size:%u\n"
                                                "}\n",
                                                callinfo->caller_object, callinfo->caller_function != nullptr ? callinfo->caller_function->identifier : "", callinfo->caller_closure, callinfo->caller_stack_base, callinfo->callee_object, callinfo->callee_function != nullptr ? callinfo->callee_function->identifier : "", callinfo->callee_closure, callinfo->callee_argument_size);

        printf_witch_red("%s %s", prefix.c_str(), callinfo_s.c_str());
    }

    unsigned int local_variable_size = callinfo->callee_function->local_variable_size;

    // 销毁 return_value_list local_variable
    VM_CUR_CO_STACK_TOP_INDEX -= return_value_list_size;
    VM_CUR_CO_STACK_TOP_INDEX -= local_variable_size;


    *caller_object   = callinfo->caller_object;
    *caller_function = callinfo->caller_function;
    *caller_closure  = callinfo->caller_closure;

    //
    // 关闭 free value
    RVM_Closure* closure = callinfo->callee_closure;
    if (closure != nullptr) {


        for (unsigned int i = 0; i < closure->free_value_size; i++) {
            if (!closure->free_value_list[i].is_recur
                && closure->free_value_list[i].is_open) {
                // TODO: deep_copy string/array/class-object
                closure->free_value_list[i].c_value = *(closure->free_value_list[i].u.p);
                closure->free_value_list[i].u.p     = &(closure->free_value_list[i].c_value);
                closure->free_value_list[i].is_open = false;
            }
        }

        if (RING_DEBUG_TRACE_CLOSURE_FREE_VALUE) {
#ifdef DEBUG_TRACE_CLOSURE_FREE_VALUE
            debug_generate_closure_dot_file(closure);
#endif
        }
    }


    //
    // 如果 callinfo 为空, 则一个协程消亡了
    // 需要切换/销毁 协程
    if (VM_CUR_CO_CALLINFO == nullptr) {
        // TODO: 一个协程结束之后，协程的返回值是否要copy到调用者的协程栈中
        finish_coroutine(rvm,
                         caller_object, caller_function,
                         callee_function);
        return;
    }

    if (!callinfo->caller_is_defer) {
        // 调用完成之后，上层的函数 pc + 1
        VM_CUR_CO_PC += 1;
    } else {
        // 如果上层是defer，那么他的pc不会+1，需要继续执行 pop_defer指令
    }


    // TODO: 为了安全性，需要进行检查
    // assert(VM_CUR_CO_STACK_TOP_INDEX == callinfo->caller_stack_base);

    // 释放arguement
    VM_CUR_CO_STACK_TOP_INDEX -= callinfo->callee_argument_size;


    // copy return value to top of stack.
    for (unsigned int i = 0; i < return_value_list_size; i++) {
        VM_CUR_CO_STACK_DATA[VM_CUR_CO_STACK_TOP_INDEX++] =
            VM_CUR_CO_STACK_DATA[old_return_value_list_index + i];
    }
}

/*
 * storage callinfo when invoke function
 *
 * 1. Encode callinfo
 * 2. Push to runtime_stack
 * @Return new head of callinfo-list
 *
 */
RVM_CallInfo* store_callinfo(RVM_CallInfo* head, RVM_CallInfo* call_info) {

    if (call_info == nullptr) {
        return head;
    }

    if (head == nullptr) {
        return call_info;
    }

    call_info->next = head;
    head->prev      = call_info;

    return call_info;
}

/*
 * restore callinfo when function finish
 *
 * 1. Pop from runtime_stack
 * 2. Decode callinfo
 * @Return the head of callinfo-list
 *
 */
RVM_CallInfo* restore_callinfo(RVM_CallInfo** head_) {

    assert(*head_ != nullptr);

    RVM_CallInfo* head = *head_;

    RVM_CallInfo* next = head->next;
    if (next != nullptr) {
        next->prev = nullptr;
    }
    *head_     = next;

    head->next = nullptr;
    head->prev = nullptr;
    return head;
}

/*
 * init_derive_function_local_variable 对函数中的局部变量进行初始化, 并放入runtime_stack中]
 * 会造成栈空间的增长
 *
 * 1. callee_class_object 是 callee_function的 所属对象
 *    用来区分是 method调用, 并 把 callee_class_object 初始化给 self 变量
 *
 * FIXME: 初始化局部变量列表的时候存在问题
 * FIXME: 如果局部变量是个数组
 */
void init_derive_function_local_variable(Ring_VirtualMachine* rvm,
                                         RVM_ClassObject*     callee_object,
                                         RVM_Function*        callee_function,
                                         unsigned int         argument_list_size) {

    RVM_TypeSpecifier*   type_specifier          = nullptr;
    RVM_ClassDefinition* rvm_class_definition    = nullptr;
    RVM_ClassObject*     class_ob                = nullptr;
    RVM_String*          string                  = nullptr;
    RVM_Array*           array                   = nullptr;

    unsigned int         argument_stack_index    = 0; // argument's abs-index in runtime_stack.
    unsigned int         local_vari_stack_offset = 0; // callee_function's local variable offset in runtime_stack.


    // Step-0: relocate argument's abs-index in runtime_stack.
    argument_stack_index = VM_CUR_CO_STACK_TOP_INDEX - argument_list_size;


    // Step-1: init `self` variable when callee_function is method.
    if (callee_object != nullptr) {
        STACK_SET_CLASS_OB_INDEX(VM_CUR_CO_STACK_TOP_INDEX + local_vari_stack_offset, callee_object);
        local_vari_stack_offset++;
    }

    // Step-2: init parameters by parameters.
    // if a parameter is variadic, convert arguments to array.
    // access arguments by array.
    unsigned int argument_stack_offset = 0;
    for (unsigned int i = 0;
         i < callee_function->parameter_size && argument_stack_offset < argument_list_size;
         i++, argument_stack_offset++) {

        RVM_Parameter* parameter = &callee_function->parameter_list[i];

        if (parameter->is_variadic) {
            /*
             * 1)
             * 可变参数只能是函数的最后一个参数, 直接一次性全部获取完成
             * 2)
             * 如果 parameter 是：var bool... array
             *  则变更为 bool[]
             * 如果 parameter 是：var bool[]... array
             *  则变更为 bool[!2]
             * 也就是增加一个维度
             */
            RVM_Array*   array_value = nullptr;
            unsigned int size        = argument_list_size - argument_stack_offset;

            //
            array_value = init_derive_function_variadic_argument(rvm,
                                                                 parameter,
                                                                 size);

            // 将stack中的参数放入array中
            for (unsigned array_index = 0;
                 argument_stack_offset < argument_list_size;
                 array_index++, argument_stack_offset++) {

                assert_throw_range(array_index, array_value->length);

                switch (parameter->type_specifier->kind) {
                case RING_BASIC_TYPE_BOOL: {
                    RVM_Bool tmp        = STACK_GET_BOOL_INDEX(argument_stack_index + argument_stack_offset);
                    bool     bool_value = tmp;
                    rvm_array_set_bool(rvm, array_value, array_index, &bool_value);
                } break;
                case RING_BASIC_TYPE_INT: {
                    int int_value = STACK_GET_INT_INDEX(argument_stack_index + argument_stack_offset);
                    rvm_array_set_int(rvm, array_value, array_index, &int_value);
                } break;
                case RING_BASIC_TYPE_INT64: {
                    long long int64_value = STACK_GET_INT64_INDEX(argument_stack_index + argument_stack_offset);
                    rvm_array_set_int64(rvm, array_value, array_index, &int64_value);
                } break;
                case RING_BASIC_TYPE_DOUBLE: {
                    double double_value = STACK_GET_DOUBLE_INDEX(argument_stack_index + argument_stack_offset);
                    rvm_array_set_double(rvm, array_value, array_index, &double_value);
                } break;
                case RING_BASIC_TYPE_STRING: {
                    RVM_String* string_value = STACK_GET_STRING_INDEX(argument_stack_index + argument_stack_offset);
                    rvm_array_set_string(rvm, array_value, array_index, &string_value);
                } break;
                case RING_BASIC_TYPE_CLASS: {
                    RVM_ClassObject* class_ob = STACK_GET_CLASS_OB_INDEX(argument_stack_index + argument_stack_offset);
                    rvm_array_set_class_object(rvm, array_value, array_index, &class_ob);
                } break;
                case RING_BASIC_TYPE_ARRAY: {
                    RVM_Array* array_value_item = STACK_GET_ARRAY_INDEX(argument_stack_index + argument_stack_offset);
                    rvm_array_set_array(rvm, array_value, array_index, array_value_item);
                } break;
                case RING_BASIC_TYPE_FUNC: {
                    RVM_Closure* closure = STACK_GET_CLOSURE_INDEX(argument_stack_index + argument_stack_offset);
                    rvm_array_set_closure(rvm, array_value, array_index, &closure);
                } break;

                default:
                    ring_error_report("not support `any` as variadic parameter");
                    break;
                }
            }

            STACK_SET_ARRAY_INDEX(
                VM_CUR_CO_STACK_TOP_INDEX + local_vari_stack_offset,
                array_value);
            local_vari_stack_offset++;

            // 可变参数只能是函数的最后一个参数
            // 直接break没有问题
            break;
        } else {
            STACK_COPY_INDEX(
                VM_CUR_CO_STACK_TOP_INDEX + local_vari_stack_offset,
                argument_stack_index + argument_stack_offset);
            local_vari_stack_offset++;
        }
    }


    // Step-3: init local variables which defined in callee_function.
    for (unsigned int i = 0;
         i < callee_function->local_variable_size;
         i++) {

        type_specifier = callee_function->local_variable_list[i].type_specifier;

        // 初始化 self 变量
        if (callee_object != nullptr && i == 0) {
            // 如果 callee_object != nullptr
            // function->local_variable_list[0] 是self 变量
            // 将 callee_object 初始化给 self
            // 这个操作 已经在 Step-1 完成了, 该变量需要忽略.
            continue;
        }

        // local_variable_list 其实是包含 parameter_list , 避免重复初始化
        // 看看 是否已经在 Step-2初始化了
        // TODO: 后续优化一下, 这个试下方式不太好
        bool already_init = false;
        for (unsigned int p = 0; p < callee_function->parameter_size; p++) {
            RVM_Parameter* parameter = &callee_function->parameter_list[p];
            if (str_eq(callee_function->local_variable_list[i].identifier, parameter->identifier)) {
                already_init = true;
                break;
            }
        }
        if (already_init) {
            continue;
        }

        switch (type_specifier->kind) {
        case RING_BASIC_TYPE_BOOL:
            STACK_SET_BOOL_INDEX(VM_CUR_CO_STACK_TOP_INDEX + local_vari_stack_offset, RVM_FALSE);
            break;
        case RING_BASIC_TYPE_INT:
            STACK_SET_INT_INDEX(VM_CUR_CO_STACK_TOP_INDEX + local_vari_stack_offset, 0);
            break;
        case RING_BASIC_TYPE_INT64:
            STACK_SET_INT64_INDEX(VM_CUR_CO_STACK_TOP_INDEX + local_vari_stack_offset, 0);
            break;
        case RING_BASIC_TYPE_DOUBLE:
            STACK_SET_DOUBLE_INDEX(VM_CUR_CO_STACK_TOP_INDEX + local_vari_stack_offset, 0.0);
            break;
        case RING_BASIC_TYPE_STRING:
            string = rvm_gc_new_string_meta(rvm);
            rvm_fill_string(rvm, string, ROUND_UP8(1));
            STACK_SET_STRING_INDEX(VM_CUR_CO_STACK_TOP_INDEX + local_vari_stack_offset, string);
            break;
        case RING_BASIC_TYPE_CLASS:
            rvm_class_definition = &(rvm->class_list[type_specifier->u.class_def_index]);
            class_ob             = rvm_gc_new_class_ob_meta(rvm);
            rvm_fill_class_ob(rvm, class_ob, rvm_class_definition);
            STACK_SET_CLASS_OB_INDEX(VM_CUR_CO_STACK_TOP_INDEX + local_vari_stack_offset, class_ob);
            break;
        case RING_BASIC_TYPE_ARRAY: {
            // 这里没有分配空间, 只分配了一下meta
            RVM_ClassDefinition* sub_class_definition = nullptr;
            RVM_TypeSpecifier*   sub_type_specifier   = type_specifier->u.array_t->sub;
            if (sub_type_specifier->kind == RING_BASIC_TYPE_CLASS) {
                sub_class_definition = &(rvm->class_list[sub_type_specifier->u.class_def_index]);
            }

            array = rvm_gc_new_array_meta(rvm,
                                          RVM_Array_Type(type_specifier->u.array_t->sub->kind), // 这里强制转化一下
                                          sub_class_definition,
                                          type_specifier->u.array_t->dimension);

            STACK_SET_ARRAY_INDEX(VM_CUR_CO_STACK_TOP_INDEX + local_vari_stack_offset, array);
        } break;
        case RING_BASIC_TYPE_FUNC:
            // TODO: 这里没有分配空间
            STACK_SET_CLOSURE_INDEX(VM_CUR_CO_STACK_TOP_INDEX + local_vari_stack_offset, nullptr);
            break;

        default:
            break;
        }

        local_vari_stack_offset++;
    }

    // 如果 runtime_stack 中没有对应的参数
    // caller 还尝试获取对应的参数，那么这里就会报错
    assert(callee_function->local_variable_size == local_vari_stack_offset);

    // Step-End: increase top index of runtime_stack.
    VM_CUR_CO_STACK_TOP_INDEX += callee_function->local_variable_size;
}


/*
 * 通过string常量 去创建一个临时变量
 *
 * TODO: 这个变量的生命周期在 会随着 function 的完成而结束
 *
 * 场景:
 *     1. string_value = "abc";
 *     2. return "abc";
 *
 */
RVM_String* string_literal_to_rvm_string(Ring_VirtualMachine* rvm, const char* string_literal) {
    size_t length      = 0;
    length             = (string_literal != nullptr) ? strlen(string_literal) : 0;

    RVM_String* string = rvm_gc_new_string_meta(rvm);
    rvm_fill_string(rvm, string, ROUND_UP8(length));

    strncpy(string->data, string_literal, length);
    string->length = length;

    return string;
}

/*
 * 拼接字符串运算符 ..
 *
 * 拼接之后会创建一个临时变量
 * TODO: 这个变量的生命周期 会随着 function 的完成而结束
 *
 * 场景:
 *     1. fmt::println_string("a".."b");
 *     2. return "a".."b";
 *
 */
RVM_String* concat_string(Ring_VirtualMachine* rvm, RVM_String* a, RVM_String* b) {
    assert(a != nullptr);
    assert(b != nullptr);

    RVM_String* string;

    string = rvm_gc_new_string_meta(rvm);
    rvm_fill_string(rvm, string, ROUND_UP8(a->length + b->length));

    string->length = a->length + b->length;
    strncpy(string->data, a->data, a->length);
    strncpy(string->data + a->length, b->data, b->length);

    return string;
}


/*
 * rvm_new_array_literal_bool
 *
 * 只用来初始化一维数组常量
 */
RVM_Array* rvm_new_array_literal_bool(Ring_VirtualMachine* rvm, unsigned int size) {
    unsigned int dimension        = 1;
    unsigned int dimension_list[] = {size};

    RVM_Array*   array            = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_BOOL, nullptr);
    for (unsigned int i = 0; i < size; i++) {
        array->u.bool_array[i] = STACK_GET_BOOL_OFFSET(-size + i);
    }

    return array;
}

/*
 * rvm_new_array_literal_int
 *
 * 只用来初始化一维数组常量
 */
RVM_Array* rvm_new_array_literal_int(Ring_VirtualMachine* rvm, unsigned int size) {
    unsigned int dimension        = 1;
    unsigned int dimension_list[] = {size};

    RVM_Array*   array            = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_INT, nullptr);
    for (unsigned int i = 0; i < size; i++) {
        array->u.int_array[i] = STACK_GET_INT_OFFSET(-size + i);
    }

    return array;
}

/*
 * rvm_new_array_literal_int64
 *
 * 只用来初始化一维数组常量
 */
RVM_Array* rvm_new_array_literal_int64(Ring_VirtualMachine* rvm, unsigned int size) {
    unsigned int dimension        = 1;
    unsigned int dimension_list[] = {size};

    RVM_Array*   array            = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_INT64, nullptr);
    for (unsigned int i = 0; i < size; i++) {
        array->u.int64_array[i] = STACK_GET_INT64_OFFSET(-size + i);
    }

    return array;
}

/*
 * rvm_new_array_literal_double
 *
 * 只用来初始化一维数组常量
 */
RVM_Array* rvm_new_array_literal_double(Ring_VirtualMachine* rvm, unsigned int size) {
    unsigned int dimension        = 1;
    unsigned int dimension_list[] = {size};

    RVM_Array*   array            = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_DOUBLE, nullptr);
    for (unsigned int i = 0; i < size; i++) {
        array->u.double_array[i] = STACK_GET_DOUBLE_OFFSET(-size + i);
    }

    return array;
}

/*
 * rvm_new_array_literal_string
 *
 * 只用来初始化一维数组常量
 */
RVM_Array* rvm_new_array_literal_string(Ring_VirtualMachine* rvm, unsigned int size) {
    unsigned int dimension        = 1;
    unsigned int dimension_list[] = {size};

    RVM_Array*   array            = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_STRING, nullptr);
    for (unsigned int i = 0; i < size; i++) {
        // shallow copy 有助于提升速度
        // 这里没有错误
        array->u.string_array[i] = STACK_GET_STRING_OFFSET(-size + i);
    }

    return array;
}

/*
 * rvm_new_array_literal_class_object
 *
 * 只用来初始化一维数组常量
 */
RVM_Array* rvm_new_array_literal_class_object(Ring_VirtualMachine* rvm,
                                              unsigned int         size,
                                              RVM_ClassDefinition* class_definition) {

    unsigned int dimension        = 1;
    unsigned int dimension_list[] = {size};

    RVM_Array*   array            = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_CLASS_OBJECT, class_definition);
    for (unsigned int i = 0; i < size; i++) {
        // TODO: shallow copy
        array->u.class_ob_array[i] = STACK_GET_CLASS_OB_OFFSET(-size + i);
    }

    return array;
}

RVM_Array* rvm_new_array_literal_closure(Ring_VirtualMachine* rvm,
                                         unsigned int         size) {

    unsigned int dimension        = 1;
    unsigned int dimension_list[] = {size};

    RVM_Array*   array            = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_CLOSURE, nullptr);
    for (unsigned int i = 0; i < size; i++) {
        array->u.closure_array[i] = *STACK_GET_CLOSURE_OFFSET(-size + i);
    }

    return array;
}

/*
 * 初始化多维数组常量
 */
RVM_Array* rvm_new_array_literal_a(Ring_VirtualMachine* rvm,
                                   unsigned int         dimension,
                                   unsigned int         size) {

    RVM_Array* array = rvm_gc_new_array_meta(rvm, RVM_ARRAY_A, nullptr, dimension);
    array->length    = size;
    array->capacity  = size;

    array->u.a_array = (RVM_Array*)mem_alloc(rvm->data_pool,
                                             sizeof(RVM_Array) * array->capacity);

    // FIXME:
    for (unsigned int i = 0; i < size; i++) {
        // this is shallow copy
        array->u.a_array[i] = *(STACK_GET_ARRAY_OFFSET(-size + i));
    }

    return array;
}


void rvm_array_get_length(Ring_VirtualMachine* rvm, RVM_Array* array, int* value) {
    // FIXME: 这里unsigned int -> int
    if (array == nullptr) {
        *value = 0;
        return;
    }
    *value = (int)array->length;
}

void rvm_array_get_capacity(Ring_VirtualMachine* rvm, RVM_Array* array, int* value) {
    // FIXME: 这里unsigned int -> int
    if (array == nullptr) {
        *value = 0;
        return;
    }
    *value = (int)array->capacity;
}

void rvm_string_get_length(Ring_VirtualMachine* rvm, RVM_String* string, int* value) {
    // FIXME: 这里unsigned int -> int
    *value = (int)string->length;
}

void rvm_string_get_capacity(Ring_VirtualMachine* rvm, RVM_String* string, int* value) {
    // FIXME: 这里unsigned int -> int
    *value = (int)string->capacity;
}

//
/*
 * 多位数组的中间态, 后续优化
 * shallow copy
 */
ErrorCode rvm_array_get_array(Ring_VirtualMachine* rvm, RVM_Array* array, int index, RVM_Array** value) {
    *value = &(array->u.a_array[index]);
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_set_array(Ring_VirtualMachine* rvm, RVM_Array* array, int index, RVM_Array* value) {
    // FIXME: deep or shallow copy
    array->u.a_array[index] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_get_bool(Ring_VirtualMachine* rvm, RVM_Array* array, int index, bool* value) {
    *value = array->u.bool_array[index];
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_set_bool(Ring_VirtualMachine* rvm, RVM_Array* array, int index, bool* value) {
    array->u.bool_array[index] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_append_bool(Ring_VirtualMachine* rvm, RVM_Array* array, bool* value) {
    if (array->length == array->capacity) {
        rvm_array_growth(rvm, array);
    }
    array->u.bool_array[array->length++] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_pop_bool(Ring_VirtualMachine* rvm, RVM_Array* array, bool* value) {
    *value = array->u.bool_array[--array->length];
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_get_int(Ring_VirtualMachine* rvm, RVM_Array* array, int index, int* value) {
    *value = array->u.int_array[index];
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_set_int(Ring_VirtualMachine* rvm, RVM_Array* array, int index, int* value) {
    array->u.int_array[index] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_append_int(Ring_VirtualMachine* rvm, RVM_Array* array, int* value) {
    if (array->length == array->capacity) {
        rvm_array_growth(rvm, array);
    }
    array->u.int_array[array->length++] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_pop_int(Ring_VirtualMachine* rvm, RVM_Array* array, int* value) {
    *value = array->u.int_array[--array->length];
    return ERROR_CODE_SUCCESS;
}


ErrorCode rvm_array_get_int64(Ring_VirtualMachine* rvm, RVM_Array* array, int index, long long* value) {
    *value = array->u.int64_array[index];
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_set_int64(Ring_VirtualMachine* rvm, RVM_Array* array, int index, long long* value) {
    array->u.int64_array[index] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_append_int64(Ring_VirtualMachine* rvm, RVM_Array* array, long long* value) {
    if (array->length == array->capacity) {
        rvm_array_growth(rvm, array);
    }
    array->u.int64_array[array->length++] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_pop_int64(Ring_VirtualMachine* rvm, RVM_Array* array, long long* value) {
    *value = array->u.int64_array[--array->length];
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_get_double(Ring_VirtualMachine* rvm, RVM_Array* array, int index, double* value) {
    *value = array->u.double_array[index];
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_set_double(Ring_VirtualMachine* rvm, RVM_Array* array, int index, double* value) {
    array->u.double_array[index] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_append_double(Ring_VirtualMachine* rvm, RVM_Array* array, double* value) {
    if (array->length == array->capacity) {
        rvm_array_growth(rvm, array);
    }
    array->u.double_array[array->length++] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_pop_double(Ring_VirtualMachine* rvm, RVM_Array* array, double* value) {
    *value = array->u.double_array[--array->length];
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_get_string(Ring_VirtualMachine* rvm, RVM_Array* array, int index, RVM_String** value) {
    RVM_String* src_string = array->u.string_array[index];

    RVM_String* dst_string = rvm_deep_copy_string(rvm, src_string);

    *value                 = dst_string;
    return ERROR_CODE_SUCCESS;
}

/*
 * deep copy `value` and set by `array`&`index`
 *
 * FIXME: 重新考虑一下, 可能存在内存泄漏
 */
ErrorCode rvm_array_set_string(Ring_VirtualMachine* rvm, RVM_Array* array, int index, RVM_String** value) {
    RVM_String* dst_string       = rvm_deep_copy_string(rvm, *value);

    array->u.string_array[index] = dst_string;

    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_append_string(Ring_VirtualMachine* rvm, RVM_Array* array, RVM_String** value) {
    if (array->length >= array->capacity) {
        rvm_array_growth(rvm, array);
    }
    array->u.string_array[array->length++] = rvm_deep_copy_string(rvm, *value);
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_pop_string(Ring_VirtualMachine* rvm, RVM_Array* array, RVM_String** value) {
    RVM_String* dst_string = rvm_deep_copy_string(rvm, array->u.string_array[--array->length]);
    *value                 = dst_string; // FIXME: 这里内存泄漏了
    return ERROR_CODE_SUCCESS;
}

/*
 * shallow copy
 */
ErrorCode rvm_array_get_class_object(Ring_VirtualMachine* rvm,
                                     RVM_Array*           array,
                                     int                  index,
                                     RVM_ClassObject**    value) {

    RVM_ClassObject* src_class_object = array->u.class_ob_array[index];
    RVM_ClassObject* dst_class_object = nullptr;

    // dst_class_object = rvm_deep_copy_class_object(rvm, src_class_object);
    dst_class_object = src_class_object;

    *value           = dst_class_object;
    return ERROR_CODE_SUCCESS;
}

/*
 * deep copy `value` and set by `array`&`index`
 */
ErrorCode rvm_array_set_class_object(Ring_VirtualMachine* rvm,
                                     RVM_Array*           array,
                                     int                  index,
                                     RVM_ClassObject**    value) {

    RVM_ClassObject* dst_class_object = nullptr;
    dst_class_object                  = rvm_deep_copy_class_ob(rvm, *value);

    array->u.class_ob_array[index]    = dst_class_object;

    return ERROR_CODE_SUCCESS;
}


ErrorCode rvm_array_append_class_object(Ring_VirtualMachine* rvm,
                                        RVM_Array*           array,
                                        RVM_ClassObject**    value) {

    if (array->length >= array->capacity) {
        rvm_array_growth(rvm, array);
    }
    array->u.class_ob_array[array->length++] = rvm_deep_copy_class_ob(rvm, *value);
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_pop_class_object(Ring_VirtualMachine* rvm,
                                     RVM_Array*           array,
                                     RVM_ClassObject**    value) {

    RVM_ClassObject* src_class_object = array->u.class_ob_array[--array->length];
    RVM_ClassObject* dst_class_object = rvm_deep_copy_class_ob(rvm, src_class_object);

    *value                            = dst_class_object;
    return ERROR_CODE_SUCCESS;
}

/*
 * shallow copy
 */
ErrorCode rvm_array_get_closure(Ring_VirtualMachine* rvm,
                                RVM_Array*           array,
                                int                  index,
                                RVM_Closure**        value) {

    RVM_Closure* src_closure = &(array->u.closure_array[index]);
    RVM_Closure* dst_closure = nullptr;

    // dst_class_object = rvm_deep_copy_class_object(rvm, src_class_object);
    // FIXME: deep 还是 shallow
    dst_closure = src_closure;

    *value      = dst_closure;
    return ERROR_CODE_SUCCESS;
}

/*
 * shallow copy
 */
ErrorCode rvm_array_set_closure(Ring_VirtualMachine* rvm,
                                RVM_Array*           array,
                                int                  index,
                                RVM_Closure**        value) {

    RVM_Closure* dst_closure = nullptr;
    // FIXME: deep 还是 shallow
    dst_closure                   = *value;

    array->u.closure_array[index] = *dst_closure;

    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_append_closure(Ring_VirtualMachine* rvm,
                                   RVM_Array*           array,
                                   RVM_Closure**        value) {

    if (array->length >= array->capacity) {
        rvm_array_growth(rvm, array);
    }
    // FIXME: deep 还是 shallow
    array->u.closure_array[array->length++] = **value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_pop_closure(Ring_VirtualMachine* rvm,
                                RVM_Array*           array,
                                RVM_Closure**        value) {

    RVM_Closure* src_closure = &(array->u.closure_array[--array->length]);
    // FIXME: deep 还是 shallow
    RVM_Closure* dst_closure = src_closure;

    *value                   = dst_closure;
    return ERROR_CODE_SUCCESS;
}


RVM_String* rvm_bool_2_string(Ring_VirtualMachine* rvm, bool value) {
    RVM_String* string = 0;

    string             = rvm_gc_new_string_meta(rvm);
    rvm_fill_string(rvm, string, ROUND_UP8(1));

    if (value) {
        string->length = 4;
        memcpy(string->data, "true", 4);
    } else {
        string->length = 5;
        memcpy(string->data, "false", 5);
    }

    return string;
}

RVM_String* rvm_int_2_string(Ring_VirtualMachine* rvm, int value) {
    RVM_String* string = 0;

    // TODO:这里直接用的 cpp的函数, 内存copy了两次
    std::string tmp = std::to_string(value);

    string          = rvm_gc_new_string_meta(rvm);
    rvm_fill_string(rvm, string, ROUND_UP8(tmp.size()));

    string->length = tmp.size();
    strncpy(string->data, tmp.c_str(), tmp.size());

    return string;
}

RVM_String* rvm_int64_2_string(Ring_VirtualMachine* rvm, long long value) {
    RVM_String* string = 0;

    // TODO:这里直接用的 cpp的函数, 内存copy了两次
    std::string tmp = std::to_string(value);

    string          = rvm_gc_new_string_meta(rvm);
    rvm_fill_string(rvm, string, ROUND_UP8(tmp.size()));

    string->length = tmp.size();
    strncpy(string->data, tmp.c_str(), tmp.size());

    return string;
}

RVM_String* rvm_double_2_string(Ring_VirtualMachine* rvm, double value) {
    RVM_String* string = 0;

    // TODO:这里直接用的 cpp的函数, 内存copy了两次
    std::string tmp = std::to_string(value);

    string          = rvm_gc_new_string_meta(rvm);
    rvm_fill_string(rvm, string, ROUND_UP8(tmp.size()));

    string->length = tmp.size();
    strncpy(string->data, tmp.c_str(), tmp.size());

    return string;
}


/*
 * rvm_string_cmp 和 string_compare 实现重复了，后续需要结合到一起
 */
int rvm_string_cmp(RVM_String* string1, RVM_String* string2) {
    char*        str1     = nullptr;
    char*        str2     = nullptr;
    unsigned int str1_len = 0;
    unsigned int str2_len = 0;

    if (string1 != nullptr) {
        str1     = string1->data;
        str1_len = string1->length;
    }
    if (string2 != nullptr) {
        str2     = string2->data;
        str2_len = string2->length;
    }

    if (str1_len == 0 && str2_len == 0) {
        return 0;
    } else if (str1_len == 0 && str2_len != 0) {
        return -1;
    } else if (str1_len != 0 && str2_len == 0) {
        return 1;
    }

    unsigned int min_len = (str1_len > str2_len) ? str2_len : str1_len;
    int          res     = strncmp(str1, str2, min_len);
    if (res == 0) {
        if (str1_len > str2_len)
            return 1;
        else if (str1_len == str2_len)
            return 0;
        else
            return -1;
    } else {
        return res;
    }
}


RVM_Closure* new_closure(Ring_VirtualMachine* rvm,
                         RVM_Function* caller_function, RVM_Closure* caller_closure,
                         RVM_Function* callee_function) {

    // FIXME: 需要分配在堆上
    // free value 需要分配在堆上
    RVM_Closure* closure = rvm_gc_new_closure_meta(rvm);
    rvm_fill_closure(rvm, closure, callee_function);

    // printf("[Debug][New Closure] parent:(%p,%p), func:%p, closure(%p)\n",
    //        caller_function, caller_closure, callee_function, closure);
    // free value 的指针指向 当前栈的空间 索引位置
    // 此时为 open
    for (unsigned int i = 0; i < callee_function->free_value_size; i++) {
        // TODO: 当前只支持直接外围函数的局部变量 作为FreeValue

        if (callee_function->free_value_list[i].is_curr_local) {
            // FIXME: 这里有问题  VM_CUR_CO_CSB 不正确
            unsigned int index                   = callee_function->free_value_list[i].u.curr_local_index;

            closure->free_value_list[i].is_recur = false;
            closure->free_value_list[i].u.p      = &(VM_CUR_CO_STACK_DATA[VM_CUR_CO_CSB + index]);
            closure->free_value_list[i].is_open  = true;
            closure->free_value_list[i].c_value  = RVM_Value{};
        } else {
            assert(caller_closure != nullptr);
            unsigned int index = callee_function->free_value_list[i].u.out_free_value_index;
            // printf("out_free_value_index:%u\n", index);

            // 通过调用链向上递归查找, 知道找到直接指向的agent
            RVM_FreeValue* parent = &(caller_closure->free_value_list[index]);
            while (parent->is_recur) {
                parent = parent->u.recur;
            }
            closure->free_value_list[i].is_recur = true;
            closure->free_value_list[i].u.recur  = parent;
        }
    }

    if (RING_DEBUG_TRACE_CLOSURE_FREE_VALUE) {
#ifdef DEBUG_TRACE_CLOSURE_FREE_VALUE
        debug_generate_closure_dot_file(closure);
#endif
    }

    return closure;
}


/*
 * new_defer_item
 * 1. 初始化 defer_item
 * 2. 对于 defer function(){}(a,b,c) 语句
 *    语义逻辑为：值捕获
 *    需要立即将 a,b,c 参数从栈中deep_copy到 defer_item的存储空间中
 *    这样在 pop_defer的时候值会保持为捕获时的值
 */
RVM_DeferItem* new_defer_item(Ring_VirtualMachine* rvm,
                              RVM_Closure*         closure,
                              unsigned int         argument_list_size) {

    RVM_DeferItem* defer_item = (RVM_DeferItem*)mem_alloc(rvm->meta_pool,
                                                          sizeof(RVM_DeferItem));

    defer_item->argument_size = argument_list_size;
    defer_item->argument_list = (RVM_Value*)mem_alloc(rvm->meta_pool, defer_item->argument_size * sizeof(RVM_Value));
    defer_item->closure       = closure;
    defer_item->next          = nullptr;

    // deep_copy argument_list from runtime_stack to defer_item->argument_list
    for (unsigned int i = 0; i < argument_list_size; i++) {
        // TODO: 这里还不是 deep copy
        defer_item->argument_list[i] = VM_CUR_CO_STACK_DATA[VM_CUR_CO_CSB + i];
    }

    // 释放 runtime_stack 空间
    VM_CUR_CO_STACK_TOP_INDEX -= argument_list_size;

    return defer_item;
}

void coroutine_push_defer_item(Ring_VirtualMachine* rvm, RVM_DeferItem* defer_item) {
    debug_exec_info_with_white("coroutine_push_defer_item: defer_item:%p argument_list:%u closure:%p\n",
                               defer_item,
                               defer_item->argument_size,
                               defer_item->closure);

    defer_item->next = VM_CUR_CO->defer_list;

    VM_CUR_CO->defer_list_size++;
    VM_CUR_CO->defer_list = defer_item;
}

RVM_DeferItem* coroutine_pop_defer_item(Ring_VirtualMachine* rvm) {
    if (VM_CUR_CO->defer_list_size == 0) {
        return nullptr;
    }

    RVM_DeferItem* defer_item = VM_CUR_CO->defer_list;
    VM_CUR_CO->defer_list_size--;
    VM_CUR_CO->defer_list = VM_CUR_CO->defer_list->next;
    return defer_item;
}

/*
 * fill_defer_item_argument_stack
 * 在 new_defer_item 中，从runtime_stack 复制到 defer_item 中
 * 此时：将 defer_item 中的参数 复制回 runtime_stack
 * defer_item->closure 将用于参数进行函数调用
 */
void fill_defer_item_argument_stack(Ring_VirtualMachine* rvm, RVM_DeferItem* defer_item) {
    // deep_copy argument_list from defer_item->argument_list to runtime_stack
    for (unsigned int i = 0; i < defer_item->argument_size; i++) {
        // TODO: 这里还不是 deep copy
        VM_CUR_CO_STACK_DATA[VM_CUR_CO_STACK_TOP_INDEX + i] = defer_item->argument_list[i];
    }

    VM_CUR_CO_STACK_TOP_INDEX += defer_item->argument_size;
}

// 在函数调用的过程中，处理函数的 可变参数，将它变为数组
// size 为数组最外围维度的大小
RVM_Array* init_derive_function_variadic_argument(Ring_VirtualMachine* rvm,
                                                  RVM_Parameter*       parameter,
                                                  unsigned int         size) {

    RVM_Array*           array_value          = nullptr;
    RVM_ClassDefinition* rvm_class_definition = nullptr;

    if (parameter->type_specifier->kind == RING_BASIC_TYPE_CLASS) {
        rvm_class_definition = &(rvm->class_list[parameter->type_specifier->u.class_def_index]);
    }

    // 默认一维数组
    unsigned int dimension = 1;
    if (parameter->type_specifier->kind == RING_BASIC_TYPE_ARRAY) {
        // 增加一个维度
        dimension = parameter->type_specifier->u.array_t->dimension + 1;
    }
    unsigned int dimension_list[] = {size, 0, 0, 0, 0, 0, 0, 0};
    // 为了实现简单，直接补齐7个0 即可，数组的最大维度为8

    array_value = rvm_new_array(rvm,
                                dimension, dimension_list, dimension,
                                RVM_Array_Type(parameter->type_specifier->kind),
                                rvm_class_definition);

    return array_value;
}

void batch_set_variadic_element(Ring_VirtualMachine* rvm) {
}