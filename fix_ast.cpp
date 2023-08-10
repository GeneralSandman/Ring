/**********************************************
主要做：
    语法树的修正和语义检查
**********************************************/

#include "ring.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// 修正ast
void ring_compiler_fix_ast(PackageUnit* package_unit) {
    // fix global block
    fix_statement_list(package_unit->global_block_statement_list, nullptr, nullptr);

    // fix function list
    for (Function* pos : package_unit->function_list) {
        if (pos->block) {
            add_parameter_to_declaration(pos->parameter_list, pos->block);
            fix_statement_list(pos->block->statement_list, pos->block, pos);
        }
    }

    // fix class list
    unsigned int class_index = 0;
    for (ClassDefinition* pos : package_unit->class_definition_list) {
        pos->class_index = class_index++;
        fix_class_definition(pos);
    }
}

void fix_statement_list(Statement* statement_list, Block* block, Function* func) {
    if (statement_list == nullptr) {
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
    if (expression == nullptr) {
        return;
    }
    switch (expression->type) {
    case EXPRESSION_TYPE_IDENTIFIER:
        // TODO: 这里需要优化一下
        // 没有必要赋值 package_posit
        expression->u.identifier_expression->package_posit = expression->package_posit;
        expression->convert_type                           = fix_identifier_expression(expression->u.identifier_expression, block);
        break;

    case EXPRESSION_TYPE_ASSIGN:
        fix_assign_expression(expression->u.assign_expression, block, func);
        break;

    case EXPRESSION_TYPE_LITERAL_BOOL:
        expression->convert_type       = (TypeSpecifier*)malloc(sizeof(TypeSpecifier));
        expression->convert_type->kind = RING_BASIC_TYPE_BOOL;
        break;
    case EXPRESSION_TYPE_LITERAL_INT:
        expression->convert_type       = (TypeSpecifier*)malloc(sizeof(TypeSpecifier));
        expression->convert_type->kind = RING_BASIC_TYPE_INT;
        break;
    case EXPRESSION_TYPE_LITERAL_DOUBLE:
        expression->convert_type       = (TypeSpecifier*)malloc(sizeof(TypeSpecifier));
        expression->convert_type->kind = RING_BASIC_TYPE_DOUBLE;
        break;
    case EXPRESSION_TYPE_LITERAL_STRING:
        expression->convert_type       = (TypeSpecifier*)malloc(sizeof(TypeSpecifier));
        expression->convert_type->kind = RING_BASIC_TYPE_STRING;
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
        // TODO: 这里需要优化一下
        // 没有必要赋值 package_posit
        expression->u.function_call_expression->package_posit = expression->package_posit;
        fix_function_call_expression(expression->u.function_call_expression, block, func);
        break;
    case EXPRESSION_TYPE_METHOD_CALL:
        fix_method_call_expression(expression->u.method_call_expression, block, func);
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
    case EXPRESSION_TYPE_DOT:
        fix_dot_expression(expression, expression->u.dot_expression, block, func);
        break;

    case EXPRESSION_TYPE_TERNARY:
        fix_ternary_condition_expression(expression->u.ternary_expression, block, func);
        break;

    case EXPRESSION_TYPE_ARRAY_INDEX:
        fix_array_index_expression(expression, expression->u.array_index_expression, block, func);
        break;

    case EXPRESSION_TYPE_ARRAY_LITERAL:
        fix_array_literal_expression(expression, expression->u.array_literal_expression, block, func);
        break;

    default: break;
    }
}

void add_declaration(Declaration* declaration, Block* block, Function* func) {
    assert(declaration != nullptr);

    Declaration* pos  = declaration;
    Declaration* next = pos->next;
    for (; pos != nullptr; pos = next) {
        next      = pos->next;
        pos->next = nullptr;

        // fix type specifier
        fix_type_specfier(pos->type);


        if (block != nullptr) {
            block->declaration_list =
                declaration_list_add_item(block->declaration_list, pos);

            pos->variable_index = block->declaration_list_size++;
            pos->is_local       = 1;
        } else {
            PackageUnit* package_unit = get_package_unit();
            pos->variable_index       = package_unit->global_declaration_list.size();
            pos->is_local             = 0;
            package_unit->global_declaration_list.push_back(pos);
        }
    }
}

void fix_type_specfier(TypeSpecifier* type_specifier) {
    assert(type_specifier != nullptr);

    // 如果这个变量是类
    // 找到类的定义

    ClassDefinition* class_definition = nullptr;
    char*            class_identifier = nullptr;


    if (type_specifier->kind == RING_BASIC_TYPE_CLASS && type_specifier->u.class_type != nullptr) {
        class_identifier = type_specifier->u.class_type->class_identifier;
        class_definition = search_class_definition(class_identifier);

        if (class_definition == nullptr) {
            // error
            // exit
            complie_err_log("not find class definition [%s]", class_identifier);
            exit(ERROR_CODE_COMPILE_ERROR);
        }

        type_specifier->u.class_type->class_definition = class_definition;
    }
}

void fix_block(Block* block, Function* func) {
    if (block == nullptr) {
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
    if (for_statement == nullptr) {
        return;
    }

    fix_expression(for_statement->init_expression, block, func);
    fix_expression(for_statement->condition_expression, block, func);
    fix_expression(for_statement->post_expression, block, func);
    fix_block(for_statement->block, func);
}

void fix_dofor_statement(DoForStatement* dofor_statement, Block* block, Function* func) {
    if (dofor_statement == nullptr) {
        return;
    }

    fix_expression(dofor_statement->init_expression, block, func);
    fix_block(dofor_statement->block, func);
    fix_expression(dofor_statement->condition_expression, block, func);
    fix_expression(dofor_statement->post_expression, block, func);
}

void fix_return_statement(ReturnStatement* return_statement, Block* block, Function* func) {
    if (return_statement == nullptr) {
        return;
    }

    Expression* pos;
    for (pos = return_statement->return_list; pos; pos = pos->next) {
        fix_expression(pos, block, func);
    }
}

TypeSpecifier* fix_identifier_expression(IdentifierExpression* expression, Block* block) {
    assert(expression != nullptr);
    // TODO: 在这里要判断 identifier 是function 还是变量，
    // 然后从不同地方进行搜索
    // 并判断当前代码片段是否已经声明过相关的变量和函数
    // 报错提示
    //
    Declaration* declaration = nullptr;
    Function*    function    = nullptr;
    switch (expression->type) {
    case IDENTIFIER_EXPRESSION_TYPE_VARIABLE:
        declaration = search_declaration(expression->package_posit, expression->identifier, block);
        if (declaration == nullptr) {
            ring_compile_error(get_package_unit()->current_file_name.c_str(),
                               expression->line_number, 4,
                               package_unit_get_line_content(expression->line_number).c_str(),
                               ERROR_UNDECLARED_IDENTIFIER,
                               "use undeclared identifier '%s'", expression->identifier);

            ring_check_exit_immediately();
        }
        expression->u.declaration = declaration;
        return declaration->type;
        break;

    case IDENTIFIER_EXPRESSION_TYPE_FUNCTION:
        function               = search_function(expression->package_posit, expression->identifier);
        expression->u.function = function;
        break;

    default:
        break;
    }

    return nullptr;
}

void fix_assign_expression(AssignExpression* expression, Block* block, Function* func) {
    if (expression == nullptr) {
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
    if (expression == nullptr || expression->u.binary_expression == nullptr) {
        return;
    }

    Expression* left_expression  = expression->u.binary_expression->left_expression;
    Expression* right_expression = expression->u.binary_expression->right_expression;

    fix_expression(left_expression, block, func);
    fix_expression(right_expression, block, func);

    if (expression->convert_type == nullptr) {
        expression->convert_type = (TypeSpecifier*)malloc(sizeof(TypeSpecifier));
    }

    if (expression->type == EXPRESSION_TYPE_CONCAT) {
        expression->convert_type->kind = RING_BASIC_TYPE_STRING;
        return;
    }

    if (left_expression->type == EXPRESSION_TYPE_LITERAL_DOUBLE
        || right_expression->type == EXPRESSION_TYPE_LITERAL_DOUBLE) {
        expression->convert_type->kind = RING_BASIC_TYPE_DOUBLE;
    }

    if ((left_expression->convert_type && left_expression->convert_type->kind == RING_BASIC_TYPE_DOUBLE)
        || (right_expression->convert_type && right_expression->convert_type->kind == RING_BASIC_TYPE_DOUBLE)) {
        expression->convert_type->kind = RING_BASIC_TYPE_DOUBLE;
    }
}

void fix_function_call_expression(FunctionCallExpression* function_call_expression, Block* block, Function* func) {
    if (function_call_expression == nullptr) {
        return;
    }

    // TODO: 这里需要优化一下
    // 没有必要赋值 package_posit
    function_call_expression->function_identifier_expression->package_posit = function_call_expression->package_posit;
    fix_expression(function_call_expression->function_identifier_expression, block, func);

    ArgumentList* pos = function_call_expression->argument_list;
    for (; pos != nullptr; pos = pos->next) {
        fix_expression(pos->expression, block, func);
    }
}

void fix_method_call_expression(MethodCallExpression* method_call_expression, Block* block, Function* func) {
    if (method_call_expression == nullptr) {
        return;
    }

    char*                   member_identifier  = method_call_expression->member_identifier;
    ClassDefinition*        class_definition   = nullptr;
    ClassMemberDeclaration* member_declaration = nullptr;
    Expression*             object_expression  = method_call_expression->object_expression;

    // 0. fix object expression
    fix_expression(object_expression, block, func);

    // 1. find class definition by object.
    class_definition = object_expression->convert_type->u.class_type->class_definition;
    if (class_definition == nullptr) {
        fprintf(stderr, "fix_method_call_expression error\n");
        exit(ERROR_CODE_COMPILE_ERROR);
    }

    // 2. find member declaration by member identifier.
    member_declaration = search_class_member(class_definition, member_identifier);
    if (member_declaration == nullptr) {
        fprintf(stderr, "fix_member_expression error\n");
        exit(ERROR_CODE_COMPILE_ERROR);
    }
    method_call_expression->member_declaration = member_declaration;

    // 4. fix argument list
    ArgumentList* pos                          = method_call_expression->argument_list;
    for (; pos != nullptr; pos = pos->next) {
        fix_expression(pos->expression, block, func);
    }
}

void fix_class_definition(ClassDefinition* class_definition) {
    assert(class_definition != nullptr);

    unsigned int field_index  = 0;
    unsigned int method_index = 0;

    for (ClassMemberDeclaration* pos = class_definition->member; pos != nullptr; pos = pos->next) {
        if (pos->type == MEMBER_FIELD) {
            pos->u.field->index_of_class = field_index++;
        } else if (pos->type == MEMBER_METHOD) {
            pos->u.method->index_of_class = method_index++;

            if (pos->u.method->block) {
                fix_statement_list(pos->u.method->block->statement_list, pos->u.method->block, nullptr);
            }
        }
    }
}

void fix_array_index_expression(Expression* expression, ArrayIndexExpression* array_index_expression, Block* block, Function* func) {
    assert(array_index_expression != nullptr);

    Declaration* declaration = nullptr;

    declaration              = search_declaration(expression->package_posit,
                                                  array_index_expression->array_expression->u.identifier_expression->identifier,
                                                  block);

    if (declaration == nullptr) {
        printf("not found identifier:%s\n", array_index_expression->array_expression->u.identifier_expression->identifier);
        exit(1);
    }

    array_index_expression->array_expression->u.identifier_expression->u.declaration = declaration;
}

void fix_array_literal_expression(Expression* expression, ArrayLiteralExpression* array_literal_expression, Block* block, Function* func) {
    assert(array_literal_expression != nullptr);
    Expression* pos = array_literal_expression->expression_list;
    for (; pos != nullptr; pos = pos->next) {
        fix_expression(pos, block, func);
    }
}

// TODO:
// 暂时只支持field-member
void fix_member_expression(Expression* expression, MemberExpression* member_expression, Block* block, Function* func) {
    assert(member_expression != nullptr);

    char*                   member_identifier  = member_expression->member_identifier;
    ClassDefinition*        class_definition   = nullptr;
    ClassMemberDeclaration* member_declaration = nullptr;
    Expression*             object_expression  = member_expression->object_expression;


    // 0. fix object expression
    fix_expression(object_expression, block, func);

    // 1. find class definition by object.
    class_definition = object_expression->convert_type->u.class_type->class_definition;
    if (class_definition == nullptr) {
        fprintf(stderr, "fix_member_expression error\n");
        exit(ERROR_CODE_COMPILE_ERROR);
    }


    // 2. find member declaration by member identifier.
    member_declaration = search_class_member(class_definition, member_identifier);
    if (member_declaration == nullptr) {
        fprintf(stderr, "fix_member_expression error\n");
        exit(ERROR_CODE_COMPILE_ERROR);
    }
    member_expression->member_declaration = member_declaration;


    // expression 最终的类型取决于field-member 的类型
    expression->convert_type              = member_declaration->u.field->type;
    fix_class_member_expression(member_expression, member_expression->object_expression, member_expression->member_identifier);
}

void fix_dot_expression(Expression* expression, DotExpression* dot_expression, Block* block, Function* func) {
    assert(dot_expression != nullptr);

    // 1. prefix is a package name
    // 2. suffix is a object name
}

void fix_class_member_expression(MemberExpression* member_expression, Expression* object_expression, char* member_identifier) {
    // member_expression->member_declaration = ;
}

ClassDefinition* search_class_definition(char* class_identifier) {
    assert(class_identifier != nullptr);
    for (ClassDefinition* pos : get_package_unit()->class_definition_list) {
        if (0 == strcmp(pos->class_identifier, class_identifier)) {
            return pos;
        }
    }

    return nullptr;
}

ClassMemberDeclaration* search_class_member(ClassDefinition* class_definition, char* member_identifier) {
    assert(class_definition != nullptr);

    ClassMemberDeclaration* member_declaration = nullptr;

    for (member_declaration = class_definition->member; member_declaration != nullptr; member_declaration = member_declaration->next) {
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
    if (ternary_expression == nullptr) {
        return;
    }

    fix_expression(ternary_expression->condition_expression, block, func);
    fix_expression(ternary_expression->true_expression, block, func);
    fix_expression(ternary_expression->false_expression, block, func);
}

void add_parameter_to_declaration(Parameter* parameter, Block* block) {
    assert(block != nullptr);

    Parameter* pos = parameter;
    for (; pos; pos = pos->next) {
        Declaration* declaration    = (Declaration*)malloc(sizeof(Declaration));
        declaration->line_number    = pos->line_number;
        declaration->type           = pos->type;
        declaration->identifier     = pos->identifier;
        declaration->initializer    = nullptr;
        declaration->is_const       = 0;
        declaration->is_local       = 1;
        declaration->variable_index = -1; // fix in add_declaration
        declaration->next           = nullptr;

        add_declaration(declaration, block, nullptr);
    }
}

// -----------------
Declaration* search_declaration(char* package_posit, char* identifier, Block* block) {
    Declaration* decl = nullptr;

    for (; block; block = block->parent_block) {
        for (decl = block->declaration_list; decl; decl = decl->next) {
            if (0 == strcmp(identifier, decl->identifier)) {
                return decl;
            }
        }
    }
    for (Declaration* decl : get_package_unit()->global_declaration_list) {
        if (0 == strcmp(identifier, decl->identifier)) {
            return decl;
        }
    }

    return nullptr;
}

Function* search_function(char* package_posit, char* identifier) {
    if (package_posit != nullptr) {
        CompilerEntry* compiler_entry = get_compiler_entry();
        Package*       package        = search_package(compiler_entry, package_posit);
        if (package == nullptr) {
            printf("can't find package:%s\n", package_posit);
        }

        // TODO: 封装成函数
        for (auto function : package->function_list) {
            if (0 == strcmp(function->function_name, identifier)) {
                return function;
            }
        }

        return nullptr;
    }
    for (Function* pos : get_package_unit()->function_list) {
        if (!strcmp(identifier, pos->function_name)) {
            return pos;
        }
    }
    return nullptr;
}
