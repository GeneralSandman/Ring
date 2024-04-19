// 语义检查
// 上下文语义分析
#include "ring.hpp"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>


void ring_compiler_semantic_analysis(Package* package) {
    ring_compiler_analysis_import_package(package);
    ring_compiler_analysis_global_variable(package);
    ring_compiler_analysis_function(package);
    ring_compiler_analysis_class(package);
}

void ring_compiler_analysis_import_package(Package* package) {
}

void ring_compiler_analysis_global_variable(Package* package) {
    for (Declaration* decl : package->global_declaration_list) {
        std::string identifier = std::string(decl->identifier);
        auto        iter       = package->global_declaration_map.find(identifier);

        // Ring-Compiler-Error-Report  ERROR_REDEFINITE_GLOBAL_VARIABLE
        if (iter != package->global_declaration_map.end()) {
            DEFINE_ERROR_REPORT_STR;

            snprintf(compile_err_buf, sizeof(compile_err_buf),
                     "redefinition of global variable `%s`; E:%d.",
                     decl->identifier,
                     ERROR_REDEFINITE_GLOBAL_VARIABLE);
            snprintf(compile_adv_buf, sizeof(compile_adv_buf),
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
        package->global_declaration_map[identifier] = decl;
    }
}

void ring_compiler_analysis_function(Package* package) {
    for (Function* function : package->function_list) {
        std::string identifier = std::string(function->function_name);
        auto        iter       = package->function_map.find(identifier);

        // Ring-Compiler-Error-Report  ERROR_REDEFINITE_FUNCTION
        if (iter != package->function_map.end()) {
            DEFINE_ERROR_REPORT_STR;

            snprintf(compile_err_buf, sizeof(compile_err_buf),
                     "redefinition of function `%s`; E:%d.",

                     function->function_name,
                     ERROR_REDEFINITE_FUNCTION);
            snprintf(compile_adv_buf, sizeof(compile_adv_buf),
                     "the first definition of function `%s` is here.",

                     function->function_name);

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
}
/*
 *check_function_call
 *
 * 对函数调用进行详细的语义分析
 * 1. 参数数量不正确
 * 2. 参数类型不正确
 * 3. 返回值和函数的声明不一致
 */
void check_function_call(FunctionCallExpression* function_call_expression, Function* function) {
    assert(function_call_expression != nullptr);


    // Ring-Compiler-Error-Report  ERROR_UNDEFINITE_FUNCTION
    if (function == nullptr) {
        DEFINE_ERROR_REPORT_STR;

        snprintf(compile_err_buf, 1024, "use undeclared function `%s`; E:%d",
                 function_call_expression->func_identifier,
                 ERROR_UNDEFINITE_FUNCTION);
        snprintf(compile_adv_buf, 1024, "definite function `%s` like: `function %s() {}` before use it.",
                 function_call_expression->func_identifier,
                 function_call_expression->func_identifier);

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = nullptr,
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(function_call_expression->line_number),
            .line_number             = function_call_expression->line_number,
            .column_number           = 0,
            .error_message           = std::string(compile_err_buf),
            .advice                  = std::string(compile_adv_buf),
            .report_type             = ERROR_REPORT_TYPE_EXIT_NOW,
            .ring_compiler_file      = (char*)__FILE__,
            .ring_compiler_file_line = __LINE__,
        };
        ring_compile_error_report(&context);
    }

    ArgumentList* argument_pos  = function_call_expression->argument_list;
    Parameter*    parameter_pos = function->parameter_list;

    std::string   parameter_str = format_function_parameters(parameter_pos);
    std::string   argument_str  = format_function_arguments(argument_pos);

    // TODO:
    // argument 有多个, 并且 有 argument 是个 function_call, 并且 返回值有多个
    // 这种语法是不被允许的
    // TODO: 比对 any类型
    // TODO: 需要 兼容  var any... any_value 这种参数
    // TODO: 深度比较
    // TODO: 比对 类
    // Ring-Compiler-Error-Report  ERROR_ARGUMENT_MISMATCH_TYPE


    for (; argument_pos != nullptr && parameter_pos != nullptr;) {


        // TODO: 深度比较
        // TODO: 比对 类
        if (parameter_pos->type_specifier->kind != RING_BASIC_TYPE_ANY // FIXME: 修正 any类型
            && parameter_pos->type_specifier->kind != argument_pos->expression->convert_type[0]->kind) {
            DEFINE_ERROR_REPORT_STR;

            snprintf(compile_err_buf, 1024, "function %s() requires (%s) arguments, but (%s) was provided; E:%d",
                     function_call_expression->func_identifier,
                     parameter_str.c_str(),
                     argument_str.c_str(),
                     ERROR_ARGUMENT_MISMATCH_NUM);

            ErrorReportContext context = {
                .package                 = nullptr,
                .package_unit            = nullptr,
                .source_file_name        = get_package_unit()->current_file_name,
                .line_content            = package_unit_get_line_content(function_call_expression->line_number),
                .line_number             = function_call_expression->line_number,
                .column_number           = 0,
                .error_message           = std::string(compile_err_buf),
                .advice                  = std::string(compile_adv_buf),
                .report_type             = ERROR_REPORT_TYPE_EXIT_NOW,
                .ring_compiler_file      = (char*)__FILE__,
                .ring_compiler_file_line = __LINE__,
            };
            ring_compile_error_report(&context);
        }


        argument_pos = argument_pos->next;
        if (!parameter_pos->is_variadic) {
            parameter_pos = parameter_pos->next;
        }
    }
}

void ring_compiler_analysis_class(Package* package) {
    // for (ClassDefinition* pos : package->class_definition_list) {
    // }
}

void ring_compiler_check_exit(Package* package) {
    if (package->compile_error_num > 0) {
        fprintf(stderr, "\n\n%d errors generated, exit.\n", package->compile_error_num);
        fflush(stderr);
        exit(1);
    }
}
