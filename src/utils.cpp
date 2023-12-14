#include "ring.hpp"
#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <string>
#include <sys/stat.h>
#include <vector>

extern RVM_Opcode_Info RVM_Opcode_Infos[];

void                   ring_compiler_functions_dump(PackageUnit* package_unit) {
                      printf(" ************  compiler functions dump ****\n");
                      Declaration* decl;
                      int          i = 0;
                      int          j = 0;

                      for (Declaration* decl : package_unit->global_declaration_list) {
                          printf("global-variable: name:%s\n", decl->identifier);
    }
                      printf("\n");

                      for (Function* func : package_unit->function_list) {
                          printf("function[%d]: name:%s\n", i, func->function_name);
                          if (func->block) {
                              decl = func->block->declaration_list;
                              for (j = 0, decl = func->block->declaration_list; decl; decl = decl->next, j++) {
                                  printf("\tlocal-variable[%d]: name:%s\n", j, decl->identifier);
            }
        }
                          i++;
    }
}


void ring_vm_constantpool_dump(Package_Executer* executer) {
    printf(" ************  rvm constant pool  ****\n");
    for (unsigned int i = 0; i < executer->constant_pool_size; i++) {
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

/*
 * dump function detail
 */
void ring_vm_code_dump(RVM_Function* function, RVM_Byte* code_list, unsigned int code_size, unsigned int pc, unsigned int screen_row, unsigned int screen_col) {
    MOVE_CURSOR(screen_row++, screen_col);
    std::string func_name = "top_level";
    if (function) {
        func_name = std::string(function->func_name);
    }
    printf("************  rvm opcode  --[function %s]\n", func_name.c_str());

    MOVE_CURSOR(screen_row++, screen_col);
    // width: 54
    printf("%10s | %20s | %10s | %5s\n", "index", "opcode", "oper num", "pc");
    for (unsigned int i = 0; i < code_size;) {
        std::string pointer = "";
        if (i == pc) {
            pointer = "<--";
        }

        unsigned int    index       = i;
        RVM_Byte        opcode      = code_list[i++];
        RVM_Opcode_Info opcode_info = RVM_Opcode_Infos[opcode];
        std::string     opcode_name = opcode_info.name;
        std::string     oper_num    = "";
        int             tmp         = 0;
        int             tmp1        = 0;
        int             tmp2        = 0;

        switch (opcode_info.operand_type) {
        case OPCODE_OPERAND_TYPE_0BYTE:
            break;

        case OPCODE_OPERAND_TYPE_1BYTE:
            oper_num = std::to_string(code_list[i++]);
            break;

        case OPCODE_OPERAND_TYPE_2BYTE_As:
            tmp = code_list[i++] << 8;
            tmp += code_list[i++];
            oper_num = std::to_string(tmp);
            break;

        case OPCODE_OPERAND_TYPE_2BYTE_AB:
            tmp1     = code_list[i++];
            tmp2     = code_list[i++];
            oper_num = std::to_string(tmp1) + " " + std::to_string(tmp2);
            break;

        case OPCODE_OPERAND_TYPE_3BYTE_ABs:
            tmp1 = code_list[i++];
            tmp2 = code_list[i++] << 8;
            tmp2 += code_list[i++];
            oper_num = std::to_string(tmp1) + " " + std::to_string(tmp2);
            break;

        default: break;
        }

        MOVE_CURSOR(screen_row++, screen_col);
        printf("%10d | %20s | %10s | %5s\n",
               index,
               opcode_name.c_str(),
               oper_num.c_str(),
               pointer.c_str());
    }
}


// TODO: caller_stack_base 是不是可以放在 RVM_RuntimeStack 中，考虑
void ring_vm_dump_runtime_stack(RVM_RuntimeStack* runtime_stack, unsigned int caller_stack_base, unsigned int screen_row, unsigned int screen_col) {
    MOVE_CURSOR(screen_row++, screen_col);
    printf("**************** runtime_stack *****************\n");

    MOVE_CURSOR(screen_row++, screen_col);
    // width 49
    printf("%7s | %20s | %6s | %6s\n", "index", "oper_num", "space", "pointer");
    for (unsigned int i = 0; i < runtime_stack->top_index; i++) {
        std::string space   = "";
        std::string pointer = "";
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
                printf("%7d | %20s | %6s | %6s\n", i, "true", space.c_str(), pointer.c_str());
            } else {
                printf("%7d | %20s | %6s | %6s\n", i, "false", space.c_str(), pointer.c_str());
            }
            break;
        case RVM_VALUE_TYPE_INT:
            printf("%7d | %20d | %6s | %6s\n", i, value.u.int_value, space.c_str(), pointer.c_str());
            break;
        case RVM_VALUE_TYPE_DOUBLE:
            printf("%7d | %20f | %6s | %6s\n", i, value.u.double_value, space.c_str(), pointer.c_str());
            break;
        case RVM_VALUE_TYPE_STRING:
            if (value.u.object == nullptr || value.u.object->u.string->data == nullptr) {
                printf("%7d | %20.*s | %6s | %6s\n", i, 20, "", space.c_str(), pointer.c_str());
            } else {
                printf("%7d | %20.*s | %6s | %6s\n", i, 20, value.u.object->u.string->data, space.c_str(), pointer.c_str());
            }
            break;
        case RVM_VALUE_TYPE_OBJECT:
            printf("%7d | %20s | %6s | %6s\n", i, "object", space.c_str(), pointer.c_str());
            break;
        default:
            break;
        }
    }
}

void ring_vm_dump_stdout_log(Ring_VirtualMachine* rvm) {
}

/*
 * List all all source file of ring std package
 * which locates in directory.
 *
 * TODO: need to do same error handling.
 */
std::vector<std::string> list_files_of_dir(char* dir) {
    std::vector<std::string> file_list;
    DIR*                     dp = nullptr;
    struct dirent*           st;
    struct stat              sta;
    int                      ret            = 0;
    char                     tmp_name[1024] = {0};
    dp                                      = opendir(dir);
    if (dp == nullptr) {
        // TODO:
        printf("open dir error!!\n");
        return file_list;
    }
    while (1) {
        st = readdir(dp);
        if (nullptr == st) {
            // 读取完毕
            break;
        }
        strcpy(tmp_name, dir);
        if (dir[strlen(dir) - 1] != '/') // 判断路径名是否带/
            strcat(tmp_name, "/");
        strcat(tmp_name, st->d_name); // 新文件路径名
        ret = stat(tmp_name, &sta);   // 查看目录下文件属性
        if (ret < 0) {
            // TODO:
            printf("read stat fail\n");
            return file_list;
        }

        if (S_ISDIR(sta.st_mode)) {
            // 如果为目录文件
            if (0 == strcmp("..", st->d_name) || 0 == strcmp(".", st->d_name)) {
                // 忽略当前目录和上一层目录
                continue;
            } else {
                // 递归读取
                //  list_file(tmp_name);
            }
        } else {
            // 不为目录则打印文件路径名
            file_list.push_back(std::string(tmp_name));
        }
    }
    closedir(dp);
    return file_list;
}

void dump_vm_function(RVM_Function* function) {
    assert(function != nullptr);

    printf("%s$%s    <%s:%d,%d>%s\n",
           LOG_COLOR_GREEN,
           format_rvm_function(function).c_str(),
           function->source_file.c_str(),
           function->start_line_number, function->end_line_number,
           LOG_COLOR_CLEAR);

    printf("+Parameter:   %d\n", function->parameter_size);
    printf("+Local:       %d\n", function->local_variable_size);

    printf("+Instructions:\n");
    printf(" ├──%-8s%-30s%-20s%-18s\n",
           "*Num", "*Instruction", "*Operand", "*SourceLineNum");
    if (function->type == RVM_FUNCTION_TYPE_DERIVE) {
        RVM_Byte*                          code_list      = nullptr;
        unsigned int                       code_size      = 0;
        unsigned int                       code_num_index = 0; // 多个 RVM_Byte 组成一个 有效的字节码, 不定长字节码
        std::vector<RVM_SourceCodeLineMap> code_line_map;
        unsigned int                       code_line_map_index = 0;

        code_list                                              = function->u.derive_func->code_list;
        code_size                                              = function->u.derive_func->code_size;
        code_line_map                                          = function->u.derive_func->code_line_map;

        for (unsigned int i = 0; i < code_size; code_num_index++) {
            std::string source_code_line_number;
            if (i == code_line_map[code_line_map_index].opcode_begin_index) {
                source_code_line_number = std::to_string(code_line_map[code_line_map_index].line_number);
                code_line_map_index++;
            }

            RVM_Byte        opcode      = code_list[i++];
            RVM_Opcode_Info opcode_info = RVM_Opcode_Infos[opcode];
            std::string     opcode_name = opcode_info.name;
            std::string     oper_num    = "";
            int             tmp         = 0;
            int             tmp1        = 0;
            int             tmp2        = 0;

            switch (opcode_info.operand_type) {
            case OPCODE_OPERAND_TYPE_0BYTE:
                break;

            case OPCODE_OPERAND_TYPE_1BYTE:
                oper_num = std::to_string(code_list[i++]);
                break;

            case OPCODE_OPERAND_TYPE_2BYTE_As:
                tmp = code_list[i++] << 8;
                tmp += code_list[i++];
                oper_num = std::to_string(tmp);
                break;

            case OPCODE_OPERAND_TYPE_2BYTE_AB:
                tmp1     = code_list[i++];
                tmp2     = code_list[i++];
                oper_num = std::to_string(tmp1) + " " + std::to_string(tmp2);
                break;

            case OPCODE_OPERAND_TYPE_3BYTE_ABs:
                tmp1 = code_list[i++];
                tmp2 = code_list[i++] << 8;
                tmp2 += code_list[i++];
                oper_num = std::to_string(tmp1) + " " + std::to_string(tmp2);
                break;

            default: break;
            }

            printf(" ├──%-8d%-30s%-20s%-18s\n",
                   code_num_index,
                   opcode_name.c_str(),
                   oper_num.c_str(),
                   source_code_line_number.c_str());
        }
    }

    printf("\n");
}