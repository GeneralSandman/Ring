#include <assert.h>
#include "ring.h"
#include "parser.h"

void create_statement_list(Statement *statement) {
    debug_log_with_yellow_coloar("statement->type:%d", statement->type);
    ring_interpreter_init_statement_list(statement);
}

void statement_list_add_item(Statement *statement) {
    debug_log_with_yellow_coloar("statement->type:%d", statement->type);

    ring_interpreter_add_statement(statement);
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

    Variable *old_variable_list = NULL;
    old_variable_list           = get_ring_interpreter()->variable_list;
    variable->next              = old_variable_list;

    get_ring_interpreter()->variable_list = variable;

    return statement;
}

void add_function_definition(Function *function_definition) {
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
    debug_log_with_yellow_coloar("identifier:%s", identifier);

    Function *function;
    function = (Function *)malloc(sizeof(function));

    function->line_number         = get_ring_interpreter_line_number();
    function->type                = type;
    function->function_name       = identifier;
    function->parameter_list_size = 0;
    function->parameter_list      = parameter_list;
    function->block_size          = 0;
    function->block               = block;
    function->inner_func          = NULL;
    function->next                = NULL;

    return function;
}
