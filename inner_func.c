#include <stdio.h>
#include <stdlib.h>
#include "ring.h"
#include "inner_func.h"

void register_inner_func(Ring_Interpreter *ring_interpreter) {
    char *    identifier;
    Function *function;

    identifier = "print";
    function   = malloc(sizeof(Function));

    function->function_name = identifier;
    function->inner_func    = ring_inner_func_print;
    function->next          = NULL;

    ring_interpreter->function_list = function;
}

void ring_inner_func_print(int argc, Expression *expression) {
#ifdef DEBUG
    printf("[DEBUG][inner_func.c][function:ring_inner_func_print]\t argc(%d)\n", argc);
#endif

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
