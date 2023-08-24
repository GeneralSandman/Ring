// 语义检查
// 上下文语义分析
#include "ring.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void ring_compiler_semantic_analysis(Package* package) {
    std::unordered_map<std::string, Declaration*> global_declaration_map;
    std::unordered_map<std::string, Function*>    function_map;

    // TODO: fix import package
    for (Declaration* decl : package->global_declaration_list) {
        std::string identifier = std::string(decl->identifier);
        auto        iter       = global_declaration_map.find(identifier);
        if (iter != global_declaration_map.end()) {
            char error_message_buffer[1024];
            char advice_buffer[1024];
            snprintf(error_message_buffer, 1024, "%sError:%s "
                                                 "redefinition of global variable `%s`; E:%d",
                     LOG_COLOR_RED,
                     LOG_COLOR_CLEAR,
                     decl->identifier,
                     ERROR_REDEFINITE_GLOBAL_VARIABLE);
            snprintf(advice_buffer, 1024, "%sNotice:%s "
                                          "the first definition of global variable `%s` is here",
                     LOG_COLOR_YELLOW,
                     LOG_COLOR_CLEAR,
                     decl->identifier);

            ErrorReportContext context = {
                package,
                get_package_unit()->current_file_name,
                package_unit_get_line_content(decl->line_number),
                decl->line_number,
                0,
                std::string(error_message_buffer),
                std::string(advice_buffer),
                ERROR_REPORT_TYPE_COLL_ERR,
            };
            ring_compile_error_report(&context);
            continue;
        }
        global_declaration_map[identifier] = decl;
    }
    for (ClassDefinition* pos : package->class_definition_list) {
    }
    for (Function* function : package->function_list) {
        std::string identifier = std::string(function->function_name);
        auto        iter       = function_map.find(identifier);
        if (iter != function_map.end()) {
            char error_message_buffer[1024];
            char advice_buffer[1024];
            snprintf(error_message_buffer, 1024, "%sError:%s "
                                                 "redefinition of function `%s`; E:%d",
                     LOG_COLOR_RED,
                     LOG_COLOR_CLEAR,
                     function->function_name,
                     ERROR_REDEFINITE_FUNCTION);
            snprintf(advice_buffer, 1024, "%sNotice:%s "
                                          "the first definition of function `%s` is here",
                     LOG_COLOR_YELLOW,
                     LOG_COLOR_CLEAR,
                     function->function_name);

            ErrorReportContext context = {
                package,
                get_package_unit()->current_file_name,
                package_unit_get_line_content(function->line_number),
                function->line_number,
                0,
                std::string(error_message_buffer),
                std::string(advice_buffer),
                ERROR_REPORT_TYPE_COLL_ERR,
            };
            ring_compile_error_report(&context);
            continue;
        }
        function_map[identifier] = function;
    }
}

void ring_compiler_check_exit(Package* package) {
    if (package->compile_error_num > 0) {
        fprintf(stderr, "%d errors generated, exit.\n", package->compile_error_num);
        fflush(stderr);
        exit(1);
    }
}
