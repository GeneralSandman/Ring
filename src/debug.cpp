#include "ring.hpp"

// TODO: 在这里设计 debug callback相关的操作, 能够实现一个简单的 交互式 debugger
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

通过 linenoise 来实现输入提示功能

break <number>: 设置断点

print 打印: 这个比较复杂

*/

std::string rdb_command_help_message =
    "Ring Debugger Usage: \n"
    "\n"
    "        <command> [arguments]\n"
    "\n"
    "All Commands:\n"
    "    \n"
    "        globals,   g        :list global variables\n"
    "        locals,    l        :list local variables\n"
    "        cont,      c        :continue running\n"
    "        bt                  :show call stack\n"
    "        clear               :clear screen\n"
    "        quit,      q        :quit rdb\n"
    "        help                :get help message\n"
    "\n"
    "Breakpoints Commands:\n"
    "        break set <line-number>      :set break point at line-number\n"
    "        breaks                       :list all break points\n"
    "        break list                   :list all break points\n"
    "\n";

static unsigned int trace_count = 0;

//
int debug_trace_dispatch(RVM_Frame* frame, const char* event, const char* arg) {

#ifdef DEBUG_RDB_TRACE_DISPATH
    printf("---debug_trace_dispatch[%u]---\n", trace_count++);
    printf("|[+]event:            %s\n", event);
    // printf("[+]arg:              %s\n", arg);
    printf("|[+]current_function: %s\n", frame->callee_func);
    printf("|[+]next_opcode:      %s\n", frame->next_opcode);
    printf("|[+]source_line_num:  %u\n", frame->source_line_number);
    printf("---debug_trace_dispatch---\n");
    printf("\n\n");
#endif


    if (str_eq(event, TRACE_EVENT_LINE)) {
        dispath_line(frame, event, arg);
    } else if (str_eq(event, TRACE_EVENT_CALL)) {
        if (str_eq(frame->callee_func, "$ring!start()") && frame->rvm->debug_config->stop_at_entry) {
            dispath_line(frame, TRACE_EVENT_SAE, arg);
        } else {
            dispath_call(frame, event, arg);
        }
    } else if (str_eq(event, TRACE_EVENT_EXIT)) {
        dispath_exit(frame, event, arg);
    } else if (str_eq(event, TRACE_EVENT_OPCODE)) {
        dispath_opcode(frame, event, arg);
    }

    return 0;
}

#define RDB_PREFIX "rdb>>> "
#define RDB_HISTORY_FILE "ring-rdb-history-command.txt"

int dispath_line(RVM_Frame* frame, const char* event, const char* arg) {

    char*                    line;
    std::string              call_stack;
    std::vector<std::string> args;

    // 1. check trace event
    printf(LOG_COLOR_GREEN);
    if (str_eq(event, TRACE_EVENT_SAE)) {
        printf("[+]stop at entry");
    } else {
        int hit_breakpoint_num = -1;

        for (int i = 0; i < frame->rvm->debug_config->break_points.size(); i++) {
            if (frame->rvm->debug_config->break_points[i] == frame->source_line_number) {
                hit_breakpoint_num = i;
                break;
            }
        }

        if (hit_breakpoint_num != -1) {
            printf("[+]stop breakpoint num:%d where:%d\n", hit_breakpoint_num, frame->source_line_number);
        } else {
            goto END;
        }
    }
    printf(LOG_COLOR_CLEAR);


    // 2. config linenoise
    linenoiseSetMultiLine(1);
    linenoiseSetCompletionCallback(ring_rdb_completion);
    linenoiseSetHintsCallback(ring_rdb_hints);
    linenoiseHistoryLoad(RDB_HISTORY_FILE);
    linenoiseHistorySetMaxLen(1024);


    printf(LOG_COLOR_GREEN);
    if (frame->rvm->debug_config->display_globals) {
        printf("[+]globals: %lu\n", frame->globals.size());
        for (std::pair<std::string, RVM_Value*>& global : frame->globals) {
            std::string type  = format_rvm_type(global.second);
            std::string value = format_rvm_value(global.second);
            printf("    %20s: %10s %s\n", global.first.c_str(), type.c_str(), value.c_str());
        }
    }

    if (frame->rvm->debug_config->display_locals) {
        printf("[+]locals: %lu\n", frame->locals.size());
        for (std::pair<std::string, RVM_Value*>& local : frame->locals) {
            std::string type  = format_rvm_type(local.second);
            std::string value = format_rvm_value(local.second);
            printf("    %20s: %10s %s\n", local.first.c_str(), type.c_str(), value.c_str());
        }
    }

    if (frame->rvm->debug_config->display_call_stack) {
        call_stack = format_rvm_call_stack(frame->rvm);
        printf("[+]call stack:\n");
        printf("%s", call_stack.c_str());
    }
    printf(LOG_COLOR_CLEAR);


    // 3. read ring debugger command
    while (1) {
        bool is_break = false;

        // read and parse command
        printf("\n");
        line = linenoise(RDB_PREFIX);
        if (line == NULL) {
            printf("Exit Ring Debugger...\n");
            exit(0);
        }
        args = splitargs(line);
        if (strlen(line) == 0 || args.empty()) {
            continue;
        }
        linenoiseHistoryAdd(line);
        linenoiseHistorySave(RDB_HISTORY_FILE);


        // exec command
        printf(LOG_COLOR_GREEN);
        if (str_eq(args[0].c_str(), "globals") || str_eq(args[0].c_str(), "g")) {

            printf("[+]globals:\n");
            for (std::pair<std::string, RVM_Value*>& global : frame->globals) {
                std::string type  = format_rvm_type(global.second);
                std::string value = format_rvm_value(global.second);
                printf("    %20s: %10s %s\n", global.first.c_str(), type.c_str(), value.c_str());
            }

        } else if (str_eq(args[0].c_str(), "locals") || str_eq(args[0].c_str(), "l")) {

            printf("[+]locals:\n");
            for (std::pair<std::string, RVM_Value*>& local : frame->locals) {
                std::string type  = format_rvm_type(local.second);
                std::string value = format_rvm_value(local.second);
                printf("    %20s: %10s %s\n", local.first.c_str(), type.c_str(), value.c_str());
            }

        } else if (str_eq(args[0].c_str(), "cont") || str_eq(args[0].c_str(), "c")) {

            printf("Continuing...\n");
            is_break = true;

        } else if (str_eq(args[0].c_str(), "break") || str_eq(args[0].c_str(), "b")) {
            if (args.size() < 2) {
                printf("Usage: break set <line>\n");
                printf("       break list\n");
                continue;
            }

            if (str_eq(args[1].c_str(), "set")) {
                if (args.size() != 3) {
                    printf("Usage: break set <line>\n");
                    continue;
                }

                unsigned int break_line = atoi(args[2].c_str());

                printf("Breakpoint %lu at %d\n",
                       frame->rvm->debug_config->break_points.size(),
                       break_line);
                frame->rvm->debug_config->break_points.push_back(break_line);

            } else if (str_eq(args[1].c_str(), "list")) {
                printf("Breakpoints:\n");
                printf("Num   Where\n");
                for (int i = 0; i < frame->rvm->debug_config->break_points.size(); i++) {
                    printf("%4d %4d\n", i, frame->rvm->debug_config->break_points[i]);
                }
            }

        } else if (str_eq(args[0].c_str(), "bt")) {

            call_stack = format_rvm_call_stack(frame->rvm);
            printf("[+]call stack:\n");
            printf("%s", call_stack.c_str());

        } else if (str_eq(args[0].c_str(), "quit") || str_eq(args[0].c_str(), "q")) {

            printf("Exit Ring Debugger...\n");
            exit(0);

        } else if (str_eq(args[0].c_str(), "clear")) {

            CLEAR_SCREEN;

        } else if (str_eq(args[0].c_str(), "help")) {
            printf("%s", rdb_command_help_message.c_str());
        } else {

            printf(LOG_COLOR_RED);
            printf("Unknow command `%s`, use `help` find tip.\n", args[0].c_str());
            printf(LOG_COLOR_CLEAR);
        }


        printf(LOG_COLOR_CLEAR);
        fflush(stdout);
        free(line);

        if (is_break) {
            break;
        }
    }

END:
    printf(LOG_COLOR_CLEAR);
    return 0;
}

int dispath_call(RVM_Frame* frame, const char* event, const char* arg) {
    return 0;
}

int dispath_exit(RVM_Frame* frame, const char* event, const char* arg) {
    printf(LOG_COLOR_GREEN);
    printf("[Process exited, code:%d]\n", 0);
    printf(LOG_COLOR_CLEAR);

    return 0;
}

int dispath_opcode(RVM_Frame* frame, const char* event, const char* arg) {
    return 0;
}


void ring_rdb_completion(const char* buf, linenoiseCompletions* lc) {
    if (buf[0] == 'h') {
        linenoiseAddCompletion(lc, "hello");
        linenoiseAddCompletion(lc, "hello 1");
        linenoiseAddCompletion(lc, "hello 2");
    }
}

char* ring_rdb_hints(const char* buf, int* color, int* bold) {
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

/* Split a line into arguments, where every argument can be in the
 * following programming-language REPL-alike form:
 *
 * foo bar "newline are supported\n" and "\xff\x00otherstuff"
 *
 * The function returns the allocated tokens on success, even when the
 * input string is empty, or NULL if the input contains unbalanced
 * quotes or closed quotes followed by non space characters
 * as in: "foo"bar or "foo'
 */
std::vector<std::string> splitargs(const char* line) {
    const char*              p = line;

    std::string              current;
    std::vector<std::string> args;

    while (1) {
        // skip blanks
        while (*p && isspace((int)*p)) p++;

        if (*p) {
            /* get a token */
            int inq  = 0; /* set to 1 if we are in "quotes" */
            int insq = 0; /* set to 1 if we are in 'single quotes' */
            int done = 0;

            while (!done) {
                if (inq) {
                    if (*p == '\\' && *(p + 1) == 'x' && isxdigit((int)*(p + 2)) && isxdigit((int)*(p + 3))) {
                        unsigned char byte;

                        byte = (hex_digit_to_int(*(p + 2)) * 16) + hex_digit_to_int(*(p + 3));
                        current += char(byte);
                        p += 3;
                    } else if (*p == '\\' && *(p + 1)) {
                        char c;

                        p++;
                        switch (*p) {
                        case 'n': c = '\n'; break;
                        case 'r': c = '\r'; break;
                        case 't': c = '\t'; break;
                        case 'b': c = '\b'; break;
                        case 'a': c = '\a'; break;
                        default: c = *p; break;
                        }
                        current += std::to_string(c);
                    } else if (*p == '"') {
                        /* closing quote must be followed by a space or
                         * nothing at all. */
                        if (*(p + 1) && !isspace((int)*(p + 1)))
                            goto err;
                        done = 1;
                    } else if (!*p) {
                        /* unterminated quotes */
                        goto err;
                    } else {
                        current += *p;
                    }
                } else if (insq) {
                    if (*p == '\\' && *(p + 1) == '\'') {
                        p++;
                        current += "'";
                    } else if (*p == '\'') {
                        /* closing quote must be followed by a space or
                         * nothing at all. */
                        if (*(p + 1) && !isspace((int)*(p + 1)))
                            goto err;
                        done = 1;
                    } else if (!*p) {
                        /* unterminated quotes */
                        goto err;
                    } else {
                        current += *p;
                    }
                } else {
                    switch (*p) {
                    case ' ':
                    case '\n':
                    case '\r':
                    case '\t':
                    case '\0':
                        done = 1;
                        break;
                    case '"':
                        inq = 1;
                        break;
                    case '\'':
                        insq = 1;
                        break;
                    default:
                        current += *p;
                        break;
                    }
                }
                if (*p)
                    p++;
            }

            args.push_back(current);
            current = "";
        } else {
            return args;
        }
    }

err:
    return args;
}


static int hex_digit_to_int(char c) {
    switch (c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'a':
    case 'A': return 10;
    case 'b':
    case 'B': return 11;
    case 'c':
    case 'C': return 12;
    case 'd':
    case 'D': return 13;
    case 'e':
    case 'E': return 14;
    case 'f':
    case 'F': return 15;
    default: return 0;
    }
}