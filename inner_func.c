#include <stdio.h>
#include <stdlib.h>
#include "ring.h"
#include "inner_func.h"

void register_inner_func(Ring_Interpreter *ring_interpreter) {
    Function *function;

    function = malloc(sizeof(Function));

    function->line_number         = get_ring_interpreter_line_number();
    function->function_name       = "print";
    function->type                = FUNCTION_TYPE_INNER_LIB;
    function->parameter_list_size = 0;
    function->parameter_list      = NULL;
    function->block_size          = 0;
    function->block               = NULL;
    function->inner_func          = ring_inner_func_print;
    function->next                = NULL;

    ring_interpreter->function_list = function;
}

void ring_inner_func_print(int argc, Expression *expression) {
    debug_log_with_blue_coloar("\t argc(%d)", argc);
    if (argc != 1) {
        printf("error\n");
        exit(1);
    }

    // TODO: 实现更多类型的打印

    Ring_BasicValue *result;

    result = interpret_expression(expression);
    if (result == NULL) {
        printf("error\n");
        exit(1);
    }

    switch (result->type) {
    case BASICVALUE_TYPE_INT:
        printf("%d", result->u.int_value);
        break;

    case BASICVALUE_TYPE_DOUBLE:
        printf("%lf", result->u.double_value);
        break;

    case BASICVALUE_TYPE_STRING:
        printf("%s", result->u.string_value);
        break;

    default:
        break;
    }
}
