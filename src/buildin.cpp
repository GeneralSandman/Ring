#include "ring.hpp"
#include <cassert>


Ring_Buildin_Func Ring_Buildin_Funcs[] = {
    {
        .identifier            = "-",
        .param_size            = 0,
        .param_types           = std::vector<TypeSpecifier*>{},
        .return_size           = 0,
        .return_types          = std::vector<TypeSpecifier*>{},
        .buildin_func_fix      = nullptr,
        .buildin_func_generate = nullptr,
    },
    {
        .identifier            = "len",
        .param_size            = 1,
        .param_types           = std::vector<TypeSpecifier*>{},
        .return_size           = 1,
        .return_types          = std::vector<TypeSpecifier*>{},
        .buildin_func_fix      = fix_buildin_func_len,
        .buildin_func_generate = generate_buildin_func_len,
    },
    {
        .identifier            = "capacity",
        .param_size            = 1,
        .param_types           = std::vector<TypeSpecifier*>{},
        .return_size           = 1,
        .return_types          = std::vector<TypeSpecifier*>{},
        .buildin_func_fix      = fix_buildin_func_capacity,
        .buildin_func_generate = generate_buildin_func_capacity,
    },
    {
        .identifier            = "push",
        .param_size            = 2,
        .param_types           = std::vector<TypeSpecifier*>{},
        .return_size           = 0,
        .return_types          = std::vector<TypeSpecifier*>{},
        .buildin_func_fix      = fix_buildin_func_push,
        .buildin_func_generate = generate_buildin_func_push,
    },
    {
        .identifier            = "pop",
        .param_size            = 1,
        .param_types           = std::vector<TypeSpecifier*>{},
        .return_size           = 0,
        .return_types          = std::vector<TypeSpecifier*>{},
        .buildin_func_fix      = fix_buildin_func_pop,
        .buildin_func_generate = generate_buildin_func_pop,
    },
    {
        .identifier            = "to_string",
        .param_size            = 1,
        .param_types           = std::vector<TypeSpecifier*>{},
        .return_size           = 1,
        .return_types          = std::vector<TypeSpecifier*>{},
        .buildin_func_fix      = fix_buildin_func_to_string,
        .buildin_func_generate = generate_buildin_func_to_string,
    },
    {
        .identifier            = "to_int64",
        .param_size            = 1,
        .param_types           = std::vector<TypeSpecifier*>{},
        .return_size           = 1,
        .return_types          = std::vector<TypeSpecifier*>{},
        .buildin_func_fix      = fix_buildin_func_to_int64,
        .buildin_func_generate = generate_buildin_func_to_int64,
    },
    {
        .identifier            = "resume",
        .param_size            = 1,
        .param_types           = std::vector<TypeSpecifier*>{},
        .return_size           = 1,
        .return_types          = std::vector<TypeSpecifier*>{},
        .buildin_func_fix      = fix_buildin_func_to_resume,
        .buildin_func_generate = generate_buildin_func_resume,
    },
    {
        .identifier            = "yield",
        .param_size            = 0,
        .param_types           = std::vector<TypeSpecifier*>{},
        .return_size           = 1,
        .return_types          = std::vector<TypeSpecifier*>{},
        .buildin_func_fix      = fix_buildin_func_to_yield,
        .buildin_func_generate = generate_buildin_func_yield,
    },
};

// 统一检查参数类型, 统一检查参数数量
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

unsigned int is_buildin_function_identifier(char* package_posit, char* identifier) {
    if (package_posit != nullptr) {
        return 0;
    }

    unsigned int size = sizeof(Ring_Buildin_Funcs) / sizeof(Ring_Buildin_Func);
    for (unsigned int i = 1; i < size; i++) {
        if (str_eq(Ring_Buildin_Funcs[i].identifier, identifier)) {
            return i;
        }
    }

    return 0;
}

void fix_buildin_func(Expression*             expression,
                      FunctionCallExpression* function_call_expression,
                      Block*                  block,
                      FunctionTuple*          func) {

    unsigned int      func_id    = is_buildin_function_identifier(function_call_expression->package_posit,
                                                                  function_call_expression->func_identifier);

    Ring_Buildin_Func build_func = Ring_Buildin_Funcs[func_id];

    build_func.buildin_func_fix(expression,
                                function_call_expression,
                                block,
                                (Function*)func,
                                &build_func);
}

void generate_vmcode_buildin_func(Package_Executer*       executer,
                                  FunctionCallExpression* function_call_expression,
                                  RVM_OpcodeBuffer*       opcode_buffer) {

    unsigned int      func_id    = is_buildin_function_identifier(function_call_expression->package_posit,
                                                                  function_call_expression->func_identifier);

    Ring_Buildin_Func build_func = Ring_Buildin_Funcs[func_id];

    build_func.buildin_func_generate(executer,
                                     function_call_expression,
                                     opcode_buffer);
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

    TypeSpecifier* array_type_specifier   = function_call_expression->argument_list->expression->convert_type[0];
    TypeSpecifier* item_type_specifier    = function_call_expression->argument_list->next->expression->convert_type[0];

    std::string    array_type_specifier_s = format_type_specifier(array_type_specifier);
    std::string    item_type_specifier_s  = format_type_specifier(item_type_specifier);


    // 1. 第一个参数必须为数组
    // Ring-Compiler-Error-Report ERROR_ARGUMENT_MISMATCH_TYPE
    if (array_type_specifier->kind != RING_BASIC_TYPE_ARRAY) {
        DEFINE_ERROR_REPORT_STR;

        compile_err_buf = sprintf_string(
            "`%s()` first argument is (%s), not array; E:%d.",
            build_func->identifier,
            array_type_specifier_s.c_str(),
            ERROR_ARGUMENT_MISMATCH_TYPE);
        compile_adv_buf = sprintf_string(
            "the aragument's type is '%s'.", array_type_specifier_s.c_str());

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

    // 2. 第一个参数必须要比第二个参数大一个维度，并且sub是同类型
    if (item_type_specifier->kind == RING_BASIC_TYPE_ARRAY) {

        // TODO: 后续放开多维数组
        goto ERROR_REPORT;
        if (!comp_type_specifier(array_type_specifier->u.array_t->sub,
                                 item_type_specifier->u.array_t->sub)) {
            goto ERROR_REPORT;
        }
        if (array_type_specifier->u.array_t->dimension != item_type_specifier->u.array_t->dimension + 1) {
            goto ERROR_REPORT;
        }
    } else {
        if (!comp_type_specifier(array_type_specifier->u.array_t->sub,
                                 item_type_specifier)) {
            goto ERROR_REPORT;
        }
    }

    return;

ERROR_REPORT:
    // Ring-Compiler-Error-Report ERROR_ARGUMENT_MISMATCH_TYPE
    {
        DEFINE_ERROR_REPORT_STR;

        compile_err_buf = sprintf_string(
            "`%s()` first(%s) and second(%s) argument type not match; E:%d.",
            build_func->identifier,
            array_type_specifier_s.c_str(),
            item_type_specifier_s.c_str(),
            ERROR_ARGUMENT_MISMATCH_TYPE);

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
    EXPRESSION_ADD_CONVERT_TYPE(expression, (array_type_specifier->u.array_t->sub));
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


void generate_buildin_func_len(Package_Executer*       executer,
                               FunctionCallExpression* function_call_expression,
                               RVM_OpcodeBuffer*       opcode_buffer) {

    TypeSpecifier* type_specifier = function_call_expression->argument_list->expression->convert_type[0];
    assert(type_specifier->kind == RING_BASIC_TYPE_STRING
           || type_specifier->kind == RING_BASIC_TYPE_ARRAY);

    // push arguments
    for (ArgumentList* pos = function_call_expression->argument_list;
         pos != nullptr;
         pos = pos->next) {
        generate_vmcode_from_expression(executer, pos->expression, opcode_buffer);
    }

    RVM_Opcode opcode = RVM_CODE_UNKNOW;
    if (type_specifier->kind == RING_BASIC_TYPE_STRING) {
        opcode = RVM_CODE_PUSH_STRING_LEN;
    } else if (type_specifier->kind == RING_BASIC_TYPE_ARRAY) {
        opcode = RVM_CODE_PUSH_ARRAY_LEN;
    }
    generate_vmcode(executer, opcode_buffer, opcode, 0, function_call_expression->line_number);
}

void generate_buildin_func_capacity(Package_Executer*       executer,
                                    FunctionCallExpression* function_call_expression,
                                    RVM_OpcodeBuffer*       opcode_buffer) {

    TypeSpecifier* type_specifier = function_call_expression->argument_list->expression->convert_type[0];
    assert(type_specifier->kind == RING_BASIC_TYPE_STRING
           || type_specifier->kind == RING_BASIC_TYPE_ARRAY);

    // push arguments
    for (ArgumentList* pos = function_call_expression->argument_list;
         pos != nullptr;
         pos = pos->next) {
        generate_vmcode_from_expression(executer, pos->expression, opcode_buffer);
    }

    RVM_Opcode opcode = RVM_CODE_UNKNOW;
    if (type_specifier->kind == RING_BASIC_TYPE_STRING) {
        opcode = RVM_CODE_PUSH_STRING_CAPACITY;
    } else if (type_specifier->kind == RING_BASIC_TYPE_ARRAY) {
        opcode = RVM_CODE_PUSH_ARRAY_CAPACITY;
    }
    generate_vmcode(executer, opcode_buffer, opcode, 0, function_call_expression->line_number);
}

void generate_buildin_func_push(Package_Executer*       executer,
                                FunctionCallExpression* function_call_expression,
                                RVM_OpcodeBuffer*       opcode_buffer) {


    TypeSpecifier* type_specifier = function_call_expression->argument_list->expression->convert_type[0];
    assert(type_specifier->kind == RING_BASIC_TYPE_ARRAY);

    // push arguments
    for (ArgumentList* pos = function_call_expression->argument_list;
         pos != nullptr;
         pos = pos->next) {
        generate_vmcode_from_expression(executer, pos->expression, opcode_buffer);
    }


    RVM_Opcode opcode = RVM_CODE_UNKNOW;
    switch (type_specifier->u.array_t->sub->kind) {
    case RING_BASIC_TYPE_BOOL: opcode = RVM_CODE_ARRAY_APPEND_BOOL; break;
    case RING_BASIC_TYPE_INT: opcode = RVM_CODE_ARRAY_APPEND_INT; break;
    case RING_BASIC_TYPE_INT64: opcode = RVM_CODE_ARRAY_APPEND_INT64; break;
    case RING_BASIC_TYPE_DOUBLE: opcode = RVM_CODE_ARRAY_APPEND_DOUBLE; break;
    case RING_BASIC_TYPE_STRING: opcode = RVM_CODE_ARRAY_APPEND_STRING; break;
    case RING_BASIC_TYPE_CLASS: opcode = RVM_CODE_ARRAY_APPEND_CLASS_OB; break;
    case RING_BASIC_TYPE_FUNC: opcode = RVM_CODE_ARRAY_APPEND_CLOSURE; break;
    default: ring_error_report("error: push() is only be used by bool[] int[] int64[] double[] string[] class[] fn[]\n");
    }
    generate_vmcode(executer, opcode_buffer, opcode, 0, function_call_expression->line_number);
}

void generate_buildin_func_pop(Package_Executer*       executer,
                               FunctionCallExpression* function_call_expression,
                               RVM_OpcodeBuffer*       opcode_buffer) {

    TypeSpecifier* type_specifier = function_call_expression->argument_list->expression->convert_type[0];
    assert(type_specifier->kind == RING_BASIC_TYPE_ARRAY);

    // push arguments
    for (ArgumentList* pos = function_call_expression->argument_list;
         pos != nullptr;
         pos = pos->next) {
        generate_vmcode_from_expression(executer, pos->expression, opcode_buffer);
    }

    RVM_Opcode opcode = RVM_CODE_UNKNOW;
    switch (type_specifier->u.array_t->sub->kind) {
    case RING_BASIC_TYPE_BOOL: opcode = RVM_CODE_ARRAY_POP_BOOL; break;
    case RING_BASIC_TYPE_INT: opcode = RVM_CODE_ARRAY_POP_INT; break;
    case RING_BASIC_TYPE_INT64: opcode = RVM_CODE_ARRAY_POP_INT64; break;
    case RING_BASIC_TYPE_DOUBLE: opcode = RVM_CODE_ARRAY_POP_DOUBLE; break;
    case RING_BASIC_TYPE_STRING: opcode = RVM_CODE_ARRAY_POP_STRING; break;
    case RING_BASIC_TYPE_CLASS: opcode = RVM_CODE_ARRAY_POP_CLASS_OB; break;
    case RING_BASIC_TYPE_FUNC: opcode = RVM_CODE_ARRAY_POP_CLOSURE; break;
    default: ring_error_report("error: pop() is only be used by bool[] int[] int64[] double[] string[] class[] fn[]\n");
    }
    generate_vmcode(executer, opcode_buffer, opcode, 0, function_call_expression->line_number);
}

void generate_buildin_func_to_string(Package_Executer*       executer,
                                     FunctionCallExpression* function_call_expression,
                                     RVM_OpcodeBuffer*       opcode_buffer) {

    TypeSpecifier* type_specifier = function_call_expression->argument_list->expression->convert_type[0];
    assert(type_specifier->kind == RING_BASIC_TYPE_BOOL
           || type_specifier->kind == RING_BASIC_TYPE_INT
           || type_specifier->kind == RING_BASIC_TYPE_INT64
           || type_specifier->kind == RING_BASIC_TYPE_DOUBLE);

    // push arguments
    for (ArgumentList* pos = function_call_expression->argument_list;
         pos != nullptr;
         pos = pos->next) {
        generate_vmcode_from_expression(executer, pos->expression, opcode_buffer);
    }

    RVM_Opcode opcode = RVM_CODE_UNKNOW;
    switch (type_specifier->kind) {
    case RING_BASIC_TYPE_BOOL: opcode = RVM_CODE_BOOL_2_STRING; break;
    case RING_BASIC_TYPE_INT: opcode = RVM_CODE_INT_2_STRING; break;
    case RING_BASIC_TYPE_INT64: opcode = RVM_CODE_INT64_2_STRING; break;
    case RING_BASIC_TYPE_DOUBLE: opcode = RVM_CODE_DOUBLE_2_STRING; break;
    default: ring_error_report("error: to_string() only be used by bool/int/double\n");
    }
    generate_vmcode(executer, opcode_buffer, opcode, 0, function_call_expression->line_number);
}

void generate_buildin_func_to_int64(Package_Executer*       executer,
                                    FunctionCallExpression* function_call_expression,
                                    RVM_OpcodeBuffer*       opcode_buffer) {

    TypeSpecifier* type_specifier = function_call_expression->argument_list->expression->convert_type[0];
    assert(type_specifier->kind == RING_BASIC_TYPE_INT);

    // push arguments
    for (ArgumentList* pos = function_call_expression->argument_list;
         pos != nullptr;
         pos = pos->next) {
        generate_vmcode_from_expression(executer, pos->expression, opcode_buffer);
    }


    generate_vmcode(executer, opcode_buffer, RVM_CODE_INT_2_INT64, 0, function_call_expression->line_number);
}

void generate_buildin_func_resume(Package_Executer*       executer,
                                  FunctionCallExpression* function_call_expression,
                                  RVM_OpcodeBuffer*       opcode_buffer) {

    TypeSpecifier* type_specifier = function_call_expression->argument_list->expression->convert_type[0];
    assert(type_specifier->kind == RING_BASIC_TYPE_INT64);

    // push arguments
    for (ArgumentList* pos = function_call_expression->argument_list;
         pos != nullptr;
         pos = pos->next) {
        generate_vmcode_from_expression(executer, pos->expression, opcode_buffer);
    }

    generate_vmcode(executer, opcode_buffer, RVM_CODE_RESUME, 0, function_call_expression->line_number);
}

void generate_buildin_func_yield(Package_Executer*       executer,
                                 FunctionCallExpression* function_call_expression,
                                 RVM_OpcodeBuffer*       opcode_buffer) {

    generate_vmcode(executer, opcode_buffer, RVM_CODE_YIELD, 0, function_call_expression->line_number);
}