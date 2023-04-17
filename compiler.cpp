#include "inner_func.h"
#include "ring.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int                      yyerror(char const* str, ...);
extern struct SyntaxInfo SyntaxInfos[];
static PackageUnit*    package_unit = NULL;

// Error Attention 某些错误提示可以精细化识别、提示
void ring_compiler_error(SyntaxType syntax_type, int need_exit) {
    char message[1024];
    sprintf(message, "syntax error:\nRing Grammar Standard:\n\t%s", SyntaxInfos[SYNTAX_VARIABLE_DEFINITION].bnf);
    yyerror(message);
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

    package->declaration_list_size = 0;
    package->declaration_list = NULL;

    package->class_definition_list_size = 0;
    package->class_definition_list = NULL;

    package->function_list_size = 0;
    package->function_list = NULL;

    package->package_unit_size = 0;
    package->package_unit_list = NULL;

    return package;
}

// 获取包下的所有 ring 源代码文件
// 依次生成 PackageUnit 进行编译
void package_compile(Package* package) {
    /*
    for(int i=0; i<package->package_unit_size; i++) {
        PackageUnit* package_unit = package_unit_create();
        package_unit_compile(package_unit);

        for(int j=0; j<package_unit->import_package_size; j++) {
            Package* new_package = package_create();

            if(-1 == compiler_entry_add_package(compiler_entry, new_package)) {
                continue;
            }
            package_compile(new_package);
        }
    }
    */
}



PackageUnit* package_unit_create(char* file_name) {
    package_unit = (PackageUnit*)malloc(sizeof(PackageUnit));

    package_unit->parent_package     = NULL;
    
    package_unit->current_file_name     = file_name;
    package_unit->current_file_fp       = NULL;
    package_unit->current_line_number   = 1;
    package_unit->current_column_number = 1;
    package_unit->current_line_content  = new_ring_string();

    package_unit->import_package_size = 0;
    package_unit->import_package_list = NULL;

    package_unit->declaration_list_size = 0;
    package_unit->declaration_list      = NULL;

    package_unit->class_definition_list_size = 0;
    package_unit->class_definition_list      = NULL;

    package_unit->function_list_size = 0;
    package_unit->function_list      = NULL;

    package_unit->current_block = NULL;

    package_unit->compile_error_num = 0;

    package_unit->current_file_fp   = fopen(file_name, "r");
    if (package_unit->current_file_fp == NULL) {
        fprintf(stderr, "%s not found.\n", file_name);
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


char* get_package_unit_current_file_name() {
    assert(package_unit != NULL);
    return package_unit->current_file_name;
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

    if (package_unit->class_definition_list == NULL) {
        package_unit->class_definition_list      = class_definition;
        package_unit->class_definition_list_size = 1;
        return 0;
    }

    ClassDefinition* pos = package_unit->class_definition_list;
    for (; pos->next != NULL; pos = pos->next) {
    }
    pos->next = class_definition;
    package_unit->class_definition_list_size++;
    return 0;
}
