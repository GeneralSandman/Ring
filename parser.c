#include "ring.h"
#include "parser.h"
#include "interpreter.h"

Statement *create_statement_list(Statement *statement) {
    printf("[DEBUG][parser.c][function:create_statement_list]\t\n");
    ring_interpreter_init_statement_list(statement);
}

Statement *statement_list_add_item(Statement *statement) {
    printf("[DEBUG][parser.c][function:statement_list_add_item]\t\n");
    ring_interpreter_add_statement(statement);
}

Statement *create_statemen() {
    Statement *statement = NULL;
    statement            = (Statement *)malloc(sizeof(Statement));

    statement->type         = STATEMENT_TYPE_EXPRESSION;
    statement->line_number  = 0;
    statement->u.expression = NULL;
    statement->next         = NULL;
    return statement;
}

Expression *create_expression() {
    Expression *expression = NULL;
    expression             = (Expression *)malloc(sizeof(Expression));

    return expression;
}

Expression *create_expression_(FunctionCallExpression *function_call_expression) {
    Expression *expression = NULL;
    expression             = (Expression *)malloc(sizeof(Expression));

    expression->type                       = EXPRESSION_TYPE_FUNCTION_CALL;
    expression->u.function_call_expression = function_call_expression;
    return expression;
}

FunctionCallExpression *create_function_call_expression(char *identifier, ArgumentList *argument_list) {
    printf("[DEBUG][parser.c][function:create_function_call_expression]\tidentifier(%s)\n", identifier);

    FunctionCallExpression *function_call_expression = NULL;
    function_call_expression                         = (FunctionCallExpression *)malloc(sizeof(FunctionCallExpression));

    function_call_expression->function_name = identifier;
    function_call_expression->argument_list = argument_list;
    return function_call_expression;
}

ArgumentList *create_argument_list(char *argument) {
    ArgumentList *argument_list = NULL;
    argument_list               = (ArgumentList *)malloc(sizeof(ArgumentList));

    argument_list->type                             = ARGUMENT_TYPE_RING_BASICVALUE;
    argument_list->u.ring_basic_value->string_value = argument;
    argument_list->next                             = NULL;
    return argument_list;
}