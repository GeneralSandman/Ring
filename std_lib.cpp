#include "ring.h"
#include <vector>

/*
 * make install 安装标准库
 * /usr/local/ring/std/ 为默认标准库的安装路径
 * 通过 更改Makefile 编译宏 DEBUG_STD_LIB 来控制调试标准库路径
 */
#ifdef DEBUG_STD_LIB
char RING_PACKAGE_STD_PATH_OS[]      = "/Users/bytedance/Desktop/Ring/std/os/";
char RING_PACKAGE_STD_PATH_IO[]      = "/Users/bytedance/Desktop/Ring/std/io/";
char RING_PACKAGE_STD_PATH_FMT[]     = "/Users/bytedance/Desktop/Ring/std/fmt/";
char RING_PACKAGE_STD_PATH_DEBUG[]   = "/Users/bytedance/Desktop/Ring/std/debug/";
char RING_PACKAGE_STD_PATH_VM[]      = "/Users/bytedance/Desktop/Ring/std/vm/";
char RING_PACKAGE_STD_PATH_REFLECT[] = "/Users/bytedance/Desktop/Ring/std/reflect/";
#else
char RING_PACKAGE_STD_PATH_OS[]      = "/usr/local/lib/ring/std/os/";
char RING_PACKAGE_STD_PATH_IO[]      = "/usr/local/lib/ring/std/io/";
char RING_PACKAGE_STD_PATH_FMT[]     = "/usr/local/lib/ring/std/fmt/";
char RING_PACKAGE_STD_PATH_DEBUG[]   = "/usr/local/lib/ring/std/debug/";
char RING_PACKAGE_STD_PATH_VM[]      = "/usr/local/lib/ring/std/vm/";
char RING_PACKAGE_STD_PATH_REFLECT[] = "/usr/local/lib/ring/std/reflect/";
#endif

/*
 * Ring compiler 当前支持的std packages.
 *
 * Std Package List:
 *  os
 *  io
 *  fmt
 *  debug
 *  vm
 *  reflect
 */
std::vector<StdPackageInfo> Std_Lib_List = {
    {
        (char*)"os",
        RING_PACKAGE_STD_PATH_OS,
        std::vector<StdPackageNativeFunction>{
            {(char*)"exit", std_lib_os_exit, 1, 0},
        },
    },

    {
        (char*)"io",
        RING_PACKAGE_STD_PATH_IO,
        std::vector<StdPackageNativeFunction>{
            {(char*)"write", std_lib_io_write, 1, 0},
        },
    },

    {
        (char*)"fmt",
        RING_PACKAGE_STD_PATH_FMT,
        std::vector<StdPackageNativeFunction>{
            {(char*)"println_bool", std_lib_fmt_println_bool, 1, 0},
            {(char*)"println_int", std_lib_fmt_println_int, 1, 0},
            {(char*)"println_double", std_lib_fmt_println_double, 1, 0},
            {(char*)"println_string", std_lib_fmt_println_string, 1, 0},
            {(char*)"println_pointer", std_lib_fmt_println_pointer, 1, 0},
            {(char*)"println", std_lib_fmt_println, 1, 0},
        },
    },

    {
        (char*)"debug",
        RING_PACKAGE_STD_PATH_DEBUG,
        std::vector<StdPackageNativeFunction>{
            {(char*)"debug_assert", std_lib_debug_debug_assert, 1, 0},
        },
    },

    {
        (char*)"vm",
        RING_PACKAGE_STD_PATH_VM,
        std::vector<StdPackageNativeFunction>{
            {(char*)"heap_size", std_lib_vm_heap_size, 0, 1},
        },
    },

    {
        (char*)"reflect",
        RING_PACKAGE_STD_PATH_REFLECT,
        std::vector<StdPackageNativeFunction>{
            {(char*)"typeof", std_lib_reflect_typeof, 0, 1},
        },
    },
};

/*
 * 将Ring std 相关的 packages都进行一起编译，
 * 生成vmcode
 *
 * 1. std packages 预先都会编译一遍
 * 2. 暂时未对package做到 lazy load，即main-package import的时候才去编译
 * 3. 目前 std packages 中相关函数 都是 @native的
 */
void compile_std_lib(CompilerEntry* compiler_entry, ExecuterEntry* executer_entry) {
    for (StdPackageInfo std_package_info : Std_Lib_List) {
        char* package_name = std_package_info.package_name;
        char* package_path = std_package_info.path;

        // 编译
        if (nullptr != search_package(compiler_entry, package_name)) {
            continue;
        }
        Package* std_package       = package_create(compiler_entry, package_name, package_path);
        std_package->package_index = compiler_entry->package_list.size(); // TODO: 这个应该在 fix的时候 设置
        package_compile(std_package);

        // 生成代码
        Package_Executer* package_executer = package_executer_create(executer_entry, std_package->package_name);
        ring_generate_vm_code(std_package, package_executer);
        executer_entry->package_executer_list.push_back(package_executer);

        // registe @native function
        for (StdPackageNativeFunction native_function : std_package_info.native_function_list) {
            register_lib(package_executer, native_function.func_name, native_function.func_proc, native_function.arg_count, native_function.return_list_count);
        }
    }
}

void register_lib(Package_Executer* package_executer, char* func_name, RVM_NativeFuncProc* func_proc, int arg_count, int return_list_count) {
    for (int i = 0; i < package_executer->function_size; i++) {
        RVM_Function* function = &package_executer->function_list[i];
        if (function->type == RVM_FUNCTION_TYPE_NATIVE && 0 == strcmp(function->func_name, func_name)) {
            function->u.native_func                    = (NativeFunction*)malloc(sizeof(NativeFunction));
            function->u.native_func->func_proc         = func_proc;
            function->u.native_func->arg_count         = arg_count;
            function->u.native_func->return_list_count = return_list_count;
        }
    }
}

/*
 * Package: os
 * Function: exit
 * Type: @native
 */
RVM_Value std_lib_os_exit(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    debug_log_with_white_coloar("\t");

    RVM_Value ret;

    ret.u.int_value = 0;


    if (arg_count != 1) {
        printf("native_proc_exit only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    // TODO: 暂时只打印int, 以后都强制转换成int_value
    exit(args->u.int_value);

    return ret;
}


/*
 * Package: io
 * Function: write
 * Type: @native
 */
RVM_Value std_lib_io_write(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    std::string str = "";

    switch (args->type) {
    case RVM_VALUE_TYPE_BOOL:
        str = "bool";
        break;
    case RVM_VALUE_TYPE_INT:
        str = "int";
        break;
    case RVM_VALUE_TYPE_DOUBLE:
        str = "double";
        break;
    case RVM_VALUE_TYPE_STRING:
        str = "string";
        break;
    case RVM_VALUE_TYPE_OBJECT:
        switch (args->u.object->type) {
        case RVM_OBJECT_TYPE_STRING:
            str = "string";
            break;
        case RVM_OBJECT_TYPE_ARRAY:
            str = "array";
            break;
        case RVM_OBJECT_TYPE_CLASS:
            str = "class";
            break;
        default:
            str = "unknow";
            break;
        }
        break;
    default:
        break;
    }

    RVM_Value ret;
    ret.type     = RVM_VALUE_TYPE_OBJECT;
    ret.u.object = string_literal_to_rvm_object(rvm, str.c_str());

    return ret;
}

/*
 * Package: fmt
 * Function: println_bool
 * Type: @native
 */
RVM_Value std_lib_fmt_println_bool(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    if (arg_count != 1) {
        printf("std_lib_fmt_println_bool only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    RVM_Value ret;
    ret.u.int_value     = 0;

    char* output_buffer = (char*)malloc(6 * sizeof(char));

    if (args->u.int_value) {
        snprintf(output_buffer, 6, "true\n");
    } else {
        snprintf(output_buffer, 7, "false\n");
    }

    printf(output_buffer, "");
    fflush(stdout);

#ifdef DEBUG_RVM_INTERACTIVE
    rvm->stdout_logs.push_back(output_buffer);
#endif

    return ret;
}

/*
 * Package: fmt
 * Function: println_int
 * Type: @native
 */
RVM_Value std_lib_fmt_println_int(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    if (arg_count != 1) {
        printf("std_lib_fmt_println_int only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    RVM_Value ret;
    ret.u.int_value     = 0;

    char* output_buffer = (char*)malloc(12 * sizeof(char));

    // TODO: 暂时只打印int, 以后都强制转换成int_value
    snprintf(output_buffer, 13, "%d\n", args->u.int_value);

    printf(output_buffer, "");
    fflush(stdout);

#ifdef DEBUG_RVM_INTERACTIVE
    rvm->stdout_logs.push_back(output_buffer);
#endif

    return ret;
}

/*
 * Package: fmt
 * Function: println_double
 * Type: @native
 */
RVM_Value std_lib_fmt_println_double(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    if (arg_count != 1) {
        printf("std_lib_fmt_println_double only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    RVM_Value ret;
    ret.u.int_value     = 0;

    char* output_buffer = (char*)malloc(1024 * sizeof(char));

    snprintf(output_buffer, 1024, "%f\n", args->u.double_value);

    printf(output_buffer, "");
    fflush(stdout);

#ifdef DEBUG_RVM_INTERACTIVE
    rvm->stdout_logs.push_back(output_buffer);
#endif

    return ret;
}

/*
 * Package: fmt
 * Function: println_string
 * Type: @native
 */
RVM_Value std_lib_fmt_println_string(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    if (arg_count != 1) {
        printf("std_lib_fmt_println_string only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    RVM_Value ret;
    ret.u.int_value            = 0;

    unsigned int length        = 2;
    char*        output_buffer = (char*)malloc(length * sizeof(char));

    if (args->u.object == nullptr
        || args->u.object->u.string == nullptr
        || args->u.object->u.string->data == nullptr) {
        snprintf(output_buffer, length, "\n");
    } else {
        length        = args->u.object->u.string->size + 2;
        output_buffer = (char*)realloc(output_buffer, length * sizeof(char));
        // printf("str:(%s)\n", args->u.object->u.string->data);
        snprintf(output_buffer, length, "%s\n", args->u.object->u.string->data);
    }
    // printf("length:%d\n", length);
    output_buffer[length - 1] = '\0';

    printf(output_buffer, "");
    fflush(stdout);

#ifdef DEBUG_RVM_INTERACTIVE
    rvm->stdout_logs.push_back(output_buffer);
#endif

    return ret;
}

/*
 * Package: fmt
 * Function: println_pointer
 * Type: @native
 *
 * TODO: 后续废弃
 */
RVM_Value std_lib_fmt_println_pointer(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    if (arg_count != 1) {
        printf("std_lib_fmt_println_pointer only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    unsigned int length        = 20;
    char*        output_buffer = (char*)malloc(length * sizeof(char));

    /*
     * 这个地方是不对的, 因为 args 已经位于栈空间了,
     * 也就是说:
     *  fmt::println_pointer(global_bool_value_1);
     *  是先copy 到 runtime_stack中, 又计算的栈空间,
     *
     *  需要弄个单独的关键字去计算 pointer
     *
     */

    switch (args->type) {
    case RVM_VALUE_TYPE_BOOL:
        snprintf(output_buffer, length, "%p\n", &(args->u.bool_value));
        break;
    case RVM_VALUE_TYPE_INT:
        snprintf(output_buffer, length, "%p\n", &(args->u.int_value));
        break;
    case RVM_VALUE_TYPE_DOUBLE:
        snprintf(output_buffer, length, "%p\n", &(args->u.double_value));
        break;
    case RVM_VALUE_TYPE_OBJECT:
        switch (args->u.object->type) {
        case RVM_OBJECT_TYPE_STRING:
            snprintf(output_buffer, length, "%p\n", args->u.object->u.string->data);
            break;
        case RVM_OBJECT_TYPE_ARRAY:
            snprintf(output_buffer, length, "%p\n", args->u.object->u.array->u.int_array);
            break;
        case RVM_OBJECT_TYPE_CLASS:
            snprintf(output_buffer, length, "%p\n", args->u.object->u.array->u.double_array);
            break;
        default:
            snprintf(output_buffer, length, "%p\n", (void*)0);
            break;
        }
        break;
    default:
        break;
    }


    output_buffer[length - 1] = '\0';

    printf(output_buffer, "");
    fflush(stdout);

#ifdef DEBUG_RVM_INTERACTIVE
    rvm->stdout_logs.push_back(output_buffer);
#endif

    RVM_Value ret;
    ret.u.int_value = 0;
    return ret;
}

/*
 * Package: fmt
 * Function: println
 * Type: @native
 */
RVM_Value std_lib_fmt_println(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    if (arg_count != 1) {
        printf("std_lib_fmt_println only one arguement\n");
        exit(ERROR_CODE_RUN_VM_ERROR);
    }

    RVM_Value ret;
    ret.u.int_value = 0;

    if (args->u.object == nullptr || args->u.object->u.string == nullptr || args->u.object->u.string->data == nullptr) {
        printf("\n");
    } else {
        printf("%s\n", args->u.object->u.string->data);
    }
    fflush(stdout);

    return ret;
}


/*
 * Package: debug
 * Function: debug_assert
 * Type: @native
 */
RVM_Value std_lib_debug_debug_assert(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    if (arg_count != 1) {
        printf("std_lib_debug_debug_assert only one arguement\n");
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


/*
 * Package: vm
 * Function: heap_size
 * Type: @native
 */
RVM_Value std_lib_vm_heap_size(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    RVM_Value ret;
    ret.type        = RVM_VALUE_TYPE_INT;
    ret.u.int_value = rvm_heap_size(rvm);

    return ret;
}


/*
 * Package: reflect
 * Function: typeof
 * Type: @native
 */
RVM_Value std_lib_reflect_typeof(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
    std::string str = "";

    switch (args->type) {
    case RVM_VALUE_TYPE_BOOL:
        str = "bool";
        break;
    case RVM_VALUE_TYPE_INT:
        str = "int";
        break;
    case RVM_VALUE_TYPE_DOUBLE:
        str = "double";
        break;
    case RVM_VALUE_TYPE_STRING:
        str = "string";
        break;
    case RVM_VALUE_TYPE_OBJECT:
        switch (args->u.object->type) {
        case RVM_OBJECT_TYPE_STRING:
            str = "string";
            break;
        case RVM_OBJECT_TYPE_ARRAY:
            str = "array";
            break;
        case RVM_OBJECT_TYPE_CLASS:
            str = "class";
            break;
        default:
            str = "unknow";
            break;
        }
        break;
    default:
        break;
    }

    RVM_Value ret;
    ret.type     = RVM_VALUE_TYPE_OBJECT;
    ret.u.object = string_literal_to_rvm_object(rvm, str.c_str());

    return ret;
}


/*
 * Package: math
 * Function: sqrt
 * Type: @native
 */
RVM_Value std_lib_math_sqrt(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {
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

//     RVM_Value ret;
//     ret.u.int_value = 0;

//     native_proc_print(rvm, arg_count, args);
//     printf("\n");

//     return ret;
// }

// RVM_Value native_proc_printf(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args) {

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

//     RVM_Value ret;
//     ret.u.int_value = 0;

//     native_proc_printf(rvm, arg_count, args);
//     printf("\n");

//     return ret;
// }
