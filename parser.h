#ifndef PARSER_INCLUDE_H
#define PARSER_INCLUDE_H

#include <stdio.h>
#include <stdlib.h>
#include "ring.h"

Statement *             create_statement_list();
Statement *             create_statemen();
Expression *            create_expression();
FunctionCallExpression *create_function_call_expression();
ArgumentList *          create_argument_list();

#endif