#include "ring.hpp"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/ioctl.h>
#include <unistd.h>


extern RVM_Opcode_Info RVM_Opcode_Infos[];


// 通过绝对索引 获取 rvm->runtime_stack->data
#define STACK_GET_BOOL_INDEX(rvm, index) \
    ((rvm)->runtime_stack->data[(index)].u.bool_value)
#define STACK_GET_INT_INDEX(rvm, index) \
    ((rvm)->runtime_stack->data[(index)].u.int_value)
#define STACK_GET_DOUBLE_INDEX(rvm, index) \
    ((rvm)->runtime_stack->data[(index)].u.double_value)
#define STACK_GET_STRING_INDEX(rvm, index) \
    ((rvm)->runtime_stack->data[(index)].u.string_value)
#define STACK_GET_CLASS_OB_INDEX(rvm, index) \
    ((rvm)->runtime_stack->data[(index)].u.class_ob_value)
#define STACK_GET_ARRAY_INDEX(rvm, index) \
    ((rvm)->runtime_stack->data[(index)].u.array_value)

// 通过栈顶偏移 offset 获取 rvm->runtime_stack->data
#define STACK_GET_BOOL_OFFSET(rvm, offset) \
    STACK_GET_BOOL_INDEX((rvm), (rvm)->runtime_stack->top_index + (offset))
#define STACK_GET_INT_OFFSET(rvm, offset) \
    STACK_GET_INT_INDEX((rvm), (rvm)->runtime_stack->top_index + (offset))
#define STACK_GET_DOUBLE_OFFSET(rvm, offset) \
    STACK_GET_DOUBLE_INDEX((rvm), (rvm)->runtime_stack->top_index + (offset))
#define STACK_GET_STRING_OFFSET(rvm, offset) \
    STACK_GET_STRING_INDEX((rvm), (rvm)->runtime_stack->top_index + (offset))
#define STACK_GET_CLASS_OB_OFFSET(rvm, offset) \
    STACK_GET_CLASS_OB_INDEX((rvm), (rvm)->runtime_stack->top_index + (offset))
#define STACK_GET_ARRAY_OFFSET(rvm, offset) \
    STACK_GET_ARRAY_INDEX((rvm), (rvm)->runtime_stack->top_index + (offset))


// 通过绝对索引 设置 rvm->runtime_stack->data
#define STACK_SET_BOOL_INDEX(rvm, index, value)                             \
    (rvm)->runtime_stack->data[(index)].type         = RVM_VALUE_TYPE_BOOL; \
    (rvm)->runtime_stack->data[(index)].u.bool_value = (value);
#define STACK_SET_INT_INDEX(rvm, index, value)                            \
    (rvm)->runtime_stack->data[(index)].type        = RVM_VALUE_TYPE_INT; \
    (rvm)->runtime_stack->data[(index)].u.int_value = (value);
#define STACK_SET_DOUBLE_INDEX(rvm, index, value)                               \
    (rvm)->runtime_stack->data[(index)].type           = RVM_VALUE_TYPE_DOUBLE; \
    (rvm)->runtime_stack->data[(index)].u.double_value = (value);
#define STACK_SET_STRING_INDEX(rvm, index, value)                               \
    (rvm)->runtime_stack->data[(index)].type           = RVM_VALUE_TYPE_STRING; \
    (rvm)->runtime_stack->data[(index)].u.string_value = (value);
#define STACK_SET_CLASS_OB_INDEX(rvm, index, value)                                 \
    (rvm)->runtime_stack->data[(index)].type             = RVM_VALUE_TYPE_CLASS_OB; \
    (rvm)->runtime_stack->data[(index)].u.class_ob_value = (value);
#define STACK_SET_ARRAY_INDEX(rvm, index, value)                              \
    (rvm)->runtime_stack->data[(index)].type          = RVM_VALUE_TYPE_ARRAY; \
    (rvm)->runtime_stack->data[(index)].u.array_value = (value);


// 通过栈顶偏移 offset 设置 rvm->runtime_stack->data
#define STACK_SET_BOOL_OFFSET(rvm, offset, value) \
    STACK_SET_BOOL_INDEX(rvm, (rvm)->runtime_stack->top_index + (offset), (value))
#define STACK_SET_INT_OFFSET(rvm, offset, value) \
    STACK_SET_INT_INDEX(rvm, (rvm)->runtime_stack->top_index + (offset), (value))
#define STACK_SET_DOUBLE_OFFSET(rvm, offset, value) \
    STACK_SET_DOUBLE_INDEX(rvm, (rvm)->runtime_stack->top_index + (offset), (value))
#define STACK_SET_STRING_OFFSET(rvm, offset, value) \
    STACK_SET_STRING_INDEX(rvm, (rvm)->runtime_stack->top_index + (offset), (value))
#define STACK_SET_CLASS_OB_OFFSET(rvm, offset, value) \
    STACK_SET_CLASS_OB_INDEX(rvm, (rvm)->runtime_stack->top_index + (offset), (value))
#define STACK_SET_ARRAY_OFFSET(rvm, offset, value) \
    STACK_SET_ARRAY_INDEX(rvm, (rvm)->runtime_stack->top_index + (offset), (value))


#define STACK_COPY_INDEX(rvm, dst_index, src_index) \
    ((rvm)->runtime_stack->data[(dst_index)] = (rvm)->runtime_stack->data[(src_index)])

#define STACK_COPY_OFFSET(rvm, dst_offset, src_offset) \
    STACK_COPY_INDEX((rvm), (rvm)->runtime_stack->top_index + (dst_offset), (rvm)->runtime_stack->top_index + (src_offset))


// 通过绝对索引 设置 rvm->runtime_static->data
#define STATIC_SET_BOOL_INDEX(rvm, index, value)                             \
    (rvm)->runtime_static->data[(index)].type         = RVM_VALUE_TYPE_BOOL; \
    (rvm)->runtime_static->data[(index)].u.bool_value = (value);
#define STATIC_SET_INT_INDEX(rvm, index, value)                            \
    (rvm)->runtime_static->data[(index)].type        = RVM_VALUE_TYPE_INT; \
    (rvm)->runtime_static->data[(index)].u.int_value = (value);
#define STATIC_SET_DOUBLE_INDEX(rvm, index, value)                               \
    (rvm)->runtime_static->data[(index)].type           = RVM_VALUE_TYPE_DOUBLE; \
    (rvm)->runtime_static->data[(index)].u.double_value = (value);
#define STATIC_SET_STRING_INDEX(rvm, index, value)                               \
    (rvm)->runtime_static->data[(index)].type           = RVM_VALUE_TYPE_STRING; \
    (rvm)->runtime_static->data[(index)].u.string_value = (value);
#define STATIC_SET_CLASS_OB_INDEX(rvm, index, value)                                 \
    (rvm)->runtime_static->data[(index)].type             = RVM_VALUE_TYPE_CLASS_OB; \
    (rvm)->runtime_static->data[(index)].u.class_ob_value = (value);
#define STATIC_SET_ARRAY_INDEX(rvm, index, value)                              \
    (rvm)->runtime_static->data[(index)].type          = RVM_VALUE_TYPE_ARRAY; \
    (rvm)->runtime_static->data[(index)].u.array_value = (value);


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
    stack->capacity         = 1024 * 1024;                                                               // FIXME: 先开辟一个大的空间
    stack->data             = (RVM_Value*)mem_alloc(NULL_MEM_POOL, stack->capacity * sizeof(RVM_Value)); // TODO: 这里暂时不需要通过内存池
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
    rvm->runtime_stack       = new_runtime_stack();
    rvm->runtime_heap        = new_runtime_heap();
    rvm->pc                  = 0;
    rvm->call_info           = nullptr;
    rvm->class_list          = nullptr;
    rvm->class_size          = 0;
    rvm->meta_pool           = create_mem_pool((char*)"RVM-Meta-Memory-Pool");
    rvm->data_pool           = create_mem_pool((char*)"RVM-Data-Memory-Pool");
    rvm->debug_config        = nullptr;
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
 * 将 package 中 所有的 全局变量添加到 runtime_static中
 */
void rvm_add_static_variable(Package_Executer*  executer,
                             RVM_RuntimeStatic* runtime_static) {

    unsigned int size    = executer->global_variable_size;
    runtime_static->size = size;
    runtime_static->data = (RVM_Value*)mem_alloc(NULL_MEM_POOL, size * sizeof(RVM_Value));
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
}

/*
 * 对全局变量进行初始化
 *
 * 1. 如果有初始化表达式的话，那就通过表达式来初始化
 * 2. 通过默认值初始化
 *
 */
void rvm_init_static_variable(Ring_VirtualMachine* rvm,
                              Package_Executer*    executer,
                              RVM_RuntimeStatic*   runtime_static) {

    unsigned int         size                 = executer->global_variable_size;
    RVM_Variable*        global_variable_list = executer->global_variable_list;
    RVM_TypeSpecifier*   type_specifier       = nullptr;
    RVM_ClassDefinition* rvm_class_definition = nullptr;
    RVM_ClassObject*     class_ob             = nullptr;
    RVM_String*          string               = nullptr;
    unsigned int         alloc_size           = 0;

    for (unsigned int i = 0; i < size; i++) {
        type_specifier = global_variable_list[i].type_specifier;

        switch (type_specifier->kind) {
        case RING_BASIC_TYPE_BOOL:
            STACK_SET_BOOL_INDEX(rvm, i, RVM_FALSE);
            break;
        case RING_BASIC_TYPE_INT:
            STACK_SET_INT_INDEX(rvm, i, 0);
            break;
        case RING_BASIC_TYPE_DOUBLE:
            STACK_SET_DOUBLE_INDEX(rvm, i, 0.0);
            break;
        case RING_BASIC_TYPE_STRING:
            string     = new_string(rvm);
            alloc_size = init_string(rvm, string, ROUND_UP8(1));
            rvm_heap_list_add_object(rvm, (RVM_GC_Object*)string);
            rvm_heap_alloc_size_incr(rvm, alloc_size);

            STATIC_SET_STRING_INDEX(rvm, i, string);
            break;
        case RING_BASIC_TYPE_CLASS:
            rvm_class_definition = &(rvm->class_list[type_specifier->u.class_def_index]);
            class_ob             = rvm_new_class_object(rvm, rvm_class_definition);
            STATIC_SET_CLASS_OB_INDEX(rvm, i, class_ob);
            break;

        case RING_BASIC_TYPE_ARRAY:
            runtime_static->data[i].type                     = RVM_VALUE_TYPE_ARRAY;
            runtime_static->data[i].u.array_value            = new_array(rvm);
            runtime_static->data[i].u.array_value->type      = RVM_Array_Type(type_specifier->sub->kind); // 这里强制转化一下
            runtime_static->data[i].u.array_value->dimension = type_specifier->dimension;
            runtime_static->data[i].u.array_value->length    = 0;
            runtime_static->data[i].u.array_value->capacity  = 0;
            break;

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
void ring_execute_vm_code(Ring_VirtualMachine* rvm) {

    RVM_Byte*            code_list              = rvm->executer->code_list;
    unsigned int         code_size              = rvm->executer->code_size;
    RVM_ConstantPool*    constant_pool_list     = rvm->executer->constant_pool_list;
    RVM_RuntimeStack*    runtime_stack          = rvm->runtime_stack;

    unsigned int         index                  = 0;
    unsigned int         runtime_static_index   = 0;
    unsigned int         package_index          = 0;
    unsigned int         func_index             = 0;
    unsigned int         method_index           = 0;
    unsigned int         oper_num               = 0;
    unsigned int         class_index            = 0;
    unsigned int         field_index            = 0;
    unsigned int         dimension              = 0;
    unsigned int         const_index            = 0;
    unsigned int         caller_stack_base      = 0;
    unsigned int         argument_list_size     = 0;
    unsigned int         caller_stack_offset    = 0;
    unsigned int         return_value_list_size = 0;
    unsigned int         array_size             = 0;

    bool                 bool_value             = false;
    int                  int_value              = 0;
    double               double_value           = 0;
    RVM_String*          string_value           = nullptr;
    RVM_ClassObject*     class_ob_value         = nullptr;
    RVM_Array*           array_value            = nullptr;
    RVM_Array*           array_c                = nullptr;

    RVM_ClassDefinition* rvm_class_definition   = nullptr;
    RVM_Function*        function               = nullptr;
    RVM_Method*          method                 = nullptr;


    ErrorCode            error_code             = ERROR_CODE_SUCCESS;
    RVM_Frame            frame;
    unsigned int         prev_code_line_number = 0;

    unsigned int*        dimension_list        = (unsigned int*)calloc(1, sizeof(unsigned int) * MAX_DIMENSION_NUM);

    while (rvm->pc < code_size) {
        RVM_Byte opcode = code_list[rvm->pc];

#ifdef DEBUG_RVM_INTERACTIVE
        debug_rvm(rvm, function, code_list, code_size, rvm->pc, caller_stack_base);
#endif

        if (rvm->debug_config != nullptr && rvm->debug_config->enable) {
            assert(rvm->debug_config->trace_dispatch != nullptr);

            RVM_Opcode_Info opcode_info;
            opcode_info = RVM_Opcode_Infos[opcode];

            std::vector<std::pair<std::string, RVM_Value*>> globals;
            std::vector<std::pair<std::string, RVM_Value*>> locals;

            // 1
            std::string function_name;
            function_name = "$ring!start()";
            if (rvm->call_info != nullptr
                && rvm->call_info->callee_function != nullptr) {
                function_name = std::string(rvm->call_info->callee_function->func_name) + "()";
            }
            // 2. build globals
            for (int i = 0; i < rvm->executer->global_variable_size; i++) {
                std::pair<std::string, RVM_Value*> global = {
                    std::string(rvm->executer->global_variable_list[i].identifier),
                    nullptr,
                };
                globals.push_back(global);
            }

            // 3. build locals
            if (rvm->call_info != nullptr
                && rvm->call_info->callee_function != nullptr) {
                for (unsigned int i = 0; i < rvm->call_info->callee_function->local_variable_size; i++) {
                    std::pair<std::string, RVM_Value*> local = {
                        std::string(rvm->call_info->callee_function->local_variable_list[i].identifier),
                        nullptr,
                    };
                    locals.push_back(local);
                }
            }

            // 4.
            std::string event;
            if (opcode == RVM_CODE_INVOKE_FUNC || opcode == RVM_CODE_INVOKE_METHOD) {
                event = "call";
            } else if (opcode == RVM_CODE_FUNCTION_FINISH) {
                event = "return";
            } else {
                event = "opcode";
            }

            // if (rvm->call_info != nullptr
            //     && rvm->call_info->callee_function != nullptr
            //     && rvm->call_info->callee_function->type == RVM_FUNCTION_TYPE_DERIVE) {
            //     std::vector<RVM_SourceCodeLineMap> code_line_map;
            //     code_line_map = rvm->call_info->callee_function->u.derive_func->code_line_map;

            //     if (rvm->pc == code_line_map[code_line_map_index].opcode_begin_index) {
            //         source_code_line_number = code_line_map[code_line_map_index].line_number;
            //         code_line_map_index++;

            //         event = "line";
            //     }
            // }

            unsigned int source_code_line_number = 0;
            if (rvm->call_info != nullptr
                && rvm->call_info->callee_function != nullptr) {
                source_code_line_number = get_source_line_number_by_pc(rvm->call_info->callee_function, rvm->pc);
            }

            if (source_code_line_number != 0 && source_code_line_number != prev_code_line_number) {
                if (event != "return")
                    event = "line";
                prev_code_line_number = source_code_line_number;
            }

            //
            frame = RVM_Frame{
                .call_info          = rvm->call_info,
                .callee_func        = function_name.c_str(),
                .next_opcode        = opcode_info.name.c_str(),
                .source_line_number = source_code_line_number,
                .globals            = globals,
                .locals             = locals,
            };
            rvm->debug_config->trace_dispatch(&frame, event.c_str(), "");
        }

        switch (opcode) {
        // int double string const
        case RVM_CODE_PUSH_BOOL:
            STACK_SET_BOOL_OFFSET(rvm, 0, (RVM_Bool)OPCODE_GET_1BYTE(&code_list[rvm->pc + 1]));
            runtime_stack->top_index++;
            rvm->pc += 2;
            break;
        case RVM_CODE_PUSH_INT_1BYTE:
            STACK_SET_INT_OFFSET(rvm, 0, OPCODE_GET_1BYTE(&code_list[rvm->pc + 1]));
            runtime_stack->top_index++;
            rvm->pc += 2;
            break;
        case RVM_CODE_PUSH_INT_2BYTE:
            STACK_SET_INT_OFFSET(rvm, 0, OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]));
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_INT:
            const_index = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_INT_OFFSET(rvm, 0, constant_pool_list[const_index].u.int_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_DOUBLE:
            const_index = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_DOUBLE_OFFSET(rvm, 0, constant_pool_list[const_index].u.double_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STRING:
            const_index  = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            string_value = string_literal_to_rvm_string(rvm, constant_pool_list[const_index].u.string_value);
            STACK_SET_STRING_OFFSET(rvm, 0, string_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;


        // static
        case RVM_CODE_POP_STATIC_BOOL:
            runtime_static_index = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STATIC_SET_BOOL_INDEX(rvm, runtime_static_index, STACK_GET_BOOL_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_STATIC_INT:
            runtime_static_index = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STATIC_SET_INT_INDEX(rvm, runtime_static_index, STACK_GET_INT_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_STATIC_DOUBLE:
            runtime_static_index = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STATIC_SET_DOUBLE_INDEX(rvm, runtime_static_index, STACK_GET_DOUBLE_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_STATIC_STRING:
            runtime_static_index = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STATIC_SET_STRING_INDEX(rvm, runtime_static_index, STACK_GET_STRING_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_STATIC_CLASS_OB:
            runtime_static_index = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STATIC_SET_CLASS_OB_INDEX(rvm, runtime_static_index, STACK_GET_CLASS_OB_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_STATIC_ARRAY:
            runtime_static_index = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            // shallow copy
            // array_value = STACK_GET_OBJECT_OFFSET(rvm, -1);
            // deep copy
            array_value = rvm_deep_copy_array(rvm, STACK_GET_ARRAY_OFFSET(rvm, -1));
            STATIC_SET_ARRAY_INDEX(rvm, runtime_static_index, array_value);
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STATIC_BOOL:
            runtime_static_index = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_BOOL_OFFSET(rvm, 0, rvm->runtime_static->data[runtime_static_index].u.bool_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STATIC_INT:
            runtime_static_index = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_INT_OFFSET(rvm, 0, rvm->runtime_static->data[runtime_static_index].u.int_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STATIC_DOUBLE:
            runtime_static_index = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_DOUBLE_OFFSET(rvm, 0, rvm->runtime_static->data[runtime_static_index].u.double_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STATIC_STRING:
            runtime_static_index = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_STRING_OFFSET(rvm, 0, rvm->runtime_static->data[runtime_static_index].u.string_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STATIC_CLASS_OB:
            runtime_static_index = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_CLASS_OB_OFFSET(rvm, 0, rvm->runtime_static->data[runtime_static_index].u.class_ob_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STATIC_ARRAY:
            runtime_static_index = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_ARRAY_OFFSET(rvm, 0, rvm->runtime_static->data[runtime_static_index].u.array_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;

        // stack
        case RVM_CODE_POP_STACK_BOOL:
            caller_stack_offset = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_BOOL_INDEX(rvm,
                                 caller_stack_base + caller_stack_offset,
                                 STACK_GET_BOOL_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_STACK_INT:
            caller_stack_offset = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_INT_INDEX(rvm,
                                caller_stack_base + caller_stack_offset,
                                STACK_GET_INT_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_STACK_DOUBLE:
            caller_stack_offset = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_DOUBLE_INDEX(rvm,
                                   caller_stack_base + caller_stack_offset,
                                   STACK_GET_DOUBLE_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_STACK_STRING:
            caller_stack_offset = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_STRING_INDEX(rvm,
                                   caller_stack_base + caller_stack_offset,
                                   STACK_GET_STRING_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_STACK_CLASS_OB:
            caller_stack_offset = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_CLASS_OB_INDEX(rvm,
                                     caller_stack_base + caller_stack_offset,
                                     STACK_GET_CLASS_OB_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_STACK_ARRAY:
            caller_stack_offset = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            // shallow copy
            // array_value         = STACK_GET_ARRAY_OFFSET(rvm, -1);
            // deep copy
            array_value = rvm_deep_copy_array(rvm, STACK_GET_ARRAY_OFFSET(rvm, -1));
            STACK_SET_ARRAY_INDEX(rvm, caller_stack_base + caller_stack_offset, array_value);
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STACK_BOOL:
            caller_stack_offset = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_BOOL_OFFSET(rvm, 0,
                                  STACK_GET_BOOL_INDEX(rvm, caller_stack_base + caller_stack_offset));
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STACK_INT:
            caller_stack_offset = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_INT_OFFSET(rvm, 0,
                                 STACK_GET_INT_INDEX(rvm, caller_stack_base + caller_stack_offset));
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STACK_DOUBLE:
            caller_stack_offset = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_DOUBLE_OFFSET(rvm, 0,
                                    STACK_GET_DOUBLE_INDEX(rvm, caller_stack_base + caller_stack_offset));
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STACK_STRING:
            caller_stack_offset = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_STRING_OFFSET(rvm, 0,
                                    STACK_GET_STRING_INDEX(rvm, caller_stack_base + caller_stack_offset));
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STACK_CLASS_OB:
            caller_stack_offset = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_CLASS_OB_OFFSET(rvm, 0,
                                      STACK_GET_CLASS_OB_INDEX(rvm, caller_stack_base + caller_stack_offset));
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STACK_ARRAY:
            caller_stack_offset = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_ARRAY_OFFSET(rvm, 0,
                                   STACK_GET_ARRAY_INDEX(rvm, caller_stack_base + caller_stack_offset));
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;

        // array
        case RVM_CODE_PUSH_ARRAY_A:
            array_c = STACK_GET_ARRAY_OFFSET(rvm, -2);
            index   = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_get_array(rvm, array_c, index, &array_value);
            runtime_stack->top_index -= 2;
            STACK_SET_ARRAY_OFFSET(rvm, 0, array_value);
            runtime_stack->top_index++;
            rvm->pc += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_BOOL:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -2);
            index       = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_get_bool(rvm, array_value, index, &bool_value);
            runtime_stack->top_index -= 2;
            STACK_SET_BOOL_OFFSET(rvm, 0, (RVM_Bool)((int)bool_value));
            runtime_stack->top_index++;
            rvm->pc += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_INT:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -2);
            index       = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_get_int(rvm, array_value, index, &int_value);
            runtime_stack->top_index -= 2;
            STACK_SET_INT_OFFSET(rvm, 0, int_value);
            runtime_stack->top_index++;
            rvm->pc += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_DOUBLE:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -2);
            index       = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_get_double(rvm, array_value, index, &double_value);
            runtime_stack->top_index -= 2;
            STACK_SET_DOUBLE_OFFSET(rvm, 0, double_value);
            runtime_stack->top_index++;
            rvm->pc += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_STRING:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -2);
            index       = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_get_string(rvm, array_value, index, &string_value);
            runtime_stack->top_index -= 2;
            STACK_SET_STRING_OFFSET(rvm, 0, string_value);
            runtime_stack->top_index++;
            rvm->pc += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_CLASS_OBJECT:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -2);
            index       = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_get_class_object(rvm, array_value, index, &class_ob_value);
            runtime_stack->top_index -= 2;
            STACK_SET_CLASS_OB_OFFSET(rvm, 0, class_ob_value);
            runtime_stack->top_index++;
            rvm->pc += 1;
            break;

        case RVM_CODE_POP_ARRAY_BOOL:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -2);
            index       = STACK_GET_INT_OFFSET(rvm, -1);
            bool_value  = (bool)STACK_GET_BOOL_OFFSET(rvm, -3);
            rvm_array_set_bool(rvm, array_value, index, &bool_value);
            runtime_stack->top_index -= 3;
            rvm->pc += 1;
            break;
        case RVM_CODE_POP_ARRAY_INT:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -2);
            index       = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_set_int(rvm, array_value, index, &STACK_GET_INT_OFFSET(rvm, -3));
            runtime_stack->top_index -= 3;
            rvm->pc += 1;
            break;
        case RVM_CODE_POP_ARRAY_DOUBLE:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -2);
            index       = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_set_double(rvm, array_value, index, &STACK_GET_DOUBLE_OFFSET(rvm, -3));
            runtime_stack->top_index -= 3;
            rvm->pc += 1;
            break;
        case RVM_CODE_POP_ARRAY_STRING:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -2);
            index       = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_set_string(rvm, array_value, index, &STACK_GET_STRING_OFFSET(rvm, -3));
            runtime_stack->top_index -= 3;
            rvm->pc += 1;
            break;
        case RVM_CODE_POP_ARRAY_CLASS_OBJECT:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -2);
            index       = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_set_class_object(rvm, array_value, index, &STACK_GET_CLASS_OB_OFFSET(rvm, -3));
            runtime_stack->top_index -= 3;
            rvm->pc += 1;
            break;

        // array append
        case RVM_CODE_ARRAY_APPEND_BOOL:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -2);
            bool_value  = (bool)STACK_GET_BOOL_OFFSET(rvm, -1);
            rvm_array_append_bool(rvm, array_value, &bool_value);
            runtime_stack->top_index -= 2;
            rvm->pc += 1;
            break;
        case RVM_CODE_ARRAY_APPEND_INT:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -2);
            int_value   = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_append_int(rvm, array_value, &int_value);
            runtime_stack->top_index -= 2;
            rvm->pc += 1;
            break;
        case RVM_CODE_ARRAY_APPEND_DOUBLE:
            array_value  = STACK_GET_ARRAY_OFFSET(rvm, -2);
            double_value = STACK_GET_DOUBLE_OFFSET(rvm, -1);
            rvm_array_append_double(rvm, array_value, &double_value);
            runtime_stack->top_index -= 2;
            rvm->pc += 1;
            break;
        case RVM_CODE_ARRAY_APPEND_STRING:
            array_value  = STACK_GET_ARRAY_OFFSET(rvm, -2);
            string_value = STACK_GET_STRING_OFFSET(rvm, -1);
            rvm_array_append_string(rvm, array_value, &string_value);
            runtime_stack->top_index -= 2;
            rvm->pc += 1;
            break;
        case RVM_CODE_ARRAY_APPEND_CLASS_OBJECT:
            array_value    = STACK_GET_ARRAY_OFFSET(rvm, -2);
            class_ob_value = STACK_GET_CLASS_OB_OFFSET(rvm, -1);
            rvm_array_append_class_object(rvm, array_value, &class_ob_value);
            runtime_stack->top_index -= 2;
            rvm->pc += 1;
            break;

        // array pop
        case RVM_CODE_ARRAY_POP_BOOL:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -1);
            bool_value  = false;
            rvm_array_pop_bool(rvm, array_value, &bool_value);
            runtime_stack->top_index -= 1;
            STACK_SET_BOOL_OFFSET(rvm, 0, (RVM_Bool)bool_value);
            runtime_stack->top_index += 1;
            rvm->pc += 1;
            break;
        case RVM_CODE_ARRAY_POP_INT:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -1);
            int_value   = 0;
            rvm_array_pop_int(rvm, array_value, &int_value);
            runtime_stack->top_index -= 1;
            STACK_SET_INT_OFFSET(rvm, 0, int_value);
            runtime_stack->top_index += 1;
            rvm->pc += 1;
            break;
        case RVM_CODE_ARRAY_POP_DOUBLE:
            array_value  = STACK_GET_ARRAY_OFFSET(rvm, -1);
            double_value = false;
            rvm_array_pop_double(rvm, array_value, &double_value);
            runtime_stack->top_index -= 1;
            STACK_SET_DOUBLE_OFFSET(rvm, 0, double_value);
            runtime_stack->top_index += 1;
            rvm->pc += 1;
            break;
        case RVM_CODE_ARRAY_POP_STRING:
            array_value  = STACK_GET_ARRAY_OFFSET(rvm, -1);
            string_value = nullptr;
            rvm_array_pop_string(rvm, array_value, &string_value);
            runtime_stack->top_index -= 1;
            STACK_SET_STRING_OFFSET(rvm, 0, string_value);
            runtime_stack->top_index += 1;
            rvm->pc += 1;
            break;
        case RVM_CODE_ARRAY_POP_CLASS_OBJECT:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -1);
            rvm_array_pop_class_object(rvm, array_value, &class_ob_value);
            runtime_stack->top_index -= 1;
            STACK_SET_CLASS_OB_OFFSET(rvm, 0, class_ob_value);
            runtime_stack->top_index += 1;
            rvm->pc += 1;
            break;


        // class
        case RVM_CODE_POP_FIELD_BOOL:
            class_ob_value                                  = STACK_GET_CLASS_OB_OFFSET(rvm, -1);
            field_index                                     = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            class_ob_value->field[field_index].type         = RVM_VALUE_TYPE_BOOL;
            class_ob_value->field[field_index].u.bool_value = STACK_GET_BOOL_OFFSET(rvm, -2);
            runtime_stack->top_index -= 2;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_FIELD_INT:
            class_ob_value                                 = STACK_GET_CLASS_OB_OFFSET(rvm, -1);
            field_index                                    = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            class_ob_value->field[field_index].type        = RVM_VALUE_TYPE_INT;
            class_ob_value->field[field_index].u.int_value = STACK_GET_INT_OFFSET(rvm, -2);
            runtime_stack->top_index -= 2;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_FIELD_DOUBLE:
            class_ob_value                                    = STACK_GET_CLASS_OB_OFFSET(rvm, -1);
            field_index                                       = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            class_ob_value->field[field_index].type           = RVM_VALUE_TYPE_DOUBLE;
            class_ob_value->field[field_index].u.double_value = STACK_GET_DOUBLE_OFFSET(rvm, -2);
            runtime_stack->top_index -= 2;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_FIELD_STRING:
            class_ob_value                                    = STACK_GET_CLASS_OB_OFFSET(rvm, -1);
            field_index                                       = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            class_ob_value->field[field_index].type           = RVM_VALUE_TYPE_STRING;
            class_ob_value->field[field_index].u.string_value = STACK_GET_STRING_OFFSET(rvm, -2);
            runtime_stack->top_index -= 2;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_FIELD_CLASS_OB:
            class_ob_value                                      = STACK_GET_CLASS_OB_OFFSET(rvm, -1);
            field_index                                         = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            class_ob_value->field[field_index].type             = RVM_VALUE_TYPE_CLASS_OB;
            class_ob_value->field[field_index].u.class_ob_value = STACK_GET_CLASS_OB_OFFSET(rvm, -2);
            runtime_stack->top_index -= 2;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_FIELD_ARRAY:
            class_ob_value                                   = STACK_GET_CLASS_OB_OFFSET(rvm, -1);
            field_index                                      = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            class_ob_value->field[field_index].type          = RVM_VALUE_TYPE_ARRAY;
            class_ob_value->field[field_index].u.array_value = STACK_GET_ARRAY_OFFSET(rvm, -2);
            runtime_stack->top_index -= 2;
            rvm->pc += 3;
            break;

        case RVM_CODE_PUSH_FIELD_BOOL:
            class_ob_value = STACK_GET_CLASS_OB_OFFSET(rvm, -1);
            field_index    = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_BOOL_OFFSET(rvm, -1, class_ob_value->field[field_index].u.bool_value);
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_FIELD_INT:
            class_ob_value = STACK_GET_CLASS_OB_OFFSET(rvm, -1);
            field_index    = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_INT_OFFSET(rvm, -1, class_ob_value->field[field_index].u.int_value);
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_FIELD_DOUBLE:
            class_ob_value = STACK_GET_CLASS_OB_OFFSET(rvm, -1);
            field_index    = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_DOUBLE_OFFSET(rvm, -1, class_ob_value->field[field_index].u.double_value);
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_FIELD_STRING:
            class_ob_value = STACK_GET_CLASS_OB_OFFSET(rvm, -1);
            field_index    = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_STRING_OFFSET(rvm, -1, class_ob_value->field[field_index].u.string_value);
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_FIELD_CLASS_OB:
            class_ob_value = STACK_GET_CLASS_OB_OFFSET(rvm, -1);
            field_index    = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_CLASS_OB_OFFSET(rvm, -1, class_ob_value->field[field_index].u.class_ob_value);
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_FIELD_ARRAY:
            class_ob_value = STACK_GET_CLASS_OB_OFFSET(rvm, -1);
            field_index    = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_ARRAY_OFFSET(rvm, -1, class_ob_value->field[field_index].u.array_value);
            rvm->pc += 3;
            break;

        // arithmetic
        case RVM_CODE_ADD_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = STACK_GET_INT_OFFSET(rvm, -2) + STACK_GET_INT_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_ADD_DOUBLE:
            STACK_GET_DOUBLE_OFFSET(rvm, -2) = STACK_GET_DOUBLE_OFFSET(rvm, -2) + STACK_GET_DOUBLE_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_SUB_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = STACK_GET_INT_OFFSET(rvm, -2) - STACK_GET_INT_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_SUB_DOUBLE:
            STACK_GET_DOUBLE_OFFSET(rvm, -2) = STACK_GET_DOUBLE_OFFSET(rvm, -2) - STACK_GET_DOUBLE_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_MUL_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = STACK_GET_INT_OFFSET(rvm, -2) * STACK_GET_INT_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_MUL_DOUBLE:
            STACK_GET_DOUBLE_OFFSET(rvm, -2) = STACK_GET_DOUBLE_OFFSET(rvm, -2) * STACK_GET_DOUBLE_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_DIV_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = STACK_GET_INT_OFFSET(rvm, -2) / STACK_GET_INT_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_DIV_DOUBLE:
            STACK_GET_DOUBLE_OFFSET(rvm, -2) = STACK_GET_DOUBLE_OFFSET(rvm, -2) / STACK_GET_DOUBLE_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_MOD_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = STACK_GET_INT_OFFSET(rvm, -2) % STACK_GET_INT_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_MOD_DOUBLE:
            STACK_GET_DOUBLE_OFFSET(rvm, -2) = fmod(STACK_GET_DOUBLE_OFFSET(rvm, -2), STACK_GET_DOUBLE_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_MINUS_INT:
            STACK_GET_INT_OFFSET(rvm, -1) = -STACK_GET_INT_OFFSET(rvm, -1);
            rvm->pc++;
            break;
        case RVM_CODE_MINUS_DOUBLE:
            STACK_GET_DOUBLE_OFFSET(rvm, -1) = -STACK_GET_DOUBLE_OFFSET(rvm, -1);
            rvm->pc++;
            break;
        case RVM_CODE_SELF_INCREASE:
            STACK_GET_INT_OFFSET(rvm, -1) += 1;
            rvm->pc++;
            break;
        case RVM_CODE_SELF_DECREASE:
            STACK_GET_INT_OFFSET(rvm, -1) -= 1;
            rvm->pc++;
            break;
        case RVM_CODE_CONCAT:
            string_value = concat_string(rvm, STACK_GET_STRING_OFFSET(rvm, -2), STACK_GET_STRING_OFFSET(rvm, -1));
            STACK_SET_STRING_OFFSET(rvm, -2, string_value);
            runtime_stack->top_index--;
            rvm->pc++;
            break;

        // type cast
        case RVM_CODE_CAST_BOOL_TO_INT:
            STACK_SET_INT_OFFSET(rvm, -1, STACK_GET_BOOL_OFFSET(rvm, -1));
            rvm->pc++;
            break;
        case RVM_CODE_CAST_INT_TO_DOUBLE:
            STACK_SET_DOUBLE_OFFSET(rvm, -1, STACK_GET_INT_OFFSET(rvm, -1));
            rvm->pc++;
            break;
        case RVM_CODE_CAST_INT_TO_BOOL:
            STACK_SET_BOOL_OFFSET(rvm, -1, (RVM_Bool)STACK_GET_INT_OFFSET(rvm, -1));
            rvm->pc++;
            break;
        case RVM_CODE_CAST_DOUBLE_TO_INT:
            STACK_SET_INT_OFFSET(rvm, -1, (int)STACK_GET_DOUBLE_OFFSET(rvm, -1));
            rvm->pc++;
            break;

        // logical
        case RVM_CODE_LOGICAL_AND:
            STACK_GET_INT_OFFSET(rvm, -2) = (STACK_GET_INT_OFFSET(rvm, -2) && STACK_GET_INT_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_LOGICAL_OR:
            STACK_GET_INT_OFFSET(rvm, -2) = (STACK_GET_INT_OFFSET(rvm, -2) || STACK_GET_INT_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_LOGICAL_NOT:
            STACK_GET_INT_OFFSET(rvm, -1) = !(STACK_GET_INT_OFFSET(rvm, -1));
            rvm->pc++;
            break;

        // relational
        case RVM_CODE_RELATIONAL_EQ_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = (STACK_GET_INT_OFFSET(rvm, -2) == STACK_GET_INT_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_RELATIONAL_EQ_DOUBLE:
            STACK_GET_INT_OFFSET(rvm, -2) = (STACK_GET_DOUBLE_OFFSET(rvm, -2) == STACK_GET_DOUBLE_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_RELATIONAL_EQ_STRING:
            STACK_GET_BOOL_OFFSET(rvm, -2) = (RVM_Bool)(rvm_string_cmp(STACK_GET_STRING_OFFSET(rvm, -2), STACK_GET_STRING_OFFSET(rvm, -1)) == 0);
            runtime_stack->top_index--;
            rvm->pc++;
            break;

        case RVM_CODE_RELATIONAL_NE_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = (STACK_GET_INT_OFFSET(rvm, -2) != STACK_GET_INT_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_RELATIONAL_NE_DOUBLE:
            STACK_GET_INT_OFFSET(rvm, -2) = (STACK_GET_DOUBLE_OFFSET(rvm, -2) != STACK_GET_DOUBLE_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_RELATIONAL_NE_STRING:
            STACK_GET_BOOL_OFFSET(rvm, -2) = (RVM_Bool)(rvm_string_cmp(STACK_GET_STRING_OFFSET(rvm, -2), STACK_GET_STRING_OFFSET(rvm, -1)) != 0);
            runtime_stack->top_index--;
            rvm->pc++;
            break;

        case RVM_CODE_RELATIONAL_GT_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = (STACK_GET_INT_OFFSET(rvm, -2) > STACK_GET_INT_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_RELATIONAL_GT_DOUBLE:
            STACK_GET_INT_OFFSET(rvm, -2) = (STACK_GET_DOUBLE_OFFSET(rvm, -2) > STACK_GET_DOUBLE_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_RELATIONAL_GT_STRING:
            STACK_GET_INT_OFFSET(rvm, -2) = (rvm_string_cmp(STACK_GET_STRING_OFFSET(rvm, -2), STACK_GET_STRING_OFFSET(rvm, -1)) > 0);
            runtime_stack->top_index--;
            rvm->pc++;
            break;

        case RVM_CODE_RELATIONAL_GE_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = (STACK_GET_INT_OFFSET(rvm, -2) >= STACK_GET_INT_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_RELATIONAL_GE_DOUBLE:
            STACK_GET_INT_OFFSET(rvm, -2) = (STACK_GET_DOUBLE_OFFSET(rvm, -2) >= STACK_GET_DOUBLE_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_RELATIONAL_GE_STRING:
            STACK_GET_INT_OFFSET(rvm, -2) = (rvm_string_cmp(STACK_GET_STRING_OFFSET(rvm, -2), STACK_GET_STRING_OFFSET(rvm, -1)) >= 0);
            runtime_stack->top_index--;
            rvm->pc++;
            break;

        case RVM_CODE_RELATIONAL_LT_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = (STACK_GET_INT_OFFSET(rvm, -2) < STACK_GET_INT_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_RELATIONAL_LT_DOUBLE:
            STACK_GET_INT_OFFSET(rvm, -2) = (STACK_GET_DOUBLE_OFFSET(rvm, -2) < STACK_GET_DOUBLE_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_RELATIONAL_LT_STRING:
            STACK_GET_INT_OFFSET(rvm, -2) = (rvm_string_cmp(STACK_GET_STRING_OFFSET(rvm, -2), STACK_GET_STRING_OFFSET(rvm, -1)) < 0);
            runtime_stack->top_index--;
            rvm->pc++;
            break;

        case RVM_CODE_RELATIONAL_LE_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = (STACK_GET_INT_OFFSET(rvm, -2) <= STACK_GET_INT_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_RELATIONAL_LE_DOUBLE:
            STACK_GET_INT_OFFSET(rvm, -2) = (STACK_GET_DOUBLE_OFFSET(rvm, -2) <= STACK_GET_DOUBLE_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        case RVM_CODE_RELATIONAL_LE_STRING:
            STACK_GET_INT_OFFSET(rvm, -2) = (rvm_string_cmp(STACK_GET_STRING_OFFSET(rvm, -2), STACK_GET_STRING_OFFSET(rvm, -1)) <= 0);
            runtime_stack->top_index--;
            rvm->pc++;
            break;

        // jump
        case RVM_CODE_JUMP:
            rvm->pc = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            break;
        case RVM_CODE_JUMP_IF_FALSE:
            if (!STACK_GET_INT_OFFSET(rvm, -1)) {
                rvm->pc = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            } else {
                rvm->pc += 3;
            }
            runtime_stack->top_index--;
            break;
        case RVM_CODE_JUMP_IF_TRUE:
            if (STACK_GET_INT_OFFSET(rvm, -1)) {
                rvm->pc = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            } else {
                rvm->pc += 3;
            }
            runtime_stack->top_index--;
            break;

        // duplicate
        case RVM_CODE_DUPLICATE: {
            unsigned int dst_offset = OPCODE_GET_1BYTE(&code_list[rvm->pc + 1]);
            unsigned int src_offset = OPCODE_GET_1BYTE(&code_list[rvm->pc + 2]);
            STACK_COPY_OFFSET(rvm, -dst_offset, -src_offset);
            runtime_stack->top_index++;
            rvm->pc += 3;
        } break;

        // func
        case RVM_CODE_PUSH_FUNC:
            // 这里设计的不太好
            func_index = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_INT_OFFSET(rvm, 0, func_index);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_METHOD:
            method_index = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_INT_OFFSET(rvm, 0, method_index);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_ARGUMENT_NUM:
            argument_list_size = OPCODE_GET_1BYTE(&code_list[rvm->pc + 1]);
            rvm->pc += 2;
            break;
        case RVM_CODE_INVOKE_FUNC:
            oper_num = STACK_GET_INT_OFFSET(rvm, -1);
            // TODO: 这里是不是直接放在字节码里比较好, 不放在 runtime_stack中
            package_index = oper_num >> 8;
            func_index    = oper_num & 0XFF;

            runtime_stack->top_index--;
            if (rvm->executer_entry->package_executer_list[package_index]->function_list[func_index].type == RVM_FUNCTION_TYPE_NATIVE) {
                invoke_native_function(rvm,
                                       &rvm->executer_entry->package_executer_list[package_index]->function_list[func_index],
                                       argument_list_size);
                rvm->pc += 1;
            } else if (rvm->executer_entry->package_executer_list[package_index]->function_list[func_index].type == RVM_FUNCTION_TYPE_DERIVE) {
                invoke_derive_function(rvm,
                                       &function,
                                       nullptr, &rvm->executer_entry->package_executer_list[package_index]->function_list[func_index],
                                       &code_list, &code_size,
                                       &rvm->pc,
                                       &caller_stack_base);
            }
            break;
        case RVM_CODE_INVOKE_METHOD:
            method_index   = STACK_GET_INT_OFFSET(rvm, -1);
            class_ob_value = STACK_GET_CLASS_OB_OFFSET(rvm, -2);
            runtime_stack->top_index -= 2;
            // 每个对象的成员变量 是单独存储的
            // 但是 method 没必要单独存储, 在 class_definition 中就可以, 通过指针寻找 class_definition
            // 需要将 class_object 赋值给 self 变量
            // TODO: 但是这里, gc会释放么, 让 invoke_derive_function变得不合法
            method = &(class_ob_value->class_ref->method_list[method_index]);
            invoke_derive_function(rvm,
                                   &function,
                                   class_ob_value, method->rvm_function,
                                   &code_list, &code_size,
                                   &rvm->pc,
                                   &caller_stack_base);
            break;
        case RVM_CODE_RETURN:
            return_value_list_size = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            rvm->pc += 3;
            [[fallthrough]];
        case RVM_CODE_FUNCTION_FINISH:
            derive_function_finish(rvm,
                                   &function, nullptr,
                                   &code_list, &code_size,
                                   &rvm->pc, &caller_stack_base, return_value_list_size);
            rvm->pc += 1;
            return_value_list_size = 0;
            break;

        case RVM_CODE_EXIT:
            oper_num = OPCODE_GET_1BYTE(&code_list[rvm->pc + 1]);
            exit(oper_num);
            break;

        // array
        case RVM_CODE_NEW_ARRAY_BOOL:
            dimension = OPCODE_GET_1BYTE(&code_list[rvm->pc + 1]);
            memset(dimension_list, 0, sizeof(unsigned int) * MAX_DIMENSION_NUM);
            for (unsigned int i = 0; i < dimension; i++) {
                dimension_list[dimension - 1 - i] = STACK_GET_INT_OFFSET(rvm, -(i + 1));
            }
            runtime_stack->top_index -= dimension;
            array_value = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_BOOL, nullptr);
            STACK_SET_ARRAY_OFFSET(rvm, 0, array_value);
            runtime_stack->top_index++;
            rvm->pc += 2;
            break;
        case RVM_CODE_NEW_ARRAY_INT:
            dimension = OPCODE_GET_1BYTE(&code_list[rvm->pc + 1]);
            memset(dimension_list, 0, sizeof(unsigned int) * MAX_DIMENSION_NUM);
            for (unsigned int i = 0; i < dimension; i++) {
                dimension_list[dimension - 1 - i] = STACK_GET_INT_OFFSET(rvm, -(i + 1));
            }
            runtime_stack->top_index -= dimension;
            array_value = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_INT, nullptr);
            STACK_SET_ARRAY_OFFSET(rvm, 0, array_value);
            runtime_stack->top_index++;
            rvm->pc += 2;
            break;
        case RVM_CODE_NEW_ARRAY_DOUBLE:
            dimension = OPCODE_GET_1BYTE(&code_list[rvm->pc + 1]);
            memset(dimension_list, 0, sizeof(unsigned int) * MAX_DIMENSION_NUM);
            for (unsigned int i = 0; i < dimension; i++) {
                dimension_list[dimension - 1 - i] = STACK_GET_INT_OFFSET(rvm, -(i + 1));
            }
            runtime_stack->top_index -= dimension;
            array_value = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_DOUBLE, nullptr);
            STACK_SET_ARRAY_OFFSET(rvm, 0, array_value);
            runtime_stack->top_index++;
            rvm->pc += 2;
            break;
        case RVM_CODE_NEW_ARRAY_STRING:
            dimension = OPCODE_GET_1BYTE(&code_list[rvm->pc + 1]);
            memset(dimension_list, 0, sizeof(unsigned int) * MAX_DIMENSION_NUM);
            for (unsigned int i = 0; i < dimension; i++) {
                dimension_list[dimension - 1 - i] = STACK_GET_INT_OFFSET(rvm, -(i + 1));
            }
            runtime_stack->top_index -= dimension;
            array_value = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_STRING, nullptr);
            STACK_SET_ARRAY_OFFSET(rvm, 0, array_value);
            runtime_stack->top_index++;
            rvm->pc += 2;
            break;
        case RVM_CODE_NEW_ARRAY_CLASS_OBJECT:
            dimension = OPCODE_GET_1BYTE(&code_list[rvm->pc + 1]);
            memset(dimension_list, 0, sizeof(unsigned int) * MAX_DIMENSION_NUM);
            for (unsigned int i = 0; i < dimension; i++) {
                dimension_list[dimension - 1 - i] = STACK_GET_INT_OFFSET(rvm, -(i + 1));
            }
            runtime_stack->top_index -= dimension;

            class_index          = OPCODE_GET_1BYTE(&code_list[rvm->pc + 2]);
            rvm_class_definition = &(rvm->class_list[class_index]);

            array_value          = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_CLASS_OBJECT, rvm_class_definition);
            STACK_SET_ARRAY_OFFSET(rvm, 0, array_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_NEW_ARRAY_LITERAL_BOOL:
            array_size  = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            array_value = rvm_new_array_literal_bool(rvm, array_size);
            runtime_stack->top_index -= array_size;
            STACK_SET_ARRAY_OFFSET(rvm, 0, array_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_NEW_ARRAY_LITERAL_INT:
            array_size  = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            array_value = rvm_new_array_literal_int(rvm, array_size);
            runtime_stack->top_index -= array_size;
            STACK_SET_ARRAY_OFFSET(rvm, 0, array_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_NEW_ARRAY_LITERAL_DOUBLE:
            array_size  = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            array_value = rvm_new_array_literal_double(rvm, array_size);
            runtime_stack->top_index -= array_size;
            STACK_SET_ARRAY_OFFSET(rvm, 0, array_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_NEW_ARRAY_LITERAL_STRING:
            array_size  = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            array_value = rvm_new_array_literal_string(rvm, array_size);
            runtime_stack->top_index -= array_size;
            STACK_SET_ARRAY_OFFSET(rvm, 0, array_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_NEW_ARRAY_LITERAL_CLASS_OBJECT:
            class_index          = OPCODE_GET_1BYTE(&code_list[rvm->pc + 1]);
            rvm_class_definition = &(rvm->class_list[class_index]);
            array_size           = OPCODE_GET_2BYTE(&code_list[rvm->pc + 2]);
            array_value          = rvm_new_array_literal_class_object(rvm, array_size, rvm_class_definition);
            runtime_stack->top_index -= array_size;
            STACK_SET_ARRAY_OFFSET(rvm, 0, array_value);
            runtime_stack->top_index++;
            rvm->pc += 4;
            break;
        case RVM_CODE_NEW_ARRAY_LITERAL_A:
            dimension   = OPCODE_GET_1BYTE(&code_list[rvm->pc + 1]);
            array_size  = OPCODE_GET_2BYTE(&code_list[rvm->pc + 2]);
            array_value = rvm_new_array_literal_a(rvm, dimension, array_size);
            runtime_stack->top_index -= array_size;
            STACK_SET_ARRAY_OFFSET(rvm, 0, array_value);
            runtime_stack->top_index++;
            rvm->pc += 4;
            break;

        case RVM_CODE_PUSH_ARRAY_LEN:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -1);
            rvm_array_get_length(rvm, array_value, &int_value);
            runtime_stack->top_index -= 1;
            STACK_SET_INT_OFFSET(rvm, 0, int_value);
            runtime_stack->top_index += 1;
            rvm->pc += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_CAPACITY:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -1);
            rvm_array_get_capacity(rvm, array_value, &int_value);
            runtime_stack->top_index -= 1;
            STACK_SET_INT_OFFSET(rvm, 0, int_value);
            runtime_stack->top_index += 1;
            rvm->pc += 1;
            break;
        case RVM_CODE_PUSH_STRING_LEN:
            string_value = STACK_GET_STRING_OFFSET(rvm, -1);
            rvm_string_get_length(rvm, string_value, &int_value);
            runtime_stack->top_index -= 1;
            STACK_SET_INT_OFFSET(rvm, 0, int_value);
            runtime_stack->top_index += 1;
            rvm->pc += 1;
            break;
        case RVM_CODE_PUSH_STRING_CAPACITY:
            string_value = STACK_GET_STRING_OFFSET(rvm, -1);
            rvm_string_get_capacity(rvm, string_value, &int_value);
            runtime_stack->top_index -= 1;
            STACK_SET_INT_OFFSET(rvm, 0, int_value);
            runtime_stack->top_index += 1;
            rvm->pc += 1;
            break;

            // class
        case RVM_CODE_NEW_CLASS_OBJECT_LITERAL:
            class_index          = OPCODE_GET_1BYTE(&code_list[rvm->pc + 1]);
            rvm_class_definition = &(rvm->class_list[class_index]);

            class_ob_value       = rvm_new_class_object(rvm, rvm_class_definition);
            STACK_SET_CLASS_OB_OFFSET(rvm, 0, class_ob_value);
            runtime_stack->top_index++;
            rvm->pc += 2;
            break;

        // range
        case RVM_CODE_FOR_RANGE_ARRAY_BOOL:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -2);
            index       = STACK_GET_INT_OFFSET(rvm, -1);
            error_code  = rvm_array_get_bool(rvm, array_value, index, &bool_value);
            if (error_code == RUNTIME_ERR_OUT_OF_ARRAY_RANGE) {
                rvm->pc = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
                break;
            }
            // runtime_stack->top_index -= 2; // 与 RVM_CODE_PUSH_ARRAY_BOOL 的不同点 区别
            STACK_SET_BOOL_OFFSET(rvm, 0, (RVM_Bool)((int)bool_value));
            runtime_stack->top_index++;
            rvm->pc += 3;

            // iter ++
            STACK_GET_INT_OFFSET(rvm, -2)
            ++;
            break;
        case RVM_CODE_FOR_RANGE_ARRAY_INT:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -2);
            index       = STACK_GET_INT_OFFSET(rvm, -1);
            error_code  = rvm_array_get_int(rvm, array_value, index, &int_value);
            if (error_code == RUNTIME_ERR_OUT_OF_ARRAY_RANGE) {
                rvm->pc = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
                break;
            }
            // runtime_stack->top_index -= 2; // 与 RVM_CODE_PUSH_ARRAY_INT 的不同点 区别
            STACK_SET_INT_OFFSET(rvm, 0, int_value);
            runtime_stack->top_index++;
            rvm->pc += 3;

            // iter ++
            STACK_GET_INT_OFFSET(rvm, -2)
            ++;
            break;
        case RVM_CODE_FOR_RANGE_ARRAY_DOUBLE:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -2);
            index       = STACK_GET_INT_OFFSET(rvm, -1);
            error_code  = rvm_array_get_double(rvm, array_value, index, &double_value);
            if (error_code == RUNTIME_ERR_OUT_OF_ARRAY_RANGE) {
                rvm->pc = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
                break;
            }
            // runtime_stack->top_index -= 2; // 与 RVM_CODE_PUSH_ARRAY_DOUBLE 的不同点 区别
            STACK_SET_DOUBLE_OFFSET(rvm, 0, double_value);
            runtime_stack->top_index++;
            rvm->pc += 3;

            // iter ++
            STACK_GET_INT_OFFSET(rvm, -2) += 1;
            break;
        case RVM_CODE_FOR_RANGE_ARRAY_STRING:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -2);
            index       = STACK_GET_INT_OFFSET(rvm, -1);
            error_code  = rvm_array_get_string(rvm, array_value, index, &string_value);
            if (error_code == RUNTIME_ERR_OUT_OF_ARRAY_RANGE) {
                rvm->pc = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
                break;
            }
            // runtime_stack->top_index -= 2; // 与 RVM_CODE_PUSH_ARRAY_STRING 的不同点 区别
            STACK_SET_STRING_OFFSET(rvm, 0, string_value);
            runtime_stack->top_index++;
            rvm->pc += 3;

            // iter ++
            STACK_GET_INT_OFFSET(rvm, -2) += 1;
            break;
        case RVM_CODE_FOR_RANGE_ARRAY_CLASS_OBJECT:
            array_value = STACK_GET_ARRAY_OFFSET(rvm, -2);
            index       = STACK_GET_INT_OFFSET(rvm, -1);
            error_code  = rvm_array_get_class_object(rvm, array_value, index, &class_ob_value);
            if (error_code == RUNTIME_ERR_OUT_OF_ARRAY_RANGE) {
                rvm->pc = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
                break;
            }
            // runtime_stack->top_index -= 2; // 与 RVM_CODE_PUSH_ARRAY_OBJECT 的不同点 区别
            STACK_SET_CLASS_OB_OFFSET(rvm, 0, class_ob_value);
            runtime_stack->top_index++;
            rvm->pc += 3;

            // iter ++
            STACK_GET_INT_OFFSET(rvm, -2) += 1;
            break;
        case RVM_CODE_FOR_RANGE_STRING:
            break;
        case RVM_CODE_FOR_RANGE_FINISH:
            runtime_stack->top_index -= 2;
            rvm->pc += 3;
            break;


        // convert
        case RVM_CODE_BOOL_2_STRING:
            bool_value   = STACK_GET_BOOL_OFFSET(rvm, -1);
            string_value = rvm_bool_2_string(rvm, bool_value);
            STACK_SET_STRING_OFFSET(rvm, -1, string_value);
            rvm->pc += 1;
            break;
        case RVM_CODE_INT_2_STRING:
            int_value    = STACK_GET_INT_OFFSET(rvm, -1);
            string_value = rvm_int_2_string(rvm, int_value);
            STACK_SET_STRING_OFFSET(rvm, -1, string_value);
            rvm->pc += 1;
            break;
        case RVM_CODE_DOUBLE_2_STRING:
            double_value = STACK_GET_DOUBLE_OFFSET(rvm, -1);
            string_value = rvm_double_2_string(rvm, double_value);
            STACK_SET_STRING_OFFSET(rvm, -1, string_value);
            rvm->pc += 1;
            break;

        default:
            ring_error_report("execute error:invalid opcode(%d), pc(%d)\n",
                              opcode, rvm->pc);
            break;
        }
    }

#ifdef DEBUG_RVM_INTERACTIVE
    debug_rvm(rvm, function, code_list, code_size, rvm->pc, caller_stack_base);
#endif

    destory_mem_pool(rvm->meta_pool);
    destory_mem_pool(rvm->data_pool);
    free(dimension_list);
}


void invoke_native_function(Ring_VirtualMachine* rvm,
                            RVM_Function*        function,
                            unsigned int         argument_list_size) {

    RVM_Value           ret;

    int                 return_list_count = function->u.native_func->return_list_count;
    RVM_NativeFuncProc* native_func_proc  = function->u.native_func->func_proc;
    RVM_Value*          args              = nullptr;

    args                                  = &rvm->runtime_stack->data[rvm->runtime_stack->top_index - argument_list_size];

    ret                                   = native_func_proc(rvm, argument_list_size, args);


    // 销毁 argument
    rvm->runtime_stack->top_index -= argument_list_size;

    // TODO: 需要补齐一个 return 指令
    // TODO: 如何在这里处理 return 多返回值的问题
    if (return_list_count == 0) {
    } else if (return_list_count == 1) {
        rvm->runtime_stack->data[rvm->runtime_stack->top_index++] = ret;
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
 */
void invoke_derive_function(Ring_VirtualMachine* rvm,
                            RVM_Function**       caller_function,
                            RVM_ClassObject* callee_object, RVM_Function* callee_function,
                            RVM_Byte** code_list, unsigned int* code_size,
                            unsigned int* pc,
                            unsigned int* caller_stack_base) {

    RVM_CallInfo* callinfo         = (RVM_CallInfo*)mem_alloc(rvm->meta_pool, sizeof(RVM_CallInfo));
    callinfo->magic_number         = CALL_INFO_MAGIC_NUMBER;
    callinfo->caller_function      = *caller_function;
    callinfo->caller_pc            = *pc;
    callinfo->caller_stack_base    = *caller_stack_base;
    callinfo->callee_object        = callee_object;
    callinfo->callee_function      = callee_function;
    callinfo->callee_argument_size = callee_function->parameter_size;
    callinfo->prev                 = nullptr;
    callinfo->next                 = nullptr;
    store_callinfo(rvm, callinfo);

    // 上下文切换
    *caller_function   = callee_function;
    *code_list         = callee_function->u.derive_func->code_list;
    *code_size         = callee_function->u.derive_func->code_size;
    *pc                = 0;
    *caller_stack_base = rvm->runtime_stack->top_index;


    init_derive_function_local_variable(rvm, callee_object, callee_function);

    unsigned int local_variable_size = callee_function->local_variable_size;
    rvm->runtime_stack->top_index += local_variable_size;
}

void derive_function_return(Ring_VirtualMachine* rvm,
                            RVM_Function** caller_function, RVM_Function* callee_function,
                            RVM_Byte** code_list, unsigned int* code_size,
                            unsigned int* pc,
                            unsigned int* caller_stack_base,
                            unsigned int  return_list_size) {
    debug_exec_info_with_white("\t");
}

/*
 * derive_function_finish
 *
 * 1. restore call info
 *      call info: caller_pc
 * 3. change vm code to callee
 * 4. change pc
 *
 * */
void derive_function_finish(Ring_VirtualMachine* rvm,
                            RVM_Function** caller_function, RVM_Function* callee_function,
                            RVM_Byte** code_list, unsigned int* code_size,
                            unsigned int* pc,
                            unsigned int* caller_stack_base,
                            unsigned int  return_value_list_size) {

    unsigned int old_return_value_list_index;

    rvm->runtime_stack->top_index -= return_value_list_size;
    old_return_value_list_index       = rvm->runtime_stack->top_index;


    RVM_CallInfo* callinfo            = nullptr;
    unsigned int  local_variable_size = (*caller_function)->local_variable_size;
    rvm->runtime_stack->top_index -= local_variable_size;

    restore_callinfo(rvm, &callinfo);
    assert(callinfo->magic_number == CALL_INFO_MAGIC_NUMBER);

    *caller_function   = callinfo->caller_function;
    *pc                = callinfo->caller_pc; // 调用完成之后, caller_pc + 1, 在 execute 中统一update
    *caller_stack_base = callinfo->caller_stack_base;
    if (*caller_function == nullptr) {
        *code_list = rvm->executer->code_list;
        *code_size = rvm->executer->code_size;
    } else {
        *code_list = (*caller_function)->u.derive_func->code_list;
        *code_size = (*caller_function)->u.derive_func->code_size;
    }

    // 释放arguement
    rvm->runtime_stack->top_index -= callinfo->callee_argument_size;


    // copy return value to top of stack.
    for (unsigned int i = 0; i < return_value_list_size; i++) {
        rvm->runtime_stack->data[rvm->runtime_stack->top_index++] = rvm->runtime_stack->data[old_return_value_list_index + i];
    }
}

/*
 * storage callinfo when invoke function
 *
 * 1. Encode callinfo
 * 2. Push to runtime_stack
 *
 */
void store_callinfo(Ring_VirtualMachine* rvm, RVM_CallInfo* call_info) {
    // TODO: 这里有点兼容逻辑, 需要吧 CALL_INFO_SIZE_V2 去掉
    rvm->runtime_stack->top_index += CALL_INFO_SIZE_V2;

    if (rvm->call_info == nullptr) {
        rvm->call_info = call_info;
        return;
    }

    call_info->next      = rvm->call_info;
    rvm->call_info->prev = call_info;

    rvm->call_info       = call_info;
}

/*
 * restore callinfo when function finish
 *
 * 1. Pop from runtime_stack
 * 2. Decode callinfo
 *
 */
void restore_callinfo(Ring_VirtualMachine* rvm, RVM_CallInfo** call_info) {
    // TODO: 这里有点兼容逻辑, 需要吧 CALL_INFO_SIZE_V2 去掉
    rvm->runtime_stack->top_index -= CALL_INFO_SIZE_V2;

    assert(rvm->call_info != nullptr);

    RVM_CallInfo* head = rvm->call_info;

    rvm->call_info     = head->next;
    if (rvm->call_info != nullptr) {
        rvm->call_info->prev = nullptr;
    }

    head->next = nullptr;
    head->prev = nullptr;
    *call_info = head;
}

/*
 * callee_class_object 是 callee_function的 所属对象
 *
 * FIXME: 初始化局部变量列表的时候存在问题
 * FIXME: 如果局部变量是个数组
 */
void init_derive_function_local_variable(Ring_VirtualMachine* rvm,
                                         RVM_ClassObject*     callee_object,
                                         RVM_Function*        function) {

    unsigned int arguement_list_size  = function->parameter_size;
    unsigned int arguement_list_index = rvm->runtime_stack->top_index - CALL_INFO_SIZE_V2 - arguement_list_size;
    // TODO: 这里有点兼容逻辑, 需要把 CALL_INFO_SIZE_V2 去掉

    unsigned int local_variable_offset = 0;

    // Step-1: 初始化 self 变量
    if (callee_object != nullptr) {
        rvm->runtime_stack->data[rvm->runtime_stack->top_index + 0].type             = RVM_VALUE_TYPE_CLASS_OB;
        rvm->runtime_stack->data[rvm->runtime_stack->top_index + 0].u.class_ob_value = callee_object;
        local_variable_offset++;
    }

    // Step-2: 通过实参 来初始化形参
    for (unsigned int i = 0; i < arguement_list_size; i++, local_variable_offset++) {
        STACK_COPY_INDEX(rvm,
                         rvm->runtime_stack->top_index + local_variable_offset,
                         arguement_list_index + i);
    }

    // 局部变量为object的情况
    // function->local_variable_list
    RVM_TypeSpecifier*   type_specifier       = nullptr;
    RVM_ClassDefinition* rvm_class_definition = nullptr;
    RVM_ClassObject*     class_ob             = nullptr;
    RVM_String*          string               = nullptr;
    unsigned int         alloc_size           = 0;

    // Step-3: 初始化函数中声明的局部变量
    for (unsigned int i = 0; i < function->local_variable_size; i++, local_variable_offset++) {
        type_specifier = function->local_variable_list[i].type_specifier;

        // 初始化 self 变量
        if (callee_object != nullptr && i == 0) {
            // 如果 callee_object != nullptr
            // function->local_variable_list[0] 必是self 变量
            // 将 callee_object 初始化给 self
            // 浅copy
            // 这个操作 已经在 Step-1 完成了, 改步骤需要忽略.
            continue;
        }

        switch (type_specifier->kind) {
        case RING_BASIC_TYPE_BOOL:
            STACK_SET_BOOL_INDEX(rvm, rvm->runtime_stack->top_index + local_variable_offset, RVM_FALSE);
            break;
        case RING_BASIC_TYPE_INT:
            STACK_SET_INT_INDEX(rvm, rvm->runtime_stack->top_index + local_variable_offset, 0);
            break;
        case RING_BASIC_TYPE_DOUBLE:
            STACK_SET_DOUBLE_INDEX(rvm, rvm->runtime_stack->top_index + local_variable_offset, 0.0);
            break;
        case RING_BASIC_TYPE_STRING:
            string     = new_string(rvm);
            alloc_size = init_string(rvm, string, ROUND_UP8(1));
            rvm_heap_list_add_object(rvm, (RVM_GC_Object*)string);
            rvm_heap_alloc_size_incr(rvm, alloc_size);

            STACK_SET_STRING_INDEX(rvm, rvm->runtime_stack->top_index + local_variable_offset, string);
            break;
        case RING_BASIC_TYPE_CLASS:
            rvm_class_definition = &(rvm->class_list[type_specifier->u.class_def_index]);
            class_ob             = rvm_new_class_object(rvm, rvm_class_definition);
            STACK_SET_CLASS_OB_INDEX(rvm, rvm->runtime_stack->top_index + local_variable_offset, class_ob);
            break;

        default:
            break;
        }
    }
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
    size_t       length     = 0;
    unsigned int capacity   = 0;
    size_t       alloc_size = 0;
    RVM_String*  string     = new_string(rvm);

    length                  = (string_literal != nullptr) ? strlen(string_literal) : 0;
    capacity                = ROUND_UP8(length);
    alloc_size              = capacity * sizeof(char);

    string->length          = length;
    string->capacity        = capacity;
    string->data            = (char*)calloc(1, alloc_size);

    rvm_heap_list_add_object(rvm, (RVM_GC_Object*)string);
    rvm_heap_alloc_size_incr(rvm, alloc_size);
    debug_exec_info_with_white("\t string::alloc_size:%ld", alloc_size);


    memset(string->data, 0, alloc_size);
    strncpy(string->data, string_literal, length);

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

    unsigned int alloc_size = 0;
    RVM_String*  string;

    string         = new_string(rvm);
    alloc_size     = init_string(rvm, string, ROUND_UP8(a->length + b->length));


    string->length = a->length + b->length;
    strncpy(string->data, a->data, a->length);
    strncpy(string->data + a->length, b->data, b->length);

    rvm_heap_list_add_object(rvm, (RVM_GC_Object*)string);
    rvm_heap_alloc_size_incr(rvm, alloc_size);

    return string;
}


/*
 * 只用来初始化一维数组常量
 */
RVM_Array* rvm_new_array_literal_bool(Ring_VirtualMachine* rvm, unsigned int size) {
    unsigned int dimension        = 1;
    unsigned int dimension_list[] = {size};

    RVM_Array*   array            = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_BOOL, nullptr);
    for (int i = 0; i < size; i++) {
        array->u.bool_array[i] = STACK_GET_INT_OFFSET(rvm, -size + i);
    }

    return array;
}

/*
 * 只用来初始化一维数组常量
 */
RVM_Array* rvm_new_array_literal_int(Ring_VirtualMachine* rvm, unsigned int size) {
    unsigned int dimension        = 1;
    unsigned int dimension_list[] = {size};

    RVM_Array*   array            = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_INT, nullptr);
    for (int i = 0; i < size; i++) {
        array->u.int_array[i] = STACK_GET_INT_OFFSET(rvm, -size + i);
    }

    return array;
}

/*
 * 只用来初始化一维数组常量
 */
RVM_Array* rvm_new_array_literal_double(Ring_VirtualMachine* rvm, unsigned int size) {
    unsigned int dimension        = 1;
    unsigned int dimension_list[] = {size};

    RVM_Array*   array            = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_DOUBLE, nullptr);
    for (int i = 0; i < size; i++) {
        array->u.double_array[i] = STACK_GET_DOUBLE_OFFSET(rvm, -size + i);
    }

    return array;
}

/*
 * 只用来初始化一维数组常量
 */
RVM_Array* rvm_new_array_literal_string(Ring_VirtualMachine* rvm, unsigned int size) {
    unsigned int dimension        = 1;
    unsigned int dimension_list[] = {size};

    RVM_Array*   array            = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_STRING, nullptr);
    for (int i = 0; i < size; i++) {
        // TODO: shallow copy
        array->u.string_array[i] = STACK_GET_STRING_OFFSET(rvm, -size + i);
    }

    return array;
}

/*
 * 只用来初始化一维数组常量
 */
RVM_Array* rvm_new_array_literal_class_object(Ring_VirtualMachine* rvm,
                                              unsigned int         size,
                                              RVM_ClassDefinition* class_definition) {

    unsigned int dimension        = 1;
    unsigned int dimension_list[] = {size};

    RVM_Array*   array            = rvm_new_array(rvm, dimension, dimension_list, dimension, RVM_ARRAY_CLASS_OBJECT, class_definition);
    for (int i = 0; i < size; i++) {
        array->u.class_ob_array[i] = *(STACK_GET_CLASS_OB_OFFSET(rvm, -size + i));
    }

    return array;
}

/*
 * 初始化多维数组常量
 */
RVM_Array* rvm_new_array_literal_a(Ring_VirtualMachine* rvm,
                                   unsigned int         dimension,
                                   unsigned int         size) {

    RVM_Array* array = new_array(rvm);
    array->type      = RVM_ARRAY_A;
    array->dimension = dimension;
    array->length    = size;
    array->capacity  = size;

    array->u.a_array = (RVM_Array*)mem_alloc(rvm->meta_pool,
                                             sizeof(RVM_Array) * array->capacity);

    for (unsigned int i = 0; i < size; i++) {
        // this is shallow copy
        array->u.a_array[i] = *(STACK_GET_ARRAY_OFFSET(rvm, -size + i));
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

// 多位数组的中间态, 后续优化
ErrorCode rvm_array_get_array(Ring_VirtualMachine* rvm, RVM_Array* array, int index, RVM_Array** value) {
    if (index >= array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }

    *value = &(array->u.a_array[index]);

    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_get_bool(Ring_VirtualMachine* rvm, RVM_Array* array, int index, bool* value) {
    if (index >= array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    *value = array->u.bool_array[index];
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_set_bool(Ring_VirtualMachine* rvm, RVM_Array* array, int index, bool* value) {
    if (index >= array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    array->u.bool_array[index] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_append_bool(Ring_VirtualMachine* rvm, RVM_Array* array, bool* value) {
    size_t old_alloc_size = 0;
    size_t new_alloc_size = 0;

    if (array->length == array->capacity) {
        old_alloc_size = array->capacity * sizeof(bool);

        if (array->capacity == 0) {
            array->capacity = 8;
        } else {
            array->capacity *= 2;
        }

        new_alloc_size      = array->capacity * sizeof(bool);

        array->u.bool_array = (bool*)realloc(array->u.bool_array,
                                             new_alloc_size);

        rvm_heap_alloc_size_incr(rvm, new_alloc_size);
        rvm_heap_alloc_size_decr(rvm, old_alloc_size);
    }
    array->u.bool_array[array->length++] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_pop_bool(Ring_VirtualMachine* rvm, RVM_Array* array, bool* value) {
    if (array->length == 0) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    *value = array->u.bool_array[--array->length];
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_get_int(Ring_VirtualMachine* rvm, RVM_Array* array, int index, int* value) {
    if (index >= array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    *value = array->u.int_array[index];
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_set_int(Ring_VirtualMachine* rvm, RVM_Array* array, int index, int* value) {
    if (index >= array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    array->u.int_array[index] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_append_int(Ring_VirtualMachine* rvm, RVM_Array* array, int* value) {
    size_t old_alloc_size = 0;
    size_t new_alloc_size = 0;

    if (array->length == array->capacity) {
        old_alloc_size = array->capacity * sizeof(int);

        if (array->capacity == 0) {
            array->capacity = 8;
        } else {
            array->capacity *= 2;
        }

        new_alloc_size     = array->capacity * sizeof(int);

        array->u.int_array = (int*)realloc(array->u.int_array,
                                           new_alloc_size);

        rvm_heap_alloc_size_incr(rvm, new_alloc_size);
        rvm_heap_alloc_size_decr(rvm, old_alloc_size);
    }
    array->u.int_array[array->length++] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_pop_int(Ring_VirtualMachine* rvm, RVM_Array* array, int* value) {
    if (array->length == 0) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    *value = array->u.int_array[--array->length];
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_get_double(Ring_VirtualMachine* rvm, RVM_Array* array, int index, double* value) {
    if (index >= array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    *value = array->u.double_array[index];
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_set_double(Ring_VirtualMachine* rvm, RVM_Array* array, int index, double* value) {
    if (index >= array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    array->u.double_array[index] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_append_double(Ring_VirtualMachine* rvm, RVM_Array* array, double* value) {
    size_t old_alloc_size = 0;
    size_t new_alloc_size = 0;

    if (array->length == array->capacity) {
        old_alloc_size = array->capacity * sizeof(double);

        if (array->capacity == 0) {
            array->capacity = 4;
        } else {
            array->capacity *= 2;
        }

        new_alloc_size        = array->capacity * sizeof(double);

        array->u.double_array = (double*)realloc(array->u.double_array,
                                                 new_alloc_size);

        rvm_heap_alloc_size_incr(rvm, new_alloc_size);
        rvm_heap_alloc_size_decr(rvm, old_alloc_size);
    }
    array->u.double_array[array->length++] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_pop_double(Ring_VirtualMachine* rvm, RVM_Array* array, double* value) {
    if (array->length == 0) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    *value = array->u.double_array[--array->length];
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_get_string(Ring_VirtualMachine* rvm, RVM_Array* array, int index, RVM_String** value) {
    if (index >= array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    RVM_String* src_string = array->u.string_array[index];

    RVM_String* dst_string = rvm_deep_copy_string(rvm, src_string);

    *value                 = dst_string;
    return ERROR_CODE_SUCCESS;
}

// TODO: 重新考虑一下, 可能存在内存泄漏
ErrorCode rvm_array_set_string(Ring_VirtualMachine* rvm, RVM_Array* array, int index, RVM_String** value) {
    if (index >= array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    RVM_String* dst_string       = rvm_deep_copy_string(rvm, *value);

    array->u.string_array[index] = dst_string;

    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_append_string(Ring_VirtualMachine* rvm, RVM_Array* array, RVM_String** value) {
    size_t old_alloc_size = 0;
    size_t new_alloc_size = 0;

    if (array->length >= array->capacity) {
        old_alloc_size = array->capacity * sizeof(RVM_String*);

        if (array->capacity == 0) {
            array->capacity = 4;
        } else {
            array->capacity *= 2;
        }

        new_alloc_size        = array->capacity * sizeof(RVM_String*);


        array->u.string_array = (RVM_String**)mem_realloc(rvm->data_pool,
                                                          array->u.string_array,
                                                          old_alloc_size,
                                                          new_alloc_size);
    }
    array->u.string_array[array->length++] = rvm_deep_copy_string(rvm, *value);
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_pop_string(Ring_VirtualMachine* rvm, RVM_Array* array, RVM_String** value) {
    if (array->length == 0) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    RVM_String* dst_string = rvm_deep_copy_string(rvm, (array->u.string_array[--array->length]));
    *value                 = dst_string; // FIXME: 这里内存泄漏了
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_get_class_object(Ring_VirtualMachine* rvm,
                                     RVM_Array*           array,
                                     int                  index,
                                     RVM_ClassObject**    value) {

    if (index >= array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    RVM_ClassObject* src_class_object = &(array->u.class_ob_array[index]);
    // RVM_ClassObject* dst_class_object = rvm_deep_copy_class_object(rvm, src_class_object);

    // TIP: this is shallow copy of class-object.
    *value = src_class_object;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_set_class_object(Ring_VirtualMachine* rvm,
                                     RVM_Array*           array,
                                     int                  index,
                                     RVM_ClassObject**    value) {

    if (index >= array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }

    RVM_ClassObject* dst_class_object = nullptr;
    dst_class_object                  = rvm_deep_copy_class_object(rvm, *value);

    array->u.class_ob_array[index]    = *dst_class_object;

    return ERROR_CODE_SUCCESS;
}


ErrorCode rvm_array_append_class_object(Ring_VirtualMachine* rvm,
                                        RVM_Array*           array,
                                        RVM_ClassObject**    value) {

    size_t old_alloc_size = 0;
    size_t new_alloc_size = 0;

    if (array->length >= array->capacity) {
        old_alloc_size = array->capacity * sizeof(RVM_ClassObject);

        if (array->capacity == 0) {
            array->capacity = 4;
        } else {
            array->capacity *= 2;
        }

        new_alloc_size          = array->capacity * sizeof(RVM_ClassObject);


        array->u.class_ob_array = (RVM_ClassObject*)mem_realloc(rvm->meta_pool,
                                                                array->u.class_ob_array,
                                                                old_alloc_size,
                                                                new_alloc_size);
    }
    array->u.class_ob_array[array->length++] = *rvm_deep_copy_class_object(rvm, *value);
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_pop_class_object(Ring_VirtualMachine* rvm,
                                     RVM_Array*           array,
                                     RVM_ClassObject**    value) {

    if (array->length == 0) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }

    RVM_ClassObject* src_class_object = &(array->u.class_ob_array[--array->length]);
    RVM_ClassObject* dst_class_object = rvm_deep_copy_class_object(rvm, src_class_object);

    *value                            = dst_class_object;
    return ERROR_CODE_SUCCESS;
}


RVM_String* rvm_bool_2_string(Ring_VirtualMachine* rvm, bool value) {
    RVM_String*  string     = 0;
    unsigned int alloc_size = 0;

    string                  = new_string(rvm);
    alloc_size              = init_string(rvm, string, ROUND_UP8(1));

    if (value) {
        string->length = 4;
        strncpy(string->data, "true", 4);
    } else {
        string->length = 5;
        strncpy(string->data, "false", 5);
    }

    rvm_heap_list_add_object(rvm, (RVM_GC_Object*)string);
    rvm_heap_alloc_size_incr(rvm, alloc_size);

    return string;
}

RVM_String* rvm_int_2_string(Ring_VirtualMachine* rvm, int value) {
    RVM_String*  string     = 0;
    unsigned int alloc_size = 0;

    // TODO:这里直接用的 cpp的函数, 是否需要自己实现?
    std::string tmp = std::to_string(value);

    string          = new_string(rvm);
    alloc_size      = init_string(rvm, string, ROUND_UP8(tmp.size()));

    string->length  = tmp.size();
    strncpy(string->data, tmp.c_str(), tmp.size());

    rvm_heap_list_add_object(rvm, (RVM_GC_Object*)string);
    rvm_heap_alloc_size_incr(rvm, alloc_size);

    return string;
}

RVM_String* rvm_double_2_string(Ring_VirtualMachine* rvm, double value) {
    RVM_String*  string     = 0;
    unsigned int alloc_size = 0;

    // TODO:这里直接用的 cpp的函数, 是否需要自己实现?
    std::string tmp = std::to_string(value);

    string          = new_string(rvm);
    alloc_size      = init_string(rvm, string, ROUND_UP8(tmp.size()));

    string->length  = tmp.size();
    strncpy(string->data, tmp.c_str(), tmp.size());

    rvm_heap_list_add_object(rvm, (RVM_GC_Object*)string);
    rvm_heap_alloc_size_incr(rvm, alloc_size);

    return string;
}


// TODO: 这里实现的不太优雅
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


void rvm_heap_alloc_size_incr(Ring_VirtualMachine* rvm, unsigned int size) {
    rvm->runtime_heap->alloc_size += size;
}

void rvm_heap_alloc_size_decr(Ring_VirtualMachine* rvm, unsigned int size) {
    rvm->runtime_heap->alloc_size -= size;
}

void rvm_heap_list_add_object(Ring_VirtualMachine* rvm, RVM_GC_Object* object) {
    assert(object != nullptr);

    object->gc_next = rvm->runtime_heap->list;
    if (rvm->runtime_heap->list != nullptr) {
        rvm->runtime_heap->list->gc_prev = object;
    }

    rvm->runtime_heap->list = object;
}

void rvm_heap_list_remove_object(Ring_VirtualMachine* rvm, RVM_GC_Object* object) {
    assert(object != nullptr);

    if (object->gc_prev != nullptr) {
        object->gc_prev->gc_next = object->gc_next;
    }
    if (object->gc_next != nullptr) {
        object->gc_next->gc_prev = object->gc_prev;
    }
    // new head
    if (object->gc_prev == nullptr) {
        rvm->runtime_heap->list = object->gc_next;
    }
}

int rvm_heap_size(Ring_VirtualMachine* rvm) {
    // FIXME: 这里会溢出
    // TODO: 数据类型不够
    return rvm->runtime_heap->alloc_size;
}

void debug_rvm(Ring_VirtualMachine* rvm,
               RVM_Function*        function,
               RVM_Byte*            code_list,
               unsigned int         code_size,
               unsigned int         pc,
               unsigned int         caller_stack_base) {

    debug_exec_info_with_white("\t");

    // get terminal windows size
    struct winsize terminal_size;
    if (isatty(STDOUT_FILENO) == 0 || ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminal_size) < 0) {
        ring_error_report("ioctl TIOCGWINSZ error");
    }

    if (terminal_size.ws_row < 38 || terminal_size.ws_col < 115) {
        ring_error_report("In Debug RVM Mode:");
        ring_error_report("    Please adjust current terminal window size: height > 38, width > 115\n");
        // exit(1);
    }

    CLEAR_SCREEN;
    ring_vm_dump_runtime_stack(rvm->runtime_stack, caller_stack_base, 1, 0);
    ring_vm_code_dump(function, code_list, code_size, pc, 1, 60);

#ifdef DEBUG_RVM_INTERACTIVE
    // 输出框的大小
    MOVE_CURSOR(terminal_size.ws_row - 17, 120);
    printf("--------------------- Output ---------------------\n");

    int row = terminal_size.ws_row - 1;
    for (int i = rvm->stdout_logs.size() - 1; i >= 0 && row > terminal_size.ws_row - 17; i--, row--) {
        MOVE_CURSOR(row, 120);
        printf("|[%d]\"%s\"\n", i, rvm->stdout_logs[i].c_str());
    }
    for (; row > terminal_size.ws_row - 17; row--) {
        MOVE_CURSOR(row, 120);
        printf("|\n");
    }

    MOVE_CURSOR(terminal_size.ws_row - 1, 120);
    printf("--------------------------------------------------\n");
#endif

    MOVE_CURSOR(terminal_size.ws_row - 7, 0);
    printf("----------Operation--------\n");
    printf("|press   enter: step into.|\n");
    printf("|        'i'  : step into.|\n");
    printf("|        'v'  : step over.|\n");
    printf("|        'o'  : step out. |\n");
    printf("|        'q'  : quit.     |\n");
    printf("---------------------------\n");

    char ch = getchar();
    if (ch == 'q') {
        exit(1);
    }
}
