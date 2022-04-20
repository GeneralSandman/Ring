#include "inner_func.h"
#include "ring.h"
#include <stdio.h>
#include <stdlib.h>


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
