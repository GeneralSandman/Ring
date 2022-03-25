#include "ring.h"
#include <string.h>

// 修正ast
void ring_compiler_fix_ast(Ring_Compiler* ring_compiler) {
    // TODO: 目前只 修复 declaration_list
    fix_statement_list(ring_compiler->statement_list);
}

void fix_statement_list(Statement* statement_list) {
    if (statement_list == NULL) {
        return;
    }
    for (Statement* pos = statement_list; pos; pos = pos->next) {
        fix_statement(pos);
    }
}

void fix_statement(Statement* statement) {
    switch (statement->type) {
    case STATEMENT_TYPE_EXPRESSION:
        fix_expression(statement->u.expression);
        break;
    case STATEMENT_TYPE_DECLARATION:
        /* code */
        fix_declaration(statement->u.declaration_statement);
        break;

    case STATEMENT_TYPE_IF:
        fix_if_statement(statement->u.if_statement);
        break;

    case STATEMENT_TYPE_FOR:
        fix_for_statement(statement->u.for_statement);
        break;

    case STATEMENT_TYPE_DOFOR:
        fix_dofor_statement(statement->u.dofor_statement);
        break;

    default: break;
    }
}

void fix_expression(Expression* expression) {
    if (expression == NULL) {
        return;
    }
    switch (expression->type) {
    case EXPRESSION_TYPE_IDENTIFIER:
        fix_identifier_expression(expression->u.identifier_expression);
        break;

    case EXPRESSION_TYPE_ASSIGN:
        fix_assign_expression(expression->u.assign_expression);
        break;

    case EXPRESSION_TYPE_ARITHMETIC_ADD:
    case EXPRESSION_TYPE_ARITHMETIC_SUB:
    case EXPRESSION_TYPE_ARITHMETIC_MUL:
    case EXPRESSION_TYPE_ARITHMETIC_DIV:
    case EXPRESSION_TYPE_ARITHMETIC_MOD:
    case EXPRESSION_TYPE_LOGICAL_AND:
    case EXPRESSION_TYPE_LOGICAL_OR:
        fix_binary_expression(expression->u.binary_expression);
        break;

    default: break;
    }
}


// TODO: 这里得改改，目前暂时添加全局变量。
void fix_declaration(Declaration* declaration) {
    Ring_Compiler* ring_compiler = get_ring_compiler();
    declaration->variable_index  = ring_compiler->declaration_list_size++;

    Declaration* pos = ring_compiler->declaration_list;
    if (pos == NULL) {
        ring_compiler->declaration_list = declaration;
        return;
    }

    for (; pos->next != NULL; pos = pos->next) {}
    pos->next = declaration;
}

void fix_if_statement(IfStatement* if_statement) {
    fix_expression(if_statement->condition_expression);
    fix_statement_list(if_statement->if_block);
    fix_statement_list(if_statement->else_block);

    ElseIfStatement* pos = if_statement->elseif_statement_list;
    for (; pos; pos = pos->next) {
        fix_expression(pos->condition_expression);
        fix_statement_list(pos->elseif_block);
    }
}

void fix_for_statement(ForStatement* for_statement) {
    fix_expression(for_statement->init_expression);
    fix_expression(for_statement->condition_expression);
    fix_expression(for_statement->post_expression);
    fix_statement_list(for_statement->block);
}

void fix_dofor_statement(DoForStatement* dofor_statement) {
    fix_expression(dofor_statement->init_expression);
    fix_statement_list(dofor_statement->block);
    fix_expression(dofor_statement->condition_expression);
    fix_expression(dofor_statement->post_expression);
}

void fix_identifier_expression(IdentifierExpression* expression) {
    Declaration* declaration  = search_declaration(expression->identifier);
    expression->u.declaration = declaration;
}

void fix_assign_expression(AssignExpression* expression) {
    fix_expression(expression->left);
    fix_expression(expression->operand);
}

void fix_binary_expression(BinaryExpression* expression) {
    fix_expression(expression->left_expression);
    fix_expression(expression->right_expression);
}


// -----------------

Declaration* search_declaration(char* identifier) {
    for (Declaration* pos = get_ring_compiler()->declaration_list; pos; pos = pos->next) {
        if (!strcmp(identifier, pos->identifier)) {
            return pos;
        }
    }

    return NULL;
}
