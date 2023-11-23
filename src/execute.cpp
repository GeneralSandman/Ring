#include "ring.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#define STACK_GET_OBJECT_INDEX(rvm, index) \
    ((rvm)->runtime_stack->data[(index)].u.object)

// 通过栈顶偏移 offset 获取 rvm->runtime_stack->data
#define STACK_GET_BOOL_OFFSET(rvm, offset) \
    STACK_GET_BOOL_INDEX((rvm), (rvm)->runtime_stack->top_index + (offset))
#define STACK_GET_INT_OFFSET(rvm, offset) \
    STACK_GET_INT_INDEX((rvm), (rvm)->runtime_stack->top_index + (offset))
#define STACK_GET_DOUBLE_OFFSET(rvm, offset) \
    STACK_GET_DOUBLE_INDEX((rvm), (rvm)->runtime_stack->top_index + (offset))
#define STACK_GET_OBJECT_OFFSET(rvm, offset) \
    STACK_GET_OBJECT_INDEX((rvm), (rvm)->runtime_stack->top_index + (offset))

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
#define STACK_SET_OBJECT_INDEX(rvm, index, value)                         \
    (rvm)->runtime_stack->data[(index)].type     = RVM_VALUE_TYPE_OBJECT; \
    (rvm)->runtime_stack->data[(index)].u.object = (value);

// 通过栈顶偏移 offset 设置 rvm->runtime_stack->data
#define STACK_SET_BOOL_OFFSET(rvm, offset, value) \
    STACK_SET_BOOL_INDEX(rvm, (rvm)->runtime_stack->top_index + (offset), (value))
#define STACK_SET_INT_OFFSET(rvm, offset, value) \
    STACK_SET_INT_INDEX(rvm, (rvm)->runtime_stack->top_index + (offset), (value))
#define STACK_SET_DOUBLE_OFFSET(rvm, offset, value) \
    STACK_SET_DOUBLE_INDEX(rvm, (rvm)->runtime_stack->top_index + (offset), (value))
#define STACK_SET_OBJECT_OFFSET(rvm, offset, value) \
    STACK_SET_OBJECT_INDEX(rvm, (rvm)->runtime_stack->top_index + (offset), (value))


#define STACK_COPY_INDEX(rvm, dst_index, src_index) \
    ((rvm)->runtime_stack->data[(dst_index)] = (rvm)->runtime_stack->data[(src_index)])

#define STACK_COPY_OFFSET(rvm, dst_offset, src_offset) \
    STACK_COPY_INDEX((rvm), (rvm)->runtime_stack->top_index + (dst_offset), (rvm)->runtime_stack->top_index + (src_offset))

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
    RVM_RuntimeStack* stack = (RVM_RuntimeStack*)malloc(sizeof(RVM_RuntimeStack));
    stack->top_index        = 0;
    stack->capacity         = 1024 * 1024; // FIXME: 先开辟一个大的空间
    stack->data             = (RVM_Value*)malloc(stack->capacity * sizeof(RVM_Value));
    stack->size             = 0;
    return stack;
}

RVM_RuntimeStatic* new_runtime_static() {
    RVM_RuntimeStatic* runtime_static = (RVM_RuntimeStatic*)malloc(sizeof(RVM_RuntimeStatic));
    runtime_static->data              = nullptr;
    runtime_static->size              = 0;
    return runtime_static;
}

RVM_RuntimeHeap* new_runtime_heap() {
    RVM_RuntimeHeap* runtime_heap = (RVM_RuntimeHeap*)malloc(sizeof(RVM_RuntimeHeap));
    runtime_heap->alloc_size      = 0;
    runtime_heap->list            = nullptr;
    runtime_heap->threshold       = 10;
    return runtime_heap;
}

Ring_VirtualMachine* ring_virtualmachine_create() {
    Ring_VirtualMachine* rvm = (Ring_VirtualMachine*)malloc(sizeof(Ring_VirtualMachine));
    rvm->executer            = nullptr;
    rvm->executer_entry      = nullptr;
    rvm->runtime_static      = new_runtime_static();
    rvm->runtime_stack       = new_runtime_stack();
    rvm->runtime_heap        = new_runtime_heap();
    rvm->pc                  = 0;
    rvm->class_list          = nullptr;
    rvm->class_size          = 0;
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
void ring_virtualmachine_load_executer(Ring_VirtualMachine* rvm, ExecuterEntry* executer_entry) {
    rvm->executer       = executer_entry->main_package_executer;
    rvm->executer_entry = executer_entry;

    // FIXME: 只初始化main包的全局变量
    rvm_add_static_variable(rvm->executer, rvm->runtime_static);

    // add classes
    // FIXME:
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
}

void rvm_add_static_variable(Package_Executer* executer, RVM_RuntimeStatic* runtime_static) {
    debug_log_with_white_coloar("\t");

    unsigned int size    = executer->global_variable_size;
    runtime_static->size = size;
    runtime_static->data = (RVM_Value*)malloc(size * sizeof(RVM_Value));
}

/*
 * 对全局变量进行初始化
 *
 * 1. 如果有初始化表达式的话，那就通过表达式来初始化
 * 2. 通过默认值初始化
 *
 */
void rvm_init_static_variable(Ring_VirtualMachine* rvm, Package_Executer* executer, RVM_RuntimeStatic* runtime_static) {
    debug_log_with_white_coloar("\t");

    unsigned int     size                 = executer->global_variable_size;
    RVM_Variable*    global_variable_list = executer->global_variable_list;
    TypeSpecifier*   type_specifier       = nullptr;
    ClassDefinition* class_definition     = nullptr;

    for (int i = 0; i < size; i++) {
        type_specifier = global_variable_list[i].type;

        switch (type_specifier->kind) {
        case RING_BASIC_TYPE_BOOL:
        case RING_BASIC_TYPE_INT:
        case RING_BASIC_TYPE_DOUBLE:
            // 这里先不用处理 array
            // 因为全局变量不支持 初始化, 只能在函数中赋值
            break;
        case RING_BASIC_TYPE_STRING:
            runtime_static->data[i].type     = RVM_VALUE_TYPE_STRING;
            runtime_static->data[i].u.object = new_string_object();
            break;
        case RING_BASIC_TYPE_CLASS:
            // Search class-definition from variable declaration.
            assert(type_specifier->u.class_type != nullptr);
            class_definition                 = type_specifier->u.class_type->class_definition;
            runtime_static->data[i].type     = RVM_VALUE_TYPE_OBJECT;
            runtime_static->data[i].u.object = new_class_object(rvm, class_definition);
            break;

        default:
            break;
        }
    }
}

// 全局变量，static空间
RVM_Object* new_string_object() {
    RVM_Object* object         = (RVM_Object*)malloc(sizeof(RVM_Object));
    object->type               = RVM_OBJECT_TYPE_STRING;
    object->u.string           = (RVM_String*)malloc(sizeof(RVM_String));
    object->u.string->length   = 0;
    object->u.string->capacity = 10;
    object->u.string->data     = (char*)malloc(10 * sizeof(char));
    object->gc_mark            = GC_MARK_COLOR_WHITE;


    return object;
}

/*
 * 类的全局变量，static空间
 *
 * 使用到了 class_definition ,  和编译器前端没有做到完全解耦
 * TODO: 解耦
 */
RVM_Object* new_class_object(Ring_VirtualMachine* rvm, ClassDefinition* class_definition) {
    assert(class_definition != nullptr);

    // Search field-member's size and detail from class-definition.
    // Alloc and Init.
    unsigned int field_count = 0;
    RVM_Value*   field       = nullptr;

    // TODO: 先用笨办法 初始化
    // TODO: field_count 后续需要在 fix_ast 就要需要算好
    for (ClassMemberDeclaration* pos = class_definition->member; pos != nullptr; pos = pos->next) {
        if (pos->type == MEMBER_FIELD) {
            field_count++;
        }
    }
    field = (RVM_Value*)malloc(field_count * sizeof(RVM_Value));
    memset(field, 0, field_count * sizeof(RVM_Value));

    RVM_Object* object                  = rvm_heap_new_object(rvm, RVM_OBJECT_TYPE_CLASS);
    object->u.class_object->class_def   = class_definition;
    object->u.class_object->field_count = field_count;
    object->u.class_object->field       = field;

    // TODO: 这里得优化一下, 算得不对, 得分析具体 member的类型
    rvm->runtime_heap->alloc_size += field_count * sizeof(RVM_Value);

    // TODO:
    // if class has constructor method, invoke it.

    return object;
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
    debug_log_with_white_coloar("\t");

    RVM_Byte*          code_list              = rvm->executer->code_list;
    unsigned int       code_size              = rvm->executer->code_size;
    RVM_ConstantPool*  constant_pool_list     = rvm->executer->constant_pool_list;
    RVM_RuntimeStack*  runtime_stack          = rvm->runtime_stack;
    RVM_RuntimeStatic* runtime_static         = rvm->runtime_static;

    unsigned int       index                  = 0;
    unsigned int       package_index          = 0;
    unsigned int       func_index             = 0;
    unsigned int       method_index           = 0;
    unsigned int       oper_num               = 0;
    unsigned int       const_index            = 0;
    unsigned int       caller_stack_base      = 0;
    unsigned int       argument_list_size     = 0;
    unsigned int       caller_stack_offset    = 0;
    unsigned int       return_value_list_size = 0;

    bool               bool_value             = false;
    int                int_value              = 0;
    double             double_value           = 0;
    RVM_Object*        object_value           = nullptr;


    RVM_Function*      function               = nullptr;
    RVM_Object*        array_object           = nullptr;
    // TODO: class_object 这个局部变量名称是不是要改一下, class_object->u.class_object 这样的情况不太好理解
    RVM_Object* class_object                  = nullptr;

    ErrorCode   error_code                    = ERROR_CODE_SUCCESS;

    while (rvm->pc < code_size) {
        RVM_Byte opcode = code_list[rvm->pc];

#ifdef DEBUG_RVM_INTERACTIVE
        debug_rvm(rvm, function, code_list, code_size, rvm->pc, caller_stack_base);
#endif

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
            const_index = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            // TOOD: 这里的写法需要优化一下
            STACK_SET_OBJECT_OFFSET(rvm, 0,
                                    string_literal_to_rvm_object(rvm,
                                                                 constant_pool_list[const_index].u.string_value));
            rvm->runtime_stack->data[rvm->runtime_stack->top_index].type = RVM_VALUE_TYPE_STRING;
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;


        // static
        case RVM_CODE_POP_STATIC_BOOL:
            oper_num                                 = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            index                                    = oper_num;                       //  在操作符后边获取
            runtime_static->data[index].u.bool_value = STACK_GET_BOOL_OFFSET(rvm, -1); // 找到对应的 static 变量
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_STATIC_INT:
            oper_num                                = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            index                                   = oper_num;                      //  在操作符后边获取
            runtime_static->data[index].u.int_value = STACK_GET_INT_OFFSET(rvm, -1); // 找到对应的 static 变量
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_STATIC_DOUBLE:
            oper_num                                   = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            index                                      = oper_num;                         //  在操作符后边获取
            runtime_static->data[index].u.double_value = STACK_GET_DOUBLE_OFFSET(rvm, -1); // 找到对应的 static 变量
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_STATIC_OBJECT:
            oper_num                             = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            index                                = oper_num; //  在操作符后边获取

            /*
             * 浅copy
             * runtime_static->data[index].u.object = STACK_GET_OBJECT_OFFSET(rvm, -1);
             */
            // deep copy
            // runtime_static->data[index] 的设置方式需要重新写一下, 不然容易遗忘
            runtime_static->data[index].type     = RVM_VALUE_TYPE_OBJECT;
            runtime_static->data[index].u.object = rvm_deep_copy_object(rvm, STACK_GET_OBJECT_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STATIC_BOOL:
            oper_num = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            index    = oper_num; //  在操作符后边获取
            STACK_SET_BOOL_OFFSET(rvm, 0, rvm->runtime_static->data[index].u.bool_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STATIC_INT:
            oper_num = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            index    = oper_num; //  在操作符后边获取
            STACK_SET_INT_OFFSET(rvm, 0, rvm->runtime_static->data[index].u.int_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STATIC_DOUBLE:
            oper_num = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            index    = oper_num; //  在操作符后边获取
            STACK_SET_DOUBLE_OFFSET(rvm, 0, rvm->runtime_static->data[index].u.double_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STATIC_OBJECT:
            oper_num = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            index    = oper_num; //  在操作符后边获取
            STACK_SET_OBJECT_OFFSET(rvm, 0, rvm->runtime_static->data[index].u.object);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;

        // stack
        case RVM_CODE_POP_STACK_BOOL:
            caller_stack_offset = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_BOOL_INDEX(rvm, caller_stack_base + caller_stack_offset, STACK_GET_BOOL_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_STACK_INT:
            caller_stack_offset = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_INT_INDEX(rvm, caller_stack_base + caller_stack_offset, STACK_GET_INT_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_STACK_DOUBLE:
            caller_stack_offset = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_DOUBLE_INDEX(rvm, caller_stack_base + caller_stack_offset, STACK_GET_DOUBLE_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_STACK_OBJECT:
            caller_stack_offset = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);

            /*
             * 这里到底是 浅拷贝 还是 深拷贝 还真得好好斟酌一下
             */

            // deep copy
            STACK_SET_OBJECT_INDEX(rvm, caller_stack_base + caller_stack_offset, rvm_deep_copy_object(rvm, STACK_GET_OBJECT_OFFSET(rvm, -1)));
            // 浅copy
            // STACK_SET_OBJECT_INDEX(rvm, caller_stack_base + caller_stack_offset, STACK_GET_OBJECT_OFFSET(rvm, -1));
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STACK_BOOL:
            oper_num            = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            caller_stack_offset = oper_num; //  在操作符后边获取
            STACK_SET_BOOL_OFFSET(rvm, 0,
                                  STACK_GET_BOOL_INDEX(rvm, caller_stack_base + caller_stack_offset));
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STACK_INT:
            oper_num            = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            caller_stack_offset = oper_num; //  在操作符后边获取
            STACK_SET_INT_OFFSET(rvm, 0,
                                 STACK_GET_INT_INDEX(rvm, caller_stack_base + caller_stack_offset));
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STACK_DOUBLE:
            oper_num            = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            caller_stack_offset = oper_num; //  在操作符后边获取
            STACK_SET_DOUBLE_OFFSET(rvm, 0,
                                    STACK_GET_DOUBLE_INDEX(rvm, caller_stack_base + caller_stack_offset));
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STACK_OBJECT:
            oper_num            = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            caller_stack_offset = oper_num; //  在操作符后边获取
            STACK_SET_OBJECT_OFFSET(rvm, 0,
                                    STACK_GET_OBJECT_INDEX(rvm, caller_stack_base + caller_stack_offset));
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;

        // array
        case RVM_CODE_PUSH_ARRAY_BOOL:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -2);
            index        = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_get_bool(rvm, array_object, index, &bool_value);
            runtime_stack->top_index -= 2;
            STACK_SET_BOOL_OFFSET(rvm, 0, (RVM_Bool)((int)bool_value));
            runtime_stack->top_index++;
            rvm->pc += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_INT:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -2);
            index        = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_get_int(rvm, array_object, index, &int_value);
            runtime_stack->top_index -= 2;
            STACK_SET_INT_OFFSET(rvm, 0, int_value);
            runtime_stack->top_index++;
            rvm->pc += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_DOUBLE:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -2);
            index        = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_get_double(rvm, array_object, index, &double_value);
            runtime_stack->top_index -= 2;
            STACK_SET_DOUBLE_OFFSET(rvm, 0, double_value);
            runtime_stack->top_index++;
            rvm->pc += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_STRING:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -2);
            index        = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_get_string(rvm, array_object, index, &object_value);
            runtime_stack->top_index -= 2;
            STACK_SET_OBJECT_OFFSET(rvm, 0, object_value);
            runtime_stack->top_index++;
            rvm->pc += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_OBJECT:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -2);
            index        = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_get_class_object(rvm, array_object, index, &object_value);
            runtime_stack->top_index -= 2;
            STACK_SET_OBJECT_OFFSET(rvm, 0, object_value);
            runtime_stack->top_index++;
            rvm->pc += 1;
            break;

        case RVM_CODE_POP_ARRAY_BOOL:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -2);
            index        = STACK_GET_INT_OFFSET(rvm, -1);
            bool_value   = (bool)STACK_GET_BOOL_OFFSET(rvm, -3);
            rvm_array_set_bool(rvm, array_object, index, &bool_value);
            runtime_stack->top_index -= 3;
            rvm->pc += 1;
            break;
        case RVM_CODE_POP_ARRAY_INT:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -2);
            index        = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_set_int(rvm, array_object, index, &STACK_GET_INT_OFFSET(rvm, -3));
            runtime_stack->top_index -= 3;
            rvm->pc += 1;
            break;
        case RVM_CODE_POP_ARRAY_DOUBLE:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -2);
            index        = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_set_double(rvm, array_object, index, &STACK_GET_DOUBLE_OFFSET(rvm, -3));
            runtime_stack->top_index -= 3;
            rvm->pc += 1;
            break;
        case RVM_CODE_POP_ARRAY_STRING:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -2);
            index        = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_set_string(rvm, array_object, index, &STACK_GET_OBJECT_OFFSET(rvm, -3));
            runtime_stack->top_index -= 3;
            rvm->pc += 1;
            break;
        case RVM_CODE_POP_ARRAY_OBJECT:
            break;

        // array append
        case RVM_CODE_ARRAY_APPEND_BOOL:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -2);
            bool_value   = (bool)STACK_GET_BOOL_OFFSET(rvm, -1);
            rvm_array_append_bool(rvm, array_object, &bool_value);
            runtime_stack->top_index -= 2;
            rvm->pc += 1;
            break;

        case RVM_CODE_ARRAY_APPEND_INT:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -2);
            int_value    = STACK_GET_INT_OFFSET(rvm, -1);
            rvm_array_append_int(rvm, array_object, &int_value);
            runtime_stack->top_index -= 2;
            rvm->pc += 1;
            break;

        case RVM_CODE_ARRAY_APPEND_DOUBLE:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -2);
            double_value = STACK_GET_DOUBLE_OFFSET(rvm, -1);
            rvm_array_append_double(rvm, array_object, &double_value);
            runtime_stack->top_index -= 2;
            rvm->pc += 1;
            break;

        case RVM_CODE_ARRAY_APPEND_STRING:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -2);
            object_value = STACK_GET_OBJECT_OFFSET(rvm, -1);
            rvm_array_append_string(rvm, array_object, &object_value);
            runtime_stack->top_index -= 2;
            rvm->pc += 1;
            break;

        case RVM_CODE_ARRAY_APPEND_OBJECT:
            rvm->pc += 1;
            break;

        // array pop
        case RVM_CODE_ARRAY_POP_BOOL:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -1);
            bool_value   = false;
            rvm_array_pop_bool(rvm, array_object, &bool_value);
            runtime_stack->top_index -= 1;
            STACK_SET_BOOL_OFFSET(rvm, 0, (RVM_Bool)bool_value);
            runtime_stack->top_index += 1;
            rvm->pc += 1;
            break;

        case RVM_CODE_ARRAY_POP_INT:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -1);
            int_value    = 0;
            rvm_array_pop_int(rvm, array_object, &int_value);
            runtime_stack->top_index -= 1;
            STACK_SET_INT_OFFSET(rvm, 0, int_value);
            runtime_stack->top_index += 1;
            rvm->pc += 1;
            break;

        case RVM_CODE_ARRAY_POP_DOUBLE:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -1);
            double_value = false;
            rvm_array_pop_double(rvm, array_object, &double_value);
            runtime_stack->top_index -= 1;
            STACK_SET_DOUBLE_OFFSET(rvm, 0, double_value);
            runtime_stack->top_index += 1;
            rvm->pc += 1;
            break;

        case RVM_CODE_ARRAY_POP_STRING:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -1);
            object_value = nullptr;
            rvm_array_pop_string(rvm, array_object, &object_value);
            runtime_stack->top_index -= 1;
            STACK_SET_OBJECT_OFFSET(rvm, 0, object_value);
            runtime_stack->top_index += 1;
            rvm->pc += 1;
            break;

        case RVM_CODE_ARRAY_POP_OBJECT:
            rvm->pc += 1;
            break;


        // class
        case RVM_CODE_POP_FIELD_BOOL:
            /*
             * TODO:
             * 这里需要优化一下:
             * 有没有必要 在 pop_field_bool 之前进行 push object
             * 这里是不是反过来写更好理解
             *
             */
            class_object                                               = STACK_GET_OBJECT_OFFSET(rvm, -1);
            oper_num                                                   = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            class_object->u.class_object->field[oper_num].u.bool_value = STACK_GET_BOOL_OFFSET(rvm, -2);
            runtime_stack->top_index -= 2;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_FIELD_INT:
            class_object                                              = STACK_GET_OBJECT_OFFSET(rvm, -1);
            oper_num                                                  = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            class_object->u.class_object->field[oper_num].u.int_value = STACK_GET_INT_OFFSET(rvm, -2);
            runtime_stack->top_index -= 2;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_FIELD_DOUBLE:
            class_object                                                 = STACK_GET_OBJECT_OFFSET(rvm, -1);
            oper_num                                                     = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            class_object->u.class_object->field[oper_num].u.double_value = STACK_GET_DOUBLE_OFFSET(rvm, -2);
            runtime_stack->top_index -= 2;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_FIELD_BOOL:
            class_object = STACK_GET_OBJECT_OFFSET(rvm, -1);
            oper_num     = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_BOOL_OFFSET(rvm, -1, class_object->u.class_object->field[oper_num].u.bool_value);
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_FIELD_INT:
            class_object = STACK_GET_OBJECT_OFFSET(rvm, -1);
            oper_num     = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_INT_OFFSET(rvm, -1, class_object->u.class_object->field[oper_num].u.int_value);
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_FIELD_DOUBLE:
            class_object = STACK_GET_OBJECT_OFFSET(rvm, -1);
            oper_num     = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_DOUBLE_OFFSET(rvm, -1, class_object->u.class_object->field[oper_num].u.double_value);
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
        case RVM_CODE_INCREASE_SUFFIX:
            STACK_GET_INT_OFFSET(rvm, -1)
            ++;
            rvm->pc++;
            break;
        case RVM_CODE_INCREASE_PREFIX:
            STACK_GET_INT_OFFSET(rvm, -1)
            ++;
            rvm->pc++;
            break;
        case RVM_CODE_DECREASE_SUFFIX:
            STACK_GET_INT_OFFSET(rvm, -1)
            --;
            rvm->pc++;
            break;
        case RVM_CODE_DECREASE_PREFIX:
            STACK_GET_INT_OFFSET(rvm, -1)
            --;
            rvm->pc++;
            break;
        case RVM_CODE_CONCAT:
            STACK_SET_OBJECT_OFFSET(rvm, -2, concat_string(rvm, STACK_GET_OBJECT_OFFSET(rvm, -2), STACK_GET_OBJECT_OFFSET(rvm, -1)));
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
            STACK_GET_BOOL_OFFSET(rvm, -2) = (RVM_Bool)(rvm_string_cmp(STACK_GET_OBJECT_OFFSET(rvm, -2), STACK_GET_OBJECT_OFFSET(rvm, -1)) == 0);
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
            STACK_GET_BOOL_OFFSET(rvm, -2) = (RVM_Bool)(rvm_string_cmp(STACK_GET_OBJECT_OFFSET(rvm, -2), STACK_GET_OBJECT_OFFSET(rvm, -1)) != 0);
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
            STACK_GET_INT_OFFSET(rvm, -2) = (rvm_string_cmp(STACK_GET_OBJECT_OFFSET(rvm, -2), STACK_GET_OBJECT_OFFSET(rvm, -1)) > 0);
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
            STACK_GET_INT_OFFSET(rvm, -2) = (rvm_string_cmp(STACK_GET_OBJECT_OFFSET(rvm, -2), STACK_GET_OBJECT_OFFSET(rvm, -1)) >= 0);
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
            STACK_GET_INT_OFFSET(rvm, -2) = (rvm_string_cmp(STACK_GET_OBJECT_OFFSET(rvm, -2), STACK_GET_OBJECT_OFFSET(rvm, -1)) < 0);
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
            STACK_GET_INT_OFFSET(rvm, -2) = (rvm_string_cmp(STACK_GET_OBJECT_OFFSET(rvm, -2), STACK_GET_OBJECT_OFFSET(rvm, -1)) <= 0);
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
        case RVM_CODE_DUPLICATE:
            STACK_COPY_OFFSET(rvm, 0, -1);
            runtime_stack->top_index++;
            rvm->pc++;
            break;

        // func
        case RVM_CODE_PUSH_FUNC:
            oper_num   = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            func_index = oper_num;
            STACK_SET_INT_OFFSET(rvm, 0, func_index);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_METHOD:
            oper_num     = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            method_index = oper_num;
            STACK_SET_INT_OFFSET(rvm, 0, method_index);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_ARGUMENT_NUM:
            oper_num           = OPCODE_GET_1BYTE(&code_list[rvm->pc + 1]);
            argument_list_size = oper_num;
            rvm->pc += 2;
            break;
        case RVM_CODE_INVOKE_FUNC:
            oper_num      = STACK_GET_INT_OFFSET(rvm, -1);
            package_index = oper_num >> 8;
            func_index    = oper_num & 0XFF;

            runtime_stack->top_index--;
            if (rvm->executer_entry->package_executer_list[package_index]->function_list[func_index].type == RVM_FUNCTION_TYPE_NATIVE) {
                invoke_native_function(rvm, &rvm->executer_entry->package_executer_list[package_index]->function_list[func_index],
                                       argument_list_size);
                rvm->pc += 1;
            } else if (rvm->executer_entry->package_executer_list[package_index]->function_list[func_index].type == RVM_FUNCTION_TYPE_DERIVE) {
                invoke_derive_function(rvm,
                                       &function, &rvm->executer_entry->package_executer_list[package_index]->function_list[func_index],
                                       &code_list, &code_size,
                                       &rvm->pc,
                                       &caller_stack_base);
            }
            break;
        case RVM_CODE_INVOKE_METHOD:
            method_index = STACK_GET_INT_OFFSET(rvm, -1);
            class_object = STACK_GET_OBJECT_OFFSET(rvm, -2);
            runtime_stack->top_index -= 2;
            // FIXME: object->u.class_object->class_def->class_index 这样使用是不对的
            invoke_derive_function(rvm,
                                   &function, rvm->class_list[class_object->u.class_object->class_def->class_index].method_list[method_index].rvm_function,
                                   &code_list, &code_size,
                                   &rvm->pc,
                                   &caller_stack_base);

            break;
        case RVM_CODE_RETURN:
            return_value_list_size = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            rvm->pc += 3;
            // break; // ATTEN: no need break
        case RVM_CODE_FUNCTION_FINISH:
            derive_function_finish(rvm,
                                   &function, nullptr,
                                   &code_list, &code_size,
                                   &rvm->pc, &caller_stack_base, return_value_list_size);
            return_value_list_size = 0;
            break;
        case RVM_CODE_EXIT:
            oper_num = OPCODE_GET_1BYTE(&code_list[rvm->pc + 1]);
            exit(oper_num);
            break;

        // array
        case RVM_CODE_NEW_ARRAY_BOOL:
            oper_num     = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            array_object = rvm_new_array_bool(rvm, oper_num);
            STACK_SET_OBJECT_OFFSET(rvm, 0, array_object);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_NEW_ARRAY_INT:
            oper_num     = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            array_object = rvm_new_array_int(rvm, oper_num);
            STACK_SET_OBJECT_OFFSET(rvm, 0, array_object);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_NEW_ARRAY_DOUBLE:
            oper_num     = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            array_object = rvm_new_array_double(rvm, oper_num);
            STACK_SET_OBJECT_OFFSET(rvm, 0, array_object);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_NEW_ARRAY_STRING:
            oper_num     = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            array_object = rvm_new_array_string(rvm, oper_num);
            STACK_SET_OBJECT_OFFSET(rvm, 0, array_object);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_NEW_ARRAY_OBJECT: {
            unsigned int field_count = OPCODE_GET_1BYTE(&code_list[rvm->pc + 1]); // field 的数量不能超过 255
            unsigned int oper_num    = OPCODE_GET_2BYTE(&code_list[rvm->pc + 2]);
            array_object             = rvm_new_array_class_object(rvm, field_count, oper_num);
            STACK_SET_OBJECT_OFFSET(rvm, 0, array_object);
            runtime_stack->top_index++;
            rvm->pc += 4;
        } break;
        case RVM_CODE_NEW_ARRAY_LITERAL_BOOL: {
            int size     = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            array_object = rvm_new_array_literal_bool(rvm, size);
            runtime_stack->top_index -= size;
            STACK_SET_OBJECT_OFFSET(rvm, 0, array_object);
            runtime_stack->top_index++;
            rvm->pc += 3;
        } break;
        case RVM_CODE_NEW_ARRAY_LITERAL_INT: {
            int size     = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            array_object = rvm_new_array_literal_int(rvm, size);
            runtime_stack->top_index -= size;
            STACK_SET_OBJECT_OFFSET(rvm, 0, array_object);
            runtime_stack->top_index++;
            rvm->pc += 3;
        } break;
        case RVM_CODE_NEW_ARRAY_LITERAL_DOUBLE: {
            int size     = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            array_object = rvm_new_array_literal_double(rvm, size);
            runtime_stack->top_index -= size;
            STACK_SET_OBJECT_OFFSET(rvm, 0, array_object);
            runtime_stack->top_index++;
            rvm->pc += 3;
        } break;
        case RVM_CODE_NEW_ARRAY_LITERAL_STRING: {
            int size     = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            array_object = rvm_new_array_literal_string(rvm, size);
            runtime_stack->top_index -= size;
            STACK_SET_OBJECT_OFFSET(rvm, 0, array_object);
            runtime_stack->top_index++;
            rvm->pc += 3;
        } break;
        case RVM_CODE_NEW_ARRAY_LITERAL_OBJECT:
            rvm->pc += 3;
            break;

        case RVM_CODE_PUSH_ARRAY_LEN:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -1);
            rvm_array_get_length(rvm, array_object, &int_value);
            runtime_stack->top_index -= 1;
            STACK_SET_INT_OFFSET(rvm, 0, int_value);
            runtime_stack->top_index += 1;
            rvm->pc += 1;
            break;
        case RVM_CODE_PUSH_ARRAY_CAPACITY:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -1);
            rvm_array_get_capacity(rvm, array_object, &int_value);
            runtime_stack->top_index -= 1;
            STACK_SET_INT_OFFSET(rvm, 0, int_value);
            runtime_stack->top_index += 1;
            rvm->pc += 1;
            break;
        case RVM_CODE_PUSH_STRING_LEN:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -1);
            rvm_string_get_length(rvm, array_object, &int_value);
            runtime_stack->top_index -= 1;
            STACK_SET_INT_OFFSET(rvm, 0, int_value);
            runtime_stack->top_index += 1;
            rvm->pc += 1;
            break;
        case RVM_CODE_PUSH_STRING_CAPACITY:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -1);
            rvm_string_get_capacity(rvm, array_object, &int_value);
            runtime_stack->top_index -= 1;
            STACK_SET_INT_OFFSET(rvm, 0, int_value);
            runtime_stack->top_index += 1;
            rvm->pc += 1;
            break;

            // class
        case RVM_CODE_NEW_CLASS_OBJECT_LITERAL: {
            unsigned int field_count   = OPCODE_GET_1BYTE(&code_list[rvm->pc + 1]); // field 的数量不能超过 255
            unsigned int init_exp_size = OPCODE_GET_1BYTE(&code_list[rvm->pc + 2]); // field 的数量不能超过 255

            class_object               = rvm_new_class_object_literal(rvm, field_count, init_exp_size);
            runtime_stack->top_index -= init_exp_size;
            STACK_SET_OBJECT_OFFSET(rvm, 0, class_object);
            runtime_stack->top_index++;
            rvm->pc += 3;
        } break;

        // range
        case RVM_CODE_FOR_RANGE_ARRAY_BOOL:
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -2);
            index        = STACK_GET_INT_OFFSET(rvm, -1);
            error_code   = rvm_array_get_bool(rvm, array_object, index, &bool_value);
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
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -2);
            index        = STACK_GET_INT_OFFSET(rvm, -1);
            error_code   = rvm_array_get_int(rvm, array_object, index, &int_value);
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
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -2);
            index        = STACK_GET_INT_OFFSET(rvm, -1);
            error_code   = rvm_array_get_double(rvm, array_object, index, &double_value);
            if (error_code == RUNTIME_ERR_OUT_OF_ARRAY_RANGE) {
                rvm->pc = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
                break;
            }
            // runtime_stack->top_index -= 2; // 与 RVM_CODE_PUSH_ARRAY_DOUBLE 的不同点 区别
            STACK_SET_DOUBLE_OFFSET(rvm, 0, double_value);
            runtime_stack->top_index++;
            rvm->pc += 3;

            // iter ++
            STACK_GET_INT_OFFSET(rvm, -2)
            ++;
            break;
        case RVM_CODE_FOR_RANGE_ARRAY_STRING: {
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -2);
            index        = STACK_GET_INT_OFFSET(rvm, -1);
            error_code   = rvm_array_get_string(rvm, array_object, index, &object_value);
            if (error_code == RUNTIME_ERR_OUT_OF_ARRAY_RANGE) {
                rvm->pc = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
                break;
            }
            // runtime_stack->top_index -= 2; // 与 RVM_CODE_PUSH_ARRAY_STRING 的不同点 区别
            STACK_SET_OBJECT_OFFSET(rvm, 0, object_value);
            runtime_stack->top_index++;
            rvm->pc += 3;

            // iter ++
            STACK_GET_INT_OFFSET(rvm, -2)
            ++;
        } break;
        case RVM_CODE_FOR_RANGE_ARRAY_OBJECT: {
            array_object = STACK_GET_OBJECT_OFFSET(rvm, -2);
            index        = STACK_GET_INT_OFFSET(rvm, -1);
            error_code   = rvm_array_get_class_object(rvm, array_object, index, &object_value);
            if (error_code == RUNTIME_ERR_OUT_OF_ARRAY_RANGE) {
                rvm->pc = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
                break;
            }
            // runtime_stack->top_index -= 2; // 与 RVM_CODE_PUSH_ARRAY_OBJECT 的不同点 区别
            STACK_SET_OBJECT_OFFSET(rvm, 0, object_value);
            runtime_stack->top_index++;
            rvm->pc += 3;

            // iter ++
            STACK_GET_INT_OFFSET(rvm, -2)
            ++;
        } break;
        case RVM_CODE_FOR_RANGE_FINISH:
            runtime_stack->top_index -= 2;
            rvm->pc += 3;
            break;


        // convert
        case RVM_CODE_BOOL_2_STRING:
            bool_value   = STACK_GET_BOOL_OFFSET(rvm, -1);
            object_value = rvm_heap_new_object_from_string(rvm,
                                                           rvm_bool_2_string(rvm, bool_value));
            STACK_SET_OBJECT_OFFSET(rvm, -1, object_value);
            // FIXME: 这里set type 需要优化一下,
            rvm->runtime_stack->data[rvm->runtime_stack->top_index - 1].type = RVM_VALUE_TYPE_STRING;
            rvm->pc += 1;
            break;
        case RVM_CODE_INT_2_STRING:
            int_value    = STACK_GET_INT_OFFSET(rvm, -1);
            object_value = rvm_heap_new_object_from_string(rvm, rvm_int_2_string(rvm, int_value));
            STACK_SET_OBJECT_OFFSET(rvm, -1, object_value);
            // FIXME: 这里set type 需要优化一下,
            rvm->runtime_stack->data[rvm->runtime_stack->top_index - 1].type = RVM_VALUE_TYPE_STRING;
            rvm->pc += 1;
            break;
        case RVM_CODE_DOUBLE_2_STRING:
            double_value = STACK_GET_DOUBLE_OFFSET(rvm, -1);
            object_value = rvm_heap_new_object_from_string(rvm, rvm_double_2_string(rvm, double_value));
            STACK_SET_OBJECT_OFFSET(rvm, -1, object_value);
            // FIXME: 这里set type 需要优化一下,
            rvm->runtime_stack->data[rvm->runtime_stack->top_index - 1].type = RVM_VALUE_TYPE_STRING;
            rvm->pc += 1;
            break;

        default:
            fprintf(stderr,
                    "execute error: pc(%d)\n"
                    "\tinvalid opcode (%d)\n",
                    rvm->pc,
                    opcode);
            exit(ERROR_CODE_RUN_VM_ERROR);
            break;
        }
    }

#ifdef DEBUG_RVM_INTERACTIVE
    debug_rvm(rvm, function, code_list, code_size, rvm->pc, caller_stack_base);
#endif
}


void invoke_native_function(Ring_VirtualMachine* rvm, RVM_Function* function, unsigned int argument_list_size) {
    debug_log_with_white_coloar("\t");

    RVM_Value           ret;

    int                 return_list_count = function->u.native_func->return_list_count;
    RVM_NativeFuncProc* native_func_proc  = function->u.native_func->func_proc;
    // unsigned int        arg_count        = function->u.native_func->arg_count;
    RVM_Value* args; // TODO:

    // TODO: how to handle arg_count > 1
    args = &rvm->runtime_stack->data[rvm->runtime_stack->top_index - argument_list_size];

    // TODO: how to handler return_list > 1
    ret  = native_func_proc(rvm, argument_list_size, args);


    // 销毁 argument
    rvm->runtime_stack->top_index -= argument_list_size;

    // TODO: 需要补齐一个 return 指令
    // TODO: 如何在这里处理 return 多返回值的问题
    if (return_list_count == 0) {
    } else if (return_list_count == 1) {
        rvm->runtime_stack->data[rvm->runtime_stack->top_index++] = ret;
    } else {
        fprintf(stderr,
                "native function return value count > 1");
        exit(ERROR_CODE_RUN_VM_ERROR);
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
 */
void invoke_derive_function(Ring_VirtualMachine* rvm,
                            RVM_Function** caller_function, RVM_Function* callee_function,
                            RVM_Byte** code_list, unsigned int* code_size,
                            unsigned int* pc,
                            unsigned int* caller_stack_base) {
    debug_log_with_white_coloar("\t");

    // FIXME:
    /* unsigned int arguement_count = 0; */

    RVM_CallInfo* callinfo         = (RVM_CallInfo*)malloc(sizeof(RVM_CallInfo));
    callinfo->magic_number         = CALL_INFO_MAGIC_NUMBER;
    callinfo->caller_function      = *caller_function;
    callinfo->caller_pc            = *pc;
    callinfo->caller_stack_base    = *caller_stack_base;
    callinfo->callee_argument_size = callee_function->parameter_size; // FIXME: 支持可变参数
    store_callinfo(rvm->runtime_stack, callinfo);


    *caller_function   = callee_function;
    *code_list         = callee_function->u.derive_func->code_list;
    *code_size         = callee_function->u.derive_func->code_size;
    *pc                = 0;
    *caller_stack_base = rvm->runtime_stack->top_index; // FIXME:


    init_derive_function_local_variable(rvm, callee_function);

    // FIXME:a local_variable_size
    // 暂时先写死为20
    unsigned int local_variable_size = 20;
    rvm->runtime_stack->top_index += local_variable_size;
}

void derive_function_return(Ring_VirtualMachine* rvm,
                            RVM_Function** caller_function, RVM_Function* callee_function,
                            RVM_Byte** code_list, unsigned int* code_size,
                            unsigned int* pc,
                            unsigned int* caller_stack_base,
                            unsigned int  return_list_size) {
    debug_log_with_white_coloar("\t");
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
    debug_log_with_white_coloar("\t");

    unsigned int old_return_value_list_index;

    rvm->runtime_stack->top_index -= return_value_list_size;
    old_return_value_list_index      = rvm->runtime_stack->top_index;


    RVM_CallInfo* callinfo           = nullptr;
    // FIXME: local_variable_size
    unsigned int local_variable_size = 20;
    rvm->runtime_stack->top_index -= local_variable_size;

    restore_callinfo(rvm->runtime_stack, &callinfo);
    assert(callinfo->magic_number == CALL_INFO_MAGIC_NUMBER);
    *caller_function   = callinfo->caller_function;
    *pc                = callinfo->caller_pc + 1;
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
    for (int i = 0; i < return_value_list_size; i++) {
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
void store_callinfo(RVM_RuntimeStack* runtime_stack, RVM_CallInfo* callinfo) {
    runtime_stack->data[runtime_stack->top_index].type        = RVM_VALUE_TYPE_CALLINFO;
    runtime_stack->data[runtime_stack->top_index].u.call_info = callinfo;
    runtime_stack->top_index += CALL_INFO_SIZE_V2;
    return;

    RVM_CallInfo* dest;
    dest = (RVM_CallInfo*)(&runtime_stack->data[runtime_stack->top_index]);
    memcpy(dest, callinfo, sizeof(RVM_CallInfo));
    runtime_stack->top_index += CALL_INFO_SIZE;
}

/*
 * restore callinfo when function finish
 *
 * 1. Pop from runtime_stack
 * 2. Decode callinfo
 *
 */
void restore_callinfo(RVM_RuntimeStack* runtime_stack, RVM_CallInfo** callinfo) {
    runtime_stack->top_index -= CALL_INFO_SIZE_V2;
    *callinfo = runtime_stack->data[runtime_stack->top_index].u.call_info;
    return;

    runtime_stack->top_index -= CALL_INFO_SIZE;
    *callinfo = (RVM_CallInfo*)(&runtime_stack->data[runtime_stack->top_index]);
}

// FIXME:  初始化局部变量列表的时候存在问题
// 如果局部变量是个数组
void init_derive_function_local_variable(Ring_VirtualMachine* rvm, RVM_Function* function) {
    debug_log_with_white_coloar("\t");

    // FIXME: 先忽略局部变量的类型，先用int
    unsigned int arguement_list_size        = function->parameter_size;
    unsigned int arguement_list_index       = rvm->runtime_stack->top_index - CALL_INFO_SIZE_V2 - arguement_list_size;

    // 通过实参 来初始化形参
    // init argument with parameter
    unsigned int local_variable_value_index = 0;
    for (; local_variable_value_index < arguement_list_size; local_variable_value_index++) {
        STACK_COPY_INDEX(rvm, rvm->runtime_stack->top_index + local_variable_value_index, arguement_list_index + local_variable_value_index);
    }

    // 局部变量为object的情况
    // function->local_variable_list
    ClassDefinition* class_definition = nullptr;
    RVM_Object*      object           = nullptr;

    for (int i = 0; i < function->local_variable_size; i++, local_variable_value_index++) {
        TypeSpecifier* type_specifier = function->local_variable_list[i].type_specifier;
        switch (type_specifier->kind) {
        case RING_BASIC_TYPE_BOOL:
        case RING_BASIC_TYPE_INT:
            // 这里先不用处理 array int
            // 因为局部变量 是通过 new 来初始化的
            // array_int = new int[10];
            break;
        case RING_BASIC_TYPE_DOUBLE:
            // 这里先不用处理 array double
            // 因为局部变量 是通过 new 来初始化的
            // array_int = new int[10];
            break;
        case RING_BASIC_TYPE_STRING:
            object = rvm_heap_new_object(rvm, RVM_OBJECT_TYPE_STRING);
            STACK_SET_OBJECT_INDEX(rvm, rvm->runtime_stack->top_index + local_variable_value_index, object);
            break;
        case RING_BASIC_TYPE_CLASS:
            // Search class-definition from variable declaration.
            assert(type_specifier->u.class_type != nullptr);
            class_definition = type_specifier->u.class_type->class_definition;
            object           = new_class_object(rvm, class_definition);
            STACK_SET_OBJECT_INDEX(rvm, rvm->runtime_stack->top_index + local_variable_value_index, object);
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
RVM_Object* string_literal_to_rvm_object(Ring_VirtualMachine* rvm, const char* string_literal) {
    RVM_Object* object = rvm_heap_new_object(rvm, RVM_OBJECT_TYPE_STRING);

    size_t      length = 0;
    if (string_literal != nullptr) {
        length = strlen(string_literal);
    }

    // capacity 需要是2的倍数
    object->u.string->length   = length;
    object->u.string->capacity = length;
    object->u.string->data     = nullptr;
    if (length > 0) {
        object->u.string->data = (char*)malloc(sizeof(char) * length);
        rvm->runtime_heap->alloc_size += sizeof(char) * length;
    }

    memset(object->u.string->data, '\0', length);
    strncpy(object->u.string->data, string_literal, length);

    return object;
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
RVM_Object* concat_string(Ring_VirtualMachine* rvm, RVM_Object* a, RVM_Object* b) {
    assert(a != nullptr);
    assert(b != nullptr);
    assert(a->u.string != nullptr);
    assert(b->u.string != nullptr);

    RVM_Object* object   = rvm_heap_new_object(rvm, RVM_OBJECT_TYPE_STRING);

    size_t      sum_size = 0;
    sum_size += a->u.string->length;
    sum_size += b->u.string->length;

    // capacity 需要是2的倍数

    object->u.string->length   = 0;
    object->u.string->capacity = sum_size;
    object->u.string->data     = nullptr;
    if (sum_size > 0) {
        object->u.string->data = (char*)malloc(sizeof(char) * sum_size);
        rvm->runtime_heap->alloc_size += sizeof(char) * sum_size;
    }

    memset(object->u.string->data, '\0', sum_size);

    strncpy(object->u.string->data, a->u.string->data, a->u.string->length);
    strncpy(object->u.string->data + a->u.string->length, b->u.string->data, b->u.string->length);
    object->u.string->length = sum_size;


    return object;
}

/*
 * create array in heap
 *
 * support create one-dimensional array only.
 * TODO: support multi-dimensional array
 *
 */
RVM_Object* rvm_new_array_bool(Ring_VirtualMachine* rvm, unsigned int dimension) {
    // TODO: malloc object in heap
    RVM_Object* object            = rvm_heap_new_object(rvm, RVM_OBJECT_TYPE_ARRAY);

    object->u.array->type         = RVM_ARRAY_BOOL;
    object->u.array->length       = dimension;
    object->u.array->capacity     = dimension;
    object->u.array->u.bool_array = (bool*)malloc(sizeof(bool) * dimension);

    memset(object->u.array->u.bool_array, 0, sizeof(bool) * dimension);

    // TODO: 这里需要重写
    rvm->runtime_heap->alloc_size += sizeof(bool) * dimension;
    return object;
}

/*
 * create array in heap
 *
 * support create one-dimensional array only.
 * TODO: support multi-dimensional array
 *
 */
RVM_Object* rvm_new_array_int(Ring_VirtualMachine* rvm, unsigned int dimension) {
    // TODO: malloc object in heap
    RVM_Object* object           = rvm_heap_new_object(rvm, RVM_OBJECT_TYPE_ARRAY);

    object->u.array->type        = RVM_ARRAY_INT;
    object->u.array->length      = dimension;
    object->u.array->capacity    = dimension;
    object->u.array->u.int_array = (int*)malloc(sizeof(int) * dimension);

    memset(object->u.array->u.int_array, 0, sizeof(int) * dimension);

    // TODO: 这里需要重写
    rvm->runtime_heap->alloc_size += sizeof(int) * dimension;
    return object;
}

/*
 * create array in heap
 *
 * support create one-dimensional array only.
 * TODO: support multi-dimensional array
 *
 */
RVM_Object* rvm_new_array_double(Ring_VirtualMachine* rvm, unsigned int dimension) {
    RVM_Object* object              = rvm_heap_new_object(rvm, RVM_OBJECT_TYPE_ARRAY);

    object->u.array->type           = RVM_ARRAY_DOUBLE;
    object->u.array->length         = dimension;
    object->u.array->capacity       = dimension;
    object->u.array->u.double_array = (double*)malloc(sizeof(double) * dimension);

    memset(object->u.array->u.double_array, 0, sizeof(double) * dimension);

    // TODO: 这里需要重写
    rvm->runtime_heap->alloc_size += sizeof(double) * dimension;
    return object;
}

/*
 * create array in heap
 *
 * support create one-dimensional array only.
 * TODO: support multi-dimensional array
 *
 */
RVM_Object* rvm_new_array_string(Ring_VirtualMachine* rvm, unsigned int dimension) {
    RVM_Object* object              = rvm_heap_new_object(rvm, RVM_OBJECT_TYPE_ARRAY);

    object->u.array->type           = RVM_ARRAY_STRING;
    object->u.array->length         = dimension;
    object->u.array->capacity       = dimension;
    object->u.array->u.string_array = (RVM_String*)malloc(sizeof(RVM_String) * dimension);

    for (unsigned int i = 0; i < dimension; i++) {
        object->u.array->u.string_array[i].data     = nullptr;
        object->u.array->u.string_array[i].length   = 0;
        object->u.array->u.string_array[i].capacity = 0;
    }


    // TODO: 这里的计算方式不对
    rvm->runtime_heap->alloc_size += sizeof(RVM_String) * dimension;
    return object;
}

/*
 * create array in heap
 *
 * support create one-dimensional array only.
 * TODO: support multi-dimensional array
 *
 * dimension: size of array
 * class_def_index: index of class definition in class table
 */
RVM_Object* rvm_new_array_class_object(Ring_VirtualMachine* rvm, unsigned int field_count, unsigned int dimension) {
    RVM_Object* object                    = rvm_heap_new_object(rvm, RVM_OBJECT_TYPE_ARRAY);

    object->u.array->type                 = RVM_ARRAY_OBJECT;
    object->u.array->length               = dimension;
    object->u.array->capacity             = dimension;
    object->u.array->u.class_object_array = (RVM_ClassObject*)malloc(sizeof(RVM_ClassObject) * dimension);


    for (unsigned int i = 0; i < dimension; i++) {
        RVM_Value* field = (RVM_Value*)malloc(field_count * sizeof(RVM_Value));
        memset(field, 0, field_count * sizeof(RVM_Value));
        // TODO: 有个遗留问题
        // RVM_Value 的 type 没有设置

        object->u.array->u.class_object_array[i].class_def   = nullptr;
        object->u.array->u.class_object_array[i].field_count = field_count;
        object->u.array->u.class_object_array[i].field       = field;
    }


    // TODO: 这里的计算方式不对
    // rvm->runtime_heap->alloc_size += sizeof(RVM_String) * dimension;
    return object;
}

/*
 * create array in heap
 *
 * support create one-dimensional array only.
 * TODO: support multi-dimensional array
 * TODO: support field is string or array
 *
 */
RVM_Object* rvm_new_class_object(Ring_VirtualMachine* rvm, unsigned int field_count) {
    RVM_Object* object = rvm_heap_new_object(rvm, RVM_OBJECT_TYPE_CLASS);

    RVM_Value*  field  = nullptr;
    field              = (RVM_Value*)malloc(field_count * sizeof(RVM_Value));
    memset(field, 0, field_count * sizeof(RVM_Value));
    // TODO: 有个遗留问题
    // RVM_Value 的 type 没有设置

    object->u.class_object->class_def   = nullptr;
    object->u.class_object->field_count = field_count;
    object->u.class_object->field       = field;


    // TODO: 这里的计算方式不对
    rvm->runtime_heap->alloc_size += 0;
    return object;
}

RVM_Object* rvm_new_array_literal_bool(Ring_VirtualMachine* rvm, int size) {
    RVM_Object* object = rvm_new_array_bool(rvm, size);
    for (int i = 0; i < size; i++) {
        object->u.array->u.bool_array[i] = STACK_GET_INT_OFFSET(rvm, -size + i);
    }
    return object;
}

RVM_Object* rvm_new_array_literal_int(Ring_VirtualMachine* rvm, int size) {
    RVM_Object* object = rvm_new_array_int(rvm, size);
    for (int i = 0; i < size; i++) {
        object->u.array->u.int_array[i] = STACK_GET_INT_OFFSET(rvm, -size + i);
    }
    return object;
}

RVM_Object* rvm_new_array_literal_double(Ring_VirtualMachine* rvm, int size) {
    RVM_Object* object = rvm_new_array_double(rvm, size);
    for (int i = 0; i < size; i++) {
        object->u.array->u.double_array[i] = STACK_GET_DOUBLE_OFFSET(rvm, -size + i);
    }
    return object;
}

RVM_Object* rvm_new_array_literal_string(Ring_VirtualMachine* rvm, int size) {
    RVM_Object* object = rvm_new_array_string(rvm, size);
    for (int i = 0; i < size; i++) {
        // TODO: 这个写法需要重构
        object->u.array->u.string_array[i] = *(STACK_GET_OBJECT_OFFSET(rvm, -size + i)->u.string);
    }
    return object;
}

RVM_Object* rvm_new_class_object_literal(Ring_VirtualMachine* rvm, unsigned int field_count, unsigned int init_exp_size) {
    RVM_Object* object = rvm_new_class_object(rvm, field_count);
    if (field_count != init_exp_size) {
        // error report
        fprintf(stderr,
                "the number of class init expresison list must equal to the number of class field");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    // 从 runtime_stack 中取出 已经push的, 然后依次初始化
    unsigned init_exp_of_stack_index = rvm->runtime_stack->top_index - init_exp_size;
    for (int i = 0; i < init_exp_size; i++) {
        object->u.class_object->field[i] = rvm->runtime_stack->data[init_exp_of_stack_index + i];
    }
    return object;
}

void rvm_array_get_length(Ring_VirtualMachine* rvm, RVM_Object* object, int* value) {
    // FIXME: 这里unsigned int -> int
    if (object == nullptr || object->u.array == nullptr) {
        *value = 0;
        return;
    }
    *value = (int)object->u.array->length;
}

void rvm_array_get_capacity(Ring_VirtualMachine* rvm, RVM_Object* object, int* value) {
    // FIXME: 这里unsigned int -> int
    if (object == nullptr || object->u.array == nullptr) {
        *value = 0;
        return;
    }
    *value = (int)object->u.array->capacity;
}

void rvm_string_get_length(Ring_VirtualMachine* rvm, RVM_Object* object, int* value) {
    // FIXME: 这里unsigned int -> int
    *value = (int)object->u.string->length;
}

void rvm_string_get_capacity(Ring_VirtualMachine* rvm, RVM_Object* object, int* value) {
    // FIXME: 这里unsigned int -> int
    *value = (int)object->u.string->capacity;
}

ErrorCode rvm_array_get_bool(Ring_VirtualMachine* rvm, RVM_Object* object, int index, bool* value) {
    if (index >= object->u.array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    *value = object->u.array->u.bool_array[index];
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_set_bool(Ring_VirtualMachine* rvm, RVM_Object* object, int index, bool* value) {
    if (index >= object->u.array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    object->u.array->u.bool_array[index] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_append_bool(Ring_VirtualMachine* rvm, RVM_Object* object, bool* value) {
    if (object->u.array->length == object->u.array->capacity) {
        if (object->u.array->capacity == 0) {
            object->u.array->capacity = 4;
        } else {
            object->u.array->capacity *= 2;
        }
        object->u.array->u.bool_array = (bool*)realloc(object->u.array->u.bool_array,
                                                       object->u.array->capacity * sizeof(bool));
    }
    object->u.array->u.bool_array[object->u.array->length++] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_pop_bool(Ring_VirtualMachine* rvm, RVM_Object* object, bool* value) {
    if (object->u.array->length == 0) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    *value = object->u.array->u.bool_array[--object->u.array->length];
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_get_int(Ring_VirtualMachine* rvm, RVM_Object* object, int index, int* value) {
    if (index >= object->u.array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    *value = object->u.array->u.int_array[index];
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_set_int(Ring_VirtualMachine* rvm, RVM_Object* object, int index, int* value) {
    if (index >= object->u.array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    object->u.array->u.int_array[index] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_append_int(Ring_VirtualMachine* rvm, RVM_Object* object, int* value) {
    if (object->u.array->length == object->u.array->capacity) {
        if (object->u.array->capacity == 0) {
            object->u.array->capacity = 4;
        } else {
            object->u.array->capacity *= 2;
        }
        object->u.array->u.int_array = (int*)realloc(object->u.array->u.int_array,
                                                     object->u.array->capacity * sizeof(int));
    }
    object->u.array->u.int_array[object->u.array->length++] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_pop_int(Ring_VirtualMachine* rvm, RVM_Object* object, int* value) {
    if (object->u.array->length == 0) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    *value = object->u.array->u.int_array[--object->u.array->length];
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_get_double(Ring_VirtualMachine* rvm, RVM_Object* object, int index, double* value) {
    if (index >= object->u.array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    *value = object->u.array->u.double_array[index];
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_set_double(Ring_VirtualMachine* rvm, RVM_Object* object, int index, double* value) {
    if (index >= object->u.array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    object->u.array->u.double_array[index] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_append_double(Ring_VirtualMachine* rvm, RVM_Object* object, double* value) {
    if (object->u.array->length == object->u.array->capacity) {
        if (object->u.array->capacity == 0) {
            object->u.array->capacity = 4;
        } else {
            object->u.array->capacity *= 2;
        }
        object->u.array->u.double_array = (double*)realloc(object->u.array->u.double_array,
                                                           object->u.array->capacity * sizeof(double));
    }
    object->u.array->u.double_array[object->u.array->length++] = *value;
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_pop_double(Ring_VirtualMachine* rvm, RVM_Object* object, double* value) {
    if (object->u.array->length == 0) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    *value = object->u.array->u.double_array[--object->u.array->length];
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_get_string(Ring_VirtualMachine* rvm, RVM_Object* object, int index, RVM_Object** value) {
    if (index >= object->u.array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    RVM_String* src_string = &(object->u.array->u.string_array[index]);
    RVM_Object* new_object = rvm_heap_new_object(rvm, RVM_OBJECT_TYPE_STRING);

    RVM_String* dst_string = rvm_deep_copy_string(rvm, src_string);

    new_object->u.string   = dst_string; // FIXME: 这里内存泄漏了
    *value                 = new_object;
    return ERROR_CODE_SUCCESS;
}

// TODO: 重新考虑一下, 可能存在内存泄漏
ErrorCode rvm_array_set_string(Ring_VirtualMachine* rvm, RVM_Object* object, int index, RVM_Object** value) {
    if (index >= object->u.array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    RVM_String* dst_string                 = rvm_deep_copy_string(rvm, (*value)->u.string);

    object->u.array->u.string_array[index] = *dst_string;

    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_append_string(Ring_VirtualMachine* rvm, RVM_Object* object, RVM_Object** value) {
    if (object->u.array->length >= object->u.array->capacity) {
        if (object->u.array->capacity == 0) {
            object->u.array->capacity = 4;
        } else {
            object->u.array->capacity *= 2;
        }

        object->u.array->u.string_array = (RVM_String*)realloc(object->u.array->u.string_array, sizeof(RVM_String) * object->u.array->capacity);
    }
    object->u.array->u.string_array[object->u.array->length++] = *rvm_deep_copy_string(rvm, (*value)->u.string);
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_pop_string(Ring_VirtualMachine* rvm, RVM_Object* object, RVM_Object** value) {
    if (object->u.array->length == 0) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    *value                 = rvm_heap_new_object(rvm, RVM_OBJECT_TYPE_STRING);
    RVM_String* dst_string = rvm_deep_copy_string(rvm, &(object->u.array->u.string_array[--object->u.array->length]));
    (*value)->u.string     = dst_string; // FIXME: 这里内存泄漏了
    return ERROR_CODE_SUCCESS;
}

ErrorCode rvm_array_get_class_object(Ring_VirtualMachine* rvm, RVM_Object* object, int index, RVM_Object** value) {
    if (index >= object->u.array->length) {
        return RUNTIME_ERR_OUT_OF_ARRAY_RANGE;
    }
    RVM_ClassObject* src_class_object = &(object->u.array->u.class_object_array[index]);

    RVM_Object*      new_object       = rvm_heap_new_object(rvm, RVM_OBJECT_TYPE_CLASS);

    RVM_ClassObject* dst_class_object = rvm_deep_copy_class_object(rvm, src_class_object);

    new_object->u.class_object        = dst_class_object; // FIXME: 这里内存泄漏了
    *value                            = new_object;
    return ERROR_CODE_SUCCESS;
}

RVM_Object* rvm_heap_new_object(Ring_VirtualMachine* rvm, RVM_Object_Type type) {
    assert(rvm != nullptr);
    assert(rvm->runtime_heap != nullptr);

    RVM_Object* object = (RVM_Object*)malloc(sizeof(RVM_Object));
    object->type       = type;
    object->gc_mark    = GC_MARK_COLOR_WHITE;
    object->prev       = nullptr;
    object->next       = nullptr;

    // add to list
    RVM_Object* head   = rvm->runtime_heap->list;
    object->next       = head;
    if (head != nullptr) {
        head->prev = object;
    }
    rvm->runtime_heap->list = object;

    switch (type) {
    case RVM_OBJECT_TYPE_STRING:
        object->u.string = rvm_heap_new_string(rvm);
        break;
    case RVM_OBJECT_TYPE_ARRAY:
        object->u.array = rvm_heap_new_array(rvm);
        break;
    case RVM_OBJECT_TYPE_CLASS:
        object->u.class_object = rvm_heap_new_class_object(rvm);
        break;
    default:
        // TODO: error report
        break;
    }

    return object;
}

RVM_Object* rvm_deep_copy_object(Ring_VirtualMachine* rvm, RVM_Object* src) {
    assert(rvm != nullptr);
    assert(rvm->runtime_heap != nullptr);

    RVM_Object* object = (RVM_Object*)malloc(sizeof(RVM_Object));
    object->type       = src->type;
    object->gc_mark    = GC_MARK_COLOR_WHITE;
    object->prev       = nullptr;
    object->next       = nullptr;

    // add to list
    RVM_Object* head   = rvm->runtime_heap->list;
    object->next       = head;
    if (head != nullptr) {
        head->prev = object;
    }
    rvm->runtime_heap->list = object;

    switch (src->type) {
    case RVM_OBJECT_TYPE_STRING:
        object->u.string = rvm_deep_copy_string(rvm, src->u.string);
        break;
    case RVM_OBJECT_TYPE_ARRAY:
        object->u.array = rvm_deep_copy_array(rvm, src->u.array);
        break;
    case RVM_OBJECT_TYPE_CLASS:
        object->u.class_object = rvm_deep_copy_class_object(rvm, src->u.class_object);
        break;
    default:
        // TODO: error report
        break;
    }

    return object;
}

RVM_Object* rvm_heap_new_object_from_string(Ring_VirtualMachine* rvm, RVM_String* str) {
    assert(rvm != nullptr);
    assert(rvm->runtime_heap != nullptr);

    RVM_Object* object = (RVM_Object*)malloc(sizeof(RVM_Object));
    object->type       = RVM_OBJECT_TYPE_STRING;
    object->gc_mark    = GC_MARK_COLOR_WHITE;
    object->prev       = nullptr;
    object->next       = nullptr;

    // add to list
    RVM_Object* head   = rvm->runtime_heap->list;
    object->next       = head;
    if (head != nullptr) {
        head->prev = object;
    }
    rvm->runtime_heap->list = object;

    object->u.string        = str;

    return object;
}

RVM_String* rvm_heap_new_string(Ring_VirtualMachine* rvm) {
    RVM_String* string = (RVM_String*)malloc(sizeof(RVM_String));
    string->length     = 0;
    string->capacity   = 0;
    string->data       = nullptr;
    return string;
}

RVM_String* rvm_deep_copy_string(Ring_VirtualMachine* rvm, RVM_String* src) {
    RVM_String* string = (RVM_String*)malloc(sizeof(RVM_String));
    string->length     = src->length;
    string->capacity   = src->capacity;
    string->data       = (char*)malloc(sizeof(char) * src->capacity);
    memcpy(string->data, src->data, src->capacity);

    // TODO: rvm->runtime_heap->size 的变化需要统一一下
    rvm->runtime_heap->alloc_size += sizeof(char) * src->capacity;

    return string;
}

RVM_String* rvm_bool_2_string(Ring_VirtualMachine* rvm, bool value) {
    RVM_String* string = (RVM_String*)malloc(sizeof(RVM_String));
    string->length     = 0;
    string->capacity   = 5;
    string->data       = (char*)malloc(sizeof(char) * string->capacity);
    memset(string->data, 0, string->capacity);
    if (value) {
        string->length = 4;
        strncpy(string->data, "true", 4);
    } else {
        string->length = 5;
        strncpy(string->data, "false", 5);
    }

    // TODO: rvm->runtime_heap->size 的变化需要统一一下
    rvm->runtime_heap->alloc_size += sizeof(char) * string->capacity;

    return string;
}

RVM_String* rvm_int_2_string(Ring_VirtualMachine* rvm, int value) {
    // 这里直接用的 cpp的函数, 是否需要自己实现?
    std::string tmp    = std::to_string(value);

    RVM_String* string = (RVM_String*)malloc(sizeof(RVM_String));
    string->length     = tmp.size();
    string->capacity   = tmp.size();
    string->data       = (char*)malloc(sizeof(char) * string->capacity);

    strncpy(string->data, tmp.c_str(), tmp.size());

    // TODO: rvm->runtime_heap->size 的变化需要统一一下
    rvm->runtime_heap->alloc_size += sizeof(char) * string->capacity;

    return string;
}

RVM_String* rvm_double_2_string(Ring_VirtualMachine* rvm, double value) {
    // 这里直接用的 cpp的函数, 是否需要自己实现?
    std::string tmp    = std::to_string(value);

    RVM_String* string = (RVM_String*)malloc(sizeof(RVM_String));
    string->length     = tmp.size();
    string->capacity   = tmp.size();
    string->data       = (char*)malloc(sizeof(char) * string->capacity);

    strncpy(string->data, tmp.c_str(), tmp.size());

    // TODO: rvm->runtime_heap->size 的变化需要统一一下
    rvm->runtime_heap->alloc_size += sizeof(char) * string->capacity;

    return string;
}


RVM_Array* rvm_heap_new_array(Ring_VirtualMachine* rvm) {
    RVM_Array* array      = (RVM_Array*)malloc(sizeof(RVM_Array));
    array->type           = RVM_ARRAY_UNKNOW;
    array->length         = 0;
    array->capacity       = 0;
    array->u.int_array    = nullptr;
    array->u.double_array = nullptr;
    return array;
}

RVM_Array* rvm_deep_copy_array(Ring_VirtualMachine* rvm, RVM_Array* src) {
    RVM_Array* array = (RVM_Array*)malloc(sizeof(RVM_Array));
    array->type      = src->type;
    array->length    = src->length;
    array->capacity  = src->capacity;

    switch (src->type) {
    case RVM_ARRAY_BOOL:
        array->u.bool_array = (bool*)malloc(sizeof(bool) * array->capacity);

        rvm->runtime_heap->alloc_size += sizeof(bool) * array->capacity;
        // TODO: 这样写有点丑, 优化一下
        memcpy(array->u.bool_array, src->u.bool_array, sizeof(bool) * src->capacity);
        break;

    case RVM_ARRAY_INT:
        array->u.int_array = (int*)malloc(sizeof(int) * array->capacity);

        rvm->runtime_heap->alloc_size += sizeof(int) * array->capacity;
        // TODO: 这样写有点丑, 优化一下
        memcpy(array->u.int_array, src->u.int_array, sizeof(int) * src->capacity);
        break;

    case RVM_ARRAY_DOUBLE:
        array->u.double_array = (double*)malloc(sizeof(double) * array->capacity);

        rvm->runtime_heap->alloc_size += sizeof(double) * array->capacity;

        // TODO: 这样写有点丑, 优化一下
        memcpy(array->u.double_array, src->u.double_array, sizeof(double) * src->capacity);
        break;

    case RVM_ARRAY_STRING:
        array->u.string_array = (RVM_String*)malloc(sizeof(RVM_String) * array->capacity);

        rvm->runtime_heap->alloc_size += sizeof(RVM_String) * array->capacity;
        // FIXME:
        // This is not deep copy string.
        // TODO: 这样写有点丑, 优化一下
        memcpy(array->u.string_array, src->u.string_array, sizeof(RVM_String) * array->capacity);
        break;

    case RVM_ARRAY_OBJECT: {
        array->u.class_object_array = (RVM_ClassObject*)malloc(sizeof(RVM_ClassObject) * array->capacity);
        rvm->runtime_heap->alloc_size += 0;

        for (int i = 0; i < src->length; i++) {
            RVM_ClassObject* tmp                       = rvm_deep_copy_class_object(rvm, &(src->u.class_object_array[i]));
            // TODO: 这里的写法不太好, 还是直接 strcpy 的那种形式最好, 结果通过 指针传入
            array->u.class_object_array[i].class_def   = tmp->class_def;
            array->u.class_object_array[i].field_count = tmp->field_count;
            array->u.class_object_array[i].field       = tmp->field;
        }

    } break;

    default:
        break;
    }

    return array;
}

RVM_ClassObject* rvm_heap_new_class_object(Ring_VirtualMachine* rvm) {
    RVM_ClassObject* class_object = (RVM_ClassObject*)malloc(sizeof(RVM_ClassObject));
    class_object->class_def       = nullptr;
    class_object->field_count     = 0;
    class_object->field           = nullptr;
    return class_object;
}

RVM_ClassObject* rvm_deep_copy_class_object(Ring_VirtualMachine* rvm, RVM_ClassObject* src) {
    RVM_ClassObject* class_object = (RVM_ClassObject*)malloc(sizeof(RVM_ClassObject));
    class_object->class_def       = src->class_def;
    class_object->field_count     = src->field_count;

    // FIXME: 这里还要继续完善深度copy
    RVM_Value* field              = nullptr;
    field                         = (RVM_Value*)malloc(src->field_count * sizeof(RVM_Value));
    memcpy(field, src->field, src->field_count * sizeof(RVM_Value));
    class_object->field = field;
    return class_object;
}


// TODO: 这里实现的有点过于复杂了, 后续优化
int rvm_string_cmp(RVM_Object* object1, RVM_Object* object2) {
    char*        str1     = nullptr;
    char*        str2     = nullptr;
    unsigned int str1_len = 0;
    unsigned int str2_len = 0;

    if (object1 != nullptr) {
        if (object1->u.string != nullptr) {
            str1     = object1->u.string->data;
            str1_len = object1->u.string->length;
        }
    }
    if (object2 != nullptr) {
        if (object2->u.string != nullptr) {
            str2     = object2->u.string->data;
            str2_len = object2->u.string->length;
        }
    }

    if (str1_len == 0 && str2_len == 0) {
        return 0;
    } else if (str1_len == 0 && str2_len != 0) {
        return -1;
    } else if (str1_len != 0 && str2_len == 0) {
        return 1;
    }

    return strcmp(str1, str2);
}

// 这里下边统一放 heap 分配内存相关
// 上边内存分配的都要 delete

/*
 * 释放 object 的内存空间，
 * 但是不会删除 heap list.
 */
void rvm_free_object(Ring_VirtualMachine* rvm, RVM_Object* object) {
    assert(object != nullptr);

    unsigned int free_size = 0;
    switch (object->type) {
    case RVM_OBJECT_TYPE_STRING:
        free_size = rvm_free_string(rvm, object->u.string);
        break;
    case RVM_OBJECT_TYPE_ARRAY:
        free_size = rvm_free_array(rvm, object->u.array);
        break;
    case RVM_OBJECT_TYPE_CLASS:
        free_size = rvm_free_class_object(rvm, object->u.class_object);
        break;
    default:
        break;
    }

    rvm->runtime_heap->alloc_size -= free_size;

    if (object->prev != nullptr) {
        object->prev->next = object->next;
    }
    if (object->next != nullptr) {
        object->next->prev = object->prev;
    }
    // new head
    if (object->prev == nullptr) {
        rvm->runtime_heap->list = object->next;
    }

    free(object);
}

unsigned int rvm_free_string(Ring_VirtualMachine* rvm, RVM_String* string) {
    assert(string != nullptr);

    if (string->data != nullptr) {
        free(string->data);
    }
    unsigned int free_size = string->capacity * sizeof(char);
    free(string);
    return free_size;
}

unsigned int rvm_free_array(Ring_VirtualMachine* rvm, RVM_Array* array) {
    assert(array != nullptr);

    unsigned int free_size = 0;

    switch (array->type) {
    case RVM_ARRAY_BOOL:
        if (array->u.bool_array != nullptr) {
            free(array->u.bool_array);
            free_size = array->capacity * sizeof(bool);
        }
        break;
    case RVM_ARRAY_INT:
        if (array->u.int_array != nullptr) {
            free(array->u.int_array);
            free_size = array->capacity * sizeof(int);
        }
        break;
    case RVM_ARRAY_DOUBLE:
        if (array->u.double_array != nullptr) {
            free(array->u.double_array);
            free_size = array->capacity * sizeof(double);
        }
        break;
    default:
        break;
    }

    free(array);
    return free_size;
}

unsigned int rvm_free_class_object(Ring_VirtualMachine* rvm, RVM_ClassObject* class_object) {
    unsigned int free_size = 0;

    if (class_object->field != nullptr) {
        free(class_object->field);
    }
    free_size = class_object->field_count * sizeof(RVM_Value);
    free(class_object);
    return free_size;
}


// 这里下边统一放 heap 分配内存相关
// 上边内存分配的都要 delete

int rvm_heap_size(Ring_VirtualMachine* rvm) {
    // FIXME: 这里会溢出
    // TODO: 数据类型不够
    return rvm->runtime_heap->alloc_size;
}

void debug_rvm(Ring_VirtualMachine* rvm, RVM_Function* function, RVM_Byte* code_list, unsigned int code_size, unsigned int pc, unsigned int caller_stack_base) {
    debug_log_with_white_coloar("\t");

    if (rvm->debug_config == nullptr) {
        rvm->debug_config             = (RVM_DebugConfig*)malloc(sizeof(RVM_DebugConfig));
        rvm->debug_config->debug_mode = RVM_DEBUG_MODE_UNKNOW;
    }

    // get terminal windows size
    struct winsize terminal_size;
    if (isatty(STDOUT_FILENO) == 0 || ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminal_size) < 0) {
        runtime_err_log("ioctl TIOCGWINSZ error");
        exit(1);
    }

    if (terminal_size.ws_row < 38 || terminal_size.ws_col < 115) {
        runtime_err_log("In Debug RVM Mode:");
        runtime_err_log("    Please adjust current terminal window size: height > 38, width > 115\n");
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
    if (ch == 'i') {
        rvm->debug_config->debug_mode = RVM_DEBUG_MODE_STEPINTO;
    } else if (ch == 'v') {
        rvm->debug_config->debug_mode = RVM_DEBUG_MODE_STEPOVER;
    } else if (ch == 'o') {
        rvm->debug_config->debug_mode = RVM_DEBUG_MODE_STEPOUT;
    } else if (ch == 'q') {
        exit(1);
    }
}