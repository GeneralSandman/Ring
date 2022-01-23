#include <assert.h>
#include "ring.h"
#include "parser.h"

void create_statement_list(Statement *statement) {
#ifdef DEBUG
    print_debug_info("\t");
#endif
    ring_interpreter_init_statement_list(statement);
}

void statement_list_add_item(Statement *statement) {
#ifdef DEBUG
    printf("[DEBUG][parser.c][function:statement_list_add_item]\t\n");
#endif

    ring_interpreter_add_statement(statement);
}

Statement *create_statemen_from_expression(Expression *expression) {
#ifdef DEBUG
    printf("[DEBUG][parser.c][function:create_statemen_from_expression]\t \n");
#endif

    Statement *statement = NULL;
    statement            = (Statement *)malloc(sizeof(Statement));

    statement->type         = STATEMENT_TYPE_EXPRESSION;
    statement->line_number  = get_ring_interpreter_line_number();
    statement->u.expression = expression;
    statement->next         = NULL;
    return statement;
}

Statement *create_statement_from_variable(Variable *variable) {
#ifdef DEBUG
    printf("[DEBUG][parser.c][function:create_statement_from_variable]\t \n");
#endif

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

Expression *create_expression() {
#ifdef DEBUG
    printf("[DEBUG][parser.c][function:create_expression]\t \n");
#endif

    Expression *expression = NULL;
    expression             = (Expression *)malloc(sizeof(Expression));

    return expression;
}

Expression *create_expression_(FunctionCallExpression *function_call_expression) {
#ifdef DEBUG
    printf("[DEBUG][parser.c][function:create_expression_]\t \n");
#endif

    Expression *expression = NULL;
    expression             = (Expression *)malloc(sizeof(Expression));

    expression->type                       = EXPRESSION_TYPE_FUNCTION_CALL;
    expression->u.function_call_expression = function_call_expression;
    return expression;
}

Expression *create_expression__(AssignExpression *assign_expression) {
#ifdef DEBUG
    printf("[DEBUG][parser.c][function:create_expression__]\t \n");
#endif

    Expression *expression = NULL;
    expression             = (Expression *)malloc(sizeof(Expression));

    expression->type                = EXPRESSION_TYPE_ASSIGN;
    expression->u.assign_expression = assign_expression;
    return expression;
}

Expression *create_expression_binary(ExpressionType type, Expression *left, Expression *right) {
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
#ifdef DEBUG
    printf("[DEBUG][parser.c][function:create_assign_expression]\t identifier(%s) \n", identifier);
#endif

    AssignExpression *assing_expression = NULL;
    assing_expression                   = (AssignExpression *)malloc(sizeof(AssignExpression));

    assing_expression->assign_identifier = identifier;
    assing_expression->expression        = expression;
    return assing_expression;
}

FunctionCallExpression *create_function_call_expression(char *identifier, ArgumentList *argument_list) {
#ifdef DEBUG
    printf("[DEBUG][parser.c][function:create_function_call_expression]\tidentifier(%s)\n", identifier);
#endif

    FunctionCallExpression *function_call_expression = NULL;
    function_call_expression                         = (FunctionCallExpression *)malloc(sizeof(FunctionCallExpression));

    function_call_expression->current_line_number = 0;
    function_call_expression->function_name       = identifier;
    function_call_expression->argument_list       = argument_list;
    return function_call_expression;
}

ArgumentList *create_argument_list(char *argument) {
#ifdef DEBUG
    printf("[DEBUG][parser.c][function:create_argument_list]\targument(%s)\n", argument);
#endif

    ArgumentList *argument_list = NULL;
    argument_list               = (ArgumentList *)malloc(sizeof(ArgumentList));

    argument_list->type                            = ARGUMENT_TYPE_RING_BASICVALUE;
    argument_list->u.ring_basic_value.string_value = argument;
    argument_list->next                            = NULL;
    return argument_list;
}

Identifier *new_identifier(IdentifierType type, char *name) {
    Identifier *identifier;
    identifier = (Identifier *)malloc(sizeof(Identifier));

    identifier->type            = type;
    identifier->identifier_name = name;
    identifier->next            = NULL;

    return identifier;
}