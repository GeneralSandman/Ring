#include <assert.h>
#include <string.h>
#include "ring.h"

void create_statement_list(Statement *statement) {
    debug_log_with_yellow_coloar("statement->type:%d", statement->type);
    ring_interpreter_init_statement_list(statement);
}

void statement_list_add_item(Statement *statement) {
    debug_log_with_yellow_coloar("statement->type:%d", statement->type);

    ring_interpreter_add_statement(statement);
}

Statement *statement_list_add_item2(Statement *statement) {
    debug_log_with_yellow_coloar("statement->type:%d", statement->type);
}

Statement *statement_list_add_item3(Statement *statement_list, Statement *statement) {
    debug_log_with_yellow_coloar("statement->type:%d", statement->type);

    Statement *pos = statement_list;
    for (; pos->next != NULL; pos = pos->next)
        ;
    pos->next = statement;
    return statement_list;
}

Statement *create_statemen_from_expression(Expression *expression) {
    debug_log_with_yellow_coloar("expression->type:%d", expression->type);

    Statement *statement = NULL;
    statement            = (Statement *)malloc(sizeof(Statement));

    statement->type         = STATEMENT_TYPE_EXPRESSION;
    statement->line_number  = get_ring_interpreter_line_number();
    statement->u.expression = expression;
    statement->next         = NULL;
    return statement;
}

Statement *create_statement_from_variable(Variable *variable) {
    debug_log_with_yellow_coloar("variable->type:%d", variable->type);

    Statement *statement = NULL;
    statement            = (Statement *)malloc(sizeof(Statement));

    statement->type        = STATEMENT_TYPE_VARIABLE_DEFINITION;
    statement->line_number = get_ring_interpreter_line_number();
    statement->u.variable  = variable;
    statement->next        = NULL;

    variable->next                        = get_ring_interpreter()->variable_list;
    get_ring_interpreter()->variable_list = variable;
    // TODO: 在这里重写，修改变量的可见范围

    return statement;
}

Statement *create_return_statement(Expression *expression) {
    debug_log_with_yellow_coloar("expression->type:%d", expression->type);

    Statement *statement = NULL;
    statement            = (Statement *)malloc(sizeof(Statement));

    statement->type                = STATEMENT_TYPE_RETURN;
    statement->line_number         = get_ring_interpreter_line_number();
    statement->u.return_expression = expression;
    statement->next                = NULL;
    return statement;
}

void add_function_definition(Function *function_definition) {
    assert(function_definition != NULL);
    debug_log_with_yellow_coloar("function_definition->type:%d", function_definition->type);

    function_definition->next             = get_ring_interpreter()->function_list;
    get_ring_interpreter()->function_list = function_definition;
}

Expression *create_expression() {
    // debug_log_with_yellow_coloar("function_definition->type:%d", function_definition->type);

    Expression *expression = NULL;
    expression             = (Expression *)malloc(sizeof(Expression));

    return expression;
}

Expression *create_expression_identifier(char *identifier) {
    debug_log_with_yellow_coloar("identifier:%s", identifier);

    Expression *expression = NULL;
    expression             = (Expression *)malloc(sizeof(Expression));

    expression->line_number           = get_ring_interpreter_line_number();
    expression->type                  = EXPRESSION_TYPE_VARIABLE;
    expression->u.variable_identifier = identifier;

    return expression;
}

Expression *create_expression_(FunctionCallExpression *function_call_expression) {
    debug_log_with_yellow_coloar("function_call_expression->name:%s", function_call_expression->function_name);

    Expression *expression = NULL;
    expression             = (Expression *)malloc(sizeof(Expression));

    expression->type                       = EXPRESSION_TYPE_FUNCTION_CALL;
    expression->u.function_call_expression = function_call_expression;
    return expression;
}

Expression *create_expression__(AssignExpression *assign_expression) {
    debug_log_with_yellow_coloar("assign_expression->assign_identifier:%s", assign_expression->assign_identifier);

    Expression *expression = NULL;
    expression             = (Expression *)malloc(sizeof(Expression));

    expression->type                = EXPRESSION_TYPE_ASSIGN;
    expression->u.assign_expression = assign_expression;
    return expression;
}

Expression *create_expression_binary(ExpressionType type, Expression *left, Expression *right) {
    debug_log_with_yellow_coloar("type:%d", type);

    Expression *expression = NULL;
    expression             = (Expression *)malloc(sizeof(Expression));

    expression->type                                  = type;
    expression->u.binary_expression                   = (BinaryExpression *)malloc(sizeof(BinaryExpression));
    expression->u.binary_expression->left_expression  = left;
    expression->u.binary_expression->right_expression = right;

    return expression;
}

Expression *
create_expression_literal(ExpressionType type, char *literal_interface) {
    debug_log_with_yellow_coloar("type:%d", type);

    assert(literal_interface != NULL);
    Expression *expression = NULL;
    expression             = (Expression *)malloc(sizeof(Expression));

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

Expression *
create_expression_bool_literal(ExpressionType type, Ring_Bool value) {
    debug_log_with_yellow_coloar("type:%d, boolean:%d", type, boolean);

    Expression *expression = NULL;
    expression             = (Expression *)malloc(sizeof(Expression));

    expression->type           = type;
    expression->u.bool_literal = value;

    return expression;
}

AssignExpression *create_assign_expression(char *identifier, Expression *expression) {
    // TODO: 这里要判断一下，identifier是不是已经定义过了，并且identifier 不是函数，还要涉及到identifier重复的问题。
    debug_log_with_yellow_coloar("identifier:%s", identifier);

    AssignExpression *assing_expression = NULL;
    assing_expression                   = (AssignExpression *)malloc(sizeof(AssignExpression));

    assing_expression->assign_identifier = identifier;
    assing_expression->expression        = expression;
    return assing_expression;
}

FunctionCallExpression *create_function_call_expression(char *identifier, ArgumentList *argument_list) {
    debug_log_with_yellow_coloar("identifier:%s", identifier);

    FunctionCallExpression *function_call_expression = NULL;
    function_call_expression                         = (FunctionCallExpression *)malloc(sizeof(FunctionCallExpression));

    function_call_expression->current_line_number = 0;
    function_call_expression->function_name       = identifier;
    function_call_expression->argument_list       = argument_list;
    return function_call_expression;
}

ArgumentList *argument_list_add_item3(ArgumentList *argument_list, ArgumentList *argument) {
    debug_log_with_yellow_coloar("argument->type:%d", argument->type);

    ArgumentList *pos = argument_list;
    for (; pos->next != NULL; pos = pos->next)
        ;
    pos->next = argument;
    return argument_list;
}

ArgumentList *create_argument_list(char *argument) {
    debug_log_with_yellow_coloar("argument:%s", argument);

    ArgumentList *argument_list = NULL;
    argument_list               = (ArgumentList *)malloc(sizeof(ArgumentList));

    argument_list->type                              = ARGUMENT_TYPE_RING_BASICVALUE;
    argument_list->u.ring_basic_value.type           = BASICVALUE_TYPE_STRING;
    argument_list->u.ring_basic_value.u.string_value = argument;
    argument_list->next                              = NULL;
    return argument_list;
}

ArgumentList *create_argument_list_from_expression(Expression *expression) {
    debug_log_with_yellow_coloar("expression->type:%d", expression->type);

    ArgumentList *argument_list = NULL;
    argument_list               = (ArgumentList *)malloc(sizeof(ArgumentList));

    argument_list->type         = ARGUMENT_TYPE_EXPRESSION;
    argument_list->u.expression = expression;
    argument_list->next         = NULL;
    return argument_list;
}

Identifier *new_identifier(IdentifierType type, char *name) {
    debug_log_with_yellow_coloar("identifier name:%s", name);

    Identifier *identifier;
    identifier = (Identifier *)malloc(sizeof(Identifier));

    identifier->type            = type;
    identifier->identifier_name = name;
    identifier->next            = NULL;

    return identifier;
}

Function *new_function_definition(FunctionType type, char *identifier, Variable *parameter_list, Statement *block) {
    debug_log_with_yellow_coloar("functionType:%d, identifier:%s", type, identifier);

    Function *function;
    function = (Function *)malloc(sizeof(Function));

    function->line_number         = get_ring_interpreter_line_number();
    function->type                = type;
    function->function_name       = identifier;
    function->parameter_list_size = 0;
    function->parameter_list      = parameter_list;
    function->variable_list_size  = 0;
    function->variable_list       = NULL;
    function->block_size          = 0;
    function->block               = block;
    function->inner_func          = NULL;
    function->next                = NULL;

    // 把函数参数的变量添加到 variable_list 中
    for (Variable *pos = parameter_list; pos != NULL; pos = pos->next) {
        Variable *tmp = new_variable(VARIABLE_TYPE_UNKNOW, NULL);
        memcpy(tmp, pos, sizeof(*pos));

        tmp->next               = function->variable_list;
        function->variable_list = tmp;
    }

    // 把block中定义的局部变量加到 variable_list 中
    for (Statement *pos = block; pos != NULL; pos = pos->next) {
        if (pos->type == STATEMENT_TYPE_VARIABLE_DEFINITION) {
            Variable *tmp = new_variable(VARIABLE_TYPE_UNKNOW, NULL);
            memcpy(tmp, pos->u.variable, sizeof(*pos->u.variable));

            tmp->next               = function->variable_list;
            function->variable_list = tmp;
        }
    }

    return function;
}

// 标识符合法性检查
// 其实这个用不到，flex是有优先级的，会有语法错误
// 检查变量是否重复定义
int identifier_check_valid(char *identifier) {
    return 0;
}

Variable *variable_list_add_item(Variable *variable_list, Variable *variable) {
    Variable *pos = variable_list;
    for (; pos->next != NULL; pos = pos->next)
        ;
    pos->next = variable;

    return variable_list;
}

Variable *new_variable(VariableType type, char *identifier) {
    debug_log_with_yellow_coloar("\t type(%d),identifier(%s)", type, identifier);

    Variable *variable;
    variable = (Variable *)malloc(sizeof(Variable));

    variable->type               = type;
    variable->variable_identifer = identifier;
    variable->u.ring_basic_value = NULL;
    variable->next               = NULL;

    insert_identifier(IDENTIFIER_TYPE_VARIABLE, identifier);
    return variable;
}

// 定义一个变量、函数时 都要执行改操作
// 确保：
//   1. 名称不能重复
//   2. 不能给函数复制
//   3. 不能用变量去调用函数
void insert_identifier(IdentifierType type, char *name) {
    Identifier *identifier;
    identifier = new_identifier(type, name);

    identifier->next                        = get_ring_interpreter()->identifier_list;
    get_ring_interpreter()->identifier_list = identifier;
}

void check_identifier_valid(char *identifier_name) {
}
