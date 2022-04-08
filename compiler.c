#include "inner_func.h"
#include "ring.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Ring_Compiler* ring_compiler = NULL;

Ring_Compiler* new_ring_compiler(char* file_name) {
    if (ring_compiler == NULL) {
        ring_compiler = malloc(sizeof(Ring_Compiler));
    }

    ring_compiler->current_file_name     = file_name;
    ring_compiler->current_line_number   = 1;
    ring_compiler->current_column_number = 1;
    ring_compiler->current_line_content  = new_ring_string();

    ring_compiler->statement_list_size = 0;
    ring_compiler->statement_list      = NULL;

    ring_compiler->function_list_size = 0;
    ring_compiler->function_list      = NULL;

    ring_compiler->variable_list_size = 0;
    ring_compiler->variable_list      = NULL;

    ring_compiler->identifier_list_size = 0;
    ring_compiler->identifier_list      = NULL;

    // ring_compiler_registe_inner_func();
    return ring_compiler;
}

Ring_Compiler* get_ring_compiler() {
    return ring_compiler;
}

// Step-1: flex 词法分析，
// Step-2: bison 语法分析，构建语法树
void ring_compiler_compile(Ring_Compiler* ring_compiler, FILE* fp) {
    extern int   yyparse(void);
    extern FILE* yyin;

    yyin = fp;
    if (yyparse()) {
        fprintf(stderr, "COMPLIE ERROR\n");
        exit(ERROR_CODE_COMPILE_ERROR);
    }

    debug_log_with_yellow_coloar("\t COMPLIE SUCCESS\n\n");
}


char* get_ring_compiler_current_file_name() {
    assert(ring_compiler != NULL);
    return ring_compiler->current_file_name;
}

Ring_String* get_ring_compiler_current_line_content() {
    assert(ring_compiler != NULL);
    return ring_compiler->current_line_content;
}

unsigned int get_ring_compiler_line_number() {
    assert(ring_compiler != NULL);
    return ring_compiler->current_line_number;
}

unsigned int increase_ring_compiler_line_number() {
    assert(ring_compiler != NULL);
    ring_compiler->current_line_number++;
    return ring_compiler->current_line_number;
}

unsigned int get_ring_compiler_column_number() {
    assert(ring_compiler != NULL);
    return ring_compiler->current_column_number;
}

unsigned int increase_ring_compiler_column_number(unsigned int len) {
    assert(ring_compiler != NULL);
    ring_compiler->current_column_number += len;
    return ring_compiler->current_column_number;
}

void ring_compiler_update_line_content(char* str) {
    assert(ring_compiler != NULL);

    for (int i = 0; i < strlen(str); i++) {
        ring_string_add_char(ring_compiler->current_line_content, str[i]);
    }

    ring_compiler->current_column_number += strlen(str);
}

void ring_compiler_reset_current_line_content() {
    reset_ring_string(ring_compiler->current_line_content);
}

char* ring_compiler_get_current_line_content() {
    return get_ring_string(ring_compiler->current_line_content);
}

void reset_ring_compiler_column_number() {
    ring_compiler->current_column_number = 1;
}

int ring_compiler_init_statement_list(Statement* statement) {
    assert(ring_compiler != NULL);
    debug_log_with_yellow_coloar("statement->type:%d", statement->type);

    ring_compiler->statement_list      = statement;
    ring_compiler->statement_list_size = 1;

    return 0;
}

int ring_compiler_add_statement(Statement* statement) {
    assert(ring_compiler != NULL);

    if (ring_compiler->statement_list == NULL) {
        ring_compiler->statement_list      = statement;
        ring_compiler->statement_list_size = 1;
        return 0;
    }


    Statement* pos;
    pos = ring_compiler->statement_list;
    for (; pos->next != NULL; pos = pos->next) {
    }
    pos->next = statement;
    ring_compiler->statement_list_size++;
    return 0;
}

void ring_compiler_registe_inner_func() {
    register_inner_func(ring_compiler);
}
