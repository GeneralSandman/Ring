#include "ring.hpp"
#include <cassert>

void crop_if_statement(IfStatement* if_statement, Block* block, FunctionTuple* func) {
    Expression* condition = if_statement->condition_expression;

    if (condition->type == EXPRESSION_TYPE_LITERAL_BOOL) {
        if (condition->u.bool_literal == false) {
            if_statement->if_block = nullptr;
        } else {
            if_statement->else_block = nullptr;
        }
    }
}

void crop_for_statement(ForStatement* for_statement, Block* block, FunctionTuple* func) {

    if (for_statement->type == FOR_STATEMENT_TYPE_TERNARY) {
        Expression* condition = for_statement->u.ternary_statement->condition_expression;

        if (condition->type == EXPRESSION_TYPE_LITERAL_BOOL) {
            if (condition->u.bool_literal == false) {
                for_statement->block = nullptr;
            }
        }
    }
}

void crop_ternary_condition_expression(Expression*        expression,
                                       TernaryExpression* ternary_expression,
                                       Block*             block,
                                       FunctionTuple*     func) {

    Expression* condition_expression = ternary_expression->condition_expression;
    Expression* true_expression      = ternary_expression->true_expression;
    Expression* false_expression     = ternary_expression->false_expression;

    if (condition_expression->type == EXPRESSION_TYPE_LITERAL_BOOL) {
        if (condition_expression->u.bool_literal) {
            memcpy(expression, true_expression, sizeof(Expression));
        } else {
            memcpy(expression, false_expression, sizeof(Expression));
        }
    }
}


void crop_binary_logical_expression(Expression*       expression,
                                    ExpressionType    expression_type,
                                    BinaryExpression* binary_expression,
                                    Block* block, FunctionTuple* func) {

    Expression* left  = binary_expression->left_expression;
    Expression* right = binary_expression->right_expression;

    assert(left->next == nullptr);
    assert(right->next == nullptr);

    if (expression_type == EXPRESSION_TYPE_LOGICAL_AND && left->type == EXPRESSION_TYPE_LITERAL_BOOL) {
        if (left->u.bool_literal == false) {
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = false;
        }
    }
    if (expression_type == EXPRESSION_TYPE_LOGICAL_OR && left->type == EXPRESSION_TYPE_LITERAL_BOOL) {
        if (left->u.bool_literal == true) {
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = true;
        }
    }


    if (left->type == EXPRESSION_TYPE_LITERAL_BOOL && right->type == EXPRESSION_TYPE_LITERAL_BOOL) {

        switch (expression_type) {
        case EXPRESSION_TYPE_LOGICAL_AND:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = left->u.bool_literal && right->u.bool_literal;
            break;
        case EXPRESSION_TYPE_LOGICAL_OR:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = left->u.bool_literal || right->u.bool_literal;
            break;

        default:
            break;
        }
    }
}

void crop_binary_relational_expression(Expression*       expression,
                                       ExpressionType    expression_type,
                                       BinaryExpression* binary_expression,
                                       Block* block, FunctionTuple* func) {

    Expression* left  = binary_expression->left_expression;
    Expression* right = binary_expression->right_expression;


    if (left->type == EXPRESSION_TYPE_LITERAL_BOOL && right->type == EXPRESSION_TYPE_LITERAL_BOOL) {
        switch (expression_type) {
        case EXPRESSION_TYPE_RELATIONAL_EQ:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.bool_literal == right->u.bool_literal);
            break;
        case EXPRESSION_TYPE_RELATIONAL_NE:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.bool_literal != right->u.bool_literal);
            break;

        default:
            break;
        }
    } else if (left->type == EXPRESSION_TYPE_LITERAL_INT && right->type == EXPRESSION_TYPE_LITERAL_INT) {
        switch (expression_type) {
        case EXPRESSION_TYPE_RELATIONAL_EQ:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.int_literal == right->u.int_literal);
            break;
        case EXPRESSION_TYPE_RELATIONAL_NE:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.int_literal != right->u.int_literal);
            break;
        case EXPRESSION_TYPE_RELATIONAL_GT:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.int_literal > right->u.int_literal);
            break;
        case EXPRESSION_TYPE_RELATIONAL_GE:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.int_literal >= right->u.int_literal);
            break;
        case EXPRESSION_TYPE_RELATIONAL_LT:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.int_literal < right->u.int_literal);
            break;
        case EXPRESSION_TYPE_RELATIONAL_LE:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.int_literal <= right->u.int_literal);
            break;

        default:
            break;
        }
    } else if (left->type == EXPRESSION_TYPE_LITERAL_INT64 && right->type == EXPRESSION_TYPE_LITERAL_INT64) {
        switch (expression_type) {
        case EXPRESSION_TYPE_RELATIONAL_EQ:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.int64_literal == right->u.int64_literal);
            break;
        case EXPRESSION_TYPE_RELATIONAL_NE:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.int64_literal != right->u.int64_literal);
            break;
        case EXPRESSION_TYPE_RELATIONAL_GT:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.int64_literal > right->u.int64_literal);
            break;
        case EXPRESSION_TYPE_RELATIONAL_GE:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.int64_literal >= right->u.int64_literal);
            break;
        case EXPRESSION_TYPE_RELATIONAL_LT:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.int64_literal < right->u.int64_literal);
            break;
        case EXPRESSION_TYPE_RELATIONAL_LE:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.int64_literal <= right->u.int64_literal);
            break;

        default:
            break;
        }
    } else if (left->type == EXPRESSION_TYPE_LITERAL_DOUBLE && right->type == EXPRESSION_TYPE_LITERAL_DOUBLE) {
        switch (expression_type) {
        case EXPRESSION_TYPE_RELATIONAL_EQ:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.double_literal == right->u.double_literal);
            break;
        case EXPRESSION_TYPE_RELATIONAL_NE:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.double_literal != right->u.double_literal);
            break;
        case EXPRESSION_TYPE_RELATIONAL_GT:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.double_literal > right->u.double_literal);
            break;
        case EXPRESSION_TYPE_RELATIONAL_GE:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.double_literal >= right->u.double_literal);
            break;
        case EXPRESSION_TYPE_RELATIONAL_LT:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.double_literal < right->u.double_literal);
            break;
        case EXPRESSION_TYPE_RELATIONAL_LE:
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = (left->u.double_literal <= right->u.double_literal);
            break;

        default:
            break;
        }
    } else if (left->type == EXPRESSION_TYPE_LITERAL_STRING && right->type == EXPRESSION_TYPE_LITERAL_STRING) {
        switch (expression_type) {
        case EXPRESSION_TYPE_RELATIONAL_EQ:
            expression->type = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal =
                (string_compare(left->u.string_literal, strlen(left->u.string_literal), right->u.string_literal, strlen(right->u.string_literal))
                 == 0);
            break;
        case EXPRESSION_TYPE_RELATIONAL_NE:
            expression->type = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal =
                (string_compare(left->u.string_literal, strlen(left->u.string_literal), right->u.string_literal, strlen(right->u.string_literal))
                 != 0);
            break;
        case EXPRESSION_TYPE_RELATIONAL_GT:
            expression->type = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal =
                (string_compare(left->u.string_literal, strlen(left->u.string_literal), right->u.string_literal, strlen(right->u.string_literal))
                 > 0);
            break;
        case EXPRESSION_TYPE_RELATIONAL_GE:
            expression->type = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal =
                (string_compare(left->u.string_literal, strlen(left->u.string_literal), right->u.string_literal, strlen(right->u.string_literal))
                 >= 0);
            break;
        case EXPRESSION_TYPE_RELATIONAL_LT:
            expression->type = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal =
                (string_compare(left->u.string_literal, strlen(left->u.string_literal), right->u.string_literal, strlen(right->u.string_literal))
                 < 0);
            break;
        case EXPRESSION_TYPE_RELATIONAL_LE:
            expression->type = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal =
                (string_compare(left->u.string_literal, strlen(left->u.string_literal), right->u.string_literal, strlen(right->u.string_literal))
                 <= 0);
            break;

        default:
            break;
        }
    }
}

void crop_binary_concat_expression(Expression*       expression,
                                   BinaryExpression* binary_expression,
                                   Block* block, FunctionTuple* func) {

    Expression* left  = binary_expression->left_expression;
    Expression* right = binary_expression->right_expression;

    assert(left->next == nullptr);
    assert(right->next == nullptr);

    if (left->type == EXPRESSION_TYPE_LITERAL_STRING && right->type == EXPRESSION_TYPE_LITERAL_STRING) {
        expression->type                    = EXPRESSION_TYPE_LITERAL_STRING;
        expression->u.string_literal        = get_string_constant_literal(left->u.string_literal, right->u.string_literal);

        binary_expression->left_expression  = nullptr;
        binary_expression->right_expression = nullptr;
    }
}

void crop_binary_match_expression(Expression*       expression,
                                  BinaryExpression* binary_expression,
                                  Block* block, FunctionTuple* func) {

    Expression* left  = binary_expression->left_expression;
    Expression* right = binary_expression->right_expression;

    assert(left->next == nullptr);
    assert(right->next == nullptr);

    if (left->type == EXPRESSION_TYPE_LITERAL_INT && right->type == EXPRESSION_TYPE_LITERAL_INT) {

        switch (expression->type) {
        case EXPRESSION_TYPE_ARITHMETIC_ADD:
            expression->u.int_literal = left->u.int_literal + right->u.int_literal;
            break;
        case EXPRESSION_TYPE_ARITHMETIC_SUB:
            expression->u.int_literal = left->u.int_literal - right->u.int_literal;
            break;
        case EXPRESSION_TYPE_ARITHMETIC_MUL:
            expression->u.int_literal = left->u.int_literal * right->u.int_literal;
            break;
        case EXPRESSION_TYPE_ARITHMETIC_DIV:
            expression->u.int_literal = left->u.int_literal / right->u.int_literal;
            break;
        case EXPRESSION_TYPE_ARITHMETIC_MOD:
            expression->u.int_literal = left->u.int_literal % right->u.int_literal;
            break;
        default:
            // TODO: error
            break;
        }

        expression->type                    = EXPRESSION_TYPE_LITERAL_INT;

        binary_expression->left_expression  = nullptr;
        binary_expression->right_expression = nullptr;
    } else if (left->type == EXPRESSION_TYPE_LITERAL_INT64 && right->type == EXPRESSION_TYPE_LITERAL_INT64) {

        switch (expression->type) {
        case EXPRESSION_TYPE_ARITHMETIC_ADD:
            expression->u.int64_literal = left->u.int64_literal + right->u.int64_literal;
            break;
        case EXPRESSION_TYPE_ARITHMETIC_SUB:
            expression->u.int64_literal = left->u.int64_literal - right->u.int64_literal;
            break;
        case EXPRESSION_TYPE_ARITHMETIC_MUL:
            expression->u.int64_literal = left->u.int64_literal * right->u.int64_literal;
            break;
        case EXPRESSION_TYPE_ARITHMETIC_DIV:
            expression->u.int64_literal = left->u.int64_literal / right->u.int64_literal;
            break;
        case EXPRESSION_TYPE_ARITHMETIC_MOD:
            expression->u.int64_literal = left->u.int64_literal % right->u.int64_literal;
            break;
        default:
            // TODO: error report
            break;
        }

        expression->type                    = EXPRESSION_TYPE_LITERAL_INT64;

        binary_expression->left_expression  = nullptr;
        binary_expression->right_expression = nullptr;
    } else if (left->type == EXPRESSION_TYPE_LITERAL_DOUBLE && right->type == EXPRESSION_TYPE_LITERAL_DOUBLE) {

        switch (expression->type) {
        case EXPRESSION_TYPE_ARITHMETIC_ADD:
            expression->u.double_literal = left->u.double_literal + right->u.double_literal;
            break;
        case EXPRESSION_TYPE_ARITHMETIC_SUB:
            expression->u.double_literal = left->u.double_literal - right->u.double_literal;
            break;
        case EXPRESSION_TYPE_ARITHMETIC_MUL:
            expression->u.double_literal = left->u.double_literal * right->u.double_literal;
            break;
        case EXPRESSION_TYPE_ARITHMETIC_DIV:
            expression->u.double_literal = left->u.double_literal / right->u.double_literal;
            break;
        case EXPRESSION_TYPE_ARITHMETIC_MOD:
            // TODO: error report
            // expression->u.double_literal = left->u.double_literal % right->u.double_literal;
            break;
        default:
            // TODO: error report
            break;
        }

        expression->type                    = EXPRESSION_TYPE_LITERAL_DOUBLE;

        binary_expression->left_expression  = nullptr;
        binary_expression->right_expression = nullptr;
    }
}

void crop_unitary_expression(Expression* expression,
                             Expression* unitary_expression,
                             Block* block, FunctionTuple* func) {

    Expression* operand = unitary_expression;


    if (expression->type == EXPRESSION_TYPE_ARITHMETIC_UNITARY_MINUS) {
        if (operand->type == EXPRESSION_TYPE_LITERAL_INT) {
            expression->type          = EXPRESSION_TYPE_LITERAL_INT;
            expression->u.int_literal = -operand->u.int_literal;
        } else if (operand->type == EXPRESSION_TYPE_LITERAL_INT64) {
            expression->type            = EXPRESSION_TYPE_LITERAL_INT64;
            expression->u.int64_literal = -operand->u.int64_literal;
        } else if (operand->type == EXPRESSION_TYPE_LITERAL_DOUBLE) {
            expression->type             = EXPRESSION_TYPE_LITERAL_DOUBLE;
            expression->u.double_literal = -operand->u.double_literal;
        }
    } else if (expression->type == EXPRESSION_TYPE_LOGICAL_UNITARY_NOT) {
        if (operand->type == EXPRESSION_TYPE_LITERAL_BOOL) {
            expression->type           = EXPRESSION_TYPE_LITERAL_BOOL;
            expression->u.bool_literal = !operand->u.bool_literal;
        }
    }
}