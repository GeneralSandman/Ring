#include "ring.hpp"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>


// finish a block compile
void finish_global_block(Statement* global_statement_list) {
    debug_log_with_yellow_coloar("");

    get_package_unit()->global_block_statement_list = global_statement_list;
    for (; global_statement_list != nullptr; global_statement_list = global_statement_list->next) {
        get_package_unit()->global_block_statement_list_size++;
    }

    // 将全局变量 添加到 package_unit->global_declaration_list 上
    for (Statement* statement = get_package_unit()->global_block_statement_list; statement; statement = statement->next) {
        switch (statement->type) {
        case STATEMENT_TYPE_DECLARATION:
            add_declaration(statement->u.declaration_statement, nullptr, nullptr);
            break;
        default:
            fprintf(stderr, "error statement->type:%d in global statement list\n", statement->type);
            exit(1);
            break;
        }
    }
}

Statement* statement_list_add_item(Statement* statement_list, Statement* statement) {
    debug_log_with_yellow_coloar("statement->type:%d", statement->type);

    Statement* pos = statement_list;
    for (; pos->next != nullptr; pos = pos->next)
        ;
    pos->next = statement;
    return statement_list;
}

Statement* create_statemen_from_expression(Expression* expression) {
    debug_log_with_yellow_coloar("expression->type:%d", expression->type);

    Statement* statement    = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->type         = STATEMENT_TYPE_EXPRESSION;
    statement->line_number  = package_unit_get_line_number();
    statement->u.expression = expression;
    statement->next         = nullptr;
    return statement;
}

void add_function_definition(AttributeInfo* attribute_info, Function* function_definition) {
    assert(function_definition != nullptr);
    debug_log_with_yellow_coloar("function_definition->type:%d", function_definition->type);

    function_definition->attribute_info = attribute_info;

    for (AttributeInfo* pos = attribute_info; pos; pos = pos->next) {
        if (0 == strcmp(pos->name, "native")) {
            function_definition->type = FUNCTION_TYPE_NATIVE;
        }
    }

    get_package_unit()->function_list.push_back(function_definition);
}

Expression* expression_add_package_posit(Expression* expression, char* package_posit) {
    assert(expression != nullptr);
    expression->package_posit = package_posit;
    return expression;
}

Expression* create_expression_identifier(char* identifier) {
    debug_log_with_yellow_coloar("identifier:%s", identifier);

    IdentifierExpression* identifier_expression = (IdentifierExpression*)mem_alloc(get_front_mem_pool(), sizeof(IdentifierExpression));
    identifier_expression->line_number          = package_unit_get_line_number();
    identifier_expression->type                 = IDENTIFIER_EXPRESSION_TYPE_VARIABLE;
    identifier_expression->identifier           = identifier;
    identifier_expression->u.declaration        = nullptr;

    Expression* expression                      = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                     = package_unit_get_line_number();
    expression->convert_type                    = nullptr; // fix in fix_ast
    expression->type                            = EXPRESSION_TYPE_IDENTIFIER;
    expression->u.identifier_expression         = identifier_expression;
    expression->next                            = nullptr;

    return expression;
}

// TODO: 后续合并为一个，目的是在 fix_ast 中 去确定 identifier 的 类型
Expression* create_expression_identifier2(char* identifier, IdentifierExpressionType type) {
    debug_log_with_yellow_coloar("identifier:%s", identifier);

    IdentifierExpression* identifier_expression = (IdentifierExpression*)mem_alloc(get_front_mem_pool(), sizeof(IdentifierExpression));
    identifier_expression->line_number          = package_unit_get_line_number();
    identifier_expression->type                 = type;
    identifier_expression->identifier           = identifier;
    identifier_expression->u.declaration        = nullptr;

    Expression* expression                      = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                     = package_unit_get_line_number();
    expression->convert_type                    = nullptr; // fix in fix_ast
    expression->type                            = EXPRESSION_TYPE_IDENTIFIER;
    expression->u.identifier_expression         = identifier_expression;

    return expression;
}

Expression* create_expression_identifier_with_index(Expression* array_expression, Expression* index) {
    debug_log_with_yellow_coloar("\t");

    ArrayIndexExpression* array_index_expression = (ArrayIndexExpression*)mem_alloc(get_front_mem_pool(), sizeof(ArrayIndexExpression));
    array_index_expression->line_number          = package_unit_get_line_number();
    array_index_expression->array_expression     = array_expression;
    array_index_expression->index_expression     = index;

    Expression* expression                       = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                      = package_unit_get_line_number();
    expression->convert_type                     = nullptr; // fix in fix_ast
    expression->type                             = EXPRESSION_TYPE_ARRAY_INDEX;
    expression->u.array_index_expression         = array_index_expression;

    return expression;
}

Expression* create_expression_from_function_call(FunctionCallExpression* function_call_expression) {
    debug_log_with_yellow_coloar("function_call_expression->name:");

    Expression* expression                 = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                = package_unit_get_line_number();
    expression->convert_type               = nullptr; // fix in fix_ast
    expression->type                       = EXPRESSION_TYPE_FUNCTION_CALL;
    expression->u.function_call_expression = function_call_expression;
    return expression;
}

Expression* create_expression_from_method_call(MethodCallExpression* method_call_expression) {
    debug_log_with_yellow_coloar("method_call_expression->name:");

    Expression* expression               = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number              = package_unit_get_line_number();
    expression->convert_type             = nullptr; // fix in fix_ast
    expression->type                     = EXPRESSION_TYPE_METHOD_CALL;
    expression->u.method_call_expression = method_call_expression;
    return expression;
}

Expression* create_expression_from_array_literal(ArrayLiteralExpression* array_literal) {
    debug_log_with_yellow_coloar("\t");

    Expression* expression                 = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                = package_unit_get_line_number();
    expression->convert_type               = nullptr; // fix in fix_ast
    expression->type                       = EXPRESSION_TYPE_ARRAY_LITERAL;
    expression->u.array_literal_expression = array_literal;
    return expression;
}

Expression* create_expression_from_class_object_literal(ClassObjectLiteralExpression* object_literal) {
    debug_log_with_yellow_coloar("\t");

    Expression* expression                        = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                       = package_unit_get_line_number();
    expression->convert_type                      = nullptr; // fix in fix_ast
    expression->type                              = EXPRESSION_TYPE_CLASS_OBJECT_LITERAL;
    expression->u.class_object_literal_expression = object_literal;
    return expression;
}

Expression* create_expression_assign(AssignExpression* assign_expression) {
    // debug_log_with_yellow_coloar("assign_expression->assign_identifier:%s", assign_expression->assign_identifier);

    Expression* expression          = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number         = package_unit_get_line_number();
    expression->convert_type        = nullptr; // fix in fix_ast
    expression->type                = EXPRESSION_TYPE_ASSIGN;
    expression->u.assign_expression = assign_expression;
    return expression;
}

Expression* create_expression_ternary(Expression* condition, Expression* true_expression, Expression* false_expression) {
    Expression* expression                                 = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                                = package_unit_get_line_number();
    expression->convert_type                               = nullptr; // fix in fix_ast
    expression->type                                       = EXPRESSION_TYPE_TERNARY;
    expression->u.ternary_expression                       = (TernaryExpression*)mem_alloc(get_front_mem_pool(), sizeof(TernaryExpression));
    expression->u.ternary_expression->line_number          = package_unit_get_line_number();
    expression->u.ternary_expression->condition_expression = condition;
    expression->u.ternary_expression->true_expression      = true_expression;
    expression->u.ternary_expression->false_expression     = false_expression;
    return expression;
}

Expression* create_expression_binary(ExpressionType type, Expression* left, Expression* right) {
    debug_log_with_yellow_coloar("type:%d", type);

    Expression* expression                            = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                           = package_unit_get_line_number();
    expression->convert_type                          = nullptr; // fix in fix_ast
    expression->type                                  = type;
    expression->u.binary_expression                   = (BinaryExpression*)mem_alloc(get_front_mem_pool(), sizeof(BinaryExpression));
    expression->u.binary_expression->line_number      = package_unit_get_line_number();
    expression->u.binary_expression->left_expression  = left;
    expression->u.binary_expression->right_expression = right;

    return expression;
}

Expression* create_expression_unitary(ExpressionType type, Expression* unitary_expression) {
    debug_log_with_yellow_coloar("type:%d", type);

    Expression* expression           = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number          = package_unit_get_line_number();
    expression->convert_type         = nullptr; // fix in fix_ast
    expression->type                 = type;
    expression->u.unitary_expression = unitary_expression;
    expression->next                 = nullptr;

    return expression;
}

// ring.bison.y 中 第一个参数是 VariableType
// 该定义       中 第一个参数是 BasicValueType
// TODO: 这里以后统一
Expression* create_expression_unitary_with_convert_type(BasicValueType convert_type, Expression* expression) {
    debug_log_with_yellow_coloar("convert_type:%d", convert_type);

    assert(expression != nullptr);

    return expression;
}

Expression*
create_expression_literal(ExpressionType type, char* literal_interface) {
    debug_log_with_yellow_coloar("type:%d", type);

    assert(literal_interface != nullptr);
    Expression* expression   = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number  = package_unit_get_line_number();
    expression->convert_type = nullptr; // fix in fix_ast

    expression->type         = type;
    switch (type) {
    case EXPRESSION_TYPE_LITERAL_INT:
        sscanf(literal_interface, "%d", &(expression->u.int_literal));
        break;
    case EXPRESSION_TYPE_LITERAL_DOUBLE:
        sscanf(literal_interface, "%lf", &expression->u.double_literal);
        break;
    case EXPRESSION_TYPE_LITERAL_STRING:
        // TODO: 这里不太对，可能要开辟新的内存
        expression->u.string_literal = literal_interface;
        // sscanf(literal_interface, "%s", expression->u.string_literal);
        break;
    default:
        break;
    }

    return expression;
}

Expression* create_expression_bool_literal(ExpressionType type, Ring_Bool value) {
    debug_log_with_yellow_coloar("type:%d, boolean:%d", type, value);

    Expression* expression     = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number    = package_unit_get_line_number();
    expression->convert_type   = nullptr; // fix in fix_ast
    expression->type           = type;
    expression->u.bool_literal = value;

    return expression;
}

Expression* create_cast_expression(TypeSpecifier* cast_type, Expression* operand) {
    Expression* expression                     = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                    = package_unit_get_line_number();
    expression->convert_type                   = nullptr; // fix in fix_ast
    expression->type                           = EXPRESSION_TYPE_CAST;
    expression->u.cast_expression              = (CastExpression*)mem_alloc(get_front_mem_pool(), sizeof(CastExpression));
    expression->u.cast_expression->line_number = package_unit_get_line_number();
    expression->u.cast_expression->type        = cast_type;
    expression->u.cast_expression->operand     = operand;

    return expression;
}

Expression* create_member_expression(Expression* object_expression, char* member_identifier) {
    Expression* expression                              = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                             = package_unit_get_line_number();
    expression->convert_type                            = nullptr; // fix in fix_ast
    expression->type                                    = EXPRESSION_TYPE_MEMBER;
    expression->u.member_expression                     = (MemberExpression*)mem_alloc(get_front_mem_pool(), sizeof(MemberExpression));
    expression->u.member_expression->line_number        = package_unit_get_line_number();
    expression->u.member_expression->object_expression  = object_expression;
    expression->u.member_expression->member_identifier  = member_identifier;
    expression->u.member_expression->member_declaration = nullptr;

    return expression;
}

Expression* create_dot_expression(Expression* prefix_expression, Expression* suffix_expression) {
    Expression* expression                          = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                         = package_unit_get_line_number();
    expression->convert_type                        = nullptr; // fix in fix_ast
    expression->type                                = EXPRESSION_TYPE_DOT;
    expression->u.dot_expression                    = (DotExpression*)mem_alloc(get_front_mem_pool(), sizeof(DotExpression));
    expression->u.dot_expression->line_number       = package_unit_get_line_number();
    expression->u.dot_expression->prefix_expression = prefix_expression;
    expression->u.dot_expression->suffix_expression = suffix_expression;

    return expression;
}

Expression* create_new_array_expression(TypeSpecifier* type_specifier, DimensionExpression* dimension_expression) {
    Expression* expression                                   = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                                  = package_unit_get_line_number();
    expression->convert_type                                 = nullptr; // fix in fix_ast
    expression->type                                         = EXPRESSION_TYPE_NEW_ARRAY;
    expression->u.new_array_expression                       = (NewArrayExpression*)mem_alloc(get_front_mem_pool(), sizeof(NewArrayExpression));
    expression->u.new_array_expression->line_number          = package_unit_get_line_number();
    expression->u.new_array_expression->type_specifier       = type_specifier;
    expression->u.new_array_expression->dimension_expression = dimension_expression;

    return expression;
}

FieldInitExpression* create_field_init_expression(char* field_identifier, Expression* init_expression) {
    FieldInitExpression* expression = (FieldInitExpression*)mem_alloc(get_front_mem_pool(), sizeof(FieldInitExpression));
    expression->line_number         = package_unit_get_line_number();
    expression->field_identifier    = field_identifier;
    expression->init_expression     = init_expression;
    expression->next                = nullptr;
    return expression;
}

FieldInitExpression* field_init_list_add_item(FieldInitExpression* list, FieldInitExpression* item) {
    FieldInitExpression* pos = list;
    for (; pos->next != nullptr; pos = pos->next)
        ;
    pos->next = item;
    return list;
}

AssignExpression* create_assign_expression(AssignExpressionType type, Expression* left, Expression* operand) {
    AssignExpression* assing_expression = (AssignExpression*)mem_alloc(get_front_mem_pool(), sizeof(AssignExpression));

    assing_expression->line_number      = package_unit_get_line_number();
    assing_expression->type             = type;
    assing_expression->left             = left;
    assing_expression->operand          = operand;
    return assing_expression;
}

AssignExpression* create_multi_assign_expression(char* first_identifier, Identifier* identifier_list, Expression* operand) {
    // TODO: 这里要判断一下，identifier是不是已经定义过了，并且identifier 不是函数，还要涉及到identifier重复的问题。
    debug_log_with_yellow_coloar("");

    Expression* left = nullptr;
    left             = create_expression_identifier(first_identifier);

    Expression* prev = left;
    for (Identifier* pos = identifier_list; pos; pos = pos->next) {
        prev->next = create_expression_identifier(pos->identifier_name);
        prev       = prev->next;
    }

    AssignExpression* assing_expression = (AssignExpression*)mem_alloc(get_front_mem_pool(), sizeof(AssignExpression));

    assing_expression->line_number      = package_unit_get_line_number();
    assing_expression->type             = ASSIGN_EXPRESSION_TYPE_MULTI_ASSIGN;
    assing_expression->left             = left;
    assing_expression->operand          = operand;
    return assing_expression;
}

FunctionCallExpression* create_function_call_expression(char* identifier, ArgumentList* argument_list) {
    debug_log_with_yellow_coloar("identifier:%s", identifier);

    Expression*             function_identifier_expression   = create_expression_identifier2(identifier, IDENTIFIER_EXPRESSION_TYPE_FUNCTION);

    FunctionCallExpression* function_call_expression         = (FunctionCallExpression*)mem_alloc(get_front_mem_pool(), sizeof(FunctionCallExpression));
    function_call_expression->line_number                    = package_unit_get_line_number();
    function_call_expression->function_identifier_expression = function_identifier_expression;
    function_call_expression->argument_list                  = argument_list;
    return function_call_expression;
}

MethodCallExpression* create_method_call_expression(Expression* object_expression, char* member_identifier, ArgumentList* argument_list) {
    MethodCallExpression* method_call_expression = (MethodCallExpression*)mem_alloc(get_front_mem_pool(), sizeof(MethodCallExpression));
    method_call_expression->line_number          = package_unit_get_line_number();
    method_call_expression->object_expression    = object_expression;
    method_call_expression->member_identifier    = member_identifier;
    method_call_expression->argument_list        = argument_list;
    return method_call_expression;
}

ArrayLiteralExpression* create_array_literal_expression(TypeSpecifier* type_specifier, DimensionExpression* dimension_expression, Expression* expression_list) {
    ArrayLiteralExpression* array_literal = (ArrayLiteralExpression*)mem_alloc(get_front_mem_pool(), sizeof(ArrayLiteralExpression));
    array_literal->line_number            = package_unit_get_line_number();
    array_literal->type_specifier         = type_specifier;
    array_literal->dimension_expression   = dimension_expression;
    array_literal->expression_list        = expression_list;
    return array_literal;
}

ClassObjectLiteralExpression* create_class_object_literal_expression(TypeSpecifier* type_specifier, FieldInitExpression* field_init_expression_list) {
    ClassObjectLiteralExpression* object_literal = (ClassObjectLiteralExpression*)mem_alloc(get_front_mem_pool(), sizeof(ClassObjectLiteralExpression));
    object_literal->line_number                  = package_unit_get_line_number();
    object_literal->type_specifier               = type_specifier;
    object_literal->field_init_expression_list   = field_init_expression_list;
    return object_literal;
}

Expression* expression_list_add_item(Expression* expression_list, Expression* expression) {
    debug_log_with_yellow_coloar("");

    Expression* pos = expression_list;
    for (; pos->next != nullptr; pos = pos->next)
        ;
    pos->next = expression;
    return expression_list;
}

ArgumentList* argument_list_add_item(ArgumentList* argument_list, ArgumentList* argument) {
    ArgumentList* pos = argument_list;
    for (; pos->next != nullptr; pos = pos->next)
        ;
    pos->next = argument;
    return argument_list;
}

ArgumentList* create_argument_list_from_expression(Expression* expression) {
    debug_log_with_yellow_coloar("expression->type:%d", expression->type);

    ArgumentList* argument_list = (ArgumentList*)mem_alloc(get_front_mem_pool(), sizeof(ArgumentList));
    argument_list->line_number  = package_unit_get_line_number();
    argument_list->expression   = expression;
    argument_list->next         = nullptr;
    return argument_list;
}

Identifier* new_identifier(IdentifierType type, char* name) {
    debug_log_with_yellow_coloar("identifier name:%s", name);

    Identifier* identifier      = (Identifier*)mem_alloc(get_front_mem_pool(), sizeof(Identifier));
    identifier->line_number     = package_unit_get_line_number();
    identifier->type            = type;
    identifier->identifier_name = name;
    identifier->array_index     = 0;
    identifier->parent_scope    = nullptr;
    identifier->next            = nullptr;

    return identifier;
}

Identifier* identifier_list_add_item(Identifier* identifier_list, Identifier* identifier) {
    Identifier* pos = identifier_list;
    for (; pos->next != nullptr; pos = pos->next)
        ;
    pos->next = identifier;
    return identifier_list;
}

FunctionReturnList* create_function_return_list(VariableType variable_type) {
    FunctionReturnList* return_list = (FunctionReturnList*)mem_alloc(get_front_mem_pool(), sizeof(FunctionReturnList));

    return_list->variable_type      = variable_type;
    return_list->next               = nullptr;

    return return_list;
}

FunctionReturnList* function_return_list_add_item(FunctionReturnList* return_list, VariableType variable_type) {
    FunctionReturnList* pos = return_list;
    for (; pos->next != nullptr; pos = pos->next)
        ;
    pos->next = create_function_return_list(variable_type);
    return return_list;
}

Function* new_function_definition(FunctionType type, Identifier* identifier, Parameter* parameter_list, FunctionReturnList* return_list, Block* block) {
    debug_log_with_yellow_coloar("functionType:%d, identifier:%s", type, identifier->identifier_name);

    Function* function            = (Function*)mem_alloc(get_front_mem_pool(), sizeof(Function));
    function->source_file         = package_unit_get_file_name();
    function->start_line_number   = identifier->line_number;
    function->end_line_number     = package_unit_get_line_number();
    function->package             = get_package_unit()->parent_package;
    function->attribute_info      = nullptr;
    function->func_index          = get_package_unit()->function_list.size();
    function->type                = type;
    function->function_name       = identifier->identifier_name;
    function->parameter_list_size = 0;
    function->parameter_list      = parameter_list;
    function->block               = block;
    function->next                = nullptr;

    // 把函数参数的变量添加到 variable_list 中
    for (Parameter* pos = parameter_list; pos != nullptr; pos = pos->next) {
        function->parameter_list_size++;
    }

    return function;
}

Statement* create_statement_from_if(IfStatement* if_statement) {
    debug_log_with_yellow_coloar("\t");

    Statement* statement      = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->line_number    = package_unit_get_line_number();
    statement->type           = STATEMENT_TYPE_IF;
    statement->u.if_statement = if_statement;
    statement->next           = nullptr;

    return statement;
}

IfStatement* create_if_statement(Expression* expression, Block* if_block, ElseIfStatement* elseif_statement_list, Block* else_block) {
    debug_log_with_yellow_coloar("\t");

    IfStatement* if_statement          = (IfStatement*)mem_alloc(get_front_mem_pool(), sizeof(IfStatement));
    if_statement->line_number          = package_unit_get_line_number();
    if_statement->condition_expression = expression;
    if_statement->if_block             = if_block;
    if_statement->elseif_list          = elseif_statement_list;
    if_statement->else_block           = else_block;

    if (if_block) {
        if_block->type = BLOCK_TYPE_IF;
    }
    if (else_block) {
        else_block->type = BLOCK_TYPE_IF;
    }

    return if_statement;
}

ElseIfStatement* create_elseif_statement(Expression* expression, Block* elseif_block) {
    debug_log_with_yellow_coloar("\t");

    ElseIfStatement* elseif_statement      = (ElseIfStatement*)mem_alloc(get_front_mem_pool(), sizeof(ElseIfStatement));
    elseif_statement->line_number          = package_unit_get_line_number();
    elseif_statement->condition_expression = expression;
    elseif_statement->elseif_block         = elseif_block;
    elseif_statement->next                 = nullptr;

    if (elseif_block) {
        elseif_block->type = BLOCK_TYPE_IF;
    }

    return elseif_statement;
}

ElseIfStatement* elseif_statement_add_item(ElseIfStatement* list, ElseIfStatement* elseif_statement) {
    debug_log_with_yellow_coloar("\t");

    assert(list != nullptr);

    ElseIfStatement* pos;
    for (pos = list; pos->next != nullptr; pos = pos->next) {
    }

    pos->next = elseif_statement;

    return list;
}

Statement* create_statement_from_for(ForStatement* for_statement) {
    debug_log_with_yellow_coloar("\t");

    Statement* statement       = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->line_number     = package_unit_get_line_number();
    statement->type            = STATEMENT_TYPE_FOR;
    statement->u.for_statement = for_statement;
    statement->next            = nullptr;

    return statement;
}

ForStatement* create_for_ternary_statement(Expression* init_expression, Expression* condition_expression, Expression* post_expression, Block* block) {
    debug_log_with_yellow_coloar("\t");

    ForStatement* for_statement                              = (ForStatement*)mem_alloc(get_front_mem_pool(), sizeof(ForStatement));
    for_statement->line_number                               = package_unit_get_line_number();
    for_statement->type                                      = FOR_STATEMENT_TYPE_TERNARY;
    for_statement->u.ternary_statement                       = (ForTernaryStatement*)mem_alloc(get_front_mem_pool(), sizeof(ForTernaryStatement));
    for_statement->u.ternary_statement->init_expression      = init_expression;
    for_statement->u.ternary_statement->condition_expression = condition_expression;
    for_statement->u.ternary_statement->post_expression      = post_expression;
    for_statement->block                                     = block;

    if (block) {
        block->type = BLOCK_TYPE_FOR;
    }

    return for_statement;
}

ForStatement* create_for_range_statement(Expression* left, Expression* operand, Block* block) {
    debug_log_with_yellow_coloar("\t");

    ForStatement* for_statement               = (ForStatement*)mem_alloc(get_front_mem_pool(), sizeof(ForStatement));
    for_statement->line_number                = package_unit_get_line_number();
    for_statement->type                       = FOR_STATEMENT_TYPE_RANGE;
    for_statement->u.range_statement          = (ForRangeStatement*)mem_alloc(get_front_mem_pool(), sizeof(ForRangeStatement));
    for_statement->u.range_statement->left    = left;
    for_statement->u.range_statement->operand = operand;
    for_statement->block                      = block;

    if (block) {
        block->type = BLOCK_TYPE_FOR;
    }

    return for_statement;
}

Statement* create_statement_from_dofor(DoForStatement* dofor_statement) {
    debug_log_with_yellow_coloar("\t");

    Statement* statement         = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->line_number       = package_unit_get_line_number();
    statement->type              = STATEMENT_TYPE_DOFOR;
    statement->u.dofor_statement = dofor_statement;
    statement->next              = nullptr;

    return statement;
}

DoForStatement* create_dofor_statement(Expression* init_expression, Block* block, Expression* condition_expression, Expression* post_expression) {
    debug_log_with_yellow_coloar("\t");

    DoForStatement* dofor_statement       = (DoForStatement*)mem_alloc(get_front_mem_pool(), sizeof(DoForStatement));
    dofor_statement->line_number          = package_unit_get_line_number();
    dofor_statement->init_expression      = init_expression;
    dofor_statement->block                = block;
    dofor_statement->condition_expression = condition_expression;
    dofor_statement->post_expression      = post_expression;

    if (block) {
        block->type = BLOCK_TYPE_DOFOR;
    }

    return dofor_statement;
}

Statement* create_statement_from_break(BreakStatement* break_statement) {
    debug_log_with_yellow_coloar("\t");

    Statement* statement         = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->line_number       = package_unit_get_line_number();
    statement->type              = STATEMENT_TYPE_BREAK;
    statement->u.break_statement = break_statement;
    statement->next              = nullptr;

    return statement;
}

BreakStatement* create_break_statement(char* literal_interface) {
    debug_log_with_yellow_coloar("\t");

    unsigned int break_loop_num = 0;
    if (literal_interface == nullptr || strlen(literal_interface) == 0) {
        break_loop_num = 1;
    } else {
        break_loop_num = atoi(literal_interface);
        // TODO: check break_loop_num valid
    }

    BreakStatement* break_statement = (BreakStatement*)mem_alloc(get_front_mem_pool(), sizeof(BreakStatement));
    break_statement->line_number    = package_unit_get_line_number();
    break_statement->break_loop_num = break_loop_num;

    return break_statement;
}


Statement* create_statement_from_continue(ContinueStatement* continue_statement) {
    debug_log_with_yellow_coloar("\t");

    Statement* statement            = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->line_number          = package_unit_get_line_number();
    statement->type                 = STATEMENT_TYPE_CONTINUE;
    statement->u.continue_statement = continue_statement;
    statement->next                 = nullptr;

    return statement;
}

ContinueStatement* create_continue_statement() {
    ContinueStatement* continue_statement = (ContinueStatement*)mem_alloc(get_front_mem_pool(), sizeof(ContinueStatement));
    continue_statement->line_number       = package_unit_get_line_number();

    return continue_statement;
}

Statement* create_statement_from_return(ReturnStatement* return_statement) {
    debug_log_with_yellow_coloar("\t");

    Statement* statement          = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->line_number        = package_unit_get_line_number();
    statement->type               = STATEMENT_TYPE_RETURN;
    statement->u.return_statement = return_statement;
    statement->next               = nullptr;

    return statement;
}

Statement* create_statement_from_tag_definition(TagDefinitionStatement* tag_def) {
    debug_log_with_yellow_coloar("\t");
    Statement* statement                  = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->line_number                = package_unit_get_line_number();
    statement->type                       = STATEMENT_TYPE_TAG_DEFINITION;
    statement->u.tag_definition_statement = tag_def;
    statement->next                       = nullptr;

    return statement;
}

Statement* create_statement_from_jump_tag(JumpTagStatement* jump_tag_statement) {
    debug_log_with_yellow_coloar("\t");
    Statement* statement            = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->line_number          = package_unit_get_line_number();
    statement->type                 = STATEMENT_TYPE_JUMP_TAG;
    statement->u.jump_tag_statement = jump_tag_statement;
    statement->next                 = nullptr;

    return statement;
}

ReturnStatement* create_return_statement(Expression* expression) {
    debug_log_with_yellow_coloar("expression->type:%d", expression->type);

    ReturnStatement* return_statement  = (ReturnStatement*)mem_alloc(get_front_mem_pool(), sizeof(ReturnStatement));
    return_statement->line_number      = package_unit_get_line_number();
    return_statement->return_list      = expression;
    return_statement->return_list_size = 0;
    for (Expression* pos = expression; pos; pos = pos->next) {
        return_statement->return_list_size++;
    }
    return return_statement;
}

Block* start_new_block() {
    debug_log_with_yellow_coloar("\t");


    Block* block                       = (Block*)mem_alloc(get_front_mem_pool(), sizeof(Block));
    block->line_number                 = package_unit_get_line_number();
    block->type                        = BLOCK_TYPE_UNKNOW;
    block->declaration_list_size       = 0;
    block->declaration_list            = nullptr;
    block->statement_list_size         = 0;
    block->statement_list              = nullptr;
    block->parent_block                = get_package_unit()->current_block;
    block->block_labels.break_label    = 0;
    block->block_labels.continue_label = 0;

    /* printf("[start] parent:%p, current:%p\n", block->parent_block, block); */

    get_package_unit()->current_block  = block;

    return block;
}

Block* finish_block(Block* block, Statement* statement_list) {
    debug_log_with_yellow_coloar("\t");
    assert(block == get_package_unit()->current_block);

    block->statement_list = statement_list;
    for (Statement* pos = statement_list; pos; pos = pos->next) {
        block->statement_list_size++;
    }

    get_package_unit()->current_block = block->parent_block;

    /* printf("[end] current:%p, parent:%p\n", block, block->parent_block); */
    return block;
}


DimensionExpression* create_dimension_expression(char* literal_interface) {
    debug_log_with_yellow_coloar("\tdimension:%s", literal_interface);
    DimensionExpression* dim = (DimensionExpression*)mem_alloc(get_front_mem_pool(), sizeof(DimensionExpression));
    dim->dimension           = 0;
    dim->next                = nullptr;
    if (literal_interface != nullptr) {
        sscanf(literal_interface, "%ud", &(dim->dimension));
    }
    return dim;
}

DimensionExpression* dimension_expression_list_add_item(DimensionExpression* list, DimensionExpression* item) {
    if (list == nullptr) {
        return item;
    }
    DimensionExpression* pos = list;
    for (; pos->next != nullptr; pos = pos->next)
        ;
    pos->next = item;
    return list;
}

TypeSpecifier* create_type_specifier(Ring_BasicType basic_type) {
    debug_log_with_yellow_coloar("basic_type:%d", basic_type);

    TypeSpecifier* type_specifier = (TypeSpecifier*)mem_alloc(get_front_mem_pool(), sizeof(TypeSpecifier));
    type_specifier->kind          = basic_type;
    type_specifier->dimension     = 0;
    type_specifier->next          = nullptr;

    return type_specifier;
}

/*
 * 基础类型数组
 *
 * array-bool
 * array-int
 * array-double
 * array-string
 * 类数组 嵌套数组
 */
TypeSpecifier* create_type_specifier_array(TypeSpecifier* type) {
    TypeSpecifier* type_specifier = (TypeSpecifier*)mem_alloc(get_front_mem_pool(), sizeof(TypeSpecifier));
    type_specifier->kind          = RING_BASIC_TYPE_ARRAY;
    type_specifier->u.array_type  = nullptr;
    type_specifier->dimension     = 1; // 暂时只支持一维数组
    type_specifier->next          = type;

    return type_specifier;
}


TypeSpecifier* create_class_type_specifier(char* identifier) {
    debug_log_with_yellow_coloar("\t");

    TypeSpecifier* type_specifier                  = (TypeSpecifier*)mem_alloc(get_front_mem_pool(), sizeof(TypeSpecifier));
    type_specifier->kind                           = RING_BASIC_TYPE_CLASS;
    type_specifier->u.class_type                   = (Ring_DeriveType_Class*)mem_alloc(get_front_mem_pool(), sizeof(Ring_DeriveType_Class));
    type_specifier->u.class_type->class_identifier = identifier;
    type_specifier->u.class_type->class_definition = nullptr;
    type_specifier->dimension                      = 0;
    type_specifier->next                           = nullptr;

    return type_specifier;
}

Declaration* create_declaration(TypeSpecifier* type, char* identifier, Expression* initializer) {
    debug_log_with_yellow_coloar("identifier:%s", identifier);

    Declaration* declaration    = (Declaration*)mem_alloc(get_front_mem_pool(), sizeof(Declaration));
    declaration->line_number    = package_unit_get_line_number();
    declaration->type           = type;
    declaration->identifier     = identifier;
    declaration->initializer    = initializer;
    declaration->is_const       = 0;
    declaration->is_local       = 0;
    declaration->variable_index = -1; // fix in fix_ast.c::add_declaration
    declaration->next           = nullptr;
    return declaration;
}

Declaration* declaration_list_add_item(Declaration* head, Declaration* declaration) {
    if (head == nullptr) {
        return declaration;
    }

    Declaration* pos = head;
    for (; pos->next != nullptr; pos = pos->next) {
    }
    pos->next = declaration;
    return head;
}

Statement* create_multi_declaration_statement(TypeSpecifier* type_specifier, Identifier* identifier_list, Expression* initializer_list) {
    Declaration* head     = nullptr;
    Identifier*  pos_ider = identifier_list;
    Expression*  pos_init = initializer_list;
    for (pos_ider = identifier_list; pos_ider; pos_ider = pos_ider->next) {
        Declaration* decl = create_declaration(type_specifier, pos_ider->identifier_name, pos_init);
        if (pos_init) {
            decl->initializer       = pos_init;
            pos_init                = pos_init->next;
            decl->initializer->next = nullptr; // 把initializer_list 拆开
        }
        head = declaration_list_add_item(head, decl);
    }


    Statement* statement               = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->line_number             = package_unit_get_line_number();
    statement->type                    = STATEMENT_TYPE_DECLARATION;
    statement->u.declaration_statement = head;
    statement->next                    = nullptr;

    return statement;
}

Statement* create_declaration_statement(TypeSpecifier* type, char* identifier, Expression* initializer) {
    debug_log_with_yellow_coloar("identifier:%s", identifier);

    Statement* statement               = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->line_number             = package_unit_get_line_number();
    statement->type                    = STATEMENT_TYPE_DECLARATION;
    statement->u.declaration_statement = create_declaration(type, identifier, initializer);
    statement->next                    = nullptr;

    return statement;
}

Parameter* create_parameter(TypeSpecifier* type, char* identifier, bool is_variadic) {
    Parameter* parameter   = (Parameter*)mem_alloc(get_front_mem_pool(), sizeof(Parameter));
    parameter->line_number = package_unit_get_line_number();
    parameter->type        = type;
    parameter->is_variadic = is_variadic;
    parameter->identifier  = identifier;
    parameter->next        = nullptr;

    return parameter;
}

Parameter* parameter_list_add_statement(Parameter* head, Parameter* parameter) {
    if (head == nullptr) {
        return parameter;
    }

    Parameter* pos = head;
    for (; pos->next != nullptr; pos = pos->next) {
    }
    pos->next = parameter;
    return head;
}

Package* create_package_info(char* package_name) {
    debug_log_with_yellow_coloar("current package name:%s\n", package_name);
    Package* package      = (Package*)mem_alloc(get_front_mem_pool(), sizeof(Package));
    package->package_name = package_name;

    return package;
}

// TODO:
void import_package_list_add_item(char* package_name, char* rename) {
    debug_log_with_yellow_coloar("import package name:%s, rename:%s\n", package_name, rename);

    // duplicate import package
    for (ImportPackageInfo* import_pack : get_package_unit()->import_package_list) {
        if (strcmp(import_pack->package_name, package_name) == 0) {
            char compile_err_buf[2048];
            char compile_adv_buf[2048];
            snprintf(compile_err_buf, sizeof(compile_err_buf),
                     "duplicate import package `%s`; E:%d.",
                     import_pack->package_name,
                     ERROR_DUPLICATE_IMPORT_PACKAGE);
            snprintf(compile_adv_buf, sizeof(compile_adv_buf),
                     "the first import package `%s` in %s:%d:%d.",
                     import_pack->package_name,
                     get_package_unit()->current_file_name.c_str(),
                     import_pack->line_number, 0);

            ErrorReportContext context = {
                .package          = nullptr,
                .package_unit     = get_package_unit(),
                .source_file_name = get_package_unit()->current_file_name,
                .line_content     = package_unit_get_line_content(import_pack->line_number),
                .line_number      = package_unit_get_line_number(),
                .column_number    = package_unit_get_column_number(),
                .error_message    = std::string(compile_err_buf),
                .advice           = std::string(compile_adv_buf),
                .report_type      = ERROR_REPORT_TYPE_COLL_ERR,
            };
            ring_compile_error_report(&context);
        }
    }

    ImportPackageInfo* import_package_info = (ImportPackageInfo*)mem_alloc(get_front_mem_pool(), sizeof(ImportPackageInfo));
    import_package_info->line_number       = package_unit_get_line_number();
    import_package_info->package_name      = package_name;
    import_package_info->package_path      = nullptr;
    import_package_info->rename            = rename;

    get_package_unit()->import_package_list.push_back(import_package_info);
}


// -------------
// class define
// -------------

ClassDefinition* start_class_definition(char* class_identifier) {
    debug_log_with_yellow_coloar("\t");

    ClassDefinition* class_def  = (ClassDefinition*)mem_alloc(get_front_mem_pool(), sizeof(ClassDefinition));
    class_def->line_number      = package_unit_get_line_number();
    class_def->class_identifier = class_identifier;
    class_def->member           = nullptr;
    class_def->next             = nullptr;


    package_unit_add_class_definition(class_def);

    return class_def;
}

ClassDefinition* finish_class_definition(ClassDefinition* class_def, ClassMemberDeclaration* class_member_declar) {
    debug_log_with_yellow_coloar("\t");

    assert(class_def != nullptr);

    class_def->member = class_member_declar;

    return class_def;
}

ClassMemberDeclaration* class_member_declaration_list_add_item(ClassMemberDeclaration* list, ClassMemberDeclaration* decl) {
    assert(decl != nullptr);

    if (list == nullptr) {
        return decl;
    }

    ClassMemberDeclaration* pos = list;
    for (; pos->next != nullptr; pos = pos->next) {
    }

    pos->next = decl;

    return list;
}

ClassMemberDeclaration* create_class_member_field_declaration(Attribute attribute, FieldMember* field_member) {
    assert(field_member != nullptr);

    ClassMemberDeclaration* class_member_declar = (ClassMemberDeclaration*)mem_alloc(get_front_mem_pool(), sizeof(ClassMemberDeclaration));
    class_member_declar->line_number            = package_unit_get_line_number();
    class_member_declar->attribute              = attribute;
    class_member_declar->type                   = MEMBER_FIELD;
    class_member_declar->u.field                = field_member;
    class_member_declar->next                   = nullptr;

    return class_member_declar;
}

ClassMemberDeclaration* create_class_member_method_declaration(Attribute attribute, MethodMember* method_member) {
    assert(method_member != nullptr);

    ClassMemberDeclaration* class_member_declar = (ClassMemberDeclaration*)mem_alloc(get_front_mem_pool(), sizeof(ClassMemberDeclaration));
    class_member_declar->line_number            = package_unit_get_line_number();
    class_member_declar->attribute              = attribute;
    class_member_declar->type                   = MEMBER_METHOD;
    class_member_declar->u.method               = method_member;
    class_member_declar->next                   = nullptr;

    return class_member_declar;
}

FieldMember* create_class_member_field(TypeSpecifier* type_specifier, Identifier* identifier_list) {
    debug_log_with_yellow_coloar("\t");

    FieldMember* field_member    = (FieldMember*)mem_alloc(get_front_mem_pool(), sizeof(FieldMember));
    field_member->line_number    = package_unit_get_line_number();
    field_member->type           = type_specifier;
    field_member->identifier     = identifier_list->identifier_name;
    field_member->index_of_class = 0;

    return field_member;
}

MethodMember* create_class_member_method(FunctionType type, Identifier* identifier, Parameter* parameter_list, FunctionReturnList* return_list, Block* block) {
    debug_log_with_yellow_coloar("\t");

    MethodMember* method_member        = (MethodMember*)mem_alloc(get_front_mem_pool(), sizeof(MethodMember));

    method_member->source_file         = package_unit_get_file_name();
    method_member->start_line_number   = identifier->line_number;
    method_member->end_line_number     = package_unit_get_line_number();

    method_member->package             = get_package_unit()->parent_package;

    method_member->attribute_info      = nullptr;

    method_member->index_of_class      = -1;

    method_member->identifier          = identifier->identifier_name;

    method_member->parameter_list_size = 0;
    method_member->parameter_list      = parameter_list;

    method_member->return_list_size    = 0;
    method_member->return_list         = return_list;

    method_member->block               = block;

    for (Parameter* pos = parameter_list; pos != nullptr; pos = pos->next) {
        method_member->parameter_list_size++;
    }
    for (FunctionReturnList* pos = return_list; pos != nullptr; pos = pos->next) {
        method_member->return_list_size++;
    }

    return method_member;
}


AttributeInfo* create_attribute_info(char* name) {
    AttributeInfo* info = (AttributeInfo*)mem_alloc(get_front_mem_pool(), sizeof(AttributeInfo));
    info->name          = name;
    info->next          = nullptr;
    return info;
}

AttributeInfo* attribute_info_add_item(AttributeInfo* list, AttributeInfo* item) {
    if (list == nullptr) {
        return item;
    } else {
        AttributeInfo* pos = list;
        for (; pos->next != nullptr; pos = pos->next) {
        }
        pos->next = item;
        return list;
    }
}

TagDefinitionStatement* create_tag_definition_statement(char* identifier) {
    TagDefinitionStatement* tag_def = (TagDefinitionStatement*)mem_alloc(get_front_mem_pool(), sizeof(TagDefinitionStatement));
    tag_def->line_number            = package_unit_get_line_number();
    tag_def->identifier             = identifier;

    return tag_def;
}

JumpTagStatement* create_jump_tag_statement(char* identifier) {
    JumpTagStatement* jump_tag = (JumpTagStatement*)mem_alloc(get_front_mem_pool(), sizeof(JumpTagStatement));
    jump_tag->line_number      = package_unit_get_line_number();
    jump_tag->identifier       = identifier;

    return jump_tag;
}

Attribute add_attribute(Attribute attribute, AttributeType type) {
    return attribute | type;
}

int attribute_is_public(Attribute attribute) {
    return (attribute >> 0) & (0x01);
}

int attribute_is_private(Attribute attribute) {
    return (attribute >> 1) & (0x01);
}

int attribute_is_constructor(Attribute attribute) {
    return (attribute >> 4) & (0x01);
}

int attribute_is_destructor(Attribute attribute) {
    return (attribute >> 5) & (0x01);
}
// -------------
// class define
// -------------
