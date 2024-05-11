/*
 * fix_ast.cpp
 *
 * 主要对 AST进行修正, 同时做语义检查
 * 1. search global class definition.
 * 2. search global function definition.
 * 3. search global variable definition.
 * 4. search local variable definition.
 *
 * 1. Fix TypeSpecifier of every Expression.
 * 2. Update class definition index.
 * 3. Update global function index.
 */


#include "ring.hpp"
#include <cassert>
#include <cstdlib>
#include <cstring>


/*
 * bool_type_specifier int_type_specifier double_type_specifier string_type_specifier
 *
 * 直接使用 全局 TypeSpecifier, 不使用 mem_alloc
 * 因为对于基础类型的 TypeSpecifier, 不会对TypeSpecifier进行修改, 全局变量可满足要求
 */
TypeSpecifier bool_type_specifier = TypeSpecifier{
    .line_number = 0,
    .kind        = RING_BASIC_TYPE_BOOL,
    .u           = {.array_type = nullptr},
    .dimension   = 0,
    .sub         = 0,
};
TypeSpecifier int_type_specifier = TypeSpecifier{
    .line_number = 0,
    .kind        = RING_BASIC_TYPE_INT,
    .u           = {.array_type = nullptr},
    .dimension   = 0,
    .sub         = 0,
};
TypeSpecifier double_type_specifier = TypeSpecifier{
    .line_number = 0,
    .kind        = RING_BASIC_TYPE_DOUBLE,
    .u           = {.array_type = nullptr},
    .dimension   = 0,
    .sub         = 0,
};
TypeSpecifier string_type_specifier = TypeSpecifier{
    .line_number = 0,
    .kind        = RING_BASIC_TYPE_STRING,
    .u           = {.array_type = nullptr},
    .dimension   = 0,
    .sub         = 0,
};


void ring_compiler_fix_ast(Package* package) {
    // fix class list
    unsigned int class_index = 0;
    for (ClassDefinition* class_def : package->class_definition_list) {
        class_def->class_index = class_index++;
        fix_class_definition(class_def);
    }

    // fix function list
    for (Function* func : package->function_list) {
        fix_function_definition(func);
    }
}

// 修正ast
// TODO: 废弃这个
void ring_compiler_fix_ast(PackageUnit* package_unit) {
    // fix class list
    unsigned int class_index = 0;
    for (ClassDefinition* pos : package_unit->class_definition_list) {
        pos->class_index = class_index++;
        fix_class_definition(pos);
    }

    // fix function list
    for (Function* pos : package_unit->function_list) {
        if (pos->block) {
            add_parameter_to_declaration(pos->parameter_list, pos->block);
            fix_statement_list(pos->block->statement_list, pos->block, pos);
        }
    }
}

void fix_function_definition(Function* func) {

    FunctionReturnList* return_list = func->return_list;
    for (; return_list != nullptr; return_list = return_list->next) {
        fix_type_specfier(return_list->type_specifier);
    }

    if (func->block) {
        add_parameter_to_declaration(func->parameter_list, func->block);
        fix_statement_list(func->block->statement_list, func->block, func);
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
        break;

    case STATEMENT_TYPE_TAG_DEFINITION:
        break;

    case STATEMENT_TYPE_JUMP_TAG:
        break;

    default: break;
    }
}

void fix_expression(Expression* expression, Block* block, Function* func) {

BEGIN:
    if (expression == nullptr) {
        return;
    }
    switch (expression->type) {

    case EXPRESSION_TYPE_LITERAL_BOOL:
        EXPRESSION_CLEAR_CONVERT_TYPE(expression);
        EXPRESSION_ADD_CONVERT_TYPE(expression, &bool_type_specifier);
        break;
    case EXPRESSION_TYPE_LITERAL_INT:
        EXPRESSION_CLEAR_CONVERT_TYPE(expression);
        EXPRESSION_ADD_CONVERT_TYPE(expression, &int_type_specifier);
        break;
    case EXPRESSION_TYPE_LITERAL_DOUBLE:
        EXPRESSION_CLEAR_CONVERT_TYPE(expression);
        EXPRESSION_ADD_CONVERT_TYPE(expression, &double_type_specifier);
        break;
    case EXPRESSION_TYPE_LITERAL_STRING:
        EXPRESSION_CLEAR_CONVERT_TYPE(expression);
        EXPRESSION_ADD_CONVERT_TYPE(expression, &string_type_specifier);
        break;

    case EXPRESSION_TYPE_VARIABLE:
        break;

    case EXPRESSION_TYPE_IDENTIFIER:
        fix_identifier_expression(expression, expression->u.identifier_expression, block);
        break;

    case EXPRESSION_TYPE_FUNCTION_CALL:
        fix_function_call_expression(expression, expression->u.function_call_expression, block, func);
        break;

    case EXPRESSION_TYPE_METHOD_CALL:
        fix_method_call_expression(expression, expression->u.method_call_expression, block, func);
        break;

    case EXPRESSION_TYPE_ASSIGN:
        fix_assign_expression(expression->u.assign_expression, block, func);
        break;

    case EXPRESSION_TYPE_TERNARY:
        fix_ternary_condition_expression(expression, expression->u.ternary_expression, block, func);
        break;


    case EXPRESSION_TYPE_CONCAT:
        fix_binary_concat_expression(expression, expression->u.binary_expression, block, func);
        break;
    case EXPRESSION_TYPE_ARITHMETIC_ADD:
    case EXPRESSION_TYPE_ARITHMETIC_SUB:
    case EXPRESSION_TYPE_ARITHMETIC_MUL:
    case EXPRESSION_TYPE_ARITHMETIC_DIV:
    case EXPRESSION_TYPE_ARITHMETIC_MOD:
        fix_binary_math_expression(expression, expression->u.binary_expression, block, func);
        break;
    case EXPRESSION_TYPE_LOGICAL_AND:
    case EXPRESSION_TYPE_LOGICAL_OR:
    case EXPRESSION_TYPE_RELATIONAL_EQ:
    case EXPRESSION_TYPE_RELATIONAL_NE:
    case EXPRESSION_TYPE_RELATIONAL_GT:
    case EXPRESSION_TYPE_RELATIONAL_GE:
    case EXPRESSION_TYPE_RELATIONAL_LT:
    case EXPRESSION_TYPE_RELATIONAL_LE:
        // TODO: 细分
        fix_binary_relational_expression(expression, expression->u.binary_expression, block, func);
        break;


    case EXPRESSION_TYPE_ARITHMETIC_UNITARY_MINUS:
    case EXPRESSION_TYPE_LOGICAL_UNITARY_NOT:
    case EXPRESSION_TYPE_UNITARY_INCREASE:
    case EXPRESSION_TYPE_UNITARY_DECREASE:
        fix_unitary_expression(expression, expression->u.unitary_expression, block, func);
        break;


    case EXPRESSION_TYPE_NEW_ARRAY:
        fix_new_array_expression(expression, expression->u.new_array_expression, block, func);
        break;
    case EXPRESSION_TYPE_ARRAY_LITERAL:
        fix_array_literal_expression(expression, expression->u.array_literal_expression, block, func);
        break;
    case EXPRESSION_TYPE_CLASS_OBJECT_LITERAL:
        fix_class_object_literal_expression(expression, expression->u.class_object_literal_expression, block, func);
        break;


    case EXPRESSION_TYPE_ARRAY_INDEX:
        fix_array_index_expression(expression, expression->u.array_index_expression, block, func);
        break;
    case EXPRESSION_TYPE_MEMBER:
        fix_field_member_expression(expression, expression->u.member_expression, block, func);
        break;

    case EXPRESSION_TYPE_ELEMENT_ACCESS:
        ring_error_report("not implemented");
        break;

    case EXPRESSION_TYPE_CAST:
        fix_expression(expression->u.cast_expression->operand, block, func);
        break;

    default: break;
    }

    expression = expression->next;
    goto BEGIN;
}

void add_declaration(Declaration* declaration, Block* block, Function* func) {
    assert(declaration != nullptr);

    Declaration* pos  = declaration;
    Declaration* next = pos->next;
    for (; pos != nullptr; pos = next) {
        next      = pos->next;
        pos->next = nullptr;

        // fix type specifier
        fix_type_specfier(pos->type_specifier);


        if (block != nullptr) {
            // 局部变量
            block->declaration_list =
                declaration_list_add_item(block->declaration_list, pos);

            pos->variable_index = block->declaration_list_size++;
            pos->is_local       = 1;

            // Ring-Compiler-Error-Report  ERROR_TOO_MANY_LOCAL_VARIABLE
            if (block->declaration_list_size > 255) {
                DEFINE_ERROR_REPORT_STR;

                snprintf(compile_err_buf, sizeof(compile_err_buf),
                         "the number of local variable is greater than 255 in this block; E:%d.",
                         ERROR_TOO_MANY_LOCAL_VARIABLES);
                snprintf(compile_adv_buf, sizeof(compile_adv_buf),
                         "delete useless local variable in this block.");

                ErrorReportContext context = {
                    .package                 = nullptr,
                    .package_unit            = get_package_unit(),
                    .source_file_name        = get_package_unit()->current_file_name,
                    .line_content            = package_unit_get_line_content(declaration->line_number),
                    .line_number             = declaration->line_number,
                    .column_number           = package_unit_get_column_number(),
                    .error_message           = std::string(compile_err_buf),
                    .advice                  = std::string(compile_adv_buf),
                    .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
                    .ring_compiler_file      = (char*)__FILE__,
                    .ring_compiler_file_line = __LINE__,
                };
                ring_compile_error_report(&context);
            }
        } else {
            // 全局变量
            PackageUnit* package_unit = get_package_unit();
            pos->variable_index       = package_unit->global_declaration_list.size();
            pos->is_local             = 0;
            package_unit->global_declaration_list.push_back(pos);
        }
    }
}

void fix_type_specfier(TypeSpecifier* type_specifier) {
    if (type_specifier == nullptr) {
        return;
    }


    ClassDefinition* class_definition = nullptr;
    char*            class_identifier = nullptr;


    // 如果这个变量是类
    // 找到类的定义
    if (type_specifier->kind == RING_BASIC_TYPE_CLASS
        && type_specifier->u.class_type != nullptr) {
        class_identifier = type_specifier->u.class_type->class_identifier;
        class_definition = search_class_definition(class_identifier);

        // Ring-Compiler-Error-Report  ERROR_MISS_CLASS_DEFINITION
        if (class_definition == nullptr) {
            DEFINE_ERROR_REPORT_STR;

            snprintf(compile_err_buf, sizeof(compile_err_buf),
                     "miss class `%s` definition; E:%d.",
                     class_identifier,
                     ERROR_MISS_CLASS_DEFINITION);
            snprintf(compile_adv_buf, sizeof(compile_adv_buf),
                     "definite class `%s` before use it.",
                     class_identifier);


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

        type_specifier->u.class_type->class_definition = class_definition;
    }

    // 递归修正数组
    // 其实修正递归数组，只会对 class-object的数组生效
    if (type_specifier->kind == RING_BASIC_TYPE_ARRAY) {
        fix_type_specfier(type_specifier->sub);
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

    if (for_statement->type == FOR_STATEMENT_TYPE_TERNARY) {
        fix_expression(for_statement->u.ternary_statement->init_expression, block, func);
        fix_expression(for_statement->u.ternary_statement->condition_expression, block, func);
        fix_expression(for_statement->u.ternary_statement->post_expression, block, func);
    } else if (for_statement->type == FOR_STATEMENT_TYPE_RANGE) {
        fix_expression(for_statement->u.range_statement->left, block, func);
        fix_expression(for_statement->u.range_statement->operand, block, func);
    } else {
        ring_error_report("for statement type is invalid error\n");
    }


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


    bool                        has_call = false;

    std::vector<TypeSpecifier*> return_convert_type;
    unsigned                    return_exp_num = 0;

    for (Expression* pos = return_statement->return_list;
         pos != nullptr;
         pos = pos->next, return_exp_num++) {

        if (pos->type == EXPRESSION_TYPE_FUNCTION_CALL
            || pos->type == EXPRESSION_TYPE_METHOD_CALL) {
            has_call = true;
        }

        fix_expression(pos, block, func);

        for (unsigned int i = 0; i < pos->convert_type_size; i++) {
            return_convert_type.push_back(pos->convert_type[i]);
        }
    }


    // check return语句 中表达式的类型 和 function_definition 中的 返回值类型 是否一致

    // Ring-Compiler-Error-Report  ERROR_FUNCTION_CALL_IN_MULTIPLE_OPERANDS
    // operand中有多个, 其中有 function_call, 这是不合法的
    if (return_exp_num > 1 && has_call) {
        DEFINE_ERROR_REPORT_STR;

        snprintf(compile_err_buf, sizeof(compile_err_buf),
                 "function-call/method-call is not allowed in multiple operands; E:%d.",
                 ERROR_FUNCTION_CALL_IN_MULTIPLE_OPERANDS);

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = get_package_unit(),
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(return_statement->line_number),
            .line_number             = return_statement->line_number,
            .column_number           = package_unit_get_column_number(),
            .error_message           = std::string(compile_err_buf),
            .advice                  = std::string(compile_adv_buf),
            .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
            .ring_compiler_file      = (char*)__FILE__,
            .ring_compiler_file_line = __LINE__,
        };
        ring_compile_error_report(&context);
    }


    if (func == nullptr) {
        // TODO:
        // 如果是个method 的话, func 为空
        // 这里是不应该的
        // 但是 Function MethodMember 结构基本相同, 但是略有差异, 后续考虑统一,
        // 然后 func 不能 为空
        // 这里暂时先跳过检查
        return;
    }

    // Ring-Compiler-Error-Report  ERROR_FUNCTION_MISMATCH_RETURN_NUM
    if (func->return_list_size != return_convert_type.size()) {
        DEFINE_ERROR_REPORT_STR;

        snprintf(compile_err_buf, sizeof(compile_err_buf),
                 "the number of return expression list mismatch function definition return value list, expect %d but return %ld; E:%d.",
                 func->return_list_size,
                 return_convert_type.size(),
                 ERROR_FUNCTION_MISMATCH_RETURN_NUM);
        snprintf(compile_adv_buf, sizeof(compile_adv_buf),
                 "delete useless local variable in this block.");

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = get_package_unit(),
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(return_statement->line_number),
            .line_number             = return_statement->line_number,
            .column_number           = package_unit_get_column_number(),
            .error_message           = std::string(compile_err_buf),
            .advice                  = std::string(compile_adv_buf),
            .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
            .ring_compiler_file      = (char*)__FILE__,
            .ring_compiler_file_line = __LINE__,
        };
        ring_compile_error_report(&context);
    }


    std::vector<std::string> expect_type_strs;
    std::string              expect_type_str;
    for (FunctionReturnList* pos = func->return_list;
         pos != nullptr;
         pos = pos->next) {

        expect_type_strs.push_back(format_type_specifier(pos->type_specifier));
    }
    expect_type_str = "(" + strings_join(expect_type_strs, ", ") + ")";

    std::vector<std::string> actual_type_strs;
    std::string              actual_type_str;
    for (TypeSpecifier* type : return_convert_type) {
        actual_type_strs.push_back(format_type_specifier(type));
    }
    actual_type_str = "(" + strings_join(actual_type_strs, ", ") + ")";


    // Ring-Compiler-Error-Report  ERROR_FUNCTION_MISMATCH_RETURN_TYPE
    FunctionReturnList* return_value = func->return_list;
    unsigned int        i            = 0;
    for (; return_value != nullptr;
         return_value = return_value->next, i++) {

        TypeSpecifier* expect = return_value->type_specifier;
        TypeSpecifier* actual = return_convert_type[i];

        // TODO: 深度比较
        // TODO: 比对 类
        if (expect->kind != actual->kind) {
            DEFINE_ERROR_REPORT_STR;

            // TODO:
            snprintf(compile_err_buf, sizeof(compile_err_buf),
                     "return mismatch: expect %s but return %s; E:%d.",
                     expect_type_str.c_str(),
                     actual_type_str.c_str(),
                     ERROR_ASSIGNMENT_MISMATCH_TYPE);

            ErrorReportContext context = {
                .package                 = nullptr,
                .package_unit            = get_package_unit(),
                .source_file_name        = get_package_unit()->current_file_name,
                .line_content            = package_unit_get_line_content(return_statement->line_number),
                .line_number             = return_statement->line_number,
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
}

void fix_identifier_expression(Expression*           expression,
                               IdentifierExpression* identifier_expression,
                               Block*                block) {

    assert(identifier_expression != nullptr);

    Declaration*   declaration    = nullptr;
    TypeSpecifier* type_specifier = nullptr;

    switch (identifier_expression->type) {
    case IDENTIFIER_EXPRESSION_TYPE_VARIABLE:
        declaration = search_declaration(identifier_expression->package_posit, identifier_expression->identifier, block);

        // Ring-Compiler-Error-Report  ERROR_UNDEFINITE_VARIABLE
        if (declaration == nullptr) {
            DEFINE_ERROR_REPORT_STR;
            snprintf(compile_err_buf, 1024,
                     "use undeclared identifier `%s`; E:%d.",
                     identifier_expression->identifier,
                     ERROR_UNDEFINITE_VARIABLE);
            snprintf(compile_adv_buf, 1024,
                     "definite variable `%s` like: `var bool|int|double|string %s;` before use it.",
                     identifier_expression->identifier,
                     identifier_expression->identifier);

            ErrorReportContext context = {
                .package                 = nullptr,
                .package_unit            = nullptr,
                .source_file_name        = get_package_unit()->current_file_name,
                .line_content            = package_unit_get_line_content(identifier_expression->line_number),
                .line_number             = identifier_expression->line_number,
                .column_number           = 0,
                .error_message           = std::string(compile_err_buf),
                .advice                  = std::string(compile_adv_buf),
                .report_type             = ERROR_REPORT_TYPE_EXIT_NOW,
                .ring_compiler_file      = (char*)__FILE__,
                .ring_compiler_file_line = __LINE__,
            };
            ring_compile_error_report(&context);
        }
        identifier_expression->u.declaration = declaration;
        type_specifier                       = declaration->type_specifier;
        break;


    default:
        break;
    }

    EXPRESSION_CLEAR_CONVERT_TYPE(expression);
    EXPRESSION_ADD_CONVERT_TYPE(expression, type_specifier);
}

/*
 * fix_assign_expression 主要对 assignment 语句进行语义检查和AST的修正
 *
 * 1. 检查 left 和 right 的数量是否匹配
 * 2. 检查 left 和 right 的类型是否匹配
 * 3. assignment 是多项赋值语句的时候, 情况复杂了
 *    3.1 如果 right 是function-call, 并且这个函数有多个返回值, 那么: 在 right中 只能存在 这个function-call
 *        a,b,c = test(); // 合法的, 因为test()返回值作为一个整体, 可以继续展开成 三个表达式
 *        a,b,c,c = test(), 1; // 不合法的, 因为test()返回值作为一个整体, 是不能继续展开的, 只能是一个表达式
 */
void fix_assign_expression(AssignExpression* expression, Block* block, Function* func) {
    if (expression == nullptr) {
        return;
    }

    unsigned int                left_expr_num = 0;
    std::vector<TypeSpecifier*> left_convert_type;
    // 对于 left, left_expr_num 和 left_convert_type.size() 是相同的
    for (Expression* pos = expression->left; pos; pos = pos->next, left_expr_num++) {
        fix_expression(pos, block, func);

        left_convert_type.push_back(pos->convert_type[0]);
    }

    bool                        has_call        = false;
    Expression*                 call_expression = nullptr;

    unsigned int                right_expr_num  = 0;
    std::vector<TypeSpecifier*> right_convert_type;
    // 对于 left, 如果 function 有多个返回值, right_expr_num 和 right_convert_type.size() 是不相同的
    for (Expression* pos = expression->operand; pos; pos = pos->next, right_expr_num++) {

        if (pos->type == EXPRESSION_TYPE_FUNCTION_CALL
            || pos->type == EXPRESSION_TYPE_METHOD_CALL) {
            call_expression = pos;
            has_call        = true;
        }

        fix_expression(pos, block, func);

        for (unsigned int i = 0; i < pos->convert_type_size; i++) {
            right_convert_type.push_back(pos->convert_type[i]);
        }
    }


    if (left_expr_num > 1 || right_expr_num > 1) {
        expression->type = ASSIGN_EXPRESSION_TYPE_MULTI_ASSIGN;
    }

    // Ring-Compiler-Error-Report  ERROR_FUNCTION_CALL_IN_MULTIPLE_OPERANDS
    // operand中有多个, 其中有 function_call, 这是不合法的
    if (right_expr_num > 1 && has_call) {
        DEFINE_ERROR_REPORT_STR;

        snprintf(compile_err_buf, sizeof(compile_err_buf),
                 "function-call/method-call is not allowed in multiple operands; E:%d.",
                 ERROR_FUNCTION_CALL_IN_MULTIPLE_OPERANDS);

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = get_package_unit(),
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(call_expression->line_number),
            .line_number             = call_expression->line_number,
            .column_number           = package_unit_get_column_number(),
            .error_message           = std::string(compile_err_buf),
            .advice                  = std::string(compile_adv_buf),
            .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
            .ring_compiler_file      = (char*)__FILE__,
            .ring_compiler_file_line = __LINE__,
        };
        ring_compile_error_report(&context);
    }


    // Ring-Compiler-Error-Report  ERROR_ASSIGNMENT_MISMATCH_NUM
    if (left_convert_type.size() != right_convert_type.size()) {
        DEFINE_ERROR_REPORT_STR;

        snprintf(compile_err_buf, sizeof(compile_err_buf),
                 "assignment mismatch: %lu variables not match %lu operands; E:%d.",
                 left_convert_type.size(),
                 right_convert_type.size(),
                 ERROR_ASSIGNMENT_MISMATCH_NUM);

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

    std::string left_type_s  = "(";
    std::string right_type_s = "(";
    // TODO: 第一个空格需要去掉
    for (TypeSpecifier* type : left_convert_type) {
        left_type_s += "," + format_type_specifier(type);
    }
    left_type_s += ")";
    // TODO: 第一个空格需要去掉
    for (TypeSpecifier* type : right_convert_type) {
        right_type_s += "," + format_type_specifier(type);
    }
    right_type_s += ")";

    // Ring-Compiler-Error-Report  ERROR_ASSIGNMENT_MISMATCH_TYPE
    for (unsigned int i = 0; i < left_convert_type.size(); i++) {

        // TODO: 深度比较
        // TODO: 比对 类
        if (left_convert_type[i]->kind != right_convert_type[i]->kind) {
            DEFINE_ERROR_REPORT_STR;

            // TODO:
            snprintf(compile_err_buf, sizeof(compile_err_buf),
                     "assignment mismatch: expect %s but return %s; E:%d.",
                     left_type_s.c_str(),
                     right_type_s.c_str(),
                     ERROR_ASSIGNMENT_MISMATCH_TYPE);

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
    }
}

void fix_binary_concat_expression(Expression*       expression,
                                  BinaryExpression* binary_expression,
                                  Block* block, Function* func) {

    assert(expression != nullptr);
    assert(binary_expression != nullptr);

    Expression* left_expression  = binary_expression->left_expression;
    Expression* right_expression = binary_expression->right_expression;

    fix_expression(left_expression, block, func);
    fix_expression(right_expression, block, func);


    // Ring-Compiler-Error-Report  ERROR_CONCAT_OPERATOR_MISMATCH_TYPE
    if (left_expression->convert_type_size != 1
        || right_expression->convert_type_size != 1) {
        DEFINE_ERROR_REPORT_STR;

        snprintf(compile_err_buf, sizeof(compile_err_buf),
                 "Type error: string concat operator `..` can only be applied to string; E:%d.",
                 ERROR_CONCAT_OPERATOR_MISMATCH_TYPE);

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = get_package_unit(),
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(left_expression->line_number),
            .line_number             = left_expression->line_number,
            .column_number           = package_unit_get_column_number(),
            .error_message           = std::string(compile_err_buf),
            .advice                  = std::string(compile_adv_buf),
            .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
            .ring_compiler_file      = (char*)__FILE__,
            .ring_compiler_file_line = __LINE__,
        };
        ring_compile_error_report(&context);
    }

    // Ring-Compiler-Error-Report  ERROR_CONCAT_OPERATOR_MISMATCH_TYPE
    if (left_expression->convert_type[0]->kind != RING_BASIC_TYPE_STRING
        || right_expression->convert_type[0]->kind != RING_BASIC_TYPE_STRING) {
        DEFINE_ERROR_REPORT_STR;

        snprintf(compile_err_buf, sizeof(compile_err_buf),
                 "Type error: string concat operator `..` can only be applied to string; E:%d.",
                 ERROR_CONCAT_OPERATOR_MISMATCH_TYPE);

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = get_package_unit(),
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(left_expression->line_number),
            .line_number             = left_expression->line_number,
            .column_number           = package_unit_get_column_number(),
            .error_message           = std::string(compile_err_buf),
            .advice                  = std::string(compile_adv_buf),
            .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
            .ring_compiler_file      = (char*)__FILE__,
            .ring_compiler_file_line = __LINE__,
        };
        ring_compile_error_report(&context);
    }

    EXPRESSION_CLEAR_CONVERT_TYPE(expression);
    EXPRESSION_ADD_CONVERT_TYPE(expression, &string_type_specifier);
}

void fix_binary_math_expression(Expression*       expression,
                                BinaryExpression* binary_expression,
                                Block* block, Function* func) {

    assert(expression != nullptr);
    assert(binary_expression != nullptr);

    Expression* left_expression  = binary_expression->left_expression;
    Expression* right_expression = binary_expression->right_expression;

    fix_expression(left_expression, block, func);
    fix_expression(right_expression, block, func);

    if (expression->convert_type == nullptr) {
        TypeSpecifier* convert_type = (TypeSpecifier*)mem_alloc(get_front_mem_pool(), sizeof(TypeSpecifier));
        convert_type->kind          = RING_BASIC_TYPE_INT;
        EXPRESSION_CLEAR_CONVERT_TYPE(expression);
        EXPRESSION_ADD_CONVERT_TYPE(expression, convert_type);
    }

    if (expression->type == EXPRESSION_TYPE_CONCAT) {
        expression->convert_type[0]->kind = RING_BASIC_TYPE_STRING;
        return;
    }

    if (left_expression->type == EXPRESSION_TYPE_LITERAL_DOUBLE
        || right_expression->type == EXPRESSION_TYPE_LITERAL_DOUBLE) {
        expression->convert_type[0]->kind = RING_BASIC_TYPE_DOUBLE;
    }

    if ((left_expression->convert_type && left_expression->convert_type[0]->kind == RING_BASIC_TYPE_DOUBLE)
        || (right_expression->convert_type && right_expression->convert_type[0]->kind == RING_BASIC_TYPE_DOUBLE)) {
        expression->convert_type[0]->kind = RING_BASIC_TYPE_DOUBLE;
    }
}

void fix_binary_relational_expression(Expression*       expression,
                                      BinaryExpression* binary_expression,
                                      Block* block, Function* func) {

    assert(expression != nullptr);
    assert(binary_expression != nullptr);

    Expression* left_expression  = binary_expression->left_expression;
    Expression* right_expression = binary_expression->right_expression;

    fix_expression(left_expression, block, func);
    fix_expression(right_expression, block, func);


    EXPRESSION_CLEAR_CONVERT_TYPE(expression);
    EXPRESSION_ADD_CONVERT_TYPE(expression, &bool_type_specifier);
}

void fix_unitary_expression(Expression* expression,
                            Expression* unitary_expression,
                            Block* block, Function* func) {

    fix_expression(unitary_expression, block, func);

    EXPRESSION_CLEAR_CONVERT_TYPE(expression);
    EXPRESSION_ADD_CONVERT_TYPE(expression, unitary_expression->convert_type[0]);
}

void fix_function_call_expression(Expression*             expression,
                                  FunctionCallExpression* function_call_expression,
                                  Block*                  block,
                                  Function*               func) {

    if (function_call_expression == nullptr) {
        return;
    }

    ArgumentList* pos = function_call_expression->argument_list;
    for (; pos != nullptr; pos = pos->next) {
        fix_expression(pos->expression, block, func);
    }


    Function* function = nullptr;
    if (is_buildin_function_identifier(function_call_expression->package_posit,
                                       function_call_expression->func_identifier)) {

        fix_buildin_func(expression, function_call_expression, block, func);

    } else {

        function = search_function(function_call_expression->package_posit,
                                   function_call_expression->func_identifier);

        check_function_call(function_call_expression, function);

        function_call_expression->function = function;


        // function_call_expression 的类型取决于 function 返回值的类型
        EXPRESSION_CLEAR_CONVERT_TYPE(expression);
        FunctionReturnList* pos = function->return_list;
        for (; pos != nullptr; pos = pos->next) {
            EXPRESSION_ADD_CONVERT_TYPE(expression, pos->type_specifier);
        }
    }
}

void fix_method_call_expression(Expression*           expression,
                                MethodCallExpression* method_call_expression,
                                Block*                block,
                                Function*             func) {

    if (method_call_expression == nullptr) {
        return;
    }

    char*            member_identifier = method_call_expression->member_identifier;
    ClassDefinition* class_definition  = nullptr;
    MethodMember*    method            = nullptr;
    Expression*      object_expression = method_call_expression->object_expression;

    // 0. fix object expression
    fix_expression(object_expression, block, func);

    // 1. find class definition by object.
    class_definition = object_expression->convert_type[0]->u.class_type->class_definition;
    if (class_definition == nullptr) {
        ring_error_report("fix_method_call_expression error\n");
    }

    // 2. find member declaration by member identifier.
    method = search_class_method(class_definition, member_identifier);

    // Ring-Compiler-Error-Report  ERROR_INVALID_NOT_FOUND_CLASS_METHOD
    if (method == nullptr) {
        DEFINE_ERROR_REPORT_STR;

        snprintf(compile_err_buf, sizeof(compile_err_buf),
                 "not found method `%s`; E:%d.",
                 member_identifier,
                 ERROR_INVALID_NOT_FOUND_CLASS_METHOD);

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = get_package_unit(),
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(method_call_expression->line_number),
            .line_number             = method_call_expression->line_number,
            .column_number           = package_unit_get_column_number(),
            .error_message           = std::string(compile_err_buf),
            .advice                  = std::string(compile_adv_buf),
            .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
            .ring_compiler_file      = (char*)__FILE__,
            .ring_compiler_file_line = __LINE__,
        };
        ring_compile_error_report(&context);
    }

    method_call_expression->method_member = method;

    // 4. fix argument list
    ArgumentList* pos = method_call_expression->argument_list;
    for (; pos != nullptr; pos = pos->next) {
        fix_expression(pos->expression, block, func);
    }

    // method_call_expression 的类型取决于 method返回值的类型
    EXPRESSION_CLEAR_CONVERT_TYPE(expression);
    FunctionReturnList* return_pos = method->return_list;
    for (; return_pos != nullptr; return_pos = return_pos->next) {
        EXPRESSION_ADD_CONVERT_TYPE(expression, return_pos->type_specifier);
    }
}

void fix_class_definition(ClassDefinition* class_definition) {
    assert(class_definition != nullptr);

    unsigned int field_index  = 0;
    unsigned int method_index = 0;

    for (FieldMember* pos = class_definition->field_list;
         pos != nullptr;
         pos = pos->next, field_index++) {
        pos->index_of_class = field_index;
        fix_class_field(class_definition, pos);
    }
    for (MethodMember* pos = class_definition->method_list;
         pos != nullptr;
         pos = pos->next, method_index++) {
        pos->index_of_class = method_index;
        fix_class_method(class_definition, pos);
    }
}

void fix_class_field(ClassDefinition* class_definition, FieldMember* field) {
    fix_type_specfier(field->type_specifier);
}

void fix_class_method(ClassDefinition* class_definition, MethodMember* method) {
    // add self declaration
    Block* block = method->block;


    // self
    TypeSpecifier* type_specifier    = create_class_type_specifier(class_definition->identifier);

    Declaration*   self_declaration  = (Declaration*)mem_alloc(get_front_mem_pool(), sizeof(Declaration));
    self_declaration->line_number    = method->start_line_number;
    self_declaration->type_specifier = type_specifier;
    self_declaration->identifier     = (char*)"self";
    self_declaration->initializer    = nullptr;
    self_declaration->is_const       = false;
    self_declaration->is_local       = false;
    self_declaration->variable_index = -1;
    self_declaration->next           = nullptr;

    // 在 method 添加 self 变量命名
    add_declaration(self_declaration, block, nullptr);

    if (block != nullptr) {
        add_parameter_to_declaration(method->parameter_list, block);
        fix_statement_list(block->statement_list, block, nullptr);
    }

    FunctionReturnList* return_list = method->return_list;
    for (; return_list != nullptr; return_list = return_list->next) {
        fix_type_specfier(return_list->type_specifier);
    }
}

void fix_array_index_expression(Expression*           expression,
                                ArrayIndexExpression* array_index_expression,
                                Block*                block,
                                Function*             func) {
    assert(array_index_expression != nullptr);

    char*        package_posit    = array_index_expression->array_expression->u.identifier_expression->package_posit;
    char*        array_identifier = array_index_expression->array_expression->u.identifier_expression->identifier;
    Declaration* declaration      = nullptr;

    declaration                   = search_declaration(package_posit,
                                                       array_identifier,
                                                       block);

    if (declaration == nullptr) {
        ring_error_report("use undeclared identifier `%s`; E:%d.\n",
                          array_identifier,
                          ERROR_UNDEFINITE_VARIABLE);
    }

    fix_expression(array_index_expression->array_expression, block, func);

    fix_dimension_expression(array_index_expression->index_expression, block, func);

    // array_index_expression->array_expression->u.identifier_expression->u.declaration = declaration;

    DimensionExpression* index_expression = array_index_expression->index_expression;
    // 修正最外层 expression 的 convert_type
    TypeSpecifier* type = (TypeSpecifier*)mem_alloc(get_front_mem_pool(), sizeof(TypeSpecifier));
    type->line_number   = expression->line_number;

    /*
     * e.g. var int[,,,] students;
     *
     * students is a four-dimension array.
     * students[0] is a three-dimension array.
     * students[0,0,0] is a int value.
     */
    if (index_expression->dimension < declaration->type_specifier->dimension) {
        type->kind = declaration->type_specifier->kind;
    } else if (index_expression->dimension == declaration->type_specifier->dimension) {
        type->kind = declaration->type_specifier->sub->kind;
    } else {
        ring_error_report("array index access error; E:%d.\n", ERROR_ARRAY_DIMENSION_INVALID);
    }


    if (type->kind == RING_BASIC_TYPE_CLASS) {
        type->u.class_type = declaration->type_specifier->sub->u.class_type;
    }
    fix_type_specfier(type);

    EXPRESSION_CLEAR_CONVERT_TYPE(expression);
    EXPRESSION_ADD_CONVERT_TYPE(expression, type);
}

void fix_new_array_expression(Expression*         expression,
                              NewArrayExpression* new_array_expression,
                              Block*              block,
                              Function*           func) {

    fix_dimension_expression(new_array_expression->dimension_expression, block, func);
    fix_type_specfier(new_array_expression->type_specifier);

    EXPRESSION_CLEAR_CONVERT_TYPE(expression);
    EXPRESSION_ADD_CONVERT_TYPE(expression, (new_array_expression->type_specifier));
}

void fix_dimension_expression(DimensionExpression* dimension_expression,
                              Block*               block,
                              Function*            func) {

    SubDimensionExpression* pos = dimension_expression->dimension_list;
    for (; pos != nullptr; pos = pos->next) {
        fix_expression(pos->num_expression, block, func);
    }
}

void fix_array_literal_expression(Expression*             expression,
                                  ArrayLiteralExpression* array_literal_expression,
                                  Block*                  block,
                                  Function*               func) {

    assert(array_literal_expression != nullptr);

    fix_type_specfier(array_literal_expression->type_specifier);

    Expression* pos = array_literal_expression->expression_list;
    for (; pos != nullptr; pos = pos->next) {
        fix_expression(pos, block, func);
    }

    EXPRESSION_CLEAR_CONVERT_TYPE(expression);
    EXPRESSION_ADD_CONVERT_TYPE(expression, array_literal_expression->type_specifier);
}

void fix_class_object_literal_expression(Expression*                   expression,
                                         ClassObjectLiteralExpression* literal_expression,
                                         Block*                        block,
                                         Function*                     func) {

    assert(literal_expression != nullptr);

    fix_type_specfier(literal_expression->type_specifier);

    ClassDefinition*     class_definition = literal_expression->type_specifier->u.class_type->class_definition;


    FieldInitExpression* pos              = literal_expression->field_init_expression_list;
    for (; pos != nullptr; pos = pos->next) {

        char*        field_identifier = pos->field_identifier;
        FieldMember* field_member     = nullptr;
        for (FieldMember* pos = class_definition->field_list; pos != nullptr; pos = pos->next) {
            if (str_eq(field_identifier, pos->identifier)) {
                field_member = pos;
                break;
            }
        }

        // Ring-Compiler-Error-Report  ERROR_INVALID_NOT_FOUND_CLASS_FIELD
        if (field_member == nullptr) {
            DEFINE_ERROR_REPORT_STR;

            snprintf(compile_err_buf, sizeof(compile_err_buf),
                     "ths class `%s` has not field `%s`; E:%d.",
                     class_definition->identifier,
                     field_identifier,
                     ERROR_ASSIGN_TO_METHOD_OF_CLASS);
            snprintf(compile_adv_buf, sizeof(compile_adv_buf),
                     "the class `%s` definition in %s:%d.",
                     class_definition->identifier,
                     class_definition->source_file.c_str(), class_definition->start_line_number);


            ErrorReportContext context = {
                .package                 = nullptr,
                .package_unit            = get_package_unit(),
                .source_file_name        = get_package_unit()->current_file_name,
                .line_content            = package_unit_get_line_content(pos->line_number),
                .line_number             = pos->line_number,
                .column_number           = package_unit_get_column_number(),
                .error_message           = std::string(compile_err_buf),
                .advice                  = std::string(compile_adv_buf),
                .report_type             = ERROR_REPORT_TYPE_EXIT_NOW,
                .ring_compiler_file      = (char*)__FILE__,
                .ring_compiler_file_line = __LINE__,
            };
            ring_compile_error_report(&context);
        }

        pos->field_member = field_member;

        // fix init_expression
        fix_expression(pos->init_expression, block, func);
    }

    EXPRESSION_CLEAR_CONVERT_TYPE(expression);
    EXPRESSION_ADD_CONVERT_TYPE(expression, literal_expression->type_specifier);
}

/*
 * fix_field_member_expression 只是 修正 field
 */
void fix_field_member_expression(Expression*       expression,
                                 MemberExpression* member_expression,
                                 Block*            block,
                                 Function*         func) {

    assert(member_expression != nullptr);

    char*            member_identifier = member_expression->member_identifier;
    ClassDefinition* class_definition  = nullptr;
    FieldMember*     field             = nullptr;
    Expression*      object_expression = member_expression->object_expression;


    // 0. fix object expression
    fix_expression(object_expression, block, func);

    // 1. find class definition by object.
    class_definition = object_expression->convert_type[0]->u.class_type->class_definition;
    if (class_definition == nullptr) {
        ring_error_report("fix_field_member_expression error, class_definition is null\n");
    }


    // 2. find member declaration by member identifier.
    field = search_class_field(class_definition, member_identifier);

    // Ring-Compiler-Error-Report  ERROR_INVALID_NOT_FOUND_CLASS_FIELD
    if (field == nullptr) {
        DEFINE_ERROR_REPORT_STR;

        snprintf(compile_err_buf, sizeof(compile_err_buf),
                 "not found field `%s`; E:%d.",
                 member_identifier,
                 ERROR_INVALID_NOT_FOUND_CLASS_FIELD);

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = get_package_unit(),
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(member_expression->line_number),
            .line_number             = member_expression->line_number,
            .column_number           = package_unit_get_column_number(),
            .error_message           = std::string(compile_err_buf),
            .advice                  = std::string(compile_adv_buf),
            .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
            .ring_compiler_file      = (char*)__FILE__,
            .ring_compiler_file_line = __LINE__,
        };
        ring_compile_error_report(&context);
    }

    member_expression->field_member = field;


    // expression 最终的类型取决于field-member 的类型
    EXPRESSION_CLEAR_CONVERT_TYPE(expression);
    EXPRESSION_ADD_CONVERT_TYPE(expression, field->type_specifier);
    fix_class_member_expression(member_expression, object_expression, member_identifier);
}


void fix_class_member_expression(MemberExpression* member_expression,
                                 Expression*       object_expression,
                                 char*             member_identifier) {

    // member_expression->member_declaration = ;
}

ClassDefinition* search_class_definition(char* class_identifier) {
    assert(class_identifier != nullptr);

    for (ClassDefinition* pos : get_package_unit()->class_definition_list) {
        if (str_eq(pos->identifier, class_identifier)) {
            return pos;
        }
    }

    return nullptr;
}


FieldMember* search_class_field(ClassDefinition* class_definition, char* identifier) {
    assert(class_definition != nullptr);

    FieldMember* res = nullptr;

    for (FieldMember* pos = class_definition->field_list; pos != nullptr; pos = pos->next) {
        if (str_eq(pos->identifier, identifier)) {
            res = pos;
            break;
        }
    }

    return res;
}

MethodMember* search_class_method(ClassDefinition* class_definition, char* identifier) {
    assert(class_definition != nullptr);

    MethodMember* res = nullptr;

    for (MethodMember* pos = class_definition->method_list; pos != nullptr; pos = pos->next) {
        if (str_eq(pos->identifier, identifier)) {
            res = pos;
            break;
        }
    }

    return res;
}

void fix_ternary_condition_expression(Expression*        expression,
                                      TernaryExpression* ternary_expression,
                                      Block*             block,
                                      Function*          func) {

    if (ternary_expression == nullptr) {
        return;
    }

    Expression* condition_expression = ternary_expression->condition_expression;
    Expression* true_expression      = ternary_expression->true_expression;
    Expression* false_expression     = ternary_expression->false_expression;

    fix_expression(condition_expression, block, func);
    fix_expression(true_expression, block, func);
    fix_expression(false_expression, block, func);

    if (true_expression->convert_type_size != false_expression->convert_type_size) {
        // TODO: error-report
        ring_error_report("true_expression false_expression type_specifier size invalid\n");
    }


    // TODO: error-report 类型不匹配
    if (true_expression->convert_type_size) {
        if (true_expression->convert_type[0]->kind != false_expression->convert_type[0]->kind) {
            ring_error_report("true_expression false_expression type unmatch\n");
        }
    }


    EXPRESSION_CLEAR_CONVERT_TYPE(expression);
    if (true_expression->convert_type_size) {
        EXPRESSION_ADD_CONVERT_TYPE(expression, true_expression->convert_type[0]);
    }

    return;
}

void add_parameter_to_declaration(Parameter* parameter, Block* block) {
    assert(block != nullptr);

    Parameter* pos = parameter;
    for (; pos; pos = pos->next) {

        TypeSpecifier* src_type_specifier = pos->type_specifier;
        TypeSpecifier* type_specifier     = nullptr;

        if (pos->is_variadic) {
            // fix type_specifier to array.
            type_specifier              = (TypeSpecifier*)mem_alloc(get_front_mem_pool(), sizeof(TypeSpecifier));
            type_specifier->line_number = src_type_specifier->line_number;
            type_specifier->kind        = RING_BASIC_TYPE_ARRAY;

            if (src_type_specifier->kind == RING_BASIC_TYPE_ARRAY) {
                // 直接增加一个维度即可
                type_specifier->dimension = src_type_specifier->dimension + 1;
                type_specifier->sub       = src_type_specifier->sub;

            } else {
                // 元素升级为数组
                type_specifier->dimension = 1;
                type_specifier->sub       = src_type_specifier;
            }
        } else {
            type_specifier = src_type_specifier;
        }


        Declaration* declaration    = (Declaration*)mem_alloc(get_front_mem_pool(), sizeof(Declaration));
        declaration->line_number    = pos->line_number;
        declaration->type_specifier = type_specifier;
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
            if (str_eq(identifier, decl->identifier)) {
                return decl;
            }
        }
    }
    for (Declaration* decl : get_package_unit()->global_declaration_list) {
        if (str_eq(identifier, decl->identifier)) {
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
            if (str_eq(function->function_name, identifier)) {
                return function;
            }
        }

        return nullptr;
    }
    for (Function* pos : get_package_unit()->function_list) {
        if (str_eq(identifier, pos->function_name)) {
            return pos;
        }
    }
    return nullptr;
}
