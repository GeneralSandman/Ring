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
        fix_expression(statement->u.if_statement->condition_expression);
        fix_statement_list(statement->u.if_statement->if_block);

    default: break;
    }
}

void fix_expression(Expression* expression) {
    switch (expression->type) {
    case EXPRESSION_TYPE_IDENTIFIER:
        fix_identifier_expression(expression->u.identifier_expression);
        break;

    case EXPRESSION_TYPE_ASSIGN:
        fix_assign_expression(expression->u.assign_expression);

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


void fix_identifier_expression(IdentifierExpression* expression) {
    Declaration* declaration  = search_declaration(expression->identifier);
    expression->u.declaration = declaration;
}

void fix_assign_expression(AssignExpression* expression) {
    fix_expression(expression->left);
    fix_expression(expression->operand);
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
