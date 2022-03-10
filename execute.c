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

Ring_VirtualMachine* new_ring_virtualmachine(Ring_VirtualMachine_Executer* executer) {
    Ring_VirtualMachine* vm = malloc(sizeof(Ring_VirtualMachine));
    vm->executer            = executer;
    vm->runtime_stack       = new_runtime_stack();
    vm->pc                  = 0;
    return vm;
}

void ring_execute_vm_code(Ring_VirtualMachine* rvm) {
    RVM_Byte*     code_list     = rvm->executer->code_list;
    unsigned int  code_size     = rvm->executer->code_size;
    RuntimeStack* runtime_stack = rvm->runtime_stack;

    while (rvm->pc < code_size) {
        RVM_Byte opcode   = code_list[rvm->pc];
        char*    name     = RVM_Opcode_Infos[opcode].name;
        int      oper_num = code_list[rvm->pc + 1];
        debug_log_with_purple_coloar("[opcode] %10d %15s %10d", rvm->pc, name, oper_num);

        switch (opcode) {
        case RVM_CODE_PUSH_INT:
            STACK_SET_INT_OFFSET(rvm, 0, code_list[rvm->pc + 1]); // FIXME:
            runtime_stack->top_index++;
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

        dump_runtime_stack(runtime_stack);
    }
}

void dump_runtime_stack(RuntimeStack* runtime_stack) {
    debug_log_with_purple_coloar("****  runtime_stack  ****");
    debug_log_with_purple_coloar("%7s %10s", "index", "oper_num");
    for (int i = 0; i < runtime_stack->top_index;) {
        debug_log_with_purple_coloar("%7d %10d", i, runtime_stack->data[i].int_value);
        i++;
    }
    debug_log_with_purple_coloar("");
}
