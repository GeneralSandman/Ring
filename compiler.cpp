#include "inner_func.h"
#include "ring.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

int                      yyerror(char const* str, ...);
extern struct SyntaxInfo SyntaxInfos[];
static PackageUnit*      package_unit = NULL;

// Error Attention 某些错误提示可以精细化识别、提示
void ring_compiler_error(SyntaxType syntax_type, int need_exit) {
    std::string message = "syntax error:\nRing Grammar Standard:\n\t" + std::string(SyntaxInfos[SYNTAX_VARIABLE_DEFINITION].bnf);
    yyerror(message.c_str());
    package_unit->compile_error_num++;
    if (need_exit) {
        // Donot exit when detect a error.
        // Get next line and compile.
        exit(ERROR_CODE_COMPILE_ERROR);
    }
}

Package* package_create(char* package_name, char* package_path) {
    Package* package = (Package*)malloc(sizeof(Package));

    package->package_name = package_name;
    package->package_path = package_path;

    package->declaration_list      = std::vector<Declaration*>{};
    package->class_definition_list = std::vector<ClassDefinition*>{};
    package->function_list         = std::vector<Function*>{};

    package->package_unit_list = std::vector<PackageUnit*>{};

    return package;
}

// 获取包下的所有 ring 源代码文件
// 依次生成 PackageUnit 进行编译
void package_compile(Package* package) {
    std::vector<std::string> source_file_list = list_file(package->package_path);

    for (std::string source_file : source_file_list) {
        PackageUnit* package_unit = package_unit_create(source_file.c_str());
        package_unit_compile(package_unit);

        // for (ImportPackageInfo* import_package_info : package_unit->import_package_list) {
        //     // TODO:
        //     // add
        // }

        package->package_unit_list.push_back(package_unit);
    }

    for (PackageUnit* package_unit : package->package_unit_list) {
        for (int d_i = 0; d_i < package_unit->declaration_list_size; d_i++) {
            package->declaration_list.push_back(&package_unit->declaration_list[d_i]);
        }

        for (ClassDefinition* pos : package_unit->class_definition_list) {
            package->class_definition_list.push_back(pos);
        }

        for (Function* pos : package_unit->function_list) {
            package->function_list.push_back(pos);
        }
    }
}

void package_dump(Package* package) {
    printf("******************* Package-Dump-begin *******************\n");
    printf("package_name:%s,package_path:%s\n", package->package_name, package->package_path);

    printf("PackageUnit:\n");
    for (auto package_unit : package->package_unit_list) {
        printf("\tfile_name:%s\n", package_unit->current_file_name.c_str());
    }

    printf("Declaration:\n");
    for (auto declaration : package->declaration_list) {
        printf("\tdeclaration identifier:%s\n", declaration->identifier);
    }

    printf("ClassDefinition:\n");
    for (auto class_definition : package->class_definition_list) {
        printf("\tclass_definition identifier:%s\n", class_definition->class_identifier);
    }

    printf("Function:\n");
    for (auto function : package->function_list) {
        printf("\tfunction function_name:%s\n", function->function_name);
    }
    printf("******************* Package-Dump-end  *******************\n");
}


PackageUnit* package_unit_create(std::string file_name) {
    package_unit = (PackageUnit*)malloc(sizeof(PackageUnit));

    package_unit->parent_package = NULL;

    package_unit->current_file_name     = file_name;
    package_unit->current_file_fp       = NULL;
    package_unit->current_line_number   = 1;
    package_unit->current_column_number = 1;
    package_unit->current_line_content  = new_ring_string();

    package_unit->import_package_list = std::vector<ImportPackageInfo*>{};

    package_unit->declaration_list_size = 0;
    package_unit->declaration_list      = NULL;

    package_unit->class_definition_list = std::vector<ClassDefinition*>{};

    package_unit->function_list = std::vector<Function*>{};

    package_unit->current_block = NULL;

    package_unit->compile_error_num = 0;

    package_unit->current_file_fp = fopen(file_name.c_str(), "r");
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

    debug_log_with_yellow_coloar("\t compile_unit COMPLIE SUCCESS\n\n");
}

void package_unit_dump(PackageUnit* package_unit) {
    printf("******************* PackageUnit-Dump-begin *******************\n");
    printf("tfile_name:%s\n", package_unit->current_file_name.c_str());

    // printf("PackageUnit:\n");
    // for (auto package_unit : package->package_unit_list) {
    //     printf("\tfile_name:%s\n", package_unit->current_file_name.c_str());
    // }

    // printf("Declaration:\n");
    // for (auto declaration : package->declaration_list) {
    //     printf("\tdeclaration identifier:%s\n", declaration->identifier);
    // }

    // printf("ClassDefinition:\n");
    // for (auto class_definition : package->class_definition_list) {
    //     printf("\tclass_definition identifier:%s\n", class_definition->class_identifier);
    // }

    // printf("Function:\n");
    // for (auto function : package->function_list) {
    //     printf("\tfunction function_name:%s\n", function->function_name);
    // }
    printf("******************* PackageUnit-Dump-end  *******************\n");
}


const char* get_package_unit_current_file_name() {
    assert(package_unit != NULL);
    return package_unit->current_file_name.c_str();
}

Ring_String* get_package_unit_current_line_content() {
    assert(package_unit != NULL);
    return package_unit->current_line_content;
}

unsigned int get_package_unit_line_number() {
    assert(package_unit != NULL);
    return package_unit->current_line_number;
}

unsigned int increase_package_unit_line_number() {
    assert(package_unit != NULL);
    package_unit->current_line_number++;
    return package_unit->current_line_number;
}

unsigned int get_package_unit_column_number() {
    assert(package_unit != NULL);
    return package_unit->current_column_number;
}

unsigned int increase_package_unit_column_number(unsigned int len) {
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

void package_unit_reset_current_line_content() {
    reset_ring_string(package_unit->current_line_content);
}

char* package_unit_get_current_line_content() {
    return get_ring_string(package_unit->current_line_content);
}

void reset_package_unit_column_number() {
    package_unit->current_column_number = 1;
}

int package_unit_add_statement(Statement* statement) {
    assert(package_unit != NULL);

    if (package_unit->statement_list == NULL) {
        package_unit->statement_list      = statement;
        package_unit->statement_list_size = 1;
        return 0;
    }


    Statement* pos;
    pos = package_unit->statement_list;
    for (; pos->next != NULL; pos = pos->next) {
    }
    pos->next = statement;
    package_unit->statement_list_size++;
    return 0;
}

int package_unit_add_class_definition(ClassDefinition* class_definition) {
    assert(package_unit != NULL);
    assert(class_definition != NULL);

    package_unit->class_definition_list.push_back(class_definition);
    return 0;
}
