%{
#include <stdio.h>
#include "ring.h"
#define YYDEBUG 1

%}

%union {
    char *identifier;
    char *string_value;
}

%token TOKEN_STRING 
%token TOKEN_SEMICOLON 
%token TOKEN_ASSIGN
%token <string_value> STRING_LITERAL
%token <identifier> IDENTIFIER

%type <statement> statement

%%
statement
    : TOKEN_STRING identifier TOKEN_ASSIGN string_value TOKEN_SEMICOLON
    {
        printf("complie success\n");
    }
    ;

identifier
    : IDENTIFIER
    {
        printf("identifier: %s\n", $1);
    }
    ;

string_value
    : STRING_LITERAL
    {
        printf("string_value: %s\n", $1);
    }
    ;

%%

int yyerror(char const *str){
    fprintf(stderr, "complie error:%s\n", str);
    return 0;
}

