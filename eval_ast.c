#include "ring.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ring_interpret(Ring_Compiler* ring_compiler) {
    debug_log_with_blue_coloar("\t interpret statement: "
                               "statement_list_size(%d)"
                               ",function_list_size(%d)"
                               ",variable_list_size(%d)"
                               ",identifier_list_size(%d)",
                               ring_compiler->statement_list_size,
                               ring_compiler->function_list_size,
                               ring_compiler->variable_list_size,
                               ring_compiler->identifier_list_size);
    interpret_statement_list(ring_compiler->statement_list, NULL);
}

StatementExecResult* interpret_statement_list(Statement* statement, Function* function) {
    Statement*           p;
    StatementExecResult* result;
    for (p = statement; p != NULL; p = p->next) {
        debug_log_with_blue_coloar("\t interpret statement: type(%d),line_number(%d)", p->type, p->line_number);
        result = interpret_statement(p, function);
        if (result != NULL) {
            if (result->type == STATEMENT_EXEC_RESULT_TYPE_RETURN
                || result->type == STATEMENT_EXEC_RESULT_TYPE_BREAK
                || result->type == STATEMENT_EXEC_RESULT_TYPE_CONTINUE) {
                return result;
            }
        }
    }
    return result;
}

StatementExecResult* interpret_statement(Statement* statement, Function* function) {
    StatementExecResult* result = malloc(sizeof(StatementExecResult));

    switch (statement->type) {
    case STATEMENT_TYPE_EXPRESSION:
        result->type = STATEMENT_EXEC_RESULT_TYPE_EXPRESSION;
        interpret_expression(statement->u.expression, function);
        break;

    case STATEMENT_TYPE_VARIABLE_DEFINITION:
        if (statement->u.variable) {
            if (statement->u.variable->init_expression) {
                Ring_BasicValue* tmp = NULL;
                // TODO:
                tmp                                       = interpret_binary_expression(statement->u.variable->init_expression, function);
                statement->u.variable->u.ring_basic_value = tmp;

                // 初始化默认值
            } else if (statement->u.variable->type == VARIABLE_TYPE_BOOL) {
                Ring_BasicValue* tmp                      = malloc(sizeof(Ring_BasicValue));
                tmp->type                                 = BASICVALUE_TYPE_BOOL;
                tmp->u.bool_value                         = BOOL_FALSE;
                statement->u.variable->u.ring_basic_value = tmp;
            } else if (statement->u.variable->type == VARIABLE_TYPE_INT) {
                Ring_BasicValue* tmp                      = malloc(sizeof(Ring_BasicValue));
                tmp->type                                 = BASICVALUE_TYPE_INT;
                tmp->u.int_value                          = 0;
                statement->u.variable->u.ring_basic_value = tmp;
            } else if (statement->u.variable->type == VARIABLE_TYPE_DOUBLE) {
                Ring_BasicValue* tmp                      = malloc(sizeof(Ring_BasicValue));
                tmp->type                                 = BASICVALUE_TYPE_DOUBLE;
                tmp->u.double_value                       = 0.0;
                statement->u.variable->u.ring_basic_value = tmp;
            } else if (statement->u.variable->type == VARIABLE_TYPE_ARRAY) {
                // 找到size值
                // 确定存储空间
                // 同时确定存储类型

                unsigned int size = 10; // FIXME:

                Ring_BasicValue* value     = malloc(sizeof(Ring_BasicValue));
                value->type                = BASICVALUE_TYPE_ARRAY;
                value->array_member_type   = BASICVALUE_TYPE_INT; // FIXME:
                value->u.array_value       = malloc(sizeof(Ring_Array));
                value->u.array_value->size = size;
                value->u.array_value->data = malloc(sizeof(Ring_BasicValue) * size);

                for (unsigned int i = 0; i < size; i++) {
                    Ring_BasicValue* tmp = value->u.array_value->data + i;
                    tmp->type            = BASICVALUE_TYPE_INT;
                    tmp->u.int_value     = 0; // 初始化默认值
                    tmp->next            = NULL;
                }
                statement->u.variable->u.ring_basic_value = value;
            }
        }
        // TODO:
        break;

    case STATEMENT_TYPE_RETURN:
        result = interpret_statement_return(statement, function);
        break;

    case STATEMENT_TYPE_IF:
        result = interpret_statement_if(statement->u.if_statement, function);
        break;

    case STATEMENT_TYPE_FOR:
        result = interpret_statement_for(statement->u.for_statement, function);
        break;

    case STATEMENT_TYPE_DOWHILE:
        result = interpret_statement_dowhile(statement->u.dowhile_statement, function);
        break;

    case STATEMENT_TYPE_BREAK:
        result = interpret_statement_break(statement->u.break_statement, function);
        break;

    case STATEMENT_TYPE_CONTINUE:
        result = interpret_statement_continue(statement->u.continue_statement, function);
        break;

    default:
        break;
    }

    return result;
}

StatementExecResult* interpret_statement_break(BreakStatement* statement, Function* function) {
    StatementExecResult* result = malloc(sizeof(StatementExecResult));
    result->type                = STATEMENT_EXEC_RESULT_TYPE_BREAK;
    return result;
}

StatementExecResult* interpret_statement_continue(ContinueStatement* statement, Function* function) {
    StatementExecResult* result = malloc(sizeof(StatementExecResult));
    result->type                = STATEMENT_EXEC_RESULT_TYPE_CONTINUE;
    return result;
}

StatementExecResult* interpret_statement_return(Statement* statement, Function* function) {
    StatementExecResult* result    = malloc(sizeof(StatementExecResult));
    result->type                   = STATEMENT_EXEC_RESULT_TYPE_RETURN;
    result->return_value_list_size = 0;
    result->return_value_list      = NULL;

    int index = 0;
    for (Expression* pos = statement->u.return_expression; pos != NULL; pos = pos->next, index++) {
        result->return_value_list        = (Ring_BasicValue**)realloc(result->return_value_list, (index + 1) * sizeof(Ring_BasicValue*));
        Ring_BasicValue* tmp             = interpret_expression(pos, function);
        result->return_value_list[index] = tmp;
    }
    result->return_value_list_size = index;
    return result;
}

StatementExecResult* interpret_statement_if(IfStatement* if_statement, Function* function) {
    StatementExecResult* result = malloc(sizeof(StatementExecResult));

    Ring_BasicValue* cond = interpret_expression(if_statement->expression, function);
    if (cond == NULL || cond->type != BASICVALUE_TYPE_BOOL) {
        runtime_err_log("the result of if statement expression is not bool!");
        exit(1);
    }

    if (cond->u.bool_value) {
        result = interpret_statement_list(if_statement->if_block, function);
    } else {
        for (ElseIfStatement* pos = if_statement->elseif_statement_list; pos != NULL; pos = pos->next) {
            Ring_BasicValue* cond = interpret_expression(pos->expression, function);
            if (cond == NULL || cond->type != BASICVALUE_TYPE_BOOL) {
                runtime_err_log("the result of if statement expression is not bool!");
                exit(1);
            }
            if (cond->u.bool_value) {
                result = interpret_statement_list(pos->elseif_block, function);
                goto END;
            }
        }
        if (if_statement->else_block != NULL) {
            result = interpret_statement_list(if_statement->else_block, function);
        }
    }

END:
    return result;
}

StatementExecResult* interpret_statement_for(ForStatement* for_statement, Function* function) {
    StatementExecResult* result = malloc(sizeof(StatementExecResult));

    Ring_BasicValue* tmp = NULL;

    if (for_statement->init_expression != NULL) {
        // TODO:
        tmp = interpret_expression(for_statement->init_expression, function);
    }

    while (1) {
        if (for_statement->condition_expression != NULL) {
            tmp = interpret_expression(for_statement->condition_expression, function);
            if (tmp == NULL || tmp->type != BASICVALUE_TYPE_BOOL) {
                runtime_err_log("the result of for statement condition_expression is not bool!");
                exit(1);
            }

            if (tmp->u.bool_value == BOOL_FALSE) {
                break;
            }
        }

        result = interpret_statement_list(for_statement->block, function);
        if (result != NULL) {
            if (result->type == STATEMENT_EXEC_RESULT_TYPE_BREAK) {
                result->type = STATEMENT_EXEC_RESULT_TYPE_NORMAL;
                goto ENDFOR;
            } else if (result->type == STATEMENT_EXEC_RESULT_TYPE_CONTINUE) {
                result->type = STATEMENT_EXEC_RESULT_TYPE_NORMAL;
            } else if (result->type == STATEMENT_EXEC_RESULT_TYPE_RETURN) {
                goto ENDFOR;
            }
        }

        if (for_statement->post_expression != NULL) {
            interpret_expression(for_statement->post_expression, function);
        }
    }

ENDFOR:
    return result;
}

StatementExecResult* interpret_statement_dowhile(DoWhileStatement* dowhile_statement, Function* function) {
    StatementExecResult* result = malloc(sizeof(StatementExecResult));

    Ring_BasicValue* tmp = NULL;

    do {
        result = interpret_statement_list(dowhile_statement->block, function);
        if (result != NULL) {
            if (result->type == STATEMENT_EXEC_RESULT_TYPE_BREAK) {
                result->type = STATEMENT_EXEC_RESULT_TYPE_NORMAL;
                goto ENDFOR;
            } else if (result->type == STATEMENT_EXEC_RESULT_TYPE_CONTINUE) {
                result->type = STATEMENT_EXEC_RESULT_TYPE_NORMAL;
            } else if (result->type == STATEMENT_EXEC_RESULT_TYPE_RETURN) {
                goto ENDFOR;
            }
        }

        tmp = interpret_expression(dowhile_statement->condition_expression, function);
        if (tmp == NULL || tmp->type != BASICVALUE_TYPE_BOOL) {
            runtime_err_log("the result of for statement condition_expression is not bool!");
            exit(1);
        }

        if (tmp->u.bool_value == BOOL_FALSE) {
            break;
        }
    } while (1);

ENDFOR:
    return result;
}

Ring_BasicValue* interpret_expression(Expression* expression, Function* function) {
    debug_log_with_blue_coloar("\t ");

    Ring_BasicValue* result = malloc(sizeof(Ring_BasicValue));
    result->next            = NULL;

    StatementExecResult* exec_result = NULL;

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
        interpret_assign_expression(expression, function);
        break;

    case EXPRESSION_TYPE_TERNARY:
        result = interpret_ternary_condition_expression(expression, function);
        break;

    case EXPRESSION_TYPE_VARIABLE:
        result = interpret_variable_expression(expression->u.variable_identifier, function);
        break;

    case EXPRESSION_TYPE_ARITHMETIC_ADD:
    case EXPRESSION_TYPE_ARITHMETIC_SUB:
    case EXPRESSION_TYPE_ARITHMETIC_MUL:
    case EXPRESSION_TYPE_ARITHMETIC_DIV:
    case EXPRESSION_TYPE_ARITHMETIC_MOD:
        result = interpret_binary_expression(expression, function);
        break;

    case EXPRESSION_TYPE_LOGICAL_AND:
    case EXPRESSION_TYPE_LOGICAL_OR:
        result = interpret_binary_expression_logical(expression, function);
        break;

    case EXPRESSION_TYPE_LOGICAL_UNITARY_NOT:
    case EXPRESSION_TYPE_ARITHMETIC_UNITARY_MINUS:
    case EXPRESSION_TYPE_UNITARY_INCREASE_SUFFIX:
    case EXPRESSION_TYPE_UNITARY_INCREASE_PREFIX:
    case EXPRESSION_TYPE_UNITARY_DECREASE_SUFFIX:
    case EXPRESSION_TYPE_UNITARY_DECREASE_PREFIX:
        result = interpret_unitary_expression(expression, function);
        break;

    case EXPRESSION_TYPE_RELATIONAL_EQ:
    case EXPRESSION_TYPE_RELATIONAL_NE:
    case EXPRESSION_TYPE_RELATIONAL_GT:
    case EXPRESSION_TYPE_RELATIONAL_GE:
    case EXPRESSION_TYPE_RELATIONAL_LT:
    case EXPRESSION_TYPE_RELATIONAL_LE:
        result = interpret_binary_expression_realational(expression, function);
        break;

    case EXPRESSION_TYPE_ARRAY_INDEX:
        result = interpret_array_index_expression(expression->u.array_index_expression, function);
        break;

    default:
        break;
    }

    return result;
}

// TODO:
Ring_BasicValue* interpret_variable_expression(char* variable_identifier, Function* function) {
    // 查找相应的变量值
    Variable* variable = NULL;
    // 查找局部变量
    if (function != NULL) {
        for (Variable* pos = function->variable_list; pos != NULL; pos = pos->next) {
            if (0 == strcmp(pos->variable_identifer, variable_identifier)) {
                variable = pos;
            }
        }
    }

    if (variable != NULL) {
        debug_log_with_blue_coloar("find match local variable\n");
    } else {
        // 查找全局变量
        for (Variable* pos = get_ring_compiler()->variable_list; pos != NULL; pos = pos->next) {
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
    Ring_BasicValue* result = malloc(sizeof(Ring_BasicValue));
    result->next            = NULL;

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

// TODO:
Ring_BasicValue* interpret_array_index_expression(ArrayIndexExpression* expression, Function* function) {
    // 查找相应的变量值
    char*     variable_identifier = expression->variable_identifier;
    Variable* variable            = NULL;
    // 查找局部变量
    if (function != NULL) {
        for (Variable* pos = function->variable_list; pos != NULL; pos = pos->next) {
            if (0 == strcmp(pos->variable_identifer, variable_identifier)) {
                variable = pos;
            }
        }
    }

    if (variable != NULL) {
        debug_log_with_blue_coloar("find match local variable\n");
    } else {
        // 查找全局变量
        for (Variable* pos = get_ring_compiler()->variable_list; pos != NULL; pos = pos->next) {
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
    Ring_BasicValue* result = malloc(sizeof(Ring_BasicValue));
    result->next            = NULL;

    Ring_BasicValue* tmp = NULL;
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

    case VARIABLE_TYPE_ARRAY:
        // FIXME: 详细检查 index 的类型
        tmp                 = interpret_expression(expression->index_expression, function);
        unsigned int index  = tmp->u.int_value;
        result->type        = BASICVALUE_TYPE_INT;                                                  // FIXME:
        result->u.int_value = variable->u.ring_basic_value->u.array_value->data[index].u.int_value; // FIXME:
        break;
    default:
        break;
    }

    return result;
}

Ring_BasicValue* interpret_binary_expression_arithmetic(Expression* expression, Function* function) {
    debug_log_with_blue_coloar("expression->type:%d", expression->type);
    Ring_BasicValue* result = malloc(sizeof(Ring_BasicValue));
    result->next            = NULL;

    Ring_BasicValue* left  = NULL;
    Ring_BasicValue* right = NULL;

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
    case EXPRESSION_TYPE_ARITHMETIC_MOD:
        result_value = (int)left_value % (int)right_value;
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

Ring_BasicValue* interpret_binary_expression_realational(Expression* expression, Function* function) {
    debug_log_with_blue_coloar("expression->type:%d", expression->type);
    Ring_BasicValue* result = malloc(sizeof(Ring_BasicValue));
    result->next            = NULL;

    Ring_BasicValue* left  = NULL;
    Ring_BasicValue* right = NULL;

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

Ring_BasicValue* interpret_binary_expression_logical(Expression* expression, Function* function) {
    debug_log_with_blue_coloar("expression->type:%d", expression->type);
    Ring_BasicValue* result = malloc(sizeof(Ring_BasicValue));
    result->next            = NULL;

    Ring_BasicValue* left  = NULL;
    Ring_BasicValue* right = NULL;

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

Ring_BasicValue* interpret_ternary_condition_expression(Expression* expression, Function* origin_function) {
    Ring_BasicValue* result;

    Expression* condition_expression = expression->u.ternary_expression->condition_expression;
    Expression* true_expression      = expression->u.ternary_expression->true_expression;
    Expression* false_expression     = expression->u.ternary_expression->false_expression;

    if (condition_expression == NULL) {
        // error
        // TODO:
        exit(1);
    }

    Ring_BasicValue* cond = interpret_expression(condition_expression, origin_function);
    if (cond == NULL || cond->type != BASICVALUE_TYPE_BOOL) {
        runtime_err_log("the result of if statement expression is not bool!");
        exit(1);
    }

    if (cond->u.bool_value) {
        result = interpret_expression(true_expression, origin_function);
    } else {
        result = interpret_expression(false_expression, origin_function);
    }

    return result;
}

Ring_BasicValue* interpret_binary_expression(Expression* expression, Function* origin_function) {
    // debug_log_with_blue_coloar("expression->type:%d", expression->type);
    // TODO: 还要考虑各个变量的类型
    //       是否涉及到强制类型转换
    //       两边类型不匹配还要编译报错

    // FIXME: 存在内存泄漏
    StatementExecResult* tmp    = NULL;
    Ring_BasicValue*     result = malloc(sizeof(Ring_BasicValue));
    result->next                = NULL;

    double tmp_value = 0;

    switch (expression->type) {
    case EXPRESSION_TYPE_LITERAL_BOOL:
        result->type         = BASICVALUE_TYPE_BOOL;
        result->u.bool_value = expression->u.bool_literal;
        tmp_value            = (double)(result->u.bool_value);
        break;
    case EXPRESSION_TYPE_LITERAL_INT:
        result->type        = BASICVALUE_TYPE_INT;
        result->u.int_value = expression->u.int_literal;
        tmp_value           = (double)(result->u.int_value);
        break;

    case EXPRESSION_TYPE_LITERAL_DOUBLE:
        result->type           = BASICVALUE_TYPE_DOUBLE;
        result->u.double_value = expression->u.double_literal;
        tmp_value              = (double)(result->u.double_value);
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

        // for (Function *pos = get_ring_compiler()->function_list; pos != NULL; pos = pos->next) {
        //     if (0 == strcmp(pos->function_name, expression->u.function_call_expression->function_name)) {
        //         function = pos;
        //     }
        // }
        tmp = invoke_function(expression->u.function_call_expression, origin_function);
        { // 这个地方写的太难看了，得重构一下
            Ring_BasicValue* head = NULL;
            Ring_BasicValue* dest = result;
            Ring_BasicValue* pre  = NULL;

            for (unsigned int i = 0; i < tmp->return_value_list_size; i++) {
                dest = tmp->return_value_list[i];
                if (pre != NULL) {
                    pre->next = dest;
                }

                if (i == 0) {
                    head = dest;
                }

                pre = dest;
            }
            return head;
        }
        // FIXME: 不能使用return_value
        // if (tmp != NULL) {
        //     result = tmp->u.return_value;
        // }
        break;

    case EXPRESSION_TYPE_TERNARY:
        result = interpret_ternary_condition_expression(expression, origin_function);
        break;

    case EXPRESSION_TYPE_ARITHMETIC_ADD:
    case EXPRESSION_TYPE_ARITHMETIC_SUB:
    case EXPRESSION_TYPE_ARITHMETIC_MUL:
    case EXPRESSION_TYPE_ARITHMETIC_DIV:
    case EXPRESSION_TYPE_ARITHMETIC_MOD:
        result = interpret_binary_expression_arithmetic(expression, origin_function);
        break;

    case EXPRESSION_TYPE_LOGICAL_AND:
    case EXPRESSION_TYPE_LOGICAL_OR:
        result = interpret_binary_expression_logical(expression, origin_function);
        break;

    case EXPRESSION_TYPE_LOGICAL_UNITARY_NOT:
    case EXPRESSION_TYPE_ARITHMETIC_UNITARY_MINUS:
    case EXPRESSION_TYPE_UNITARY_INCREASE_SUFFIX:
    case EXPRESSION_TYPE_UNITARY_INCREASE_PREFIX:
    case EXPRESSION_TYPE_UNITARY_DECREASE_SUFFIX:
    case EXPRESSION_TYPE_UNITARY_DECREASE_PREFIX:
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

    // TODO: 这里实现的有点难看，需要再修改
    switch (expression->convert_type) {
    case BASICVALUE_TYPE_BOOL:
        result->type         = BASICVALUE_TYPE_BOOL;
        result->u.bool_value = (Ring_Bool)tmp_value;
        break;

    case BASICVALUE_TYPE_INT:
        result->type        = BASICVALUE_TYPE_INT;
        result->u.int_value = (int)tmp_value;
        break;

    case BASICVALUE_TYPE_DOUBLE:
        result->type           = BASICVALUE_TYPE_DOUBLE;
        result->u.double_value = (double)tmp_value;
        break;

    default:
        break;
    }

    return result;
}

Ring_BasicValue* interpret_unitary_expression(Expression* expression, Function* origin_function) {
    debug_log_with_blue_coloar("\t expression->type:%d", expression->type);
    // TODO: 还要考虑各个变量的类型
    //       是否涉及到强制类型转换
    //       两边类型不匹配还要编译报错

    // FIXME: 存在内存泄漏

    Ring_BasicValue* result = malloc(sizeof(Ring_BasicValue));
    result->next            = NULL;

    Ring_BasicValue* left = NULL;

    switch (expression->type) {
    case EXPRESSION_TYPE_LOGICAL_UNITARY_NOT:
        left                 = interpret_expression(expression->u.unitary_expression, origin_function);
        result->type         = BASICVALUE_TYPE_BOOL;
        result->u.bool_value = !left->u.bool_value;
        break;

    case EXPRESSION_TYPE_ARITHMETIC_UNITARY_MINUS:
        left         = interpret_expression(expression->u.unitary_expression, origin_function);
        result->type = left->type;
        if (left->type == BASICVALUE_TYPE_INT) {
            result->u.int_value = -left->u.int_value;
        } else if (left->type == BASICVALUE_TYPE_DOUBLE) {
            result->u.double_value = -left->u.double_value;
        }
        break;

    case EXPRESSION_TYPE_UNITARY_INCREASE_SUFFIX:
    case EXPRESSION_TYPE_UNITARY_INCREASE_PREFIX:
    case EXPRESSION_TYPE_UNITARY_DECREASE_SUFFIX:
    case EXPRESSION_TYPE_UNITARY_DECREASE_PREFIX:
        result = interpret_unitary_expression_(expression, origin_function);
        break;

    default:
        break;
    }

    return result;
}

// TODO: 改名字
Ring_BasicValue* interpret_unitary_expression_(Expression* expression, Function* origin_function) {
    debug_log_with_blue_coloar("\t expression->type:%d", expression->type);

    assert(expression->type == EXPRESSION_TYPE_UNITARY_INCREASE_SUFFIX
           || expression->type == EXPRESSION_TYPE_UNITARY_INCREASE_PREFIX
           || expression->type == EXPRESSION_TYPE_UNITARY_DECREASE_SUFFIX
           || expression->type == EXPRESSION_TYPE_UNITARY_DECREASE_PREFIX);
    assert(expression->u.unitary_expression != NULL);
    assert(expression->u.unitary_expression->type == EXPRESSION_TYPE_VARIABLE);

    Ring_BasicValue* return_value = NULL;

    Ring_BasicValue* new_value = malloc(sizeof(Ring_BasicValue));
    new_value->next            = NULL;

    Ring_BasicValue* old_value = interpret_expression(expression->u.unitary_expression, origin_function);

    double tmp = 0;
    switch (old_value->type) {
    case BASICVALUE_TYPE_INT: tmp = (double)old_value->u.int_value; break;
    case BASICVALUE_TYPE_DOUBLE: tmp = old_value->u.double_value; break;
    default:
        runtime_err_log("the type of increase/decrease target must be int/double.");
        exit(1);
        break;
    }

    switch (expression->type) {
    case EXPRESSION_TYPE_UNITARY_INCREASE_SUFFIX:
        tmp++;
        return_value = old_value;
        break;
    case EXPRESSION_TYPE_UNITARY_INCREASE_PREFIX:
        tmp++;
        return_value = new_value;
        break;
    case EXPRESSION_TYPE_UNITARY_DECREASE_SUFFIX:
        tmp--;
        return_value = old_value;
        break;
    case EXPRESSION_TYPE_UNITARY_DECREASE_PREFIX:
        tmp--;
        return_value = new_value;
        break;
    default: break;
    }

    switch (old_value->type) {
    case BASICVALUE_TYPE_INT:
        new_value->type        = BASICVALUE_TYPE_INT;
        new_value->u.int_value = (int)tmp;
        break;
    case BASICVALUE_TYPE_DOUBLE:
        new_value->type           = BASICVALUE_TYPE_DOUBLE;
        new_value->u.double_value = tmp;
        break;
    default: break;
    }

    char* identifier = expression->u.unitary_expression->u.variable_identifier;

    Variable* variable = NULL;
    variable           = search_variable(identifier, origin_function);
    if (variable == NULL) {
        exit(1);
    }

    assign_identifier(variable, new_value, ASSIGN_EXPRESSION_TYPE_ASSIGN);

    return return_value;
}

Ring_BasicValue* search_variable_value(char* identifier, Function* origin_function) {
    Variable* variable = NULL;

    // 查找局部变量
    if (origin_function != NULL) {
        for (Variable* pos = origin_function->variable_list; pos != NULL; pos = pos->next) {
            if (0 == strcmp(pos->variable_identifer, identifier)) {
                variable = pos;
            }
        }
    }

    if (variable != NULL) {
        return variable->u.ring_basic_value;
    }

    for (Variable* pos = get_ring_compiler()->variable_list; pos != NULL; pos = pos->next) {
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

StatementExecResult* invoke_function(FunctionCallExpression* function_call_expression, Function* origin_function) { // TODO: origin_function这个名字重新取一下
    debug_log_with_blue_coloar("function_call_expression->function_name:%s", function_call_expression->function_name);

    StatementExecResult* result = NULL;

    // search_funcaion
    Function* function = NULL;

    for (Function* pos = get_ring_compiler()->function_list; pos != NULL; pos = pos->next) {
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
        ArgumentList* argument_list = function_call_expression->argument_list;
        for (Variable* pos = function->parameter_list; pos != NULL; pos = pos->next) {
            Ring_BasicValue* result = interpret_binary_expression(argument_list->u.expression, origin_function);
            argument_list           = argument_list->next;

            Variable* variable   = NULL;
            char*     identifier = pos->variable_identifer;
            // 查找局部变量
            if (function != NULL) {
                for (Variable* pos = function->variable_list; pos != NULL; pos = pos->next) {
                    if (0 == strcmp(pos->variable_identifer, identifier)) {
                        variable = pos;
                    }
                }
            }
            if (variable != NULL) {
                debug_log_with_blue_coloar("find match local variable\n");
            } else {
                // 查找全局变量
                for (Variable* pos = get_ring_compiler()->variable_list; pos != NULL; pos = pos->next) {
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
        Ring_BasicValue** values = NULL;
        for (ArgumentList* pos = function_call_expression->argument_list; pos != NULL; pos = pos->next) {
            argc += 1;
            Ring_BasicValue* value = interpret_expression(pos->u.expression, origin_function);

            values           = (Ring_BasicValue**)realloc(values, argc * sizeof(Ring_BasicValue*));
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

StatementExecResult* invoke_external_function(Function* function) {
    debug_log_with_blue_coloar("");
    StatementExecResult* result;
    result = interpret_statement_list(function->block, function);
    return result;
}

// TODO: 重构
void interpret_assign_expression(Expression* expression, Function* function) {
    debug_log_with_blue_coloar("expression->type:%d", expression->type);

    assert(expression->type == EXPRESSION_TYPE_ASSIGN);

    Expression* pos = expression->u.assign_expression->expression;

    unsigned int identifier_list_index = 0;

    for (; pos != NULL; pos = pos->next) {
        Ring_BasicValue* result = interpret_binary_expression(pos, function);

        for (; result != NULL; result = result->next, identifier_list_index++) {
            char* identifier;
            identifier = expression->u.assign_expression->assign_identifiers[identifier_list_index];

            Variable* variable = NULL;
            variable           = search_variable(identifier, function);
            if (variable == NULL) {
                return;
            }

            assign_identifier(variable, result, expression->u.assign_expression->type);
        }
    }
}

void assign_identifier(Variable* variable, Ring_BasicValue* new_value, AssignExpressionType type) {
    Ring_BasicValue* old = variable->u.ring_basic_value;

    if (new_value->type != BASICVALUE_TYPE_INT && type != ASSIGN_EXPRESSION_TYPE_ASSIGN) {
        // TODO: 暂时不支持 对于 += -= %= /= *= 支持int，后续支持
        return;
    }

    switch (type) {
    case ASSIGN_EXPRESSION_TYPE_ASSIGN: break;
    case ASSIGN_EXPRESSION_TYPE_ADD_ASSIGN: new_value->u.int_value = old->u.int_value + new_value->u.int_value; break;
    case ASSIGN_EXPRESSION_TYPE_SUB_ASSIGN: new_value->u.int_value = old->u.int_value - new_value->u.int_value; break;
    case ASSIGN_EXPRESSION_TYPE_MUL_ASSIGN: new_value->u.int_value = old->u.int_value * new_value->u.int_value; break;
    case ASSIGN_EXPRESSION_TYPE_DIV_ASSIGN: new_value->u.int_value = old->u.int_value / new_value->u.int_value; break;
    case ASSIGN_EXPRESSION_TYPE_MOD_ASSIGN: new_value->u.int_value = old->u.int_value % new_value->u.int_value; break;
    default: break;
    }

    variable->u.ring_basic_value = new_value;
}

Variable* search_variable(char* variable_identifier, Function* function) {
    // 查找 function 里局部变量
    if (function != NULL) {
        for (Variable* pos = function->variable_list; pos != NULL; pos = pos->next) {
            if (0 == strcmp(pos->variable_identifer, variable_identifier)) {
                return pos;
            }
        }
    }

    debug_log_with_blue_coloar("don't find match local variable\n");

    // 查找全局变量
    for (Variable* pos = get_ring_compiler()->variable_list; pos != NULL; pos = pos->next) {
        if (0 == strcmp(pos->variable_identifer, variable_identifier)) {
            return pos;
        }
    }

    debug_log_with_blue_coloar("don't find match global variable\n");

    return NULL;
}
