#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "interpreter.h"

static Ring_Interpreter *ring_interpreter = NULL;

Ring_Interpreter *new_ring_interpreter() {
    if (ring_interpreter == NULL) {
        ring_interpreter = malloc(sizeof(Ring_Interpreter));
    }
    return ring_interpreter;
}

Ring_Interpreter *get_ring_interpreter() {
    return ring_interpreter;
}

unsigned int get_ring_interpreter_line_number() {
    if (ring_interpreter == NULL) {
        // TODO: asser();
        return 0;
    }
    return ring_interpreter->line_number;
}

unsigned int increase_ring_interpreter_line_number() {
    if (ring_interpreter == NULL) {
        // TODO: asser();
        return 0;
    }
    ring_interpreter->line_number++;
}

int ring_interpreter_init_statement_list(Statement *statement) {
    assert(ring_interpreter != NULL);

    ring_interpreter->statement_list      = statement;
    ring_interpreter->statement_list_size = 1;

    printf("%p\n", ring_interpreter->statement_list);
    return 0;
}

int ring_interpreter_add_statement(Statement *statement) {
    assert(ring_interpreter != NULL);
    assert(ring_interpreter->statement_list != NULL);
    printf("%p\n", ring_interpreter->statement_list);

    Statement *pos;
    pos = ring_interpreter->statement_list;
    // for (; pos->next != NULL; pos = pos->next) {
    // }
    pos->next = statement;
    ring_interpreter->statement_list_size++;
    return 0;
}