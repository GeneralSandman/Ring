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
        .identifier       = "launch",
        .param_size       = 1,
        .param_types      = std::vector<TypeSpecifier*>{},
        .return_size      = 1,
        .return_types     = std::vector<TypeSpecifier*>{},
        .buildin_func_fix = fix_buildin_func_to_launch,
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
        .param_size       = 1,
        .param_types      = std::vector<TypeSpecifier*>{},
        .return_size      = 1,
        .return_types     = std::vector<TypeSpecifier*>{},
        .buildin_func_fix = fix_buildin_func_to_yield,
    },
};

void fix_buildin_func_len(Expression*             expression,
                          FunctionCallExpression* function_call_expression,
                          Block*                  block,
                          Function*               func) {

    TypeSpecifier* array_type_specifier = function_call_expression->argument_list->expression->convert_type[0];
    if (array_type_specifier->kind != RING_BASIC_TYPE_STRING
        && array_type_specifier->kind != RING_BASIC_TYPE_ARRAY) {
        // TODO:
        // Ring-Compiler-Error-Report pop array
        ring_error_report("only len string/array");
    }

    EXPRESSION_CLEAR_CONVERT_TYPE(expression);
    extern TypeSpecifier int_type_specifier;
    EXPRESSION_ADD_CONVERT_TYPE(expression, &int_type_specifier);
}


void fix_buildin_func_capacity(Expression*             expression,
                               FunctionCallExpression* function_call_expression,
                               Block*                  block,
                               Function*               func) {

    TypeSpecifier* array_type_specifier = function_call_expression->argument_list->expression->convert_type[0];
    if (array_type_specifier->kind != RING_BASIC_TYPE_STRING
        && array_type_specifier->kind != RING_BASIC_TYPE_ARRAY) {
        // TODO:
        // Ring-Compiler-Error-Report pop array
        ring_error_report("only len string/array");
    }

    EXPRESSION_CLEAR_CONVERT_TYPE(expression);
    extern TypeSpecifier int_type_specifier;
    EXPRESSION_ADD_CONVERT_TYPE(expression, &int_type_specifier);
}

void fix_buildin_func_push(Expression*             expression,
                           FunctionCallExpression* function_call_expression,
                           Block*                  block,
                           Function*               func) {

    TypeSpecifier* array_type_specifier = function_call_expression->argument_list->expression->convert_type[0];

    if (array_type_specifier->kind != RING_BASIC_TYPE_ARRAY) {
        // TODO:
        // Ring-Compiler-Error-Report pop array
        ring_error_report("only pop a array");
    }
}

void fix_buildin_func_pop(Expression*             expression,
                          FunctionCallExpression* function_call_expression,
                          Block*                  block,
                          Function*               func) {

    TypeSpecifier* array_type_specifier = function_call_expression->argument_list->expression->convert_type[0];

    if (array_type_specifier->kind != RING_BASIC_TYPE_ARRAY) {
        // TODO:
        // Ring-Compiler-Error-Report pop array
        ring_error_report("only pop a array");
    }
    EXPRESSION_CLEAR_CONVERT_TYPE(expression);
    EXPRESSION_ADD_CONVERT_TYPE(expression, (array_type_specifier->sub));
}

void fix_buildin_func_to_string(Expression*             expression,
                                FunctionCallExpression* function_call_expression,
                                Block*                  block,
                                Function*               func) {

    EXPRESSION_CLEAR_CONVERT_TYPE(expression);
    extern TypeSpecifier string_type_specifier;
    EXPRESSION_ADD_CONVERT_TYPE(expression, &string_type_specifier);
}

void fix_buildin_func_to_int64(Expression*             expression,
                               FunctionCallExpression* function_call_expression,
                               Block*                  block,
                               Function*               func) {

    TypeSpecifier* type_specifier = function_call_expression->argument_list->expression->convert_type[0];

    if (type_specifier->kind != RING_BASIC_TYPE_INT) {
        // TODO:
        // Ring-Compiler-Error-Report pop array
        ring_error_report("only apply int to to_int64()");
    }

    EXPRESSION_CLEAR_CONVERT_TYPE(expression);
    extern TypeSpecifier int64_type_specifier;
    EXPRESSION_ADD_CONVERT_TYPE(expression, &int64_type_specifier);
}

void fix_buildin_func_to_launch(Expression*             expression,
                                FunctionCallExpression* function_call_expression,
                                Block*                  block,
                                Function*               func) {

    TypeSpecifier* type_specifier = function_call_expression->argument_list->expression->convert_type[0];

    if (type_specifier->kind != RING_BASIC_TYPE_FUNC) {
        // TODO:
        // Ring-Compiler-Error-Report pop array
        ring_error_report("only apply a function to launch()");
    }

    EXPRESSION_CLEAR_CONVERT_TYPE(expression);
    extern TypeSpecifier int64_type_specifier;
    EXPRESSION_ADD_CONVERT_TYPE(expression, &int64_type_specifier);
}

void fix_buildin_func_to_resume(Expression*             expression,
                                FunctionCallExpression* function_call_expression,
                                Block*                  block,
                                Function*               func) {
}
void fix_buildin_func_to_yield(Expression*             expression,
                               FunctionCallExpression* function_call_expression,
                               Block*                  block,
                               Function*               func) {
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
    } else if (str_eq(identifier, "launch")) {
        return RING_BUILD_IN_FNC_LAUNCH;
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
    Ring_Buildin_Funcs[func_id].buildin_func_fix(expression, function_call_expression, block, (Function*)func);
}
