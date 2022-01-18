%{
#include <stdio.h>
#include "ring.h"
#define YYDEBUG 1

%}

%union {
    char *identifier;
    char *string_value;
    char *comment_value;
}

%token TOKEN_STRING 
%token TOKEN_LP 
%token TOKEN_RP 
%token TOKEN_COMMA 
%token TOKEN_SEMICOLON 
%token TOKEN_ASSIGN
%token <string_value> STRING_LITERAL
%token <identifier> IDENTIFIER

%type <statement_list> statement_list
%type <statement> statement
%type <argument_list> argument_list

%%

statement_list
    : statement
    {

    }
    | statement_list statement
    {
        
    }
    ;

statement
    : TOKEN_STRING identifier TOKEN_ASSIGN string_value TOKEN_SEMICOLON
    {
        #ifdef DEBUG
        printf("[Complie SUCCESS] line[variable definition]\n\n");
        #endif
    }
    | identifier TOKEN_LP argument_list TOKEN_RP TOKEN_SEMICOLON
    {
        #ifdef DEBUG
        printf("[Complie SUCCESS] line[function call]\n\n");
        #endif
    }
    ;

argument_list
    : string_value 
    | argument_list TOKEN_COMMA string_value
    {
    }
    ;


identifier
    : IDENTIFIER
    {
        #ifdef DEBUG
        printf("[union]identifier: %s\n", $1);
        #endif
    }
    ;

string_value
    : STRING_LITERAL
    {
        #ifdef DEBUG
        printf("[union]string_value: %s\n", $1);
        #endif
    }
    ;

%%

int yyerror(char const *str){
    fprintf(stderr, "complie error:%s\n", str);
    return 0;
}

