#include "ring.h"

void register_lib(Package_Executer* package_executer, char* func_name, RVM_NativeFuncProc* func_proc, int arg_count) {
    debug_log_with_white_coloar("\t");

    for (int i = 0; i < package_executer->function_size; i++) {
        RVM_Function* function = &package_executer->function_list[i];
        if (function->type == RVM_FUNCTION_TYPE_NATIVE && 0 == strcmp(function->func_name, func_name)) {
            function->u.native_func            = (NativeFunction*)malloc(sizeof(NativeFunction));
            function->u.native_func->func_proc = func_proc;
            function->u.native_func->arg_count = arg_count;
        }
    }
}

// ------------------ std fmt ------------------
// std_fmt_lib_println_bool
// std_fmt_lib_println_int
// std_fmt_lib_println_double
// std_fmt_lib_println_string

RVM_Value std_fmt_lib_println_bool(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    debug_log_with_white_coloar("\t");

    if (arg_count != 1) {
        printf("native_proc_print only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    RVM_Value ret;
    ret.u.int_value = 0;

    if (args->u.int_value) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    fflush(stdout);

    return ret;
}

RVM_Value std_fmt_lib_println_int(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    debug_log_with_white_coloar("\t");

    if (arg_count != 1) {
        printf("native_proc_print only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    RVM_Value ret;
    ret.u.int_value = 0;

    // TODO: 暂时只打印int, 以后都强制转换成int_value
    printf("%d\n", args->u.int_value);
    fflush(stdout);

    return ret;
}

RVM_Value std_fmt_lib_println_double(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    debug_log_with_white_coloar("\t");

    if (arg_count != 1) {
        printf("native_proc_print only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    RVM_Value ret;
    ret.u.int_value = 0;

    printf("%f\n", args->u.double_value);
    fflush(stdout);

    return ret;
}

RVM_Value std_fmt_lib_println_string(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    debug_log_with_white_coloar("\t");

    if (arg_count != 1) {
        printf("native_proc_print only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    RVM_Value ret;
    ret.u.int_value = 0;

    if (args->u.object == NULL || args->u.object->u.string.data == NULL) {
        printf("\n");
    } else {
        printf("%s\n", args->u.object->u.string.data);
    }
    fflush(stdout);

    return ret;
}

// ------------------ std debug ------------------
// std_debug_lib_debug_assert

RVM_Value std_debug_lib_debug_assert(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    debug_log_with_white_coloar("\t");

    if (arg_count != 1) {
        printf("native_proc_print only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    RVM_Value ret;
    ret.u.int_value = 0;

    if (args->u.int_value) {
        printf("debug_assert PASS\n");
    } else {
        printf("debug_assert FAILED\n");
    }
    fflush(stdout);

    return ret;
}

// ------------------ std math ------------------
// std_math_lib_sqrt

RVM_Value std_math_lib_sqrt(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    debug_log_with_white_coloar("\t");

    // if (arg_count != 1) {
    //     printf("native_proc_print only one arguement\n");
    //     exit(ERROR_CODE_RUN_VM_ERROR);
    // }

    RVM_Value ret;
    ret.u.int_value = 0;

    // if (args->u.int_value) {
    //     printf("debug_assert PASS\n");
    // } else {
    //     printf("debug_assert FAILED\n");
    // }
    // fflush(stdout);

    return ret;
}