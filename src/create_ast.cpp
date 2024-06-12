#include "ring.hpp"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>


// finish a block compile
void finish_global_block(Statement* global_statement_list) {
    debug_ast_info_with_yellow("");

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
            ring_error_report("error statement->type:%d in global statement list\n", statement->type);
            break;
        }
    }
}

Statement* statement_list_add_item(Statement* statement_list, Statement* statement) {
    debug_ast_info_with_yellow("statement->type:%d", statement->type);

    Statement* pos = statement_list;
    for (; pos->next != nullptr; pos = pos->next)
        ;
    pos->next = statement;
    return statement_list;
}

Statement* create_statemen_from_expression(Expression* expression) {
    debug_ast_info_with_yellow("expression->type:%d", expression->type);

    Statement* statement    = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->type         = STATEMENT_TYPE_EXPRESSION;
    statement->line_number  = package_unit_get_line_number();
    statement->u.expression = expression;
    statement->next         = nullptr;
    return statement;
}

void add_function_definition(AttributeInfo* attribute_info, Function* function_definition) {
    assert(function_definition != nullptr);
    debug_ast_info_with_yellow("function_definition->type:%d", function_definition->type);

    for (AttributeInfo* pos = attribute_info; pos; pos = pos->next) {
        if (str_eq(pos->name, "native")) {
            function_definition->type = FUNCTION_TYPE_NATIVE;
        }
    }

    get_package_unit()->function_list.push_back(function_definition);
}

Expression* expression_add_package_posit(Expression* expression, char* package_posit) {
    assert(expression != nullptr);

    // 将 package_posit 注入到最底层的 Expression
    switch (expression->type) {
    case EXPRESSION_TYPE_IDENTIFIER:
        expression->u.identifier_expression->package_posit = package_posit;
        break;
    case EXPRESSION_TYPE_FUNCTION_CALL:
        expression->u.function_call_expression->package_posit = package_posit;
        break;
    default:
        break;
    }

    return expression;
}

Expression* create_expression_identifier(char* identifier) {
    debug_ast_info_with_yellow("identifier:%s", identifier);

    IdentifierExpression* identifier_expression = (IdentifierExpression*)mem_alloc(get_front_mem_pool(), sizeof(IdentifierExpression));
    identifier_expression->line_number          = package_unit_get_line_number();
    identifier_expression->package_posit        = nullptr;
    identifier_expression->type                 = IDENTIFIER_EXPRESSION_TYPE_VARIABLE;
    identifier_expression->identifier           = identifier;
    identifier_expression->u.declaration        = nullptr;

    Expression* expression                      = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                     = package_unit_get_line_number();
    expression->convert_type                    = nullptr; // UPDATED_BY_FIX_AST
    expression->type                            = EXPRESSION_TYPE_IDENTIFIER;
    expression->u.identifier_expression         = identifier_expression;
    expression->next                            = nullptr;

    return expression;
}

Expression* create_expression_identifier_with_index(Expression*          array_expression,
                                                    DimensionExpression* index) {

    debug_ast_info_with_yellow("\t");

    ArrayIndexExpression* array_index_expression = (ArrayIndexExpression*)mem_alloc(get_front_mem_pool(), sizeof(ArrayIndexExpression));
    array_index_expression->line_number          = package_unit_get_line_number();
    array_index_expression->array_expression     = array_expression;
    array_index_expression->index_expression     = index;

    Expression* expression                       = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                      = package_unit_get_line_number();
    expression->convert_type                     = nullptr; // UPDATED_BY_FIX_AST
    expression->type                             = EXPRESSION_TYPE_ARRAY_INDEX;
    expression->u.array_index_expression         = array_index_expression;

    return expression;
}

Expression* create_member_expression(Expression* object_expression, char* member_identifier) {

    MemberExpression* member_expression  = (MemberExpression*)mem_alloc(get_front_mem_pool(), sizeof(MemberExpression));
    member_expression->line_number       = package_unit_get_line_number();
    member_expression->object_expression = object_expression;
    member_expression->member_identifier = member_identifier;
    member_expression->field_member      = nullptr;

    Expression* expression               = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number              = package_unit_get_line_number();
    expression->convert_type             = nullptr; // UPDATED_BY_FIX_AST
    expression->type                     = EXPRESSION_TYPE_MEMBER;
    expression->u.member_expression      = member_expression;

    return expression;
}

Expression* create_expression_from_function_call(FunctionCallExpression* function_call_expression) {
    debug_ast_info_with_yellow("function_call_expression->name:");

    Expression* expression                 = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                = package_unit_get_line_number();
    expression->convert_type               = nullptr; // UPDATED_BY_FIX_AST
    expression->type                       = EXPRESSION_TYPE_FUNCTION_CALL;
    expression->u.function_call_expression = function_call_expression;
    return expression;
}

Expression* create_expression_from_method_call(MethodCallExpression* method_call_expression) {
    debug_ast_info_with_yellow("method_call_expression->name:");

    Expression* expression               = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number              = package_unit_get_line_number();
    expression->convert_type             = nullptr; // UPDATED_BY_FIX_AST
    expression->type                     = EXPRESSION_TYPE_METHOD_CALL;
    expression->u.method_call_expression = method_call_expression;
    return expression;
}

Expression* create_expression_from_array_literal(ArrayLiteralExpression* array_literal) {
    debug_ast_info_with_yellow("\t");

    Expression* expression                 = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                = package_unit_get_line_number();
    expression->convert_type               = nullptr; // UPDATED_BY_FIX_AST
    expression->type                       = EXPRESSION_TYPE_ARRAY_LITERAL;
    expression->u.array_literal_expression = array_literal;
    return expression;
}

Expression* create_expression_from_class_object_literal(ClassObjectLiteralExpression* object_literal) {
    debug_ast_info_with_yellow("\t");

    Expression* expression                        = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                       = package_unit_get_line_number();
    expression->convert_type                      = nullptr; // UPDATED_BY_FIX_AST
    expression->type                              = EXPRESSION_TYPE_CLASS_OBJECT_LITERAL;
    expression->u.class_object_literal_expression = object_literal;
    return expression;
}

Expression* create_expression_assign(AssignExpression* assign_expression) {
    // debug_ast_info_with_yellow("assign_expression->assign_identifier:%s", assign_expression->assign_identifier);

    Expression* expression          = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number         = package_unit_get_line_number();
    expression->convert_type        = nullptr; // UPDATED_BY_FIX_AST
    expression->type                = EXPRESSION_TYPE_ASSIGN;
    expression->u.assign_expression = assign_expression;
    return expression;
}

Expression* create_expression_ternary(Expression* condition,
                                      Expression* true_expression,
                                      Expression* false_expression) {

    Expression* expression                                 = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                                = package_unit_get_line_number();
    expression->convert_type                               = nullptr; // UPDATED_BY_FIX_AST
    expression->type                                       = EXPRESSION_TYPE_TERNARY;
    expression->u.ternary_expression                       = (TernaryExpression*)mem_alloc(get_front_mem_pool(), sizeof(TernaryExpression));
    expression->u.ternary_expression->line_number          = package_unit_get_line_number();
    expression->u.ternary_expression->condition_expression = condition;
    expression->u.ternary_expression->true_expression      = true_expression;
    expression->u.ternary_expression->false_expression     = false_expression;
    return expression;
}

Expression* create_expression_binary(ExpressionType type, Expression* left, Expression* right) {
    debug_ast_info_with_yellow("type:%d", type);

    Expression* expression                            = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                           = package_unit_get_line_number();
    expression->convert_type                          = nullptr; // UPDATED_BY_FIX_AST
    expression->type                                  = type;
    expression->u.binary_expression                   = (BinaryExpression*)mem_alloc(get_front_mem_pool(), sizeof(BinaryExpression));
    expression->u.binary_expression->line_number      = package_unit_get_line_number();
    expression->u.binary_expression->left_expression  = left;
    expression->u.binary_expression->right_expression = right;

    return expression;
}

Expression* create_expression_unitary(ExpressionType type, Expression* unitary_expression) {
    debug_ast_info_with_yellow("type:%d", type);

    Expression* expression           = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number          = package_unit_get_line_number();
    expression->convert_type         = nullptr; // UPDATED_BY_FIX_AST
    expression->type                 = type;
    expression->u.unitary_expression = unitary_expression;
    expression->next                 = nullptr;

    return expression;
}


Expression* create_expression_literal(ExpressionType type, char* literal_interface) {
    debug_ast_info_with_yellow("type:%d", type);

    assert(literal_interface != nullptr);
    Expression* expression   = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number  = package_unit_get_line_number();
    expression->convert_type = nullptr; // UPDATED_BY_FIX_AST

    expression->type         = type;
    switch (type) {
    case EXPRESSION_TYPE_LITERAL_INT: {
        unsigned long long int64_value = 0;
        sscanf(literal_interface, "%llu", &int64_value);
        /*
         * 在这里解析到的 int 常量都是正数
         */

        if (int64_value <= INT32_MAX) {
            expression->type          = EXPRESSION_TYPE_LITERAL_INT;
            expression->u.int_literal = (unsigned int)int64_value;
        } else if (int64_value <= INT64_MAX) {
            expression->type            = EXPRESSION_TYPE_LITERAL_INT64;
            expression->u.int64_literal = (unsigned long long)int64_value;
        } else {
            // FIXME:
            // ring error report 数据类型溢出
            // 这里还有一个棘手的问题需要处理一下
            // 2147483648 会溢出 但是 -2147483648 不会溢出, 所以针对 负号 还要做更加细致的语义检查
            // 9223372036854775808 同理
            // 更合理的方式应该是在常量折叠之后 再 进行判断


            // Ring-Compiler-Error-Report  ERROR_OVERFLOWS
            DEFINE_ERROR_REPORT_STR;

            snprintf(compile_err_buf, sizeof(compile_err_buf),
                     "can't use num literal `%s` in expression, raise overflows; E:%d.",
                     literal_interface,
                     ERROR_OVERFLOWS);


            ErrorReportContext context = {
                .package                 = nullptr,
                .package_unit            = get_package_unit(),
                .source_file_name        = get_package_unit()->current_file_name,
                .line_content            = package_unit_get_line_content(expression->line_number),
                .line_number             = expression->line_number,
                .column_number           = package_unit_get_column_number(),
                .error_message           = std::string(compile_err_buf),
                .advice                  = std::string(compile_adv_buf),
                .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
                .ring_compiler_file      = (char*)__FILE__,
                .ring_compiler_file_line = __LINE__,
            };
            ring_compile_error_report(&context);
        }

    } break;
    case EXPRESSION_TYPE_LITERAL_INT64: {
        unsigned int literal_length = strlen(literal_interface);
        if (literal_interface[literal_length - 1] != 'L') {
            // error report  invalid int64 literal
        }
        literal_interface[literal_length - 1] = '\0';

        unsigned long long int64_value        = 0;
        sscanf(literal_interface, "%llu", &int64_value);

        expression->type            = EXPRESSION_TYPE_LITERAL_INT64;
        expression->u.int64_literal = int64_value;

    } break;
    case EXPRESSION_TYPE_LITERAL_DOUBLE:
        sscanf(literal_interface, "%lf", &expression->u.double_literal);
        break;
    case EXPRESSION_TYPE_LITERAL_STRING:
        expression->u.string_literal = literal_interface;
        break;
    default:
        break;
    }

    return expression;
}

Expression* create_expression_bool_literal(ExpressionType type, Ring_Bool value) {
    debug_ast_info_with_yellow("type:%d, boolean:%d", type, value);

    Expression* expression     = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number    = package_unit_get_line_number();
    expression->convert_type   = nullptr; // UPDATED_BY_FIX_AST
    expression->type           = type;
    expression->u.bool_literal = value;

    return expression;
}

Expression* create_cast_expression(TypeSpecifier* cast_type, Expression* operand) {
    Expression* expression                        = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                       = package_unit_get_line_number();
    expression->convert_type                      = nullptr; // UPDATED_BY_FIX_AST
    expression->type                              = EXPRESSION_TYPE_CAST;
    expression->u.cast_expression                 = (CastExpression*)mem_alloc(get_front_mem_pool(), sizeof(CastExpression));
    expression->u.cast_expression->line_number    = package_unit_get_line_number();
    expression->u.cast_expression->type_specifier = cast_type;
    expression->u.cast_expression->operand        = operand;

    return expression;
}


/*
 * new 关键字  创建数组
 *
 * 在这里, type_specifier 是没有嵌套的
 * 也就是说 type_specifier 是 booll int double string class
 *
 */
Expression* create_new_array_expression(TypeSpecifier*       sub_type,
                                        DimensionExpression* dimension_expression) {

    TypeSpecifier* type_specifier                            = create_type_specifier_array(sub_type, dimension_expression);

    Expression*    expression                                = (Expression*)mem_alloc(get_front_mem_pool(), sizeof(Expression));
    expression->line_number                                  = package_unit_get_line_number();
    expression->convert_type                                 = nullptr; // UPDATED_BY_FIX_AST
    expression->type                                         = EXPRESSION_TYPE_NEW_ARRAY;
    expression->u.new_array_expression                       = (NewArrayExpression*)mem_alloc(get_front_mem_pool(), sizeof(NewArrayExpression));
    expression->u.new_array_expression->line_number          = package_unit_get_line_number();
    expression->u.new_array_expression->type_specifier       = type_specifier;
    expression->u.new_array_expression->dimension_expression = dimension_expression;

    return expression;
}

FieldInitExpression* create_field_init_expression(char*       field_identifier,
                                                  Expression* init_expression) {

    FieldInitExpression* expression = (FieldInitExpression*)mem_alloc(get_front_mem_pool(), sizeof(FieldInitExpression));
    expression->line_number         = package_unit_get_line_number();
    expression->field_identifier    = field_identifier;
    expression->field_member        = nullptr; // UPDATED_BY_FIX_AST
    expression->init_expression     = init_expression;
    expression->next                = nullptr;
    return expression;
}

FieldInitExpression* field_init_list_add_item(FieldInitExpression* list,
                                              FieldInitExpression* item) {

    FieldInitExpression* pos = list;
    for (; pos->next != nullptr; pos = pos->next)
        ;
    pos->next = item;
    return list;
}

AssignExpression* create_assign_expression(AssignExpressionType type,
                                           Expression*          left,
                                           Expression*          operand) {

    AssignExpression* assing_expression = (AssignExpression*)mem_alloc(get_front_mem_pool(), sizeof(AssignExpression));

    assing_expression->line_number      = package_unit_get_line_number();
    assing_expression->type             = type;
    assing_expression->left             = left;
    assing_expression->operand          = operand;
    return assing_expression;
}

AssignExpression* create_multi_assign_expression(Expression* first_left_value_exp,
                                                 Expression* left_value_exp_list,
                                                 Expression* operand) {

    debug_ast_info_with_yellow("");

    Expression*       left              = expression_list_add_item(first_left_value_exp, left_value_exp_list);

    AssignExpression* assing_expression = (AssignExpression*)mem_alloc(get_front_mem_pool(), sizeof(AssignExpression));

    assing_expression->line_number      = package_unit_get_line_number();
    assing_expression->type             = ASSIGN_EXPRESSION_TYPE_MULTI_ASSIGN;
    assing_expression->left             = left;
    assing_expression->operand          = operand;
    return assing_expression;
}

FunctionCallExpression* create_function_call_expression(char*         func_identifier,
                                                        ArgumentList* argument_list) {

    FunctionCallExpression* function_call_expression = (FunctionCallExpression*)mem_alloc(get_front_mem_pool(), sizeof(FunctionCallExpression));
    function_call_expression->line_number            = package_unit_get_line_number();
    function_call_expression->package_posit          = nullptr;
    function_call_expression->func_identifier        = func_identifier;
    function_call_expression->argument_list_size     = 0;
    function_call_expression->argument_list          = argument_list;

    for (ArgumentList* pos = argument_list; pos != nullptr; pos = pos->next) {
        function_call_expression->argument_list_size++;
    }

    return function_call_expression;
}

MethodCallExpression* create_method_call_expression(Expression*   object_expression,
                                                    char*         member_identifier,
                                                    ArgumentList* argument_list) {

    MethodCallExpression* method_call_expression = (MethodCallExpression*)mem_alloc(get_front_mem_pool(), sizeof(MethodCallExpression));
    method_call_expression->line_number          = package_unit_get_line_number();
    method_call_expression->object_expression    = object_expression;
    method_call_expression->member_identifier    = member_identifier;
    method_call_expression->argument_list        = argument_list;
    return method_call_expression;
}

ArrayLiteralExpression* create_array_literal_expression(TypeSpecifier*       sub_type,
                                                        DimensionExpression* dimension_expression,
                                                        Expression*          expression_list) {
    TypeSpecifier*          type_specifier = create_type_specifier_array(sub_type, dimension_expression);

    ArrayLiteralExpression* array_literal  = (ArrayLiteralExpression*)mem_alloc(get_front_mem_pool(), sizeof(ArrayLiteralExpression));
    array_literal->line_number             = package_unit_get_line_number();
    array_literal->type_specifier          = type_specifier;
    array_literal->dimension_expression    = dimension_expression;
    array_literal->expression_list         = expression_list;
    return array_literal;
}

ClassObjectLiteralExpression* create_class_object_literal_expression(TypeSpecifier*       type_specifier,
                                                                     FieldInitExpression* field_init_expression_list) {

    ClassObjectLiteralExpression* object_literal = (ClassObjectLiteralExpression*)mem_alloc(get_front_mem_pool(), sizeof(ClassObjectLiteralExpression));
    object_literal->line_number                  = package_unit_get_line_number();
    object_literal->type_specifier               = type_specifier;
    object_literal->field_init_expression_list   = field_init_expression_list;
    return object_literal;
}

Expression* expression_list_add_item(Expression* expression_list, Expression* expression) {
    debug_ast_info_with_yellow("");

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
    debug_ast_info_with_yellow("expression->type:%d", expression->type);

    ArgumentList* argument_list = (ArgumentList*)mem_alloc(get_front_mem_pool(), sizeof(ArgumentList));
    argument_list->line_number  = package_unit_get_line_number();
    argument_list->expression   = expression;
    argument_list->next         = nullptr;
    return argument_list;
}

Identifier* create_identifier(IdentifierType type, char* name) {
    debug_ast_info_with_yellow("identifier name:%s", name);

    Identifier* identifier   = (Identifier*)mem_alloc(get_front_mem_pool(), sizeof(Identifier));
    identifier->line_number  = package_unit_get_line_number();
    identifier->type         = type; // UPDATED_BY_FIX_AST
    identifier->name         = name;
    identifier->array_index  = 0;
    identifier->parent_scope = nullptr;
    identifier->next         = nullptr;

    return identifier;
}

Identifier* identifier_list_add_item(Identifier* identifier_list, Identifier* identifier) {
    Identifier* pos = identifier_list;
    for (; pos->next != nullptr; pos = pos->next)
        ;
    pos->next = identifier;
    return identifier_list;
}

FunctionReturnList* create_function_return_list(TypeSpecifier* type_specifier) {
    FunctionReturnList* return_list = (FunctionReturnList*)mem_alloc(get_front_mem_pool(), sizeof(FunctionReturnList));
    return_list->line_number        = package_unit_get_line_number();
    return_list->type_specifier     = type_specifier;
    return_list->next               = nullptr;

    return return_list;
}

FunctionReturnList* function_return_list_add_item(FunctionReturnList* return_list,
                                                  TypeSpecifier*      type_specifier) {

    FunctionReturnList* pos = return_list;
    for (; pos->next != nullptr; pos = pos->next)
        ;
    pos->next = create_function_return_list(type_specifier);
    return return_list;
}

Function* create_function_definition(FunctionType        type,
                                     Identifier*         identifier,
                                     Parameter*          parameter_list,
                                     FunctionReturnList* return_list,
                                     Block*              block) {

    debug_ast_info_with_yellow("functionType:%d, identifier:%s", type, identifier->name);

    unsigned parameter_list_size = 0;
    for (Parameter* pos = parameter_list; pos != nullptr; pos = pos->next) {
        parameter_list_size++;
    }

    unsigned int parameter_index = 0;
    for (Parameter* pos = parameter_list; pos != nullptr; pos = pos->next) {

        // 可变参数只能在函数定义中作为 最后一个参数
        // Ring-Compiler-Error-Report  ERROR_FUNCTION_INVALID_VARIADIC_PARAMETER
        if (pos->is_variadic && parameter_index != parameter_list_size - 1) {
            DEFINE_ERROR_REPORT_STR;

            snprintf(compile_err_buf, sizeof(compile_err_buf),
                     "can only use ... with final parameter in function %s; E:%d.",
                     identifier->name,
                     ERROR_FUNCTION_INVALID_VARIADIC_PARAMETER);

            ErrorReportContext context = {
                .package                 = nullptr,
                .package_unit            = get_package_unit(),
                .source_file_name        = get_package_unit()->current_file_name,
                .line_content            = package_unit_get_line_content(identifier->line_number),
                .line_number             = identifier->line_number,
                .column_number           = package_unit_get_column_number(),
                .error_message           = std::string(compile_err_buf),
                .advice                  = std::string(compile_adv_buf),
                .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
                .ring_compiler_file      = (char*)__FILE__,
                .ring_compiler_file_line = __LINE__,
            };
            ring_compile_error_report(&context);
        }
        parameter_index++;
    }

    unsigned int return_list_size = 0;
    for (FunctionReturnList* pos = return_list; pos != nullptr; pos = pos->next) {
        return_list_size++;
    }

    Function* function            = (Function*)mem_alloc(get_front_mem_pool(), sizeof(Function));
    function->source_file         = package_unit_get_file_name();
    function->start_line_number   = identifier->line_number;
    function->end_line_number     = package_unit_get_line_number();
    function->package             = get_package_unit()->parent_package;
    function->ring_file_stat      = get_package_unit()->ring_file_stat;

    function->identifier          = identifier->name;

    function->parameter_list_size = parameter_list_size;
    function->parameter_list      = parameter_list;

    function->return_list_size    = return_list_size;
    function->return_list         = return_list;

    function->block               = block;

    function->next                = nullptr;

    function->func_index          = get_package_unit()->function_list.size();
    function->type                = type;


    return function;
}

Statement* create_statement_from_if(IfStatement* if_statement) {
    debug_ast_info_with_yellow("\t");

    Statement* statement      = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->line_number    = package_unit_get_line_number();
    statement->type           = STATEMENT_TYPE_IF;
    statement->u.if_statement = if_statement;
    statement->next           = nullptr;

    return statement;
}

IfStatement* create_if_statement(Expression*      expression,
                                 Block*           if_block,
                                 ElseIfStatement* elseif_statement_list,
                                 Block*           else_block) {

    debug_ast_info_with_yellow("\t");

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
    debug_ast_info_with_yellow("\t");

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

ElseIfStatement* elseif_statement_add_item(ElseIfStatement* list,
                                           ElseIfStatement* elseif_statement) {

    debug_ast_info_with_yellow("\t");

    assert(list != nullptr);

    ElseIfStatement* pos;
    for (pos = list; pos->next != nullptr; pos = pos->next) {
    }

    pos->next = elseif_statement;

    return list;
}

Statement* create_statement_from_for(ForStatement* for_statement) {
    debug_ast_info_with_yellow("\t");

    Statement* statement       = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->line_number     = package_unit_get_line_number();
    statement->type            = STATEMENT_TYPE_FOR;
    statement->u.for_statement = for_statement;
    statement->next            = nullptr;

    return statement;
}

ForStatement* create_for_ternary_statement(Expression* init_expression,
                                           Expression* condition_expression,
                                           Expression* post_expression,
                                           Block*      block) {

    debug_ast_info_with_yellow("\t");

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

ForStatement* create_for_range_statement(Expression* left,
                                         Expression* operand,
                                         Block*      block) {

    debug_ast_info_with_yellow("\t");

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
    debug_ast_info_with_yellow("\t");

    Statement* statement         = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->line_number       = package_unit_get_line_number();
    statement->type              = STATEMENT_TYPE_DOFOR;
    statement->u.dofor_statement = dofor_statement;
    statement->next              = nullptr;

    return statement;
}

DoForStatement* create_dofor_statement(Expression* init_expression,
                                       Block*      block,
                                       Expression* condition_expression,
                                       Expression* post_expression) {

    debug_ast_info_with_yellow("\t");

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
    debug_ast_info_with_yellow("\t");

    Statement* statement         = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->line_number       = package_unit_get_line_number();
    statement->type              = STATEMENT_TYPE_BREAK;
    statement->u.break_statement = break_statement;
    statement->next              = nullptr;

    return statement;
}

BreakStatement* create_break_statement(char* literal_interface) {
    debug_ast_info_with_yellow("\t");

    unsigned int break_loop_num = 0;
    if (literal_interface == nullptr || strlen(literal_interface) == 0) {
        break_loop_num = 1;
    } else {
        break_loop_num = atoi(literal_interface);
    }

    BreakStatement* break_statement = (BreakStatement*)mem_alloc(get_front_mem_pool(), sizeof(BreakStatement));
    break_statement->line_number    = package_unit_get_line_number();
    break_statement->break_loop_num = break_loop_num;

    return break_statement;
}


Statement* create_statement_from_continue(ContinueStatement* continue_statement) {
    debug_ast_info_with_yellow("\t");

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
    debug_ast_info_with_yellow("\t");

    Statement* statement          = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->line_number        = package_unit_get_line_number();
    statement->type               = STATEMENT_TYPE_RETURN;
    statement->u.return_statement = return_statement;
    statement->next               = nullptr;

    return statement;
}

Statement* create_statement_from_tag_definition(TagDefinitionStatement* tag_def) {
    debug_ast_info_with_yellow("\t");
    Statement* statement                  = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->line_number                = package_unit_get_line_number();
    statement->type                       = STATEMENT_TYPE_TAG_DEFINITION;
    statement->u.tag_definition_statement = tag_def;
    statement->next                       = nullptr;

    return statement;
}

Statement* create_statement_from_jump_tag(JumpTagStatement* jump_tag_statement) {
    debug_ast_info_with_yellow("\t");
    Statement* statement            = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->line_number          = package_unit_get_line_number();
    statement->type                 = STATEMENT_TYPE_JUMP_TAG;
    statement->u.jump_tag_statement = jump_tag_statement;
    statement->next                 = nullptr;

    return statement;
}

ReturnStatement* create_return_statement(Expression* expression) {
    debug_ast_info_with_yellow("expression->type:%d", expression->type);

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
    debug_ast_info_with_yellow("\t");


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

    get_package_unit()->current_block  = block;

    return block;
}

Block* finish_block(Block* block, Statement* statement_list) {
    debug_ast_info_with_yellow("\t");
    assert(block == get_package_unit()->current_block);

    block->statement_list = statement_list;
    for (Statement* pos = statement_list; pos; pos = pos->next) {
        block->statement_list_size++;
    }

    get_package_unit()->current_block = block->parent_block;

    return block;
}

DimensionExpression* create_dimension_expression(SubDimensionExpression* dimension_list) {
    DimensionExpression* dim = (DimensionExpression*)mem_alloc(get_front_mem_pool(), sizeof(DimensionExpression));
    dim->line_number         = package_unit_get_line_number();
    dim->dimension           = dimension_list->index; // head 的 index 就是size
    dim->dimension_list      = dimension_list;

    return dim;
}

DimensionExpression* create_dimension_expression_with_exclam(char* dimension_literal) {
    DimensionExpression* dim = (DimensionExpression*)mem_alloc(get_front_mem_pool(), sizeof(DimensionExpression));
    dim->line_number         = package_unit_get_line_number();
    dim->dimension           = atoi(dimension_literal);
    dim->dimension_list      = nullptr;

    return dim;
}

SubDimensionExpression* create_sub_dimension_expression(Expression* num_expression) {
    SubDimensionExpression* dim = (SubDimensionExpression*)mem_alloc(get_front_mem_pool(), sizeof(SubDimensionExpression));
    dim->line_number            = package_unit_get_line_number();
    dim->index                  = 1;
    dim->num_expression         = num_expression;
    dim->next                   = nullptr;
    return dim;
}

SubDimensionExpression* sub_dimension_expression_list_add_item(SubDimensionExpression* list,
                                                               SubDimensionExpression* item) {

    if (list == nullptr) {
        return item;
    }
    SubDimensionExpression* pos = list;
    for (; pos->next != nullptr; pos = pos->next) {
        pos->index++;
    }
    pos->index++;
    pos->next = item;
    return list;
}

TypeSpecifier* create_type_specifier(Ring_BasicType basic_type) {
    debug_ast_info_with_yellow("basic_type:%d", basic_type);

    TypeSpecifier* type_specifier = (TypeSpecifier*)mem_alloc(get_front_mem_pool(), sizeof(TypeSpecifier));
    type_specifier->line_number   = package_unit_get_line_number();
    type_specifier->kind          = basic_type;
    type_specifier->dimension     = 0;
    type_specifier->sub           = nullptr;

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
TypeSpecifier* create_type_specifier_array(TypeSpecifier*       sub_type,
                                           DimensionExpression* dimension_expression) {

    TypeSpecifier* type_specifier = (TypeSpecifier*)mem_alloc(get_front_mem_pool(), sizeof(TypeSpecifier));
    type_specifier->line_number   = package_unit_get_line_number();
    type_specifier->kind          = RING_BASIC_TYPE_ARRAY;
    type_specifier->u.array_type  = nullptr;
    type_specifier->dimension     = dimension_expression->dimension;
    type_specifier->sub           = sub_type;

    // Ring-Compiler-Error-Report  ERROR_ARRAY_DIMENSION_INVALID
    if (type_specifier->dimension > MAX_DIMENSION_NUM) {
        DEFINE_ERROR_REPORT_STR;

        snprintf(compile_err_buf, sizeof(compile_err_buf),
                 "dimension of array is %d, greater then 8; E:%d.",
                 type_specifier->dimension,
                 ERROR_ARRAY_DIMENSION_INVALID);


        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = get_package_unit(),
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(type_specifier->line_number),
            .line_number             = type_specifier->line_number,
            .column_number           = package_unit_get_column_number(),
            .error_message           = std::string(compile_err_buf),
            .advice                  = std::string(compile_adv_buf),
            .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
            .ring_compiler_file      = (char*)__FILE__,
            .ring_compiler_file_line = __LINE__,
        };
        ring_compile_error_report(&context);
    }

    return type_specifier;
}


TypeSpecifier* create_class_type_specifier(char* identifier) {
    debug_ast_info_with_yellow("\t");

    TypeSpecifier* type_specifier                  = (TypeSpecifier*)mem_alloc(get_front_mem_pool(), sizeof(TypeSpecifier));
    type_specifier->kind                           = RING_BASIC_TYPE_CLASS;
    type_specifier->line_number                    = package_unit_get_line_number();
    type_specifier->u.class_type                   = (Ring_DeriveType_Class*)mem_alloc(get_front_mem_pool(), sizeof(Ring_DeriveType_Class));
    type_specifier->u.class_type->class_identifier = identifier;
    type_specifier->u.class_type->class_definition = nullptr;
    type_specifier->dimension                      = 0;
    type_specifier->sub                            = nullptr;

    return type_specifier;
}

Declaration* create_declaration(TypeSpecifier* type, char* identifier, Expression* initializer) {
    debug_ast_info_with_yellow("identifier:%s", identifier);

    Declaration* declaration    = (Declaration*)mem_alloc(get_front_mem_pool(), sizeof(Declaration));
    declaration->line_number    = package_unit_get_line_number();
    declaration->type_specifier = type;
    declaration->identifier     = identifier;
    declaration->initializer    = initializer;
    declaration->is_const       = 0;
    declaration->is_local       = 0;
    declaration->variable_index = -1; // UPDATED_BY_FIX_AST
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

Statement* create_multi_declaration_statement(TypeSpecifier* type_specifier,
                                              Identifier*    identifier_list,
                                              Expression*    initializer_list) {

    Declaration* head     = nullptr;
    Identifier*  pos_ider = identifier_list;
    Expression*  pos_init = initializer_list;
    for (pos_ider = identifier_list; pos_ider; pos_ider = pos_ider->next) {
        // Ring-Compiler-Error-Report  ERROR_INVALID_VARIABLE_IDENTIFIER
        if (str_eq(pos_ider->name, "self")) {
            DEFINE_ERROR_REPORT_STR;

            snprintf(compile_err_buf, sizeof(compile_err_buf),
                     "forbid definite `self` variable; E:%d.",
                     ERROR_INVALID_VARIABLE_IDENTIFIER);
            snprintf(compile_adv_buf, sizeof(compile_adv_buf),
                     "`self` only be used to access field of class in method block.");


            ErrorReportContext context = {
                .package                 = nullptr,
                .package_unit            = get_package_unit(),
                .source_file_name        = get_package_unit()->current_file_name,
                .line_content            = package_unit_get_line_content(pos_ider->line_number),
                .line_number             = pos_ider->line_number,
                .column_number           = package_unit_get_column_number(),
                .error_message           = std::string(compile_err_buf),
                .advice                  = std::string(compile_adv_buf),
                .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
                .ring_compiler_file      = (char*)__FILE__,
                .ring_compiler_file_line = __LINE__,
            };
            ring_compile_error_report(&context);
        }


        Declaration* decl = create_declaration(type_specifier, pos_ider->name, pos_init);
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

Statement* create_declaration_statement(TypeSpecifier* type,
                                        char*          identifier,
                                        Expression*    initializer) {

    debug_ast_info_with_yellow("identifier:%s", identifier);

    Statement* statement               = (Statement*)mem_alloc(get_front_mem_pool(), sizeof(Statement));
    statement->line_number             = package_unit_get_line_number();
    statement->type                    = STATEMENT_TYPE_DECLARATION;
    statement->u.declaration_statement = create_declaration(type, identifier, initializer);
    statement->next                    = nullptr;

    return statement;
}

Parameter* create_parameter(TypeSpecifier* type, char* identifier, bool is_variadic) {
    Parameter* parameter      = (Parameter*)mem_alloc(get_front_mem_pool(), sizeof(Parameter));
    parameter->line_number    = package_unit_get_line_number();
    parameter->type_specifier = type;
    parameter->is_variadic    = is_variadic;
    parameter->identifier     = identifier;
    parameter->next           = nullptr;

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
    debug_ast_info_with_yellow("current package name:%s\n", package_name);
    Package* package      = (Package*)mem_alloc(get_front_mem_pool(), sizeof(Package));
    package->package_name = package_name;

    return package;
}

void import_package_list_add_item(char* package_name, char* rename) {
    debug_ast_info_with_yellow("import package name:%s, rename:%s\n", package_name, rename);

    // duplicate import package
    for (ImportPackageInfo* import_pack : get_package_unit()->import_package_list) {
        // Ring-Compiler-Error-Report  ERROR_DUPLICATE_IMPORT_PACKAGE
        if (str_eq(import_pack->package_name, package_name)) {
            DEFINE_ERROR_REPORT_STR;
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
                .package                 = nullptr,
                .package_unit            = get_package_unit(),
                .source_file_name        = get_package_unit()->current_file_name,
                .line_content            = package_unit_get_line_content(import_pack->line_number),
                .line_number             = package_unit_get_line_number(),
                .column_number           = package_unit_get_column_number(),
                .error_message           = std::string(compile_err_buf),
                .advice                  = std::string(compile_adv_buf),
                .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
                .ring_compiler_file      = (char*)__FILE__,
                .ring_compiler_file_line = __LINE__,
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
    debug_ast_info_with_yellow("\t");

    ClassDefinition* class_def   = (ClassDefinition*)mem_alloc(get_front_mem_pool(), sizeof(ClassDefinition));
    class_def->source_file       = package_unit_get_file_name();
    class_def->start_line_number = package_unit_get_line_number();
    class_def->end_line_number   = package_unit_get_line_number();
    class_def->identifier        = class_identifier;
    class_def->field_size        = 0;
    class_def->field_list        = nullptr;
    class_def->method_size       = 0;
    class_def->method_list       = nullptr;
    class_def->next              = nullptr;


    package_unit_add_class_definition(class_def);

    return class_def;
}

ClassDefinition* finish_class_definition(ClassDefinition*        class_def,
                                         ClassMemberDeclaration* class_member_declar) {
    debug_ast_info_with_yellow("\t");

    assert(class_def != nullptr);

    unsigned int  field_size  = 0;
    FieldMember*  field_list  = nullptr;
    FieldMember*  prev_field  = nullptr;
    unsigned int  method_size = 0;
    MethodMember* method_list = nullptr;
    MethodMember* prev_method = nullptr;

    // 分别存储在 field_list 和 method_list
    for (ClassMemberDeclaration* pos = class_member_declar; pos != nullptr; pos = pos->next) {
        if (pos->type == MEMBER_FIELD) {

            pos->u.field->next = nullptr;
            if (prev_field == nullptr) {
                field_list = pos->u.field;
            } else {
                prev_field->next = pos->u.field;
            }

            prev_field = pos->u.field;
            field_size++;
        } else if (pos->type == MEMBER_METHOD) {

            pos->u.method->next = nullptr;
            if (prev_method == nullptr) {
                method_list = pos->u.method;
            } else {
                prev_method->next = (FunctionTuple*)pos->u.method;
            }

            prev_method = pos->u.method;
            method_size++;
        }
    }

    class_def->end_line_number = package_unit_get_line_number();
    class_def->field_size      = field_size;
    class_def->field_list      = field_list;
    class_def->method_size     = method_size;
    class_def->method_list     = method_list;


    return class_def;
}

ClassMemberDeclaration* class_member_declaration_list_add_item(ClassMemberDeclaration* list,
                                                               ClassMemberDeclaration* decl) {

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

ClassMemberDeclaration* create_class_member_field_declaration(Attribute    attribute,
                                                              FieldMember* field_member) {

    assert(field_member != nullptr);

    ClassMemberDeclaration* class_member_declar = (ClassMemberDeclaration*)mem_alloc(get_front_mem_pool(), sizeof(ClassMemberDeclaration));
    class_member_declar->line_number            = package_unit_get_line_number();
    class_member_declar->type                   = MEMBER_FIELD;
    class_member_declar->u.field                = field_member;
    class_member_declar->next                   = nullptr;

    return class_member_declar;
}

ClassMemberDeclaration* create_class_member_method_declaration(Attribute     attribute,
                                                               MethodMember* method_member) {

    assert(method_member != nullptr);

    ClassMemberDeclaration* class_member_declar = (ClassMemberDeclaration*)mem_alloc(get_front_mem_pool(), sizeof(ClassMemberDeclaration));
    class_member_declar->line_number            = package_unit_get_line_number();
    class_member_declar->type                   = MEMBER_METHOD;
    class_member_declar->u.method               = method_member;
    class_member_declar->next                   = nullptr;

    return class_member_declar;
}

FieldMember* create_class_member_field(TypeSpecifier* type_specifier,
                                       Identifier*    identifier_list) {

    debug_ast_info_with_yellow("\t");

    // 当前field 的类型只能是 bool int double string
    // Ring-Compiler-Error-Report
    if (type_specifier->kind == RING_BASIC_TYPE_ANY
        || type_specifier->kind == RING_BASIC_TYPE_UNKNOW
        || (type_specifier->kind == RING_BASIC_TYPE_ARRAY
            && (type_specifier->sub->kind == RING_BASIC_TYPE_ANY
                || type_specifier->sub->kind == RING_BASIC_TYPE_UNKNOW))) {
        DEFINE_ERROR_REPORT_STR;

        snprintf(compile_err_buf, sizeof(compile_err_buf),
                 "class field's type only support bool/int/double/string/class bool[]/int[]/double[]/string[]/class[]; E:%d.",
                 ERROR_INVALID_FIELD_IN_CLASS);

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = get_package_unit(),
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(type_specifier->line_number),
            .line_number             = type_specifier->line_number,
            .column_number           = package_unit_get_column_number(),
            .error_message           = std::string(compile_err_buf),
            .advice                  = std::string(compile_adv_buf),
            .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
            .ring_compiler_file      = (char*)__FILE__,
            .ring_compiler_file_line = __LINE__,
        };
        ring_compile_error_report(&context);
    }

    FieldMember* field_member    = (FieldMember*)mem_alloc(get_front_mem_pool(), sizeof(FieldMember));
    field_member->line_number    = package_unit_get_line_number();
    field_member->type_specifier = type_specifier;
    field_member->identifier     = identifier_list->name;
    field_member->index_of_class = 0;

    return field_member;
}

MethodMember* create_class_member_method(FunctionType        type,
                                         Identifier*         identifier,
                                         Parameter*          parameter_list,
                                         FunctionReturnList* return_list,
                                         Block*              block) {

    debug_ast_info_with_yellow("\t");

    MethodMember* method_member        = (MethodMember*)mem_alloc(get_front_mem_pool(), sizeof(MethodMember));

    method_member->source_file         = package_unit_get_file_name();
    method_member->start_line_number   = identifier->line_number;
    method_member->end_line_number     = package_unit_get_line_number();
    method_member->package             = get_package_unit()->parent_package;
    method_member->ring_file_stat      = get_package_unit()->ring_file_stat;

    method_member->identifier          = identifier->name;

    method_member->parameter_list_size = 0;
    method_member->parameter_list      = parameter_list;

    method_member->return_list_size    = 0;
    method_member->return_list         = return_list;

    method_member->block               = block;

    method_member->next                = nullptr;

    method_member->index_of_class      = -1;


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
