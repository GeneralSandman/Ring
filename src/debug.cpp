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

// static unsigned int trace_count = 0;

//
int debug_trace_dispatch(RVM_Frame* frame, const char* event, const char* arg) {
    // printf("---debug_trace_dispatch[%u]---\n", trace_count++);
    // printf("[+]event:            %s\n", event);
    // // printf("[+]arg:              %s\n", arg);
    // printf("[+]current_function: %s\n", frame->callee_func);
    // printf("[+]next_opcode:      %s\n", frame->next_opcode);
    // printf("[+]source_line_num:  %u\n", frame->source_line_number);
    // printf("---debug_trace_dispatch---\n");
    // printf("\n\n");


    if (str_eq(event, "line")) {
        dispath_line(frame, event, arg);
    } else if (str_eq(event, "call")) {
        dispath_call(frame, event, arg);
    }

    return 0;
}

#define RDB_PREFIX LOG_COLOR_BLUE "rdb> " LOG_COLOR_CLEAR
#define RDB_HISTORY_FILE "ring-rdb-history-command.txt"

int dispath_line(RVM_Frame* frame, const char* event, const char* arg) {
    char* line;

    linenoiseSetMultiLine(1);
    linenoiseSetCompletionCallback(ring_rdb_completion);
    linenoiseSetHintsCallback(ring_rdb_hints);
    linenoiseHistoryLoad(RDB_HISTORY_FILE);

    while (1) {
        line = linenoise(RDB_PREFIX);
        if (line == NULL)
            break;

        linenoiseHistoryAdd(line);              /* Add to the history. */
        linenoiseHistorySave(RDB_HISTORY_FILE); /* Save the history on disk. */

        printf(LOG_COLOR_GREEN);

        if (str_eq(line, "globals")) {
            printf("[+]globals:\n");
            for (std::pair<std::string, RVM_Value*>& global : frame->globals) {
                printf("    %20s: %p\n", global.first.c_str(), global.second);
            }

        } else if (str_eq(line, "locals")) {

            printf("[+]locals:\n");
            for (std::pair<std::string, RVM_Value*>& local : frame->locals) {
                printf("    %20s: %p\n", local.first.c_str(), local.second);
            }

        } else if (str_eq(line, "cont")) {
            break;
        } else if (str_eq(line, "q")) {
            exit(0);
        } else if (str_eq(line, "help")) {
            printf("globals:     list global variable\n");
            printf("locals:      list local  variable\n");
        }

        printf(LOG_COLOR_CLEAR);
    }
    return 0;
}

int dispath_call(RVM_Frame* frame, const char* event, const char* arg) {
    return 0;
}


void ring_rdb_completion(const char* buf, linenoiseCompletions* lc) {
    // if (buf[0] == 'h') {
    //     linenoiseAddCompletion(lc, "hello");
    //     linenoiseAddCompletion(lc, "hello 1");
    //     linenoiseAddCompletion(lc, "hello 2");
    // }
}

char* ring_rdb_hints(const char* buf, int* color, int* bold) {
    *color = 35;
    *bold  = 0;


    return nullptr;
}