#include "ring.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

RVM_Opcode_Info RVM_Opcode_Infos[] = {
    {RVM_CODE_UNKNOW, "", OPCODE_OPERAND_TYPE_UNKNOW},

    // push
    {RVM_CODE_PUSH_INT_1BYTE, "push_int_1byte", OPCODE_OPERAND_TYPE_1BYTE}, // 后边紧跟 int 常量 1 type
    {RVM_CODE_PUSH_INT_2BYTE, "push_int_2byte", OPCODE_OPERAND_TYPE_2BYTE}, // 后边紧跟 int 常量 2 type
    {RVM_CODE_PUSH_INT, "push_int", OPCODE_OPERAND_TYPE_2BYTE},             // 后边紧跟 int 常量 2 的索引 这里的还要 改一下 OPCODE_OPERAND_TYPE_2BYTE

    {RVM_CODE_PUSH_DOUBLE, "push_double", OPCODE_OPERAND_TYPE_2BYTE}, // 后边紧跟 int 常量 2 的索引

    {RVM_CODE_PUSH_STRING, "push_string", OPCODE_OPERAND_TYPE_2BYTE}, // 后边紧跟 int 常量 2 的索引

    // pop
    {RVM_CODE_POP_STATIC_INT, "pop_static_int", OPCODE_OPERAND_TYPE_2BYTE}, // 全局变量的赋值  这里后续要扩展成2 byte，面的index不够

    {RVM_CODE_PUSH_STATIC_INT, "push_static_int", OPCODE_OPERAND_TYPE_2BYTE},


    //
    {RVM_CODE_ADD_INT, "add_int", OPCODE_OPERAND_TYPE_0BYTE},
    {RVM_CODE_SUB_INT, "sub_int", OPCODE_OPERAND_TYPE_0BYTE},
    {RVM_CODE_MUL_INT, "mul_int", OPCODE_OPERAND_TYPE_0BYTE},
    {RVM_CODE_DIV_INT, "div_int", OPCODE_OPERAND_TYPE_0BYTE},
    {RVM_CODE_MOD_INT, "mod_int", OPCODE_OPERAND_TYPE_0BYTE},

    //
    {RVM_CODE_LOGICAL_AND, "logical_and", OPCODE_OPERAND_TYPE_0BYTE},
    {RVM_CODE_LOGICAL_OR, "logical_or", OPCODE_OPERAND_TYPE_0BYTE},

    //
    {RVM_CODE_JUMP, "jump", OPCODE_OPERAND_TYPE_2BYTE},
    {RVM_CODE_JUMP_IF_FALSE, "jump_if_false", OPCODE_OPERAND_TYPE_2BYTE},
    {RVM_CODE_JUMP_IF_TRUE, "jump_if_true", OPCODE_OPERAND_TYPE_2BYTE},

    //
    {RVM_CODE_PUSH_FUNC, "push_func", OPCODE_OPERAND_TYPE_1BYTE}, // TODO: update to 2 byte
    {RVM_CODE_INVOKE_FUNC, "invoke_func", OPCODE_OPERAND_TYPE_0BYTE},


};

Ring_VirtualMachine_Executer* new_ring_vm_executer() {
    Ring_VirtualMachine_Executer* executer = malloc(sizeof(Ring_VirtualMachine_Executer));
    executer->constant_pool_size           = 0;
    executer->constant_pool_list           = NULL;
    executer->global_variable_size         = 0;
    executer->global_variable_list         = NULL;
    executer->function_size                = 0;
    executer->function_list                = NULL;
    executer->code_size                    = 0;
    executer->code_list                    = NULL;
    return executer;
}

// 生成 RVM 虚拟机代码
void ring_generate_vm_code(Ring_Compiler* compiler, Ring_VirtualMachine_Executer* vm_executer) {
    add_global_variable(compiler, vm_executer);
    add_functions(compiler, vm_executer);
    add_top_level_code(compiler, vm_executer);

#ifdef DEBUG
    vm_executer_dump(vm_executer);
#endif
}

// 添加全局变量
void add_global_variable(Ring_Compiler* compiler, Ring_VirtualMachine_Executer* vm_executer) {
    // FIXME: 在 Compiler 中大部分是链表：因为在编译的时候不确定存储空间
    // 在 Executer 中 大部分是数组，因为编译完成，存储空间的数量都已经确认了。
    if (compiler->declaration_list_size == 0) {
        return;
    }

    vm_executer->global_variable_size = compiler->declaration_list_size;
    vm_executer->global_variable_list = malloc(vm_executer->global_variable_size * sizeof(RVM_Variable));

    Declaration* pos = compiler->declaration_list;
    int          i   = 0;
    for (; pos; pos = pos->next, i++) {
        vm_executer->global_variable_list[i].identifier = pos->identifier;
        vm_executer->global_variable_list[i].type       = pos->type; // TODO: 这里考虑要深度复制
    }
}

// 添加函数定义
void add_functions(Ring_Compiler* compiler, Ring_VirtualMachine_Executer* vm_executer) {
    Function*    pos                = compiler->function_list;
    unsigned int function_list_size = compiler->function_list_size;
    unsigned int i                  = 0;

    vm_executer->function_size = function_list_size;
    vm_executer->function_list = malloc(sizeof(RVM_Function) * function_list_size);

    // 暂时只处理 native function
    for (; pos; pos = pos->next, i++) {
        copy_function(pos, &vm_executer->function_list[i]);
    }
}

void copy_function(Function* src, RVM_Function* dest) {
    dest->type      = RVM_FUNCTION_TYPE_NATIVE;
    dest->func_name = src->function_name;
}

// 添加顶层代码
void add_top_level_code(Ring_Compiler* compiler, Ring_VirtualMachine_Executer* vm_executer) {
    RVM_OpcodeBuffer* opcode_buffer = new_opcode_buffer();
    generate_vmcode_from_statement_list(vm_executer, compiler->statement_list, opcode_buffer);

    opcode_buffer_fix_label(opcode_buffer);

    RVM_Byte*    code_list = opcode_buffer->code_list;
    unsigned int code_size = opcode_buffer->code_size;
    // unsigned int code_capacity = opcode_buffer->code_capacity;

    vm_executer->code_list = code_list;
    vm_executer->code_size = code_size;
}

void vm_executer_dump(Ring_VirtualMachine_Executer* vm_executer) {
    // CLEAR_SCREEN;
    ring_vm_constantpool_dump(vm_executer);
    ring_vm_code_dump(vm_executer, 0, 60, 1);
}

RVM_OpcodeBuffer* new_opcode_buffer() {
    RVM_OpcodeBuffer* buffer = malloc(sizeof(RVM_OpcodeBuffer));
    buffer->code_list        = NULL;
    buffer->code_size        = 0;
    buffer->code_capacity    = 0;
    buffer->lable_list       = NULL;
    buffer->lable_size       = 0;
    buffer->lable_capacity   = 0;
    return buffer;
}

void generate_vmcode_from_block(Ring_VirtualMachine_Executer* vm_executer, Block* block, RVM_OpcodeBuffer* opcode_buffer) {
    generate_vmcode_from_statement_list(vm_executer, block->statement_list, opcode_buffer);
}

void generate_vmcode_from_statement_list(Ring_VirtualMachine_Executer* vm_executer, Statement* statement_list, RVM_OpcodeBuffer* opcode_buffer) {
    for (Statement* statement = statement_list; statement != NULL; statement = statement->next) {
        switch (statement->type) {
        case STATEMENT_TYPE_EXPRESSION:
            generate_vmcode_from_expression(vm_executer, statement->u.expression, opcode_buffer);
            break;

        case STATEMENT_TYPE_IF:
            generate_vmcode_from_if_statement(vm_executer, statement->u.if_statement, opcode_buffer);
            break;

        case STATEMENT_TYPE_FOR:
            generate_vmcode_from_for_statement(vm_executer, statement->u.for_statement, opcode_buffer);
            break;

        case STATEMENT_TYPE_DOFOR:
            generate_vmcode_from_dofor_statement(vm_executer, statement->u.dofor_statement, opcode_buffer);
            break;

        default: break;
        }
    }
}

void generate_vmcode_from_if_statement(Ring_VirtualMachine_Executer* executer, IfStatement* if_statement, RVM_OpcodeBuffer* opcode_buffer) {
    unsigned int if_false_jump_label = 0;
    unsigned int if_end_label        = 0;

    generate_vmcode_from_expression(executer, if_statement->condition_expression, opcode_buffer);

    if_false_jump_label = opcode_buffer_get_label(opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, if_false_jump_label);

    generate_vmcode_from_block(executer, if_statement->if_block, opcode_buffer);

    if_end_label = opcode_buffer_get_label(opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, if_end_label);


    opcode_buffer_set_label(opcode_buffer, if_false_jump_label, opcode_buffer->code_size);

    // handle elseif list
    ElseIfStatement* pos = if_statement->elseif_list;
    for (; pos; pos = pos->next) {
        generate_vmcode_from_expression(executer, pos->condition_expression, opcode_buffer);

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
    unsigned int end_label  = 0;
    unsigned int loop_label = 0;

    // Step-1:
    if (for_statement->init_expression) {
        generate_vmcode_from_expression(executer, for_statement->init_expression, opcode_buffer);
    }
    loop_label = opcode_buffer_get_label(opcode_buffer);
    opcode_buffer_set_label(opcode_buffer, loop_label, opcode_buffer->code_size);

    // Step-2:
    end_label = opcode_buffer_get_label(opcode_buffer);
    if (for_statement->condition_expression) {
        generate_vmcode_from_expression(executer, for_statement->condition_expression, opcode_buffer);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, end_label);
    }

    // Step-3:
    generate_vmcode_from_block(executer, for_statement->block, opcode_buffer);

    // Step-4:
    if (for_statement->post_expression) {
        generate_vmcode_from_expression(executer, for_statement->post_expression, opcode_buffer);
    }

    // Step-5:
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, loop_label);


    // Step-End:

    opcode_buffer_set_label(opcode_buffer, end_label, opcode_buffer->code_size);
}

// TODO: 暂时不支持 break continue
void generate_vmcode_from_dofor_statement(Ring_VirtualMachine_Executer* executer, DoForStatement* dofor_statement, RVM_OpcodeBuffer* opcode_buffer) {
    unsigned int end_label  = 0;
    unsigned int loop_label = 0;


    // Step-1:
    if (dofor_statement->init_expression) {
        generate_vmcode_from_expression(executer, dofor_statement->init_expression, opcode_buffer);
    }
    loop_label = opcode_buffer_get_label(opcode_buffer);
    opcode_buffer_set_label(opcode_buffer, loop_label, opcode_buffer->code_size);


    // Step-2:
    generate_vmcode_from_block(executer, dofor_statement->block, opcode_buffer);


    // Step-3:
    end_label = opcode_buffer_get_label(opcode_buffer);
    if (dofor_statement->condition_expression) {
        generate_vmcode_from_expression(executer, dofor_statement->condition_expression, opcode_buffer);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, end_label);
    }


    // Step-4:
    if (dofor_statement->post_expression) {
        generate_vmcode_from_expression(executer, dofor_statement->post_expression, opcode_buffer);
    }

    // Step-5;
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, loop_label);

    // Step-End;
    opcode_buffer_set_label(opcode_buffer, end_label, opcode_buffer->code_size);
}


void generate_vmcode_from_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer) {
    assert(expression != NULL);

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

    case EXPRESSION_TYPE_LOGICAL_AND:
        generate_vmcode_from_logical_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_LOGICAL_AND);
        break;

    case EXPRESSION_TYPE_LOGICAL_OR:
        generate_vmcode_from_logical_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_LOGICAL_OR);
        break;

    case EXPRESSION_TYPE_ASSIGN:
        generate_vmcode_from_assign_expression(executer, expression->u.assign_expression, opcode_buffer);
        break;

    case EXPRESSION_TYPE_FUNCTION_CALL:
        generate_vmcode_from_function_call_expression(executer, expression->u.function_call_expression, opcode_buffer);
        break;

    default:
        break;
    }
}

void generate_vmcode_from_assign_expression(Ring_VirtualMachine_Executer* executer, AssignExpression* expression, RVM_OpcodeBuffer* opcode_buffer) {
    if (expression->type != ASSIGN_EXPRESSION_TYPE_ASSIGN) {
        // += -= *= /=
        generate_vmcode_from_expression(executer, expression->left, opcode_buffer);
    }

    generate_vmcode_from_expression(executer, expression->operand, opcode_buffer);

    switch (expression->type) {
    case ASSIGN_EXPRESSION_TYPE_ASSIGN:
        /* code */
        break;

    case ASSIGN_EXPRESSION_TYPE_ADD_ASSIGN:
        generate_vmcode(executer, opcode_buffer, RVM_CODE_ADD_INT, 0);
        break;

    case ASSIGN_EXPRESSION_TYPE_SUB_ASSIGN:
        generate_vmcode(executer, opcode_buffer, RVM_CODE_SUB_INT, 0);
        break;

    case ASSIGN_EXPRESSION_TYPE_MUL_ASSIGN:
        generate_vmcode(executer, opcode_buffer, RVM_CODE_MUL_INT, 0);
        break;

    case ASSIGN_EXPRESSION_TYPE_DIV_ASSIGN:
        generate_vmcode(executer, opcode_buffer, RVM_CODE_DIV_INT, 0);
        break;

    case ASSIGN_EXPRESSION_TYPE_MOD_ASSIGN:
        generate_vmcode(executer, opcode_buffer, RVM_CODE_MOD_INT, 0);
        break;

    default:
        break;
    }

    if (expression->left->type != EXPRESSION_TYPE_IDENTIFIER) {
        fprintf(stderr, "generate opcode error\n");
        exit(ERROR_CODE_GENERATE_OPCODE_ERROR);
    }

    generate_pop_to_leftvalue(executer, expression->left->u.identifier_expression, opcode_buffer);
}

void generate_pop_to_leftvalue(Ring_VirtualMachine_Executer* executer, IdentifierExpression* identifier_expression, RVM_OpcodeBuffer* opcode_buffer) {
    Declaration* declaration = identifier_expression->u.declaration;

    unsigned int variable_index = declaration->variable_index;
    generate_vmcode(executer, opcode_buffer, RVM_CODE_POP_STATIC_INT, variable_index);
}

void generate_vmcode_from_logical_expression(Ring_VirtualMachine_Executer* executer, BinaryExpression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode) {
    Expression*  left      = expression->left_expression;
    Expression*  right     = expression->right_expression;
    unsigned int end_label = 0;

    if (opcode == RVM_CODE_LOGICAL_AND) {
        generate_vmcode_from_expression(executer, left, opcode_buffer);

        end_label = opcode_buffer_get_label(opcode_buffer);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, end_label);

        generate_vmcode_from_expression(executer, right, opcode_buffer);

        generate_vmcode(executer, opcode_buffer, opcode, 0);
    } else if (opcode == RVM_CODE_LOGICAL_OR) {
        generate_vmcode_from_expression(executer, left, opcode_buffer);

        end_label = opcode_buffer_get_label(opcode_buffer);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_TRUE, end_label);

        generate_vmcode_from_expression(executer, right, opcode_buffer);

        generate_vmcode(executer, opcode_buffer, opcode, 0);
    }

    opcode_buffer_set_label(opcode_buffer, end_label, opcode_buffer->code_size);
}

void generate_vmcode_from_binary_expression(Ring_VirtualMachine_Executer* executer, BinaryExpression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode) {
    Expression* left  = expression->left_expression;
    Expression* right = expression->right_expression;

    generate_vmcode_from_expression(executer, left, opcode_buffer);
    generate_vmcode_from_expression(executer, right, opcode_buffer);

    generate_vmcode(executer, opcode_buffer, opcode, 0);
}

void generate_vmcode_from_identifier_expression(Ring_VirtualMachine_Executer* executer, IdentifierExpression* identifier_expression, RVM_OpcodeBuffer* opcode_buffer) {
    unsigned int offset = 0;
    switch (identifier_expression->type) {
    case IDENTIFIER_EXPRESSION_TYPE_VARIABLE:
        offset = identifier_expression->u.declaration->variable_index;
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_STATIC_INT, offset);
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
    if (!expression->u.bool_literal) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_INT_1BYTE, 0);
    } else {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_INT_1BYTE, 1);
    }
}

void generate_vmcode_from_int_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer) {
    assert(expression->type == EXPRESSION_TYPE_LITERAL_INT);

    if (0 <= expression->u.int_literal && expression->u.int_literal < 256) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_INT_1BYTE, expression->u.int_literal);
    } else if (expression->u.int_literal < 65536) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_INT_2BYTE, expression->u.int_literal);
    } else {
        int constant_index = constant_pool_add_int(executer, expression->u.int_literal);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_INT, constant_index);
    }
}

void generate_vmcode_from_double_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer) {
    assert(expression->type == EXPRESSION_TYPE_LITERAL_DOUBLE);

    int constant_index = constant_pool_add_double(executer, expression->u.double_literal);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_DOUBLE, constant_index);
}

void generate_vmcode_from_string_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer) {
    // 都放在常量区
    assert(expression->type == EXPRESSION_TYPE_LITERAL_STRING);
    int constant_index = constant_pool_add_string(executer, expression->u.string_literal);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_STRING, constant_index);
}

void generate_vmcode_from_function_call_expression(Ring_VirtualMachine_Executer* executer, FunctionCallExpression* function_call_expression, RVM_OpcodeBuffer* opcode_buffer) {
    ArgumentList* pos = function_call_expression->argument_list;
    for (; pos != NULL; pos = pos->next) {
        generate_vmcode_from_expression(executer, pos->expression, opcode_buffer);
    }

    generate_vmcode_from_expression(executer, function_call_expression->function_identifier_expression, opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_INVOKE_FUNC, 0);
}

void generate_vmcode(Ring_VirtualMachine_Executer* executer, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode, unsigned int int_literal) {
    if (opcode_buffer->code_capacity == 0) {
        opcode_buffer->code_capacity = 2;
    }
    if (opcode_buffer->code_capacity == opcode_buffer->code_size + 2) {
        opcode_buffer->code_capacity *= 2;
    }

    RVM_Opcode_Info opcode_info                          = RVM_Opcode_Infos[opcode];
    opcode_buffer->code_list                             = realloc(opcode_buffer->code_list, opcode_buffer->code_capacity * sizeof(RVM_Byte));
    opcode_buffer->code_list[opcode_buffer->code_size++] = opcode; // 操作码

    switch (opcode_info.type) {
    case OPCODE_OPERAND_TYPE_0BYTE:
        break;

    case OPCODE_OPERAND_TYPE_1BYTE:
        opcode_buffer->code_list[opcode_buffer->code_size++] = int_literal;
        break;

    case OPCODE_OPERAND_TYPE_2BYTE:
        opcode_buffer->code_list[opcode_buffer->code_size++] = (RVM_Byte)(int_literal >> 8);
        opcode_buffer->code_list[opcode_buffer->code_size++] = (RVM_Byte)(int_literal & 0Xff);
        break;

    default: break;
    }
}

int constant_pool_grow(Ring_VirtualMachine_Executer* executer, unsigned int growth_size) {
    int old_size = executer->constant_pool_size;
    executer->constant_pool_size += growth_size;

    executer->constant_pool_list = realloc(executer->constant_pool_list,
                                           executer->constant_pool_size * sizeof(RVM_ConstantPool));

    return old_size;
}

int constant_pool_add_int(Ring_VirtualMachine_Executer* executer, int int_literal) {
    int index = constant_pool_grow(executer, 1);

    RVM_ConstantPool new_value;
    new_value.type                      = CONSTANTPOOL_TYPE_INT;
    new_value.u.int_value               = int_literal;
    executer->constant_pool_list[index] = new_value;

    return index;
}

int constant_pool_add_double(Ring_VirtualMachine_Executer* executer, double double_literal) {
    int index = constant_pool_grow(executer, 1);

    RVM_ConstantPool new_value;
    new_value.type                      = CONSTANTPOOL_TYPE_DOUBLE;
    new_value.u.double_value            = double_literal;
    executer->constant_pool_list[index] = new_value;

    return index;
}

int constant_pool_add_string(Ring_VirtualMachine_Executer* executer, char* string_literal) {
    int index = constant_pool_grow(executer, 1);

    RVM_ConstantPool new_value;
    new_value.type                      = CONSTANTPOOL_TYPE_STRING;
    new_value.u.string_value            = string_literal;
    executer->constant_pool_list[index] = new_value;

    return index;
}


unsigned int opcode_buffer_get_label(RVM_OpcodeBuffer* opcode_buffer) {
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
    opcode_buffer->lable_list[label].label_address = label_address;
}

void opcode_buffer_fix_label(RVM_OpcodeBuffer* opcode_buffer) {
    unsigned int label;
    unsigned int label_address;

    for (unsigned int i = 0; i < opcode_buffer->code_size;) {
        RVM_Byte        opcode      = opcode_buffer->code_list[i];
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

        default: break;
        }
    }
}
