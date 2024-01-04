#include "ring.hpp"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#include <vector>


extern struct SyntaxInfo SyntaxInfos[];
static PackageUnit*      g_package_unit   = nullptr;
static CompilerEntry*    g_compiler_entry = nullptr;

// 编译阶段使用的 Memory Pool
// 这里暂时使用全局变量
MemPool* front_mem_pool                   = nullptr;


// 初始化一次
void init_front_mem_pool() {
    if (front_mem_pool != nullptr) {
        return;
    }

    front_mem_pool = create_mem_pool((char*)"Compiler-Front-Memory-Pool");
}

MemPool* get_front_mem_pool() {
    return front_mem_pool;
}

void destory_front_mem_pool() {
    if (front_mem_pool == nullptr) {
        return;
    }

    destory_mem_pool(front_mem_pool);
}


CompilerEntry* compiler_entry_create() {
    g_compiler_entry               = (CompilerEntry*)mem_alloc(get_front_mem_pool(), sizeof(CompilerEntry));
    g_compiler_entry->package_list = std::vector<Package*>{};
    g_compiler_entry->main_package = nullptr;
    return g_compiler_entry;
}

CompilerEntry* get_compiler_entry() {
    return g_compiler_entry;
}

void compiler_entry_dump(CompilerEntry* compiler_entry) {
    assert(compiler_entry != nullptr);
    printf("|------------------ CompilerEntry-Dump-begin ------------------\n");

    printf("|PackageList:\n");
    for (Package* package : compiler_entry->package_list) {
        printf("|\t package:%s\n", package->package_name);
    }

    printf("|MainPackage:\n");
    printf("|## package_name:%s,package_path:%s\n",
           compiler_entry->main_package->package_name,
           compiler_entry->main_package->package_path);


    printf("|------------------ CompilerEntry-Dump-begin ------------------\n\n");
}

Package* search_package(CompilerEntry* compiler_entry, char* package_name) {
    for (Package* package : compiler_entry->package_list) {
        if (0 == strcmp(package->package_name, package_name)) {
            return package;
        }
    }
    return nullptr;
}

ExecuterEntry* executer_entry_create() {
    ExecuterEntry* executer_entry         = (ExecuterEntry*)mem_alloc(NULL_MEM_POOL, sizeof(ExecuterEntry));
    executer_entry->package_executer_list = std::vector<Package_Executer*>{};
    executer_entry->main_package_executer = nullptr;
    return executer_entry;
}

void executer_entry_dump(ExecuterEntry* executer_entry) {
    assert(executer_entry != nullptr);
    printf("|------------------ ExecuterEntry-Dump-Summary ------------------\n");

    printf("|Package_Executer:\n");
    for (Package_Executer* package_executer : executer_entry->package_executer_list) {
        printf("|\t package: %s%s%s\n", LOG_COLOR_GREEN, package_executer->package_name, LOG_COLOR_CLEAR);
    }

    printf("|MainPackage_Executer:\n");
    printf("|## package_name:%s\n", executer_entry->main_package_executer->package_name);

    printf("|------------------ ExecuterEntry-Dump-Summary  ------------------\n\n");
}

// create package from a package's dir which contains multi files
Package* package_create(CompilerEntry* compiler_entry, char* package_name, char* package_path) {
    assert(compiler_entry != nullptr);
    debug_log_with_yellow_coloar("\t package[%s] create", package_name);

    Package* package                 = (Package*)mem_alloc(get_front_mem_pool(), sizeof(Package));

    package->compiler_entry          = compiler_entry;
    package->package_index           = -1; // TODO: 这个应该在 fix的时候 设置
    package->package_name            = package_name;
    package->package_path            = package_path;

    package->source_file_list        = list_files_of_dir(package_path);

    package->global_declaration_list = std::vector<Declaration*>{};
    package->class_definition_list   = std::vector<ClassDefinition*>{};
    package->function_list           = std::vector<Function*>{};

    package->global_identifier_map   = std::unordered_set<std::string>{};
    package->global_declaration_map  = std::unordered_map<std::string, Declaration*>{};
    package->class_definition_map    = std::unordered_map<std::string, ClassDefinition*>{};
    package->function_map            = std::unordered_map<std::string, Function*>{};
    package->import_package_map      = std::unordered_map<std::string, std::string>{};

    package->package_unit_list       = std::vector<PackageUnit*>{};

    package->compile_error_num       = 0;

    return package;
}

// create package from only source file
Package* package_create_input_file(CompilerEntry* compiler_entry, char* package_name, char* input_main_file) {
    assert(compiler_entry != nullptr);
    debug_log_with_yellow_coloar("\t package[%s] create", package_name);

    Package* package                 = (Package*)mem_alloc(get_front_mem_pool(), sizeof(Package));

    package->compiler_entry          = compiler_entry;
    package->package_index           = -1; // TODO: 这个应该在 fix的时候 设置
    package->package_name            = package_name;
    package->package_path            = nullptr;

    package->source_file_list        = std::vector<std::string>{std::string(input_main_file)};

    package->global_declaration_list = std::vector<Declaration*>{};
    package->class_definition_list   = std::vector<ClassDefinition*>{};
    package->function_list           = std::vector<Function*>{};

    package->global_identifier_map   = std::unordered_set<std::string>{};
    package->global_declaration_map  = std::unordered_map<std::string, Declaration*>{};
    package->class_definition_map    = std::unordered_map<std::string, ClassDefinition*>{};
    package->function_map            = std::unordered_map<std::string, Function*>{};
    package->import_package_map      = std::unordered_map<std::string, std::string>{};

    package->package_unit_list       = std::vector<PackageUnit*>{};

    package->compile_error_num       = 0;


    return package;
}

// 获取包下的所有 ring 源代码文件
// 依次生成 PackageUnit 进行编译
void package_compile(Package* package) {
    CompilerEntry* compiler_entry = package->compiler_entry;

    if (nullptr != search_package(compiler_entry, package->package_name)) {
        debug_log_with_yellow_coloar("\t package[%s] already compiled", package->package_name);
        return;
    }
    debug_log_with_yellow_coloar("\t package[%s] start compile...", package->package_name);

    package->package_index = compiler_entry->package_list.size(); // TODO: 这个应该在 fix的时候 设置
    compiler_entry->package_list.push_back(package);

    for (std::string source_file : package->source_file_list) {
        PackageUnit* package_unit = package_unit_create(package, source_file);
        package_unit_compile(package_unit);
        package->package_unit_list.push_back(package_unit);
    }

    for (PackageUnit* package_unit : package->package_unit_list) {
        for (Declaration* decl : package_unit->global_declaration_list) {
            package->global_declaration_list.push_back(decl);
        }
        for (ClassDefinition* pos : package_unit->class_definition_list) {
            package->class_definition_list.push_back(pos);
        }
        for (Function* pos : package_unit->function_list) {
            package->function_list.push_back(pos);
        }
    }

    ring_compiler_semantic_analysis(package);
    ring_compiler_check_exit(package);
    ring_compiler_fix_ast(package);


#ifdef DEBUG_COMPILER_SUMMARY
    package_dump(package);
    for (PackageUnit* package_unit : package->package_unit_list) {
        package_unit_dump(package_unit);
    }
    printf("\n\n");
#endif
}

void package_dump(Package* package) {
    printf("|------------------ Package-Dump-begin ------------------\n");

    printf("|## package_name: %s%s%s\n", LOG_COLOR_GREEN, package->package_name, LOG_COLOR_CLEAR);
    printf("|## package_path: %s%s%s\n", LOG_COLOR_GREEN, package->package_path, LOG_COLOR_CLEAR);

    printf("|## PackageUnit:\n");
    for (auto package_unit : package->package_unit_list) {
        printf("|\tfile_name: %s%s%s\n", LOG_COLOR_GREEN, package_unit->current_file_name.c_str(), LOG_COLOR_CLEAR);
    }

    printf("|## Declaration:\n");
    for (auto declaration : package->global_declaration_list) {
        printf("|\tdeclaration identifier:%s\n", declaration->identifier);
    }

    printf("|## ClassDefinition:\n");
    for (auto class_definition : package->class_definition_list) {
        printf("|\tclass_definition identifier:%s\n", class_definition->class_identifier);
    }

    printf("|## Function:\n");
    for (auto function : package->function_list) {
        printf("|\tfunction_name: %s%s%s\n", LOG_COLOR_YELLOW, function->function_name, LOG_COLOR_CLEAR);
    }

    printf("|------------------ Package-Dump-end  ------------------\n");
}

// create packge by a input source file
PackageUnit* package_unit_create(Package* parent_package, std::string file_name) {
    g_package_unit                                   = (PackageUnit*)mem_alloc(get_front_mem_pool(), sizeof(PackageUnit));

    g_package_unit->parent_package                   = parent_package;

    g_package_unit->current_file_name                = file_name;
    g_package_unit->current_file_fp                  = nullptr;
    g_package_unit->file_fp_random                   = nullptr;
    g_package_unit->current_line_number              = 1;
    g_package_unit->current_column_number            = 1;
    g_package_unit->current_line_content             = new_ring_string();

    g_package_unit->current_line_start_offset        = 0;
    g_package_unit->current_offset                   = 0;
    g_package_unit->line_offset_map                  = std::vector<SourceLineInfo>{SourceLineInfo{0, 0}};

    g_package_unit->import_package_list              = std::vector<ImportPackageInfo*>{};

    g_package_unit->global_block_statement_list_size = 0;
    g_package_unit->global_block_statement_list      = nullptr;
    g_package_unit->global_declaration_list          = std::vector<Declaration*>{};

    g_package_unit->class_definition_list            = std::vector<ClassDefinition*>{};
    g_package_unit->function_list                    = std::vector<Function*>{};

    g_package_unit->current_block                    = nullptr;

    g_package_unit->compile_error_num                = 0;


    g_package_unit->current_file_fp                  = fopen(file_name.c_str(), "r");
    g_package_unit->file_fp_random                   = fopen(file_name.c_str(), "r");

    if (g_package_unit->current_file_fp == nullptr
        || g_package_unit->file_fp_random == nullptr) {
        fprintf(stderr, "%s not found.\n", file_name.c_str());
        exit(1);
    }

    return g_package_unit;
}

PackageUnit* get_package_unit() {
    return g_package_unit;
}

void package_unit_compile(PackageUnit* package_unit) {
    extern int   yyparse(void);
    extern FILE* yyin;

    yyin = package_unit->current_file_fp;

    // bison 在 yyparse 过程中如果遇到不合法的语法, 会调用 yyerror
    if (yyparse()) {
        package_unit->compile_error_num++;
    }
    if (package_unit->compile_error_num) {
        complie_err_log("\n\n%d grammars error detected.\n", package_unit->compile_error_num);
        exit(ERROR_CODE_COMPILE_ERROR);
    }

#ifdef DEBUG_CREATE_AST
    // check package_unit->line_offset_map is valid
    printf("File:%s\n", package_unit->current_file_name.c_str());
    for (int i = 1; i < package_unit->line_offset_map.size(); i++) {
        printf("Line:%5d:%s\n", i, package_unit_get_line_content(i).c_str());
    }
#endif

    debug_log_with_yellow_coloar("\t package_unit COMPLIE SUCCESS\n\n");
}

void package_unit_dump(PackageUnit* package_unit) {
    printf("|------------------ PackageUnit-Dump-begin ------------------\n");

    printf("|## file_name: %s%s%s\n", LOG_COLOR_GREEN, package_unit->current_file_name.c_str(), LOG_COLOR_CLEAR);

    printf("|## Declaration:\n");
    for (Declaration* decl : package_unit->global_declaration_list) {
        printf("|\tdeclaration global-variable: identifier:%s\n", decl->identifier);
    }

    printf("|## ClassDefinition:\n");
    for (auto class_definition : package_unit->class_definition_list) {
        printf("|\tclass_definition identifier:%s\n", class_definition->class_identifier);
    }

    printf("|## Function:\n");
    for (auto function : package_unit->function_list) {
        printf("|\tfunction_name: %s%s%s\n", LOG_COLOR_YELLOW, function->function_name, LOG_COLOR_CLEAR);
    }

    printf("|------------------ PackageUnit-Dump-end  ------------------\n");
}


std::string package_unit_get_file_name() {
    assert(g_package_unit != nullptr);
    return g_package_unit->current_file_name;
}

Ring_String* get_package_unit_current_line_content() {
    assert(g_package_unit != nullptr);
    return g_package_unit->current_line_content;
}

unsigned int package_unit_get_line_number() {
    assert(g_package_unit != nullptr);
    return g_package_unit->current_line_number;
}

unsigned int package_unit_increa_line_number() {
    assert(g_package_unit != nullptr);
    g_package_unit->current_line_number++;
    return g_package_unit->current_line_number;
}

unsigned int package_unit_get_column_number() {
    assert(g_package_unit != nullptr);
    return g_package_unit->current_column_number;
}

unsigned int package_unit_increa_column_number(unsigned int len) {
    assert(g_package_unit != nullptr);
    g_package_unit->current_column_number += len;
    return g_package_unit->current_column_number;
}

void package_unit_update_line_content(char* str) {
    assert(g_package_unit != nullptr);

    unsigned int str_len = strlen(str);

    for (unsigned int i = 0; i < str_len; i++) {
        ring_string_add_char(g_package_unit->current_line_content, str[i]);
    }

    if (g_package_unit->current_line_number == g_package_unit->line_offset_map.size()) {
        g_package_unit->line_offset_map.push_back(SourceLineInfo{
            .start_offset = g_package_unit->current_line_start_offset,
            .size         = 0,
        });
    }

    g_package_unit->line_offset_map[g_package_unit->current_line_number].size += str_len;

    g_package_unit->current_offset += str_len;
    g_package_unit->current_column_number += str_len;

    if (strcmp(str, "\n") == 0 || strcmp(str, "\r\n") == 0) {
        // TODO: 这里 -1 没搞明白
        g_package_unit->line_offset_map[g_package_unit->current_line_number].size -= (str_len - 1);

        g_package_unit->current_line_start_offset = g_package_unit->current_offset;
    }
}


void package_unit_reset_line_content() {
    reset_ring_string(g_package_unit->current_line_content);
}

char* package_unit_get_current_line_content() {
    return get_ring_string(g_package_unit->current_line_content);
}

void package_unit_reset_column_number() {
    g_package_unit->current_column_number = 1;
}

std::string package_unit_get_line_content(unsigned int line_number) {
    if (line_number >= g_package_unit->line_offset_map.size()) {
        return "";
    }
    off_t        line_offset = g_package_unit->line_offset_map[line_number].start_offset;
    unsigned int size        = g_package_unit->line_offset_map[line_number].size;

    // 这里得使用一个新的随机指针, 不然会印象 bision继续 向下分析
    fseek(g_package_unit->file_fp_random, line_offset, SEEK_SET);
    char buffer[500];
    if (fgets(buffer, size, g_package_unit->file_fp_random) == NULL) {
        fprintf(stderr, "Warning: fgets line content is error.\n");
        exit(1);
    }

    return std::string(buffer);
}

int package_unit_add_class_definition(ClassDefinition* class_definition) {
    assert(g_package_unit != nullptr);
    assert(class_definition != nullptr);

    g_package_unit->class_definition_list.push_back(class_definition);
    return 0;
}

Ring_Grammar_Info Ring_Grammar_Infos[] = {
    {
        GRAMMAR_UNKNOW,
        std::vector<std::string>{},
    },
    {
        GRAMMAR_IMPORT_PACKAGE,
        std::vector<std::string>{
            "import {",
            "    package-name;",
            "}",
        },
    },
    {
        GRAMMAR_FUNCTION_DEFIN,
        std::vector<std::string>{
            "function <identifier> (parameter_list) -> (return_value_list) {",
            "    code_block;",
            "}",
        },

    },
    {
        GRAMMAR_CLASS_DEFIN,
        std::vector<std::string>{
            "typedef class <identifier> {",
            "    code_block;",
            "}",
        },
    },

};

extern char linebuf[1024];

//
void ring_grammar_error(RING_GRAMMAR_ID grammar_id) {
    char compile_adv_buf[2048];
    snprintf(compile_adv_buf, sizeof(compile_adv_buf), "%sTip:%s import package grammar",
             LOG_COLOR_YELLOW,
             LOG_COLOR_CLEAR);

    printf("|%s\n", compile_adv_buf);
    for (std::string grammar : Ring_Grammar_Infos[grammar_id].grammar) {
        printf("|%s\n", grammar.c_str());
    }

    // TODO: 这里不能进行 多个错误的上报了
    fprintf(stderr, "\n\n%d errors generated, exit.\n", 1);
    fflush(stderr);
    exit(1);
}

int yyerror(char const* str, ...) {
    // 调用 ring_compiler_error
    // 在这里捕获详细信息

    std::string err_str = trans_flex_token_to_human_char(std::string(str));

    fprintf(stderr, "\n%s:%d:%d: \n",
            package_unit_get_file_name().c_str(),
            package_unit_get_line_number(),
            package_unit_get_column_number());

    fprintf(stderr, "|%s\n", linebuf);
    fprintf(stderr, "|%s%*s^......%s\n",
            LOG_COLOR_GREEN,
            package_unit_get_column_number(), " ",
            LOG_COLOR_CLEAR);
    fprintf(stderr, "|\n");

    fprintf(stderr, "|%sError:%s %s\n",
            LOG_COLOR_RED,
            LOG_COLOR_CLEAR,
            err_str.c_str());

    // fprintf(stderr, "\n\n\n\n");
    fflush(stderr);

    return 0;
}


// ring_compile_error_report
void ring_compile_error_report(ErrorReportContext* context) {
    fprintf(stderr, "%s:%d:%d: \n",
            context->source_file_name.c_str(),
            context->line_number,
            context->column_number);

    fprintf(stderr, "|%s\n", context->line_content.c_str());
    fprintf(stderr, "|%s%*s^......%s\n",
            LOG_COLOR_GREEN,
            context->column_number, " ",
            LOG_COLOR_CLEAR);
    fprintf(stderr, "|\n");

    if (context->error_message.size()) {
        fprintf(stderr, "|%sError:%s %s\n",
                LOG_COLOR_RED,
                LOG_COLOR_CLEAR,
                context->error_message.c_str());
    }

    if (context->advice.size()) {
        fprintf(stderr, "|%sTip:%s %s\n",
                LOG_COLOR_YELLOW,
                LOG_COLOR_CLEAR,
                context->advice.c_str());
    }

#ifdef DEBUG
    fprintf(stderr, "|RingDebug: %s:%d\n", context->ring_compiler_file, context->ring_compiler_file_line);
#endif

    // fprintf(stderr, "\n\n\n\n");
    fflush(stderr);

    if (context->report_type == ERROR_REPORT_TYPE_EXIT_NOW
        || context->package_unit == nullptr) {
        exit(1);
    }

    context->package_unit->compile_error_num += 1;
    if (context->package_unit->compile_error_num >= 7) {
        fprintf(stderr, "%d errors generated, exit.\n", context->package_unit->compile_error_num);
        fflush(stderr);
        exit(1);
    }
}

void ring_check_exit_immediately() {
    exit(1);
}

/*
 * 将bison报错的原始信息进行转化, 转化成更人性化的形式
 */
std::string trans_flex_token_to_human_char(std::string str) {
    // e.g.  TOKEN_TYPEDEF 转化成  typedef
    std::vector<std::pair<std::string, std::string>> replace_tokens = {
        {"grammar error", "syntax error"},

        {"`typedef`", "TOKEN_TYPEDEF"},
        {"`bool`", "TOKEN_BOOL"},
        {"`int`", "TOKEN_INT"},
        {"`double`", "TOKEN_DOUBLE"},
        {"`string`", "TOKEN_STRING"},
        {"`struct`", "TOKEN_STRUCT"},
        {"`bind`", "TOKEN_BIND"},
        {"`lambda`", "TOKEN_LAMBDA"},
        {"`return`", "TOKEN_RETURN"},
        {"`defer`", "TOKEN_DEFER"},
        {"`range`", "TOKEN_RANGE"},
        {"`in`", "TOKEN_IN"},
        {"`class`", "TOKEN_CLASS"},
        {"`private`", "TOKEN_PRIVATE"},
        {"`public`", "TOKEN_PUBLIC"},
        {"`@`", "TOKEN_ATTRIBUTE"},
        {"`field`", "TOKEN_FIELD"},
        {"`method`", "TOKEN_METHOD"},
        {"`constructor`", "TOKEN_CONSTRUCTOR"},
        {"`global`", "TOKEN_GLOBAL"},
        {"`if`", "TOKEN_IF"},
        {"`elseif`", "TOKEN_ELSEIF"},
        {"`else`", "TOKEN_ELSE"},
        {"`for`", "TOKEN_FOR"},
        {"`do`", "TOKEN_DO"},
        {"`break`", "TOKEN_BREAK"},
        {"`jump`", "TOKEN_JUMP"},
        {"`continue`", "TOKEN_CONTINUE"},
        {"`null`", "TOKEN_NULL"},
        {"`true`", "TOKEN_TRUE"},
        {"`false`", "TOKEN_FALSE"},
        {"`var`", "TOKEN_VAR"},
        {"`auto`", "TOKEN_AUTO"},
        {"`any`", "TOKEN_ANY"},
        {"`const`", "TOKEN_CONST"},
        {"`function`", "TOKEN_FUNCTION"},
        {"`new`", "TOKEN_NEW"},
        {"`delete`", "TOKEN_DELETE"},
        {"`.`", "TOKEN_DOT"},
        {"`..`", "TOKEN_2DOT"},
        {"`...`", "TOKEN_3DOT"},
        {"`->`", "TOKEN_ARROW"},
        {"`package`", "TOKEN_PACKAGE"},
        {"`import`", "TOKEN_IMPORT"},
        {"`+`", "TOKEN_ADD"},
        {"`-`", "TOKEN_SUB"},
        {"`*`", "TOKEN_MUL"},
        {"`/`", "TOKEN_DIV"},
        {"`%`", "TOKEN_MOD"},
        {"`++`", "TOKEN_INCREASE"},
        {"`--`", "TOKEN_DECREASE"},
        {"`+=`", "TOKEN_ADD_ASSIGN"},
        {"`-=`", "TOKEN_SUB_ASSIGN"},
        {"`*=`", "TOKEN_MUL_ASSIGN"},
        {"`/=`", "TOKEN_DIV_ASSIGN"},
        {"`%=`", "TOKEN_MOD_ASSIGN"},
        {"`and`", "TOKEN_AND"},
        {"`or`", "TOKEN_OR"},
        {"`not`", "TOKEN_NOT"},
        {"`==`", "TOKEN_EQ"},
        {"`!=`", "TOKEN_NE"},
        {"`>`", "TOKEN_GT"},
        {"`>=`", "TOKEN_GE"},
        {"`<`", "TOKEN_LT"},
        {"`<=`", "TOKEN_LE"},
        {"`(`", "TOKEN_LP"},
        {"`)`", "TOKEN_RP"},
        {"`{`", "TOKEN_LC"},
        {"`}`", "TOKEN_RC"},
        {"`[`", "TOKEN_LB"},
        {"`]`", "TOKEN_RB"},
        {"`,`", "TOKEN_COMMA"},
        {"`:`", "TOKEN_COLON"},
        {"`::`", "TOKEN_2COLON"},
        {"`;`", "TOKEN_SEMICOLON"},
        {"`?`", "TOKEN_QUESTION_MARK"},
        {"`=`", "TOKEN_ASSIGN"},
        {"`#`", "TOKEN_NUM_SIGN"},
    };

    // 先排一下顺序, 在字符串替换的时候要先匹配最长的, 再匹配最短的
    std::sort(replace_tokens.begin(), replace_tokens.end(),
              [](const std::pair<std::string, std::string>& a, const std::pair<std::string, std::string>& b) {
                  return a.second.length() > b.second.length();
              });

    for (int i = 0; i < replace_tokens.size(); i++) {
        str = str_replace_all(str, replace_tokens[i].second, replace_tokens[i].first);
    }

    return str;
}

std::string str_replace_all(std::string        subject,
                            const std::string& search,
                            const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

// 用于错误恢复
// 将 yyin移动到下一行中
void yyin_move_to_next_line() {
    extern FILE* yyin;


    // printf("yyin_move_to_next_line\n");

    // printf("_offset %ld\n", yyin->_offset);
    // char buffer[500];
    // fgets(buffer, 50, yyin);
    // printf("=%s\n", buffer);
    // exit(1);
    // char buffer;
    // while(fgets(&buffer, 1, yyin) != NULL) {
    //     printf("buffer:%c\n", buffer);
    //     if (buffer == '\n') {
    //         break;
    //     }
    //     fseek(yyin, 1, SEEK_CUR);
    //     exit(1);
    // }
}