// 语义检查
// 上下文语义分析
#include "ring.hpp"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>


void ring_compiler_semantic_analysis(Package* package) {
    ring_compiler_analysis_import_package(package);
}

void ring_compiler_analysis_import_package(Package* package) {
}

void ring_compiler_analysis_global_variable(Package* package) {
    for (VarDecl* decl : package->global_var_decl_list) {
        std::string identifier = std::string(decl->identifier);
        auto        iter       = package->global_var_decl_map.find(identifier);

        // Ring-Compiler-Error-Report ERROR_REDEFINITE_GLOBAL_VARIABLE
        if (iter != package->global_var_decl_map.end()) {
            DEFINE_ERROR_REPORT_STR;

            compile_err_buf = sprintf_string(
                "redefinition of global variable `%s`; E:%d.",
                decl->identifier,
                ERROR_REDEFINITE_GLOBAL_VARIABLE);
            compile_adv_buf = sprintf_string(
                "the first definition of global variable `%s` is here.",
                decl->identifier);

            ErrorReportContext context = {
                .package                 = package,
                .package_unit            = nullptr,
                .source_file_name        = get_package_unit()->current_file_name,
                .line_content            = package_unit_get_line_content(decl->line_number),
                .line_number             = decl->line_number,
                .column_number           = 0,
                .error_message           = std::string(compile_err_buf),
                .advice                  = std::string(compile_adv_buf),
                .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
                .ring_compiler_file      = (char*)__FILE__,
                .ring_compiler_file_line = __LINE__,
            };
            ring_compile_error_report(&context);
            continue;
        }
        package->global_var_decl_map[identifier] = decl;
    }
}

void ring_compiler_analysis_function(Package* package) {

    // 一个package中的函数是否重复
    for (Function* function : package->function_list) {
        std::string identifier = std::string(function->identifier);
        auto        iter       = package->function_map.find(identifier);

        // Ring-Compiler-Error-Report ERROR_REDEFINITE_FUNCTION
        if (iter != package->function_map.end()) {
            DEFINE_ERROR_REPORT_STR;

            compile_err_buf = sprintf_string(
                "redefinition of function `%s`; E:%d.",
                function->identifier,
                ERROR_REDEFINITE_FUNCTION);

            ErrorReportContext context = {
                .package                 = package,
                .package_unit            = nullptr,
                .source_file_name        = get_package_unit()->current_file_name,
                .line_content            = package_unit_get_line_content(function->start_line_number),
                .line_number             = function->start_line_number,
                .column_number           = 0,
                .error_message           = std::string(compile_err_buf),
                .advice                  = std::string(compile_adv_buf),
                .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
                .ring_compiler_file      = (char*)__FILE__,
                .ring_compiler_file_line = __LINE__,
            };
            ring_compile_error_report(&context);
            continue;
        }

        package->function_map[identifier] = function;
    }

    for (Function* function : package->function_list) {
        if (function->type != FUNCTION_TYPE_DERIVE) {
            continue;
        }
        ring_compiler_analysis_function_block(package, function->block);
    }
}

void ring_compiler_analysis_function_block(Package* package, Block* block) {

    //
    std::unordered_map<std::string, VarDecl*> local_var_map;

    for (VarDecl* decl_pos = block->var_decl_list;
         decl_pos != nullptr;
         decl_pos = decl_pos->next) {
        std::string identifier = std::string(decl_pos->identifier);
        auto        iter       = local_var_map.find(identifier);

        // Ring-Compiler-Error-Report ERROR_REDEFINITE_LOCAL_VARIABLE
        if (iter != local_var_map.end()) {
            DEFINE_ERROR_REPORT_STR;

            compile_err_buf = sprintf_string(
                "redefinition of variable `%s`; E:%d.",
                decl_pos->identifier,
                ERROR_REDEFINITE_LOCAL_VARIABLE);

            ErrorReportContext context = {
                .package                 = package,
                .package_unit            = nullptr,
                .source_file_name        = get_package_unit()->current_file_name,
                .line_content            = package_unit_get_line_content(decl_pos->line_number),
                .line_number             = decl_pos->line_number,
                .column_number           = 0,
                .error_message           = std::string(compile_err_buf),
                .advice                  = std::string(compile_adv_buf),
                .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
                .ring_compiler_file      = (char*)__FILE__,
                .ring_compiler_file_line = __LINE__,
            };
            ring_compile_error_report(&context);
            continue;
        }

        local_var_map[identifier] = decl_pos;
    }
}

void check_function_call(FunctionCallExpression* function_call_expression,
                         Function*               function) {

    check_call(function_call_expression->func_identifier,
               function_call_expression->line_number,
               function_call_expression->argument_list,
               function,
               nullptr,
               nullptr,
               nullptr);
}

void check_func_var_call(FunctionCallExpression* function_call_expression,
                         VarDecl*                anony_func_decl) {

    check_call(function_call_expression->func_identifier,
               function_call_expression->line_number,
               function_call_expression->argument_list,
               nullptr,
               anony_func_decl,
               nullptr,
               nullptr);
}

void check_iife_call(ImmediateInvokFuncExpression* iife) {
    check_call((char*)"<closure>",
               iife->line_number,
               iife->argument_list,
               nullptr,
               nullptr,
               iife->anonymous_func,
               nullptr);
}

void check_method_call(MethodCallExpression* method_call_expression,
                       MethodMember*         method) {
    check_call(method_call_expression->member_identifier,
               method_call_expression->line_number,
               method_call_expression->argument_list,
               nullptr,
               nullptr,
               nullptr,
               method);
}


/*
 * check_function_call
 *
 * 对函数调用进行详细的语义分析
 * 1. 参数数量不正确
 * 2. 参数类型不正确
 * 3. 返回值和函数的声明不一致
 *
 * - function_call_expression method_call_expression iife_expression 三者选其一
 * - function anony_func_decl 二者选其一
 * function 为 函数调用
 * anony_func_decl 为匿名函数变量定义
 *
 */
void check_call(char*          func_identifier,
                unsigned int   line_number,
                ArgumentList*  argument_list,
                Function*      function,
                VarDecl*       func_var_decl,
                AnonymousFunc* anony_func,
                MethodMember*  method_member) {

    assert(function != nullptr
           || func_var_decl != nullptr
           || anony_func != nullptr
           || method_member != nullptr);


    ArgumentList* argument_pos  = argument_list;
    Parameter*    parameter_pos = nullptr;

    if (function != nullptr) {
        parameter_pos = function->parameter_list;
    } else if (func_var_decl != nullptr) {
        assert(func_var_decl->type_specifier->kind == RING_BASIC_TYPE_FUNC);
        parameter_pos = func_var_decl->type_specifier->u.func_t->parameter_list;
    } else if (anony_func != nullptr) {
        parameter_pos = anony_func->parameter_list;
    } else if (method_member != nullptr) {
        parameter_pos = method_member->parameter_list;
    }


    std::string parameter_str = format_function_parameters(parameter_pos);
    std::string argument_str  = format_function_arguments(argument_pos);


    // TODO:
    // 这里比对 arguments 和 parameters, 有几个细节需要注意
    // 1. 深度比对派生类型 数组(多维数组)、类
    // 2. 比对 parameter 为     any类型
    // 3. 比对 parameter 为 可变参数类型
    // 4. 如果 parameter 有多个, 并且 argument 是个 function_call, 并且 funciton_call 的返回值有多个, 这种语法是不合法的
    // TIP. argument 给 parameter copy 数据, 其实就行赋值, 要遵守多项赋值过程中 对于 function_call 的限制.
    for (; argument_pos != nullptr && parameter_pos != nullptr;) {

        // Ring-Compiler-Error-Report ERROR_ARGUMENT_MISMATCH_TYPE
        if (!comp_type_specifier(parameter_pos->type_specifier,
                                 argument_pos->expression->convert_type[0])) {
            // FIXME：这里只比对了 convert_type[0]
            goto ERROR_REPORT;
        }

        argument_pos = argument_pos->next;
        if (!parameter_pos->is_variadic) {
            parameter_pos = parameter_pos->next;
        }
    }

    if (parameter_pos != nullptr && parameter_pos->is_variadic) {
        parameter_pos = parameter_pos->next;
    }

    // argument, parameter 都消费完
    // success
    if (argument_pos == nullptr && parameter_pos == nullptr) {
        return;
    }

ERROR_REPORT:
    // Ring-Compiler-Error-Report ERROR_ARGUMENT_MISMATCH_TYPE
    {
        DEFINE_ERROR_REPORT_STR;

        compile_err_buf            = sprintf_string("function %s() requires (%s) arguments, but (%s) was provided; E:%d",
                                                    func_identifier,
                                                    parameter_str.c_str(),
                                                    argument_str.c_str(),
                                                    ERROR_ARGUMENT_MISMATCH_TYPE);

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = nullptr,
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(line_number),
            .line_number             = line_number,
            .column_number           = 0,
            .error_message           = std::string(compile_err_buf),
            .advice                  = std::string(compile_adv_buf),
            .report_type             = ERROR_REPORT_TYPE_EXIT_NOW,
            .ring_compiler_file      = (char*)__FILE__,
            .ring_compiler_file_line = __LINE__,
        };
        ring_compile_error_report(&context);
    }
}

void ring_compiler_analysis_class(Package* package) {
    std::unordered_map<std::string, ClassDefinition*> class_map;

    for (ClassDefinition* class_def : package->class_definition_list) {

        std::string identifier = std::string(class_def->identifier);
        auto        iter       = class_map.find(identifier);

        // Ring-Compiler-Error-Report ERROR_REDEFINITE_CLASS
        if (iter != class_map.end()) {
            DEFINE_ERROR_REPORT_STR;

            compile_err_buf = sprintf_string(
                "redefinition of class`%s`; E:%d.",
                class_def->identifier,
                ERROR_REDEFINITE_CLASS);

            ErrorReportContext context = {
                .package                 = package,
                .package_unit            = nullptr,
                .source_file_name        = get_package_unit()->current_file_name,
                .line_content            = package_unit_get_line_content(class_def->start_line_number),
                .line_number             = class_def->start_line_number,
                .column_number           = 0,
                .error_message           = std::string(compile_err_buf),
                .advice                  = std::string(compile_adv_buf),
                .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
                .ring_compiler_file      = (char*)__FILE__,
                .ring_compiler_file_line = __LINE__,
            };
            ring_compile_error_report(&context);
            continue;
        }

        class_map[identifier] = class_def;
    }

    for (ClassDefinition* class_def : package->class_definition_list) {
        ring_compiler_analysis_class_block(package, class_def);
    }
}


/*
 * ring_compiler_analysis_class_block
 * 1. field method 名字不能重复
 * 2. 对 method 进行 function 式检查
 */
void ring_compiler_analysis_class_block(Package* package, ClassDefinition* class_def) {
    std::unordered_set<std::string> member_map;


    for (FieldMember* field_member = class_def->field_list;
         field_member != nullptr;
         field_member = field_member->next) {

        std::string identifier = std::string(field_member->identifier);
        auto        iter       = member_map.find(identifier);

        // Ring-Compiler-Error-Report ERROR_REDEFINITE_MEMBER_IN_CLASS
        if (iter != member_map.end()) {
            DEFINE_ERROR_REPORT_STR;

            compile_err_buf = sprintf_string(
                "redefinition of field `%s`; E:%d.",
                field_member->identifier,
                ERROR_REDEFINITE_MEMBER_IN_CLASS);

            ErrorReportContext context = {
                .package                 = package,
                .package_unit            = nullptr,
                .source_file_name        = get_package_unit()->current_file_name,
                .line_content            = package_unit_get_line_content(field_member->line_number),
                .line_number             = field_member->line_number,
                .column_number           = 0,
                .error_message           = std::string(compile_err_buf),
                .advice                  = std::string(compile_adv_buf),
                .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
                .ring_compiler_file      = (char*)__FILE__,
                .ring_compiler_file_line = __LINE__,
            };
            ring_compile_error_report(&context);
            continue;
        }

        member_map.insert(identifier);
    }

    for (MethodMember* method_member = class_def->method_list;
         method_member != nullptr;
         method_member = (MethodMember*)method_member->next) {

        std::string identifier = std::string(method_member->identifier);
        auto        iter       = member_map.find(identifier);

        // Ring-Compiler-Error-Report ERROR_REDEFINITE_MEMBER_IN_CLASS
        if (iter != member_map.end()) {
            DEFINE_ERROR_REPORT_STR;

            compile_err_buf = sprintf_string(
                "redefinition of method `%s`; E:%d.",
                method_member->identifier,
                ERROR_REDEFINITE_MEMBER_IN_CLASS);

            ErrorReportContext context = {
                .package                 = package,
                .package_unit            = nullptr,
                .source_file_name        = get_package_unit()->current_file_name,
                .line_content            = package_unit_get_line_content(method_member->start_line_number),
                .line_number             = method_member->start_line_number,
                .column_number           = 0,
                .error_message           = std::string(compile_err_buf),
                .advice                  = std::string(compile_adv_buf),
                .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
                .ring_compiler_file      = (char*)__FILE__,
                .ring_compiler_file_line = __LINE__,
            };
            ring_compile_error_report(&context);
            continue;
        }

        member_map.insert(identifier);
    }


    for (MethodMember* method_member = class_def->method_list;
         method_member != nullptr;
         method_member = (MethodMember*)method_member->next) {

        ring_compiler_analysis_function_block(package, method_member->block);
    }
}

void ring_compiler_check_exit(Package* package) {
    if (package->compile_error_num > 0) {
        fprintf(stderr, "\n\n%d errors generated, exit.\n", package->compile_error_num);
        fflush(stderr);
        exit(1);
    }
}
