#include "ring.h"
#include "parser.h"

StatementList *create_statement_list() {
    StatementList *statement_list = NULL;

    statement_list = (StatementList *)malloc(sizeof(StatementList));

    return statement_list;
}

StatementList *statement_list_add_item(StatementList *statement_list, Statement *statement) {
}

Statement *create_statemen() {
    Statement *statement = NULL;

    statement = (Statement *)malloc(sizeof(Statement));

    return statement;
}

Expression *create_expression() {
    Expression *expression = NULL;

    expression = (Expression *)malloc(sizeof(Expression));

    return expression;
}

FunctionCallExpression *create_function_call_expression(char *identifier, ArgumentList *argument_list) {
    FunctionCallExpression *function_call_expression = NULL;

    function_call_expression = (FunctionCallExpression *)malloc(sizeof(FunctionCallExpression));

    function_call_expression->function_name = identifier;
    function_call_expression->argument_list = argument_list;

    return function_call_expression;
}

ArgumentList *create_argument_list(char *argument) {
    ArgumentList *argument_list = NULL;

    argument_list = (ArgumentList *)malloc(sizeof(ArgumentList));

    argument_list->type                             = ARGUMENT_TYPE_RING_BASICVALUE;
    argument_list->u.ring_basic_value->string_value = argument;
    argument_list->next                             = NULL;

    return argument_list;
}