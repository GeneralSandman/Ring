#include "ring.h"
#include <stdio.h>
#include <stdlib.h>

extern RVM_Opcode_Info RVM_Opcode_Infos[];


// 通过绝对索引 获取
#define STACK_GET_INT_INDEX(rvm, index) \
    ((rvm)->runtime_stack->data[(index)].int_value)
#define STACK_GET_DOUBLE_INDEX(rvm, index) \
    ((rvm)->runtime_stack->data[(index)].double_value)

// 通过栈顶偏移 offset 获取
#define STACK_GET_INT_OFFSET(rvm, offset) \
    STACK_GET_INT_INDEX((rvm), (rvm)->runtime_stack->top_index + (offset))
#define STACK_GET_DOUBLE_OFFSET(rvm, offset) \
    STACK_GET_DOUBLE_INDEX((rvm), (rvm)->runtime_stack->top_index + (offset))


// 通过绝对索引 设置
#define STACK_SET_INT_INDEX(rvm, index, value) \
    ((rvm)->runtime_stack->data[(index)].int_value = (value))
#define STACK_SET_DOUBLE_INDEX(rvm, index, value) \
    ((rvm)->runtime_stack->data[(index)].double_value = (value))

// 通过栈顶偏移 offset 设置
#define STACK_SET_INT_OFFSET(rvm, offset, value) \
    STACK_SET_INT_INDEX(rvm, (rvm)->runtime_stack->top_index + (offset), value)
#define STACK_SET_DOUBLE_OFFSET(rvm, offset, double_value) \
    STACK_SET_DOUBLE_INDEX(rvm, (rvm)->runtime_stack->top_index + (offset), value)


RVM_RuntimeStack* new_runtime_stack() {
    RVM_RuntimeStack* stack = malloc(sizeof(RVM_RuntimeStack));
    stack->top_index        = 0;
    stack->capacity         = 1024 * 1024; // FIXME: 先开辟一个大的空间
    stack->data             = malloc(stack->capacity * sizeof(RVM_Value));
    stack->size             = 0;
    return stack;
}

RVM_RuntimeStatic* new_runtime_static() {
    RVM_RuntimeStatic* runtime_static = malloc(sizeof(RVM_RuntimeStatic));
    runtime_static->data              = NULL;
    runtime_static->size              = 0;
    return runtime_static;
}

Ring_VirtualMachine* new_ring_virtualmachine(Ring_VirtualMachine_Executer* executer) {
    Ring_VirtualMachine* rvm = malloc(sizeof(Ring_VirtualMachine));
    rvm->executer            = executer;
    rvm->runtime_static      = new_runtime_static();
    rvm->runtime_stack       = new_runtime_stack();
    rvm->pc                  = 0;

    // init something
    rvm_add_static_variable(executer, rvm->runtime_static);
    rvm_register_native_functions(rvm);
    // rvm_add_functions(executer, rvm);

    return rvm;
}

void rvm_add_static_variable(Ring_VirtualMachine_Executer* executer, RVM_RuntimeStatic* runtime_static) {
    runtime_static->size = executer->global_variable_size;
    runtime_static->data = malloc(runtime_static->size * sizeof(RVM_Value));
}

void rvm_add_functions(Ring_VirtualMachine_Executer* executer, Ring_VirtualMachine* rvm) {
    rvm->function_list = executer->function_list;
    rvm->function_size = executer->function_size;
}

void ring_execute_vm_code(Ring_VirtualMachine* rvm) {
    RVM_Byte*          code_list      = rvm->executer->code_list;
    unsigned int       code_size      = rvm->executer->code_size;
    RVM_RuntimeStack*  runtime_stack  = rvm->runtime_stack;
    RVM_RuntimeStatic* runtime_static = rvm->runtime_static;

    unsigned int index;
    unsigned int func_index;

    while (rvm->pc < code_size) {
        RVM_Byte opcode = code_list[rvm->pc];
        // char*    name     = RVM_Opcode_Infos[opcode].name;
        int oper_num = code_list[rvm->pc + 1];
        debug_rvm(rvm);

        switch (opcode) {
        case RVM_CODE_PUSH_INT_1BYTE:
            STACK_SET_INT_OFFSET(rvm, 0, code_list[rvm->pc + 1]);
            runtime_stack->top_index++;
            rvm->pc += 2;
            break;

        case RVM_CODE_PUSH_INT_2BYTE:
            break;

        case RVM_CODE_PUSH_INT:
            STACK_SET_INT_OFFSET(rvm, 0, code_list[rvm->pc + 1]); // FIXME: 需要取两个
            runtime_stack->top_index++;
            rvm->pc += 2;
            break;

        case RVM_CODE_POP_STATIC_INT:
            index                                 = oper_num;                      //  在操作符后边获取
            runtime_static->data[index].int_value = STACK_GET_INT_OFFSET(rvm, -1); // 找到对应的 static 变量
            runtime_stack->top_index--;
            rvm->pc += 2;
            break;

        case RVM_CODE_ADD_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = STACK_GET_INT_OFFSET(rvm, -2) + STACK_GET_INT_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc++; // FIXME:  没有操作数不需要占用重复的空间
            break;

        case RVM_CODE_SUB_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = STACK_GET_INT_OFFSET(rvm, -2) - STACK_GET_INT_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc++; // FIXME:  没有操作数不需要占用重复的空间
            break;

        case RVM_CODE_MUL_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = STACK_GET_INT_OFFSET(rvm, -2) * STACK_GET_INT_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc++; // FIXME:  没有操作数不需要占用重复的空间
            break;

        case RVM_CODE_DIV_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = STACK_GET_INT_OFFSET(rvm, -2) / STACK_GET_INT_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc++; // FIXME:  没有操作数不需要占用重复的空间
            break;

        case RVM_CODE_MOD_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = STACK_GET_INT_OFFSET(rvm, -2) % STACK_GET_INT_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc++; // FIXME:  没有操作数不需要占用重复的空间
            break;

        case RVM_CODE_PUSH_FUNC:
            func_index = code_list[rvm->pc + 1];
            printf("func_index:%d\n", func_index);
            STACK_SET_INT_OFFSET(rvm, 0, func_index);
            runtime_stack->top_index++;
            rvm->pc += 2;
            break;

        case RVM_CODE_INVOKE_FUNC:
            if (rvm->function_list[func_index].type == RVM_FUNCTION_TYPE_NATIVE) {
                invoke_native_function(rvm, &rvm->function_list[func_index]);
                rvm->pc++;
            } else if (rvm->function_list[func_index].type == RVM_FUNCTION_TYPE_DERIVE) {
                invoke_derive_function(rvm);
            }
            break;

        default:
            fprintf(stderr, "execute error CODE:%d\n", opcode);
            exit(ERROR_CODE_RUN_VM_ERROR);
            break;
        }
    }

    debug_rvm(rvm);
}


void invoke_native_function(Ring_VirtualMachine* rvm, RVM_Function* function) {
    RVM_Value ret;

    RVM_NativeFuncProc* native_func_proc = function->u.native_func->func_proc;
    unsigned int        arg_count        = function->u.native_func->arg_count;
    RVM_Value*          args; // TODO:

    args = &rvm->runtime_stack->data[rvm->runtime_stack->top_index];

    ret = native_func_proc(rvm, arg_count, args);


    rvm->runtime_stack->top_index -= arg_count;
    rvm->runtime_stack->data[rvm->runtime_stack->top_index - 1] = ret;
}

void invoke_derive_function(Ring_VirtualMachine* rvm) {
}

void debug_rvm(Ring_VirtualMachine* rvm) {
#ifndef DEBUG_RVM
    return;
#endif

    CLEAR_SCREEN;
    ring_vm_dump_runtime_stack(rvm->runtime_stack, 1, 0);
    ring_vm_code_dump(rvm->executer, rvm->pc, 1, 60);

    printf("press enter to step, 'q' to quit.\n");
    char ch = getchar();
    if (ch == 'q') {
        exit(1);
    }
}


RVM_Value native_proc_print(Ring_VirtualMachine* rvm, unsigned int arg_cout, RVM_Value* args) {
    RVM_Value ret;

    ret.int_value = 0;


    if (arg_cout != 1) {
        printf("native_proc_print only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }


    // TODO: 暂时只打印int, 以后都强制转换成int_value
    printf("%d", args->int_value);
    fflush(stdout);

    return ret;
}

RVM_Value native_proc_println(Ring_VirtualMachine* rvm, unsigned int arg_cout, RVM_Value* args) {
    RVM_Value ret;

    ret.int_value = 0;


    if (arg_cout != 1) {
        printf("native_proc_print only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }


    // TODO: 暂时只打印int, 以后都强制转换成int_value
    printf("%d\n", args->int_value);
    fflush(stdout);

    return ret;
}

void rvm_register_native_function(Ring_VirtualMachine* rvm, char* func_name, RVM_NativeFuncProc* func_proc, unsigned int arg_count) {
    rvm->function_list = realloc(rvm->function_list, sizeof(Function) * (rvm->function_size + 1));

    rvm->function_list[rvm->function_size].func_name                = func_name;
    rvm->function_list[rvm->function_size].type                     = RVM_FUNCTION_TYPE_NATIVE;
    rvm->function_list[rvm->function_size].u.native_func            = malloc(sizeof(NativeFunction));
    rvm->function_list[rvm->function_size].u.native_func->func_proc = func_proc;
    rvm->function_list[rvm->function_size].u.native_func->arg_count = arg_count;

    rvm->function_size++;
}

void rvm_register_native_functions(Ring_VirtualMachine* rvm) {
    rvm_register_native_function(rvm, "print", native_proc_print, 1);
    rvm_register_native_function(rvm, "println", native_proc_println, 1);
}

