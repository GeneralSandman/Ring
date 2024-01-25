#include "ring.hpp"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <string>
#include <sys/stat.h>
#include <vector>


extern RVM_Opcode_Info RVM_Opcode_Infos[];


// dump function by PackageUnit
void ring_compiler_functions_dump(PackageUnit* package_unit) {
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
void ring_vm_code_dump(RVM_Function* function,
                       RVM_Byte* code_list, unsigned int code_size,
                       unsigned int pc,
                       unsigned int screen_row, unsigned int screen_col) {

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
void ring_vm_dump_runtime_stack(RVM_RuntimeStack* runtime_stack,
                                unsigned int      caller_stack_base,
                                unsigned int screen_row, unsigned int screen_col) {

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
            if (value.u.object == nullptr || value.u.string_value->data == nullptr) {
                printf("%7d | %20.*s | %6s | %6s\n", i, 20, "", space.c_str(), pointer.c_str());
            } else {
                printf("%7d | %20.*s | %6s | %6s\n", i, 20, value.u.string_value->data, space.c_str(), pointer.c_str());
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

/*
 * ring dump derive function 细节
 * Detail:
 * 1. 函数名
 * 2. 所在源代码文件名, 源代码文件行树
 * 3. 函数参数的数量
 * 4. 局部变量的数量
 * 5. 代码对应的虚拟机字节码
 *
 * TIP:
 * class_definition == nullptr: 打印 非 method的细节
 * class_definition != nullptr: 是打印 method的细节
 */
void dump_vm_function(RVM_ClassDefinition* class_definition, RVM_Function* function) {
    assert(function != nullptr);

    // TODO: 这里想个更好的办法, 减少代码重复
    // 1. function name
    if (class_definition == nullptr) {
        printf("$%s    ", format_rvm_function(function).c_str());
    } else {
        printf("$%s.%s    ", class_definition->identifier, format_rvm_function(function).c_str());
    }
    printf("<%s:%d,%d>\n",
           function->source_file.c_str(),
           function->start_line_number, function->end_line_number);

    // 2. function parameters
    printf("+Parameter:   %d\n", function->parameter_size);
    for (unsigned int i = 0; i < function->parameter_size; i++) {
        printf(" ├──%-20s %-20s\n",
               format_rvm_type_specifier(function->parameter_list[i].type_specifier).c_str(),
               function->parameter_list[i].identifier);
    }


    // 3. function local variable
    printf("+Local:       %d\n", function->local_variable_size);
    for (unsigned int i = 0; i < function->local_variable_size; i++) {
        printf(" ├──%-20s %-20s\n",
               format_rvm_type_specifier(function->local_variable_list[i].type_specifier).c_str(),
               function->local_variable_list[i].identifier);
    }

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

        for (unsigned int pc = 0; pc < code_size; code_num_index++) {
            std::string source_code_line_number;
            if (pc == code_line_map[code_line_map_index].opcode_begin_index) {
                source_code_line_number = std::to_string(code_line_map[code_line_map_index].line_number);
                code_line_map_index++;
            }

            RVM_Byte        opcode      = code_list[pc++];
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
                oper_num = std::to_string(code_list[pc++]);
                break;

            case OPCODE_OPERAND_TYPE_2BYTE_As:
                tmp = code_list[pc++] << 8;
                tmp += code_list[pc++];
                oper_num = std::to_string(tmp);
                break;

            case OPCODE_OPERAND_TYPE_2BYTE_AB:
                tmp1     = code_list[pc++];
                tmp2     = code_list[pc++];
                oper_num = std::to_string(tmp1) + " " + std::to_string(tmp2);
                break;

            case OPCODE_OPERAND_TYPE_3BYTE_ABs:
                tmp1 = code_list[pc++];
                tmp2 = code_list[pc++] << 8;
                tmp2 += code_list[pc++];
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

void dump_vm_class(RVM_ClassDefinition* class_definition) {
    assert(class_definition != nullptr);

    printf("%%%s    <%s:%d,%d>\n",
           class_definition->identifier,
           class_definition->source_file.c_str(),
           class_definition->start_line_number, class_definition->end_line_number);

    printf("+Field:     %d\n", class_definition->field_size);
    for (unsigned int i = 0; i < class_definition->field_size; i++) {
        printf(" ├──%-30s %-20s\n",
               format_rvm_type_specifier(class_definition->field_list[i].type_specifier).c_str(),
               class_definition->field_list[i].identifier);
    }

    printf("+Method:    %d\n", class_definition->method_size);
    for (unsigned int i = 0; i < class_definition->method_size; i++) {
        printf(" ├──%s\n", class_definition->method_list[i].identifier);
    }

    printf("\n");


    for (unsigned int i = 0; i < class_definition->method_size; i++) {
        dump_vm_function(class_definition, class_definition->method_list[i].rvm_function);
    }
    printf("\n");
}

std::string dump_vm_constant(RVM_ConstantPool* constant) {
    switch (constant->type) {
    case CONSTANTPOOL_TYPE_INT:
        return "int(" + std::to_string(constant->u.int_value) + ")";
        break;
    case CONSTANTPOOL_TYPE_DOUBLE:
        return "double(" + std::to_string(constant->u.double_value) + ")";
        break;
    case CONSTANTPOOL_TYPE_STRING:
        return "string(" + std::string(constant->u.string_value) + ")";
        break;
    default:
        // TODO: error-report
        break;
    }
    return "";
}

/*
 * 通过当前Function 的 Pc 计算出 对应的源代码所在的行数
 *
 * 只能计算 derive function 对应的源代码行数
 * binary search
 * 单调性可查看 RVM_SourceCodeLineMap
 */
unsigned int get_source_line_number_by_pc(RVM_Function* function, unsigned int pc) {
    DeriveFunction* derive_function = function->u.derive_func;

    unsigned int    left            = 0;
    unsigned int    right           = derive_function->code_line_map.size();

    while (left < right) {
        unsigned int mid = (left + right) / 2;

        if (derive_function->code_line_map[mid].opcode_begin_index == pc) {
            return derive_function->code_line_map[mid].line_number;
        } else if (derive_function->code_line_map[mid].opcode_begin_index < pc) {
            if (mid == derive_function->code_line_map.size() - 1
                || derive_function->code_line_map[mid + 1].opcode_begin_index > pc) {
                return derive_function->code_line_map[mid].line_number;
            }
            left = mid + 1;
        } else {
            if (mid == 0)
                return derive_function->code_line_map[mid].line_number;
            else
                right = mid - 1;
        }
    }

    return derive_function->code_line_map[left].line_number;
}