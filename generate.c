#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ring.h"

RVM_Opcode_Info RVM_Opcode_Infos[] = {
    {RVM_CODE_UNKNOW, ""},

    {RVM_CODE_PUSH_INT, "push_int"},

    {RVM_CODE_POP_STATIC_INT, "pop_static_int"},

    {RVM_CODE_ADD_INT, "add_int"},
};

Ring_VirtualMachine_Executer *new_ring_vm_executer() {
    Ring_VirtualMachine_Executer *executer = malloc(sizeof(Ring_VirtualMachine_Executer));
    executer->global_variable_size         = 0;
    executer->global_variable              = NULL;
    executer->function_size                = 0;
    executer->function                     = NULL;
    executer->code_size                    = 0;
    executer->code                         = NULL;
    return executer;
}

// 生成 RVM 虚拟机代码
void ring_generate_vm_code(Ring_Compiler *compiler, Ring_VirtualMachine_Executer *vm_executer) {
    add_global_variable(compiler, vm_executer);
    add_functions(compiler, vm_executer);
    add_top_level_code(compiler, vm_executer);

#ifdef DEBUG
    vm_executer_dump(vm_executer);
#endif
}

// 添加全局变量
void add_global_variable(Ring_Compiler *compiler, Ring_VirtualMachine_Executer *vm_executer) {
}

// 添加函数定义
void add_functions(Ring_Compiler *compiler, Ring_VirtualMachine_Executer *vm_executer) {
}

// 添加顶层代码
void add_top_level_code(Ring_Compiler *compiler, Ring_VirtualMachine_Executer *vm_executer) {
    RVM_OpcodeBuffer *opcode_buffer = new_opcode_buffer();
    generate_vmcode_from_statement_list(compiler, vm_executer, opcode_buffer);

    RVM_Byte *   code_list = opcode_buffer->code_list;
    unsigned int size      = opcode_buffer->code_size;
    unsigned int capacity  = opcode_buffer->code_capacity;

    debug_log_with_purple_coloar("----------top level code----------");
    debug_log_with_purple_coloar("code_size:%d, code_capacity:%d", size, capacity);
    for (int i = 0; i < size; i++) {
        char *name = RVM_Opcode_Infos[code_list[i]].name;
        debug_log_with_purple_coloar("[opcode] %10d %15s %10d", i, name, code_list[++i]);
    }
}

void vm_executer_dump(Ring_VirtualMachine_Executer *vm_executer) {
    debug_log_with_purple_coloar("");
}

RVM_OpcodeBuffer *new_opcode_buffer() {
    RVM_OpcodeBuffer *buffer = malloc(sizeof(RVM_OpcodeBuffer));
    buffer->code_list        = NULL;
    buffer->code_size        = 0;
    buffer->code_capacity    = 0;
    buffer->lable_list       = NULL;
    buffer->lable_size       = 0;
    buffer->lable_capacity   = 0;
    return buffer;
}

void generate_vmcode_from_statement_list(Ring_Compiler *compiler, Ring_VirtualMachine_Executer *vm_executer, RVM_OpcodeBuffer *opcode_buffer) {
    assert(compiler != NULL);

    for (Statement *statement = compiler->statement_list; statement != NULL; statement = statement->next) {
        debug_log_with_purple_coloar("statement->type:%d\n", statement->type);
        switch (statement->type) {
        case STATEMENT_TYPE_EXPRESSION:
            generate_vmcode_from_expression(statement->u.expression, opcode_buffer);
            break;

        default: break;
        }
    }
}

void generate_vmcode_from_expression(Expression *expression, RVM_OpcodeBuffer *opcode_buffer) {
    assert(expression != NULL);

    debug_log_with_purple_coloar("expression->type:%d", expression->type);

    switch (expression->type) {
    case EXPRESSION_TYPE_LITERAL_INT:
        generate_vmcode_from_int_expression(expression, opcode_buffer);
        break;
    case EXPRESSION_TYPE_ARITHMETIC_ADD:
        generate_vmcode_from_binary_expression(expression->u.binary_expression, opcode_buffer);
        break;

    default:
        break;
    }
}

void generate_vmcode_from_binary_expression(BinaryExpression *expression, RVM_OpcodeBuffer *opcode_buffer) {
    debug_log_with_purple_coloar("");

    Expression *left  = expression->left_expression;
    Expression *right = expression->right_expression;

    generate_vmcode_from_expression(left, opcode_buffer);
    generate_vmcode_from_expression(right, opcode_buffer);
}

void generate_vmcode_from_int_expression(Expression *expression, RVM_OpcodeBuffer *opcode_buffer) {
    debug_log_with_purple_coloar("");

    generate_vmcode(opcode_buffer, RVM_CODE_PUSH_INT);
}

void generate_vmcode(RVM_OpcodeBuffer *opcode_buffer, RVM_Opcode opcode) {
    if (opcode_buffer->code_capacity == 0) {
        opcode_buffer->code_capacity = 2;
    }
    if (opcode_buffer->code_capacity == opcode_buffer->code_size) {
        opcode_buffer->code_capacity *= 2;
    }

    opcode_buffer->code_list                             = realloc(opcode_buffer->code_list, opcode_buffer->code_capacity * sizeof(RVM_Byte));
    opcode_buffer->code_list[opcode_buffer->code_size++] = opcode;
    opcode_buffer->code_list[opcode_buffer->code_size++] = 123; // FIXME:
}
