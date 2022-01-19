#ifndef INTERPRETER_INCLUDE_H
#define interpreter_INCLUDE_H

#include "ring.h"

typedef struct {
    unsigned int line_number;

    unsigned int statement_list_size;
    Statement *  statement_list;

} Ring_Interpreter;

Ring_Interpreter *new_ring_interpreter();
Ring_Interpreter *get_ring_interpreter();
unsigned int      get_ring_interpreter_line_number();
unsigned int      increase_ring_interpreter_line_number();
int               ring_interpreter_init_statement_list(Statement *statement);
int               ring_interpreter_add_statement(Statement *statement);

#endif