#include "linenoise.h"
#include "ring.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>


std::string command_help_message =
    "Ring Command Usage: \n"
    "\n"
    "        ring <command> [arguments]\n"
    "\n"
    "All Commands:\n"
    "    \n"
    "        run    <filename>                              :compile and run Ring program\n"
    "        build  <filename>                              :compile and generate bytecode\n"
    "        dump   <filename>                              :dump bytecode detail after compile\n"
    "        rdb    <filename>                              :debug interactive\n"
    "        repl                                           :start interactive program\n"
    "        \n"
    "        man    <keyword>                               :get prompt of ring by keyword\n"
    "        version                                        :get Ring version\n"
    "        help                                           :get Ring version\n"
    "\n";


Args parse_args(int argc, char** argv) {
    char* command;
    char* input_file_name;
    char* keyword;
    Args  res;

    if (argc < 2) {
        goto ERR_ARG;
    }
    command = argv[1];
    if (str_eq(command, "repl")) {
        ring_repl();
        exit(ERROR_CODE_SUCCESS);
    } else if (str_eq(command, "version")) {
        printf("%s \n", RING_VERSION);
        exit(ERROR_CODE_SUCCESS);
    } else if (str_eq(command, "help")) {
        printf("%s", command_help_message.c_str());
        exit(ERROR_CODE_SUCCESS);
    }


    if (argc < 3) {
        goto ERR_ARG;
    }
    input_file_name = argv[2];
    if (str_eq(command, "run")) {
        res = Args{
            .command_run     = true,
            .command_dump    = false,
            .command_debug   = false,
            .input_file_name = input_file_name,
        };
        return res;
    } else if (str_eq(command, "build")) {
        printf("ring build\n");
        exit(ERROR_CODE_SUCCESS);
    } else if (str_eq(command, "dump")) {
        res = Args{
            .command_run     = false,
            .command_dump    = true,
            .command_debug   = false,
            .input_file_name = input_file_name,
        };
        return res;
    } else if (str_eq(command, "rdb")) {
        res = Args{
            .command_run     = false,
            .command_dump    = false,
            .command_debug   = true,
            .input_file_name = input_file_name,
        };
        return res;
    } else if (str_eq(command, "man")) {
        keyword = input_file_name;
        ring_give_man_help(keyword);
        exit(ERROR_CODE_SUCCESS);
    }

ERR_ARG:
    fprintf(stderr, "%s", command_help_message.c_str());
    exit(ERROR_CODE_COMMAND_ERROR);
}

int main(int argc, char** argv) {
    Args args;
    args = parse_args(argc, argv);

    /*
     *初始化编译阶段的 Memory Pool
     *
     * 在编译完成之后, destory_front_mem_pool
     * 解耦编译器前后端
     */
    init_front_mem_pool();


    /*
     * 初始化语法处理节点相关的struct
     */
    CompilerEntry* compiler_entry = compiler_entry_create();
    // FIX: 目前main package 只能有一个源文件
    // main package 源文件即为 ring run 指定的输入文件
    Package* main_package        = package_create_input_file(compiler_entry,
                                                             (char*)"main",
                                                             args.input_file_name);
    compiler_entry->main_package = main_package; // TODO: optimize the method of set main_package;

    /*
     * 初始化代码生成阶段相关的struct
     */
    ExecuterEntry*    executer_entry        = executer_entry_create();
    Package_Executer* main_package_executer = package_executer_create(executer_entry, (char*)"main");
    executer_entry->main_package_executer   = main_package_executer; // TODO: optimize the method of set main_package_executer;

    /*
     * 初始化虚拟机相关的struct
     */
    Ring_VirtualMachine* ring_vm = ring_virtualmachine_create();


    // Step-0: 预编译官方std包, 并生成vmcode
    compile_std_lib(compiler_entry, executer_entry);

    // Step-1: flex 词法分析，
    // Step-2: bison 语法分析，构建语法树
    // Step-3: 修正语法树
    package_compile(main_package);

    // Step-4: 生成虚拟机中间代码
    ring_generate_vm_code(compiler_entry, executer_entry);

    // Step-5: 链接符号表
    // Complier force destory memory of front-end.
    destory_front_mem_pool();

    if (args.command_dump) {
        // Only dump `main` package bytecode detail.
        package_executer_dump(executer_entry->main_package_executer);
        return 0;
    }

    if (args.command_debug) {
        register_debugger(ring_vm, args);
    }

    // Step-6: 加载虚拟机
    ring_virtualmachine_load_executer(ring_vm, executer_entry);

    // Step-7: 初始化虚拟机
    ring_virtualmachine_init(ring_vm);

    // Step-8: 运行虚拟机
    ring_execute_vm_code(ring_vm);

    return 0;
}


#define REPL_PREFIX "> "
#define REPL_HISTORY_FILE "ring-repl-history.txt"

int ring_repl() {
    printf("%s\n", RING_VERSION);
    printf("Start Ring REPL...\n\n");

    char* line;

    linenoiseSetMultiLine(1);
    linenoiseSetCompletionCallback(ring_repl_completion);
    linenoiseSetHintsCallback(ring_repl_hints);
    linenoiseHistoryLoad(REPL_HISTORY_FILE);

    while (1) {

        line = linenoise(REPL_PREFIX);
        if (line == NULL)
            break;


        /* Do something with the string. */
        if (line[0] != '\0' && line[0] != '/') {
            // printf("echo: '%s'\n", line);
            linenoiseHistoryAdd(line);               /* Add to the history. */
            linenoiseHistorySave(REPL_HISTORY_FILE); /* Save the history on disk. */
        } else if (!strncmp(line, "/historylen", 11)) {
            /* The "/historylen" command will change the history len. */
            int len = atoi(line + 11);
            linenoiseHistorySetMaxLen(len);
        } else if (line[0] == '/') {
            printf("Unreconized command: %s\n", line);
        }

        free(line);
    }
    return 0;
}

void ring_repl_completion(const char* buf, linenoiseCompletions* lc) {
    // if (buf[0] == 'h') {
    //     linenoiseAddCompletion(lc, "hello");
    //     linenoiseAddCompletion(lc, "hello 1");
    //     linenoiseAddCompletion(lc, "hello 2");
    // }
}

char* ring_repl_hints(const char* buf, int* color, int* bold) {
    *color = 35;
    *bold  = 0;

    if (str_eq(buf, "hello")) {
        return (char*)" World";
    } else if (str_eq(buf, "var") || str_eq(buf, "var ")) {
        return (char*)" bool/int/double/string/class identifier";
    } else if (str_eq(buf, "function") || str_eq(buf, "function ")) {
        return (char*)" identifier(arguments) { block }";
    }

    return nullptr;
}


int register_debugger(Ring_VirtualMachine* rvm, Args args) {
    RVM_DebugConfig* debug_config = (RVM_DebugConfig*)malloc(sizeof(RVM_DebugConfig));
    debug_config->enable          = true;
    debug_config->trace_dispatch  = debug_trace_dispatch;
    rvm->debug_config             = debug_config;

    printf("%s\n", RING_VERSION);
    printf("Start Ring Debugger...\n");
    printf("\n");
    printf("Input file:%s\n", args.input_file_name);

    return 0;
}