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

void ring_compiler_analysis_class(Package* package) {
    // for (ClassDefinition* pos : package->class_definition_list) {
    // }
}

void ring_compiler_check_exit(Package* package) {
    if (package->compile_error_num > 0) {
        fprintf(stderr, "%d errors generated, exit.\n", package->compile_error_num);
        fflush(stderr);
        exit(1);
    }
}
