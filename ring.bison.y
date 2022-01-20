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
    AssignExpression *m_assign_expression;
    FunctionCallExpression *m_function_call_expression;
    ArgumentList *m_argument_list;
    Variable * m_variable;
    VariableType * m_variable_type;
}

%token TOKEN_INT 
%token TOKEN_DOUBLE 
%token TOKEN_STRING 

%token TOKEN_TRUE
%token TOKEN_FALSE

%token TOKEN_VAR
%token TOKEN_FUNCTION

%token TOKEN_ADD
%token TOKEN_SUB
%token TOKEN_MUL
%token TOKEN_DIV

%token TOKEN_AND
%token TOKEN_OR

%token TOKEN_LP 
%token TOKEN_RP 
%token TOKEN_COMMA 
%token TOKEN_SEMICOLON 
%token TOKEN_ASSIGN
%token STRING_LITERAL
%token IDENTIFIER

%type <m_string_value> STRING_LITERAL string_value
%type <m_identifier> IDENTIFIER identifier
%type <m_statement_list> statement statement_list
%type <m_expression> expression
%type <m_assign_expression> assign_expression
%type <m_function_call_expression> function_call_expression
%type <m_argument_list> argument_list
%type <m_variable> variable_definition
%type <m_variable_type> variable_type


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
        $$ = create_statemen_from_expression($1);
    }
    | variable_definition TOKEN_SEMICOLON
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:statement]\t \n");
        #endif

        $$ = create_statement_from_variable($1);
    }
    ;

variable_definition
    : TOKEN_VAR variable_type identifier
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:variable_definition]\t \n");
        #endif

        $$ = new_variable($2, $3);
    }
    ;

variable_type
    : TOKEN_INT
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:variable_type]\t variable_type(TOKEN_INT) \n");
        #endif

        $$ = VARIABLE_TYPE_INT;
    }
    | TOKEN_DOUBLE
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:variable_type]\t variable_type(TOKEN_DOUBLE) \n");
        #endif

        $$ = VARIABLE_TYPE_DOUBLE;
    }
    | TOKEN_STRING
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:variable_type]\t variable_type(TOKEN_STRING) \n");
        #endif

        $$ = VARIABLE_TYPE_STRING;
    }
    ;


expression
    : function_call_expression 
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:expression]\t\n");
        #endif

        $$ = create_expression_($1);
    }
    | assign_expression
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:expression]\t\n");
        #endif
        
        $$ = create_expression__($1);
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

assign_expression
    : identifier TOKEN_ASSIGN string_value
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:assign_expression]\t\n");
        #endif

        $$ = create_assign_expression($1, $3);
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

