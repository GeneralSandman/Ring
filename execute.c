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
    Ring_VirtualMachine* vm = malloc(sizeof(Ring_VirtualMachine));
    vm->executer            = executer;
    vm->runtime_static      = new_runtime_static();
    vm->runtime_stack       = new_runtime_stack();
    vm->pc                  = 0;

    add_static_variable(executer, vm->runtime_static);
    return vm;
}

void add_static_variable(Ring_VirtualMachine_Executer* executer, RVM_RuntimeStatic* runtime_static) {
    runtime_static->size = executer->global_variable_size;
    runtime_static->data = malloc(runtime_static->size * sizeof(RVM_Value));
}

void ring_execute_vm_code(Ring_VirtualMachine* rvm) {
    RVM_Byte*         code_list     = rvm->executer->code_list;
    unsigned int      code_size     = rvm->executer->code_size;
    RVM_RuntimeStack* runtime_stack = rvm->runtime_stack;

    RVM_RuntimeStatic* runtime_static = rvm->runtime_static;

    unsigned int index;

    while (rvm->pc < code_size) {
        RVM_Byte opcode   = code_list[rvm->pc];
        char*    name     = RVM_Opcode_Infos[opcode].name;
        int      oper_num = code_list[rvm->pc + 1];
        debug_rvm(rvm);

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

        default:
            fprintf(stderr, "execute error\n");
            exit(ERROR_CODE_RUN_VM_ERROR);
            break;
        }
    }

    debug_rvm(rvm);
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
