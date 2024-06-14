#include "ring.hpp"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>


extern RVM_Opcode_Info RVM_Opcode_Infos[];

/*
 * formate_expression
 *
 * 前端通过 bison 生成AST
 * 这里将AST表达式转换为字符串
 * 这样在语义分析的时候，可以展示源代码，报错提示更加人性化
 */
std::string formate_expression(Expression* expression) {
    std::string result;

    if (expression == nullptr) {
        return result;
    }

    switch (expression->type) {

    case EXPRESSION_TYPE_LITERAL_BOOL:
        if (expression->u.bool_literal) {
            result = "true";
        } else {
            result = "false";
        }
        break;
    case EXPRESSION_TYPE_LITERAL_INT:
        result = std::to_string(expression->u.int_literal);
        break;
    case EXPRESSION_TYPE_LITERAL_INT64:
        result = std::to_string(expression->u.int64_literal) + "L";
        break;
    case EXPRESSION_TYPE_LITERAL_DOUBLE:
        result = std::to_string(expression->u.double_literal);
        break;
    case EXPRESSION_TYPE_LITERAL_STRING:
        result = expression->u.string_literal;
        break;

    case EXPRESSION_TYPE_VARIABLE:
        break;

    case EXPRESSION_TYPE_IDENTIFIER:
        break;

    case EXPRESSION_TYPE_FUNCTION_CALL:
        result = expression->u.function_call_expression->func_identifier;
        break;

    case EXPRESSION_TYPE_METHOD_CALL:
        break;

    case EXPRESSION_TYPE_ASSIGN:
        break;

    case EXPRESSION_TYPE_TERNARY:
        break;


    case EXPRESSION_TYPE_CONCAT:
        break;
    case EXPRESSION_TYPE_ARITHMETIC_ADD:
    case EXPRESSION_TYPE_ARITHMETIC_SUB:
    case EXPRESSION_TYPE_ARITHMETIC_MUL:
    case EXPRESSION_TYPE_ARITHMETIC_DIV:
    case EXPRESSION_TYPE_ARITHMETIC_MOD:
        break;
    case EXPRESSION_TYPE_LOGICAL_AND:
    case EXPRESSION_TYPE_LOGICAL_OR:
        break;
    case EXPRESSION_TYPE_RELATIONAL_EQ:
    case EXPRESSION_TYPE_RELATIONAL_NE:
    case EXPRESSION_TYPE_RELATIONAL_GT:
    case EXPRESSION_TYPE_RELATIONAL_GE:
    case EXPRESSION_TYPE_RELATIONAL_LT:
    case EXPRESSION_TYPE_RELATIONAL_LE:
        break;


    case EXPRESSION_TYPE_ARITHMETIC_UNITARY_MINUS:
    case EXPRESSION_TYPE_LOGICAL_UNITARY_NOT:
    case EXPRESSION_TYPE_UNITARY_INCREASE:
    case EXPRESSION_TYPE_UNITARY_DECREASE:
        break;


    case EXPRESSION_TYPE_NEW_ARRAY:
        break;
    case EXPRESSION_TYPE_ARRAY_LITERAL:
        break;
    case EXPRESSION_TYPE_CLASS_OBJECT_LITERAL:
        break;


    case EXPRESSION_TYPE_ARRAY_INDEX:
        break;
    case EXPRESSION_TYPE_MEMBER:
        break;

    case EXPRESSION_TYPE_ELEMENT_ACCESS:
        break;

    case EXPRESSION_TYPE_CAST:
        break;

    default: break;
    }

    return result;
}


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
        printf("function[%d]: name:%s\n", i, func->identifier);
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
        func_name = std::string(function->identifier);
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
 * 计算文件的 file_stat, 方便后续直接引用
 *
 * file_name 可以是绝对路径, 可以是相对路径
 *
 * TODO: 文件的路径可能要兼容 linux 和 windows
 */
RingFileStat* create_ring_file_stat(std::string& file_name) {

    assert(file_name.size());

    char absolute_path[PATH_MAX * 2];
    if (file_name[0] == '/') {
        strcpy(absolute_path, file_name.c_str());
    } else {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            ring_error_report("getcwd error:%s\n", strerror(errno));
        }

        snprintf(absolute_path, sizeof(absolute_path),
                 "%s/%s", cwd, file_name.c_str());
    }

    // 将相对路径转换为绝对路径，并解析符号链接和 .. 和 . 目录引用
    char* real_path = realpath(absolute_path, NULL);
    if (real_path == NULL) {
        ring_error_report("realpath error:%s, path:%s\n", strerror(errno), absolute_path);
    }

    struct stat stat_;
    if (stat(real_path, &stat_) != 0) {
        ring_error_report("get file stat error:%s, path:%s\n", strerror(errno), real_path);
    }

    FILE* fp = fopen(real_path, "r");
    if (fp == nullptr) {
        ring_error_report("open file error:%s, path:%s\n", strerror(errno), real_path);
    }

    // 绝对路径中 取文件名
    char* basename_ = basename(real_path);
    if (basename_ == nullptr) {
        ring_error_report("basename error:%s, path:%s\n", strerror(errno), real_path);
    }

    // 绝对路径中 取路径名
    char* dirname_ = dirname(real_path);
    if (dirname_ == nullptr) {
        ring_error_report("dirname error:%s, path:%s\n", strerror(errno), real_path);
    }


    RingFileStat* file_stat    = (RingFileStat*)mem_alloc(nullptr, sizeof(RingFileStat)); // TODO: 内存分配在哪里
    file_stat->dir             = dirname_;
    file_stat->file_name       = basename_;
    file_stat->abs_path        = real_path;
    file_stat->last_modified   = stat_.st_mtime;
    file_stat->fp              = fp;
    file_stat->line_offset_map = std::vector<SourceLineInfo>{SourceLineInfo{0, 0}};

    /*
     * 在 g++ (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0 中
     * file_stat->dir             = std::string(basename(real_path));
     * 会引起崩溃
     */

    return file_stat;
}

// get_file_contents [start_line, end_line)
std::vector<std::string> get_file_contents(RingFileStat* file_stat, unsigned int start_line, unsigned int end_line) {
    if (end_line < start_line) {
        end_line = start_line + end_line;
    }

    if (start_line >= file_stat->line_offset_map.size()) {
        return std::vector<std::string>{};
    }

    std::vector<std::string> result;
    for (unsigned int i = start_line; i < end_line; i++) {
        result.push_back(get_file_content(file_stat, i));
    }


    return result;
}

std::string get_file_content(RingFileStat* file_stat, unsigned int line_number) {
    if (line_number >= file_stat->line_offset_map.size()) {
        return "";
    }

    // 找到源代码行数 所对应的 文件的偏移、行的空间
    // 方便 fseek快速定位读取
    off_t        line_offset = file_stat->line_offset_map[line_number].start_offset;
    unsigned int size        = file_stat->line_offset_map[line_number].size;

    // 这里得使用一个新的随机读取指针, 不能和bison使用的fp共用
    // 不然会影响 bision继续 向下分析
    fseek(file_stat->fp, line_offset, SEEK_SET);
    char buffer[1024]; // TODO: 这里后续要按需分配
    if (size == 0) {
        return "";
    }
    // size + 1 because fgets read size (including the final null-character).
    if (fgets(buffer, size + 1, file_stat->fp) == NULL) {
        ring_error_report("Warning: fgets line content is error.\n");
    }

    return std::string(buffer);
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
        std::string tmp = format_rvm_type_specifier(package_executer, function->parameter_list[i].type_specifier)
            + (function->parameter_list[i].is_variadic ? "..." : "");
        printf(" ├──%-20s %-20s\n",
               tmp.c_str(),
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
    case CONSTANTPOOL_TYPE_INT64:
        return "int64(" + std::to_string(constant->u.int64_value) + ")";
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
    case RVM_VALUE_TYPE_INT64:
        type_s = "int64";
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
        case RVM_ARRAY_INT64: type_s = "int64"; break;
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

/*
 * format_rvm_value
 *
 * 这个函数的扩展性还不是特别好, 目前只是给debugger使用,
 * 因为在 formate  string 的时候, 怕数据过多, 只formate了 8 个字符
 *
 */
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
    case RVM_VALUE_TYPE_INT64:
        result = std::to_string(value->u.int64_value);
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
    std::string   item;

    std::string   prefix;
    std::string   func_name;
    std::string   source_file;
    unsigned int  source_line_number = 0;

    for (; pos != nullptr; pos = pos->next, offset++) {

        if (offset == 0) {
            prefix = "#" + std::to_string(offset) + " $ring!";

            if (pos->callee_object == nullptr) {
                func_name = format_rvm_function(rvm->executer, pos->callee_function);
            } else {
                func_name = std::string(pos->callee_object->class_ref->identifier)
                    + "."
                    + format_rvm_function(rvm->executer, pos->callee_function);
            }

            source_file        = pos->callee_function->source_file;
            source_line_number = get_source_line_number_by_pc(pos->callee_function, rvm->pc);

            //
            item = prefix + func_name + "\n"
                + "    " + source_file + ":" + std::to_string(source_line_number) + "\n";

            result += item;

            offset++;
        }

        prefix = "#" + std::to_string(offset) + " $ring!";

        if (pos->caller_function == nullptr) {
            item = prefix + "start()\n";
        } else {

            if (pos->caller_object == nullptr) {
                func_name = format_rvm_function(rvm->executer, pos->caller_function);
            } else {
                func_name = std::string(pos->caller_object->class_ref->identifier)
                    + "."
                    + format_rvm_function(rvm->executer, pos->caller_function);
            }

            source_file        = pos->caller_function->source_file;
            source_line_number = get_source_line_number_by_pc(pos->caller_function, pos->caller_pc);

            //
            item = prefix + func_name + "\n"
                + "    " + source_file + ":" + std::to_string(source_line_number) + "\n";
        }

        result += item;
    }

    return result;
}

std::string format_rvm_current_func(Ring_VirtualMachine* rvm, unsigned int source_line_number) {
    RVM_CallInfo* pos = rvm->call_info;
    std::string   result;

    assert(pos != nullptr);
    assert(pos->callee_function != nullptr);


    std::string source_file = pos->callee_function->source_file;


    result += "$ring!";
    // TODO: 这里想个更好的办法, 减少代码重复
    if (pos->callee_object == nullptr) {
        result += format_rvm_function(rvm->executer, pos->callee_function);
    } else {
        result += std::string(pos->callee_object->class_ref->identifier) + "." + format_rvm_function(rvm->executer, pos->callee_function);
    }


    if (source_line_number == 0) {
        // 当前正在执行的函数
        source_line_number = get_source_line_number_by_pc(pos->callee_function, rvm->pc);
    }


    result += "    " + source_file + ":" + std::to_string(source_line_number) + "\n";


    return result;
}

// TODO: 格式化数组类型
std::string format_type_specifier(TypeSpecifier* type_specifier) {
    assert(type_specifier != nullptr);

    std::string str = "";

    switch (type_specifier->kind) {
    case RING_BASIC_TYPE_BOOL:
        str = "bool";
        break;
    case RING_BASIC_TYPE_INT:
        str = "int";
        break;
    case RING_BASIC_TYPE_INT64:
        str = "int64";
        break;
    case RING_BASIC_TYPE_DOUBLE:
        str = "double";
        break;
    case RING_BASIC_TYPE_STRING:
        str = "string";
        break;

    case RING_BASIC_TYPE_CLASS:
        str = "class";
        break;
    case RING_BASIC_TYPE_ARRAY:
        str = "array";
        break;

    case RING_BASIC_TYPE_ANY:
        str = "any";
        break;

    default:
        str = ".unknow";
        break;
    }

    return str;
}

// TODO: 格式化数组类型
std::string format_function_parameters(Parameter* parameter) {
    std::string              str = "";
    std::vector<std::string> strings;


    for (; parameter != nullptr; parameter = parameter->next) {
        str += format_type_specifier(parameter->type_specifier);
        if (parameter->is_variadic) {
            str += "...";
        }

        strings.push_back(str);
    }


    return strings_join(strings, ",");
}

// TODO: 格式化数组类型
std::string format_function_arguments(ArgumentList* argument) {
    std::string              str = "";
    std::vector<std::string> strings;


    for (; argument != nullptr; argument = argument->next) {
        strings.push_back(format_type_specifier(argument->expression->convert_type[0]));
    }

    str = strings_join(strings, ",");

    return str;
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

std::string strings_join(const std::vector<std::string>& lst, const std::string& delim) {
    std::string ret;
    for (const auto& s : lst) {
        if (!ret.empty())
            ret += delim;
        ret += s;
    }
    return ret;
}

/*
 * rvm_string_cmp 和 string_compare 实现重复了，后续需要结合到一起
 * TODO: 这里实现的不太优雅
 */
int string_compare(const char* str1, unsigned int str1_len, const char* str2, unsigned int str2_len) {

    if (str1_len == 0 && str2_len == 0) {
        return 0;
    } else if (str1_len == 0 && str2_len != 0) {
        return -1;
    } else if (str1_len != 0 && str2_len == 0) {
        return 1;
    }

    unsigned int min_len = (str1_len > str2_len) ? str2_len : str1_len;
    int          res     = strncmp(str1, str2, min_len);
    if (res == 0) {
        if (str1_len > str2_len)
            return 1;
        else if (str1_len == str2_len)
            return 0;
        else
            return -1;
    } else {
        return res;
    }
}