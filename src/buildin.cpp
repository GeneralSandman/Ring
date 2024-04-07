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
};

void fix_buildin_func_len(Expression*             expression,
                          FunctionCallExpression* function_call_expression,
                          Block*                  block,
                          Function*               func) {

    TypeSpecifier* array_type_specifier = function_call_expression->argument_list->expression->convert_type[0];
    if (array_type_specifier->kind != RING_BASIC_TYPE_STRING
        && array_type_specifier->kind != RING_BASIC_TYPE_ARRAY) {
        // TODO:
        // Ring-Compiler-Error-Report  pop array
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
        // Ring-Compiler-Error-Report  pop array
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
        // Ring-Compiler-Error-Report  pop array
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
        // Ring-Compiler-Error-Report  pop array
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
    }

    return RING_BUILD_IN_FNC_UNKNOW;
}

void fix_buildin_func(Expression*             expression,
                      FunctionCallExpression* function_call_expression,
                      Block*                  block,
                      Function*               func) {

    RING_BUILD_IN_FUNC_ID    func_id = is_buildin_function_identifier(function_call_expression->package_posit, function_call_expression->func_identifier);

    extern Ring_Buildin_Func Ring_Buildin_Funcs[];
    Ring_Buildin_Funcs[func_id].buildin_func_fix(expression, function_call_expression, block, func);
}
