#include "ring.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

int                      yyerror(char const* str, ...);
extern struct SyntaxInfo SyntaxInfos[];
static PackageUnit*      package_unit   = NULL;
static CompilerEntry*    compiler_entry = NULL;

// Error Attention 某些错误提示可以精细化识别、提示
void                     ring_compiler_error(SyntaxType syntax_type, int need_exit) {
    std::string message = "syntax error:\nRing Grammar Standard:\n\t" + std::string(SyntaxInfos[SYNTAX_VARIABLE_DEFINITION].bnf);
    yyerror(message.c_str());
    package_unit->compile_error_num++;
    if (need_exit) {
        // Donot exit when detect a error.
        // Get next line and compile.
        exit(ERROR_CODE_COMPILE_ERROR);
    }
}

CompilerEntry* compiler_entry_create() {
    compiler_entry               = (CompilerEntry*)malloc(sizeof(CompilerEntry));
    compiler_entry->package_list = std::vector<Package*>{};
    compiler_entry->main_package = NULL;
    return compiler_entry;
}

CompilerEntry* get_compiler_entry() {
    return compiler_entry;
}

void compiler_entry_dump(CompilerEntry* compiler_entry) {
    assert(compiler_entry != NULL);
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
    return NULL;
}

ExecuterEntry* executer_entry_create() {
    ExecuterEntry* executer_entry         = (ExecuterEntry*)malloc(sizeof(ExecuterEntry));
    executer_entry->package_executer_list = std::vector<Package_Executer*>{};
    executer_entry->main_package_executer = NULL;
    return executer_entry;
}

void executer_entry_dump(ExecuterEntry* executer_entry) {
    assert(executer_entry != NULL);
    printf("|------------------ ExecuterEntry-Dump-begin ------------------\n");

    printf("|Package_Executer:\n");
    for (Package_Executer* package_executer : executer_entry->package_executer_list) {
        printf("|\t package:%s\n", package_executer->package_name);
    }

    printf("|MainPackage_Executer:\n");
    printf("|## package_name:%s\n", executer_entry->main_package_executer->package_name);

    printf("|------------------ ExecuterEntry-Dump-end  ------------------\n\n");
}

// create package from a package's dir which contains multi files
Package* package_create(CompilerEntry* compiler_entry, char* package_name, char* package_path) {
    assert(compiler_entry != NULL);
    debug_log_with_yellow_coloar("\t package[%s] create", package_name);

    Package* package                 = (Package*)malloc(sizeof(Package));

    package->compiler_entry          = compiler_entry;
    package->package_index           = -1; // TODO: 这个应该在 fix的时候 设置
    package->package_name            = package_name;
    package->package_path            = package_path;

    package->source_file_list        = list_file(package->package_path);

    package->global_declaration_list = std::vector<Declaration*>{};
    package->class_definition_list   = std::vector<ClassDefinition*>{};
    package->function_list           = std::vector<Function*>{};

    package->package_unit_list       = std::vector<PackageUnit*>{};

    return package;
}

// create package from only source file
Package* package_create_input_file(CompilerEntry* compiler_entry, char* package_name, char* input_main_file) {
    assert(compiler_entry != NULL);
    debug_log_with_yellow_coloar("\t package[%s] create", package_name);

    Package* package                 = (Package*)malloc(sizeof(Package));

    package->compiler_entry          = compiler_entry;
    package->package_index           = -1; // TODO: 这个应该在 fix的时候 设置
    package->package_name            = package_name;
    package->package_path            = NULL;

    package->source_file_list        = std::vector<std::string>{std::string(input_main_file)};

    package->global_declaration_list = std::vector<Declaration*>{};
    package->class_definition_list   = std::vector<ClassDefinition*>{};
    package->function_list           = std::vector<Function*>{};

    package->package_unit_list       = std::vector<PackageUnit*>{};

    return package;
}

// 获取包下的所有 ring 源代码文件
// 依次生成 PackageUnit 进行编译
void package_compile(Package* package) {
    CompilerEntry* compiler_entry = package->compiler_entry;

    if (NULL != search_package(compiler_entry, package->package_name)) {
        debug_log_with_yellow_coloar("\t package[%s] already compiled", package->package_name);
        return;
    }
    debug_log_with_yellow_coloar("\t package[%s] start compile...", package->package_name);
    package->package_index = compiler_entry->package_list.size(); // TODO: 这个应该在 fix的时候 设置
    compiler_entry->package_list.push_back(package);

    for (std::string source_file : package->source_file_list) {
        PackageUnit* package_unit = package_unit_create(package, source_file.c_str());
        package_unit_compile(package_unit);

        // for (ImportPackageInfo* import_package_info : package_unit->import_package_list) {
        // // TODO:
        // char* package_name = import_package_info->package_name;
        // char* package_path = (char*)"/Users/zhenhuli/Desktop/Ring//"; // TODO:

        // if (NULL != search_package(compiler_entry, package_name)) {
        //     debug_log_with_yellow_coloar("\t package[%s] already compiled", package_name);
        //     continue;
        // }
        // Package* import_package       = package_create(compiler_entry, package_name, package_path);
        // import_package->package_index = compiler_entry->package_list.size(); // TODO: 这个应该在 fix的时候 设置
        // compiler_entry->package_list.push_back(import_package);
        // package_compile(import_package);
        //}

        package->package_unit_list.push_back(package_unit);
    }

    for (PackageUnit* package_unit : package->package_unit_list) {
        ring_compiler_fix_ast(package_unit);

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

    printf("|## package_name:%s,package_path:%s\n", package->package_name, package->package_path);

    printf("|## PackageUnit:\n");
    for (auto package_unit : package->package_unit_list) {
        printf("|\tfile_name:%s\n", package_unit->current_file_name.c_str());
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
        printf("|\tfunction function_name:%s\n", function->function_name);
    }

    printf("|------------------ Package-Dump-end  ------------------\n");
}

// create packge by a input source file
PackageUnit* package_unit_create(Package* parent_package, std::string file_name) {
    package_unit                                   = (PackageUnit*)malloc(sizeof(PackageUnit));

    package_unit->parent_package                   = parent_package;

    package_unit->current_file_name                = file_name;
    package_unit->current_file_fp                  = NULL;
    package_unit->current_line_number              = 1;
    package_unit->current_column_number            = 1;
    package_unit->current_line_content             = new_ring_string();

    package_unit->import_package_list              = std::vector<ImportPackageInfo*>{};

    package_unit->global_block_statement_list_size = 0;
    package_unit->global_block_statement_list      = NULL;
    package_unit->global_declaration_list          = std::vector<Declaration*>{};

    package_unit->class_definition_list            = std::vector<ClassDefinition*>{};

    package_unit->function_list                    = std::vector<Function*>{};

    package_unit->current_block                    = NULL;

    package_unit->compile_error_num                = 0;

    package_unit->current_file_fp                  = fopen(file_name.c_str(), "r");
    if (package_unit->current_file_fp == NULL) {
        fprintf(stderr, "%s not found.\n", file_name.c_str());
        exit(1);
    }

    return package_unit;
}

PackageUnit* get_package_unit() {
    return package_unit;
}

void package_unit_compile(PackageUnit* package_unit) {
    extern int   yyparse(void);
    extern FILE* yyin;

    yyin = package_unit->current_file_fp;
    if (yyparse()) {
        package_unit->compile_error_num++;
    }
    if (package_unit->compile_error_num) {
        complie_err_log("%d syntax error detected.\n", package_unit->compile_error_num);
        exit(ERROR_CODE_COMPILE_ERROR);
    }

    debug_log_with_yellow_coloar("\t package_unit COMPLIE SUCCESS\n\n");
}

void package_unit_dump(PackageUnit* package_unit) {
    printf("|------------------ PackageUnit-Dump-begin ------------------\n");

    printf("|## file_name:%s\n", package_unit->current_file_name.c_str());

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
        printf("|\tfunction function_name:%s\n", function->function_name);
    }

    printf("|------------------ PackageUnit-Dump-end  ------------------\n");
}


const char* package_unit_get_file_name() {
    assert(package_unit != NULL);
    return package_unit->current_file_name.c_str();
}

Ring_String* get_package_unit_current_line_content() {
    assert(package_unit != NULL);
    return package_unit->current_line_content;
}

unsigned int package_unit_get_line_number() {
    assert(package_unit != NULL);
    return package_unit->current_line_number;
}

unsigned int package_unit_increa_line_number() {
    assert(package_unit != NULL);
    package_unit->current_line_number++;
    return package_unit->current_line_number;
}

unsigned int package_unit_get_column_number() {
    assert(package_unit != NULL);
    return package_unit->current_column_number;
}

unsigned int package_unit_increa_column_number(unsigned int len) {
    assert(package_unit != NULL);
    package_unit->current_column_number += len;
    return package_unit->current_column_number;
}

void package_unit_update_line_content(char* str) {
    assert(package_unit != NULL);

    for (int i = 0; i < strlen(str); i++) {
        ring_string_add_char(package_unit->current_line_content, str[i]);
    }

    package_unit->current_column_number += strlen(str);
}

void package_unit_reset_line_content() {
    reset_ring_string(package_unit->current_line_content);
}

char* package_unit_get_current_line_content() {
    return get_ring_string(package_unit->current_line_content);
}

void package_unit_reset_column_number() {
    package_unit->current_column_number = 1;
}

int package_unit_add_class_definition(ClassDefinition* class_definition) {
    assert(package_unit != NULL);
    assert(class_definition != NULL);

    package_unit->class_definition_list.push_back(class_definition);
    return 0;
}
