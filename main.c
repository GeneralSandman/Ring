#include "ring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

    if (!strcmp(argv[1], "--version") 
        || !strcmp(argv[1], "-v")) {
        printf("Ring version: %s \n", RING_VERSION);
        return 0;
    }

    if (!strcmp(argv[1], "--interactive")
        || !strcmp(argv[1], "-i")) {
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

    ring_compiler    = new_ring_compiler(file_name);
    ring_vm_executer = new_ring_vm_executer();

    // Step-1: flex 词法分析，
    // Step-2: bison 语法分析，构建语法树
    ring_compiler_compile(ring_compiler, fp);

    // Step-3: 语义分析
    ring_semantic_check(ring_compiler);

    // Step-4: 修正语法树
    ring_compiler_fix_ast(ring_compiler);

    // Step-5: 生成虚拟机中间代码
    ring_generate_vm_code(ring_compiler, ring_vm_executer);

    // Step-6: 运行虚拟机
    ring_vm = new_ring_virtualmachine(ring_vm_executer);
    ring_execute_vm_code(ring_vm);

    // Step-6: 直接解释执行
    // ring_interpret(ring_compiler);

    return 0;
}

