#include "ring.hpp"


Ring_Buildin_Func Ring_Buildin_Funcs[] = {
    {
        .identifier       = "-",
        .param_size       = 0,
        .param_types      = std::vector<TypeSpecifier*>{},
        .return_size      = 0,
        .return_types     = std::vector<TypeSpecifier*>{},
        .buildin_func_fix = nullptr,
    },
    {
        .identifier       = "len",
        .param_size       = 1,
        .param_types      = std::vector<TypeSpecifier*>{},
        .return_size      = 1,
        .return_types     = std::vector<TypeSpecifier*>{},
        .buildin_func_fix = fix_buildin_func_len,
    },
    {
        .identifier       = "capacity",
        .param_size       = 1,
        .param_types      = std::vector<TypeSpecifier*>{},
        .return_size      = 1,
        .return_types     = std::vector<TypeSpecifier*>{},
        .buildin_func_fix = fix_buildin_func_capacity,
    },
    {
        .identifier       = "push",
        .param_size       = 2,
        .param_types      = std::vector<TypeSpecifier*>{},
        .return_size      = 0,
        .return_types     = std::vector<TypeSpecifier*>{},
        .buildin_func_fix = fix_buildin_func_push,
    },
    {
        .identifier       = "pop",
        .param_size       = 1,
        .param_types      = std::vector<TypeSpecifier*>{},
        .return_size      = 0,
        .return_types     = std::vector<TypeSpecifier*>{},
        .buildin_func_fix = fix_buildin_func_pop,
    },
    {
        .identifier       = "to_string",
        .param_size       = 1,
        .param_types      = std::vector<TypeSpecifier*>{},
        .return_size      = 1,
        .return_types     = std::vector<TypeSpecifier*>{},
        .buildin_func_fix = fix_buildin_func_to_string,
    },
    {
        .identifier       = "to_int64",
        .param_size       = 1,
        .param_types      = std::vector<TypeSpecifier*>{},
        .return_size      = 1,
        .return_types     = std::vector<TypeSpecifier*>{},
        .buildin_func_fix = fix_buildin_func_to_int64,
    },
    {
        .identifier       = "resume",
        .param_size       = 1,
        .param_types      = std::vector<TypeSpecifier*>{},
        .return_size      = 1,
        .return_types     = std::vector<TypeSpecifier*>{},
        .buildin_func_fix = fix_buildin_func_to_resume,
    },
    {
        .identifier       = "yield",
        .param_size       = 0,
        .param_types      = std::vector<TypeSpecifier*>{},
        .return_size      = 1,
        .return_types     = std::vector<TypeSpecifier*>{},
        .buildin_func_fix = fix_buildin_func_to_yield,
    },
};

// TODO: 统一检查参数类型, 统一检查参数数量
void check_build_func_param_num(Expression*             expression,
                                FunctionCallExpression* function_call_expression,
                                Block*                  block,
                                Function*               func,
                                Ring_Buildin_Func*      build_func) {

    unsigned int argument_list_size = function_call_expression->argument_list_size;


    // Ring-Compiler-Error-Report ERROR_ARGUMENT_MISMATCH_NUM
    if (argument_list_size != build_func->param_size) {
        DEFINE_ERROR_REPORT_STR;

        compile_err_buf = sprintf_string(
            "the buildin function `%s()` want %d arguments.; E:%d.",
            build_func->identifier,
            build_func->param_size,
            ERROR_ARGUMENT_MISMATCH_NUM);

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = get_package_unit(),
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(function_call_expression->line_number),
            .line_number             = function_call_expression->line_number,
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

void fix_buildin_func_len(Expression*             expression,
                          FunctionCallExpression* function_call_expression,
                          Block*                  block,
                          Function*               func,
                          Ring_Buildin_Func*      build_func) {

    check_build_func_param_num(expression, function_call_expression, block, (Function*)func, build_func);

    TypeSpecifier* array_type_specifier = function_call_expression->argument_list->expression->convert_type[0];

    // Ring-Compiler-Error-Report ERROR_ARGUMENT_MISMATCH_TYPE
    if (array_type_specifier->kind != RING_BASIC_TYPE_STRING
        && array_type_specifier->kind != RING_BASIC_TYPE_ARRAY) {
        DEFINE_ERROR_REPORT_STR;

        compile_err_buf = sprintf_string(
            "the buildin function `%s()` can only be applied to string or array; E:%d.",
            build_func->identifier,
            ERROR_ARGUMENT_MISMATCH_TYPE);
        compile_adv_buf = sprintf_string(
            "the aragument's type is '%s'.", format_type_specifier(array_type_specifier).c_str());

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = get_package_unit(),
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(function_call_expression->line_number),
            .line_number             = function_call_expression->line_number,
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
    extern TypeSpecifier int_type_specifier;
    EXPRESSION_ADD_CONVERT_TYPE(expression, &int_type_specifier);
}


void fix_buildin_func_capacity(Expression*             expression,
                               FunctionCallExpression* function_call_expression,
                               Block*                  block,
                               Function*               func,
                               Ring_Buildin_Func*      build_func) {

    check_build_func_param_num(expression, function_call_expression, block, (Function*)func, build_func);

    TypeSpecifier* array_type_specifier = function_call_expression->argument_list->expression->convert_type[0];

    // Ring-Compiler-Error-Report ERROR_ARGUMENT_MISMATCH_TYPE
    if (array_type_specifier->kind != RING_BASIC_TYPE_STRING
        && array_type_specifier->kind != RING_BASIC_TYPE_ARRAY) {
        DEFINE_ERROR_REPORT_STR;

        compile_err_buf = sprintf_string(
            "the buildin function `%s()` can only be applied to string or array; E:%d.",
            build_func->identifier,
            ERROR_ARGUMENT_MISMATCH_TYPE);
        compile_adv_buf = sprintf_string(
            "the aragument's type is '%s'.", format_type_specifier(array_type_specifier).c_str());

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = get_package_unit(),
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(function_call_expression->line_number),
            .line_number             = function_call_expression->line_number,
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
    extern TypeSpecifier int_type_specifier;
    EXPRESSION_ADD_CONVERT_TYPE(expression, &int_type_specifier);
}

void fix_buildin_func_push(Expression*             expression,
                           FunctionCallExpression* function_call_expression,
                           Block*                  block,
                           Function*               func,
                           Ring_Buildin_Func*      build_func) {

    check_build_func_param_num(expression, function_call_expression, block, (Function*)func, build_func);

    TypeSpecifier* array_type_specifier = function_call_expression->argument_list->expression->convert_type[0];

    // TODO: 这里的还应该有更详细的语法检测
    // push 的 第一个参数和第二个参数是否可以对比
    if (array_type_specifier->kind != RING_BASIC_TYPE_ARRAY) {
        DEFINE_ERROR_REPORT_STR;

        compile_err_buf = sprintf_string(
            "the buildin function `%s()` can only be applied to array; E:%d.",
            build_func->identifier,
            ERROR_ARGUMENT_MISMATCH_TYPE);
        compile_adv_buf = sprintf_string(
            "the aragument's type is '%s'.", format_type_specifier(array_type_specifier).c_str());

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = get_package_unit(),
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(function_call_expression->line_number),
            .line_number             = function_call_expression->line_number,
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

void fix_buildin_func_pop(Expression*             expression,
                          FunctionCallExpression* function_call_expression,
                          Block*                  block,
                          Function*               func,
                          Ring_Buildin_Func*      build_func) {

    check_build_func_param_num(expression, function_call_expression, block, (Function*)func, build_func);

    TypeSpecifier* array_type_specifier = function_call_expression->argument_list->expression->convert_type[0];

    // Ring-Compiler-Error-Report ERROR_ARGUMENT_MISMATCH_TYPE
    if (array_type_specifier->kind != RING_BASIC_TYPE_ARRAY) {
        DEFINE_ERROR_REPORT_STR;

        compile_err_buf = sprintf_string(
            "the buildin function `%s()` can only be applied to array; E:%d.",
            build_func->identifier,
            ERROR_ARGUMENT_MISMATCH_TYPE);
        compile_adv_buf = sprintf_string(
            "the aragument's type is '%s'.", format_type_specifier(array_type_specifier).c_str());

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = get_package_unit(),
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(function_call_expression->line_number),
            .line_number             = function_call_expression->line_number,
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
    EXPRESSION_ADD_CONVERT_TYPE(expression, (array_type_specifier->sub));
}

void fix_buildin_func_to_string(Expression*             expression,
                                FunctionCallExpression* function_call_expression,
                                Block*                  block,
                                Function*               func,
                                Ring_Buildin_Func*      build_func) {

    check_build_func_param_num(expression, function_call_expression, block, (Function*)func, build_func);

    TypeSpecifier* type_specifier = function_call_expression->argument_list->expression->convert_type[0];

    // Ring-Compiler-Error-Report ERROR_ARGUMENT_MISMATCH_TYPE
    if (type_specifier->kind != RING_BASIC_TYPE_BOOL
        && type_specifier->kind != RING_BASIC_TYPE_INT
        && type_specifier->kind != RING_BASIC_TYPE_INT64
        && type_specifier->kind != RING_BASIC_TYPE_DOUBLE) {
        DEFINE_ERROR_REPORT_STR;

        compile_err_buf = sprintf_string(
            "the buildin function `%s()` can only be applied to bool/int/int64/double; E:%d.",
            build_func->identifier,
            ERROR_ARGUMENT_MISMATCH_TYPE);
        compile_adv_buf = sprintf_string(
            "the aragument's type is '%s'.", format_type_specifier(type_specifier).c_str());

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = get_package_unit(),
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(function_call_expression->line_number),
            .line_number             = function_call_expression->line_number,
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
    extern TypeSpecifier string_type_specifier;
    EXPRESSION_ADD_CONVERT_TYPE(expression, &string_type_specifier);
}

void fix_buildin_func_to_int64(Expression*             expression,
                               FunctionCallExpression* function_call_expression,
                               Block*                  block,
                               Function*               func,
                               Ring_Buildin_Func*      build_func) {

    check_build_func_param_num(expression, function_call_expression, block, (Function*)func, build_func);

    TypeSpecifier* type_specifier = function_call_expression->argument_list->expression->convert_type[0];

    // Ring-Compiler-Error-Report ERROR_ARGUMENT_MISMATCH_TYPE
    if (type_specifier->kind != RING_BASIC_TYPE_INT) {
        DEFINE_ERROR_REPORT_STR;

        compile_err_buf = sprintf_string(
            "the buildin function `%s()` can only be applied to int; E:%d.",
            build_func->identifier,
            ERROR_ARGUMENT_MISMATCH_TYPE);
        compile_adv_buf = sprintf_string(
            "the aragument's type is '%s'.", format_type_specifier(type_specifier).c_str());

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = get_package_unit(),
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(function_call_expression->line_number),
            .line_number             = function_call_expression->line_number,
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
    extern TypeSpecifier int64_type_specifier;
    EXPRESSION_ADD_CONVERT_TYPE(expression, &int64_type_specifier);
}


void fix_buildin_func_to_resume(Expression*             expression,
                                FunctionCallExpression* function_call_expression,
                                Block*                  block,
                                Function*               func,
                                Ring_Buildin_Func*      build_func) {

    check_build_func_param_num(expression, function_call_expression, block, (Function*)func, build_func);

    TypeSpecifier* type_specifier = function_call_expression->argument_list->expression->convert_type[0];

    // Ring-Compiler-Error-Report ERROR_ARGUMENT_MISMATCH_TYPE
    if (type_specifier->kind != RING_BASIC_TYPE_INT64) {
        DEFINE_ERROR_REPORT_STR;

        compile_err_buf = sprintf_string(
            "the buildin function `%s()` can only be applied to int64; E:%d.",
            build_func->identifier,
            ERROR_ARGUMENT_MISMATCH_TYPE);
        compile_adv_buf = sprintf_string(
            "the aragument's type is '%s'.", format_type_specifier(type_specifier).c_str());

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = get_package_unit(),
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(function_call_expression->line_number),
            .line_number             = function_call_expression->line_number,
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
void fix_buildin_func_to_yield(Expression*             expression,
                               FunctionCallExpression* function_call_expression,
                               Block*                  block,
                               Function*               func,
                               Ring_Buildin_Func*      build_func) {

    check_build_func_param_num(expression, function_call_expression, block, (Function*)func, build_func);
}

// TODO:  需要优化一下
RING_BUILD_IN_FUNC_ID is_buildin_function_identifier(char* package_posit, char* identifier) {
    if (package_posit != nullptr) {
        return RING_BUILD_IN_FNC_UNKNOW;
    }

    if (str_eq(identifier, "len")) {
        return RING_BUILD_IN_FNC_LEN;
    } else if (str_eq(identifier, "capacity")) {
        return RING_BUILD_IN_FNC_CAPACITY;
    } else if (str_eq(identifier, "push")) {
        return RING_BUILD_IN_FNC_PUSH;
    } else if (str_eq(identifier, "pop")) {
        return RING_BUILD_IN_FNC_POP;
    } else if (str_eq(identifier, "to_string")) {
        return RING_BUILD_IN_FNC_TO_STRING;
    } else if (str_eq(identifier, "to_int64")) {
        return RING_BUILD_IN_FNC_TO_INT64;
    } else if (str_eq(identifier, "resume")) {
        return RING_BUILD_IN_FNC_RESUME;
    } else if (str_eq(identifier, "yield")) {
        return RING_BUILD_IN_FNC_YIELD;
    }

    return RING_BUILD_IN_FNC_UNKNOW;
}

void fix_buildin_func(Expression*             expression,
                      FunctionCallExpression* function_call_expression,
                      Block*                  block,
                      FunctionTuple*          func) {

    RING_BUILD_IN_FUNC_ID    func_id = is_buildin_function_identifier(function_call_expression->package_posit, function_call_expression->func_identifier);

    extern Ring_Buildin_Func Ring_Buildin_Funcs[];
    Ring_Buildin_Func        build_func = Ring_Buildin_Funcs[func_id];

    build_func.buildin_func_fix(expression,
                                function_call_expression,
                                block,
                                (Function*)func,
                                &build_func);
}
