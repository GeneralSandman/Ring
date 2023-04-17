#include "ring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* command_help_message =
    "Ring Command Usage: \n"
    "\n"
    "        ring <command> [arguments]\n"
    "\n"
    "The commands are:\n"
    "    \n"
    "        run  <filename>                                :compile and run Ring program\n"
    "        build <filename>                               :compile and generate bytecode\n"
    "        dump <filename>                                :dump bytecode\n"
    "        version                                        :get Ring version\n"
    "        help                                           :get Ring version\n"
    "\n";


int main(int argc, char** argv) {
    PackageUnit*                package_unit;
    Ring_VirtualMachine_Executer* ring_vm_executer;
    Ring_VirtualMachine*          ring_vm;
    char*                         file_name;
    FILE*                         fp;
    char*                         command;


    if (argc < 2) {
        fprintf(stderr, "%s", command_help_message);
        exit(ERROR_CODE_COMMAND_ERROR);
    }
    command = argv[1];
    if(!strcmp(command, "version")) {
        printf("Ring version: %s \n", RING_VERSION);
        return 0;
    } else if (!strcmp(command, "help")) {
        printf("%s", command_help_message);
        return 0;
    }


    if(argc < 3) {
        fprintf(stderr, "%s", command_help_message);
        exit(ERROR_CODE_COMMAND_ERROR);
    }
    file_name = argv[2];
    if (!strcmp(command, "run")) {
    } else if (!strcmp(command, "build")) {
        printf("ring build\n");
        return 0;
    } else if (!strcmp(command, "dump")) {
        printf("ring dump\n");
        return 0;
    }

    // Step-0: 读取文件
    fp        = fopen(file_name, "r");
    if (fp == NULL) {
        fprintf(stderr, "%s not found.\n", file_name);
        exit(1);
    }

    package_unit    = package_unit_create(file_name);
    ring_vm_executer = new_ring_vm_executer();

    // Step-1: flex 词法分析，
    // Step-2: bison 语法分析，构建语法树
    package_unit_compile(package_unit);

    // Step-4: 修正语法树
    ring_compiler_fix_ast(package_unit);

    // Step-5: 生成虚拟机中间代码
    ring_generate_vm_code(package_unit, ring_vm_executer);

    // Step-6: 运行虚拟机
    ring_vm = new_ring_virtualmachine(ring_vm_executer);
    ring_execute_vm_code(ring_vm);

    return 0;
}

