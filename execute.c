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


RuntimeStack* new_runtime_stack() {
    RuntimeStack* stack = malloc(sizeof(RuntimeStack));
    stack->top_index    = 0;
    stack->capacity     = 1024 * 1024; // FIXME: 先开辟一个大的空间
    stack->data         = malloc(stack->capacity * sizeof(RuntimeStackValue));
    stack->size         = 0;
    return stack;
}

RuntimeStatic* new_runtime_static() {
    RuntimeStatic* runtime_static = malloc(sizeof(RuntimeStatic));
    runtime_static->data          = NULL;
    runtime_static->size          = 0;
    return runtime_static;
}

Ring_VirtualMachine* new_ring_virtualmachine(Ring_VirtualMachine_Executer* executer) {
    Ring_VirtualMachine* vm = malloc(sizeof(Ring_VirtualMachine));
    vm->executer            = executer;
    vm->runtime_static      = new_runtime_static();
    vm->runtime_stack       = new_runtime_stack();
    vm->pc                  = 0;

    add_global_variables(executer, vm->runtime_static);
    return vm;
}

void add_global_variables(Ring_VirtualMachine_Executer* executer, RuntimeStatic* runtime_static) {
    runtime_static->size = executer->global_variable_size;
    runtime_static->data = malloc(runtime_static->size * sizeof(RuntimeStackValue));
}

void ring_execute_vm_code(Ring_VirtualMachine* rvm) {
    RVM_Byte*     code_list     = rvm->executer->code_list;
    unsigned int  code_size     = rvm->executer->code_size;
    RuntimeStack* runtime_stack = rvm->runtime_stack;

    RuntimeStatic* runtime_static = rvm->runtime_static;

    unsigned int index;

    while (rvm->pc < code_size) {
        RVM_Byte opcode   = code_list[rvm->pc];
        char*    name     = RVM_Opcode_Infos[opcode].name;
        int      oper_num = code_list[rvm->pc + 1];
        debug_log_with_darkgreen_coloar("[opcode] %10d %15s %10d", rvm->pc, name, oper_num);

        switch (opcode) {
        case RVM_CODE_PUSH_INT:
            STACK_SET_INT_OFFSET(rvm, 0, code_list[rvm->pc + 1]); // FIXME:
            runtime_stack->top_index++;
            rvm->pc += 2;
            break;

        case RVM_CODE_POP_STATIC_INT:
            index                                      = oper_num;                      //  在操作符后边获取
            rvm->runtime_static->data[index].int_value = STACK_GET_INT_OFFSET(rvm, -1); // 找到对应的 static 变量
            runtime_stack->top_index--;
            rvm->pc += 2;
            break;

        case RVM_CODE_ADD_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = STACK_GET_INT_OFFSET(rvm, -2) + STACK_GET_INT_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc += 2; // FIXME:  没有操作数不需要占用重复的空间
            break;

        case RVM_CODE_SUB_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = STACK_GET_INT_OFFSET(rvm, -2) - STACK_GET_INT_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc += 2; // FIXME:  没有操作数不需要占用重复的空间
            break;

        case RVM_CODE_MUL_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = STACK_GET_INT_OFFSET(rvm, -2) * STACK_GET_INT_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc += 2; // FIXME:  没有操作数不需要占用重复的空间
            break;

        case RVM_CODE_DIV_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = STACK_GET_INT_OFFSET(rvm, -2) / STACK_GET_INT_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc += 2; // FIXME:  没有操作数不需要占用重复的空间
            break;

        case RVM_CODE_MOD_INT:
            STACK_GET_INT_OFFSET(rvm, -2) = STACK_GET_INT_OFFSET(rvm, -2) % STACK_GET_INT_OFFSET(rvm, -1);
            runtime_stack->top_index--;
            rvm->pc += 2; // FIXME:  没有操作数不需要占用重复的空间
            break;

        default:
            printf("error\n");
            exit(1);
            break;
        }

        debug_rvm(rvm);
    }
}


void debug_rvm(Ring_VirtualMachine* rvm) {
#ifndef DEBUG_RVM
    return;
#endif

    CLEAR_SCREEN;
    dump_runtime_stack(rvm->runtime_stack);
    dump_vm_code(rvm);

    printf("press enter to step, 'q' to quit.\n");
    char ch = getchar();
    if (ch == 'q') {
        exit(1);
    }
}

void dump_runtime_stack(RuntimeStack* runtime_stack) {
    printf("****  runtime_stack  ****\n");
    printf("%7s | %10s\n", "index", "oper_num");
    for (int i = 0; i < runtime_stack->top_index;) {
        printf("%7d | %10d\n", i, runtime_stack->data[i].int_value);
        i++;
    }
    printf("\n");
}

void dump_vm_code(Ring_VirtualMachine* rvm) {
    Ring_VirtualMachine_Executer* executer  = rvm->executer;
    RVM_Byte*                     code_list = rvm->executer->code_list;
    unsigned int                  code_size = rvm->executer->code_size;

    int col = 60;
    int row = 1;

    MOVE_CURSOR(row++, col);
    printf("+++++ ************  rvm opcode  ****\n");

    MOVE_CURSOR(row++, col);
    printf("+++++ %10s | %15s | %10s | %5s\n", "index", "opcode", "oper num", "pointer");
    for (int i = 0; i < code_size; i++) {
        RVM_Byte opcode   = code_list[i];
        char*    name     = RVM_Opcode_Infos[opcode].name;
        int      oper_num = code_list[i + 1];


        char* pointer = "";
        if (i == rvm->pc) {
            pointer = "<--";
        }
        MOVE_CURSOR(row++, col);
        printf("+++++ %10d | %15s | %10d | %5s\n", i, name, oper_num, pointer);
    }
}