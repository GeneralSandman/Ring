#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "ring.h"
#include "inner_func.h"

static Ring_Interpreter *ring_interpreter = NULL;

Ring_Interpreter *new_ring_interpreter(char *file_name) {
    if (ring_interpreter == NULL) {
        ring_interpreter = malloc(sizeof(Ring_Interpreter));
    }

    ring_interpreter->current_file_name     = file_name;
    ring_interpreter->current_line_number   = 1;
    ring_interpreter->current_column_number = 1;
    ring_interpreter->current_line_content  = new_ring_string();

    ring_interpreter->statement_list_size = 0;
    ring_interpreter->statement_list      = NULL;

    ring_interpreter->function_list_size = 0;
    ring_interpreter->function_list      = NULL;

    ring_interpreter->variable_list_size = 0;
    ring_interpreter->variable_list      = NULL;

    ring_interpreter->identifier_list_size = 0;
    ring_interpreter->identifier_list      = NULL;

    ring_interpreter_registe_inner_func();
    return ring_interpreter;
}

Ring_Interpreter *get_ring_interpreter() {
    return ring_interpreter;
}

char *get_ring_interpreter_current_file_name() {
    assert(ring_interpreter != NULL);
    return ring_interpreter->current_file_name;
}

char *get_ring_interpreter_current_line_content() {
    assert(ring_interpreter != NULL);
    return ring_interpreter->current_line_content;
}

unsigned int get_ring_interpreter_line_number() {
    if (ring_interpreter == NULL) {
        // TODO: asser();
        return 0;
    }
    return ring_interpreter->current_line_number;
}

unsigned int increase_ring_interpreter_line_number() {
    if (ring_interpreter == NULL) {
        // TODO: asser();
        return 0;
    }
    ring_interpreter->current_line_number++;
    return ring_interpreter->current_line_number;
}

unsigned int get_ring_interpreter_column_number() {
    assert(ring_interpreter != NULL);
    return ring_interpreter->current_column_number;
}

unsigned int increase_ring_interpreter_column_number(unsigned int len) {
    assert(ring_interpreter != NULL);
    ring_interpreter->current_column_number += len;
    return ring_interpreter->current_column_number;
}

void ring_interpreter_update_line_content(char *str) {
    assert(ring_interpreter != NULL);

    for (int i = 0; i < strlen(str); i++) {
        ring_string_add_char(ring_interpreter->current_line_content, str[i]);
    }

    ring_interpreter->current_column_number += strlen(str);
}

void ring_interpreter_reset_current_line_content() {
    reset_ring_string(ring_interpreter->current_line_content);
}

char *ring_interpreter_get_current_line_content() {
    return get_ring_string(ring_interpreter->current_line_content);
}

void reset_ring_interpreter_column_number() {
    ring_interpreter->current_column_number = 1;
}

int ring_interpreter_init_statement_list(Statement *statement) {
    assert(ring_interpreter != NULL);
    debug_log_with_yellow_coloar();

    ring_interpreter->statement_list      = statement;
    ring_interpreter->statement_list_size = 1;

    return 0;
}

int ring_interpreter_add_statement(Statement *statement) {
    assert(ring_interpreter != NULL);
    assert(ring_interpreter->statement_list != NULL);

    Statement *pos;
    pos = ring_interpreter->statement_list;
    for (; pos->next != NULL; pos = pos->next) {
    }
    pos->next = statement;
    ring_interpreter->statement_list_size++;
    return 0;
}

void ring_interpreter_registe_inner_func() {
    register_inner_func(ring_interpreter);
}
