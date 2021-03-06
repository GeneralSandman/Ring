#include "ring.h"
#include <stdio.h>

extern RVM_Opcode_Info RVM_Opcode_Infos[];

void ring_compiler_functions_dump(Ring_Compiler* compiler) {
    printf(" ************  compiler functions dump ****\n");
    Function*    func;
    Declaration* decl;
    int          i = 0;
    int          j = 0;

    for (j = 0, decl = compiler->declaration_list; decl; decl = decl->next, j++) {
        printf("global-variable[%d]: name:%s\n", j, decl->identifier);
    }
    printf("\n");

    for (func = compiler->function_list; func; func = func->next, i++) {
        printf("function[%d]: name:%s\n", i, func->function_name);
        if (func->block) {
            decl = func->block->declaration_list;
            for (j = 0, decl = func->block->declaration_list; decl; decl = decl->next, j++) {
                printf("\tlocal-variable[%d]: name:%s\n", j, decl->identifier);
            }
        }
    }
}


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
            fprintf(stderr, "error-----------");
            break;
        }
    }
}

void ring_vm_code_dump(RVM_Function* function, RVM_Byte* code_list, unsigned int code_size, unsigned int pc, unsigned int screen_row, unsigned int screen_col) {
    MOVE_CURSOR(screen_row++, screen_col);
    char* func_name = "top_level";
    if (function) {
        func_name = function->func_name;
    }
    printf("************  rvm opcode  --[function %s]\n", func_name);

    MOVE_CURSOR(screen_row++, screen_col);
    // width: 54
    printf("%10s | %20s | %10s | %5s\n", "index", "opcode", "oper num", "pc");
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
            tmp = code_list[i++] << 8;
            tmp += code_list[i++];
            sprintf(oper_num, "%d", tmp);
            break;

        default: break;
        }

        MOVE_CURSOR(screen_row++, screen_col);
        printf(" %10d | %20s | %10s | %5s\n", index, opcode_name, oper_num, pointer);
    }
}


// TODO: caller_stack_base ????????????????????? RVM_RuntimeStack ????????????
void ring_vm_dump_runtime_stack(RVM_RuntimeStack* runtime_stack, unsigned int caller_stack_base, unsigned int screen_row, unsigned int screen_col) {
    MOVE_CURSOR(screen_row++, screen_col);
    printf("**************** runtime_stack *****************\n");

    MOVE_CURSOR(screen_row++, screen_col);
    // width 49
    printf("%7s | %20s | %6s | %6s\n", "index", "oper_num", "space", "pointer");
    for (int i = 0; i < runtime_stack->top_index; i++) {
        char* space   = "";
        char* pointer = "";
        if (i >= caller_stack_base) {
            space = "+++";
        }
        if (i == runtime_stack->top_index - 1) {
            pointer = "<--";
        }

        MOVE_CURSOR(screen_row++, screen_col);

        RVM_Value value = runtime_stack->data[i];
        switch (value.type) {
        case RVM_VALUE_TYPE_BOOL:
            if (value.u.int_value) {
                printf("%7d | %20s | %6s | %6s\n", i, "true", space, pointer);
            } else {
                printf("%7d | %20s | %6s | %6s\n", i, "false", space, pointer);
            }
            break;
        case RVM_VALUE_TYPE_INT:
            printf("%7d | %20d | %6s | %6s\n", i, value.u.int_value, space, pointer);
            break;
        case RVM_VALUE_TYPE_DOUBLE:
            printf("%7d | %20f | %6s | %6s\n", i, value.u.double_value, space, pointer);
            break;
        case RVM_VALUE_TYPE_STRING:
            if (value.u.object == NULL || value.u.object->u.string.data == NULL) {
                printf("%7d | %20.*s | %6s | %6s\n", i, 20, "", space, pointer);
            } else {
                printf("%7d | %20.*s | %6s | %6s\n", i, 20, value.u.object->u.string.data, space, pointer);
            }
            break;
        default:
            break;
        }
    }
}

