#include "ring.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_statement_list(Statement* statement) {
    debug_log_with_yellow_coloar("statement->type:%d", statement->type);
    ring_compiler_init_statement_list(statement);
}

void statement_list_add_item(Statement* statement) {
    debug_log_with_yellow_coloar("statement->type:%d", statement->type);

    ring_compiler_add_statement(statement);
}

Statement* statement_list_add_item2(Statement* statement) {
    debug_log_with_yellow_coloar("statement->type:%d", statement->type);
    return NULL;
}

Statement* statement_list_add_item3(Statement* statement_list, Statement* statement) {
    debug_log_with_yellow_coloar("statement->type:%d", statement->type);

    Statement* pos = statement_list;
    for (; pos->next != NULL; pos = pos->next)
        ;
    pos->next = statement;
    return statement_list;
}

Statement* create_statemen_from_expression(Expression* expression) {
    debug_log_with_yellow_coloar("expression->type:%d", expression->type);

    Statement* statement    = malloc(sizeof(Statement));
    statement->type         = STATEMENT_TYPE_EXPRESSION;
    statement->line_number  = get_ring_compiler_line_number();
    statement->u.expression = expression;
    statement->next         = NULL;
    return statement;
}

Statement* create_statement_from_variable(Variable* variable) {
    debug_log_with_yellow_coloar("variable->type:%d", variable->type);

    Statement* statement   = malloc(sizeof(Statement));
    statement->type        = STATEMENT_TYPE_VARIABLE_DEFINITION;
    statement->line_number = get_ring_compiler_line_number();
    statement->u.variable  = variable;
    statement->next        = NULL;

    variable->next                     = get_ring_compiler()->variable_list;
    get_ring_compiler()->variable_list = variable;
    // TODO: 在这里重写，修改变量的可见范围

    get_ring_compiler()->variable_list_size = 0;
    for (Variable* pos = variable; pos; pos = pos->next) {
        get_ring_compiler()->variable_list_size++;
    }

    return statement;
}

Statement* create_return_statement(Expression* expression) {
    debug_log_with_yellow_coloar("expression->type:%d", expression->type);

    Statement* statement           = malloc(sizeof(Statement));
    statement->type                = STATEMENT_TYPE_RETURN;
    statement->line_number         = get_ring_compiler_line_number();
    statement->u.return_expression = expression;
    statement->next                = NULL;
    return statement;
}

void add_function_definition(Function* function_definition) {
    assert(function_definition != NULL);
    debug_log_with_yellow_coloar("function_definition->type:%d", function_definition->type);

    Function* pos = get_ring_compiler()->function_list;

    get_ring_compiler()->function_list_size++;
    if (pos == NULL) {
        get_ring_compiler()->function_list = function_definition;
        return;
    }

    for (; pos->next; pos = pos->next) {
    }

    pos->next = function_definition;
}

Expression* create_expression() {
    // debug_log_with_yellow_coloar("function_definition->type:%d", function_definition->type);

    Expression* expression = malloc(sizeof(Expression));

    return expression;
}

Expression* create_expression_identifier(char* identifier) {
    debug_log_with_yellow_coloar("identifier:%s", identifier);

    IdentifierExpression* identifier_expression = malloc(sizeof(IdentifierExpression));
    identifier_expression->line_number          = get_ring_compiler_line_number();
    identifier_expression->type                 = IDENTIFIER_EXPRESSION_TYPE_VARIABLE;
    identifier_expression->identifier           = identifier;
    identifier_expression->u.declaration        = NULL;

    Expression* expression              = malloc(sizeof(Expression));
    expression->line_number             = get_ring_compiler_line_number();
    expression->type                    = EXPRESSION_TYPE_IDENTIFIER;
    expression->u.identifier_expression = identifier_expression;
    expression->next                    = NULL;

    return expression;
}

Expression* create_expression_identifier2(char* identifier, IdentifierExpressionType type) {
    debug_log_with_yellow_coloar("identifier:%s", identifier);

    IdentifierExpression* identifier_expression = malloc(sizeof(IdentifierExpression));
    identifier_expression->line_number          = get_ring_compiler_line_number();
    identifier_expression->type                 = type;
    identifier_expression->identifier           = identifier;
    identifier_expression->u.declaration        = NULL;

    Expression* expression              = malloc(sizeof(Expression));
    expression->line_number             = get_ring_compiler_line_number();
    expression->type                    = EXPRESSION_TYPE_IDENTIFIER;
    expression->u.identifier_expression = identifier_expression;

    return expression;
}

Expression* create_expression_identifier_with_index(char* identifier, Expression* index) {
    debug_log_with_yellow_coloar("identifier:%s", identifier);

    ArrayIndexExpression* array_index_expression = malloc(sizeof(ArrayIndexExpression));
    array_index_expression->line_number          = get_ring_compiler_line_number();
    array_index_expression->variable_identifier  = identifier;
    array_index_expression->index_expression     = index;

    Expression* expression               = malloc(sizeof(Expression));
    expression->line_number              = get_ring_compiler_line_number();
    expression->type                     = EXPRESSION_TYPE_ARRAY_INDEX;
    expression->u.array_index_expression = array_index_expression;

    return expression;
}

Expression* create_expression_(FunctionCallExpression* function_call_expression) {
    debug_log_with_yellow_coloar("function_call_expression->name:");

    Expression* expression                 = malloc(sizeof(Expression));
    expression->line_number                = get_ring_compiler_line_number();
    expression->type                       = EXPRESSION_TYPE_FUNCTION_CALL;
    expression->u.function_call_expression = function_call_expression;
    return expression;
}

Expression* create_expression__(AssignExpression* assign_expression) {
    // debug_log_with_yellow_coloar("assign_expression->assign_identifier:%s", assign_expression->assign_identifier);

    Expression* expression          = malloc(sizeof(Expression));
    expression->line_number         = get_ring_compiler_line_number();
    expression->type                = EXPRESSION_TYPE_ASSIGN;
    expression->u.assign_expression = assign_expression;
    return expression;
}

Expression* create_expression_ternary(Expression* condition, Expression * true, Expression * false) {
    Expression* expression                                 = malloc(sizeof(Expression));
    expression->line_number                                = get_ring_compiler_line_number();
    expression->type                                       = EXPRESSION_TYPE_TERNARY;
    expression->u.ternary_expression                       = malloc(sizeof(TernaryExpression));
    expression->u.ternary_expression->condition_expression = condition;
    expression->u.ternary_expression->true_expression      = true;
    expression->u.ternary_expression->false_expression     = false;
    return expression;
}

Expression* create_expression_binary(ExpressionType type, Expression* left, Expression* right) {
    debug_log_with_yellow_coloar("type:%d", type);

    Expression* expression                            = malloc(sizeof(Expression));
    expression->line_number                           = get_ring_compiler_line_number();
    expression->type                                  = type;
    expression->u.binary_expression                   = malloc(sizeof(BinaryExpression));
    expression->u.binary_expression->left_expression  = left;
    expression->u.binary_expression->right_expression = right;

    return expression;
}

Expression* create_expression_unitary(ExpressionType type, Expression* unitary_expression) {
    debug_log_with_yellow_coloar("type:%d", type);

    Expression* expression           = malloc(sizeof(Expression));
    expression->line_number          = get_ring_compiler_line_number();
    expression->convert_type         = BASICVALUE_TYPE_UNKNOW;
    expression->type                 = type;
    expression->u.unitary_expression = unitary_expression;
    expression->next                 = NULL;

    return expression;
}

// ring.bison.y 中 第一个参数是 VariableType
// 该定义       中 第一个参数是 BasicValueType
// TODO: 这里以后统一
Expression* create_expression_unitary_with_convert_type(BasicValueType convert_type, Expression* expression) {
    debug_log_with_yellow_coloar("convert_type:%d", convert_type);

    assert(expression != NULL);
    expression->convert_type = convert_type; // enum 转换一下

    return expression;
}

Expression*
create_expression_literal(ExpressionType type, char* literal_interface) {
    debug_log_with_yellow_coloar("type:%d", type);

    assert(literal_interface != NULL);
    Expression* expression  = malloc(sizeof(Expression));
    expression->line_number = get_ring_compiler_line_number();

    expression->type = type;
    switch (type) {
    case EXPRESSION_TYPE_LITERAL_INT:
        sscanf(literal_interface, "%d", &(expression->u.int_literal));
        break;
    case EXPRESSION_TYPE_LITERAL_DOUBLE:
        sscanf(literal_interface, "%lf", &expression->u.double_literal);
        break;
    case EXPRESSION_TYPE_LITERAL_STRING:
        // TODO: 这里不太对，可能要开辟新的内存
        expression->u.string_literal = literal_interface;
        // sscanf(literal_interface, "%s", expression->u.string_literal);
        break;
    default:
        break;
    }

    return expression;
}

Expression* create_expression_bool_literal(ExpressionType type, Ring_Bool value) {
    debug_log_with_yellow_coloar("type:%d, boolean:%d", type, value);

    Expression* expression     = malloc(sizeof(Expression));
    expression->line_number    = get_ring_compiler_line_number();
    expression->type           = type;
    expression->u.bool_literal = value;

    return expression;
}

Expression* create_cast_expression(CastType cast_type, Expression* operand) {
    debug_log_with_yellow_coloar("cast_type:%d", cast_type);


    Expression* expression                     = malloc(sizeof(Expression));
    expression->line_number                    = get_ring_compiler_line_number();
    expression->type                           = EXPRESSION_TYPE_CAST;
    expression->u.cast_expression              = malloc(sizeof(CastExpression));
    expression->u.cast_expression->line_number = get_ring_compiler_line_number();
    expression->u.cast_expression->type        = cast_type;
    expression->u.cast_expression->operand     = operand;

    return expression;
}

AssignExpression* create_assign_expression(AssignExpressionType type, Expression* left, Expression* operand) {
    AssignExpression* assing_expression = malloc(sizeof(AssignExpression));

    assing_expression->line_number = get_ring_compiler_line_number();
    assing_expression->type        = type;
    assing_expression->left        = left;
    assing_expression->operand     = operand;
    return assing_expression;
}

AssignExpression* create_multi_assign_expression(char* first_identifier, Identifier* identifier_list, Expression* operand) {
    // TODO: 这里要判断一下，identifier是不是已经定义过了，并且identifier 不是函数，还要涉及到identifier重复的问题。
    debug_log_with_yellow_coloar("");

    Expression* left = NULL;
    left             = create_expression_identifier(first_identifier);

    Expression* prev = left;
    for (Identifier* pos = identifier_list; pos; pos = pos->next) {
        prev->next = create_expression_identifier(pos->identifier_name);
        prev       = prev->next;
    }

    AssignExpression* assing_expression = malloc(sizeof(AssignExpression));

    assing_expression->line_number = get_ring_compiler_line_number();
    assing_expression->type        = ASSIGN_EXPRESSION_TYPE_MULTI_ASSIGN;
    assing_expression->left        = left;
    assing_expression->operand     = operand;
    return assing_expression;
}

FunctionCallExpression* create_function_call_expression(char* identifier, ArgumentList* argument_list) {
    debug_log_with_yellow_coloar("identifier:%s", identifier);

    Expression* function_identifier_expression = create_expression_identifier2(identifier, IDENTIFIER_EXPRESSION_TYPE_FUNCTION);

    FunctionCallExpression* function_call_expression         = malloc(sizeof(FunctionCallExpression));
    function_call_expression->line_number                    = get_ring_compiler_line_number();
    function_call_expression->function_identifier_expression = function_identifier_expression;
    function_call_expression->argument_list                  = argument_list;
    return function_call_expression;
}

Expression* expression_list_add_item(Expression* expression_list, Expression* expression) {
    debug_log_with_yellow_coloar("");

    Expression* pos = expression_list;
    for (; pos->next != NULL; pos = pos->next)
        ;
    pos->next = expression;
    return expression_list;
}

ArgumentList* argument_list_add_item3(ArgumentList* argument_list, ArgumentList* argument) {
    ArgumentList* pos = argument_list;
    for (; pos->next != NULL; pos = pos->next)
        ;
    pos->next = argument;
    return argument_list;
}

ArgumentList* create_argument_list_from_expression(Expression* expression) {
    debug_log_with_yellow_coloar("expression->type:%d", expression->type);

    ArgumentList* argument_list = malloc(sizeof(ArgumentList));
    argument_list->expression   = expression;
    argument_list->next         = NULL;
    return argument_list;
}

Identifier* new_identifier(IdentifierType type, char* name) {
    debug_log_with_yellow_coloar("identifier name:%s", name);

    Identifier* identifier      = malloc(sizeof(Identifier));
    identifier->type            = type;
    identifier->identifier_name = name;
    identifier->next            = NULL;

    return identifier;
}

Identifier* identifier_list_add_item(Identifier* identifier_list, Identifier* identifier) {
    Identifier* pos = identifier_list;
    for (; pos->next != NULL; pos = pos->next)
        ;
    pos->next = identifier;
    return identifier_list;
}

FunctionReturnList* create_function_return_list(VariableType variable_type) {
    FunctionReturnList* return_list = malloc(sizeof(FunctionReturnList*));

    return_list->variable_type = variable_type;
    return_list->next          = NULL;

    return return_list;
}

FunctionReturnList* function_return_list_add_item(FunctionReturnList* return_list, VariableType variable_type) {
    FunctionReturnList* pos = return_list;
    for (; pos->next != NULL; pos = pos->next)
        ;
    pos->next = create_function_return_list(variable_type);
    return return_list;
}

Function* new_function_definition(FunctionType type, char* identifier, Variable* parameter_list, FunctionReturnList* return_list, Block* block) {
    debug_log_with_yellow_coloar("functionType:%d, identifier:%s", type, identifier);

    // FIXME:
    if (!strcmp(identifier, "println_bool")
        || !strcmp(identifier, "println_int")
        || !strcmp(identifier, "println_double")
        || !strcmp(identifier, "println_string")
        || !strcmp(identifier, "debug_assert")
        || !strcmp(identifier, "exit")) {
        type = FUNCTION_TYPE_NATIVE;
    }

    Function* function            = malloc(sizeof(Function));
    function->line_number         = get_ring_compiler_line_number();
    function->func_index          = get_ring_compiler()->function_list_size;
    function->type                = type;
    function->function_name       = identifier;
    function->parameter_list_size = 0;
    function->parameter_list      = parameter_list;
    function->variable_list_size  = 0;
    function->variable_list       = NULL;
    function->block               = block;
    function->inner_func          = NULL;
    function->next                = NULL;

    // 把函数参数的变量添加到 variable_list 中
    for (Variable* pos = parameter_list; pos != NULL; pos = pos->next) {
        Variable* tmp = new_variable(VARIABLE_TYPE_UNKNOW, NULL, NULL, 0);
        memcpy(tmp, pos, sizeof(*pos));

        tmp->next               = function->variable_list;
        function->variable_list = tmp;
    }

    // 把block中定义的局部变量加到 variable_list 中
    if (block != NULL) {
        block->type = BLOCK_TYPE_FUNCTION;
        for (Statement* pos = block->statement_list; pos != NULL; pos = pos->next) {
            if (pos->type == STATEMENT_TYPE_VARIABLE_DEFINITION) {
                Variable* tmp = new_variable(VARIABLE_TYPE_UNKNOW, NULL, NULL, 0);
                memcpy(tmp, pos->u.variable, sizeof(*pos->u.variable));

                tmp->next               = function->variable_list;
                function->variable_list = tmp;
            }
        }
    }
    return function;
}

Statement* create_statement_from_if(IfStatement* if_statement) {
    debug_log_with_yellow_coloar("\t");

    Statement* statement      = malloc(sizeof(Statement));
    statement->line_number    = get_ring_compiler_line_number();
    statement->type           = STATEMENT_TYPE_IF;
    statement->u.if_statement = if_statement;
    statement->next           = NULL;

    return statement;
}

IfStatement* create_if_statement(Expression* expression, Block* if_block, ElseIfStatement* elseif_statement_list, Block* else_block) {
    debug_log_with_yellow_coloar("\t");

    IfStatement* if_statement          = malloc(sizeof(IfStatement));
    if_statement->line_number          = get_ring_compiler_line_number();
    if_statement->condition_expression = expression;
    if_statement->if_block             = if_block;
    if_statement->elseif_list          = elseif_statement_list;
    if_statement->else_block           = else_block;

    if (if_block) {
        if_block->type = BLOCK_TYPE_IF;
    }
    if (else_block) {
        else_block->type = BLOCK_TYPE_IF;
    }

    return if_statement;
}

ElseIfStatement* create_elseif_statement(Expression* expression, Block* elseif_block) {
    debug_log_with_yellow_coloar("\t");

    ElseIfStatement* elseif_statement      = malloc(sizeof(ElseIfStatement));
    elseif_statement->line_number          = get_ring_compiler_line_number();
    elseif_statement->condition_expression = expression;
    elseif_statement->elseif_block         = elseif_block;
    elseif_statement->next                 = NULL;

    if (elseif_block) {
        elseif_block->type = BLOCK_TYPE_IF;
    }

    return elseif_statement;
}

ElseIfStatement* elseif_statement_add_item(ElseIfStatement* list, ElseIfStatement* elseif_statement) {
    debug_log_with_yellow_coloar("\t");

    assert(list != NULL);

    ElseIfStatement* pos;
    for (pos = list; pos->next != NULL; pos = pos->next) {
    }

    pos->next = elseif_statement;

    return list;
}

Statement* create_statement_from_for(ForStatement* for_statement) {
    debug_log_with_yellow_coloar("\t");

    Statement* statement       = malloc(sizeof(Statement));
    statement->line_number     = get_ring_compiler_line_number();
    statement->type            = STATEMENT_TYPE_FOR;
    statement->u.for_statement = for_statement;
    statement->next            = NULL;

    return statement;
}

ForStatement* create_for_statement(Expression* init_expression, Expression* condition_expression, Expression* post_expression, Block* block) {
    debug_log_with_yellow_coloar("\t");

    ForStatement* for_statement         = malloc(sizeof(ForStatement));
    for_statement->line_number          = get_ring_compiler_line_number();
    for_statement->init_expression      = init_expression;
    for_statement->condition_expression = condition_expression;
    for_statement->post_expression      = post_expression;
    for_statement->block                = block;

    if (block) {
        block->type = BLOCK_TYPE_FOR;
    }

    return for_statement;
}

Statement* create_statement_from_dofor(DoForStatement* dofor_statement) {
    debug_log_with_yellow_coloar("\t");

    Statement* statement         = malloc(sizeof(Statement));
    statement->line_number       = get_ring_compiler_line_number();
    statement->type              = STATEMENT_TYPE_DOFOR;
    statement->u.dofor_statement = dofor_statement;
    statement->next              = NULL;

    return statement;
}

DoForStatement* create_dofor_statement(Expression* init_expression, Block* block, Expression* condition_expression, Expression* post_expression) {
    debug_log_with_yellow_coloar("\t");

    DoForStatement* dofor_statement       = malloc(sizeof(DoForStatement));
    dofor_statement->line_number          = get_ring_compiler_line_number();
    dofor_statement->init_expression      = init_expression;
    dofor_statement->block                = block;
    dofor_statement->condition_expression = condition_expression;
    dofor_statement->post_expression      = post_expression;

    if (block) {
        block->type = BLOCK_TYPE_DOFOR;
    }

    return dofor_statement;
}

Statement* create_statement_from_break(BreakStatement* break_statement) {
    debug_log_with_yellow_coloar("\t");

    Statement* statement         = malloc(sizeof(Statement));
    statement->line_number       = get_ring_compiler_line_number();
    statement->type              = STATEMENT_TYPE_BREAK;
    statement->u.break_statement = break_statement;
    statement->next              = NULL;

    return statement;
}

BreakStatement* create_break_statement(char* literal_interface) {
    debug_log_with_yellow_coloar("\t");

    unsigned int break_loop_num = 0;
    if (literal_interface == NULL || strlen(literal_interface) == 0) {
        break_loop_num = 1;
    } else {
        sscanf(literal_interface, "%ud", &break_loop_num);
        // TODO: check break_loop_num valid
    }

    BreakStatement* break_statement = malloc(sizeof(BreakStatement));
    break_statement->line_number    = get_ring_compiler_line_number();
    break_statement->break_loop_num = break_loop_num;

    return break_statement;
}


Statement* create_statement_from_continue(ContinueStatement* continue_statement) {
    debug_log_with_yellow_coloar("\t");

    Statement* statement            = malloc(sizeof(Statement));
    statement->line_number          = get_ring_compiler_line_number();
    statement->type                 = STATEMENT_TYPE_CONTINUE;
    statement->u.continue_statement = continue_statement;
    statement->next                 = NULL;

    return statement;
}

ContinueStatement* create_continue_statement() {
    ContinueStatement* continue_statement = malloc(sizeof(ContinueStatement));
    continue_statement->line_number       = get_ring_compiler_line_number();

    return continue_statement;
}
// Block* create_block(Statement* statement_list) {
//     debug_log_with_yellow_coloar("\t");
//
//     Block* block                 = malloc(sizeof(Block));
//     block->line_number           = get_ring_compiler_line_number();
//     block->declaration_list_size = 0;
//     block->declaration_list      = NULL;
//     block->statement_list_size   = 0;
//     block->statement_list        = statement_list;
//     block->parent_block          = NULL;
//
//     for (Statement* pos = statement_list; pos; pos = pos->next) {
//         block->statement_list_size++;
//     }
//
//     // TODO: 这里不要直接赋值，要扫描statment_list 把变量加到当前变量列表中
//     return block;
// }

Block* start_new_block() {
    debug_log_with_yellow_coloar("\t");


    Block* block                       = malloc(sizeof(Block));
    block->line_number                 = get_ring_compiler_line_number();
    block->type                        = BLOCK_TYPE_UNKNOW;
    block->declaration_list_size       = 0;
    block->declaration_list            = NULL;
    block->statement_list_size         = 0;
    block->statement_list              = NULL;
    block->parent_block                = get_ring_compiler()->current_block;
    block->block_labels.break_label    = 0;
    block->block_labels.continue_label = 0;

    /* printf("[start] parent:%p, current:%p\n", block->parent_block, block); */

    get_ring_compiler()->current_block = block;

    return block;
}
Block* finish_block(Block* block, Statement* statement_list) {
    debug_log_with_yellow_coloar("\t");
    assert(block == get_ring_compiler()->current_block);

    block->statement_list = statement_list;
    for (Statement* pos = statement_list; pos; pos = pos->next) {
        block->statement_list_size++;
    }

    get_ring_compiler()->current_block = block->parent_block;

    /* printf("[end] current:%p, parent:%p\n", block, block->parent_block); */
    return block;
}

// 标识符合法性检查
// 其实这个用不到，flex是有优先级的，会有语法错误
// 检查变量是否重复定义
int identifier_check_valid(char* identifier) {
    return 0;
}

Variable* variable_list_add_item(Variable* variable_list, Variable* variable) {
    Variable* pos = variable_list;
    for (; pos->next != NULL; pos = pos->next)
        ;
    pos->next = variable;

    return variable_list;
}

Variable* new_variable(VariableType type, char* identifier, Expression* init_expression, int is_const) {
    debug_log_with_yellow_coloar("\t type(%d),identifier(%s)", type, identifier);

    Variable* variable           = malloc(sizeof(Variable));
    variable->line_number        = get_ring_compiler_line_number();
    variable->is_const           = is_const;
    variable->type               = type;
    variable->variable_identifer = identifier;
    variable->u.ring_basic_value = NULL;
    variable->init_expression    = init_expression;
    variable->next               = NULL;

    insert_identifier(IDENTIFIER_TYPE_VARIABLE, identifier);
    return variable;
}

Variable* new_variable_array(VariableType type, Expression* size, char* identifier, Expression* init_expression, int is_const) {
    debug_log_with_yellow_coloar("\t type(%d),identifier(%s)", type, identifier);

    // 这个应该放到解释的时候

    Variable* variable           = malloc(sizeof(Variable));
    variable->line_number        = get_ring_compiler_line_number();
    variable->is_const           = is_const;
    variable->type               = VARIABLE_TYPE_ARRAY;
    variable->array_member_type  = type;
    variable->variable_identifer = identifier;
    variable->u.ring_basic_value = NULL;
    variable->init_expression    = init_expression;
    variable->next               = NULL;

    insert_identifier(IDENTIFIER_TYPE_VARIABLE, identifier);
    return variable;
}

// 定义一个变量、函数时 都要执行改操作
// 确保：
//   1. 名称不能重复
//   2. 不能给函数复制
//   3. 不能用变量去调用函数
void insert_identifier(IdentifierType type, char* name) {
    Identifier* identifier;
    identifier = new_identifier(type, name);

    identifier->next                     = get_ring_compiler()->identifier_list;
    get_ring_compiler()->identifier_list = identifier;
}

void check_identifier_valid(char* identifier_name) {
}

// -
TypeSpecifier* create_type_specifier(Ring_BasicType basic_type) {
    debug_log_with_yellow_coloar("basic_type:%d", basic_type);

    TypeSpecifier* type_specifier = malloc(sizeof(TypeSpecifier));
    type_specifier->basic_type    = basic_type;
    type_specifier->derive_type   = NULL;
    return type_specifier;
}

Declaration* create_declaration(TypeSpecifier* type, char* identifier, Expression* initializer) {
    debug_log_with_yellow_coloar("identifier:%s", identifier);

    Declaration* declaration    = malloc(sizeof(Declaration));
    declaration->line_number    = get_ring_compiler_line_number();
    declaration->type           = type;
    declaration->identifier     = identifier;
    declaration->initializer    = initializer;
    declaration->is_const       = 0;
    declaration->is_local       = 0;
    declaration->variable_index = -1; // fix in fix_ast.c
    declaration->next           = NULL;
    return declaration;
}

Declaration* declaration_list_add_item(Declaration* head, Declaration* declaration) {
    if (head == NULL) {
        return declaration;
    }

    Declaration* pos = head;
    for (; pos->next != NULL; pos = pos->next) {}
    pos->next = declaration;
    return head;
}


Statement* create_declaration_statement(TypeSpecifier* type, char* identifier, Expression* initializer) {
    debug_log_with_yellow_coloar("identifier:%s", identifier);

    Statement* statement               = malloc(sizeof(Statement));
    statement->line_number             = get_ring_compiler_line_number();
    statement->type                    = STATEMENT_TYPE_DECLARATION;
    statement->u.declaration_statement = create_declaration(type, identifier, initializer);
    statement->next                    = NULL;

    return statement;
}
