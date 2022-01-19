%{
#include <stdio.h>
#include "ring.h"
#include "parser.h"
#define YYDEBUG 1

%}


%union {
    char *m_identifier;
    char *m_string_value;
    char *comment_value;

    StatementList *m_statement_list;
    Statement *m_statement;
    Expression *m_expression;
    FunctionCallExpression *m_function_call_expression;
    ArgumentList *m_argument_list;
}

%token TOKEN_STRING 
%token TOKEN_LP 
%token TOKEN_RP 
%token TOKEN_COMMA 
%token TOKEN_SEMICOLON 
%token TOKEN_ASSIGN

%token <m_string_value> STRING_LITERAL
%token <m_identifier> IDENTIFIER

%type <m_statement_list> statement_list
%type <m_statement> statement
%type <m_expression> expression
%type <m_function_call_expression> function_call_expression
%type <m_argument_list> argument_list


%%


statement_list
    : statement
    {

    }
    | statement_list statement
    {
        $$ = statement_list_add_item($1, $2);
    }
    ;

statement
    : expression TOKEN_SEMICOLON
    {

    }
    ;

expression
    : function_call_expression 
    {

    }
    ;

function_call_expression
    : identifier TOKEN_LP argument_list TOKEN_RP
    {
        // $$ = create_function_call_expression($1, $3);
        #ifdef DEBUG
        printf("[Complie SUCCESS] line[function call]\n\n");
        #endif
    }
    ;

argument_list
    : string_value 
    {
        #ifdef DEBUG
        printf("[DEBUG] create_argument_list\n");
        #endif
        $$ = create_argument_list($1);
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
        // $$ = (char*)($1->string_value);
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

