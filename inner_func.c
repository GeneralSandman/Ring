#include "inner_func.h"
#include "ring.h"
#include <stdio.h>
#include <stdlib.h>

void register_inner_func(Ring_Compiler* ring_compiler) {
    Function* function;

    function = malloc(sizeof(Function));

    function->line_number         = get_ring_compiler_line_number();
    function->function_name       = "print";
    function->type                = FUNCTION_TYPE_INNER_LIB;
    function->parameter_list_size = 0;
    function->parameter_list      = NULL;
    function->block_size          = 0;
    function->block               = NULL;
    function->inner_func          = ring_inner_func_print;
    function->next                = NULL;

    ring_compiler->function_list = function;
    ring_compiler->function_list_size++;
}

void ring_inner_func_print1(int argc, Ring_BasicValue* value) {
    debug_log_with_blue_coloar("\t argc(%d)", argc);
    if (argc != 1) {
        printf("error\n");
        exit(1);
    }

    // TODO: 实现更多类型的打印

    // Ring_BasicValue *result;

    // result = interpret_expression(expression, NULL);
    // if (result == NULL) {
    //     printf("error\n");
    //     exit(1);
    // }

    switch (value->type) {
    case BASICVALUE_TYPE_BOOL:
        if (value->u.bool_value == BOOL_FALSE)
            printf("%s", "false");
        else if (value->u.bool_value == BOOL_TRUE)
            printf("%s", "true");
        break;

    case BASICVALUE_TYPE_INT:
        printf("%d", value->u.int_value);
        break;

    case BASICVALUE_TYPE_DOUBLE:
        printf("%lf", value->u.double_value);
        break;

    case BASICVALUE_TYPE_STRING:
        printf("%s", value->u.string_value);
        break;

    default:
        break;
    }
}

void ring_inner_func_print(int argc, Ring_BasicValue** values) {
    debug_log_with_blue_coloar("\t argc(%d)", argc);

    for (int i = 0; i < argc; i++) {
        Ring_BasicValue* value = values[i];
        switch (value->type) {
        case BASICVALUE_TYPE_BOOL:
            if (value->u.bool_value == BOOL_FALSE)
                printf("%s", "false");
            else if (value->u.bool_value == BOOL_TRUE)
                printf("%s", "true");
            break;

        case BASICVALUE_TYPE_INT:
            printf("%d", value->u.int_value);
            break;

        case BASICVALUE_TYPE_DOUBLE:
            printf("%lf", value->u.double_value);
            break;

        case BASICVALUE_TYPE_STRING:
            printf("%s", value->u.string_value);
            break;

        default:
            break;
        }
    }
}
