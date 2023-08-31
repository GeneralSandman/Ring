#include "ring.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

extern RVM_Opcode_Info RVM_Opcode_Infos[];


// 通过绝对索引 获取
#define STACK_GET_BOOL_INDEX(rvm, index) \
    ((rvm)->runtime_stack->data[(index)].u.bool_value)
#define STACK_GET_INT_INDEX(rvm, index) \
    ((rvm)->runtime_stack->data[(index)].u.int_value)
#define STACK_GET_DOUBLE_INDEX(rvm, index) \
    ((rvm)->runtime_stack->data[(index)].u.double_value)
#define STACK_GET_OBJECT_INDEX(rvm, index) \
    ((rvm)->runtime_stack->data[(index)].u.object)

// 通过栈顶偏移 offset 获取
#define STACK_GET_BOOL_OFFSET(rvm, offset) \
    STACK_GET_BOOL_INDEX((rvm), (rvm)->runtime_stack->top_index + (offset))
#define STACK_GET_INT_OFFSET(rvm, offset) \
    STACK_GET_INT_INDEX((rvm), (rvm)->runtime_stack->top_index + (offset))
#define STACK_GET_DOUBLE_OFFSET(rvm, offset) \
    STACK_GET_DOUBLE_INDEX((rvm), (rvm)->runtime_stack->top_index + (offset))
#define STACK_GET_OBJECT_OFFSET(rvm, offset) \
    STACK_GET_OBJECT_INDEX((rvm), (rvm)->runtime_stack->top_index + (offset))

// 通过绝对索引 设置
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

// 通过栈顶偏移 offset 设置
#define STACK_SET_BOOL_OFFSET(rvm, offset, value) \
    STACK_SET_BOOL_INDEX(rvm, (rvm)->runtime_stack->top_index + (offset), (value))
#define STACK_SET_INT_OFFSET(rvm, offset, value) \
    STACK_SET_INT_INDEX(rvm, (rvm)->runtime_stack->top_index + (offset), (value))
#define STACK_SET_DOUBLE_OFFSET(rvm, offset, value) \
    STACK_SET_DOUBLE_INDEX(rvm, (rvm)->runtime_stack->top_index + (offset), (value))
#define STACK_SET_OBJECT_OFFSET(rvm, offset, value) \
    STACK_SET_OBJECT_INDEX(rvm, (rvm)->runtime_stack->top_index + (offset), (value))


#define STACK_COPY_INDEX(rvm, src_index, dest_index) \
    ((rvm)->runtime_stack->data[(dest_index)] = (rvm)->runtime_stack->data[(src_index)])

#define STACK_COPY_OFFSET(rvm, src_offset, dest_offset) \
    STACK_COPY_INDEX((rvm), (rvm)->runtime_stack->top_index + (src_offset), (rvm)->runtime_stack->top_index + (dest_offset))

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
    runtime_heap->size            = 0;
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
 * 做好执行虚拟机代码的初始化
 * 对全局变量进行初始化
 * 对运行栈做初始化
 */
void ring_virtualmachine_init(Ring_VirtualMachine* rvm) {
    rvm_init_static_variable(rvm->executer, rvm->runtime_static);
}

void rvm_add_static_variable(Package_Executer* executer, RVM_RuntimeStatic* runtime_static) {
    debug_log_with_white_coloar("\t");

    // 分配空间
    unsigned int size    = executer->global_variable_size;
    runtime_static->size = size;
    runtime_static->data = (RVM_Value*)malloc(size * sizeof(RVM_Value));
}

void rvm_init_static_variable(Package_Executer* executer, RVM_RuntimeStatic* runtime_static) {
    debug_log_with_white_coloar("\t");

    // 初始化默认值
    // 如果有初始化表达式的话，那就通过表达式来初始化

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
            memset(&runtime_static->data[i], 0, sizeof(RVM_Value));
            // TODO: 临时处理一下 int[]
            if (type_specifier->kind == RING_BASIC_TYPE_ARRAY) {
                runtime_static->data[i].u.object = rvm_new_array_int(nullptr, 10);
            }
            break;
        case RING_BASIC_TYPE_CLASS:
            // Search class-definition from variable declaration.
            assert(type_specifier->u.class_type != nullptr);
            class_definition                 = type_specifier->u.class_type->class_definition;
            runtime_static->data[i].u.object = new_class_object(class_definition);
            break;

        default:
            break;
        }
    }
}

RVM_Object* new_class_object(ClassDefinition* class_definition) {
    assert(class_definition != nullptr);

    // Search field-member's size and detail from class-definition.
    // Alloc and Init.
    unsigned int field_count = 0;
    RVM_Value*   field       = (RVM_Value*)malloc(field_count * sizeof(RVM_Value));

    // TODO: 先用笨办法
    for (ClassMemberDeclaration* pos = class_definition->member; pos != nullptr; pos = pos->next) {
        if (pos->type == MEMBER_FIELD) {
            field_count++;
        }
    }
    field                               = (RVM_Value*)malloc(field_count * sizeof(RVM_Value));

    RVM_Object* object                  = (RVM_Object*)malloc(sizeof(RVM_Object));
    object->type                        = RVM_OBJECT_TYPE_CLASS;
    object->u.class_object              = (RVM_ClassObject*)malloc(sizeof(RVM_ClassObject));
    object->u.class_object->class_def   = class_definition;
    object->u.class_object->field_count = field_count;
    object->u.class_object->field       = field;

    memset(field, 0, field_count * sizeof(RVM_Value));


    // TODO:
    // if class has constructor method, invoke it.

    return object;
}

void ring_execute_vm_code(Ring_VirtualMachine* rvm) {
    debug_log_with_white_coloar("\t");

    RVM_Byte*          code_list              = rvm->executer->code_list;
    unsigned int       code_size              = rvm->executer->code_size;
    RVM_ConstantPool*  const_pool_list        = rvm->executer->constant_pool_list;
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

    RVM_Function*      function               = nullptr;
    RVM_Object*        object                 = nullptr;

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
            STACK_SET_INT_OFFSET(rvm, 0, const_pool_list[const_index].u.int_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_DOUBLE:
            const_index = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_DOUBLE_OFFSET(rvm, 0, const_pool_list[const_index].u.double_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STRING:
            const_index = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_OBJECT_OFFSET(rvm, 0,
                                    string_literal_to_rvm_object(rvm, const_pool_list[const_index].u.string_value));
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
            runtime_static->data[index].u.object = STACK_GET_OBJECT_OFFSET(rvm, -1);
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
            STACK_SET_OBJECT_INDEX(rvm, caller_stack_base + caller_stack_offset, STACK_GET_OBJECT_OFFSET(rvm, -1));
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
        case RVM_CODE_PUSH_ARRAY_INT: {
            object    = STACK_GET_OBJECT_OFFSET(rvm, -2);
            index     = STACK_GET_INT_OFFSET(rvm, -1);
            int value = 0;
            rvm_array_get_int(rvm, object, index, &value);
            runtime_stack->top_index -= 2;
            STACK_SET_INT_OFFSET(rvm, 0, value);
            runtime_stack->top_index++;
            rvm->pc += 1;
        } break;
        case RVM_CODE_PUSH_ARRAY_DOUBLE: {
            object       = STACK_GET_OBJECT_OFFSET(rvm, -2);
            index        = STACK_GET_INT_OFFSET(rvm, -1);
            double value = 0;
            rvm_array_get_double(rvm, object, index, &value);
            runtime_stack->top_index -= 2;
            STACK_SET_DOUBLE_OFFSET(rvm, 0, value);
            runtime_stack->top_index++;
            rvm->pc += 1;
        } break;
        case RVM_CODE_PUSH_ARRAY_OBJECT:
            break;

        // class
        case RVM_CODE_POP_FIELD_BOOL:
            object                                               = STACK_GET_OBJECT_OFFSET(rvm, -1);
            oper_num                                             = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            object->u.class_object->field[oper_num].u.bool_value = STACK_GET_BOOL_OFFSET(rvm, -2);
            runtime_stack->top_index -= 2;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_FIELD_INT:
            object                                              = STACK_GET_OBJECT_OFFSET(rvm, -1);
            oper_num                                            = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            object->u.class_object->field[oper_num].u.int_value = STACK_GET_INT_OFFSET(rvm, -2);
            runtime_stack->top_index -= 2;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_FIELD_DOUBLE:
            object                                                 = STACK_GET_OBJECT_OFFSET(rvm, -1);
            oper_num                                               = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            object->u.class_object->field[oper_num].u.double_value = STACK_GET_DOUBLE_OFFSET(rvm, -2);
            runtime_stack->top_index -= 2;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_FIELD_BOOL:
            object   = STACK_GET_OBJECT_OFFSET(rvm, -1);
            oper_num = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_BOOL_OFFSET(rvm, -1, object->u.class_object->field[oper_num].u.bool_value);
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_FIELD_INT:
            object   = STACK_GET_OBJECT_OFFSET(rvm, -1);
            oper_num = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_INT_OFFSET(rvm, -1, object->u.class_object->field[oper_num].u.int_value);
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_FIELD_DOUBLE:
            object   = STACK_GET_OBJECT_OFFSET(rvm, -1);
            oper_num = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_DOUBLE_OFFSET(rvm, -1, object->u.class_object->field[oper_num].u.double_value);
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
        case RVM_CODE_RELATIONAL_EQ_STRING: {
            // RVM_Object* object2 = STACK_GET_OBJECT_OFFSET(rvm, -2);
            // RVM_Object* object1 = STACK_GET_OBJECT_OFFSET(rvm, -1);
            // printf("-----object2:%s-\n", object2->u.string->data);
            // printf("-----object1:%s-\n", object1->u.string->data);
            STACK_GET_BOOL_OFFSET(rvm, -2) = (RVM_Bool)(rvm_string_cmp(STACK_GET_OBJECT_OFFSET(rvm, -2), STACK_GET_OBJECT_OFFSET(rvm, -1)) == 0);
            runtime_stack->top_index--;
            rvm->pc++;
            break;
        }

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
            STACK_GET_INT_OFFSET(rvm, -2) = (strcmp(STACK_GET_OBJECT_OFFSET(rvm, -2)->u.string->data, STACK_GET_OBJECT_OFFSET(rvm, -1)->u.string->data) != 0);
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
            STACK_GET_INT_OFFSET(rvm, -2) = (strcmp(STACK_GET_OBJECT_OFFSET(rvm, -2)->u.string->data, STACK_GET_OBJECT_OFFSET(rvm, -1)->u.string->data) > 0);
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
            STACK_GET_INT_OFFSET(rvm, -2) = (strcmp(STACK_GET_OBJECT_OFFSET(rvm, -2)->u.string->data, STACK_GET_OBJECT_OFFSET(rvm, -1)->u.string->data) >= 0);
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
            STACK_GET_INT_OFFSET(rvm, -2) = (strcmp(STACK_GET_OBJECT_OFFSET(rvm, -2)->u.string->data, STACK_GET_OBJECT_OFFSET(rvm, -1)->u.string->data) < 0);
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
            STACK_GET_INT_OFFSET(rvm, -2) = (strcmp(STACK_GET_OBJECT_OFFSET(rvm, -2)->u.string->data, STACK_GET_OBJECT_OFFSET(rvm, -1)->u.string->data) <= 0);
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
            STACK_COPY_OFFSET(rvm, -1, 0);
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
                invoke_native_function(rvm, &rvm->executer_entry->package_executer_list[package_index]->function_list[func_index], argument_list_size);
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
            object       = STACK_GET_OBJECT_OFFSET(rvm, -2);
            runtime_stack->top_index -= 2;
            // FIXME: object->u.class_object->class_def->class_index 这样使用是不对的
            invoke_derive_function(rvm,
                                   &function, rvm->class_list[object->u.class_object->class_def->class_index].method_list[method_index].rvm_function,
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
        case RVM_CODE_NEW_ARRAY_INT:
            oper_num = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            object   = rvm_new_array_int(rvm, oper_num);
            STACK_SET_OBJECT_OFFSET(rvm, 0, object);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_NEW_ARRAY_DOUBLE:
            oper_num = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            object   = rvm_new_array_double(rvm, oper_num);
            STACK_SET_OBJECT_OFFSET(rvm, 0, object);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_NEW_ARRAY_OBJECT:
            break;
        case RVM_CODE_NEW_ARRAY_LITERAL_INT: {
            int size = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            object   = rvm_new_array_literal_int(rvm, size);
            runtime_stack->top_index -= size;
            STACK_SET_OBJECT_OFFSET(rvm, 0, object);
            runtime_stack->top_index++;
            rvm->pc += 3;
        } break;
        case RVM_CODE_NEW_ARRAY_LITERAL_DOUBLE: {
            int size = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            object   = rvm_new_array_literal_double(rvm, size);
            runtime_stack->top_index -= size;
            STACK_SET_OBJECT_OFFSET(rvm, 0, object);
            runtime_stack->top_index++;
            rvm->pc += 3;
        } break;
        case RVM_CODE_NEW_ARRAY_LITERAL_OBJECT:
            rvm->pc += 3;
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

    RVM_NativeFuncProc* native_func_proc = function->u.native_func->func_proc;
    // unsigned int        arg_count        = function->u.native_func->arg_count;
    RVM_Value*          args; // TODO:

    // TODO: how to handle arg_count > 1
    args = &rvm->runtime_stack->data[rvm->runtime_stack->top_index - argument_list_size];

    ret  = native_func_proc(rvm, argument_list_size, args);


    rvm->runtime_stack->top_index -= argument_list_size;
    rvm->runtime_stack->data[rvm->runtime_stack->top_index] = ret;
}

// invoke_derive_function
// 1. store call info
//      call info: - caller_function
//                 - caller_pc
// - callee_stack_base
// 2. expan runtime stack
// 3. change
//          caller_function
//          vm code_list
//          vm code_size
//          pc
//          caller_stack_base
// 3. change vm code to callee
// 4. change pc
void invoke_derive_function(Ring_VirtualMachine* rvm,
                            RVM_Function** caller_function, RVM_Function* callee_function,
                            RVM_Byte** code_list, unsigned int* code_size,
                            unsigned int* pc,
                            unsigned int* caller_stack_base) {
    debug_log_with_white_coloar("\t");

    // FIXME:
    /* unsigned int arguement_count = 0; */

    RVM_CallInfo callinfo;
    callinfo.magic_number         = CALL_INFO_MAGIC_NUMBER;
    callinfo.caller_function      = *caller_function;
    callinfo.caller_pc            = *pc;
    callinfo.caller_stack_base    = *caller_stack_base;
    callinfo.callee_argument_size = callee_function->parameter_size; // FIXME: 支持可变参数
    store_callinfo(rvm->runtime_stack, &callinfo);


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

// derive_function_finish
// 1. restore call info
//      call info: caller_pc
// 3. change vm code to callee
// 4. change pc
void derive_function_finish(Ring_VirtualMachine* rvm,
                            RVM_Function** caller_function, RVM_Function* callee_function,
                            RVM_Byte** code_list, unsigned int* code_size,
                            unsigned int* pc,
                            unsigned int* caller_stack_base,
                            unsigned int  return_value_list_size) {
    debug_log_with_white_coloar("\t");

    unsigned int old_return_value_list_index;

    rvm->runtime_stack->top_index -= return_value_list_size;
    old_return_value_list_index = rvm->runtime_stack->top_index;


    RVM_CallInfo* callinfo;
    // FIXME: local_variable_size
    unsigned int  local_variable_size = 20;
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

// FIXME:  初始化局部变量列表的时候存在问题
// 如果局部变量是个数组
void init_derive_function_local_variable(Ring_VirtualMachine* rvm, RVM_Function* function) {
    debug_log_with_white_coloar("\t");

    // FIXME: 先忽略局部变量的类型，先用int
    unsigned int arguement_list_size        = function->parameter_size;
    unsigned int arguement_list_index       = rvm->runtime_stack->top_index - CALL_INFO_SIZE - arguement_list_size;

    // 通过实参 来初始化形参
    // init argument with parameter
    unsigned int local_variable_value_index = 0;
    for (; local_variable_value_index < arguement_list_size; local_variable_value_index++) {
        STACK_COPY_INDEX(rvm, arguement_list_index + local_variable_value_index, rvm->runtime_stack->top_index + local_variable_value_index);
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
        case RING_BASIC_TYPE_DOUBLE:
            break;
        case RING_BASIC_TYPE_STRING:
            object = rvm_heap_new_object(rvm, RVM_OBJECT_TYPE_STRING);
            STACK_SET_OBJECT_INDEX(rvm, rvm->runtime_stack->top_index + local_variable_value_index, object);
            break;
        case RING_BASIC_TYPE_CLASS:
            // Search class-definition from variable declaration.
            assert(type_specifier->u.class_type != nullptr);
            class_definition = type_specifier->u.class_type->class_definition;
            object           = new_class_object(class_definition);
            STACK_SET_OBJECT_INDEX(rvm, rvm->runtime_stack->top_index + local_variable_value_index, object);
            break;

        default:
            break;
        }
    }
}

RVM_Object* create_rvm_object() {
    RVM_Object* object = (RVM_Object*)malloc(sizeof(RVM_Object));
    return object;
}

RVM_Object* string_literal_to_rvm_object(Ring_VirtualMachine* rvm, char* string_literal) {
    RVM_Object* object = create_rvm_object();
    object->type       = RVM_OBJECT_TYPE_STRING;
    object->u.string   = rvm_new_string(rvm, string_literal);
    return object;
}

RVM_Object* concat_string(Ring_VirtualMachine* rvm, RVM_Object* a, RVM_Object* b) {
    RVM_Object* object = create_rvm_object();
    object->type       = RVM_OBJECT_TYPE_STRING;
    object->u.string   = rvm_concat_new_string(rvm, a->u.string, b->u.string);
    return object;
}

// store_callinfo
// encode callinfo to runtime_stack
// increase runtime_stack top_index
void store_callinfo(RVM_RuntimeStack* runtime_stack, RVM_CallInfo* callinfo) {
    RVM_CallInfo* dest;
    dest = (RVM_CallInfo*)(&runtime_stack->data[runtime_stack->top_index]);
    memcpy(dest, callinfo, sizeof(RVM_CallInfo));
    runtime_stack->top_index += CALL_INFO_SIZE;
}

// restore_callinfo
// decode callinfo from runtime_stack
// decrease runtime_stack top_index
void restore_callinfo(RVM_RuntimeStack* runtime_stack, RVM_CallInfo** callinfo) {
    runtime_stack->top_index -= CALL_INFO_SIZE;
    *callinfo = (RVM_CallInfo*)(&runtime_stack->data[runtime_stack->top_index]);
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
        exit(1);
    }

    CLEAR_SCREEN;
    ring_vm_dump_runtime_stack(rvm->runtime_stack, caller_stack_base, 1, 0);
    ring_vm_code_dump(function, code_list, code_size, pc, 1, 60);

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

RVM_Value native_proc_exit(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    debug_log_with_white_coloar("\t");

    RVM_Value ret;

    ret.u.int_value = 0;


    if (arg_count != 1) {
        printf("native_proc_exit only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    // TODO: 暂时只打印int, 以后都强制转换成int_value
    exit(args->u.int_value);

    return ret;
}

// create array in heap
// support create one-dimensional array only.
// TODO: support multi-dimensional array
RVM_Object* rvm_new_array_int(Ring_VirtualMachine* rvm, unsigned int dimension) {
    RVM_Object* object           = (RVM_Object*)malloc(sizeof(RVM_Object));
    object->type                 = RVM_OBJECT_TYPE_ARRAY;
    object->u.array              = (RVM_Array*)malloc(sizeof(RVM_Array));
    object->u.array->type        = RVM_ARRAY_INT;
    object->u.array->size        = dimension;
    object->u.array->capacity    = dimension;
    object->u.array->u.int_array = (int*)malloc(sizeof(int) * dimension);
    return object;
}

// create array in heap
// support create one-dimensional array only.
// TODO: support multi-dimensional array
RVM_Object* rvm_new_array_double(Ring_VirtualMachine* rvm, unsigned int dimension) {
    RVM_Object* object              = (RVM_Object*)malloc(sizeof(RVM_Object));
    object->type                    = RVM_OBJECT_TYPE_ARRAY;
    object->u.array                 = (RVM_Array*)malloc(sizeof(RVM_Array));
    object->u.array->type           = RVM_ARRAY_DOUBLE;
    object->u.array->size           = dimension;
    object->u.array->capacity       = dimension;
    object->u.array->u.double_array = (double*)malloc(sizeof(double) * dimension);
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

void rvm_array_get_int(Ring_VirtualMachine* rvm, RVM_Object* object, int index, int* value) {
    *value = object->u.array->u.int_array[index];
}

void rvm_array_get_double(Ring_VirtualMachine* rvm, RVM_Object* object, int index, double* value) {
    *value = object->u.array->u.double_array[index];
}

RVM_String* rvm_new_string(Ring_VirtualMachine* rvm, unsigned int size, unsigned int capacity) {
    // TODO: capacity 需要是2的倍数
    RVM_String* string = (RVM_String*)malloc(sizeof(RVM_String));
    string->size       = size;
    string->capacity   = capacity;
    string->data       = nullptr;
    if (size > 0)
        string->data = (char*)malloc(sizeof(char) * size);
    return string;
}

RVM_String* rvm_new_string(Ring_VirtualMachine* rvm, const char* string_literal) {
    // capacity 需要是2的倍数
    size_t      size   = strlen(string_literal);

    RVM_String* string = (RVM_String*)malloc(sizeof(RVM_String));
    string->size       = size;
    string->capacity   = size;
    string->data       = nullptr;
    if (size > 0)
        string->data = (char*)malloc(sizeof(char) * size);

    strncpy(string->data, string_literal, size);

    return string;
}

RVM_String* rvm_concat_new_string(Ring_VirtualMachine* rvm, RVM_String* a, RVM_String* b) {
    size_t size = 0;
    if (a != nullptr) {
        size += a->size;
    }
    if (b != nullptr) {
        size += b->size;
    }

    RVM_String* result = rvm_new_string(rvm, size, size);

    strncpy(result->data, a->data, a->size);
    strncpy(result->data + a->size, b->data, b->size);

    return result;
}

RVM_Object* rvm_heap_new_object(Ring_VirtualMachine* rvm, RVM_Object_Type type) {
    assert(rvm != nullptr);
    assert(rvm->runtime_heap != nullptr);

    RVM_Object* object = (RVM_Object*)realloc(nullptr, sizeof(RVM_Object));
    if (object == nullptr) {
        // TODO:
        // alloc error
    }
    object->type = type;
    object->prev = nullptr;
    object->next = rvm->runtime_heap->list;
    if (rvm->runtime_heap->list != nullptr) {
        rvm->runtime_heap->list->prev = object;
    }

    switch (type) {
    case RVM_OBJECT_TYPE_STRING:
        object->u.string = rvm_heap_new_string(rvm);
        break;
    case RVM_OBJECT_TYPE_ARRAY:
        object->u.array = nullptr;
        break;
    case RVM_OBJECT_TYPE_CLASS:
        object->u.class_object = nullptr;
        break;
    default:
        // TODO: error report
        break;
    }

    return object;
}

RVM_String* rvm_heap_new_string(Ring_VirtualMachine* rvm) {
    RVM_String* string = (RVM_String*)malloc(sizeof(RVM_String));
    string->size       = 0;
    string->capacity   = 0;
    string->data       = nullptr;
    return string;
}

RVM_Array* rvm_heap_new_array(Ring_VirtualMachine* rvm) {
    RVM_Array* array      = (RVM_Array*)malloc(sizeof(RVM_Array));
    array->type           = RVM_ARRAY_UNKNOW;
    array->size           = 0;
    array->capacity       = 0;
    array->u.int_array    = nullptr;
    array->u.double_array = nullptr;
    return array;
}

RVM_ClassObject* rvm_heap_new_class_object(Ring_VirtualMachine* rvm) {
    RVM_ClassObject* class_object = (RVM_ClassObject*)malloc(sizeof(RVM_ClassObject));
    class_object->class_def       = nullptr;
    class_object->field_count     = 0;
    class_object->field           = nullptr;
    return class_object;
}

int rvm_string_cmp(RVM_Object* object1, RVM_Object* object2) {
    char* str1 = nullptr;
    char* str2 = nullptr;
    if (object1 != nullptr) {
        if (object1->u.string != nullptr) {
            str1 = object1->u.string->data;
        }
    }
    if (object2 != nullptr) {
        if (object2->u.string != nullptr) {
            str2 = object2->u.string->data;
        }
    }

    if (str1 == nullptr && str2 == nullptr) {
        return 0;
    } else if (str1 != nullptr && str2 == nullptr) {
        return 1;
    } else if (str1 == nullptr && str2 != nullptr) {
        return -1;
    } else if (str1 != nullptr && str2 != nullptr) {
        return strcmp(str1, str2);
    }
    return 0;
}
