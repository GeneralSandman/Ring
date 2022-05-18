#include "ring.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern RVM_Opcode_Info RVM_Opcode_Infos[];


// 通过绝对索引 获取
#define STACK_GET_INT_INDEX(rvm, index) \
    ((rvm)->runtime_stack->data[(index)].int_value)
#define STACK_GET_DOUBLE_INDEX(rvm, index) \
    ((rvm)->runtime_stack->data[(index)].double_value)
#define STACK_GET_OBJECT_INDEX(rvm, index) \
    ((rvm)->runtime_stack->data[(index)].object)

// 通过栈顶偏移 offset 获取
#define STACK_GET_INT_OFFSET(rvm, offset) \
    STACK_GET_INT_INDEX((rvm), (rvm)->runtime_stack->top_index + (offset))
#define STACK_GET_DOUBLE_OFFSET(rvm, offset) \
    STACK_GET_DOUBLE_INDEX((rvm), (rvm)->runtime_stack->top_index + (offset))
#define STACK_GET_OBJECT_OFFSET(rvm, offset) \
    STACK_GET_OBJECT_INDEX((rvm), (rvm)->runtime_stack->top_index + (offset))


// 通过绝对索引 设置
#define STACK_SET_INT_INDEX(rvm, index, value) \
    ((rvm)->runtime_stack->data[(index)].int_value = (value))
#define STACK_SET_DOUBLE_INDEX(rvm, index, value) \
    ((rvm)->runtime_stack->data[(index)].double_value = (value))
#define STACK_SET_OBJECT_INDEX(rvm, index, value) \
    ((rvm)->runtime_stack->data[(index)].object = (value))

// 通过栈顶偏移 offset 设置
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

    // init something
    rvm_add_static_variable(executer, rvm->runtime_static);
    rvm_register_native_functions(rvm);
    rvm_add_derive_functions(executer, rvm);

    return rvm;
}

void rvm_add_static_variable(Ring_VirtualMachine_Executer* executer, RVM_RuntimeStatic* runtime_static) {
    debug_log_with_white_coloar("\t");

    runtime_static->size = executer->global_variable_size;
    runtime_static->data = malloc(runtime_static->size * sizeof(RVM_Value));
}

void rvm_add_derive_functions(Ring_VirtualMachine_Executer* executer, Ring_VirtualMachine* rvm) {
    debug_log_with_white_coloar("\t");

    for (int i = 0; i < executer->function_size; i++) {
        RVM_Function function = executer->function_list[i];
        if (function.type == RVM_FUNCTION_TYPE_NATIVE) {
        }
    }
}

void ring_execute_vm_code(Ring_VirtualMachine* rvm) {
    debug_log_with_white_coloar("\t");

    RVM_Byte*         code_list       = rvm->executer->code_list;
    unsigned int      code_size       = rvm->executer->code_size;
    RVM_ConstantPool* const_pool_list = rvm->executer->constant_pool_list;
    /* unsigned int       const_pool_size = rvm->executer->constant_pool_size; */
    RVM_RuntimeStack*  runtime_stack  = rvm->runtime_stack;
    RVM_RuntimeStatic* runtime_static = rvm->runtime_static;
    unsigned int       opcode_num     = 0;

    unsigned int index;
    unsigned int func_index;
    unsigned int oper_num;
    unsigned int const_index;

    char* string_buf;

    while (rvm->pc < code_size) {
        RVM_Byte opcode = code_list[rvm->pc];
        // char*    name     = RVM_Opcode_Infos[opcode].name;
        debug_rvm(rvm);

        switch (opcode) {
        // int double string const
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
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;


        // static
        case RVM_CODE_POP_STATIC_INT:
            oper_num                              = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            index                                 = oper_num;                      //  在操作符后边获取
            runtime_static->data[index].int_value = STACK_GET_INT_OFFSET(rvm, -1); // 找到对应的 static 变量
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_STATIC_DOUBLE:
            oper_num                                 = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            index                                    = oper_num;                         //  在操作符后边获取
            runtime_static->data[index].double_value = STACK_GET_DOUBLE_OFFSET(rvm, -1); // 找到对应的 static 变量
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_POP_STATIC_OBJECT:
            oper_num                           = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            index                              = oper_num; //  在操作符后边获取
            runtime_static->data[index].object = STACK_GET_OBJECT_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STATIC_INT:
            oper_num = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            index    = oper_num; //  在操作符后边获取
            STACK_SET_INT_OFFSET(rvm, 0, rvm->runtime_static->data[index].int_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STATIC_DOUBLE:
            oper_num = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            index    = oper_num; //  在操作符后边获取
            STACK_SET_DOUBLE_OFFSET(rvm, 0, rvm->runtime_static->data[index].double_value);
            runtime_stack->top_index++;
            rvm->pc += 3;
            break;
        case RVM_CODE_PUSH_STATIC_OBJECT:
            oper_num = OPCODE_GET_2BYTE(&code_list[rvm->pc + 1]);
            index    = oper_num; //  在操作符后边获取
            STACK_SET_OBJECT_OFFSET(rvm, 0, rvm->runtime_static->data[index].object);
            runtime_stack->top_index++;
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
        case RVM_CODE_ADD_STRING:
            STACK_SET_OBJECT_OFFSET(rvm, -2, concat_string(STACK_GET_OBJECT_OFFSET(rvm, -2), STACK_GET_OBJECT_OFFSET(rvm, -1)));
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
            // TODO:
            /* STACK_SET_INT_OFFSET(rvm, 0, ); */
            /* runtime_stack->top_index++; */
            STACK_GET_INT_OFFSET(rvm, -1)
            ++;
            rvm->pc++;
            break;
        case RVM_CODE_INCREASE_PREFIX:
            // TODO:
            STACK_GET_INT_OFFSET(rvm, -1)
            ++;
            rvm->pc++;
            break;
        case RVM_CODE_DECREASE_SUFFIX:
            // TODO:
            STACK_GET_INT_OFFSET(rvm, -1)
            --;
            rvm->pc++;
            break;
        case RVM_CODE_DECREASE_PREFIX:
            // TODO:
            STACK_GET_INT_OFFSET(rvm, -1)
            --;
            rvm->pc++;
            break;

        // type cast
        case RVM_CODE_CAST_BOOL_TO_STRING:
            string_buf = malloc(sizeof(char) * 1024);
            if (!STACK_GET_INT_OFFSET(rvm, -1)) {
                sprintf(string_buf, "%s", "false");
            } else {
                sprintf(string_buf, "%s", "true");
            }
            STACK_SET_OBJECT_OFFSET(rvm, -1, string_literal_to_rvm_object((string_buf)));
            rvm->pc++;
            break;
        case RVM_CODE_CAST_INT_TO_STRING:
            break;
        case RVM_CODE_CAST_DOUBLE_TO_STRING:
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
        case RVM_CODE_INVOKE_FUNC:
            func_index = STACK_GET_INT_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            if (rvm->function_list[func_index].type == RVM_FUNCTION_TYPE_NATIVE) {
                invoke_native_function(rvm, &rvm->function_list[func_index]);
            } else if (rvm->function_list[func_index].type == RVM_FUNCTION_TYPE_DERIVE) {
                invoke_derive_function(rvm);
            }
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

        opcode_num++;
    }

    debug_rvm(rvm);
}


void invoke_native_function(Ring_VirtualMachine* rvm, RVM_Function* function) {
    debug_log_with_white_coloar("\t");

    RVM_Value ret;

    RVM_NativeFuncProc* native_func_proc = function->u.native_func->func_proc;
    unsigned int        arg_count        = function->u.native_func->arg_count;
    RVM_Value*          args; // TODO:

    // TODO: how to handle arg_count > 1
    args = &rvm->runtime_stack->data[rvm->runtime_stack->top_index - 1];

    ret = native_func_proc(rvm, arg_count, args);


    rvm->runtime_stack->top_index -= arg_count;
    rvm->runtime_stack->data[rvm->runtime_stack->top_index] = ret;
}

void invoke_derive_function(Ring_VirtualMachine* rvm) {
    debug_log_with_white_coloar("\t");
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

void debug_rvm(Ring_VirtualMachine* rvm) {
#ifndef DEBUG_RVM
    return;
#endif
    debug_log_with_white_coloar("\t");

    CLEAR_SCREEN;
    ring_vm_dump_runtime_stack(rvm->runtime_stack, 1, 0);
    ring_vm_code_dump(rvm->executer, rvm->pc, 1, 60);

    printf("press enter to step, 'q' to quit.\n");
    char ch = getchar();
    if (ch == 'q') {
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
    ret.int_value = 0;

    if (args->int_value) {
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
    ret.int_value = 0;

    // TODO: 暂时只打印int, 以后都强制转换成int_value
    printf("%d\n", args->int_value);
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
    ret.int_value = 0;

    printf("%f\n", args->double_value);
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
    ret.int_value = 0;

    if (args->object == NULL || args->object->u.string.data == NULL) {
        printf("\n");
    } else {
        printf("%s\n", args->object->u.string.data);
    }
    fflush(stdout);

    return ret;
}

RVM_Value native_proc_exit(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    debug_log_with_white_coloar("\t");

    RVM_Value ret;

    ret.int_value = 0;


    if (arg_count != 1) {
        printf("native_proc_print only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    // TODO: 暂时只打印int, 以后都强制转换成int_value
    exit(args->int_value);

    return ret;
}

void rvm_register_native_function(Ring_VirtualMachine* rvm, char* func_name, RVM_NativeFuncProc* func_proc, unsigned int arg_count) {
    debug_log_with_white_coloar("\t");

    if (rvm->function_list == NULL) {
        rvm->function_list = malloc(sizeof(Function));
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

    // rvm_register_native_function(rvm, "print", native_proc_print, 1);
    // rvm_register_native_function(rvm, "println", native_proc_println, 1);
    rvm_register_native_function(rvm, "println_bool", native_proc_println_bool, 1);
    rvm_register_native_function(rvm, "println_int", native_proc_println_int, 1);
    rvm_register_native_function(rvm, "println_double", native_proc_println_double, 1);
    rvm_register_native_function(rvm, "println_string", native_proc_println_string, 1);
    rvm_register_native_function(rvm, "exit", native_proc_exit, 1);
}
