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
void STACK_SET_BOOL_INDEX(Ring_VirtualMachine* rvm, unsigned int index, RVM_Bool value) {
    rvm->runtime_stack->data[index].type         = RVM_VALUE_TYPE_BOOL;
    rvm->runtime_stack->data[index].u.bool_value = value;
}
void STACK_SET_INT_INDEX(Ring_VirtualMachine* rvm, unsigned int index, int value) {
    rvm->runtime_stack->data[index].type        = RVM_VALUE_TYPE_INT;
    rvm->runtime_stack->data[index].u.int_value = value;
}
void STACK_SET_DOUBLE_INDEX(Ring_VirtualMachine* rvm, unsigned int index, double value) {
    rvm->runtime_stack->data[index].type           = RVM_VALUE_TYPE_DOUBLE;
    rvm->runtime_stack->data[index].u.double_value = value;
}
void STACK_SET_OBJECT_INDEX(Ring_VirtualMachine* rvm, unsigned int index, RVM_Object* value) {
    rvm->runtime_stack->data[index].type     = RVM_VALUE_TYPE_STRING;
    rvm->runtime_stack->data[index].u.object = value;
}

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

// 从后边获取 2BYTE的操作数
#define OPCODE_GET_2BYTE(p) \
    (((p)[0] << 8) + (p)[1])
// 把两BYTE的操作数放到后边
#define OPCODE_SET_2BYTE(p, value) \
    (((p)[0] = (value) >> 8), ((p)[1] = value & 0xff))

RVM_RuntimeStack* new_runtime_stack() {
    debug_log_with_white_coloar("\t");

    RVM_RuntimeStack* stack = malloc(sizeof(RVM_RuntimeStack));
    stack->top_index        = 0;
    stack->capacity         = 1024 * 1024; // FIXME: 先开辟一个大的空间
    stack->data             = malloc(stack->capacity * sizeof(RVM_Value));
    stack->size             = 0;
    return stack;
}

RVM_RuntimeStatic* new_runtime_static() {
    debug_log_with_white_coloar("\t");

    RVM_RuntimeStatic* runtime_static = malloc(sizeof(RVM_RuntimeStatic));
    runtime_static->data              = NULL;
    runtime_static->size              = 0;
    return runtime_static;
}

Ring_VirtualMachine* new_ring_virtualmachine(Ring_VirtualMachine_Executer* executer) {
    debug_log_with_white_coloar("\t");

    Ring_VirtualMachine* rvm = malloc(sizeof(Ring_VirtualMachine));
    rvm->executer            = executer;
    rvm->runtime_static      = new_runtime_static();
    rvm->runtime_stack       = new_runtime_stack();
    rvm->pc                  = 0;
    rvm->function_list       = NULL;
    rvm->function_size       = 0;
    rvm->debug_config        = NULL;

    // init something
    rvm_add_static_variable(executer, rvm->runtime_static);
    rvm_register_native_functions(rvm);
    rvm_add_derive_functions(executer, rvm);

    return rvm;
}

void rvm_add_static_variable(Ring_VirtualMachine_Executer* executer, RVM_RuntimeStatic* runtime_static) {
    debug_log_with_white_coloar("\t");

    // 分配空间
    // 初始化默认值

    unsigned int     size                 = executer->global_variable_size;
    RVM_Variable*    global_variable_list = executer->global_variable_list;
    TypeSpecifier*   type_specifier       = NULL;
    ClassDefinition* class_definition     = NULL;

    runtime_static->size = size;
    runtime_static->data = malloc(size * sizeof(RVM_Value));

    for (int i = 0; i < size; i++) {
        type_specifier = global_variable_list[i].type;

        switch (type_specifier->basic_type) {
        case RING_BASIC_TYPE_BOOL:
        case RING_BASIC_TYPE_INT:
        case RING_BASIC_TYPE_DOUBLE:
            memset(&runtime_static->data[i], 0, sizeof(RVM_Value));
            break;
        case RING_BASIC_TYPE_CLASS:
            // Search class-definition from variable declaration.
            assert(type_specifier->derive_type != NULL);
            assert(type_specifier->derive_type->u.class_type != NULL);
            class_definition                 = type_specifier->derive_type->u.class_type->class_definition;
            runtime_static->data[i].u.object = new_class_object(class_definition);
            break;

        default:
            break;
        }
    }
}

RVM_Object* new_class_object(ClassDefinition* class_definition) {
    assert(class_definition != NULL);

    // Search field-member's size and detail from class-definition.
    // Alloc and Init.
    unsigned int field_count = 0;
    RVM_Value*   field       = malloc(field_count * sizeof(RVM_Value));

    // TODO: 先用笨办法
    for (ClassMemberDeclaration* pos = class_definition->member; pos != NULL; pos = pos->next) {
        if (pos->type == MEMBER_FIELD) {
            field_count++;
        }
    }
    field = malloc(field_count * sizeof(RVM_Value));

    RVM_Object* object                 = malloc(sizeof(RVM_Object));
    object->type                       = RVM_OBJECT_TYPE_CLASS;
    object->u.class_object.field_count = field_count;
    object->u.class_object.field       = field;

    memset(field, 0, field_count * sizeof(RVM_Value));


    // TODO:
    // if class has constructor method, invoke it.

    return object;
}

void rvm_add_derive_functions(Ring_VirtualMachine_Executer* executer, Ring_VirtualMachine* rvm) {
    debug_log_with_white_coloar("\t");

    for (int i = 0; i < executer->function_size; i++) {
        RVM_Function function = executer->function_list[i];
        if (function.type == RVM_FUNCTION_TYPE_DERIVE) {
            rvm->function_list = realloc(rvm->function_list, sizeof(RVM_Function) * (rvm->function_size + 1));

            rvm->function_list[rvm->function_size].func_name           = function.func_name;
            rvm->function_list[rvm->function_size].type                = RVM_FUNCTION_TYPE_DERIVE;
            rvm->function_list[rvm->function_size].parameter_size      = function.parameter_size;
            rvm->function_list[rvm->function_size].parameter_list      = function.parameter_list;
            rvm->function_list[rvm->function_size].local_variable_size = function.local_variable_size;
            rvm->function_list[rvm->function_size].local_variable_list = function.local_variable_list;
            rvm->function_list[rvm->function_size].u.derive_func       = function.u.derive_func;

            rvm->function_size++;
        }
    }
}

void ring_execute_vm_code(Ring_VirtualMachine* rvm) {
    debug_log_with_white_coloar("\t");

    RVM_Byte*          code_list       = rvm->executer->code_list;
    unsigned int       code_size       = rvm->executer->code_size;
    RVM_ConstantPool*  const_pool_list = rvm->executer->constant_pool_list;
    RVM_RuntimeStack*  runtime_stack   = rvm->runtime_stack;
    RVM_RuntimeStatic* runtime_static  = rvm->runtime_static;
    unsigned int       opcode_num      = 0;
    /* unsigned int       const_pool_size = rvm->executer->constant_pool_size; */

    unsigned int index                  = 0;
    unsigned int func_index             = 0;
    unsigned int oper_num               = 0;
    unsigned int const_index            = 0;
    unsigned int caller_stack_base      = 0;
    unsigned int argument_list_size     = 0;
    unsigned int caller_stack_offset    = 0;
    unsigned int return_value_list_size = 0;

    RVM_Function* function = NULL;
    RVM_Object*   object   = NULL;

    char* string_buf;

    while (rvm->pc < code_size) {
        RVM_Byte opcode = code_list[rvm->pc];
        // char*    name     = RVM_Opcode_Infos[opcode].name;

#ifdef DEBUG
#ifdef DEBUG_RVM
        debug_rvm(rvm, function, code_list, code_size, rvm->pc, caller_stack_base);
#endif
#endif

        switch (opcode) {
        // int double string const
        case RVM_CODE_PUSH_BOOL:
            STACK_SET_BOOL_OFFSET(rvm, 0, (RVM_Bool)code_list[rvm->pc + 1]);
            runtime_stack->top_index++;
            rvm->pc += 2;
            break;
        case RVM_CODE_PUSH_INT_1BYTE:
            STACK_SET_INT_OFFSET(rvm, 0, code_list[rvm->pc + 1]);
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
                                    string_literal_to_rvm_object(const_pool_list[const_index].u.string_value));
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

        // class
        case RVM_CODE_POP_FIELD_BOOL:
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_FIELD_INT:
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_FIELD_DOUBLE:
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_FIELD_BOOL:
            object   = STACK_GET_OBJECT_OFFSET(rvm, -1);
            oper_num = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_BOOL_OFFSET(rvm, -1, object->u.class_object.field[oper_num].u.bool_value);
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_FIELD_INT:
            object   = STACK_GET_OBJECT_OFFSET(rvm, -1);
            oper_num = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_BOOL_OFFSET(rvm, -1, object->u.class_object.field[oper_num].u.int_value);
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_FIELD_DOUBLE:
            object   = STACK_GET_OBJECT_OFFSET(rvm, -1);
            oper_num = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            STACK_SET_BOOL_OFFSET(rvm, -1, object->u.class_object.field[oper_num].u.double_value);
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
            STACK_SET_OBJECT_OFFSET(rvm, -2, concat_string(STACK_GET_OBJECT_OFFSET(rvm, -2), STACK_GET_OBJECT_OFFSET(rvm, -1)));
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
            STACK_GET_INT_OFFSET(rvm, -2) = (strcmp(STACK_GET_OBJECT_OFFSET(rvm, -2)->u.string.data, STACK_GET_OBJECT_OFFSET(rvm, -1)->u.string.data) == 0);
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
            STACK_GET_INT_OFFSET(rvm, -2) = (strcmp(STACK_GET_OBJECT_OFFSET(rvm, -2)->u.string.data, STACK_GET_OBJECT_OFFSET(rvm, -1)->u.string.data) != 0);
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
            STACK_GET_INT_OFFSET(rvm, -2) = (strcmp(STACK_GET_OBJECT_OFFSET(rvm, -2)->u.string.data, STACK_GET_OBJECT_OFFSET(rvm, -1)->u.string.data) > 0);
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
            STACK_GET_INT_OFFSET(rvm, -2) = (strcmp(STACK_GET_OBJECT_OFFSET(rvm, -2)->u.string.data, STACK_GET_OBJECT_OFFSET(rvm, -1)->u.string.data) >= 0);
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
            STACK_GET_INT_OFFSET(rvm, -2) = (strcmp(STACK_GET_OBJECT_OFFSET(rvm, -2)->u.string.data, STACK_GET_OBJECT_OFFSET(rvm, -1)->u.string.data) < 0);
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
            STACK_GET_INT_OFFSET(rvm, -2) = (strcmp(STACK_GET_OBJECT_OFFSET(rvm, -2)->u.string.data, STACK_GET_OBJECT_OFFSET(rvm, -1)->u.string.data) <= 0);
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
        case RVM_CODE_ARGUMENT_NUM:
            oper_num           = code_list[rvm->pc + 1];
            argument_list_size = oper_num;
            rvm->pc += 2;
            break;
        case RVM_CODE_INVOKE_FUNC:
            func_index = STACK_GET_INT_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            if (rvm->function_list[func_index].type == RVM_FUNCTION_TYPE_NATIVE) {
                invoke_native_function(rvm, &rvm->function_list[func_index], argument_list_size);
                rvm->pc += 1;
            } else if (rvm->function_list[func_index].type == RVM_FUNCTION_TYPE_DERIVE) {
                invoke_derive_function(rvm,
                                       &function, &rvm->function_list[func_index],
                                       &code_list, &code_size,
                                       &rvm->pc,
                                       &caller_stack_base);
            }
            break;
        case RVM_CODE_RETURN:
            return_value_list_size = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            rvm->pc += 3;
            // break; // ATTEN: no need break
        case RVM_CODE_FUNCTION_FINISH:
            derive_function_finish(rvm,
                                   &function, NULL,
                                   &code_list, &code_size,
                                   &rvm->pc, &caller_stack_base, return_value_list_size);
            return_value_list_size = 0;
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

        opcode_num++;
    }

#ifdef DEBUG
#ifdef DEBUG_RVM
    debug_rvm(rvm, function, code_list, code_size, rvm->pc, caller_stack_base);
#endif
#endif
}


void invoke_native_function(Ring_VirtualMachine* rvm, RVM_Function* function, unsigned int argument_list_size) {
    debug_log_with_white_coloar("\t");

    RVM_Value ret;

    RVM_NativeFuncProc* native_func_proc = function->u.native_func->func_proc;
    unsigned int        arg_count        = function->u.native_func->arg_count;
    RVM_Value*          args; // TODO:

    // TODO: how to handle arg_count > 1
    args = &rvm->runtime_stack->data[rvm->runtime_stack->top_index - argument_list_size];

    ret = native_func_proc(rvm, argument_list_size, args);


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
    unsigned int local_variable_size = 44;
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
    unsigned int local_variable_size = 44;
    rvm->runtime_stack->top_index -= local_variable_size;

    restore_callinfo(rvm->runtime_stack, &callinfo);
    assert(callinfo->magic_number == CALL_INFO_MAGIC_NUMBER);
    *caller_function   = callinfo->caller_function;
    *pc                = callinfo->caller_pc + 1;
    *caller_stack_base = callinfo->caller_stack_base;
    if (*caller_function == NULL) {
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

void init_derive_function_local_variable(Ring_VirtualMachine* rvm, RVM_Function* function) {
    debug_log_with_white_coloar("\t");

    // FIXME: 先忽略局部变量的类型，先用int
    unsigned int arguement_list_size  = function->parameter_size;
    unsigned int arguement_list_index = rvm->runtime_stack->top_index - CALL_INFO_SIZE - arguement_list_size;

    for (int i = 0; i < arguement_list_size; i++) {
        STACK_COPY_INDEX(rvm, arguement_list_index + i, rvm->runtime_stack->top_index + i);
    }
}

RVM_Object* create_rvm_object() {
    RVM_Object* object = malloc(sizeof(RVM_Object));
    return object;
}

RVM_Object* string_literal_to_rvm_object(char* string_literal) {
    RVM_Object* object    = create_rvm_object();
    object->type          = RVM_OBJECT_TYPE_STRING;
    object->u.string.data = string_literal;
    return object;
}

RVM_Object* concat_string(RVM_Object* a, RVM_Object* b) {
    char*        left       = NULL;
    char*        right      = NULL;
    char*        result     = NULL;
    unsigned int result_len = 0;

    if (a != NULL) {
        left = a->u.string.data;
    }
    if (b != NULL) {
        right = b->u.string.data;
    }

    result_len = strlen(left) + strlen(right);
    result     = malloc(sizeof(char) * (result_len + 1));

    strcpy(result, left);
    strcpy(result + strlen(left), right);

    RVM_Object* object    = create_rvm_object();
    object->type          = RVM_OBJECT_TYPE_STRING;
    object->u.string.data = result;
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

    if (rvm->debug_config == NULL) {
        rvm->debug_config             = malloc(sizeof(RVM_DebugConfig));
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


RVM_Value native_proc_println_bool(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    debug_log_with_white_coloar("\t");

    if (arg_count != 1) {
        printf("native_proc_print only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    RVM_Value ret;
    ret.u.int_value = 0;

    if (args->u.int_value) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    fflush(stdout);

    return ret;
}

RVM_Value native_proc_println_int(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    debug_log_with_white_coloar("\t");

    if (arg_count != 1) {
        printf("native_proc_print only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    RVM_Value ret;
    ret.u.int_value = 0;

    // TODO: 暂时只打印int, 以后都强制转换成int_value
    printf("%d\n", args->u.int_value);
    fflush(stdout);

    return ret;
}

RVM_Value native_proc_println_double(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    debug_log_with_white_coloar("\t");

    if (arg_count != 1) {
        printf("native_proc_print only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    RVM_Value ret;
    ret.u.int_value = 0;

    printf("%f\n", args->u.double_value);
    fflush(stdout);

    return ret;
}

RVM_Value native_proc_println_string(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    debug_log_with_white_coloar("\t");

    if (arg_count != 1) {
        printf("native_proc_print only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    RVM_Value ret;
    ret.u.int_value = 0;

    if (args->u.object == NULL || args->u.object->u.string.data == NULL) {
        printf("\n");
    } else {
        printf("%s\n", args->u.object->u.string.data);
    }
    fflush(stdout);

    return ret;
}

RVM_Value native_proc_debug_assert(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    debug_log_with_white_coloar("\t");

    if (arg_count != 1) {
        printf("native_proc_print only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    RVM_Value ret;
    ret.u.int_value = 0;

    if (args->u.int_value) {
        printf("debug_assert PASS\n");
    } else {
        printf("debug_assert FAILED\n");
    }
    fflush(stdout);

    return ret;
}

RVM_Value native_proc_exit(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    debug_log_with_white_coloar("\t");

    RVM_Value ret;

    ret.u.int_value = 0;


    if (arg_count != 1) {
        printf("native_proc_print only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    // TODO: 暂时只打印int, 以后都强制转换成int_value
    exit(args->u.int_value);

    return ret;
}

RVM_Value native_proc_print(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    debug_log_with_white_coloar("\t");

    RVM_Value ret;
    ret.u.int_value = 0;

    for (unsigned int i = 0; i < arg_count; i++) {
        switch (args[i].type) {
        case RVM_VALUE_TYPE_BOOL:
            if (args[i].u.int_value) {
                printf("true");
            } else {
                printf("false");
            }
            break;
        case RVM_VALUE_TYPE_INT:
            printf("%d", args[i].u.int_value);
            break;
        case RVM_VALUE_TYPE_DOUBLE:
            printf("%f", args[i].u.double_value);
            break;
        case RVM_VALUE_TYPE_STRING:
            if (args[i].u.object == NULL || args[i].u.object->u.string.data == NULL) {
                printf("");
            } else {
                printf("%s", args[i].u.object->u.string.data);
            }
            break;
        default:
            break;
        }
        if (i < arg_count - 1)
            printf(" ");
    }


    return ret;
}

RVM_Value native_proc_println(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    debug_log_with_white_coloar("\t");

    RVM_Value ret;
    ret.u.int_value = 0;

    native_proc_print(rvm, arg_count, args);
    printf("\n");

    return ret;
}

RVM_Value native_proc_printf(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    debug_log_with_white_coloar("\t");

    RVM_Value ret;
    ret.u.int_value = 0;

    assert(args[0].type == RVM_VALUE_TYPE_STRING);

    char*        format     = args[0].u.object->u.string.data;
    size_t       length     = strlen(format);
    unsigned int args_index = 1;

    // printf("format:%s\n", format);
    // printf("length:%ld\n", length);


    for (size_t i = 0; i < length;) {
        size_t lasti = i;

        while (i < length && format[i] != '_') {
            i++;
        }
        if (i > lasti) {
            // printf("[debug]------:%ld, %ld\n", lasti, i-lasti);
            printf("%.*s", (int)(i - lasti), format + lasti);
            // fflush(stdout);
        }
        if (i >= length) {
            break;
        }


        switch (args[args_index].type) {
        case RVM_VALUE_TYPE_BOOL:
            if (args[args_index].u.int_value) {
                printf("true");
            } else {
                printf("false");
            }
            break;
        case RVM_VALUE_TYPE_INT:
            printf("%d", args[args_index].u.int_value);
            break;
        case RVM_VALUE_TYPE_DOUBLE:
            printf("%f", args[args_index].u.double_value);
            break;
        case RVM_VALUE_TYPE_STRING:
            if (args[args_index].u.object == NULL || args[args_index].u.object->u.string.data == NULL) {
                printf("");
            } else {
                printf("%s", args[args_index].u.object->u.string.data);
            }
            break;
        default:
            break;
        }
        args_index++;
        i++;
    }

    return ret;
}

RVM_Value native_proc_printfln(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    debug_log_with_white_coloar("\t");

    RVM_Value ret;
    ret.u.int_value = 0;

    native_proc_printf(rvm, arg_count, args);
    printf("\n");

    return ret;
}

void rvm_register_native_function(Ring_VirtualMachine* rvm, char* func_name, RVM_NativeFuncProc* func_proc, int arg_count) {
    debug_log_with_white_coloar("\t");

    if (rvm->function_list == NULL) {
        rvm->function_list = malloc(sizeof(RVM_Function));
    } else {
        rvm->function_list = realloc(rvm->function_list, sizeof(RVM_Function) * (rvm->function_size + 1));
    }
    rvm->function_list[rvm->function_size].func_name                = func_name;
    rvm->function_list[rvm->function_size].type                     = RVM_FUNCTION_TYPE_NATIVE;
    rvm->function_list[rvm->function_size].u.native_func            = malloc(sizeof(NativeFunction));
    rvm->function_list[rvm->function_size].u.native_func->func_proc = func_proc;
    rvm->function_list[rvm->function_size].u.native_func->arg_count = arg_count;

    rvm->function_size++;
}

void rvm_register_native_functions(Ring_VirtualMachine* rvm) {
    debug_log_with_white_coloar("\t");
    // FIXME: 如果 println_bool 和 println_string 生命的顺序不一致怎么办

    // rvm_register_native_function(rvm, "print", native_proc_print, 1);
    // rvm_register_native_function(rvm, "println", native_proc_println, 1);
    rvm_register_native_function(rvm, "println_bool", native_proc_println_bool, 1);
    rvm_register_native_function(rvm, "println_int", native_proc_println_int, 1);
    rvm_register_native_function(rvm, "println_double", native_proc_println_double, 1);
    rvm_register_native_function(rvm, "println_string", native_proc_println_string, 1);
    rvm_register_native_function(rvm, "debug_assert", native_proc_debug_assert, 1);
    rvm_register_native_function(rvm, "exit", native_proc_exit, 1);

    rvm_register_native_function(rvm, "print", native_proc_print, -1);
    rvm_register_native_function(rvm, "println", native_proc_println, -1);
    rvm_register_native_function(rvm, "printf", native_proc_printf, -1);
    rvm_register_native_function(rvm, "printfln", native_proc_printfln, -1);
}
