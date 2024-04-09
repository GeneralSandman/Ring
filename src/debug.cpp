#include "clipp.h"
#include "ring.hpp"
#include <algorithm>
#include <iostream>


/*
调试器一般有这么几个功能

1. 设置断点：在编译器中添加断点的功能，允许用户在需要时设置断点。当虚拟机执行到断点处时，暂停执行并进入调试模式。

2. 单步执行：实现单步执行功能，允许用户逐步执行虚拟机指令，方便用户跟踪程序执行过程。

3. 变量查看：提供查看当前栈状态、局部变量、全局变量等的功能，让用户可以查看程序中的变量值。

4. 函数跟踪：记录函数调用堆栈，显示当前函数调用链，帮助用户跟踪函数调用关系。

5. 错误处理：捕获运行时错误，并提供错误信息显示和定位功能，帮助用户快速定位问题。

6. 用户交互界面：设计一个友好的用户交互界面，让用户可以方便地操作调试功能，设置断点、单步执行、查看变量等。

7. 调试命令：设计一些调试命令，如继续执行、打印变量、查看堆栈等，让用户可以通过命令来控制调试过程。

*/


/*
 * ring debugger 实现方式
 *
 * 1. 通过 ring rdb <input-file> 调用debugger
 * 2. 在main函数中 对 rvm 注册debug 回调函数 debug_trace_dispatch
 * 3. 在rvm中执行字节码的过程中, 调用注册的回调函数 debug_trace_dispatch
 * 4. 可以在 debug_trace_dispatch 获取 event 和当前的 frame信息
 *
 *
 * 1. 通过 linenoise 来实现输入提示功能
 * 2. 通过 clipp 来实现命令的解析
 */

/*
 * ring debugger 当前实现的功能
 *
 * 1. cont/c: 继续运行
 */


#define RDB_PREFIX "rdb>>> "
#define RDB_HISTORY_FILE "ring-rdb-history-command.txt"

#define RDB_UNKNOW_COMMAND                                        \
    printf(LOG_COLOR_RED);                                        \
    printf("Unknow command `%s`, type `help` find tip.\n", line); \
    printf(LOG_COLOR_CLEAR);


std::string rdb_command_help_message =
    "Ring Debugger Usage: \n"
    "\n"
    "        <command> [arguments]\n"
    "\n"
    "Commands:\n"
    "    \n"
    "        help(?)                             :get help message\n"
    "        clear                               :clear screen\n"
    "        quit(q)                             :quit rdb\n"
    "\n"
    "        global                              :list global variables\n"
    "        local                               :list local variables\n"
    "        bt                                  :show call stack\n"
    "\n"
    "Exec Commands:\n"
    "        cont      (c)                       :continue running until hit break-point\n"
    "        step over (n)                       :whihout into function\n"
    "        step into (i)                       :into function\n"
    "        step out  (o)                       :run to current function return\n"
    "\n"
    "Breakpoints Commands:\n"
    "        break set   <line-number>           :set    break point at line-number\n"
    "        break unset <line-number>           :unset  break point at line-number\n"
    "        break list                          :list   all break points\n"
    "        break clear                         :delete all break points\n"
    "\n";


std::vector<RDB_Command> rdb_commands = {
    {
        .token       = "-",
        .rule        = {},
        .description = "-",
        .sub_command = std::vector<RDB_Command>{},
    },

    {
        .token       = RDB_CMD_T_HELP,
        .rule        = {},
        .description = "get help message",
        .sub_command = std::vector<RDB_Command>{},
    },
    {
        .token       = RDB_CMD_T_CLEAR,
        .rule        = {},
        .description = "clear screen",
        .sub_command = std::vector<RDB_Command>{},
    },
    {
        .token       = RDB_CMD_T_QUIT,
        .rule        = {},
        .description = "quit rdb",
        .sub_command = std::vector<RDB_Command>{},
    },

    {
        .token       = RDB_CMD_T_GLOBAL,
        .rule        = {},
        .description = "list global variables",
        .sub_command = std::vector<RDB_Command>{},
    },
    {
        .token       = RDB_CMD_T_LOCAL,
        .rule        = {},
        .description = "list local variables",
        .sub_command = std::vector<RDB_Command>{},
    },
    {
        .token       = RDB_CMD_T_CONT,
        .rule        = {},
        .description = "continue running",
        .sub_command = std::vector<RDB_Command>{},
    },
    {
        .token       = RDB_CMD_T_BT,
        .rule        = {},
        .description = "show call stack",
        .sub_command = std::vector<RDB_Command>{},
    },


    {
        .token       = RDB_CMD_T_BREAK,
        .rule        = std::vector<std::string>{"break", "{set|unset|list|clear}", "[arguments]"},
        .description = "breakpoints commands",
        .sub_command = std::vector<RDB_Command>{
            {
                .token       = "-",
                .rule        = {},
                .description = "-",
                .sub_command = std::vector<RDB_Command>{},
            },
            {
                .token       = RDB_CMD_T_BREAK_SET,
                .rule        = std::vector<std::string>{"break", "set", "<line-number>"},
                .description = "set break-point at line-number",
                .sub_command = std::vector<RDB_Command>{},
            },
            {
                .token       = RDB_CMD_T_BREAK_UNSET,
                .rule        = std::vector<std::string>{"break", "unset", "<line-number>"},
                .description = "unset break-point at line-number",
                .sub_command = std::vector<RDB_Command>{},
            },
            {
                .token       = RDB_CMD_T_BREAK_LIST,
                .rule        = std::vector<std::string>{"break", "list"},
                .description = "list all break-point",
                .sub_command = std::vector<RDB_Command>{},
            },
            {
                .token       = RDB_CMD_T_BREAK_CLEAR,
                .rule        = std::vector<std::string>{"break", "clear"},
                .description = "clear all break-point",
                .sub_command = std::vector<RDB_Command>{},
            },
        },
    },

    {
        .token       = RDB_CMD_T_STEP,
        .rule        = std::vector<std::string>{"step", "{over|into|out}"},
        .description = "step actions",
        .sub_command = std::vector<RDB_Command>{
            {
                .token       = "-",
                .rule        = {},
                .description = "-",
                .sub_command = {},
            },
            {
                .token       = RDB_CMD_T_STEP_OVER,
                .rule        = std::vector<std::string>{"step", "over"},
                .description = "step over action",
                .sub_command = std::vector<RDB_Command>{},
            },
            {
                .token       = RDB_CMD_T_STEP_INTO,
                .rule        = std::vector<std::string>{"step", "into"},
                .description = "step into action",
                .sub_command = std::vector<RDB_Command>{},
            },
            {
                .token       = RDB_CMD_T_STEP_OUT,
                .rule        = std::vector<std::string>{"step", "out"},
                .description = "step out action",
                .sub_command = std::vector<RDB_Command>{},
            },
        },
    },

    {
        .token       = RDB_CMD_T_CODE,
        .rule        = {},
        .description = "list source file code",
        .sub_command = std::vector<RDB_Command>{},
    },

};

static unsigned int trace_count = 0;

//
int debug_trace_dispatch(RVM_Frame* frame, const char* event, const char* arg) {

    RVM_DebugConfig* debug_config = frame->rvm->debug_config;
    std::string      func_name;

    func_name = "$ring!start()";
    if (frame->call_info != nullptr
        && frame->call_info->callee_function != nullptr) {
        func_name = std::string(frame->call_info->callee_function->func_name) + "()";
    }

    if (str_eq(event, TRACE_EVENT_CALL)
        && str_eq(func_name.c_str(), "$ring!start()")) {
        if (debug_config->stop_at_entry) {
            event = TRACE_EVENT_SAE;
        }
    }


#ifdef DEBUG_RDB_TRACE_DISPATH_DETAIL
    // printf("---debug_trace_dispatch[%u]---\n", trace_count);
    // printf("|[@]event:            %s\n", event);
    // printf("|[@]current_function: %s\n", frame->callee_func);
    // printf("|[@]next_opcode:      %s\n", frame->next_opcode);
    // printf("|[@]source_line_num:  %u\n", frame->source_line_number);
    // printf("---debug_trace_dispatch---\n");
    // printf("\n\n");
#endif


    if (str_eq(event, TRACE_EVENT_SAE)) {
        if (ISSET_TRACE_EVENT_SAE(debug_config))
            dispath_sae(frame, event, arg);
    } else if (str_eq(event, TRACE_EVENT_OPCODE)) {
        if (ISSET_TRACE_EVENT_OPCODE(debug_config))
            dispath_opcode(frame, event, arg);
    } else if (str_eq(event, TRACE_EVENT_LINE)) {
        if (ISSET_TRACE_EVENT_LINE(debug_config))
            dispath_line(frame, event, arg);
    } else if (str_eq(event, TRACE_EVENT_CALL)) {
        if (ISSET_TRACE_EVENT_CALL(debug_config))
            dispath_call(frame, event, arg);
    } else if (str_eq(event, TRACE_EVENT_RETURN)) {
        if (ISSET_TRACE_EVENT_RETURN(debug_config))
            dispath_return(frame, event, arg);
    } else if (str_eq(event, TRACE_EVENT_EXIT)) {
        if (ISSET_TRACE_EVENT_EXIT(debug_config))
            dispath_exit(frame, event, arg);
    }


    trace_count++;

    return 0;
}

int dispath_sae(RVM_Frame* frame, const char* event, const char* arg) {

    printf(LOG_COLOR_GREEN);
    printf("[@]stop at entry: main()\n");
    printf(LOG_COLOR_CLEAR);


    rdb_cli(frame, event, arg);


    printf(LOG_COLOR_CLEAR);
    return 0;
}

int dispath_opcode(RVM_Frame* frame, const char* event, const char* arg) {
    return 0;
}

int dispath_line(RVM_Frame* frame, const char* event, const char* arg) {

    RVM_DebugConfig*           debug_config = frame->rvm->debug_config;
    std::vector<unsigned int>& break_points = debug_config->break_points;
    RDB_COMMAND_STEP_TYPE&     step_cmd     = debug_config->step_cmd;
    std::string                location;

    // 1. check trace event
    printf(LOG_COLOR_GREEN);
    if (step_cmd != RDB_COMMAND_STEP_UNKNOW) {

#ifdef DEBUG_RDB_TRACE_DISPATH_DETAIL
        if (step_cmd == RDB_COMMAND_STEP_OVER) {
            printf("[@]step over, stop.\n");
        } else if (step_cmd == RDB_COMMAND_STEP_INTO) {
            printf("[@]step into, stop.\n");
        } else if (step_cmd == RDB_COMMAND_STEP_OUT) {
            printf("[@]step out, stop.\n");
        }
#endif

        location = format_rvm_current_func(frame->rvm, frame->source_line_number);
        printf("[@]stop at: %s\n", location.c_str());

        step_cmd = RDB_COMMAND_STEP_UNKNOW;

    } else {
        // check hit breakpoints
        int hit_breakpoint_num = -1;

        for (int i = 0; i < break_points.size(); i++) {
            if (break_points[i] == frame->source_line_number) {
                hit_breakpoint_num = i;
                break;
            }
        }

        if (hit_breakpoint_num != -1) {
            location = format_rvm_current_func(frame->rvm, frame->source_line_number);
            printf("[@]hit breakpoint num:%d, stop at: %s\n", hit_breakpoint_num, location.c_str());
        } else {
            goto END_DISPATH_LINE;
        }
    }
    printf(LOG_COLOR_CLEAR);


    printf(LOG_COLOR_GREEN);
    if (debug_config->display_globals) {
        printf("[@]globals: %lu\n", frame->globals.size());
        for (std::pair<std::string, RVM_Value*>& global : frame->globals) {
            std::string type  = format_rvm_type(global.second);
            std::string value = format_rvm_value(global.second);
            printf("    %20s: %10s %s\n", global.first.c_str(), type.c_str(), value.c_str());
        }
    }

    if (debug_config->display_locals) {
        printf("[@]locals: %lu\n", frame->locals.size());
        for (std::pair<std::string, RVM_Value*>& local : frame->locals) {
            std::string type  = format_rvm_type(local.second);
            std::string value = format_rvm_value(local.second);
            printf("    %20s: %10s %s\n", local.first.c_str(), type.c_str(), value.c_str());
        }
    }

    if (debug_config->display_call_stack) {
        std::string call_stack;
        call_stack = format_rvm_call_stack(frame->rvm);
        printf("[@]call stack:\n");
        printf("%s", call_stack.c_str());
    }
    printf(LOG_COLOR_CLEAR);


    rdb_cli(frame, event, arg);


END_DISPATH_LINE:
    printf(LOG_COLOR_CLEAR);
    return 0;
}

int dispath_call(RVM_Frame* frame, const char* event, const char* arg) {
    RVM_DebugConfig* debug_config = frame->rvm->debug_config;

    debug_config->call_func_deep_count++;

    if (debug_config->step_cmd == RDB_COMMAND_STEP_OVER) {
        if (debug_config->step_over_deep_count < debug_config->call_func_deep_count) {
            UNSET_TRACE_EVENT_LINE(debug_config);
        }
    }
    return 0;
}

int dispath_return(RVM_Frame* frame, const char* event, const char* arg) {
    RVM_DebugConfig* debug_config = frame->rvm->debug_config;

    debug_config->call_func_deep_count--;

    if (debug_config->step_cmd == RDB_COMMAND_STEP_OVER) {
        if (debug_config->step_over_deep_count == debug_config->call_func_deep_count) {
            SET_TRACE_EVENT_LINE(debug_config);
        }
    } else if (debug_config->step_cmd == RDB_COMMAND_STEP_OUT) {
        if (debug_config->step_out_deep_count - 1 == debug_config->call_func_deep_count) {
            SET_TRACE_EVENT_LINE(debug_config);
        }
    }

    return 0;
}

int dispath_exit(RVM_Frame* frame, const char* event, const char* arg) {
    printf(LOG_COLOR_GREEN);
    printf("[@]Process exited, code:%d\n", 0);
    printf(LOG_COLOR_CLEAR);

    return 0;
}


// 启动命令行交互式输入输出
int rdb_cli(RVM_Frame* frame, const char* event, const char* arg) {
    char*                      line;
    std::string                call_stack;
    unsigned int               breakpoint_line;
    RVM_DebugConfig*           debug_config = frame->rvm->debug_config;

    std::vector<unsigned int>& break_points = frame->rvm->debug_config->break_points;

    // 1. config linenoise
    linenoiseSetMultiLine(1);
    linenoiseSetCompletionCallback(rdb_input_completion);
    linenoiseSetHintsCallback(rdb_input_hints);
    linenoiseHistoryLoad(RDB_HISTORY_FILE);
    linenoiseHistorySetMaxLen(1024);


    // 2. read ring debugger command
    while (1) {
        bool    break_read_input = false;
        RDB_Arg rdb_arg;

        // read and parse command
        printf("\n");
        line = linenoise(RDB_PREFIX);
        if (line == NULL) {
            // ctrl-c ctrl-d
            printf("Exit Ring Debugger...\n");
            exit(0);
        }
        if (strlen(line) == 0) {
            continue;
        }

        rdb_arg = rdb_parse_command(line);
        if (rdb_arg.cmd == RDB_COMMAND_UNKNOW) {
            RDB_UNKNOW_COMMAND;
            goto END_GET_LINE;
        }


        // exec command
        printf(LOG_COLOR_GREEN);
        if (rdb_arg.cmd == RDB_COMMAND_HELP) {
            printf("[@]%s", rdb_command_help_message.c_str());
        } else if (rdb_arg.cmd == RDB_COMMAND_CLEAR) {
            STDOUT_CLEAR_SCREEN;
        } else if (rdb_arg.cmd == RDB_COMMAND_QUIT) {
            printf("[@]CMD: Exit Ring Debugger...\n");
            exit(0);
        } else if (rdb_arg.cmd == RDB_COMMAND_GLOBAL) {
            printf("[@]globals:\n");
            for (std::pair<std::string, RVM_Value*>& global : frame->globals) {
                std::string type  = format_rvm_type(global.second);
                std::string value = format_rvm_value(global.second);
                printf("    %20s: %10s %s\n", global.first.c_str(), type.c_str(), value.c_str());
            }
        } else if (rdb_arg.cmd == RDB_COMMAND_LOCAL) {
            printf("[@]locals:\n");
            for (std::pair<std::string, RVM_Value*>& local : frame->locals) {
                std::string type  = format_rvm_type(local.second);
                std::string value = format_rvm_value(local.second);
                printf("    %20s: %10s %s\n", local.first.c_str(), type.c_str(), value.c_str());
            }
        } else if (rdb_arg.cmd == RDB_COMMAND_CONT) {
            printf("[@]CMD: Continuing...\n");
            break_read_input = true;
        } else if (rdb_arg.cmd == RDB_COMMAND_BT) {
            call_stack = format_rvm_call_stack(frame->rvm);
            printf("[@]call stack:\n");
            printf("%s", call_stack.c_str());
        } else if (rdb_arg.cmd == RDB_COMMAND_BREAK) {
            if (rdb_arg.break_cmd == RDB_COMMAND_BREAK_SET) {
                breakpoint_line = atoi(rdb_arg.argument.c_str());
                printf("[@]Breakpoint %lu set at %d\n",
                       break_points.size(),
                       breakpoint_line);
                break_points.push_back(breakpoint_line);
            } else if (rdb_arg.break_cmd == RDB_COMMAND_BREAK_UNSET) {
                breakpoint_line = atoi(rdb_arg.argument.c_str());
                printf("[@]Breakpoint %lu unset at %d\n",
                       break_points.size(),
                       breakpoint_line);
                break_points.erase(std::remove(break_points.begin(),
                                               break_points.end(),
                                               breakpoint_line),
                                   break_points.end());
            } else if (rdb_arg.break_cmd == RDB_COMMAND_BREAK_LIST) {
                printf("[@]Breakpoints:\n");
                printf("Num   Where\n");
                for (int i = 0; i < break_points.size(); i++) {
                    printf("%4d %4d\n", i, break_points[i]);
                }
            } else if (rdb_arg.break_cmd == RDB_COMMAND_BREAK_CLEAR) {
                printf("[@]Clear all breakpoint \n");
                break_points.clear();
            }
        } else if (rdb_arg.cmd == RDB_COMMAND_STEP) {
            // need update to debug_config
            debug_config->step_cmd = rdb_arg.step_cmd;

            switch (rdb_arg.step_cmd) {
            case RDB_COMMAND_STEP_OVER:
                debug_config->step_over_deep_count = debug_config->call_func_deep_count;
                printf("[@]CMD: Step over...\n");
                break;
            case RDB_COMMAND_STEP_INTO:
                printf("[@]CMD: Step into...\n");
                break;
            case RDB_COMMAND_STEP_OUT:
                debug_config->step_out_deep_count = debug_config->call_func_deep_count;
                printf("[@]CMD: Step out...\n");
                UNSET_TRACE_EVENT_LINE(debug_config);
                break;

            default:
                break;
            }


            break_read_input = true;
        }


        linenoiseHistoryAdd(line);

    END_GET_LINE:
        printf(LOG_COLOR_CLEAR);
        fflush(stdout);
        free(line);
        if (break_read_input) {
            break;
        }
    }


    linenoiseHistorySave(RDB_HISTORY_FILE);
    printf(LOG_COLOR_CLEAR);
    return 0;
}

RDB_Arg rdb_parse_command(const char* line) {
    std::vector<std::string> argv;
    RDB_COMMAND_TYPE         cmd       = RDB_COMMAND_UNKNOW;
    RDB_COMMAND_BREAK_TYPE   break_cmd = RDB_COMMAND_BREAK_UNKNOW;
    RDB_COMMAND_STEP_TYPE    step_cmd  = RDB_COMMAND_STEP_UNKNOW;
    std::string              argument;


    //
    argv = splitargs(line);

    // break points
    auto break_rule =
        ((clipp::command(RDB_CMD_T_BREAK_SET).set(break_cmd, RDB_COMMAND_BREAK_SET), clipp::value("line-number", argument))
         | (clipp::command(RDB_CMD_T_BREAK_UNSET).set(break_cmd, RDB_COMMAND_BREAK_UNSET), clipp::value("line-number", argument))
         | clipp::command(RDB_CMD_T_BREAK_LIST).set(break_cmd, RDB_COMMAND_BREAK_LIST)
         | clipp::command(RDB_CMD_T_BREAK_CLEAR).set(break_cmd, RDB_COMMAND_BREAK_CLEAR));
    // step action
    auto step_rule = (clipp::command(RDB_CMD_T_STEP_OVER).set(step_cmd, RDB_COMMAND_STEP_OVER)
                      | clipp::command(RDB_CMD_T_STEP_INTO).set(step_cmd, RDB_COMMAND_STEP_INTO)
                      | clipp::command(RDB_CMD_T_STEP_OUT).set(step_cmd, RDB_COMMAND_STEP_OUT)); // TODO: step out 后续支持

    auto rdb_command_rule =
        ((clipp::command(RDB_CMD_T_BREAK).set(cmd, RDB_COMMAND_BREAK), break_rule)
         | (clipp::command(RDB_CMD_T_STEP).set(cmd, RDB_COMMAND_STEP), step_rule)
         | clipp::command("n").set(cmd, RDB_COMMAND_STEP).set(step_cmd, RDB_COMMAND_STEP_OVER)
         | clipp::command("i").set(cmd, RDB_COMMAND_STEP).set(step_cmd, RDB_COMMAND_STEP_INTO)
         | clipp::command("o").set(cmd, RDB_COMMAND_STEP).set(step_cmd, RDB_COMMAND_STEP_OUT) // TODO: step out 后续支持
         | clipp::command(RDB_CMD_T_GLOBAL).set(cmd, RDB_COMMAND_GLOBAL)
         | clipp::command(RDB_CMD_T_LOCAL).set(cmd, RDB_COMMAND_LOCAL)
         | clipp::command(RDB_CMD_T_CONT).set(cmd, RDB_COMMAND_CONT) | clipp::command("c").set(cmd, RDB_COMMAND_CONT)
         | clipp::command(RDB_CMD_T_BT).set(cmd, RDB_COMMAND_BT)
         | clipp::command(RDB_CMD_T_CLEAR).set(cmd, RDB_COMMAND_CLEAR)
         | clipp::command(RDB_CMD_T_QUIT).set(cmd, RDB_COMMAND_QUIT) | clipp::command("q").set(cmd, RDB_COMMAND_QUIT)
         | clipp::command(RDB_CMD_T_STEP).set(cmd, RDB_COMMAND_STEP)
         | clipp::command(RDB_CMD_T_HELP).set(cmd, RDB_COMMAND_HELP) | clipp::command("?").set(cmd, RDB_COMMAND_HELP));


    clipp::parse(argv, rdb_command_rule);

    return RDB_Arg{
        .cmd       = cmd,
        .break_cmd = break_cmd,
        .step_cmd  = step_cmd,
        .argument  = argument,
    };
}


void rdb_input_completion(const char* buf, linenoiseCompletions* lc) {

    for (RDB_Command& cmd : rdb_commands) {
        if (str_eq_n(buf, cmd.token.c_str(), strlen(buf))) {
            linenoiseAddCompletion(lc, cmd.token.c_str());
        }

        for (RDB_Command& subs : cmd.sub_command) {
            if (str_eq_n(buf, subs.token.c_str(), strlen(buf))) {
                linenoiseAddCompletion(lc, subs.token.c_str());
            }
        }
    }
}

static std::string hit_str;

//
char* rdb_input_hints(const char* buf, int* color, int* bold) {
    hit_str                                 = "";

    *color                                  = 35;
    *bold                                   = 0;

    std::vector<std::string> args           = splitargs(buf);
    bool                     end_with_space = strlen(buf) && isspace(buf[strlen(buf) - 1]);
    int                      match_argc     = end_with_space ? args.size() : args.size() - 1;

    if (args.empty()) {
        return nullptr;
    }

    RDB_Arg rdb_arg = rdb_parse_command(buf);
    if (rdb_arg.cmd == RDB_COMMAND_UNKNOW) {
        return nullptr;
    }


    if (rdb_arg.cmd == RDB_COMMAND_HELP
        || rdb_arg.cmd == RDB_COMMAND_CLEAR
        || rdb_arg.cmd == RDB_COMMAND_QUIT
        || rdb_arg.cmd == RDB_COMMAND_GLOBAL
        || rdb_arg.cmd == RDB_COMMAND_LOCAL
        || rdb_arg.cmd == RDB_COMMAND_CONT
        || rdb_arg.cmd == RDB_COMMAND_BT) {

        hit_str = std::string("    // ") + rdb_commands[rdb_arg.cmd].description;

    } else if (rdb_arg.cmd == RDB_COMMAND_BREAK) {
        if (args.size() == 1 || match_argc == 1) {
            return (char*)" {set|unset|list|clear} [arguments]  // break-point";
        } else if (match_argc == 2) {

            if (rdb_arg.break_cmd == RDB_COMMAND_BREAK_UNKNOW) {
                return nullptr;
            }

            if (rdb_arg.break_cmd == RDB_COMMAND_BREAK_SET) {
                return (char*)" <line-number>    // set break-point at line-number";
            } else if (rdb_arg.break_cmd == RDB_COMMAND_BREAK_UNSET) {
                return (char*)" <line-number>    // unset break-point at line-number";
            } else if (rdb_arg.break_cmd == RDB_COMMAND_BREAK_LIST) {
                return (char*)"    // list all break-point";
            } else if (rdb_arg.break_cmd == RDB_COMMAND_BREAK_CLEAR) {
                return (char*)"    // clear all break-point";
            }
        } else if (match_argc == 3) {
            if (rdb_arg.break_cmd == RDB_COMMAND_BREAK_UNKNOW) {
                return nullptr;
            }

            hit_str = std::string("    // ") + rdb_commands[RDB_COMMAND_BREAK].sub_command[rdb_arg.break_cmd].description;
        }
    } else if (rdb_arg.cmd == RDB_COMMAND_STEP) {
        if (args.size() == 1 || match_argc == 1) {
            return (char*)" {over|into|out}  // step actions";
        } else if (match_argc == 2) {

            if (rdb_arg.step_cmd == RDB_COMMAND_STEP_UNKNOW) {
                return nullptr;
            }

            hit_str = std::string("    // ") + rdb_commands[RDB_COMMAND_STEP].sub_command[rdb_arg.step_cmd].description;
        }
    }


    return (char*)hit_str.c_str();
}
