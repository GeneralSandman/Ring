#include "ring.hpp"
#include <cassert>
#include <cmath>
#include <cstring>
#include <ctime>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <vector>

/*
 * make install 安装标准库
 * /usr/local/ring/std/ 为默认标准库的安装路径
 * 通过 更改Makefile 编译宏 DEBUG_STD_LIB 来控制调试标准库路径
 */
#ifdef DEBUG_STD_LIB
char RING_PACKAGE_STD_PATH_DEBUG[]   = "/Users/bytedance/Desktop/Ring/std/debug/";
char RING_PACKAGE_STD_PATH_FMT[]     = "/Users/bytedance/Desktop/Ring/std/fmt/";
char RING_PACKAGE_STD_PATH_IO[]      = "/Users/bytedance/Desktop/Ring/std/io/";
char RING_PACKAGE_STD_PATH_MATH[]    = "/Users/bytedance/Desktop/Ring/std/math/";
char RING_PACKAGE_STD_PATH_OS[]      = "/Users/bytedance/Desktop/Ring/std/os/";
char RING_PACKAGE_STD_PATH_REFLECT[] = "/Users/bytedance/Desktop/Ring/std/reflect/";
char RING_PACKAGE_STD_PATH_RUNTIME[] = "/Users/bytedance/Desktop/Ring/std/runtime/";
char RING_PACKAGE_STD_PATH_STRINGS[] = "/Users/bytedance/Desktop/Ring/std/strings";
char RING_PACKAGE_STD_PATH_TIME[]    = "/Users/bytedance/Desktop/Ring/std/time/";
#else
char RING_PACKAGE_STD_PATH_DEBUG[]   = "/usr/local/lib/ring/std/debug/";
char RING_PACKAGE_STD_PATH_FMT[]     = "/usr/local/lib/ring/std/fmt/";
char RING_PACKAGE_STD_PATH_IO[]      = "/usr/local/lib/ring/std/io/";
char RING_PACKAGE_STD_PATH_MATH[]    = "/usr/local/lib/ring/std/math/";
char RING_PACKAGE_STD_PATH_OS[]      = "/usr/local/lib/ring/std/os/";
char RING_PACKAGE_STD_PATH_REFLECT[] = "/usr/local/lib/ring/std/reflect/";
char RING_PACKAGE_STD_PATH_RUNTIME[] = "/usr/local/lib/ring/std/runtime/";
char RING_PACKAGE_STD_PATH_STRINGS[] = "/usr/local/lib/ring/std/strings/";
char RING_PACKAGE_STD_PATH_TIME[]    = "/usr/local/lib/ring/std/time/";
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
 *
 * 在编译过程中, 同样需要对std函数调用做详细的语义检查, 包括: 参数数量/类型, 返回值
 * 其中函数详细的定义 必须用 ring文件表明
 * 这里 std函数调用过程中不需要在做语义检查
 */
std::vector<StdPackageInfo> Std_Lib_List = {

    {
        (char*)"debug",
        RING_PACKAGE_STD_PATH_DEBUG,
        std::vector<StdPackageNativeFunction>{
            {(char*)"assert", std_lib_debug_assert, 1, 0},
            {(char*)"var_dump", std_lib_debug_var_dump, 1, 0},
        },
    },

    {
        (char*)"fmt",
        RING_PACKAGE_STD_PATH_FMT,
        std::vector<StdPackageNativeFunction>{
            {(char*)"println_bool", std_lib_fmt_println_bool, 1, 0},
            {(char*)"println_int", std_lib_fmt_println_int, 1, 0},
            {(char*)"println_int64", std_lib_fmt_println_int64, 1, 0},
            {(char*)"println_double", std_lib_fmt_println_double, 1, 0},
            {(char*)"println_string", std_lib_fmt_println_string, 1, 0},
            {(char*)"println_pointer", std_lib_fmt_println_pointer, 1, 0},
            {(char*)"println", std_lib_fmt_println, 1, 0},
            {(char*)"printf", std_lib_fmt_printf, 1, 0},
            {(char*)"sprintf", std_lib_fmt_sprintf, 1, 1},
        },
    },

    {
        (char*)"io",
        RING_PACKAGE_STD_PATH_IO,
        std::vector<StdPackageNativeFunction>{
            {(char*)"exist", std_lib_io_exist, 1, 1},
            {(char*)"open", std_lib_io_open, 1, 1},
            {(char*)"create", std_lib_io_create, 1, 1},
            {(char*)"seek", std_lib_io_seek, 1, 0},
            {(char*)"read_all", std_lib_io_read_all, 1, 1},
            {(char*)"write", std_lib_io_write, 2, 0},
            {(char*)"close", std_lib_io_close, 1, 1},
            {(char*)"remove", std_lib_io_remove, 1, 0},
        },
    },

    {
        (char*)"math",
        RING_PACKAGE_STD_PATH_MATH,
        std::vector<StdPackageNativeFunction>{
            {(char*)"abs", std_lib_math_abs, 1, 1},
            {(char*)"sqrt", std_lib_math_sqrt, 1, 1},
            {(char*)"pow", std_lib_math_pow, 2, 1},
        },
    },

    {
        (char*)"os",
        RING_PACKAGE_STD_PATH_OS,
        std::vector<StdPackageNativeFunction>{
            {(char*)"exit", std_lib_os_exit, 1, 0},
            {(char*)"remove", std_lib_io_remove, 1, 0},
            {(char*)"getenv", std_lib_os_getenv, 1, 1},
            {(char*)"setenv", std_lib_os_setenv, 2, 0},
        },
    },

    {
        (char*)"reflect",
        RING_PACKAGE_STD_PATH_REFLECT,
        std::vector<StdPackageNativeFunction>{
            {(char*)"typeof", std_lib_reflect_typeof, 0, 1},
        },
    },

    {
        (char*)"runtime",
        RING_PACKAGE_STD_PATH_RUNTIME,
        std::vector<StdPackageNativeFunction>{
            {(char*)"heap_size", std_lib_runtime_heap_size, 0, 1},
            {(char*)"gc", std_lib_runtime_gc, 0, 0},
            {(char*)"print_call_stack", std_lib_runtime_print_call_stack, 0, 0},
            {(char*)"call_info", std_lib_runtime_call_info, 1, 4},
        },
    },

    {
        (char*)"strings",
        RING_PACKAGE_STD_PATH_STRINGS,
        std::vector<StdPackageNativeFunction>{},
    },

    {
        (char*)"time",
        RING_PACKAGE_STD_PATH_TIME,
        std::vector<StdPackageNativeFunction>{
            {(char*)"time", std_lib_time_time, 0, 1},
            {(char*)"sleep", std_lib_time_sleep, 0, 0},
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
            register_lib(package_executer, native_function.identifier, native_function.func_proc, native_function.arg_count, native_function.return_list_count);
        }
    }
}

void register_lib(Package_Executer*   package_executer,
                  char*               func_name,
                  RVM_NativeFuncProc* func_proc,
                  int                 arg_count,
                  int                 return_list_count) {

    for (unsigned int i = 0; i < package_executer->function_size; i++) {
        RVM_Function* function = &package_executer->function_list[i];
        if (function->type == RVM_FUNCTION_TYPE_NATIVE && str_eq(function->identifier, func_name)) {
            function->u.native_func                    = (NativeFunction*)mem_alloc(NULL_MEM_POOL, sizeof(NativeFunction));
            function->u.native_func->func_proc         = func_proc;
            function->u.native_func->arg_count         = arg_count;
            function->u.native_func->return_list_count = return_list_count;
        }
    }
}

RVM_Value* new_native_return_list(unsigned int return_size) {
    return (RVM_Value*)mem_alloc(NULL_MEM_POOL, return_size * sizeof(RVM_Value));
}
void destory_native_return_list(RVM_Value* return_list, unsigned int return_size) {
    mem_free(NULL_MEM_POOL, return_list, return_size * sizeof(RVM_Value));
}

#define RETURN_LIST_SET_BOOL(list, index, value)        \
    (list)[(index)].type         = RVM_VALUE_TYPE_BOOL; \
    (list)[(index)].u.bool_value = (value);
#define RETURN_LIST_SET_INT(list, index, value)       \
    (list)[(index)].type        = RVM_VALUE_TYPE_INT; \
    (list)[(index)].u.int_value = (value);
#define RETURN_LIST_SET_INT64(list, index, value)         \
    (list)[(index)].type          = RVM_VALUE_TYPE_INT64; \
    (list)[(index)].u.int64_value = (value);
#define RETURN_LIST_SET_DOUBLE(list, index, value)          \
    (list)[(index)].type           = RVM_VALUE_TYPE_DOUBLE; \
    (list)[(index)].u.double_value = (value);
#define RETURN_LIST_SET_STRING(list, index, value)          \
    (list)[(index)].type           = RVM_VALUE_TYPE_STRING; \
    (list)[(index)].u.string_value = (value);

/*
 * Package: os
 * Function: exit
 * Type: @native
 */
void std_lib_os_exit(Ring_VirtualMachine* rvm,
                     unsigned int arg_count, RVM_Value* args,
                     unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);

    exit(args->u.int_value);

    *return_size = 0;
    *return_list = nullptr;
}

/*
 * Package: os
 * Function: remove
 * Type: @native
 */
void std_lib_os_remove(Ring_VirtualMachine* rvm,
                       unsigned int arg_count, RVM_Value* args,
                       unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);
    assert(args[0].type == RVM_VALUE_TYPE_STRING);

    RVM_String* str = args[0].u.string_value;

    // TODO: 写法丑陋，需要后续抽象
    str->data[str->length] = '\0';
    remove(str->data);

    *return_size = 0;
    *return_list = nullptr;
}

/*
 * Package: os
 * Function: rename
 * Type: @native
 */
void std_lib_os_rename(Ring_VirtualMachine* rvm,
                       unsigned int arg_count, RVM_Value* args,
                       unsigned int* return_size, RVM_Value** return_list) {

    *return_size = 0;
    *return_list = nullptr;
}

/*
 * Package: os
 * Function: getenv
 * Type: @native
 */
void std_lib_os_getenv(Ring_VirtualMachine* rvm,
                       unsigned int arg_count, RVM_Value* args,
                       unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);
    assert(args[0].type == RVM_VALUE_TYPE_STRING);

    RVM_String* str = args[0].u.string_value;
    // TODO: 写法丑陋，需要后续抽象
    str->data[str->length] = '\0';

    char* res              = getenv(str->data);
    if (res == nullptr) {
        res = (char*)"";
    }

    RVM_String* str_val = rvm_gc_new_string_meta(rvm);
    rvm_fill_string(rvm, str_val, ROUND_UP8(strlen(res)));
    memcpy(str_val->data, res, strlen(res));
    str_val->length            = strlen(res);
    str_val->data[strlen(res)] = '\0';

    *return_size               = 1;
    *return_list               = new_native_return_list(*return_size);
    RETURN_LIST_SET_STRING(*return_list, 0, str_val);
}

/*
 * Package: os
 * Function: setenv
 * Type: @native
 */
void std_lib_os_setenv(Ring_VirtualMachine* rvm,
                       unsigned int arg_count, RVM_Value* args,
                       unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 2);
    assert(args[0].type == RVM_VALUE_TYPE_STRING);
    assert(args[1].type == RVM_VALUE_TYPE_STRING);

    RVM_String* name  = args[0].u.string_value;
    RVM_String* value = args[1].u.string_value;

    setenv(name->data, value->data, 1);

    *return_size = 0;
    *return_list = nullptr;
}

/*
 * Package: io
 * Function: exist
 * Type: @native
 */
void std_lib_io_exist(Ring_VirtualMachine* rvm,
                      unsigned int arg_count, RVM_Value* args,
                      unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);
    assert(args[0].type == RVM_VALUE_TYPE_STRING);

    RVM_String* str = args[0].u.string_value;

    int         res;
    res          = access(str->data, F_OK);


    *return_size = 1;
    *return_list = new_native_return_list(*return_size);
    RETURN_LIST_SET_BOOL(*return_list, 0, ((res == 0) ? RVM_TRUE : RVM_FALSE));
}

/*
 * Package: io
 * Function: open
 * Type: @native
 */
void std_lib_io_open(Ring_VirtualMachine* rvm,
                     unsigned int arg_count, RVM_Value* args,
                     unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);
    assert(args[0].type == RVM_VALUE_TYPE_STRING);

    int fid      = open(args[0].u.string_value->data, O_RDONLY);

    *return_size = 1;
    *return_list = new_native_return_list(*return_size);
    RETURN_LIST_SET_INT(*return_list, 0, fid);
}

/*
 * Package: io
 * Function: create
 * Type: @native
 */
void std_lib_io_create(Ring_VirtualMachine* rvm,
                       unsigned int arg_count, RVM_Value* args,
                       unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);
    assert(args[0].type == RVM_VALUE_TYPE_STRING);

    int fid      = open(args[0].u.string_value->data, O_CREAT | O_RDWR, 0666);

    *return_size = 1;
    *return_list = new_native_return_list(*return_size);
    RETURN_LIST_SET_INT(*return_list, 0, fid);
}

/*
 * Package: io
 * Function: seek
 * Type: @native
 */
void std_lib_io_seek(Ring_VirtualMachine* rvm,
                     unsigned int arg_count, RVM_Value* args,
                     unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 3);
    assert(args[0].type == RVM_VALUE_TYPE_INT);
    assert(args[1].type == RVM_VALUE_TYPE_INT64);
    assert(args[2].type == RVM_VALUE_TYPE_INT);

    int       fid    = args[0].u.int_value;
    long long offset = args[1].u.int64_value;
    int       whence = args[2].u.int_value;

    lseek(fid, offset, whence);

    *return_size = 0;
    *return_list = nullptr;
}

/*
 * Package: io
 * Function: read_all
 * Type: @native
 */
void std_lib_io_read_all(Ring_VirtualMachine* rvm,
                         unsigned int arg_count, RVM_Value* args,
                         unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);
    assert(args[0].type == RVM_VALUE_TYPE_INT);

    std::string result;

    char        buffer[1024];

    int         fid    = args[0].u.int_value;
    int         read_n = 0;

    while ((read_n = read(fid, buffer, 1024)) > 0) {
        std::string tmp = std::string(buffer, read_n);
        result += tmp;

        memset(buffer, 0, 1024);
    }

    // TODO: 写法丑陋，需要后续抽象
    RVM_String* str_val = rvm_gc_new_string_meta(rvm);
    rvm_fill_string(rvm, str_val, ROUND_UP8(result.size()));

    memcpy(str_val->data, result.c_str(), result.size());

    str_val->length              = result.size();
    str_val->data[result.size()] = '\0';

    *return_size                 = 1;
    *return_list                 = new_native_return_list(*return_size);
    RETURN_LIST_SET_STRING(*return_list, 0, str_val);
}

/*
 * Package: io
 * Function: write
 * Type: @native
 */
void std_lib_io_write(Ring_VirtualMachine* rvm,
                      unsigned int arg_count, RVM_Value* args,
                      unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 2);
    assert(args[0].type == RVM_VALUE_TYPE_INT);
    assert(args[1].type == RVM_VALUE_TYPE_STRING);

    int         fid    = args[0].u.int_value;
    RVM_String* buffer = args[1].u.string_value;

    ssize_t     ws     = write(fid, buffer->data, buffer->length);
    (void)ws;

    *return_size = 0;
    *return_list = nullptr;
}

/*
 * Package: io
 * Function: close
 * Type: @native
 */
void std_lib_io_close(Ring_VirtualMachine* rvm,
                      unsigned int arg_count, RVM_Value* args,
                      unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);
    assert(args[0].type == RVM_VALUE_TYPE_INT);

    int fid      = args[0].u.int_value;

    int res      = close(fid);

    *return_size = 1;
    *return_list = new_native_return_list(*return_size);
    RETURN_LIST_SET_INT(*return_list, 0, res);
}

/*
 * Package: io
 * Function: remove
 * Type: @native
 */
void std_lib_io_remove(Ring_VirtualMachine* rvm,
                       unsigned int arg_count, RVM_Value* args,
                       unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);
    assert(args[0].type == RVM_VALUE_TYPE_STRING);

    RVM_String* str = args[0].u.string_value;

    // TODO: 写法丑陋，需要后续抽象
    str->data[str->length] = '\0';
    remove(str->data);

    *return_size = 0;
    *return_list = nullptr;
}

/*
 * Package: fmt
 * Function: println_bool
 * Type: @native
 */
void std_lib_fmt_println_bool(Ring_VirtualMachine* rvm,
                              unsigned int arg_count, RVM_Value* args,
                              unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);
    assert(args[0].type == RVM_VALUE_TYPE_BOOL);

    RVM_Value ret;
    ret.u.int_value     = 0;

    char* output_buffer = (char*)mem_alloc(NULL_MEM_POOL, 6 * sizeof(char));

    if (args->u.bool_value) {
        snprintf(output_buffer, 6, "true\n");
    } else {
        snprintf(output_buffer, 7, "false\n");
    }

    printf(output_buffer, "");
    fflush(stdout);

    mem_free(NULL_MEM_POOL, (void*)output_buffer, 6 * sizeof(char));


    *return_size = 0;
    *return_list = nullptr;
}

/*
 * Package: fmt
 * Function: println_int
 * Type: @native
 */
void std_lib_fmt_println_int(Ring_VirtualMachine* rvm,
                             unsigned int arg_count, RVM_Value* args,
                             unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);
    assert(args[0].type == RVM_VALUE_TYPE_INT);

    RVM_Value ret;
    ret.u.int_value     = 0;

    char* output_buffer = (char*)mem_alloc(NULL_MEM_POOL, 12 * sizeof(char));

    snprintf(output_buffer, 13, "%d\n", args->u.int_value);

    printf(output_buffer, "");
    fflush(stdout);

    mem_free(NULL_MEM_POOL, (void*)output_buffer, 12 * sizeof(char));


    *return_size = 0;
    *return_list = nullptr;
}

/*
 * Package: fmt
 * Function: println_int64
 * Type: @native
 */
void std_lib_fmt_println_int64(Ring_VirtualMachine* rvm,
                               unsigned int arg_count, RVM_Value* args,
                               unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);
    assert(args[0].type == RVM_VALUE_TYPE_INT64);

    RVM_Value ret;
    ret.u.int_value     = 0;

    char* output_buffer = (char*)mem_alloc(NULL_MEM_POOL, 22 * sizeof(char));

    snprintf(output_buffer, 22, "%lld\n", args->u.int64_value);

    printf(output_buffer, "");
    fflush(stdout);

    mem_free(NULL_MEM_POOL, (void*)output_buffer, 22 * sizeof(char));


    *return_size = 0;
    *return_list = nullptr;
}

/*
 * Package: fmt
 * Function: println_double
 * Type: @native
 */
void std_lib_fmt_println_double(Ring_VirtualMachine* rvm,
                                unsigned int arg_count, RVM_Value* args,
                                unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);
    assert(args[0].type == RVM_VALUE_TYPE_DOUBLE);

    RVM_Value ret;
    ret.u.int_value     = 0;

    char* output_buffer = (char*)mem_alloc(NULL_MEM_POOL, 1024 * sizeof(char));

    snprintf(output_buffer, 1024, "%f\n", args->u.double_value);

    printf(output_buffer, "");
    fflush(stdout);

    mem_free(NULL_MEM_POOL, (void*)output_buffer, 1024 * sizeof(char));


    *return_size = 0;
    *return_list = nullptr;
}

/*
 * Package: fmt
 * Function: println_string
 * Type: @native
 */
void std_lib_fmt_println_string(Ring_VirtualMachine* rvm,
                                unsigned int arg_count, RVM_Value* args,
                                unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);
    assert(args[0].type == RVM_VALUE_TYPE_STRING);

    RVM_Value ret;
    ret.u.int_value            = 0;

    unsigned int length        = 0;
    unsigned int capacity      = 8;
    char*        output_buffer = nullptr;

    if (args->u.string_value == nullptr
        || args->u.string_value->data == nullptr) {
        // FIXME: shoud alloced in rvm->data_mem_pool
        output_buffer = (char*)mem_alloc(NULL_MEM_POOL, capacity * sizeof(char));
        length        = 1;
    } else {
        unsigned int str_length = args->u.string_value->length;
        if (str_length + 1 > capacity) {
            capacity = str_length + 1;
        }
        length = str_length + 1;
        // FIXME: shoud alloced in rvm->data_mem_pool
        output_buffer = (char*)mem_alloc(NULL_MEM_POOL, capacity * sizeof(char));
        strncpy(output_buffer, args->u.string_value->data, str_length);
    }
    output_buffer[length - 1] = '\n';

    printf("%.*s", length, output_buffer);
    fflush(stdout);

    mem_free(NULL_MEM_POOL, (void*)output_buffer, capacity * sizeof(char));


    *return_size = 0;
    *return_list = nullptr;
}

/*
 * Package: fmt
 * Function: println_pointer
 * Type: @native
 *
 * TODO: 后续废弃
 */
void std_lib_fmt_println_pointer(Ring_VirtualMachine* rvm,
                                 unsigned int arg_count, RVM_Value* args,
                                 unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);

    unsigned int length        = 20;
    char*        output_buffer = (char*)mem_alloc(NULL_MEM_POOL, length * sizeof(char));

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
    case RVM_VALUE_TYPE_INT64:
        snprintf(output_buffer, length, "%p\n", &(args->u.int64_value));
        break;
    case RVM_VALUE_TYPE_DOUBLE:
        snprintf(output_buffer, length, "%p\n", &(args->u.double_value));
        break;
    case RVM_VALUE_TYPE_STRING:
        snprintf(output_buffer, length, "%p\n", args->u.string_value->data);
        break;
    case RVM_VALUE_TYPE_CLASS_OB:
        snprintf(output_buffer, length, "%p\n", args->u.class_ob_value->field_list);
        break;
    case RVM_VALUE_TYPE_ARRAY:
        snprintf(output_buffer, length, "%p\n", args->u.array_value->u.int_array);
        break;
    default:
        break;
    }


    output_buffer[length - 1] = '\0';

    printf(output_buffer, "");
    fflush(stdout);

    mem_free(NULL_MEM_POOL, (void*)output_buffer, length * sizeof(char));

    *return_size = 0;
    *return_list = nullptr;
}

/*
 * Package: fmt
 * Function: println
 * Type: @native
 */
void std_lib_fmt_println(Ring_VirtualMachine* rvm,
                         unsigned int arg_count, RVM_Value* args,
                         unsigned int* return_size, RVM_Value** return_list) {

    std::string result;
    std::string tmp;

    for (unsigned int args_index = 0; args_index < arg_count; args_index++) {
        if (args_index != 0) {
            result += " ";
        }

        result += fmt_any(&args[args_index]);
    }
    result += "\n";


    printf("%s", result.c_str());
    fflush(stdout);

    *return_size = 0;
    *return_list = nullptr;
}

/*
 * Package: fmt
 * Function: printf
 * Type: @native
 */
void std_lib_fmt_printf(Ring_VirtualMachine* rvm,
                        unsigned int arg_count, RVM_Value* args,
                        unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count >= 1);
    assert(args[0].type == RVM_VALUE_TYPE_STRING);

    // TODO: 这里先留一个坑吧, 先使用 std::string
    // 不太合规, 后续统一优化
    std::string  result;


    unsigned int format_index  = 0;
    unsigned int format_length = args[0].u.string_value->length;
    unsigned int args_index    = 1;
    while (format_index < format_length) {

        if (args[0].u.string_value->data[format_index] == '\\') {
            if (format_index + 1 < args[0].u.string_value->length
                && (args[0].u.string_value->data[format_index + 1] == '{'
                    || args[0].u.string_value->data[format_index + 1] == '}')) {
                result += args[0].u.string_value->data[format_index + 1];
                format_index += 2;
            } else {
                result += '\\';
                format_index++;
            }
        } else if (args[0].u.string_value->data[format_index] == '{') {
            if (args[0].u.string_value->data[format_index + 1] == '}') {
                // 消费一个{} 和一个参数
                if (args_index < arg_count) {
                    result += fmt_any(&args[args_index]);

                    args_index++;
                    format_index += 2;
                } else {
                    result += args[0].u.string_value->data[format_index];
                    format_index++;
                }

            } else {
                result += args[0].u.string_value->data[format_index];
                format_index++;
            }

        } else {
            result += args[0].u.string_value->data[format_index];
            format_index++;
        }
    }

    printf("%s", result.c_str());
    fflush(stdout);

    *return_size = 0;
    *return_list = nullptr;
}

/*
 * Package: fmt
 * Function: printf
 * Type: @native
 */
void std_lib_fmt_sprintf(Ring_VirtualMachine* rvm,
                         unsigned int arg_count, RVM_Value* args,
                         unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count >= 1);
    assert(args[0].type == RVM_VALUE_TYPE_STRING);

    // TODO: 这里先留一个坑吧, 先使用 std::string
    // 不太合规, 后续统一优化
    std::string result;


    // TODO: 这里和 printf 代码重复了, 后续优化
    unsigned int format_index  = 0;
    unsigned int format_length = args[0].u.string_value->length;
    unsigned int args_index    = 1;
    while (format_index < format_length) {

        if (args[0].u.string_value->data[format_index] == '\\') {
            if (format_index + 1 < args[0].u.string_value->length
                && (args[0].u.string_value->data[format_index + 1] == '{'
                    || args[0].u.string_value->data[format_index + 1] == '}')) {
                result += args[0].u.string_value->data[format_index + 1];
                format_index += 2;
            } else {
                result += '\\';
                format_index++;
            }
        } else if (args[0].u.string_value->data[format_index] == '{') {
            if (args[0].u.string_value->data[format_index + 1] == '}') {
                // 消费一个{} 和一个参数
                if (args_index < arg_count) {
                    result += fmt_any(&args[args_index]);

                    args_index++;
                    format_index += 2;
                } else {
                    result += args[0].u.string_value->data[format_index];
                    format_index++;
                }

            } else {
                result += args[0].u.string_value->data[format_index];
                format_index++;
            }

        } else {
            result += args[0].u.string_value->data[format_index];
            format_index++;
        }
    }


    *return_size = 1;
    *return_list = new_native_return_list(*return_size);
    RETURN_LIST_SET_STRING(*return_list, 0, rvm_gc_new_rvm_string(rvm, result.c_str()));
}


/*
 * Package: debug
 * Function: debug_assert
 * Type: @native
 */
void std_lib_debug_assert(Ring_VirtualMachine* rvm,
                          unsigned int arg_count, RVM_Value* args,
                          unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);
    assert(args[0].type == RVM_VALUE_TYPE_BOOL);


    unsigned int length        = 20;
    char*        output_buffer = (char*)mem_alloc(NULL_MEM_POOL, length * sizeof(char));

    memset(output_buffer, '\0', length);

    if (args->u.bool_value) {
        strcpy(output_buffer, "debug_assert PASS\n");
    } else {
        strcpy(output_buffer, "debug_assert FAILED\n");
    }

    printf("%s", output_buffer);
    fflush(stdout);

    mem_free(NULL_MEM_POOL, (void*)output_buffer, length * sizeof(char));


    *return_size = 0;
    *return_list = nullptr;
}


/*
 * Package: debug
 * Function: std_lib_debug_var_dump
 * Type: @native
 */
void std_lib_debug_var_dump(Ring_VirtualMachine* rvm,
                            unsigned int arg_count, RVM_Value* args,
                            unsigned int* return_size, RVM_Value** return_list) {

    std::string res;
    for (unsigned int i = 0; i < arg_count; i++) {
        res += var_dump_any(rvm->executer, &args[i], 0);
        res += "\n";
    }

    printf("%s", res.c_str());
    fflush(stdout);

    *return_size = 0;
    *return_list = nullptr;
}


/*
 * Package: reflect
 * Function: typeof
 * Type: @native
 */
void std_lib_reflect_typeof(Ring_VirtualMachine* rvm,
                            unsigned int arg_count, RVM_Value* args,
                            unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);

    std::string str = "";

    str             = format_rvm_type(rvm, args);


    *return_size    = 1;
    *return_list    = new_native_return_list(*return_size);
    RETURN_LIST_SET_STRING(*return_list, 0, rvm_gc_new_rvm_string(rvm, str.c_str()));
}


/*
 * Package: runtime
 * Function: heap_size
 * Type: @native
 *
 */
void std_lib_runtime_heap_size(Ring_VirtualMachine* rvm,
                               unsigned int arg_count, RVM_Value* args,
                               unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 0);


    *return_size = 1;
    *return_list = new_native_return_list(*return_size);
    RETURN_LIST_SET_INT64(*return_list, 0, rvm_heap_size(rvm));
}

/*
 * Package: runtime
 * Function: heap_size
 * Type: @native
 */
void std_lib_runtime_gc(Ring_VirtualMachine* rvm,
                        unsigned int arg_count, RVM_Value* args,
                        unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 0);

    RVM_Value ret;
    ret.u.int_value = 0;

    // gc_incremental(rvm);
    gc_make_sweep(rvm);

    *return_size = 0;
    *return_list = nullptr;
}

/*
 * Package: runtime
 * Function: print_call_stack
 * Type: @native
 */
void std_lib_runtime_print_call_stack(Ring_VirtualMachine* rvm,
                                      unsigned int arg_count, RVM_Value* args,
                                      unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 0);

    std::string call_stack = format_rvm_call_stack(rvm);
    printf("%s", call_stack.c_str());

    fflush(stdout);

    *return_size = 0;
    *return_list = nullptr;
}

/*
 * Package: runtime
 * Function: call_info
 * Type: @native
 */
void std_lib_runtime_call_info(Ring_VirtualMachine* rvm,
                               unsigned int arg_count, RVM_Value* args,
                               unsigned int* return_size, RVM_Value** return_list) {

    CallInfo call_info = get_rvm_call_stack(rvm, args[0].u.int_value);

    *return_size       = 4;
    *return_list       = new_native_return_list(*return_size);
    RETURN_LIST_SET_INT64(*return_list, 0, call_info.pc);
    RETURN_LIST_SET_STRING(*return_list, 1, rvm_gc_new_rvm_string(rvm, call_info.file.c_str()));
    RETURN_LIST_SET_STRING(*return_list, 2, rvm_gc_new_rvm_string(rvm, call_info.func.c_str()));
    RETURN_LIST_SET_INT(*return_list, 3, call_info.line);
}

/*
 * Package: time
 * Function: time
 * Type: @native
 * 返回 纳秒时间戳
 */
void std_lib_time_time(Ring_VirtualMachine* rvm,
                       unsigned int arg_count, RVM_Value* args,
                       unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 0);

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    long long timestamp = (long long)(ts.tv_sec) * 1000000000 + ts.tv_nsec;


    *return_size        = 1;
    *return_list        = new_native_return_list(*return_size);
    RETURN_LIST_SET_INT64(*return_list, 0, timestamp);
}

/*
 * Package: time
 * Function: sleep
 * Type: @native
 *
 * // 单位纳秒
 */
void std_lib_time_sleep(Ring_VirtualMachine* rvm,
                        unsigned int arg_count, RVM_Value* args,
                        unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);
    assert(args[0].type == RVM_VALUE_TYPE_INT64);

    long long       ns = args[0].u.int64_value;

    struct timespec ts;
    ts.tv_sec  = ns / 1000000000;
    ts.tv_nsec = ns % 1000000000;

    nanosleep(&ts, NULL);

    *return_size = 0;
    *return_list = nullptr;
}

/*
 * Package: math
 * Function: abs
 * Type: @native
 */
void std_lib_math_abs(Ring_VirtualMachine* rvm,
                      unsigned int arg_count, RVM_Value* args,
                      unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);
    assert(args[0].type == RVM_VALUE_TYPE_DOUBLE);

    double double_val = args[0].u.double_value;

    double res        = fabs(double_val);

    *return_size      = 1;
    *return_list      = new_native_return_list(*return_size);
    RETURN_LIST_SET_DOUBLE(*return_list, 0, res);
}


/*
 * Package: math
 * Function: sqrt
 * Type: @native
 */
void std_lib_math_sqrt(Ring_VirtualMachine* rvm,
                       unsigned int arg_count, RVM_Value* args,
                       unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 1);
    assert(args[0].type == RVM_VALUE_TYPE_DOUBLE);

    double double_val = args[0].u.double_value;

    double res        = sqrt(double_val);

    *return_size      = 1;
    *return_list      = new_native_return_list(*return_size);
    RETURN_LIST_SET_DOUBLE(*return_list, 0, res);
}

/*
 * Package: math
 * Function: pow
 * Type: @native
 */
void std_lib_math_pow(Ring_VirtualMachine* rvm,
                      unsigned int arg_count, RVM_Value* args,
                      unsigned int* return_size, RVM_Value** return_list) {

    assert(arg_count == 2);
    assert(args[0].type == RVM_VALUE_TYPE_DOUBLE);
    assert(args[1].type == RVM_VALUE_TYPE_DOUBLE);

    double x     = args[0].u.double_value;
    double y     = args[1].u.double_value;

    double res   = pow(x, y);

    *return_size = 1;
    *return_list = new_native_return_list(*return_size);
    RETURN_LIST_SET_DOUBLE(*return_list, 0, res);
}