#ifndef PARSER_INCLUDE_H
#define PARSER_INCLUDE_H

#include <stdio.h>
#include <stdlib.h>
#include "ring.h"

void                    create_statement_list();
void                    statement_list_add_item();
Statement *             create_statemen();
Expression *            create_expression();
Expression *            create_expression_(FunctionCallExpression *function_call_expression);
FunctionCallExpression *create_function_call_expression();
ArgumentList *          create_argument_list();

#endif