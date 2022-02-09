#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ring.h"

void ring_compile(Ring_Interpreter *ring_interpreter, FILE *fp);
void ring_interactive_program();

int main(int argc, char **argv) {
    Ring_Interpreter *ring_interpreter;
    char *            file_name;
    FILE *            fp;

    if (argc != 2) {
        printf("Ring version: %s \n\n", RING_VERSION);

        printf("usage:\t%s <filename>\n", argv[0]);
        printf("      \t%s --version\n", argv[0]);
        exit(1);
    }

    if (!strcmp(argv[1], "--version")) {
        printf("Ring version: %s \n", RING_VERSION);
        return 0;
    }

    if (!strcmp(argv[1], "--interactive")) {
        printf("Ring version: %s \n", RING_VERSION);
        printf("An enhanced Interactive Python. Type 'cmd:help' for help.\n");
        ring_interactive_program();
        return 0;
    }

    file_name = argv[1];

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        fprintf(stderr, "%s not found.\n", argv[1]);
        exit(1);
    }

    ring_interpreter = new_ring_interpreter(file_name);

    // 词法分析，语法分析，构建语法树
    ring_compile(ring_interpreter, fp);

    // 语义分析
    int result = ring_semantic_check(ring_interpreter);
    if (result != 0) {
        fprintf(stderr, "semantic_check error\n");
        exit(1);
    }

    // 解释执行
    ring_interpret(ring_interpreter);

    return 0;
}

// 词法分析，语法分析，构建语法树
void ring_compile(Ring_Interpreter *ring_interpreter, FILE *fp) {
    extern int   yyparse(void);
    extern FILE *yyin;

    yyin = fp;
    if (yyparse()) {
        fprintf(stderr, "YYPARSE error\n");
        exit(1);
    }

    debug_log_with_yellow_coloar("\t COMPLIE SUCCESS\n\n", "");
}

// 交互式编程
// 从命令行输入
void ring_interactive_program() {
    extern int   yyparse(void);
    extern FILE *yyin;

    Ring_Interpreter *ring_interpreter;
    time_t            rand_int;
    FILE *            tmp_source_file;
    char              tmp_source_file_name[1024];
    char              current_line_content[1024];
    unsigned int      line_number = 1;

    time(&rand_int);
    sprintf(tmp_source_file_name, "ring-interactive-%ld.ring.tmp", rand_int);
    printf("tmp_file_name:%s\n", tmp_source_file_name);
    tmp_source_file = fopen(tmp_source_file_name, "w+");
    if (tmp_source_file == NULL) {
        fprintf(stderr, "open tmp_source_file_name error (%s)\n", tmp_source_file_name);
        exit(1);
    }

    ring_interpreter = new_ring_interpreter(tmp_source_file_name);

    while (1) {
        printf("line[%d]: ", line_number);
        if (fgets(current_line_content, 1024, stdin) == NULL) {
            printf("get input from stdin error, exit\n");
            exit(1);
        }

        // printf("[DEBUG] line[%d] content:%s\n", line_number++, current_line_content);

        if (!strncmp(current_line_content, "cmd:run", 7)) {
            yyin = fopen(tmp_source_file_name, "r");
            if (yyin == NULL) {
                fprintf(stderr, "open tmp_source_file_name error (%s)\n", tmp_source_file_name);
                exit(1);
            }
            if (yyparse()) {
                fprintf(stderr, "YYPARSE error\n");
            }

            // 解释执行
            ring_interpret(ring_interpreter);
            printf("\n");

            // 只清除相关语句不清楚相关变量
            ring_interpreter->statement_list_size = 0;
            ring_interpreter->statement_list      = NULL;
            fclose(yyin);
            continue;
        } else if (!strncmp(current_line_content, "cmd:clear", 9)) {
            // 初始化一个新实例
            ring_interpreter = new_ring_interpreter(tmp_source_file_name);
            line_number      = 1;
            printf("[cmd:clear] OK\n");
            continue;
        } else if (!strncmp(current_line_content, "cmd:help", 8)) {
            printf("[cmd:help] OK\n");
            continue;
        }

        printf("\n");
        fprintf(tmp_source_file, current_line_content);
        fprintf(tmp_source_file, "\n");
        fflush(tmp_source_file);
        line_number++;
    }

    // if (yyparse()) {
    //     fprintf(stderr, "YYPARSE error\n");
    //     printf("--------\n");
    //     exit(1);
    // }
}