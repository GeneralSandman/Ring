#include "ring.h"
#include <string.h>

// 修正ast
void ring_compiler_fix_ast(Ring_Compiler* compiler) {
    Function* pos;

    fix_statement_list(compiler->statement_list, NULL, NULL);

    for (pos = compiler->function_list; pos; pos = pos->next) {
        if (pos->block) {
            add_parameter_to_declaration(pos->parameter_list);
            fix_statement_list(pos->block->statement_list, pos->block, pos);
        }
    }

#ifdef DEBUG
    ring_compiler_functions_dump(compiler);
#endif
}

void fix_statement_list(Statement* statement_list, Block* block, Function* func) {
    if (statement_list == NULL) {
        return;
    }

    for (Statement* pos = statement_list; pos; pos = pos->next) {
        fix_statement(pos, block, func);
    }
}

void fix_statement(Statement* statement, Block* block, Function* func) {
    switch (statement->type) {
    case STATEMENT_TYPE_EXPRESSION:
        fix_expression(statement->u.expression, block, func);
        break;
    case STATEMENT_TYPE_DECLARATION:
        add_declaration(statement->u.declaration_statement, block, func);
        break;

    case STATEMENT_TYPE_IF:
        fix_if_statement(statement->u.if_statement, block, func);
        break;

    case STATEMENT_TYPE_FOR:
        fix_for_statement(statement->u.for_statement, block, func);
        break;

    case STATEMENT_TYPE_DOFOR:
        fix_dofor_statement(statement->u.dofor_statement, block, func);
        break;

    default: break;
    }
}

void fix_expression(Expression* expression, Block* block, Function* func) {
    if (expression == NULL) {
        return;
    }
    switch (expression->type) {
    case EXPRESSION_TYPE_IDENTIFIER:
        fix_identifier_expression(expression->u.identifier_expression, block);
        break;

    case EXPRESSION_TYPE_ASSIGN:
        fix_assign_expression(expression->u.assign_expression, block, func);
        break;

    case EXPRESSION_TYPE_LITERAL_STRING:
        break;

    case EXPRESSION_TYPE_ARITHMETIC_ADD:
    case EXPRESSION_TYPE_ARITHMETIC_SUB:
    case EXPRESSION_TYPE_ARITHMETIC_MUL:
    case EXPRESSION_TYPE_ARITHMETIC_DIV:
    case EXPRESSION_TYPE_ARITHMETIC_MOD:
    case EXPRESSION_TYPE_LOGICAL_AND:
    case EXPRESSION_TYPE_LOGICAL_OR:
    case EXPRESSION_TYPE_RELATIONAL_EQ:
    case EXPRESSION_TYPE_RELATIONAL_NE:
    case EXPRESSION_TYPE_RELATIONAL_GT:
    case EXPRESSION_TYPE_RELATIONAL_GE:
    case EXPRESSION_TYPE_RELATIONAL_LT:
    case EXPRESSION_TYPE_RELATIONAL_LE:
        fix_binary_expression(expression->u.binary_expression, block, func);
        break;

    case EXPRESSION_TYPE_FUNCTION_CALL:
        fix_function_call_expression(expression->u.function_call_expression, block, func);
        break;

    case EXPRESSION_TYPE_LOGICAL_UNITARY_NOT:
    case EXPRESSION_TYPE_UNITARY_INCREASE_SUFFIX:
    case EXPRESSION_TYPE_UNITARY_INCREASE_PREFIX:
    case EXPRESSION_TYPE_UNITARY_DECREASE_SUFFIX:
    case EXPRESSION_TYPE_UNITARY_DECREASE_PREFIX:
        fix_expression(expression->u.unitary_expression, block, func);
        break;

    case EXPRESSION_TYPE_CAST:
        fix_expression(expression->u.cast_expression->operand, block, func);
        break;

    default: break;
    }
}


// TODO: 这里得改改，目前暂时添加全局变量。
void add_declaration(Declaration* declaration, Block* block, Function* func) {
    if (block != NULL) {
        block->declaration_list =
            declaration_list_add_item(block->declaration_list, declaration);

        declaration->variable_index = block->declaration_list_size++;
        declaration->is_local       = 1;
    } else {
        Ring_Compiler* ring_compiler = get_ring_compiler();
        ring_compiler->declaration_list =
            declaration_list_add_item(ring_compiler->declaration_list, declaration);

        declaration->variable_index = ring_compiler->declaration_list_size++;
        declaration->is_local       = 0;
    }
}

void fix_block(Block* block, Function* func) {
    if (block == NULL) {
        return;
    }
    fix_statement_list(block->statement_list, block, func);
}

void fix_if_statement(IfStatement* if_statement, Block* block, Function* func) {
    fix_expression(if_statement->condition_expression, block, func);

    fix_block(if_statement->if_block, func);
    fix_block(if_statement->else_block, func);

    ElseIfStatement* pos = if_statement->elseif_list;
    for (; pos; pos = pos->next) {
        fix_expression(pos->condition_expression, block, func);
        fix_block(pos->elseif_block, func);
    }
}


void fix_for_statement(ForStatement* for_statement, Block* block, Function* func) {
    if (for_statement == NULL) {
        return;
    }

    fix_expression(for_statement->init_expression, block, func);
    fix_expression(for_statement->condition_expression, block, func);
    fix_expression(for_statement->post_expression, block, func);
    fix_block(for_statement->block, func);
}

void fix_dofor_statement(DoForStatement* dofor_statement, Block* block, Function* func) {
    if (dofor_statement == NULL) {
        return;
    }

    fix_expression(dofor_statement->init_expression, block, func);
    fix_block(dofor_statement->block, func);
    fix_expression(dofor_statement->condition_expression, block, func);
    fix_expression(dofor_statement->post_expression, block, func);
}

void fix_identifier_expression(IdentifierExpression* expression, Block* block) {
    if (expression == NULL) {
        return;
    }
    // TODO: 在这里要判断 identifier 是function 还是变量，
    // 然后从不同地方进行搜索
    // 并判断当前代码片段是否已经声明过相关的变量和函数
    // 报错提示
    //
    Declaration* declaration = NULL;
    Function*    function    = NULL;
    switch (expression->type) {
    case IDENTIFIER_EXPRESSION_TYPE_VARIABLE:
        declaration               = search_declaration(expression->identifier, block);
        expression->u.declaration = declaration;
        break;

    case IDENTIFIER_EXPRESSION_TYPE_VARIABLE_ARRAY:
        break;

    case IDENTIFIER_EXPRESSION_TYPE_FUNCTION:
        function               = search_function(expression->identifier);
        expression->u.function = function;
        break;

    default:
        break;
    }
}

void fix_assign_expression(AssignExpression* expression, Block* block, Function* func) {
    if (expression == NULL) {
        return;
    }

    fix_expression(expression->left, block, func);
    fix_expression(expression->operand, block, func);
}

void fix_binary_expression(BinaryExpression* expression, Block* block, Function* func) {
    if (expression == NULL) {
        return;
    }

    fix_expression(expression->left_expression, block, func);
    fix_expression(expression->right_expression, block, func);
}

void fix_function_call_expression(FunctionCallExpression* function_call_expression, Block* block, Function* func) {
    if (function_call_expression == NULL) {
        return;
    }

    fix_expression(function_call_expression->function_identifier_expression, block, func);

    ArgumentList* pos = function_call_expression->argument_list;
    for (; pos != NULL; pos = pos->next) {
        fix_expression(pos->expression, block, func);
    }
}

void add_parameter_to_declaration(Variable* parameter) {
}


// -----------------

Declaration* search_declaration(char* identifier, Block* block) {
    Block*       current_block = NULL;
    Declaration* decl          = NULL;

    for (current_block = block; current_block; current_block = current_block->parent_block) {
        for (decl = block->declaration_list; decl; decl = decl->next) {
            if (0 == strcmp(identifier, decl->identifier)) {
                return decl;
            }
        }
    }

    for (decl = get_ring_compiler()->declaration_list; decl; decl = decl->next) {
        if (!strcmp(identifier, decl->identifier)) {
            return decl;
        }
    }

    return NULL;
}

Function* search_function(char* identifier) {
    Function* pos = get_ring_compiler()->function_list;
    for (; pos; pos = pos->next) {
        if (!strcmp(identifier, pos->function_name)) {
            return pos;
        }
    }
    return NULL;
}
