#include "clipp.h"
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
    "        dump   <filename>                              :dump bytecode detail after compile\n"
    "        rdb    <filename>                              :debug interactive\n"
    "        \n"
    "        man    <keyword>                               :get prompt of ring by keyword\n"
    "        version                                        :get Ring version\n"
    "        help                                           :get Ring version\n"
    "\n";
// "        build  <filename>                              :compile and generate bytecode\n"
// "        repl                                           :start interactive program\n"


Ring_Arg ring_parse_command(int argc, char** argv) {
    Ring_Arg          args;
    RING_COMMAND_TYPE cmd = RING_COMMAND_UNKNOW;
    std::string       input_file_name;
    std::string       keyword;


    auto              ring_command_rule =
        ((clipp::command(RING_CMD_T_RUN).set(cmd, RING_COMMAND_RUN), clipp::value("input-file", input_file_name))
         | (clipp::command(RING_CMD_T_DUMP).set(cmd, RING_COMMAND_DUMP), clipp::value("input-file", input_file_name))
         | (clipp::command(RING_CMD_T_RDB).set(cmd, RING_COMMAND_RDB), clipp::value("input-file", input_file_name))
         | (clipp::command(RING_CMD_T_MAN).set(cmd, RING_COMMAND_MAN), clipp::value("keyword", keyword))
         | clipp::command(RING_CMD_T_VERSION).set(cmd, RING_COMMAND_VERSION)
         | clipp::command(RING_CMD_T_HELP).set(cmd, RING_COMMAND_HELP));

    clipp::parse(argc, argv, ring_command_rule);

    // printf("cmd:%d\n", cmd);
    // printf("input_file_name:%s\n", input_file_name.c_str());
    // printf("keyword:%s\n", keyword.c_str());

    args = Ring_Arg{
        .cmd             = cmd,
        .input_file_name = input_file_name,
        .keyword         = keyword,
    };

    return args;
}


int main(int argc, char** argv) {

    Ring_Arg ring_arg;
    int      exit_code = 0;


#ifdef DEBUG_RVM_INTERACTIVE

    FILE*     fp;
    time_t    t  = time(NULL);
    struct tm tm = *localtime(&t);


    fp           = freopen(DEBUG_RVM_INTERACTIVE_STDOUT_FILE, "a", stdout);
    if (fp == nullptr) {
        ring_error_report("reopen stdout failed\n");
    }


    fprintf(stdout, LOG_COLOR_YELLOW);
    fprintf(stdout, "\n\n"
                    "@Start debug ring virtual machine in interactive mode...\n"
                    "@Date: %d-%02d-%02d %02d:%02d:%02d\n"
                    "@stdout redirect to: %s\n"
                    "@Stdout<<<\n",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,
            DEBUG_RVM_INTERACTIVE_STDOUT_FILE);
    fprintf(stdout, LOG_COLOR_CLEAR);

    fflush(stdout);
#endif

    // parse and switch ring command
    ring_arg = ring_parse_command(argc, argv);
    switch (ring_arg.cmd) {
    case RING_COMMAND_UNKNOW:
        fprintf(stderr, "Unknow command, type `ring help` find tip.\n");
        exit(ERROR_CODE_COMMAND_ERROR);
        break;
    case RING_COMMAND_RUN:
        break;
    case RING_COMMAND_DUMP:
        break;
    case RING_COMMAND_RDB:
        break;
    case RING_COMMAND_VERSION:
        printf("%s \n", RING_VERSION);
        exit(ERROR_CODE_SUCCESS);
        break;
    case RING_COMMAND_MAN:
        ring_give_man_help(ring_arg.keyword.c_str());
        exit(ERROR_CODE_SUCCESS);
        break;
    case RING_COMMAND_HELP:
        fprintf(stderr, "%s", command_help_message.c_str());
        exit(ERROR_CODE_SUCCESS);
        break;
    default:
        break;
    }


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
                                                             (char*)ring_arg.input_file_name.c_str());
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

    if (ring_arg.cmd == RING_COMMAND_DUMP) {
        // Only dump `main` package bytecode detail.
        package_executer_dump(executer_entry->main_package_executer);
        return 0;
    }

    if (ring_arg.cmd == RING_COMMAND_RDB) {
        register_debugger(ring_vm, ring_arg);
    }

    // Step-6: 加载虚拟机
    ring_virtualmachine_load_executer(ring_vm, executer_entry);

    // Step-7: 初始化虚拟机
    ring_virtualmachine_init(ring_vm);

    // Step-8: 运行虚拟机
    exit_code = ring_execute_vm_code(ring_vm);


#ifdef DEBUG_RVM_INTERACTIVE
    fprintf(stdout, LOG_COLOR_YELLOW);
    fprintf(stdout, "@End interactive session.\n"
                    "\n\n");
    fprintf(stdout, LOG_COLOR_CLEAR);
    fclose(stdout);
#endif

    return exit_code;
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


int register_debugger(Ring_VirtualMachine* rvm, Ring_Arg args) {
    RVM_DebugConfig* debug_config    = (RVM_DebugConfig*)mem_alloc(NULL_MEM_POOL, sizeof(RVM_DebugConfig));
    debug_config->enable             = true;
    debug_config->trace_dispatch     = debug_trace_dispatch;
    debug_config->enable_trace_event = 0;
    debug_config->stop_at_entry      = true;
    debug_config->display_globals    = false;
    debug_config->display_locals     = false;
    debug_config->display_call_stack = false;
    debug_config->step_cmd           = RDB_COMMAND_STEP_UNKNOW;
    debug_config->break_points       = std::vector<unsigned int>{};

    SET_TRACE_EVENT_ALL(debug_config);

    rvm->debug_config = debug_config;

    printf(LOG_COLOR_YELLOW);
    printf("%s\n", RING_VERSION);
    printf("Start Ring Debugger...\n");
    printf("\n");
    printf("Input file:%s\n", args.input_file_name.c_str());
    printf(LOG_COLOR_CLEAR);

    return 0;
}