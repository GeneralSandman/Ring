#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "ring.h"

void ring_interpret(Ring_Interpreter *ring_interpreter) {
    debug_log_with_blue_coloar("\t interpret statement: statement_list_size(%d)", ring_interpreter->statement_list_size);
    interpret_statement_list(ring_interpreter->statement_list, NULL);
}

void interpret_statement_list(Statement *statement, Function *function) {
    Statement *p;
    for (p = statement; p != NULL; p = p->next) {
        debug_log_with_blue_coloar("\t interpret statement: type(%d),line_number(%d)", p->type, p->line_number);
        interpret_statement(p, function);
    }
}

void interpret_statement(Statement *statement, Function *function) {
    switch (statement->type) {
    case STATEMENT_TYPE_VARIABLE_DEFINITION:
        // TODO:
        break;

    case STATEMENT_TYPE_EXPRESSION:
        interpret_expression(statement->u.expression, function);
        break;

    default:
        break;
    }
}

Ring_BasicValue *interpret_expression(Expression *expression, Function *function) {
    debug_log_with_blue_coloar("\t ");

    Ring_BasicValue *result;

    result = (Ring_BasicValue *)malloc(sizeof(Ring_BasicValue));

    switch (expression->type) {
    case EXPRESSION_TYPE_LITERAL_INT:
        result->type        = BASICVALUE_TYPE_INT;
        result->u.int_value = expression->u.int_literal;
        break;
    case EXPRESSION_TYPE_LITERAL_DOUBLE:
        result->type           = BASICVALUE_TYPE_DOUBLE;
        result->u.double_value = expression->u.double_literal;
        break;
    case EXPRESSION_TYPE_LITERAL_STRING:
        result->type           = BASICVALUE_TYPE_STRING;
        result->u.string_value = expression->u.string_literal;
        break;

    case EXPRESSION_TYPE_FUNCTION_CALL:
        /* code */
        invoke_function(expression->u.function_call_expression, function);
        break;

    case EXPRESSION_TYPE_ASSIGN:
        assign(expression, function);
        break;

    case EXPRESSION_TYPE_VARIABLE:
        result = interpret_variable_expression(expression->u.variable_identifier, function);
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

// TODO:
Ring_BasicValue *interpret_variable_expression(char *variable_identifier, Function *function) {
    // 查找相应的变量值
    Variable *variable = NULL;
    // 查找局部变量
    if (function != NULL) {
        for (Variable *pos = function->variable_list; pos != NULL; pos = pos->next) {
            if (0 == strcmp(pos->variable_identifer, variable_identifier)) {
                variable = pos;
            }
        }
    }

    if (variable != NULL) {
        debug_log_with_blue_coloar("find match local variable\n");
    } else {
        // 查找全局变量
        for (Variable *pos = get_ring_interpreter()->variable_list; pos != NULL; pos = pos->next) {
            if (0 == strcmp(pos->variable_identifer, variable_identifier)) {
                variable = pos;
            }
        }
    }

    if (variable == NULL) {
        debug_log_with_blue_coloar("find not match global variable\n");
        return NULL;
    }

    // FIXME: 存在内存泄漏
    Ring_BasicValue *result;

    result = (Ring_BasicValue *)malloc(sizeof(Ring_BasicValue));

    switch (variable->type) {
    case VARIABLE_TYPE_INT:
        result->type        = BASICVALUE_TYPE_INT;
        result->u.int_value = variable->u.ring_basic_value->u.int_value;
        break;
    case VARIABLE_TYPE_DOUBLE:
        result->type           = BASICVALUE_TYPE_DOUBLE;
        result->u.double_value = variable->u.ring_basic_value->u.double_value;
        break;

    case VARIABLE_TYPE_STRING:
        result->type           = BASICVALUE_TYPE_STRING;
        result->u.string_value = variable->u.ring_basic_value->u.string_value;
        break;
    default:
        break;
    }

    return result;
}

Ring_BasicValue *interpret_binary_expression_arithmetic(Expression *expression) {
    debug_log_with_blue_coloar("expression->type:%d", expression->type);
    Ring_BasicValue *result;

    result = (Ring_BasicValue *)malloc(sizeof(Ring_BasicValue));

    Ring_BasicValue *left  = NULL;
    Ring_BasicValue *right = NULL;

    left  = interpret_binary_expression(expression->u.binary_expression->left_expression);
    right = interpret_binary_expression(expression->u.binary_expression->right_expression);

    double left_value   = 0.0;
    double right_value  = 0.0;
    double result_value = 0.0;

    if (left->type == BASICVALUE_TYPE_INT && right->type == BASICVALUE_TYPE_INT) {
        result->type = BASICVALUE_TYPE_INT;
        left_value   = (double)left->u.int_value;
        right_value  = (double)right->u.int_value;
    } else if (left->type == BASICVALUE_TYPE_INT && right->type == BASICVALUE_TYPE_DOUBLE) {
        result->type = BASICVALUE_TYPE_DOUBLE;
        left_value   = (double)left->u.int_value;
        right_value  = (double)right->u.double_value;
    } else if (left->type == BASICVALUE_TYPE_DOUBLE && right->type == BASICVALUE_TYPE_INT) {
        result->type = BASICVALUE_TYPE_DOUBLE;
        left_value   = (double)left->u.double_value;
        right_value  = (double)right->u.int_value;
    } else if (left->type == BASICVALUE_TYPE_DOUBLE && right->type == BASICVALUE_TYPE_DOUBLE) {
        result->type = BASICVALUE_TYPE_DOUBLE;
        left_value   = (double)left->u.double_value;
        right_value  = (double)right->u.double_value;
    }

    switch (expression->type) {
    case EXPRESSION_TYPE_ARITHMETIC_ADD:
        result_value = left_value + right_value;
        break;
    case EXPRESSION_TYPE_ARITHMETIC_SUB:
        result_value = left_value - right_value;
        break;
    case EXPRESSION_TYPE_ARITHMETIC_MUL:
        result_value = left_value * right_value;
        break;
    case EXPRESSION_TYPE_ARITHMETIC_DIV:
        result_value = left_value / right_value;
        break;
    default:
        // log error
        break;
    }

    if (result->type == BASICVALUE_TYPE_INT) {
        result->u.int_value = (int)result_value;
    } else if (result->type == BASICVALUE_TYPE_DOUBLE) {
        result->u.double_value = result_value;
    }

    return result;
}

Ring_BasicValue *interpret_binary_expression(Expression *expression) {
    debug_log_with_blue_coloar("expression->type:%d", expression->type);
    // TODO: 还要考虑各个变量的类型
    //       是否涉及到强制类型转换
    //       两边类型不匹配还要编译报错

    // FIXME: 存在内存泄漏
    Ring_BasicValue *result;

    result = (Ring_BasicValue *)malloc(sizeof(Ring_BasicValue));

    switch (expression->type) {
    case EXPRESSION_TYPE_LITERAL_INT:
        result->type        = BASICVALUE_TYPE_INT;
        result->u.int_value = expression->u.int_literal;
        break;

    case EXPRESSION_TYPE_LITERAL_DOUBLE:
        result->type           = BASICVALUE_TYPE_DOUBLE;
        result->u.double_value = expression->u.double_literal;
        break;

    case EXPRESSION_TYPE_LITERAL_STRING:
        result->type           = BASICVALUE_TYPE_STRING;
        result->u.string_value = expression->u.string_literal;
        break;

    case EXPRESSION_TYPE_VARIABLE:
        // TODO: 找到相应的变量值
        result = search_variable_value(expression->u.variable_identifier);
        break;

    case EXPRESSION_TYPE_ARITHMETIC_ADD:
    case EXPRESSION_TYPE_ARITHMETIC_SUB:
    case EXPRESSION_TYPE_ARITHMETIC_MUL:
    case EXPRESSION_TYPE_ARITHMETIC_DIV:
        result = interpret_binary_expression_arithmetic(expression);
        break;
    default:
        // log error
        break;
    }

    return result;
}

Ring_BasicValue *search_variable_value(char *identifier) {
    Variable *variable = NULL;

    for (Variable *pos = get_ring_interpreter()->variable_list; pos != NULL; pos = pos->next) {
        if (0 == strcmp(pos->variable_identifer, identifier)) {
            variable = pos;
        }
    }

    if (variable == NULL) {
        printf("findn't match variable\n");
        return NULL;
    }
    return variable->u.ring_basic_value;
}

void invoke_function(FunctionCallExpression *function_call_expression, Function *origin_function) { // TODO: origin_function这个名字重新取一下
    debug_log_with_blue_coloar("function_call_expression->function_name:%s", function_call_expression->function_name);

    // search_funcaion
    Function *function = NULL;

    for (Function *pos = get_ring_interpreter()->function_list; pos != NULL; pos = pos->next) {
        if (0 == strcmp(pos->function_name, function_call_expression->function_name)) {
            function = pos;
        }
    }

    if (function == NULL) {
        printf("findn't match function\n");
        return;
    }

    Ring_BasicValue *value;

    switch (function->type) {
    case FUNCTION_TYPE_INNER_LIB:
        value = interpret_expression(function_call_expression->argument_list->u.expression, origin_function);
        function->inner_func(1, value);
        break;

    case FUNCTION_TYPE_EXTERNAL:
        invoke_external_function(function);
        break;

    default:
        break;
    }

    // invoke
}

void invoke_external_function(Function *function) {
    debug_log_with_blue_coloar("");
    interpret_statement_list(function->block, function);
}

void assign(Expression *expression, Function *function) {
    debug_log_with_blue_coloar("expression->type:%d", expression->type);

    assert(expression->type == EXPRESSION_TYPE_ASSIGN);

    Ring_BasicValue *result = NULL;
    // TODO:
    result = interpret_binary_expression(expression->u.assign_expression->expression);

    char *identifier;
    identifier = expression->u.assign_expression->assign_identifier;

    Variable *variable = NULL;
    // 查找局部变量
    if (function != NULL) {
        for (Variable *pos = function->variable_list; pos != NULL; pos = pos->next) {
            if (0 == strcmp(pos->variable_identifer, identifier)) {
                variable = pos;
            }
        }
    }

    if (variable != NULL) {
        debug_log_with_blue_coloar("find match local variable\n");
    } else {
        // 查找全局变量
        for (Variable *pos = get_ring_interpreter()->variable_list; pos != NULL; pos = pos->next) {
            if (0 == strcmp(pos->variable_identifer, identifier)) {
                variable = pos;
            }
        }
    }

    if (variable == NULL) {
        debug_log_with_blue_coloar("don't find match global variable\n");
        return;
    }

    // TODO:
    variable->u.ring_basic_value = result;
}
