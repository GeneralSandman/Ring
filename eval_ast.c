#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "ring.h"

void ring_interpret(Ring_Interpreter *ring_interpreter) {
    debug_log_with_blue_coloar("\t interpret statement: "
                               "statement_list_size(%d)"
                               ",function_list_size(%d)"
                               ",variable_list_size(%d)"
                               ",identifier_list_size(%d)",
                               ring_interpreter->statement_list_size,
                               ring_interpreter->function_list_size,
                               ring_interpreter->variable_list_size,
                               ring_interpreter->identifier_list_size);
    interpret_statement_list(ring_interpreter->statement_list, NULL);
}

StatementExecResult *interpret_statement_list(Statement *statement, Function *function) {
    Statement *          p;
    StatementExecResult *result;
    for (p = statement; p != NULL; p = p->next) {
        debug_log_with_blue_coloar("\t interpret statement: type(%d),line_number(%d)", p->type, p->line_number);
        result = interpret_statement(p, function);
        if (result != NULL && result->type == STATEMENT_EXEC_RESULT_TYPE_RETURN) {
            return result;
        }
    }
    return result;
}

StatementExecResult *interpret_statement(Statement *statement, Function *function) {
    StatementExecResult *result = NULL;

    result = (StatementExecResult *)malloc(sizeof(StatementExecResult));

    switch (statement->type) {
    case STATEMENT_TYPE_EXPRESSION:
        result->type = STATEMENT_EXEC_RESULT_TYPE_EXPRESSION;
        interpret_expression(statement->u.expression, function);
        break;

    case STATEMENT_TYPE_VARIABLE_DEFINITION:
        // TODO:
        break;

    case STATEMENT_TYPE_RETURN:
        result = interpret_statement_return(statement, function);
        break;

    default:
        break;
    }

    return result;
}

StatementExecResult *interpret_statement_return(Statement *statement, Function *function) {
    StatementExecResult *result = NULL;
    result                      = (StatementExecResult *)malloc(sizeof(StatementExecResult));
    result->type                = STATEMENT_EXEC_RESULT_TYPE_RETURN;
    result->u.return_value      = interpret_expression(statement->u.expression, function);
    return result;
}

Ring_BasicValue *interpret_expression(Expression *expression, Function *function) {
    debug_log_with_blue_coloar("\t ");

    Ring_BasicValue *result;

    result = (Ring_BasicValue *)malloc(sizeof(Ring_BasicValue));

    StatementExecResult *exec_result = NULL;

    switch (expression->type) {
    case EXPRESSION_TYPE_LITERAL_BOOL:
        result->type         = BASICVALUE_TYPE_BOOL;
        result->u.bool_value = expression->u.bool_literal;
        break;
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
        exec_result = invoke_function(expression->u.function_call_expression, function);
        break;

    case EXPRESSION_TYPE_ASSIGN:
        assign(expression, function);
        break;

    case EXPRESSION_TYPE_LOGICAL_UNITARY_NOT:
        result = interpret_unitary_expression(expression, function);
        break;

    case EXPRESSION_TYPE_UNITARY_MINUS:
        break;

    case EXPRESSION_TYPE_VARIABLE:
        result = interpret_variable_expression(expression->u.variable_identifier, function);
        break;

    case EXPRESSION_TYPE_ARITHMETIC_ADD:
    case EXPRESSION_TYPE_ARITHMETIC_SUB:
    case EXPRESSION_TYPE_ARITHMETIC_MUL:
    case EXPRESSION_TYPE_ARITHMETIC_DIV:
        result = interpret_binary_expression(expression, function);
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
    case VARIABLE_TYPE_BOOL:
        result->type         = BASICVALUE_TYPE_BOOL;
        result->u.bool_value = variable->u.ring_basic_value->u.bool_value;
        break;
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

Ring_BasicValue *interpret_binary_expression_arithmetic(Expression *expression, Function *function) {
    debug_log_with_blue_coloar("expression->type:%d", expression->type);
    Ring_BasicValue *result;

    result = (Ring_BasicValue *)malloc(sizeof(Ring_BasicValue));

    Ring_BasicValue *left  = NULL;
    Ring_BasicValue *right = NULL;

    left  = interpret_binary_expression(expression->u.binary_expression->left_expression, function);
    right = interpret_binary_expression(expression->u.binary_expression->right_expression, function);

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

Ring_BasicValue *interpret_binary_expression_realational(Expression *expression, Function *function) {
    debug_log_with_blue_coloar("expression->type:%d", expression->type);
    Ring_BasicValue *result;

    result = (Ring_BasicValue *)malloc(sizeof(Ring_BasicValue));

    Ring_BasicValue *left  = NULL;
    Ring_BasicValue *right = NULL;

    left  = interpret_binary_expression(expression->u.binary_expression->left_expression, function);
    right = interpret_binary_expression(expression->u.binary_expression->right_expression, function);

    double left_value  = 0.0;
    double right_value = 0.0;

    if (left->type == BASICVALUE_TYPE_BOOL) {
        left_value = (double)left->u.bool_value;
    } else if (left->type == BASICVALUE_TYPE_INT) {
        left_value = (double)left->u.int_value;
    } else if (left->type == BASICVALUE_TYPE_DOUBLE) {
        left_value = (double)left->u.double_value;
    }

    if (right->type == BASICVALUE_TYPE_BOOL) {
        right_value = (double)right->u.bool_value;
    } else if (right->type == BASICVALUE_TYPE_INT) {
        right_value = (double)right->u.int_value;
    } else if (right->type == BASICVALUE_TYPE_DOUBLE) {
        right_value = (double)right->u.double_value;
    }

    result->type = BASICVALUE_TYPE_BOOL;

    switch (expression->type) {
    case EXPRESSION_TYPE_RELATIONAL_EQ:
        result->u.bool_value = left_value == right_value;
        break;
    case EXPRESSION_TYPE_RELATIONAL_NE:
        result->u.bool_value = left_value != right_value;
        break;

    case EXPRESSION_TYPE_RELATIONAL_GT:
        result->u.bool_value = left_value > right_value;
        break;

    case EXPRESSION_TYPE_RELATIONAL_GE:
        result->u.bool_value = left_value >= right_value;
        break;

    case EXPRESSION_TYPE_RELATIONAL_LT:
        result->u.bool_value = left_value < right_value;
        break;

    case EXPRESSION_TYPE_RELATIONAL_LE:
        result->u.bool_value = left_value <= right_value;
        break;

    default: break;
    }

    return result;
}

Ring_BasicValue *interpret_binary_expression_logical(Expression *expression, Function *function) {
    debug_log_with_blue_coloar("expression->type:%d", expression->type);
    Ring_BasicValue *result;

    result = (Ring_BasicValue *)malloc(sizeof(Ring_BasicValue));

    Ring_BasicValue *left  = NULL;
    Ring_BasicValue *right = NULL;

    left  = interpret_binary_expression(expression->u.binary_expression->left_expression, function);
    right = interpret_binary_expression(expression->u.binary_expression->right_expression, function);

    double left_value  = 0.0;
    double right_value = 0.0;

    if (left->type == BASICVALUE_TYPE_BOOL) {
        left_value = (double)left->u.bool_value;
    } else if (left->type == BASICVALUE_TYPE_INT) {
        left_value = (double)left->u.int_value;
    } else if (left->type == BASICVALUE_TYPE_DOUBLE) {
        left_value = (double)left->u.double_value;
    }

    if (right->type == BASICVALUE_TYPE_BOOL) {
        right_value = (double)right->u.bool_value;
    } else if (right->type == BASICVALUE_TYPE_INT) {
        right_value = (double)right->u.int_value;
    } else if (right->type == BASICVALUE_TYPE_DOUBLE) {
        right_value = (double)right->u.double_value;
    }

    result->type = BASICVALUE_TYPE_BOOL;

    switch (expression->type) {
    case EXPRESSION_TYPE_LOGICAL_AND:
        result->u.bool_value = left_value && right_value;
        break;
    case EXPRESSION_TYPE_LOGICAL_OR:
        result->u.bool_value = left_value || right_value;
        break;

    default: break;
    }

    return result;
}

Ring_BasicValue *interpret_binary_expression(Expression *expression, Function *origin_function) {
    debug_log_with_blue_coloar("expression->type:%d", expression->type);
    // TODO: 还要考虑各个变量的类型
    //       是否涉及到强制类型转换
    //       两边类型不匹配还要编译报错

    // FIXME: 存在内存泄漏
    Function *function = NULL;

    Ring_BasicValue *result;

    StatementExecResult *tmp = NULL;

    result = (Ring_BasicValue *)malloc(sizeof(Ring_BasicValue));

    switch (expression->type) {
    case EXPRESSION_TYPE_LITERAL_BOOL:
        result->type         = BASICVALUE_TYPE_BOOL;
        result->u.bool_value = expression->u.bool_literal;
        break;
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
        result = search_variable_value(expression->u.variable_identifier, origin_function);
        break;

    case EXPRESSION_TYPE_FUNCTION_CALL:
        // result =

        // for (Function *pos = get_ring_interpreter()->function_list; pos != NULL; pos = pos->next) {
        //     if (0 == strcmp(pos->function_name, expression->u.function_call_expression->function_name)) {
        //         function = pos;
        //     }
        // }
        tmp = invoke_function(expression->u.function_call_expression, origin_function);
        if (tmp != NULL) {
            result = tmp->u.return_value;
        }
        break;

    case EXPRESSION_TYPE_ARITHMETIC_ADD:
    case EXPRESSION_TYPE_ARITHMETIC_SUB:
    case EXPRESSION_TYPE_ARITHMETIC_MUL:
    case EXPRESSION_TYPE_ARITHMETIC_DIV:
        result = interpret_binary_expression_arithmetic(expression, origin_function);
        break;

    case EXPRESSION_TYPE_LOGICAL_AND:
    case EXPRESSION_TYPE_LOGICAL_OR:
        result = interpret_binary_expression_logical(expression, origin_function);
        break;

    case EXPRESSION_TYPE_LOGICAL_UNITARY_NOT:
        result = interpret_unitary_expression(expression, origin_function);
        break;

    case EXPRESSION_TYPE_RELATIONAL_EQ:
    case EXPRESSION_TYPE_RELATIONAL_NE:
    case EXPRESSION_TYPE_RELATIONAL_GT:
    case EXPRESSION_TYPE_RELATIONAL_GE:
    case EXPRESSION_TYPE_RELATIONAL_LT:
    case EXPRESSION_TYPE_RELATIONAL_LE:
        result = interpret_binary_expression_realational(expression, origin_function);
        break;

    default:
        // log error
        break;
    }

    return result;
}

Ring_BasicValue *interpret_unitary_expression(Expression *expression, Function *origin_function) {
    debug_log_with_blue_coloar("\t expression->type:%d", expression->type);
    // TODO: 还要考虑各个变量的类型
    //       是否涉及到强制类型转换
    //       两边类型不匹配还要编译报错

    // FIXME: 存在内存泄漏
    Function *function = NULL;

    Ring_BasicValue *result;

    StatementExecResult *tmp = NULL;

    result = (Ring_BasicValue *)malloc(sizeof(Ring_BasicValue));

    Ring_BasicValue *left = NULL;

    switch (expression->type) {
    case EXPRESSION_TYPE_LOGICAL_UNITARY_NOT:
        left                 = interpret_expression(expression->u.unitary_expression, origin_function);
        result->type         = BASICVALUE_TYPE_BOOL;
        result->u.bool_value = !left->u.bool_value;
        break;

    default:
        break;
    }

    return result;
}

Ring_BasicValue *search_variable_value(char *identifier, Function *origin_function) {
    Variable *variable = NULL;

    // 查找局部变量
    if (origin_function != NULL) {
        for (Variable *pos = origin_function->variable_list; pos != NULL; pos = pos->next) {
            if (0 == strcmp(pos->variable_identifer, identifier)) {
                variable = pos;
            }
        }
    }

    if (variable != NULL) {
        return variable->u.ring_basic_value;
    }

    for (Variable *pos = get_ring_interpreter()->variable_list; pos != NULL; pos = pos->next) {
        if (0 == strcmp(pos->variable_identifer, identifier)) {
            variable = pos;
        }
    }

    if (variable == NULL) {
        debug_log_with_blue_coloar("not find match variable identifier:%s", identifier);

        return NULL;
    }
    return variable->u.ring_basic_value;
}

StatementExecResult *invoke_function(FunctionCallExpression *function_call_expression, Function *origin_function) { // TODO: origin_function这个名字重新取一下
    debug_log_with_blue_coloar("function_call_expression->function_name:%s", function_call_expression->function_name);

    StatementExecResult *result = NULL;

    // search_funcaion
    Function *function = NULL;

    for (Function *pos = get_ring_interpreter()->function_list; pos != NULL; pos = pos->next) {
        if (0 == strcmp(pos->function_name, function_call_expression->function_name)) {
            function = pos;
        }
    }

    if (function == NULL) {
        printf("findn't match function\n");
        return NULL;
    }

    // 给参数变量赋值
    if (function->type == FUNCTION_TYPE_EXTERNAL) {
        ArgumentList *argument_list = function_call_expression->argument_list;
        for (Variable *pos = function->parameter_list; pos != NULL; pos = pos->next) {
            Ring_BasicValue *result = interpret_binary_expression(argument_list->u.expression, origin_function);
            argument_list           = argument_list->next;

            Variable *variable   = NULL;
            char *    identifier = pos->variable_identifer;
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
                return NULL;
            }
            variable->u.ring_basic_value = result;
        }
    }

    // Ring_BasicValue *value;

    if (function->type == FUNCTION_TYPE_INNER_LIB) {
        // TODO 支持多个参数
        int               argc   = 0;
        Ring_BasicValue **values = NULL;
        for (ArgumentList *pos = function_call_expression->argument_list; pos != NULL; pos = pos->next) {
            argc += 1;
            Ring_BasicValue *value = interpret_expression(pos->u.expression, origin_function);

            values           = (Ring_BasicValue **)realloc(values, argc * sizeof(Ring_BasicValue *));
            values[argc - 1] = value;
        }
        function->inner_func(argc, values);
        if (values != NULL) {
            free(values);
        }
    } else if (function->type == FUNCTION_TYPE_EXTERNAL) {
        result = invoke_external_function(function);
    }

    // switch (function->type) {
    // case FUNCTION_TYPE_INNER_LIB:
    //     // TODO 支持多个参数
    //     value = interpret_expression(function_call_expression->argument_list->u.expression, origin_function);
    //     function->inner_func(1, &value);
    //     break;

    // case FUNCTION_TYPE_EXTERNAL:
    //     result = invoke_external_function(function);
    //     break;

    // default:
    //     break;
    // }

    // invoke
    return result;
}

StatementExecResult *invoke_external_function(Function *function) {
    debug_log_with_blue_coloar("");
    StatementExecResult *result;
    result = interpret_statement_list(function->block, function);
    return result;
}

void assign(Expression *expression, Function *function) {
    debug_log_with_blue_coloar("expression->type:%d", expression->type);

    assert(expression->type == EXPRESSION_TYPE_ASSIGN);

    Ring_BasicValue *result = NULL;
    // TODO:
    result = interpret_binary_expression(expression->u.assign_expression->expression, function);

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
