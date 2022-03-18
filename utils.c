#include "ring.h"
#include <stdio.h>

extern RVM_Opcode_Info RVM_Opcode_Infos[];


void ring_vm_constantpool_dump(Ring_VirtualMachine_Executer* executer) {
    printf(" ************  rvm constant pool  ****\n");
    for (int i = 0; i < executer->constant_pool_size; i++) {
        printf("%10d | ", i);
        switch (executer->constant_pool_list[i].type) {
        case CONSTANTPOOL_TYPE_INT:
            printf("<int> %15d\n", executer->constant_pool_list[i].u.int_value);
            break;
        case CONSTANTPOOL_TYPE_DOUBLE:
            printf("<double> %15f\n", executer->constant_pool_list[i].u.double_value);
            break;
        case CONSTANTPOOL_TYPE_STRING:
            printf("<string> %15s\n", executer->constant_pool_list[i].u.string_value);
            break;
        default:
            break;
        }
    }
}

void ring_vm_code_dump(Ring_VirtualMachine_Executer* executer, unsigned int pc, unsigned int screen_row, unsigned int screen_col) {
    RVM_Byte*    code_list = executer->code_list;
    unsigned int code_size = executer->code_size;

    // int col = 60;
    // int row = 1;

    MOVE_CURSOR(screen_row++, screen_col);
    printf(" ************  rvm opcode  ****\n");

    MOVE_CURSOR(screen_row++, screen_col);
    printf(" %10s | %15s | %10s | %5s\n", "index", "opcode", "oper num", "pc");
    for (unsigned int i = 0; i < code_size;) {
        char* pointer = "";
        if (i == pc) {
            pointer = "<--";
        }

        unsigned int    index       = i;
        RVM_Byte        opcode      = code_list[i++];
        RVM_Opcode_Info opcode_info = RVM_Opcode_Infos[opcode];
        char*           opcode_name = opcode_info.name;
        char            oper_num[]  = "         -";

        int tmp = 0;

        switch (opcode_info.type) {
        case OPCODE_OPERAND_TYPE_0BYTE:
            break;

        case OPCODE_OPERAND_TYPE_1BYTE:
            sprintf(oper_num, "%d", code_list[i++]);
            break;

        case OPCODE_OPERAND_TYPE_2BYTE:
            // TODO: 位运算，从高位开始填充
            tmp = code_list[i++] << 8;
            tmp += code_list[i++];
            sprintf(oper_num, "%d", tmp);
            break;

        default: break;
        }

        MOVE_CURSOR(screen_row++, screen_col);
        printf(" %10d | %15s | %10s | %5s\n", index, opcode_name, oper_num, pointer);
    }
}


void ring_vm_dump_runtime_stack(RVM_RuntimeStack* runtime_stack, unsigned int screen_row, unsigned int screen_col) {
    MOVE_CURSOR(screen_row++, screen_col);
    printf("****  runtime_stack  ****\n");

    MOVE_CURSOR(screen_row++, screen_col);
    printf("%7s | %10s | %5s\n", "index", "oper_num", "pointer");
    for (int i = 0; i < runtime_stack->top_index; i++) {
        char* pointer = "";
        if (i == runtime_stack->top_index - 1) {
            pointer = "<--";
        }

        MOVE_CURSOR(screen_row++, screen_col);
        printf("%7d | %10d | %5s\n", i, runtime_stack->data[i].int_value, pointer);
    }
}
