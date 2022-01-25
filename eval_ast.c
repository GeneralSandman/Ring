#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "ring.h"

void ring_interpret(Ring_Interpreter *ring_interpreter) {
    debug_log_with_blue_coloar("\t interpret statement: statement_list_size(%d)", ring_interpreter->statement_list_size);

    Statement *p;
    for (p = ring_interpreter->statement_list; p != NULL; p = p->next) {
        debug_log_with_blue_coloar("\t interpret statement: type(%d),line_number(%d)", p->type, p->line_number);
        interpret_statement(p);
    }
}

void interpret_statement(Statement *statement) {
    switch (statement->type) {
    case STATEMENT_TYPE_VARIABLE_DEFINITION:
        break;

    case STATEMENT_TYPE_EXPRESSION:
        interpret_expression(statement->u.expression);
        break;

    default:
        break;
    }
}

Ring_BasicValue *interpret_expression(Expression *expression) {
    Ring_BasicValue *result;

    result = (Ring_BasicValue *)malloc(sizeof(Ring_BasicValue));

    switch (expression->type) {
    case EXPRESSION_TYPE_FUNCTION_CALL:
        /* code */
        invoke_function(expression->u.function_call_expression);
        break;

    case EXPRESSION_TYPE_ASSIGN:
        assign(expression);
        break;

    case EXPRESSION_TYPE_VARIABLE:
        result->type        = BASICVALUE_TYPE_INT;
        result->u.int_value = interpret_variable_expression(expression->u.variable_identifier);
        break;

    case EXPRESSION_TYPE_ARITHMETIC_ADD:
    case EXPRESSION_TYPE_ARITHMETIC_SUB:
    case EXPRESSION_TYPE_ARITHMETIC_MUL:
    case EXPRESSION_TYPE_ARITHMETIC_DIV:
        interpret_binary_expression(expression);
        break;

    default:
        break;
    }

    return result;
}

int interpret_variable_expression(char *variable_identifier) {
    // 查找相应的变量值
    Variable *variable = NULL;

    for (Variable *pos = get_ring_interpreter()->variable_list; pos != NULL; pos = pos->next) {
        if (0 == strcmp(pos->variable_identifer, variable_identifier)) {
            variable = pos;
        }
    }

    if (variable == NULL) {
        printf("findn't match variable\n");
        exit(1);
    }

    return variable->u.ring_basic_value->u.int_value;
}

int interpret_binary_expression(Expression *expression) {
    debug_log_with_blue_coloar();
    // TODO: 还要考虑各个变量的类型
    //       是否涉及到强制类型转换
    //       两边类型不匹配还要编译报错

    int result;

    switch (expression->type) {
    case EXPRESSION_TYPE_LITERAL_INT:
        result = expression->u.int_literal;
        break;

    case EXPRESSION_TYPE_ARITHMETIC_ADD:
        result = interpret_binary_expression(expression->u.binary_expression->left_expression) + interpret_binary_expression(expression->u.binary_expression->right_expression);
        break;
    case EXPRESSION_TYPE_ARITHMETIC_SUB:
        result = interpret_binary_expression(expression->u.binary_expression->left_expression) - interpret_binary_expression(expression->u.binary_expression->right_expression);
        break;
    case EXPRESSION_TYPE_ARITHMETIC_MUL:
        result = interpret_binary_expression(expression->u.binary_expression->left_expression) * interpret_binary_expression(expression->u.binary_expression->right_expression);
        break;
    case EXPRESSION_TYPE_ARITHMETIC_DIV:
        result = interpret_binary_expression(expression->u.binary_expression->left_expression) / interpret_binary_expression(expression->u.binary_expression->right_expression);
        break;
    default:
        // log error
        break;
    }

    return result;
}

void invoke_function(FunctionCallExpression *function_call_expression) {
    debug_log_with_blue_coloar();

    // search_funcaion
    Function *function = NULL;

    for (Function *pos = get_ring_interpreter()->function_list; pos != NULL; pos = function->next) {
        if (0 == strcmp(pos->function_name, function_call_expression->function_name)) {
            function = pos;
        }
    }

    if (function == NULL) {
        printf("findn't match function\n");
        return;
    }

    function->inner_func(1, function_call_expression->argument_list->u.expression);

    // invoke
}

void assign(Expression *expression) {
    debug_log_with_blue_coloar();

    assert(expression->type == EXPRESSION_TYPE_ASSIGN);

    int result = 0;
    result     = interpret_binary_expression(expression->u.assign_expression->expression);

    char *identifier;
    identifier = expression->u.assign_expression->assign_identifier;

    Variable *variable = NULL;

    for (Variable *pos = get_ring_interpreter()->variable_list; pos != NULL; pos = pos->next) {
        if (0 == strcmp(pos->variable_identifer, identifier)) {
            variable = pos;
        }
    }

    if (variable == NULL) {
        printf("findn't match variable\n");
        return;
    }

    variable->u.ring_basic_value              = (Ring_BasicValue *)malloc(sizeof(Ring_BasicValue));
    variable->u.ring_basic_value->type        = BASICVALUE_TYPE_INT;
    variable->u.ring_basic_value->u.int_value = result;
}
