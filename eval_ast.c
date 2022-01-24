#include <stdio.h>
#include "ring.h"

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

void interpret_expression(Expression *expression) {
    switch (expression->type) {
    case EXPRESSION_TYPE_FUNCTION_CALL:
        /* code */
        invoke_function(expression->u.function_call_expression);
        break;

    case EXPRESSION_TYPE_ASSIGN:
        assign(expression);
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
}

int interpret_binary_expression(Expression *expression) {
#ifdef DEBUG
    print_debug_info("\t");
#endif
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
        break;
    }

    return result;
}

void invoke_function(FunctionCallExpression *function_call_expression) {
    // search_funcaion
    Function *function = NULL;

    for (Function *pos = get_ring_interpreter()->function_list; pos != NULL; pos = function->next) {
        if (!strcmp(pos->function_name, function_call_expression->function_name)) {
            function = pos;
        }
    }

    if (function == NULL) {
        printf("findn't match function\n");
        return;
    }

    function->inner_func(1, function_call_expression->argument_list->u.ring_basic_value.string_value);

    // invoke
}

void assign(Expression *expression) {
    printf("-------------%d\n", interpret_binary_expression(expression->u.assign_expression->expression));
}