#include "ring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void ring_compile(Ring_Compiler* ring_compiler, FILE* fp);
void ring_interactive_program();
int  write_tmp_source_file(char* tmp_source_file_name, int start_line_num, int line_size, char** input_line_content);

int main(int argc, char** argv) {
    Ring_Compiler*                ring_compiler;
    Ring_VirtualMachine_Executer* ring_vm_executer;
    Ring_VirtualMachine*          ring_vm;
    char*                         file_name;
    FILE*                         fp;

    if (argc != 2) {
        printf("Ring version: %s \n\n", RING_VERSION);

        printf("usage:\n");
        printf("      \t%s <filename>       complie ring source file\n", argv[0]);
        printf("      \t%s --interactive    interactive program\n", argv[0]);
        printf("      \t%s --version        get version\n", argv[0]);
        exit(1);
    }

    if (!strcmp(argv[1], "--version")) {
        printf("Ring version: %s \n", RING_VERSION);
        return 0;
    }

    if (!strcmp(argv[1], "--interactive")) {
        ring_interactive_program();
        return 0;
    }

    // Step-0: 读取文件
    file_name = argv[1];
    fp        = fopen(file_name, "r");
    if (fp == NULL) {
        fprintf(stderr, "%s not found.\n", argv[1]);
        exit(1);
    }

    ring_compiler = new_ring_compiler(file_name);

    // Step-1: flex 词法分析，
    // Step-2: bison 语法分析，构建语法树
    ring_compile(ring_compiler, fp);

    // Step-3: 语义分析
    int result = ring_semantic_check(ring_compiler);
    if (result != 0) {
        fprintf(stderr, "semantic_check error\n");
        exit(1);
    }

    // Step-4: 修正语法树
    ring_fix_ast(ring_compiler);

    ring_vm_executer = new_ring_vm_executer();

    // Step-5: 生成虚拟机中间代码
    ring_generate_vm_code(ring_compiler, ring_vm_executer);

    // Step-6: 运行虚拟机
    ring_vm = new_ring_virtualmachine(ring_vm_executer);
    ring_execute_vm_code(ring_vm);

    // Step-6: 直接解释执行
    ring_interpret(ring_compiler);

    return 0;
}

// Step-1: flex 词法分析，
// Step-2: bison 语法分析，构建语法树
void ring_compile(Ring_Compiler* ring_compiler, FILE* fp) {
    extern int   yyparse(void);
    extern FILE* yyin;

    yyin = fp;
    if (yyparse()) {
        fprintf(stderr, "YYPARSE error\n");
        exit(1);
    }

    debug_log_with_yellow_coloar("\t COMPLIE SUCCESS\n\n");
}

// 交互式编程
// 从命令行输入
void ring_interactive_program() {
    printf_witch_blue("Ring version: %s \n", RING_VERSION);
    printf_witch_blue("An enhanced Interactive Ring. Type '-h' for help.\n");

    extern int     yyparse(void);
    extern FILE*   yyin;
    Ring_Compiler* ring_compiler;
    time_t         rand_int;
    char           tmp_source_file_name[1024];
    char           save_file_name[1024];
    char*          input_line_contents[1024];
    unsigned int   line_number       = 1;
    unsigned int   start_line_number = 1;

    time(&rand_int);
    sprintf(tmp_source_file_name, "/tmp/ring-interactive-%ld.ring.tmp", rand_int);
    printf_witch_blue("tmp_file_name:%s\n\n\n", tmp_source_file_name);
    memset(input_line_contents, 0, sizeof(input_line_contents));
    ring_compiler = new_ring_compiler(tmp_source_file_name);

    while (1) {
        printf_witch_green("line[%d]: ", line_number);

        char* content = malloc(1024);
        if (fgets(content, 1024, stdin) == NULL) {
            printf_witch_red("get input from stdin error, exit\n");
            exit(1);
        }

        if (!strncmp(content, "-r", 2)) {
            // 写入临时文件
            if (line_number - start_line_number == 0) {
                continue;
            }
            write_tmp_source_file(tmp_source_file_name, start_line_number, line_number - start_line_number, input_line_contents);

            // 编译临时文件
            yyin = fopen(tmp_source_file_name, "r");
            if (yyin == NULL) {
                printf_witch_red("open tmp_source_file_name error (%s)\n", tmp_source_file_name);
                exit(1);
            }
            if (yyparse()) {
                printf_witch_red("YYPARSE error\n");
            }

            // 解释执行
            ring_interpret(ring_compiler);
            printf_witch_green("\n");

            // 只清除相关语句不清楚相关变量
            ring_compiler->statement_list_size = 0;
            ring_compiler->statement_list      = NULL;
            fclose(yyin);

            start_line_number = line_number;
            continue;
        } else if (!strncmp(content, "-c", 2)) {
            ring_compiler = new_ring_compiler(tmp_source_file_name);
            memset(input_line_contents, 0, sizeof(input_line_contents));
            start_line_number = 1;
            line_number       = 1;
            printf_witch_blue("clear code block\n");
            continue;
        } else if (!strncmp(content, "-s", 2)) {
            time(&rand_int);
            sprintf(save_file_name, "./ring-interactive-%ld.ring", rand_int);
            write_tmp_source_file(save_file_name, 1, line_number - 1, input_line_contents);
            printf_witch_blue("save ring source code success: %s\n\n", save_file_name);

            continue;
        } else if (!strncmp(content, "-h", 2)) {
            printf_witch_blue("-r:\trun this code block\n");
            printf_witch_blue("-c:\tclear code block\n");
            printf_witch_blue("-s:\tsave code block to disk\n");
            printf_witch_blue("-h:\thelp information\n");
            printf_witch_blue("\n\n");
            continue;
        } else if (!strncmp(content, "\n", 1)) {
            // empty line
            continue;
        }

        input_line_contents[line_number++] = content;
    }
}

int write_tmp_source_file(char* tmp_source_file_name, int start_line_num, int line_size, char** input_line_contents) {
    FILE* tmp_source_file = fopen(tmp_source_file_name, "w+");
    if (tmp_source_file == NULL) {
        printf_witch_red("open tmp_source_file_name error (%s)\n", tmp_source_file_name);
        exit(1);
    }

    for (int i = start_line_num; i < start_line_num + line_size; i++) {
        fprintf(tmp_source_file, "%s", input_line_contents[i]);
    }

    fflush(tmp_source_file);
    fclose(tmp_source_file);
    return 0;
}
