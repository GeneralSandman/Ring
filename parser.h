#ifndef PARSER_INCLUDE_H
#define PARSER_INCLUDE_H

#include <stdio.h>
#include <stdlib.h>
#include "ring.h"

void                    create_statement_list();
void                    statement_list_add_item();
Statement *             create_statemen_from_expression();
Statement *             create_statement_from_variable(Variable *variable);
Expression *            create_expression();
Expression *            create_expression_identifier(char *identifier);
Expression *            create_expression_(FunctionCallExpression *function_call_expression);
Expression *            create_expression__(AssignExpression *assign_expression);
Expression *            create_expression_binary(ExpressionType type, Expression *left, Expression *right);
Expression *            create_expression_literal(ExpressionType type, char *literal_interface);
AssignExpression *      create_assign_expression(char *identifier, Expression *expression);
FunctionCallExpression *create_function_call_expression();
ArgumentList *          create_argument_list();
ArgumentList *          create_argument_list_from_expression(Expression *expression);
Identifier *            new_identifier(IdentifierType type, char *name);

#endif