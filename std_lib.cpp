#include "ring.h"
#include <vector>

/*
make install 安装标准库
/usr/local/ring/std/ 为默认标准库的安装路径

通过 更改Makefile 编译宏 来控制调试标准库
RING_PACKAGE_STD_PAHT_FMT 即为调试标准库路径
RING_PACKAGE_STD_PATH_DEBUG 即为调试标准库路径
*/
#ifdef DEBUG_STD_LIB
char RING_PACKAGE_STD_PAHT_FMT[]   = "/Users/bytedance/Desktop/Ring/std/fmt/";
char RING_PACKAGE_STD_PATH_DEBUG[] = "/Users/bytedance/Desktop/Ring/std/debug/";
#else
char RING_PACKAGE_STD_PAHT_FMT[]   = "/usr/local/ring/std/fmt/";
char RING_PACKAGE_STD_PATH_DEBUG[] = "/usr/local/ring/std/debug/";
#endif

std::vector<StdPackageInfo> Std_Lib_List = {
    {
        (char*)"fmt",
        RING_PACKAGE_STD_PAHT_FMT,
        std::vector<StdPackageNativeFunction>{
            {(char*)"println_bool", std_fmt_lib_println_bool, 1},
            {(char*)"println_int", std_fmt_lib_println_int, 1},
            {(char*)"println_double", std_fmt_lib_println_double, 1},
            {(char*)"println_string", std_fmt_lib_println_string, 1},
        },
    },

    {
        (char*)"debug",
        RING_PACKAGE_STD_PATH_DEBUG,
        std::vector<StdPackageNativeFunction>{
            {(char*)"debug_assert", std_debug_lib_debug_assert, 1},
        },
    },
};

void compile_std_lib(CompilerEntry* compiler_entry, ExecuterEntry* executer_entry) {
    for (StdPackageInfo std_package_info : Std_Lib_List) {
        char* package_name = std_package_info.package_name;
        char* package_path = std_package_info.path;

        // 编译
        if (nullptr != search_package(compiler_entry, package_name)) {
            debug_log_with_yellow_coloar("\t package[%s] already compiled", package_name);
            continue;
        }
        Package* std_package       = package_create(compiler_entry, package_name, package_path);
        std_package->package_index = compiler_entry->package_list.size(); // TODO: 这个应该在 fix的时候 设置
        package_compile(std_package);

        // 生成代码
        Package_Executer* package_executer = package_executer_create(executer_entry, std_package->package_name);
        ring_generate_vm_code(std_package, package_executer);
        executer_entry->package_executer_list.push_back(package_executer);

        // 注册native function
        for (StdPackageNativeFunction native_function : std_package_info.native_function_list) {
            register_lib(package_executer, native_function.func_name, native_function.func_proc, native_function.arg_count);
        }
    }
}

void register_lib(Package_Executer* package_executer, char* func_name, RVM_NativeFuncProc* func_proc, int arg_count) {
    debug_log_with_white_coloar("\t func_name:%s", func_name);

    for (int i = 0; i < package_executer->function_size; i++) {
        RVM_Function* function = &package_executer->function_list[i];
        if (function->type == RVM_FUNCTION_TYPE_NATIVE && 0 == strcmp(function->func_name, func_name)) {
            debug_log_with_white_coloar("\t func_name:%s register succ", func_name);

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
        printf("std_fmt_lib_println_bool only one arguement\n");
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
        printf("std_fmt_lib_println_int only one arguement\n");
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
        printf("std_fmt_lib_println_double only one arguement\n");
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
        printf("std_fmt_lib_println_string only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    RVM_Value ret;
    ret.u.int_value = 0;

    if (args->u.object == nullptr || args->u.object->u.string.data == nullptr) {
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
        printf("std_debug_lib_debug_assert only one arguement\n");
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


// RVM_Value native_proc_print(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
//     debug_log_with_white_coloar("\t");

//     RVM_Value ret;
//     ret.u.int_value = 0;

//     for (unsigned int i = 0; i < arg_count; i++) {
//         switch (args[i].type) {
//         case RVM_VALUE_TYPE_BOOL:
//             if (args[i].u.int_value) {
//                 printf("true");
//             } else {
//                 printf("false");
//             }
//             break;
//         case RVM_VALUE_TYPE_INT:
//             printf("%d", args[i].u.int_value);
//             break;
//         case RVM_VALUE_TYPE_DOUBLE:
//             printf("%f", args[i].u.double_value);
//             break;
//         case RVM_VALUE_TYPE_STRING:
//             if (args[i].u.object == nullptr || args[i].u.object->u.string.data == nullptr) {
//                 printf("");
//             } else {
//                 printf("%s", args[i].u.object->u.string.data);
//             }
//             break;
//         default:
//             break;
//         }
//         if (i < arg_count - 1)
//             printf(" ");
//     }


//     return ret;
// }

// RVM_Value native_proc_println(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
//     debug_log_with_white_coloar("\t");

//     RVM_Value ret;
//     ret.u.int_value = 0;

//     native_proc_print(rvm, arg_count, args);
//     printf("\n");

//     return ret;
// }

// RVM_Value native_proc_printf(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
//     debug_log_with_white_coloar("\t");

//     RVM_Value ret;
//     ret.u.int_value = 0;

//     assert(args[0].type == RVM_VALUE_TYPE_STRING);

//     char*        format     = args[0].u.object->u.string.data;
//     size_t       length     = strlen(format);
//     unsigned int args_index = 1;

//     // printf("format:%s\n", format);
//     // printf("length:%ld\n", length);


//     for (size_t i = 0; i < length;) {
//         size_t lasti = i;

//         while (i < length && format[i] != '_') {
//             i++;
//         }
//         if (i > lasti) {
//             // printf("[debug]------:%ld, %ld\n", lasti, i-lasti);
//             printf("%.*s", (int)(i - lasti), format + lasti);
//             // fflush(stdout);
//         }
//         if (i >= length) {
//             break;
//         }


//         switch (args[args_index].type) {
//         case RVM_VALUE_TYPE_BOOL:
//             if (args[args_index].u.int_value) {
//                 printf("true");
//             } else {
//                 printf("false");
//             }
//             break;
//         case RVM_VALUE_TYPE_INT:
//             printf("%d", args[args_index].u.int_value);
//             break;
//         case RVM_VALUE_TYPE_DOUBLE:
//             printf("%f", args[args_index].u.double_value);
//             break;
//         case RVM_VALUE_TYPE_STRING:
//             if (args[args_index].u.object == nullptr || args[args_index].u.object->u.string.data == nullptr) {
//                 printf("");
//             } else {
//                 printf("%s", args[args_index].u.object->u.string.data);
//             }
//             break;
//         default:
//             break;
//         }
//         args_index++;
//         i++;
//     }

//     return ret;
// }

// RVM_Value native_proc_printfln(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
//     debug_log_with_white_coloar("\t");

//     RVM_Value ret;
//     ret.u.int_value = 0;

//     native_proc_printf(rvm, arg_count, args);
//     printf("\n");

//     return ret;
// }
