#include "clipp.h"
#include "ring.hpp"
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

/*
 * 交互式调试 Ring Virtual Machine
 *
 * return 0: 继续运行
 *        else: 退出
 */
int debug_rvm_interactive(Ring_VirtualMachine* rvm,
                          RVM_Function*        function,
                          RVM_Byte*            code_list,
                          unsigned int         code_size,
                          unsigned int         pc,
                          unsigned int         caller_stack_base) {

    debug_exec_info_with_white("\t");

    // get terminal windows size
    struct winsize terminal_size;
    if (isatty(STDERR_FILENO) == 0 || ioctl(STDERR_FILENO, TIOCGWINSZ, &terminal_size) < 0) {
        ring_error_report("ioctl TIOCGWINSZ error");
    }

    if (terminal_size.ws_row < 41 || terminal_size.ws_col < 154) {
        ring_error_report("In DEBUG_RVM_INTERACTIVE Mode:\n"
                          "Current terminal window size: height:%d, width:%d\n"
                          "Please adjust terminal window size: height > 41, width > 154\n",
                          terminal_size.ws_row, terminal_size.ws_col);
    }

    STDERR_CLEAR_SCREEN;
    ring_vm_dump_runtime_stack(rvm->runtime_stack, caller_stack_base, 1, 0);
    ring_vm_code_dump(function, code_list, code_size, pc, 1, 70);

    STDERR_MOVE_CURSOR(terminal_size.ws_row - 10, 0);
    fprintf(stderr, "-------------Operation-----------\n");
    fprintf(stderr, "stdout redirect to: %s\n", DEBUG_RVM_INTERACTIVE_STDOUT_FILE);
    fprintf(stderr, "press 'help': get help message.\n");


    vm_debugger_cli(rvm);


    fflush(stderr);


    return 0;
}

#define VM_DB_PREFIX "rvm-debugger>>>"
#define VM_DB_HISTORY_FILE "ring-rvm-debugger-history-command.txt"
#define VM_DB_UNKNOW_COMMAND                                               \
    fprintf(stderr, LOG_COLOR_RED);                                        \
    fprintf(stderr, "Unknow command `%s`, type `help` find tip.\n", line); \
    fprintf(stderr, LOG_COLOR_CLEAR);

std::string vm_db_command_help_message =
    "Ring Debugger Usage: \n"
    "\n"
    "        <command> [arguments]\n"
    "\n"
    "Basic Commands:\n"
    "        help(?)                             :List of available commands.\n"
    "        clear                               :Clear the screen.\n"
    "        quit(q)                             :Quit from the debugger. The program being executed is aborted.\n"
    "\n"
    "        global                              :Print the global variables.\n"
    "        local                               :Print the local variables.\n"
    "        bt                                  :Print a stack trace, with the most recent frame at the top.\n"
    "\n"
    "Exec Commands:\n"
    "        cont      (c)                       :Continue execution, only stop when a breakpoint is encountered.\n"
    "        \n"
    "        step over (n)                       :Executes the current line of code and moves to the next line.\n"
    "        step into (i)                       :Enters the current function or method and executes it line by line.\n"
    "        step out  (o)                       :Exits the current function or method and returns to the caller.\n"
    "\n"
    "Breakpoints Commands:\n"
    "        break set   <line-number>           :Set a break at *line-number*.\n"
    "        break unset <line-number>           :Unset a breakpoint at *line-number*.\n"
    "        break list                          :List  all the breakpoints.\n"
    "        break clear                         :Clear all the breakpoints.\n"
    "\n"
    "Source Code Commands:\n"
    "        code list (l)                       :list ring source code\n"
    "\n";


int vm_debugger_cli(Ring_VirtualMachine* rvm) {
    bool  is_exit = false;
    char* line;


    // step-2. read & parse & exec command
    while (1) {
        bool      break_read_input = false;
        VM_DB_Arg vm_db_arg;
        char      line_buffer[1024];

        // step-2.1 read & parse command
        fprintf(stderr, "\n");
        fprintf(stderr, VM_DB_PREFIX);
        line = fgets(line_buffer, sizeof(line_buffer), stdin);
        if (line == NULL) {
            // ctrl-c ctrl-d
            fprintf(stderr, "Exit Ring Virtual Machine Debugger...\n");
            exit(0);
        }
        if (strlen(line) == 0) {
            continue;
        }
        if (strlen(line) == 1 && line[0] == '\n') {
            // press <Enter>
            // 继续执行虚拟机
            // 退出 cli
            return 0;
        }

        vm_db_arg = vm_db_parse_command(line);
        if (vm_db_arg.cmd == VM_DB_COMMAND_UNKNOW) {
            VM_DB_UNKNOW_COMMAND;
            goto END_GET_LINE;
        }


        // step-2.2 exec command
        fprintf(stderr, LOG_COLOR_GREEN);
        if (vm_db_arg.cmd == VM_DB_COMMAND_HELP) {
            fprintf(stderr, "[@]%s", vm_db_command_help_message.c_str());
        } else if (vm_db_arg.cmd == VM_DB_COMMAND_CLEAR) {
            // TODO:
            // STDOUT_CLEAR_SCREEN;
        } else if (vm_db_arg.cmd == VM_DB_COMMAND_QUIT) {
            fprintf(stderr, "[@]CMD: Exit Ring Virtual Machine Debugger...\n");

            break_read_input = true;
            is_exit          = true;
        } else if (vm_db_arg.cmd == VM_DB_COMMAND_STACK) {
            // 支持两种写法
            // stack 1 取出index为1 的 RVM_Value
            // stack 1-10 取出index为 1-9 的 RVM_Value, 左闭右开

            unsigned int begin_index = 0;
            unsigned int end_index   = 0;

            std::size_t  split_mark  = vm_db_arg.argument.find("-");
            if (split_mark != std::string::npos) {
                begin_index = atoi(vm_db_arg.argument.substr(0, split_mark).c_str());
                end_index   = atoi(vm_db_arg.argument.substr(split_mark + 1, vm_db_arg.argument.size()).c_str());
            } else {
                unsigned int tmp = atoi(vm_db_arg.argument.c_str());
                begin_index      = tmp;
                end_index        = tmp + 1;
            }

            fprintf(stderr, "stack: %u-%u\n", begin_index, end_index);
            for (unsigned int index = begin_index; index < end_index; index++) {
                RVM_Value*  value     = &(rvm->runtime_stack->data[index]);
                std::string type_str  = format_rvm_type(value);
                std::string value_str = format_rvm_value(value);
                std::string format    = type_str + "(" + value_str + ")";

                fprintf(stderr, "    index[%u] value:%s\n", index, format.c_str());
            }
        }


    END_GET_LINE:
        fprintf(stderr, LOG_COLOR_CLEAR);
        fflush(stdout);
        if (break_read_input) {
            break;
        }
    }


    fprintf(stderr, LOG_COLOR_CLEAR);

    if (is_exit) {
        exit(0);
    }
    return 0;
}

VM_DB_Arg vm_db_parse_command(const char* line) {
    std::vector<std::string> argv;
    VM_DB_COMMAND_TYPE       cmd = VM_DB_COMMAND_UNKNOW;
    std::string              argument;


    //
    argv = splitargs(line);

    // rule
    auto stack_rule =
        (clipp::value("line-number", argument));
    auto vm_db_command_rule =
        ((clipp::command(VM_DB_CMD_T_STACK).set(cmd, VM_DB_COMMAND_STACK), stack_rule)
         | clipp::command(VM_DB_CMD_T_CLEAR).set(cmd, VM_DB_COMMAND_CLEAR)
         | clipp::command(VM_DB_CMD_T_QUIT).set(cmd, VM_DB_COMMAND_QUIT) | clipp::command("q").set(cmd, VM_DB_COMMAND_QUIT)
         | clipp::command(VM_DB_CMD_T_HELP).set(cmd, VM_DB_COMMAND_HELP) | clipp::command("?").set(cmd, VM_DB_COMMAND_HELP));


    clipp::parse(argv, vm_db_command_rule);

    VM_DB_Arg result = VM_DB_Arg{
        .cmd      = cmd,
        .argument = argument,
    };
    printf("result info\n");
    return result;
}
