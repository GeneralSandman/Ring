#include <stdio.h>
#include <stdlib.h>

void complie(FILE *fp) {
    extern int yyparse(void);
    extern FILE *yyin;

    yyin = fp;
    if (yyparse()) {
        /* BUGBUG */
        fprintf(stderr, "Error ! Error ! Error !\n");
        exit(1);
    }
}

int main(int argc, char **argv) {
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "usage:%s filename", argv[0]);
        exit(1);
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "%s not found.\n", argv[1]);
        exit(1);
    }

    complie(fp);

    return 0;
}