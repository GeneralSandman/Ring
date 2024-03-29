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

    std::string func_name = "top_level";
    if (function) {
        func_name = std::string(function->func_name);
    }

    STDERR_MOVE_CURSOR(screen_row++, screen_col);
    fprintf(stderr, "-----------------------------  rvm opcode [function:%s] -----------------------------\n",
            func_name.c_str());

    STDERR_MOVE_CURSOR(screen_row++, screen_col);
    fprintf(stderr, "%-8s | %-30s | %-20s | %5s | %-11s\n",
            "*Num", "*Instruction", "*Operand", "*PC", "*CodeLineNo");

    unsigned int             opcode_num = 0; // 多个 RVM_Byte 组成一个 有效的字节码, 不定长字节码

    std::vector<std::string> lines;
    int                      pc_lines_index = 0; // 当前pc 所在的 lines 的 index
    // 取当前pc 所在的 前后20 行进行展示

    for (unsigned int i = 0; i < code_size; opcode_num++) {
        std::string pointer = "";
        if (i == pc) {
            pointer        = "<--";
            pc_lines_index = lines.size();
        }

        RVM_Byte        opcode      = code_list[i++];
        RVM_Opcode_Info opcode_info = RVM_Opcode_Infos[opcode];
        std::string     opcode_name = opcode_info.name;
        std::string     operand_str = "";
        int             operand1    = 0;
        int             operand2    = 0;

        switch (opcode_info.operand_type) {
        case OPCODE_OPERAND_TYPE_0BYTE:
            break;

        case OPCODE_OPERAND_TYPE_1BYTE_A:
            operand_str = std::to_string(code_list[i++]);
            break;

        case OPCODE_OPERAND_TYPE_2BYTE_As:
            operand1 = code_list[i++] << 8;
            operand1 += code_list[i++];
            operand_str = std::to_string(operand1);
            break;

        case OPCODE_OPERAND_TYPE_2BYTE_AB:
            operand1    = code_list[i++];
            operand2    = code_list[i++];
            operand_str = std::to_string(operand1) + ", " + std::to_string(operand2);
            break;

        case OPCODE_OPERAND_TYPE_3BYTE_ABs:
            operand1 = code_list[i++];
            operand2 = code_list[i++] << 8;
            operand2 += code_list[i++];
            operand_str = std::to_string(operand1) + ", " + std::to_string(operand2);
            break;

        default: break;
        }

        char line[90];
        snprintf(line, sizeof(line),
                 "%-8d | %-30s | %20s | %5s | %-11s\n",
                 opcode_num,
                 opcode_name.c_str(),
                 operand_str.c_str(),
                 pointer.c_str(),
                 ""); // TODO: display sourceLineNo
        lines.push_back(std::string(line));
    }

    for (int i = 0; i < lines.size(); i++) {
        // 取当前pc 所在的 前后20 行进行展示
        if (pc_lines_index - 20 <= i && i <= pc_lines_index + 20) {
            STDERR_MOVE_CURSOR(screen_row++, screen_col);
            fprintf(stderr, "%s", lines[i].c_str());
        }
    }
}


// TODO: caller_stack_base 是不是可以放在 RVM_RuntimeStack 中，考虑
// TODO:
void ring_vm_dump_runtime_stack(RVM_RuntimeStack* runtime_stack,
                                unsigned int      caller_stack_base,
                                unsigned int screen_row, unsigned int screen_col) {

    STDERR_MOVE_CURSOR(screen_row++, screen_col);
    fprintf(stderr, "******************** runtime_stack *********************\n");

    STDERR_MOVE_CURSOR(screen_row++, screen_col);
    // width 49
    fprintf(stderr, "%7s | %20s | %10s | %10s\n", "*Index", "*Value", "*CallSpace", "*StackTop");
    for (unsigned int i = 0; i < runtime_stack->top_index; i++) {
        std::string space   = "";
        std::string pointer = "";
        if (i >= caller_stack_base) {
            space = "+++";
        }
        if (i == runtime_stack->top_index - 1) {
            pointer = "<--";
        }

        STDERR_MOVE_CURSOR(screen_row++, screen_col);

        RVM_Value   value     = runtime_stack->data[i];
        std::string type_str  = format_rvm_type(&value);
        std::string value_str = format_rvm_value(&value);
        std::string format    = type_str + "(" + value_str + ")";

        fprintf(stderr, "%7d | %20s | %10s | %10s\n",
                i, format.c_str(),
                space.c_str(), pointer.c_str());
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
            if (str_eq("..", st->d_name) || str_eq(".", st->d_name)) {
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
void dump_vm_function(Package_Executer*    package_executer,
                      RVM_ClassDefinition* class_definition,
                      RVM_Function*        function) {

    assert(function != nullptr);

    // TODO: 这里想个更好的办法, 减少代码重复
    // 1. function name
    if (class_definition == nullptr) {
        printf("$%s    ", format_rvm_function(package_executer, function).c_str());
    } else {
        printf("$%s.%s    ", class_definition->identifier, format_rvm_function(package_executer, function).c_str());
    }
    printf("<%s:%d,%d>\n",
           function->source_file.c_str(),
           function->start_line_number, function->end_line_number);

    // 2. function parameters
    printf("+Parameter:   %d\n", function->parameter_size);
    for (unsigned int i = 0; i < function->parameter_size; i++) {
        printf(" ├──%-20s %-20s\n",
               format_rvm_type_specifier(package_executer, function->parameter_list[i].type_specifier).c_str(),
               function->parameter_list[i].identifier);
    }


    // 3. function local variable
    printf("+Local:       %d\n", function->local_variable_size);
    for (unsigned int i = 0; i < function->local_variable_size; i++) {
        printf(" ├──%-20s %-20s\n",
               format_rvm_type_specifier(package_executer, function->local_variable_list[i].type_specifier).c_str(),
               function->local_variable_list[i].identifier);
    }

    printf("+Instructions:\n");
    printf(" ├──%-8s%-30s%-20s%-18s\n",
           "*Num", "*Instruction", "*Operand", "*SourceLineNum");
    if (function->type == RVM_FUNCTION_TYPE_DERIVE) {
        RVM_Byte*                          code_list  = nullptr;
        unsigned int                       code_size  = 0;
        unsigned int                       opcode_num = 0; // 多个 RVM_Byte 组成一个 有效的字节码, 不定长字节码
        std::vector<RVM_SourceCodeLineMap> code_line_map;
        unsigned int                       code_line_map_index = 0;

        code_list                                              = function->u.derive_func->code_list;
        code_size                                              = function->u.derive_func->code_size;
        code_line_map                                          = function->u.derive_func->code_line_map;

        for (unsigned int i = 0; i < code_size; opcode_num++) {
            std::string source_code_line_number;
            if (i == code_line_map[code_line_map_index].opcode_begin_index) {
                source_code_line_number = std::to_string(code_line_map[code_line_map_index].line_number);
                code_line_map_index++;
            }

            RVM_Byte        opcode      = code_list[i++];
            RVM_Opcode_Info opcode_info = RVM_Opcode_Infos[opcode];
            std::string     opcode_name = opcode_info.name;
            std::string     operand_str = "";
            int             operand1    = 0;
            int             operand2    = 0;

            switch (opcode_info.operand_type) {
            case OPCODE_OPERAND_TYPE_0BYTE:
                break;

            case OPCODE_OPERAND_TYPE_1BYTE_A:
                operand_str = std::to_string(code_list[i++]);
                break;

            case OPCODE_OPERAND_TYPE_2BYTE_As:
                operand1 = code_list[i++] << 8;
                operand1 += code_list[i++];
                operand_str = std::to_string(operand1);
                break;

            case OPCODE_OPERAND_TYPE_2BYTE_AB:
                operand1    = code_list[i++];
                operand2    = code_list[i++];
                operand_str = std::to_string(operand1) + ", " + std::to_string(operand2);
                break;

            case OPCODE_OPERAND_TYPE_3BYTE_ABs:
                operand1 = code_list[i++];
                operand2 = code_list[i++] << 8;
                operand2 += code_list[i++];
                operand_str = std::to_string(operand1) + ", " + std::to_string(operand2);
                break;

            default: break;
            }

            printf(" ├──%-8d%-30s%-20s%-18s\n",
                   opcode_num,
                   opcode_name.c_str(),
                   operand_str.c_str(),
                   source_code_line_number.c_str());
        }
    }

    printf("\n");
}

void dump_vm_class(Package_Executer*    package_executer,
                   RVM_ClassDefinition* class_definition) {

    assert(class_definition != nullptr);

    printf("%%%s    <%s:%d,%d>\n",
           class_definition->identifier,
           class_definition->source_file.c_str(),
           class_definition->start_line_number, class_definition->end_line_number);

    printf("+Field:     %d\n", class_definition->field_size);
    for (unsigned int i = 0; i < class_definition->field_size; i++) {
        printf(" ├──%-30s %-20s\n",
               format_rvm_type_specifier(package_executer, class_definition->field_list[i].type_specifier).c_str(),
               class_definition->field_list[i].identifier);
    }

    printf("+Method:    %d\n", class_definition->method_size);
    for (unsigned int i = 0; i < class_definition->method_size; i++) {
        printf(" ├──%s\n", class_definition->method_list[i].identifier);
    }

    printf("\n");


    for (unsigned int i = 0; i < class_definition->method_size; i++) {
        dump_vm_function(package_executer, class_definition, class_definition->method_list[i].rvm_function);
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

std::string format_rvm_type(RVM_Value* value) {
    std::string type_s = "";

    // TODO: 这里写和 std_lib.cpp::std_lib_reflect_typeof 重复了
    // 后期需要降低重复度
    switch (value->type) {
    case RVM_VALUE_TYPE_BOOL:
        type_s = "bool";
        break;
    case RVM_VALUE_TYPE_INT:
        type_s = "int";
        break;
    case RVM_VALUE_TYPE_DOUBLE:
        type_s = "double";
        break;
    case RVM_VALUE_TYPE_STRING:
        type_s = "string";
        break;
    case RVM_VALUE_TYPE_CLASS_OB:
        type_s = "class";
        break;
    case RVM_VALUE_TYPE_ARRAY:
        switch (value->u.array_value->type) {
        case RVM_ARRAY_BOOL: type_s = "bool"; break;
        case RVM_ARRAY_INT: type_s = "int"; break;
        case RVM_ARRAY_DOUBLE: type_s = "double"; break;
        case RVM_ARRAY_STRING: type_s = "string"; break;
        case RVM_ARRAY_CLASS_OBJECT: type_s = "class"; break;
        default: type_s = "unknow"; break;
        }

        type_s = type_s + "[!" + std::to_string(value->u.array_value->dimension) + "]";
        break;
    default:
        type_s = "unknow";
        break;
    }

    return type_s;
}

std::string format_rvm_value(RVM_Value* value) {
    std::string result;
    std::string str_data;

    // std_lib.cpp:std_lib_fmt_printf 代码重复
    // TODO: 需要后期优化
    switch (value->type) {
        // TODO: 这里重复了, 如何重写
    case RVM_VALUE_TYPE_BOOL:
        if (value->u.bool_value == RVM_FALSE) {
            result = std::string("false");
        } else {
            result = std::string("true");
        }
        break;
    case RVM_VALUE_TYPE_INT:
        result = std::to_string(value->u.int_value);
        break;
    case RVM_VALUE_TYPE_DOUBLE:
        result = std::to_string(value->u.double_value);
        break;
    case RVM_VALUE_TYPE_STRING:
        str_data = value->u.string_value->data;
        // 最多取 8 个字符, 方便显示
        result = "l:" + std::to_string(value->u.string_value->length) + ","
            + "d:\"" + str_data.substr(0, 8) + "\"";
        break;
    case RVM_VALUE_TYPE_CLASS_OB:
        result = std::string("class-ob"); // TODO:
        break;
    case RVM_VALUE_TYPE_ARRAY:
        result = "l:" + std::to_string(value->u.array_value->length) + ","
            + "c:" + std::to_string(value->u.array_value->capacity);
        break;
    default:
        break;
    }

    return result;
}


std::string format_rvm_call_stack(Ring_VirtualMachine* rvm) {

    unsigned int  offset = 0;
    RVM_CallInfo* pos    = rvm->call_info;

    std::string   result;


    for (; pos != nullptr; pos = pos->next, offset++) {
        if (pos->callee_function == nullptr) {
            result += "#" + std::to_string(offset) + " $ring!start()\n";
        } else {
            unsigned int source_line_number = 0;
            std::string  source_file        = pos->callee_function->source_file;


            result += "#" + std::to_string(offset) + " $ring!";
            // TODO: 这里想个更好的办法, 减少代码重复
            if (pos->callee_object == nullptr) {
                result += format_rvm_function(rvm->executer, pos->callee_function) + "\n";
            } else {
                result += std::string(pos->callee_object->class_ref->identifier) + "." + format_rvm_function(rvm->executer, pos->callee_function) + "\n";
            }


            if (offset == 0) {
                // 当前正在执行的函数
                source_line_number = get_source_line_number_by_pc(pos->callee_function, rvm->pc);
            } else {
                // 调用栈内的函数
                source_line_number = get_source_line_number_by_pc(pos->callee_function, pos->caller_pc);
            }
            result += "    " + source_file + ":" + std::to_string(source_line_number) + "\n";
        }
    }

    return result;
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