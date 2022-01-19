%{
#include <stdio.h>
#include "ring.h"
#include "parser.h"
#define YYDEBUG 1

%}


%union {
    char *m_identifier;
    char *m_string_value;
    char *m_comment_value;

    Statement *m_statement_list;
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
%token STRING_LITERAL
%token IDENTIFIER

%type <m_string_value> STRING_LITERAL
%type <m_identifier> IDENTIFIER identifier
%type <m_statement_list> statement statement_list
%type <m_expression> expression
%type <m_function_call_expression> function_call_expression
%type <m_argument_list> argument_list


%%


statement_list
    : statement
    {
        create_statement_list($1);
    }
    | statement_list statement
    {
        statement_list_add_item($2);
    }
    ;

statement
    : expression TOKEN_SEMICOLON
    {
        $$ = create_statemen($1);
    }
    ;

expression
    : function_call_expression 
    {
        $$ = create_expression_($1);
    }
    ;

function_call_expression
    : identifier TOKEN_LP argument_list TOKEN_RP
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:function_call_expression]\t\n");
        #endif

        $$ = create_function_call_expression($1, $3);
    }
    ;

identifier
    : IDENTIFIER
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:identifier]\tidentifier(%s)\n", $1);
        #endif
    }
    ;

argument_list
    : STRING_LITERAL 
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:argument_list]\t\n");
        #endif

        $$ = create_argument_list($1);
    }
    ;


string_value
    : STRING_LITERAL
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:string_value] string_value(%s)\n", $1);
        #endif
    }
    ;


%%


int yyerror(char const *str){
    fprintf(stderr, "complie error:%s\n", str);
    return 0;
}

