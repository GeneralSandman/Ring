#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ring.h"

void ring_compile(Ring_Interpreter *ring_interpreter, FILE *fp);

int main(int argc, char **argv) {
    Ring_Interpreter *ring_interpreter;
    char *            file_name;
    FILE *            fp;

    if (argc != 2) {
        fprintf(stderr, "usage:%s <filename>", argv[0]);
        exit(1);
    }

    if (!strcmp(argv[1], "--version")) {
        printf("Ring version: %s \n", RING_VERSION);
        return 0;
    }

    file_name = argv[1];

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        fprintf(stderr, "%s not found.\n", argv[1]);
        exit(1);
    }

    ring_interpreter = new_ring_interpreter(file_name);
    ring_compile(ring_interpreter, fp);
    ring_interpret(ring_interpreter);

    return 0;
}

void ring_compile(Ring_Interpreter *ring_interpreter, FILE *fp) {
    extern int   yyparse(void);
    extern FILE *yyin;

    yyin = fp;
    if (yyparse()) {
        fprintf(stderr, "YYPARSE error\n");
        exit(1);
    }

    debug_log_with_yellow_coloar("\t COMPLIE SUCCESS\n\n", "");
}
