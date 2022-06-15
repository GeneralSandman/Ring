#include "ring.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

RVM_Opcode_Info RVM_Opcode_Infos[] = {
    {RVM_CODE_UNKNOW, "", OPCODE_OPERAND_TYPE_UNKNOW, 0},


    // init double string const
    {RVM_CODE_PUSH_BOOL, "push_bool", OPCODE_OPERAND_TYPE_1BYTE, 1},
    {RVM_CODE_PUSH_INT_1BYTE, "push_int_1byte", OPCODE_OPERAND_TYPE_1BYTE, 1}, // 后边紧跟 int 常量 1 type
    {RVM_CODE_PUSH_INT_2BYTE, "push_int_2byte", OPCODE_OPERAND_TYPE_2BYTE, 1}, // 后边紧跟 int 常量 2 type
    {RVM_CODE_PUSH_INT, "push_int", OPCODE_OPERAND_TYPE_2BYTE, 1},             // 后边紧跟 int 常量 2 的索引 这里的还要 改一下 OPCODE_OPERAND_TYPE_2BYTE
    {RVM_CODE_PUSH_DOUBLE, "push_double", OPCODE_OPERAND_TYPE_2BYTE, 1},       // 后边紧跟 double 常量
    {RVM_CODE_PUSH_STRING, "push_string", OPCODE_OPERAND_TYPE_2BYTE, 1},       // 后边紧跟 string 常量


    // static
    {RVM_CODE_POP_STATIC_BOOL, "pop_static_bool", OPCODE_OPERAND_TYPE_2BYTE, -1},
    {RVM_CODE_POP_STATIC_INT, "pop_static_int", OPCODE_OPERAND_TYPE_2BYTE, -1},
    {RVM_CODE_POP_STATIC_DOUBLE, "pop_static_double", OPCODE_OPERAND_TYPE_2BYTE, -1},
    {RVM_CODE_POP_STATIC_OBJECT, "pop_static_object", OPCODE_OPERAND_TYPE_2BYTE, -1},
    {RVM_CODE_PUSH_STATIC_BOOL, "push_static_bool", OPCODE_OPERAND_TYPE_2BYTE, 1},
    {RVM_CODE_PUSH_STATIC_INT, "push_static_int", OPCODE_OPERAND_TYPE_2BYTE, 1},
    {RVM_CODE_PUSH_STATIC_DOUBLE, "push_static_double", OPCODE_OPERAND_TYPE_2BYTE, 1},
    {RVM_CODE_PUSH_STATIC_OBJECT, "push_static_object", OPCODE_OPERAND_TYPE_2BYTE, 1},


    // stack
    {RVM_CODE_POP_STACK_BOOL, "pop_stack_bool", OPCODE_OPERAND_TYPE_2BYTE, -1},
    {RVM_CODE_POP_STACK_INT, "pop_stack_int", OPCODE_OPERAND_TYPE_2BYTE, -1},
    {RVM_CODE_POP_STACK_DOUBLE, "pop_stack_double", OPCODE_OPERAND_TYPE_2BYTE, -1},
    {RVM_CODE_POP_STACK_OBJECT, "pop_stack_object", OPCODE_OPERAND_TYPE_2BYTE, -1},
    {RVM_CODE_PUSH_STACK_BOOL, "push_stack_bool", OPCODE_OPERAND_TYPE_2BYTE, 1},
    {RVM_CODE_PUSH_STACK_INT, "push_stack_int", OPCODE_OPERAND_TYPE_2BYTE, 1},
    {RVM_CODE_PUSH_STACK_DOUBLE, "push_stack_double", OPCODE_OPERAND_TYPE_2BYTE, 1},
    {RVM_CODE_PUSH_STACK_OBJECT, "push_stack_object", OPCODE_OPERAND_TYPE_2BYTE, 1},


    // arithmetic
    {RVM_CODE_ADD_INT, "add_int", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_ADD_DOUBLE, "add_double", OPCODE_OPERAND_TYPE_0BYTE, -1},

    {RVM_CODE_SUB_INT, "sub_int", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_SUB_DOUBLE, "sub_double", OPCODE_OPERAND_TYPE_0BYTE, -1},

    {RVM_CODE_MUL_INT, "mul_int", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_MUL_DOUBLE, "mul_double", OPCODE_OPERAND_TYPE_0BYTE, -1},

    {RVM_CODE_DIV_INT, "div_int", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_DIV_DOUBLE, "div_double", OPCODE_OPERAND_TYPE_0BYTE, -1},

    {RVM_CODE_MOD_INT, "mod_int", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_MOD_DOUBLE, "mod_double", OPCODE_OPERAND_TYPE_0BYTE, -1},

    {RVM_CODE_MINUS_INT, "minus_int", OPCODE_OPERAND_TYPE_0BYTE, 0},
    {RVM_CODE_MINUS_DOUBLE, "minus_double", OPCODE_OPERAND_TYPE_0BYTE, 0},

    {RVM_CODE_INCREASE_SUFFIX, "increase_suffix", OPCODE_OPERAND_TYPE_0BYTE, 0},
    {RVM_CODE_INCREASE_PREFIX, "increase_prefix", OPCODE_OPERAND_TYPE_0BYTE, 0},
    {RVM_CODE_DECREASE_SUFFIX, "decrease_suffix", OPCODE_OPERAND_TYPE_0BYTE, 0},
    {RVM_CODE_DECREASE_PREFIX, "decrease_prefix", OPCODE_OPERAND_TYPE_0BYTE, 0},

    {RVM_CODE_CONCAT, "concat", OPCODE_OPERAND_TYPE_0BYTE, -1},

    // type cast
    {RVM_CODE_CAST_BOOL_TO_INT, "cast_bool_to_int", OPCODE_OPERAND_TYPE_0BYTE, 0},
    {RVM_CODE_CAST_INT_TO_DOUBLE, "cast_int_to_double", OPCODE_OPERAND_TYPE_0BYTE, 0},

    {RVM_CODE_CAST_INT_TO_BOOL, "cast_int_to_bool", OPCODE_OPERAND_TYPE_0BYTE, 0},
    {RVM_CODE_CAST_DOUBLE_TO_INT, "cast_double_to_int", OPCODE_OPERAND_TYPE_0BYTE, 0},


    // logical
    {RVM_CODE_LOGICAL_AND, "logical_and", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_LOGICAL_OR, "logical_or", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_LOGICAL_NOT, "logical_not", OPCODE_OPERAND_TYPE_0BYTE, 0},

    // relational
    {RVM_CODE_RELATIONAL_EQ_INT, "eq_int", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_RELATIONAL_EQ_DOUBLE, "eq_double", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_RELATIONAL_EQ_STRING, "eq_string", OPCODE_OPERAND_TYPE_0BYTE, -1},

    {RVM_CODE_RELATIONAL_NE_INT, "ne_int", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_RELATIONAL_NE_DOUBLE, "ne_double", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_RELATIONAL_NE_STRING, "ne_string", OPCODE_OPERAND_TYPE_0BYTE, -1},

    {RVM_CODE_RELATIONAL_GT_INT, "gt_int", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_RELATIONAL_GT_DOUBLE, "gt_double", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_RELATIONAL_GT_STRING, "gt_string", OPCODE_OPERAND_TYPE_0BYTE, -1},

    {RVM_CODE_RELATIONAL_GE_INT, "ge_int", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_RELATIONAL_GE_DOUBLE, "ge_double", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_RELATIONAL_GE_STRING, "ge_string", OPCODE_OPERAND_TYPE_0BYTE, -1},

    {RVM_CODE_RELATIONAL_LT_INT, "lt_int", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_RELATIONAL_LT_DOUBLE, "lt_double", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_RELATIONAL_LT_STRING, "lt_string", OPCODE_OPERAND_TYPE_0BYTE, -1},

    {RVM_CODE_RELATIONAL_LE_INT, "le_int", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_RELATIONAL_LE_DOUBLE, "le_double", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_RELATIONAL_LE_STRING, "le_string", OPCODE_OPERAND_TYPE_0BYTE, -1},

    // jump
    {RVM_CODE_JUMP, "jump", OPCODE_OPERAND_TYPE_2BYTE, 0},
    {RVM_CODE_JUMP_IF_FALSE, "jump_if_false", OPCODE_OPERAND_TYPE_2BYTE, -1},
    {RVM_CODE_JUMP_IF_TRUE, "jump_if_true", OPCODE_OPERAND_TYPE_2BYTE, -1},

    // duplicate
    {RVM_CODE_DUPLICATE, "duplicate", OPCODE_OPERAND_TYPE_0BYTE, 1},


    // func
    {RVM_CODE_PUSH_FUNC, "push_func", OPCODE_OPERAND_TYPE_2BYTE, 1}, // TODO: update to 2 byte
    {RVM_CODE_ARGUMENT_NUM, "argument_num", OPCODE_OPERAND_TYPE_1BYTE, 0},
    {RVM_CODE_INVOKE_FUNC, "invoke_func", OPCODE_OPERAND_TYPE_0BYTE, -1},
    {RVM_CODE_RETURN, "return", OPCODE_OPERAND_TYPE_2BYTE, 0}, // 操作数代表返回值的数量，ex；return int, double, string;  操作数就是3 FIXME:runtime_stack_increment
    {RVM_CODE_FUNCTION_FINISH, "function_finish", OPCODE_OPERAND_TYPE_0BYTE, 0},


    {RVM_CODES_NUM, "", OPCODE_OPERAND_TYPE_0BYTE, 0},
};

Ring_VirtualMachine_Executer* new_ring_vm_executer() {
    debug_log_with_darkgreen_coloar("\t");
    Ring_VirtualMachine_Executer* executer    = malloc(sizeof(Ring_VirtualMachine_Executer));
    executer->constant_pool_size              = 0;
    executer->constant_pool_list              = NULL;
    executer->global_variable_size            = 0;
    executer->global_variable_list            = NULL;
    executer->function_size                   = 0;
    executer->function_list                   = NULL;
    executer->code_size                       = 0;
    executer->code_list                       = NULL;
    executer->estimate_runtime_stack_capacity = 0;
    return executer;
}

// 生成 RVM 虚拟机代码
void ring_generate_vm_code(Ring_Compiler* compiler, Ring_VirtualMachine_Executer* executer) {
    debug_log_with_darkgreen_coloar("\t");

    add_global_variable(compiler, executer);
    add_functions(compiler, executer);
    add_top_level_code(compiler, executer);

#ifdef DEBUG
    vm_executer_dump(executer);
#endif
}

// 添加全局变量
void add_global_variable(Ring_Compiler* compiler, Ring_VirtualMachine_Executer* executer) {
    debug_log_with_darkgreen_coloar("\t");
    // FIXME: 在 Compiler 中大部分是链表：因为在编译的时候不确定存储空间
    // 在 Executer 中 大部分是数组，因为编译完成，存储空间的数量都已经确认了。
    if (compiler->declaration_list_size == 0) {
        return;
    }

    executer->global_variable_size = compiler->declaration_list_size;
    executer->global_variable_list = malloc(executer->global_variable_size * sizeof(RVM_Variable));

    Declaration* pos = compiler->declaration_list;
    int          i   = 0;
    for (; pos; pos = pos->next, i++) {
        executer->global_variable_list[i].identifier = pos->identifier;
        executer->global_variable_list[i].type       = pos->type; // TODO: 这里考虑要深度复制
    }
}

// 添加函数定义
void add_functions(Ring_Compiler* compiler, Ring_VirtualMachine_Executer* executer) {
    debug_log_with_darkgreen_coloar("\t");
    Function*    pos                = compiler->function_list;
    unsigned int function_list_size = compiler->function_list_size;
    unsigned int i                  = 0;

    executer->function_size = function_list_size;
    executer->function_list = malloc(sizeof(RVM_Function) * function_list_size);

    // 暂时只处理 native function
    for (; pos; pos = pos->next, i++) {
        copy_function(pos, &executer->function_list[i]);
        if (pos->block != NULL) {
            generate_code_from_function_definition(executer, pos, &executer->function_list[i]);
        }
    }
}

void copy_function(Function* src, RVM_Function* dest) {
    debug_log_with_darkgreen_coloar("\t");

    dest->func_name = src->function_name;
    if (src->type == FUNCTION_TYPE_NATIVE) {
        dest->type                = RVM_FUNCTION_TYPE_NATIVE;
        dest->parameter_size      = src->parameter_list_size;
        dest->parameter_list      = NULL; // TODO:
        dest->local_variable_size = 0;
        dest->local_variable_list = NULL; // TODO:
    } else if (src->type == FUNCTION_TYPE_DERIVE) {
        dest->type                = RVM_FUNCTION_TYPE_DERIVE;
        dest->parameter_size      = src->parameter_list_size;
        dest->parameter_list      = NULL; // TODO:
        dest->local_variable_size = src->block->declaration_list_size;
        dest->local_variable_list = NULL; // TODO:
        dest->u.derive_func       = malloc(sizeof(DeriveFunction));
    }

    dest->estimate_runtime_stack_capacity = 0;
}

// 添加顶层代码
void add_top_level_code(Ring_Compiler* compiler, Ring_VirtualMachine_Executer* executer) {
    debug_log_with_darkgreen_coloar("\t");

    RVM_OpcodeBuffer* opcode_buffer = new_opcode_buffer();
    generate_vmcode_from_statement_list(executer, NULL, compiler->statement_list, opcode_buffer);

    opcode_buffer_fix_label(opcode_buffer);


    RVM_Byte*    code_list = opcode_buffer->code_list;
    unsigned int code_size = opcode_buffer->code_size;
    // unsigned int code_capacity = opcode_buffer->code_capacity;

    executer->code_list = code_list;
    executer->code_size = code_size;
}

void generate_code_from_function_definition(Ring_VirtualMachine_Executer* executer, Function* src, RVM_Function* dest) {
    debug_log_with_darkgreen_coloar("\t");

    RVM_OpcodeBuffer* opcode_buffer = new_opcode_buffer();
    generate_vmcode_from_statement_list(executer, src->block, src->block->statement_list, opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_FUNCTION_FINISH, 0);

    opcode_buffer_fix_label(opcode_buffer);


    dest->u.derive_func->code_list           = opcode_buffer->code_list;
    dest->u.derive_func->code_size           = opcode_buffer->code_size;
    dest->u.derive_func->local_variable_size = src->block->declaration_list_size;

#ifdef DEBUG
    ring_vm_code_dump(dest, opcode_buffer->code_list, opcode_buffer->code_size, 0, 60, 1);
#endif
}


void vm_executer_dump(Ring_VirtualMachine_Executer* executer) {
    debug_log_with_darkgreen_coloar("\t");
    // CLEAR_SCREEN;
    ring_vm_constantpool_dump(executer);
    ring_vm_code_dump(NULL, executer->code_list, executer->code_size, 0, 60, 1);
}

RVM_OpcodeBuffer* new_opcode_buffer() {
    debug_log_with_darkgreen_coloar("\t");
    RVM_OpcodeBuffer* buffer = malloc(sizeof(RVM_OpcodeBuffer));
    buffer->code_list        = NULL;
    buffer->code_size        = 0;
    buffer->code_capacity    = 0;
    buffer->lable_list       = NULL;
    buffer->lable_size       = 0;
    buffer->lable_capacity   = 0;
    return buffer;
}

void generate_vmcode_from_block(Ring_VirtualMachine_Executer* executer, Block* block, RVM_OpcodeBuffer* opcode_buffer) {
    if (block == NULL) {
        return;
    }
    debug_log_with_darkgreen_coloar("\t");
    generate_vmcode_from_statement_list(executer, block, block->statement_list, opcode_buffer);
}

void generate_vmcode_from_statement_list(Ring_VirtualMachine_Executer* executer, Block* block, Statement* statement_list, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    for (Statement* statement = statement_list; statement != NULL; statement = statement->next) {
        switch (statement->type) {
        case STATEMENT_TYPE_EXPRESSION:
            generate_vmcode_from_expression(executer, statement->u.expression, opcode_buffer, 0);
            break;

        case STATEMENT_TYPE_IF:
            generate_vmcode_from_if_statement(executer, statement->u.if_statement, opcode_buffer);
            break;

        case STATEMENT_TYPE_FOR:
            generate_vmcode_from_for_statement(executer, statement->u.for_statement, opcode_buffer);
            break;

        case STATEMENT_TYPE_DOFOR:
            generate_vmcode_from_dofor_statement(executer, statement->u.dofor_statement, opcode_buffer);
            break;

        case STATEMENT_TYPE_BREAK:
            generate_vmcode_from_break_statement(executer, block, statement->u.break_statement, opcode_buffer);
            break;

        case STATEMENT_TYPE_CONTINUE:
            generate_vmcode_from_continue_statement(executer, block, statement->u.continue_statement, opcode_buffer);
            break;

        case STATEMENT_TYPE_RETURN:
            generate_vmcode_from_return_statement(executer, block, statement->u.return_statement, opcode_buffer);
            break;

        case STATEMENT_TYPE_DECLARATION:
            generate_vmcode_from_initializer(executer, block, statement->u.declaration_statement, opcode_buffer);
            break;


        default: break;
        }
    }
}

void generate_vmcode_from_if_statement(Ring_VirtualMachine_Executer* executer, IfStatement* if_statement, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (if_statement == NULL) {
        return;
    }

    unsigned int if_false_jump_label = 0;
    unsigned int if_end_label        = 0;

    generate_vmcode_from_expression(executer, if_statement->condition_expression, opcode_buffer, 1);

    if_false_jump_label = opcode_buffer_get_label(opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, if_false_jump_label);

    generate_vmcode_from_block(executer, if_statement->if_block, opcode_buffer);

    if_end_label = opcode_buffer_get_label(opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, if_end_label);


    opcode_buffer_set_label(opcode_buffer, if_false_jump_label, opcode_buffer->code_size);

    // handle elseif list
    ElseIfStatement* pos = if_statement->elseif_list;
    for (; pos; pos = pos->next) {
        generate_vmcode_from_expression(executer, pos->condition_expression, opcode_buffer, 0);

        unsigned int elseif_false_jump_label = 0;
        elseif_false_jump_label              = opcode_buffer_get_label(opcode_buffer);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, elseif_false_jump_label);

        generate_vmcode_from_block(executer, pos->elseif_block, opcode_buffer);

        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, if_end_label);

        opcode_buffer_set_label(opcode_buffer, elseif_false_jump_label, opcode_buffer->code_size);
    }

    // handle else
    if (if_statement->else_block != NULL) {
        generate_vmcode_from_block(executer, if_statement->else_block, opcode_buffer);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, if_end_label);
    }


    opcode_buffer_set_label(opcode_buffer, if_end_label, opcode_buffer->code_size);
}

// TODO: 暂时不支持 break continue
void generate_vmcode_from_for_statement(Ring_VirtualMachine_Executer* executer, ForStatement* for_statement, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (for_statement == NULL) {
        return;
    }
    unsigned int end_label      = 0;
    unsigned int loop_label     = 0;
    unsigned int continue_label = 0;

    // Step-1:
    if (for_statement->init_expression) {
        generate_vmcode_from_expression(executer, for_statement->init_expression, opcode_buffer, 0);
    }
    loop_label = opcode_buffer_get_label(opcode_buffer);
    opcode_buffer_set_label(opcode_buffer, loop_label, opcode_buffer->code_size);

    // Step-2:
    end_label = opcode_buffer_get_label(opcode_buffer);
    if (for_statement->condition_expression) {
        generate_vmcode_from_expression(executer, for_statement->condition_expression, opcode_buffer, 0);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, end_label);
    }


    // Step-3:
    if (for_statement->block) {
        for_statement->block->block_labels.break_label = end_label;
        for_statement->block->block_labels.continue_label =
            continue_label = opcode_buffer_get_label(opcode_buffer);

        generate_vmcode_from_block(executer, for_statement->block, opcode_buffer);
    }

    opcode_buffer_set_label(opcode_buffer, continue_label, opcode_buffer->code_size);

    // Step-4:
    if (for_statement->post_expression) {
        generate_vmcode_from_expression(executer, for_statement->post_expression, opcode_buffer, 0);
    }

    // Step-5:
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, loop_label);


    // Step-End:

    opcode_buffer_set_label(opcode_buffer, end_label, opcode_buffer->code_size);
}

// TODO: 暂时不支持 break continue
void generate_vmcode_from_dofor_statement(Ring_VirtualMachine_Executer* executer, DoForStatement* dofor_statement, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (dofor_statement == NULL) {
        return;
    }
    unsigned int end_label      = 0;
    unsigned int loop_label     = 0;
    unsigned int continue_label = 0;


    // Step-1:
    if (dofor_statement->init_expression) {
        generate_vmcode_from_expression(executer, dofor_statement->init_expression, opcode_buffer, 0);
    }
    loop_label = opcode_buffer_get_label(opcode_buffer);
    opcode_buffer_set_label(opcode_buffer, loop_label, opcode_buffer->code_size);


    // Step-2:
    end_label = opcode_buffer_get_label(opcode_buffer);
    if (dofor_statement->block) {
        dofor_statement->block->block_labels.break_label = end_label;
        dofor_statement->block->block_labels.continue_label =
            continue_label = opcode_buffer_get_label(opcode_buffer);

        generate_vmcode_from_block(executer, dofor_statement->block, opcode_buffer);
    }


    opcode_buffer_set_label(opcode_buffer, continue_label, opcode_buffer->code_size);


    // Step-3:
    if (dofor_statement->condition_expression) {
        generate_vmcode_from_expression(executer, dofor_statement->condition_expression, opcode_buffer, 0);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, end_label);
    }


    // Step-4:
    if (dofor_statement->post_expression) {
        generate_vmcode_from_expression(executer, dofor_statement->post_expression, opcode_buffer, 0);
    }

    // Step-5;
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, loop_label);

    // Step-End;
    opcode_buffer_set_label(opcode_buffer, end_label, opcode_buffer->code_size);
}

void generate_vmcode_from_break_statement(Ring_VirtualMachine_Executer* executer, Block* block, BreakStatement* break_statement, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (break_statement == NULL) {
        return;
    }

    unsigned int break_loop_num = break_statement->break_loop_num;

    Block*       pos      = block;
    unsigned int loop_num = 1;
    for (; pos; pos = pos->parent_block) {
        if (pos->type == BLOCK_TYPE_FOR) {
        } else if (pos->type == BLOCK_TYPE_DOFOR) {
        } else {
            continue;
        }

        if (break_loop_num == loop_num) {
            break;
        }
        loop_num++;
    }


    if (pos == NULL) {
        printf("generate_vmcode_from_break_statement error------------\n");
        exit(ERROR_CODE_GENERATE_OPCODE_ERROR);
    }

    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, pos->block_labels.break_label);
}

void generate_vmcode_from_continue_statement(Ring_VirtualMachine_Executer* executer, Block* block, ContinueStatement* continue_statement, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (continue_statement == NULL) {
        return;
    }

    Block* pos = block;
    for (; pos; pos = pos->parent_block) {
        if (pos->type == BLOCK_TYPE_FOR) {
            break;
        } else if (pos->type == BLOCK_TYPE_DOFOR) {
            break;
        } else {
            continue;
        }
    }


    if (pos == NULL) {
        printf("generate_vmcode_from_continue_statement error------------\n");
        exit(ERROR_CODE_GENERATE_OPCODE_ERROR);
    }

    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, pos->block_labels.continue_label);
}

void generate_vmcode_from_return_statement(Ring_VirtualMachine_Executer* executer, Block* block, ReturnStatement* return_statement, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (return_statement == NULL) {
        return;
    }


    Expression* pos;
    for (pos = return_statement->return_list; pos; pos = pos->next) {
        generate_vmcode_from_expression(executer, pos, opcode_buffer, 1);
    }


    generate_vmcode(executer, opcode_buffer, RVM_CODE_RETURN, return_statement->return_list_size);
}

void generate_vmcode_from_initializer(Ring_VirtualMachine_Executer* executer, Block* block, Declaration* declaration, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (declaration == NULL) {
        return;
    }

    Declaration* pos = declaration;
    for (; pos; pos = pos->next) {
        if (pos->initializer) {
            generate_vmcode_from_expression(executer, pos->initializer, opcode_buffer, 1);
            RVM_Opcode opcode = RVM_CODE_UNKNOW;
            if (pos->is_local) {
                // 局部变量
                opcode = convert_opcode_by_rvm_type(RVM_CODE_POP_STACK_BOOL, pos->type);
            } else {
                // 全局变量
                opcode = convert_opcode_by_rvm_type(RVM_CODE_POP_STATIC_BOOL, pos->type);
            }
            generate_vmcode(executer, opcode_buffer, opcode, pos->variable_index);
        }
    }
}

void generate_vmcode_from_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer, int need_duplicate) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == NULL) {
        return;
    }

    switch (expression->type) {
    case EXPRESSION_TYPE_LITERAL_BOOL:
        generate_vmcode_from_bool_expression(executer, expression, opcode_buffer);
        break;
    case EXPRESSION_TYPE_LITERAL_INT:
        generate_vmcode_from_int_expression(executer, expression, opcode_buffer);
        break;
    case EXPRESSION_TYPE_LITERAL_DOUBLE:
        generate_vmcode_from_double_expression(executer, expression, opcode_buffer);
        break;
    case EXPRESSION_TYPE_LITERAL_STRING:
        generate_vmcode_from_string_expression(executer, expression, opcode_buffer);
        break;
    case EXPRESSION_TYPE_IDENTIFIER:
        generate_vmcode_from_identifier_expression(executer, expression->u.identifier_expression, opcode_buffer);
        break;
    case EXPRESSION_TYPE_CONCAT:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_CONCAT);
        break;
    case EXPRESSION_TYPE_ARITHMETIC_ADD:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_ADD_INT);
        break;

    case EXPRESSION_TYPE_ARITHMETIC_SUB:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_SUB_INT);
        break;

    case EXPRESSION_TYPE_ARITHMETIC_MUL:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_MUL_INT);
        break;

    case EXPRESSION_TYPE_ARITHMETIC_DIV:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_DIV_INT);
        break;

    case EXPRESSION_TYPE_ARITHMETIC_MOD:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_MOD_INT);
        break;

    case EXPRESSION_TYPE_ARITHMETIC_UNITARY_MINUS:
        generate_vmcode_from_unitary_expression(executer, expression->u.unitary_expression, opcode_buffer, RVM_CODE_MINUS_INT);
        break;

    case EXPRESSION_TYPE_LOGICAL_AND:
        generate_vmcode_from_logical_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_LOGICAL_AND);
        break;
    case EXPRESSION_TYPE_LOGICAL_OR:
        generate_vmcode_from_logical_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_LOGICAL_OR);
        break;
    case EXPRESSION_TYPE_LOGICAL_UNITARY_NOT:
        generate_vmcode_from_unitary_expression(executer, expression->u.unitary_expression, opcode_buffer, RVM_CODE_LOGICAL_NOT);
        break;

    case EXPRESSION_TYPE_UNITARY_INCREASE_SUFFIX:
    case EXPRESSION_TYPE_UNITARY_INCREASE_PREFIX:
    case EXPRESSION_TYPE_UNITARY_DECREASE_SUFFIX:
    case EXPRESSION_TYPE_UNITARY_DECREASE_PREFIX:
        generate_vmcode_from_increase_decrease_expression(executer, expression, opcode_buffer, need_duplicate);
        break;

    case EXPRESSION_TYPE_RELATIONAL_EQ:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_RELATIONAL_EQ_INT);
        break;
    case EXPRESSION_TYPE_RELATIONAL_NE:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_RELATIONAL_NE_INT);
        break;
    case EXPRESSION_TYPE_RELATIONAL_GT:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_RELATIONAL_GT_INT);
        break;
    case EXPRESSION_TYPE_RELATIONAL_GE:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_RELATIONAL_GE_INT);
        break;
    case EXPRESSION_TYPE_RELATIONAL_LT:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_RELATIONAL_LT_INT);
        break;
    case EXPRESSION_TYPE_RELATIONAL_LE:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_RELATIONAL_LE_INT);
        break;

    case EXPRESSION_TYPE_ASSIGN:
        generate_vmcode_from_assign_expression(executer, expression->u.assign_expression, opcode_buffer);
        break;

    case EXPRESSION_TYPE_FUNCTION_CALL:
        generate_vmcode_from_function_call_expression(executer, expression->u.function_call_expression, opcode_buffer);
        break;

    case EXPRESSION_TYPE_CAST:
        generate_vmcode_from_cast_expression(executer, expression->u.cast_expression, opcode_buffer);
        break;

    case EXPRESSION_TYPE_TERNARY:
        generate_vmcode_from_ternary_condition_expression(executer, expression->u.ternary_expression, opcode_buffer);
        break;

    default:
        break;
    }
}

void generate_vmcode_from_assign_expression(Ring_VirtualMachine_Executer* executer, AssignExpression* expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == NULL) {
        return;
    }
    if (expression->type != ASSIGN_EXPRESSION_TYPE_ASSIGN) {
        // += -= *= /=
        generate_vmcode_from_expression(executer, expression->left, opcode_buffer, 1);
    }

    if (expression->type == ASSIGN_EXPRESSION_TYPE_MULTI_ASSIGN) {
        Expression* pos;
        for (pos = expression->operand; pos; pos = pos->next) {
            generate_vmcode_from_expression(executer, pos, opcode_buffer, 1);
        }
    } else {
        generate_vmcode_from_expression(executer, expression->operand, opcode_buffer, 1);
    }

    unsigned int opcode_offset = 0;
    if (expression->operand->convert_type != NULL && expression->operand->convert_type->basic_type == RING_BASIC_TYPE_DOUBLE) {
        opcode_offset += 1;
    }

    switch (expression->type) {
    case ASSIGN_EXPRESSION_TYPE_ASSIGN:
        /* code */
        break;
    case ASSIGN_EXPRESSION_TYPE_MULTI_ASSIGN:
        break;

    case ASSIGN_EXPRESSION_TYPE_ADD_ASSIGN:
        generate_vmcode(executer, opcode_buffer, RVM_CODE_ADD_INT + opcode_offset, 0);
        break;
    case ASSIGN_EXPRESSION_TYPE_SUB_ASSIGN:
        generate_vmcode(executer, opcode_buffer, RVM_CODE_SUB_INT + opcode_offset, 0);
        break;
    case ASSIGN_EXPRESSION_TYPE_MUL_ASSIGN:
        generate_vmcode(executer, opcode_buffer, RVM_CODE_MUL_INT + opcode_offset, 0);
        break;
    case ASSIGN_EXPRESSION_TYPE_DIV_ASSIGN:
        generate_vmcode(executer, opcode_buffer, RVM_CODE_DIV_INT + opcode_offset, 0);
        break;
    case ASSIGN_EXPRESSION_TYPE_MOD_ASSIGN:
        generate_vmcode(executer, opcode_buffer, RVM_CODE_MOD_INT + opcode_offset, 0);
        break;

    default:
        break;
    }

    if (expression->left->type != EXPRESSION_TYPE_IDENTIFIER) {
        fprintf(stderr, "generate opcode error\n");
        exit(ERROR_CODE_GENERATE_OPCODE_ERROR);
    }

    if (expression->type == ASSIGN_EXPRESSION_TYPE_MULTI_ASSIGN) {
        // access identifier in reverse order.
        generate_pop_to_leftvalue_reverse(executer, expression->left, opcode_buffer);
    } else {
        generate_pop_to_leftvalue(executer, expression->left->u.identifier_expression, opcode_buffer);
    }
}

void generate_pop_to_leftvalue_reverse(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == NULL) {
        return;
    }

    generate_pop_to_leftvalue_reverse(executer, expression->next, opcode_buffer);
    generate_pop_to_leftvalue(executer, expression->u.identifier_expression, opcode_buffer);
}

void generate_pop_to_leftvalue(Ring_VirtualMachine_Executer* executer, IdentifierExpression* identifier_expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (identifier_expression == NULL) {
        return;
    }
    Declaration* declaration = identifier_expression->u.declaration;

    unsigned int variable_index = declaration->variable_index;
    RVM_Opcode   opcode         = RVM_CODE_UNKNOW;
    if (declaration->is_local) {
        // 局部变量
        opcode = convert_opcode_by_rvm_type(RVM_CODE_POP_STACK_BOOL, declaration->type);
    } else {
        // 全局变量
        opcode = convert_opcode_by_rvm_type(RVM_CODE_POP_STATIC_BOOL, declaration->type);
    }
    generate_vmcode(executer, opcode_buffer, opcode, variable_index);
}

void generate_vmcode_from_logical_expression(Ring_VirtualMachine_Executer* executer, BinaryExpression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == NULL) {
        return;
    }

    Expression*  left      = expression->left_expression;
    Expression*  right     = expression->right_expression;
    unsigned int end_label = 0;

    if (opcode == RVM_CODE_LOGICAL_AND) {
        generate_vmcode_from_expression(executer, left, opcode_buffer, 1);

        generate_vmcode(executer, opcode_buffer, RVM_CODE_DUPLICATE, 0);
        end_label = opcode_buffer_get_label(opcode_buffer);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, end_label);

        generate_vmcode_from_expression(executer, right, opcode_buffer, 1);

        generate_vmcode(executer, opcode_buffer, opcode, 0);
    } else if (opcode == RVM_CODE_LOGICAL_OR) {
        generate_vmcode_from_expression(executer, left, opcode_buffer, 1);

        generate_vmcode(executer, opcode_buffer, RVM_CODE_DUPLICATE, 0);
        end_label = opcode_buffer_get_label(opcode_buffer);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_TRUE, end_label);

        generate_vmcode_from_expression(executer, right, opcode_buffer, 1);

        generate_vmcode(executer, opcode_buffer, opcode, 0);
    }

    opcode_buffer_set_label(opcode_buffer, end_label, opcode_buffer->code_size);
}

void generate_vmcode_from_binary_expression(Ring_VirtualMachine_Executer* executer, BinaryExpression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == NULL) {
        return;
    }
    Expression* left  = expression->left_expression;
    Expression* right = expression->right_expression;


    if (opcode == RVM_CODE_CONCAT) {
        goto END;
    }

    if (left->convert_type != NULL && left->convert_type->basic_type == RING_BASIC_TYPE_STRING
        && right->convert_type != NULL && right->convert_type->basic_type == RING_BASIC_TYPE_STRING) {
        // TODO: 要在语义检查里严格检查
        // 肯定是eq ne gt ge lt le
        opcode += 2;
        goto END;
    }


    if (left->type == EXPRESSION_TYPE_LITERAL_DOUBLE
        || right->type == EXPRESSION_TYPE_LITERAL_DOUBLE) {
        opcode += 1;
    } else if ((left->convert_type != NULL && left->convert_type->basic_type == RING_BASIC_TYPE_DOUBLE)
               || (right->convert_type != NULL && right->convert_type->basic_type == RING_BASIC_TYPE_DOUBLE)) {
        opcode += 1;
    }

END:
    generate_vmcode_from_expression(executer, left, opcode_buffer, 1);
    generate_vmcode_from_expression(executer, right, opcode_buffer, 1);

    generate_vmcode(executer, opcode_buffer, opcode, 0);
}

void generate_vmcode_from_increase_decrease_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer, int need_duplicate) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == NULL) {
        return;
    }

    Expression* unitary_expression = expression->u.unitary_expression;
    generate_vmcode_from_expression(executer, unitary_expression, opcode_buffer, 1);

    switch (expression->type) {
    case EXPRESSION_TYPE_UNITARY_INCREASE_SUFFIX:
        /* generate_vmcode(executer, opcode_buffer, ); */
        if (need_duplicate) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_DUPLICATE, 0);
        }
        generate_vmcode(executer, opcode_buffer, RVM_CODE_INCREASE_SUFFIX, 0);
        break;
    case EXPRESSION_TYPE_UNITARY_INCREASE_PREFIX:
        generate_vmcode(executer, opcode_buffer, RVM_CODE_INCREASE_PREFIX, 0);
        if (need_duplicate) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_DUPLICATE, 0);
        }
        break;
    case EXPRESSION_TYPE_UNITARY_DECREASE_SUFFIX:
        if (need_duplicate) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_DUPLICATE, 0);
        }
        generate_vmcode(executer, opcode_buffer, RVM_CODE_DECREASE_SUFFIX, 0);
        break;
    case EXPRESSION_TYPE_UNITARY_DECREASE_PREFIX:
        generate_vmcode(executer, opcode_buffer, RVM_CODE_DECREASE_PREFIX, 0);
        if (need_duplicate) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_DUPLICATE, 0);
        }
        break;
    default: break;
    }


    generate_pop_to_leftvalue(executer, unitary_expression->u.identifier_expression, opcode_buffer);
}

void generate_vmcode_from_unitary_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == NULL) {
        return;
    }

    generate_vmcode_from_expression(executer, expression, opcode_buffer, 1);

    generate_vmcode(executer, opcode_buffer, opcode, 0);
}

void generate_vmcode_from_identifier_expression(Ring_VirtualMachine_Executer* executer, IdentifierExpression* identifier_expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (identifier_expression == NULL) {
        return;
    }
    RVM_Opcode   opcode = RVM_CODE_UNKNOW;
    unsigned int offset = 0;
    switch (identifier_expression->type) {
    case IDENTIFIER_EXPRESSION_TYPE_VARIABLE:
        if (identifier_expression->u.declaration->is_local) {
            opcode = convert_opcode_by_rvm_type(RVM_CODE_PUSH_STACK_BOOL, identifier_expression->u.declaration->type);
        } else {
            opcode = convert_opcode_by_rvm_type(RVM_CODE_PUSH_STATIC_BOOL, identifier_expression->u.declaration->type);
        }
        offset = identifier_expression->u.declaration->variable_index;
        generate_vmcode(executer, opcode_buffer, opcode, offset);
        break;

    case IDENTIFIER_EXPRESSION_TYPE_VARIABLE_ARRAY:
        break;

    case IDENTIFIER_EXPRESSION_TYPE_FUNCTION:
        // find func index
        offset = identifier_expression->u.function->func_index;
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_FUNC, offset);
        break;

    default:
        break;
    }
}

void generate_vmcode_from_bool_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == NULL) {
        return;
    }
    if (!expression->u.bool_literal) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_BOOL, RVM_FALSE);
    } else {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_BOOL, RVM_TRUE);
    }
}

void generate_vmcode_from_int_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == NULL) {
        return;
    }
    assert(expression->type == EXPRESSION_TYPE_LITERAL_INT);

    if (0 <= expression->u.int_literal && expression->u.int_literal < 256) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_INT_1BYTE, expression->u.int_literal);
    } else if (256 <= expression->u.int_literal && expression->u.int_literal < 65536) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_INT_2BYTE, expression->u.int_literal);
    } else {
        int constant_index = constant_pool_add_int(executer, expression->u.int_literal);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_INT, constant_index);
    }
}

void generate_vmcode_from_double_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == NULL) {
        return;
    }
    assert(expression->type == EXPRESSION_TYPE_LITERAL_DOUBLE);

    int constant_index = constant_pool_add_double(executer, expression->u.double_literal);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_DOUBLE, constant_index);
}

void generate_vmcode_from_string_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    // 都放在常量区
    assert(expression->type == EXPRESSION_TYPE_LITERAL_STRING);
    int constant_index = constant_pool_add_string(executer, expression->u.string_literal);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_STRING, constant_index);
}

void generate_vmcode_from_function_call_expression(Ring_VirtualMachine_Executer* executer, FunctionCallExpression* function_call_expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (function_call_expression == NULL) {
        return;
    }
    ArgumentList* pos                = function_call_expression->argument_list;
    unsigned int  argument_list_size = 0;
    for (; pos != NULL; pos = pos->next) {
        generate_vmcode_from_expression(executer, pos->expression, opcode_buffer, 1);
        argument_list_size++;
    }

    generate_vmcode(executer, opcode_buffer, RVM_CODE_ARGUMENT_NUM, argument_list_size);

    generate_vmcode_from_expression(executer, function_call_expression->function_identifier_expression, opcode_buffer, 1);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_INVOKE_FUNC, 0);
}

void generate_vmcode_from_cast_expression(Ring_VirtualMachine_Executer* executer, CastExpression* cast_expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (cast_expression == NULL) {
        return;
    }

    generate_vmcode_from_expression(executer, cast_expression->operand, opcode_buffer, 1);
    RVM_Opcode opcode = RVM_CODE_UNKNOW;

    // FIXME: derive type
    switch (cast_expression->type->basic_type) {
    case RING_BASIC_TYPE_BOOL:
        if (cast_expression->operand->convert_type != NULL
            && cast_expression->operand->convert_type->basic_type == RING_BASIC_TYPE_INT) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_CAST_INT_TO_BOOL, 0);
        } else if (cast_expression->operand->convert_type != NULL
                   && cast_expression->operand->convert_type->basic_type == RING_BASIC_TYPE_DOUBLE) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_CAST_DOUBLE_TO_INT, 0);
            generate_vmcode(executer, opcode_buffer, RVM_CODE_CAST_INT_TO_BOOL, 0);
        }
        break;
    case RING_BASIC_TYPE_INT:
        if (cast_expression->operand->convert_type != NULL
            && cast_expression->operand->convert_type->basic_type == RING_BASIC_TYPE_BOOL) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_CAST_BOOL_TO_INT, 0);
        } else if (cast_expression->operand->convert_type != NULL
                   && cast_expression->operand->convert_type->basic_type == RING_BASIC_TYPE_DOUBLE) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_CAST_DOUBLE_TO_INT, 0);
        }
        break;

    case RING_BASIC_TYPE_DOUBLE:
        if (cast_expression->operand->convert_type != NULL
            && cast_expression->operand->convert_type->basic_type == RING_BASIC_TYPE_BOOL) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_CAST_BOOL_TO_INT, 0);
            generate_vmcode(executer, opcode_buffer, RVM_CODE_CAST_INT_TO_DOUBLE, 0);
        } else if (cast_expression->operand->convert_type != NULL
                   && cast_expression->operand->convert_type->basic_type == RING_BASIC_TYPE_INT) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_CAST_INT_TO_DOUBLE, 0);
        }
        break;
    default:
        break;
    }
    // generate_vmcode(executer, opcode_buffer, opcode, 0);
}

void generate_vmcode_from_ternary_condition_expression(Ring_VirtualMachine_Executer* executer, TernaryExpression* ternary_expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (ternary_expression == NULL) {
        return;
    }

    unsigned int if_false_jump_label = 0;
    unsigned int if_end_label        = 0;

    generate_vmcode_from_expression(executer, ternary_expression->condition_expression, opcode_buffer, 1);

    if_false_jump_label = opcode_buffer_get_label(opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, if_false_jump_label);

    generate_vmcode_from_expression(executer, ternary_expression->true_expression, opcode_buffer, 1);

    if_end_label = opcode_buffer_get_label(opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, if_end_label);


    opcode_buffer_set_label(opcode_buffer, if_false_jump_label, opcode_buffer->code_size);

    generate_vmcode_from_expression(executer, ternary_expression->false_expression, opcode_buffer, 1);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, if_end_label);

    opcode_buffer_set_label(opcode_buffer, if_end_label, opcode_buffer->code_size);
}

void generate_vmcode(Ring_VirtualMachine_Executer* executer, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode, unsigned int oper_num) {
    debug_log_with_darkgreen_coloar("\t");
    if (opcode_buffer->code_capacity == opcode_buffer->code_size) {
        // FIXME:
        opcode_buffer->code_capacity += 3000;
    }

    RVM_Opcode_Info opcode_info                          = RVM_Opcode_Infos[opcode];
    opcode_buffer->code_list                             = realloc(opcode_buffer->code_list, opcode_buffer->code_capacity * sizeof(RVM_Byte));
    opcode_buffer->code_list[opcode_buffer->code_size++] = opcode; // 操作码

    switch (opcode_info.type) {
    case OPCODE_OPERAND_TYPE_0BYTE:
        break;

    case OPCODE_OPERAND_TYPE_1BYTE:
        opcode_buffer->code_list[opcode_buffer->code_size++] = oper_num;
        break;

    case OPCODE_OPERAND_TYPE_2BYTE:
        opcode_buffer->code_list[opcode_buffer->code_size++] = (RVM_Byte)(oper_num >> 8);
        opcode_buffer->code_list[opcode_buffer->code_size++] = (RVM_Byte)(oper_num & 0Xff);
        break;

    default: break;
    }
}

int constant_pool_grow(Ring_VirtualMachine_Executer* executer, unsigned int growth_size) {
    debug_log_with_darkgreen_coloar("\t");
    int old_size = executer->constant_pool_size;
    executer->constant_pool_size += growth_size;

    executer->constant_pool_list = realloc(executer->constant_pool_list,
                                           executer->constant_pool_size * sizeof(RVM_ConstantPool));

    return old_size;
}

int constant_pool_add_int(Ring_VirtualMachine_Executer* executer, int int_literal) {
    debug_log_with_darkgreen_coloar("\t");
    int index = constant_pool_grow(executer, 1);

    executer->constant_pool_list[index].type        = CONSTANTPOOL_TYPE_INT;
    executer->constant_pool_list[index].u.int_value = int_literal;
    return index;
}

int constant_pool_add_double(Ring_VirtualMachine_Executer* executer, double double_literal) {
    debug_log_with_darkgreen_coloar("\t");
    int index = constant_pool_grow(executer, 1);

    executer->constant_pool_list[index].type           = CONSTANTPOOL_TYPE_DOUBLE;
    executer->constant_pool_list[index].u.double_value = double_literal;
    return index;
}

int constant_pool_add_string(Ring_VirtualMachine_Executer* executer, char* string_literal) {
    debug_log_with_darkgreen_coloar("\t");
    int index = constant_pool_grow(executer, 1);

    RVM_ConstantPool new_value;
    new_value.type                      = CONSTANTPOOL_TYPE_STRING;
    new_value.u.string_value            = string_literal;
    executer->constant_pool_list[index] = new_value;

    executer->constant_pool_list[index].type           = CONSTANTPOOL_TYPE_STRING;
    executer->constant_pool_list[index].u.string_value = string_literal;
    return index;
}


unsigned int opcode_buffer_get_label(RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    unsigned int old_index = opcode_buffer->lable_size;

    if (opcode_buffer->lable_capacity <= opcode_buffer->code_size) {
        opcode_buffer->lable_capacity += 1024;
        opcode_buffer->lable_list = realloc(opcode_buffer->lable_list,
                                            sizeof(RVM_LabelTable) * opcode_buffer->lable_capacity);
    }

    opcode_buffer->lable_list[opcode_buffer->lable_size].label_name    = NULL;
    opcode_buffer->lable_list[opcode_buffer->lable_size].label_address = 0; // update in opcode_buffer_set_label
    opcode_buffer->lable_size++;


    return old_index;
}

void opcode_buffer_set_label(RVM_OpcodeBuffer* opcode_buffer, unsigned int label, unsigned int label_address) {
    debug_log_with_darkgreen_coloar("\t");
    opcode_buffer->lable_list[label].label_address = label_address;
}

void opcode_buffer_fix_label(RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");

    unsigned int label;
    unsigned int label_address;

    for (unsigned int i = 0; i < opcode_buffer->code_size;) {
        RVM_Byte opcode = opcode_buffer->code_list[i];
        if (opcode <= RVM_CODE_UNKNOW || opcode >= RVM_CODES_NUM) {
            fprintf(stderr, "generate vm code: opcode_buffer_fix_label(opcode is valid:%d)\n", opcode);
            exit(ERROR_CODE_GENERATE_OPCODE_ERROR);
        }
        RVM_Opcode_Info opcode_info = RVM_Opcode_Infos[opcode];

        switch (opcode) {
        case RVM_CODE_JUMP:
        case RVM_CODE_JUMP_IF_FALSE:
        case RVM_CODE_JUMP_IF_TRUE:
            label         = (opcode_buffer->code_list[i + 1] << 8) + (opcode_buffer->code_list[i + 2]);
            label_address = opcode_buffer->lable_list[label].label_address;

            opcode_buffer->code_list[i + 1] = (RVM_Byte)(label_address >> 8);
            opcode_buffer->code_list[i + 2] = (RVM_Byte)(label_address & 0Xff);
            break;

        default:
            break;
        }


        switch (opcode_info.type) {
        case OPCODE_OPERAND_TYPE_0BYTE:
            i++;
            break;

        case OPCODE_OPERAND_TYPE_1BYTE:
            i += 2;
            break;

        case OPCODE_OPERAND_TYPE_2BYTE:
            i += 3;
            break;

        default:
            fprintf(stderr, "opcode_buffer_fix_label(opcode is valid:%d)\n", opcode);
            exit(ERROR_CODE_GENERATE_OPCODE_ERROR);
            break;
        }
    }
}

RVM_Opcode convert_opcode_by_rvm_type(RVM_Opcode opcode, TypeSpecifier* type) {
    debug_log_with_darkgreen_coloar("\t");
    assert(type != NULL);

    if (!(opcode == RVM_CODE_POP_STATIC_BOOL
          || opcode == RVM_CODE_PUSH_STATIC_BOOL
          || opcode == RVM_CODE_POP_STACK_BOOL
          || opcode == RVM_CODE_PUSH_STACK_BOOL)) {
        fprintf(stderr, "convert_opcode_by_rvm_type error(opcode is valid:%d)\n", opcode);
        exit(ERROR_CODE_GENERATE_OPCODE_ERROR);
        return RVM_CODE_UNKNOW;
    }

    switch (type->basic_type) {
    case RING_BASIC_TYPE_BOOL:
        return opcode;
        break;
    case RING_BASIC_TYPE_INT:
        return opcode + 1;
        break;
    case RING_BASIC_TYPE_DOUBLE:
        return opcode + 2;
        break;
    case RING_BASIC_TYPE_STRING:
        return opcode + 3;
        break;

    default:
        fprintf(stderr, "generate opcode error\n");
        exit(ERROR_CODE_GENERATE_OPCODE_ERROR);
        break;
    }

    return RVM_CODE_UNKNOW;
}

unsigned int calc_runtime_stack_capacity(RVM_Byte* code_list, unsigned int code_size) {
    return 0;
}

