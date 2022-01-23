%{
#include <stdio.h>
#include "ring.h"
#include "parser.h"
#define YYDEBUG 1

%}


%union {
    char *m_comment_value;

    char *m_literal_interface;
    char *m_identifier;

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
%token TOKEN_STRUCT 

%token TOKEN_TRUE
%token TOKEN_FALSE

%token TOKEN_VAR
%token TOKEN_CONST
%token TOKEN_FUNCTION

%token TOKEN_ADD
%token TOKEN_SUB
%token TOKEN_MUL
%token TOKEN_DIV

%token TOKEN_AND
%token TOKEN_OR
%token TOKEN_NOT

%token TOKEN_EQ
%token TOKEN_NE

%token TOKEN_GT
%token TOKEN_GE
%token TOKEN_LT
%token TOKEN_LE

%token TOKEN_LP 
%token TOKEN_RP 
%token TOKEN_COMMA 
%token TOKEN_SEMICOLON 
%token TOKEN_ASSIGN

%token INT_LITERAL
%token DOUBLE_LITERAL
%token STRING_LITERAL
%token IDENTIFIER

%type <m_literal_interface> literal_term INT_LITERAL DOUBLE_LITERAL STRING_LITERAL
%type <m_identifier> IDENTIFIER identifier
%type <m_statement_list> statement statement_list
%type <m_expression> expression 
%type <m_expression> expression_arithmetic_operation_additive 
%type <m_expression> expression_arithmetic_operation_multiplicative 
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
        printf("[DEBUG][ring.bison.y][RULE:expression-function_call_expression]\t\n");
        #endif

        $$ = create_expression_($1);
    }
    | assign_expression
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:expression-assign_expression]\t\n");
        #endif
        
        $$ = create_expression__($1);
    }
    | expression_arithmetic_operation_additive
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:expression-expression_arithmetic_operation_additive]\t\n");
        #endif

    }
    ;

expression_arithmetic_operation_additive
    : expression_arithmetic_operation_multiplicative 
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:expression_arithmetic_operation_additive]\t\n");
        #endif

    }
    | expression_arithmetic_operation_additive TOKEN_ADD expression_arithmetic_operation_multiplicative
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:expression_arithmetic_operation_additive]\t\n");
        #endif

        $$ = create_expression_binary(EXPRESSION_TYPE_ARITHMETIC_ADD, $1, $3);
    }
    | expression_arithmetic_operation_additive TOKEN_SUB expression_arithmetic_operation_multiplicative
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:expression_arithmetic_operation_additive]\t\n");
        #endif

        $$ = create_expression_binary(EXPRESSION_TYPE_ARITHMETIC_SUB, $1, $3);
    }
    ;

expression_arithmetic_operation_multiplicative
    : literal_term
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:expression_arithmetic_operation_multiplicative]\t\n");
        #endif

    }
    | expression_arithmetic_operation_multiplicative TOKEN_MUL literal_term
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:expression_arithmetic_operation_multiplicative]\t\n");
        #endif

        $$ = create_expression_binary(EXPRESSION_TYPE_ARITHMETIC_MUL, $1, $3);
    }
    | expression_arithmetic_operation_multiplicative TOKEN_DIV literal_term
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:expression_arithmetic_operation_multiplicative]\t\n");
        #endif

        $$ = create_expression_binary(EXPRESSION_TYPE_ARITHMETIC_DIV, $1, $3);
    }
    ;

literal_term
    : INT_LITERAL
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:literal_term-INT_LITERAL]\t\n");
        #endif

        $$ = create_expression_literal(EXPRESSION_TYPE_LITERAL_INT, $1);
    }
    | DOUBLE_LITERAL
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:literal_term-DOUBLE_LITERAL]\t\n");
        #endif

        $$ = create_expression_literal(EXPRESSION_TYPE_LITERAL_DOUBLE, $1);
    }
    | STRING_LITERAL
    {
        #ifdef DEBUG
        printf("[DEBUG][ring.bison.y][RULE:literal_term-STRING_LITERAL]\t\n");
        #endif

        $$ = create_expression_literal(EXPRESSION_TYPE_LITERAL_STRING, $1);
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
    : identifier TOKEN_ASSIGN expression
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



%%


int yyerror(char const *str){
    fprintf(stderr, "file:\t%s \n\
        \t line:%d column:%d \n\
        \t complie error:%s\n", 
        get_ring_interpreter_current_file_name(),
        get_ring_interpreter_line_number(), 
        get_ring_interpreter_column_number(), 
        str);
    
    return 0;
}

