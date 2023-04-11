#include "ring.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// 修正ast
void ring_compiler_fix_ast(Ring_Compiler* compiler) {
    // fix statement list
    fix_statement_list(compiler->statement_list, NULL, NULL);

    // fix function list
    for (Function* pos = compiler->function_list; pos; pos = pos->next) {
        if (pos->block) {
            add_parameter_to_declaration(pos->parameter_list, pos->block);
            fix_statement_list(pos->block->statement_list, pos->block, pos);
        }
    }

    // fix class list
    for (ClassDefinition* pos = compiler->class_definition_list; pos != NULL; pos = pos->next) {
        fix_class_definition(pos);
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

    case STATEMENT_TYPE_RETURN:
        fix_return_statement(statement->u.return_statement, block, func);

    default: break;
    }
}

void fix_expression(Expression* expression, Block* block, Function* func) {
    if (expression == NULL) {
        return;
    }
    switch (expression->type) {
    case EXPRESSION_TYPE_IDENTIFIER:
        expression->convert_type = fix_identifier_expression(expression->u.identifier_expression, block);
        break;

    case EXPRESSION_TYPE_ASSIGN:
        fix_assign_expression(expression->u.assign_expression, block, func);
        break;

    case EXPRESSION_TYPE_LITERAL_BOOL:
        expression->convert_type             = malloc(sizeof(TypeSpecifier));
        expression->convert_type->basic_type = RING_BASIC_TYPE_BOOL;
        break;
    case EXPRESSION_TYPE_LITERAL_INT:
        expression->convert_type             = malloc(sizeof(TypeSpecifier));
        expression->convert_type->basic_type = RING_BASIC_TYPE_INT;
        break;
    case EXPRESSION_TYPE_LITERAL_DOUBLE:
        expression->convert_type             = malloc(sizeof(TypeSpecifier));
        expression->convert_type->basic_type = RING_BASIC_TYPE_DOUBLE;
        break;
    case EXPRESSION_TYPE_LITERAL_STRING:
        expression->convert_type             = malloc(sizeof(TypeSpecifier));
        expression->convert_type->basic_type = RING_BASIC_TYPE_STRING;
        break;

    case EXPRESSION_TYPE_CONCAT:
    case EXPRESSION_TYPE_ARITHMETIC_ADD:
    case EXPRESSION_TYPE_ARITHMETIC_SUB:
    case EXPRESSION_TYPE_ARITHMETIC_MUL:
    case EXPRESSION_TYPE_ARITHMETIC_DIV:
    case EXPRESSION_TYPE_ARITHMETIC_MOD:
        fix_binary_expression(expression, block, func);
        break;
    case EXPRESSION_TYPE_LOGICAL_AND:
    case EXPRESSION_TYPE_LOGICAL_OR:
    case EXPRESSION_TYPE_RELATIONAL_EQ:
    case EXPRESSION_TYPE_RELATIONAL_NE:
    case EXPRESSION_TYPE_RELATIONAL_GT:
    case EXPRESSION_TYPE_RELATIONAL_GE:
    case EXPRESSION_TYPE_RELATIONAL_LT:
    case EXPRESSION_TYPE_RELATIONAL_LE:
        fix_binary_expression(expression, block, func);
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

    case EXPRESSION_TYPE_MEMBER:
        fix_member_expression(expression, expression->u.member_expression, block, func);
        break;

    case EXPRESSION_TYPE_TERNARY:
        fix_ternary_condition_expression(expression->u.ternary_expression, block, func);
        break;

    default: break;
    }
}


void add_declaration(Declaration* declaration, Block* block, Function* func) {
    if (declaration == NULL) {
        return;
    }

    Declaration* pos  = declaration;
    Declaration* next = pos->next;
    for (; pos != NULL; pos = next) {
        next      = pos->next;
        pos->next = NULL;

        // fix type specifier
        fix_type_specfier(pos->type);


        if (block != NULL) {
            block->declaration_list =
                declaration_list_add_item(block->declaration_list, pos);

            pos->variable_index = block->declaration_list_size++;
            pos->is_local       = 1;
        } else {
            Ring_Compiler* ring_compiler = get_ring_compiler();
            ring_compiler->declaration_list =
                declaration_list_add_item(ring_compiler->declaration_list, pos);

            pos->variable_index = ring_compiler->declaration_list_size++;
            pos->is_local       = 0;
        }
    }
}

void fix_type_specfier(TypeSpecifier* type_specifier) {
    assert(type_specifier != NULL);

    // 如果这个变量是类
    // 找到类的定义

    ClassDefinition* class_definition = NULL;
    char*            class_identifier = NULL;


    if (type_specifier->basic_type == RING_BASIC_TYPE_CLASS && type_specifier->derive_type->u.class_type != NULL) {
        class_identifier = type_specifier->derive_type->u.class_type->class_identifier;
        class_definition = search_class_definition(class_identifier);

        if (class_definition == NULL) {
            // error
            // exit
            complie_err_log("not find class definition [%s]", class_identifier);
            exit(ERROR_CODE_COMPILE_ERROR);
        }

        type_specifier->derive_type->u.class_type->class_definition = class_definition;
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

void fix_return_statement(ReturnStatement* return_statement, Block* block, Function* func) {
    if (return_statement == NULL) {
        return;
    }

    Expression* pos;
    for (pos = return_statement->return_list; pos; pos = pos->next) {
        fix_expression(pos, block, func);
    }
}

TypeSpecifier* fix_identifier_expression(IdentifierExpression* expression, Block* block) {
    if (expression == NULL) {
        return NULL;
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
        return declaration->type;
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

    return NULL;
}

void fix_assign_expression(AssignExpression* expression, Block* block, Function* func) {
    if (expression == NULL) {
        return;
    }

    for (Expression* pos = expression->left; pos; pos = pos->next) {
        fix_expression(pos, block, func);
    }
    for (Expression* pos = expression->operand; pos; pos = pos->next) {
        fix_expression(pos, block, func);
    }
}

void fix_binary_expression(Expression* expression, Block* block, Function* func) {
    if (expression == NULL || expression->u.binary_expression == NULL) {
        return;
    }

    Expression* left_expression  = expression->u.binary_expression->left_expression;
    Expression* right_expression = expression->u.binary_expression->right_expression;

    fix_expression(left_expression, block, func);
    fix_expression(right_expression, block, func);

    if (expression->convert_type == NULL) {
        expression->convert_type = malloc(sizeof(TypeSpecifier));
    }

    if (expression->type == EXPRESSION_TYPE_CONCAT) {
        expression->convert_type->basic_type = RING_BASIC_TYPE_STRING;
        return;
    }

    if (left_expression->type == EXPRESSION_TYPE_LITERAL_DOUBLE
        || right_expression->type == EXPRESSION_TYPE_LITERAL_DOUBLE) {
        expression->convert_type->basic_type = RING_BASIC_TYPE_DOUBLE;
    }

    if ((left_expression->convert_type && left_expression->convert_type->basic_type == RING_BASIC_TYPE_DOUBLE)
        || (right_expression->convert_type && right_expression->convert_type->basic_type == RING_BASIC_TYPE_DOUBLE)) {
        expression->convert_type->basic_type = RING_BASIC_TYPE_DOUBLE;
    }
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

void fix_class_definition(ClassDefinition* class_definition) {
    assert(class_definition != NULL);

    unsigned int field_index  = 0;
    unsigned int method_index = 0;

    for (ClassMemberDeclaration* pos = class_definition->member; pos != NULL; pos = pos->next) {
        if (pos->type == MEMBER_FIELD) {
            pos->u.field->index_of_class = field_index++;
        } else if (pos->type == MEMBER_METHOD) {
            pos->u.method->index_of_class = method_index++;
        }
    }
}

// TODO:
// 暂时只支持field-member
void fix_member_expression(Expression* expression, MemberExpression* member_expression, Block* block, Function* func) {
    assert(member_expression != NULL);

    char*                   member_identifier  = member_expression->member_identifier;
    ClassDefinition*        class_definition   = NULL;
    ClassMemberDeclaration* member_declaration = NULL;
    Expression*             object_expression  = member_expression->object_expression;


    // 0. fix object expression
    fix_expression(object_expression, block, func);

    // 1. find class definition by object.
    class_definition = object_expression->convert_type->derive_type->u.class_type->class_definition;
    if (class_definition == NULL) {
        fprintf(stderr, "fix_member_expression error\n");
        exit(ERROR_CODE_COMPILE_ERROR);
    }


    // 2. find member declaration by member identifier.
    member_declaration = search_class_member(class_definition, member_identifier);
    if (member_declaration == NULL) {
        fprintf(stderr, "fix_member_expression error\n");
        exit(ERROR_CODE_COMPILE_ERROR);
    }
    member_expression->member_declaration = member_declaration;


    // expression 最终的类型取决于field-member 的类型
    expression->convert_type = member_declaration->u.field->type;
    fix_class_member_expression(member_expression, member_expression->object_expression, member_expression->member_identifier);
}

void fix_class_member_expression(MemberExpression* member_expression, Expression* object_expression, char* member_identifier) {
    // member_expression->member_declaration = ;
}

ClassDefinition* search_class_definition(char* class_identifier) {
    assert(class_identifier != NULL);
    ClassDefinition* pos = get_ring_compiler()->class_definition_list;

    for (; pos != NULL; pos = pos->next) {
        if (0 == strcmp(pos->class_identifier, class_identifier)) {
            break;
        }
    }

    return pos;
}

ClassMemberDeclaration* search_class_member(ClassDefinition* class_definition, char* member_identifier) {
    assert(class_definition != NULL);

    ClassMemberDeclaration* member_declaration = NULL;

    for (member_declaration = class_definition->member; member_declaration != NULL; member_declaration = member_declaration->next) {
        if (member_declaration->type == MEMBER_FIELD) {
            if (0 == strcmp(member_declaration->u.field->identifier, member_identifier)) {
                break;
            }
        } else if (member_declaration->type == MEMBER_METHOD) {
            if (0 == strcmp(member_declaration->u.method->identifier, member_identifier)) {
                break;
            }
        }
    }

    return member_declaration;
}

void fix_ternary_condition_expression(TernaryExpression* ternary_expression, Block* block, Function* func) {
    if (ternary_expression == NULL) {
        return;
    }

    fix_expression(ternary_expression->condition_expression, block, func);
    fix_expression(ternary_expression->true_expression, block, func);
    fix_expression(ternary_expression->false_expression, block, func);
}

void add_parameter_to_declaration(Parameter* parameter, Block* block) {
    assert(block != NULL);

    Parameter* pos = parameter;
    for (; pos; pos = pos->next) {
        Declaration* declaration    = malloc(sizeof(Declaration));
        declaration->line_number    = pos->line_number;
        declaration->type           = pos->type;
        declaration->identifier     = pos->identifier;
        declaration->initializer    = NULL;
        declaration->is_const       = 0;
        declaration->is_local       = 1;
        declaration->variable_index = -1; // fix in add_declaration
        declaration->next           = NULL;

        add_declaration(declaration, block, NULL);
    }
}


// -----------------

Declaration* search_declaration(char* identifier, Block* block) {
    Declaration* decl = NULL;

    for (; block; block = block->parent_block) {
        for (decl = block->declaration_list; decl; decl = decl->next) {
            if (0 == strcmp(identifier, decl->identifier)) {
                return decl;
            }
        }
    }

    for (decl = get_ring_compiler()->declaration_list; decl; decl = decl->next) {
        if (0 == strcmp(identifier, decl->identifier)) {
            return decl;
        }
    }

    printf("can't find identifier %s\n", identifier);
    exit(ERROR_CODE_COMPILE_ERROR);
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
