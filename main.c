#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"

void compile(Ring_Interpreter *ring_interpreter, FILE *fp) {
    extern int   yyparse(void);
    extern FILE *yyin;

    yyin = fp;
    if (yyparse()) {
        /* BUGBUG */
        fprintf(stderr, "Error ! Error ! Error !\n");
        exit(1);
    }
}

void interpret(Ring_Interpreter *ring_interpreter) {
    Statement *p;
    for (p = ring_interpreter->statement_list; p != NULL; p = p->next) {
#ifdef DEBUG
        printf("[DEBUG][main.c][function:interpret]\t interpret statement: type(%d),line_number(%d)\n", p->type, p->line_number);
#endif
    }
}

int main(int argc, char **argv) {
    Ring_Interpreter *ring_interpreter;
    FILE *            fp;

    if (argc != 2) {
        fprintf(stderr, "usage:%s filename", argv[0]);
        exit(1);
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "%s not found.\n", argv[1]);
        exit(1);
    }

    ring_interpreter = new_ring_interpreter();
    compile(ring_interpreter, fp);
    interpret(ring_interpreter);

    return 0;
}