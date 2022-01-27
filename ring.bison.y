%{
#include <stdio.h>
#include "ring.h"
#include "parser.h"
#define YYDEBUG 1

int yylex();
int yyerror(char const *str);

%}


%union {
    char*                       m_comment_value;
    char*                       m_literal_interface;
    char*                       m_identifier;
    Statement*                  m_statement_list;
    Expression*                 m_expression;
    AssignExpression*           m_assign_expression;
    FunctionCallExpression*     m_function_call_expression;
    ArgumentList*               m_argument_list;
    Variable*                   m_variable;
    VariableType                m_variable_type;
    Function*                   m_function_definition;
}

%token TOKEN_INT 
%token TOKEN_DOUBLE 
%token TOKEN_STRING 
%token TOKEN_STRUCT 
%token TOKEN_BIND 
%token TOKEN_LAMBDA 

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
%token TOKEN_LC 
%token TOKEN_RC 
%token TOKEN_COMMA 
%token TOKEN_SEMICOLON 
%token TOKEN_ASSIGN

%token INT_LITERAL
%token DOUBLE_LITERAL
%token STRING_LITERAL
%token IDENTIFIER

%type <m_literal_interface> INT_LITERAL DOUBLE_LITERAL STRING_LITERAL
%type <m_identifier> identifier IDENTIFIER
%type <m_statement_list> statement statement_list
%type <m_expression> expression 
%type <m_expression> literal_term
%type <m_expression> expression_arithmetic_operation_additive 
%type <m_expression> expression_arithmetic_operation_multiplicative 
%type <m_assign_expression> assign_expression
%type <m_function_call_expression> function_call_expression
%type <m_argument_list> argument_list
%type <m_variable> variable_definition
%type <m_variable_type> variable_type
%type <m_function_definition> function_definition


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
    | function_definition
    {
        debug_log_with_green_coloar("[RULE::statement:function_definition]\t ", "");
        add_function_definition($1);
    }
    ;

statement
    : expression TOKEN_SEMICOLON
    {
        $$ = create_statemen_from_expression($1);
    }
    | variable_definition TOKEN_SEMICOLON
    {
        debug_log_with_green_coloar("[RULE::statement]\t ", "");

        $$ = create_statement_from_variable($1);
    }
    ;

variable_definition
    : TOKEN_VAR variable_type identifier
    {
        debug_log_with_green_coloar("[RULE::variable_definition]\t ", "");

        $$ = new_variable($2, $3);
    }
    ;

function_definition
    : TOKEN_FUNCTION identifier TOKEN_LP TOKEN_RP block
    {
        debug_log_with_green_coloar("[RULE::function_definition]\t ", "");

        $$ = new_function_definition(FUNCTION_TYPE_EXTERNAL, $2, NULL, NULL);

    }
    | TOKEN_FUNCTION identifier TOKEN_LP parameter_list TOKEN_RP block
    {
        debug_log_with_green_coloar("[RULE::function_definition]\t ", "");

    }
    ;

parameter_list
    :
    {
        debug_log_with_green_coloar("[RULE::parameter_list]\t ", "");

    }
    ;

return_list
    :
    {
        debug_log_with_green_coloar("[RULE::return_list]\t ", "");
    }
    ;

block
    : TOKEN_LC TOKEN_RC
    {
        debug_log_with_green_coloar("[RULE::block:block]\t ", "");
    }
    ;


variable_type
    : TOKEN_INT
    {
        debug_log_with_green_coloar("[RULE::variable_type]\t variable_type(TOKEN_INT) ", "");

        $$ = VARIABLE_TYPE_INT;
    }
    | TOKEN_DOUBLE
    {
        debug_log_with_green_coloar("[RULE::variable_type]\t variable_type(TOKEN_DOUBLE) ", "");

        $$ = VARIABLE_TYPE_DOUBLE;
    }
    | TOKEN_STRING
    {
        debug_log_with_green_coloar("[RULE::variable_type]\t variable_type(TOKEN_STRING) ", "");

        $$ = VARIABLE_TYPE_STRING;
    }
    ;


expression
    : function_call_expression 
    {
        debug_log_with_green_coloar("[RULE::expression:function_call_expression]\t ", "");

        $$ = create_expression_($1);
    }
    | assign_expression
    {
        debug_log_with_green_coloar("[RULE:expression-assign_expression]\t ", "");
        
        $$ = create_expression__($1);
    }
    | expression_arithmetic_operation_additive
    {
        debug_log_with_green_coloar("[RULE::expression:expression_arithmetic_operation_additive]\t ", "");

    }
    | identifier 
    {
        debug_log_with_green_coloar("[RULE::expression:identifier]\t ", "");

        $$ = create_expression_identifier($1);
    }
    ;

expression_arithmetic_operation_additive
    : expression_arithmetic_operation_multiplicative 
    {
        debug_log_with_green_coloar("[RULE::expression_arithmetic_operation_additive]\t ", "");

    }
    | expression_arithmetic_operation_additive TOKEN_ADD expression_arithmetic_operation_multiplicative
    {
        debug_log_with_green_coloar("[RULE::expression_arithmetic_operation_additive]\t ", "");

        $$ = create_expression_binary(EXPRESSION_TYPE_ARITHMETIC_ADD, $1, $3);
    }
    | expression_arithmetic_operation_additive TOKEN_SUB expression_arithmetic_operation_multiplicative
    {
        debug_log_with_green_coloar("[RULE::expression_arithmetic_operation_additive]\t ", "");

        $$ = create_expression_binary(EXPRESSION_TYPE_ARITHMETIC_SUB, $1, $3);
    }
    ;

expression_arithmetic_operation_multiplicative
    : literal_term
    {
        debug_log_with_green_coloar("[RULE::expression_arithmetic_operation_multiplicative]\t ", "");

    }
    | expression_arithmetic_operation_multiplicative TOKEN_MUL literal_term
    {
        debug_log_with_green_coloar("[RULE::expression_arithmetic_operation_multiplicative]\t ", "");

        $$ = create_expression_binary(EXPRESSION_TYPE_ARITHMETIC_MUL, $1, $3);
    }
    | expression_arithmetic_operation_multiplicative TOKEN_DIV literal_term
    {
        debug_log_with_green_coloar("[RULE::expression_arithmetic_operation_multiplicative]\t ", "");

        $$ = create_expression_binary(EXPRESSION_TYPE_ARITHMETIC_DIV, $1, $3);
    }
    ;

literal_term
    : INT_LITERAL
    {
        debug_log_with_green_coloar("[RULE::literal_term:INT_LITERAL]\t ", "");

        $$ = create_expression_literal(EXPRESSION_TYPE_LITERAL_INT, $1);
    }
    | DOUBLE_LITERAL
    {
        debug_log_with_green_coloar("[RULE::literal_term:DOUBLE_LITERAL]\t ", "");

        $$ = create_expression_literal(EXPRESSION_TYPE_LITERAL_DOUBLE, $1);
    }
    | STRING_LITERAL
    {
        debug_log_with_green_coloar("[RULE::literal_term:STRING_LITERAL]\t ", "");

        $$ = create_expression_literal(EXPRESSION_TYPE_LITERAL_STRING, $1);
    }
    ;

function_call_expression
    : identifier TOKEN_LP argument_list TOKEN_RP
    {
        debug_log_with_green_coloar("[RULE::function_call_expression]\t ", "");

        $$ = create_function_call_expression($1, $3);
    }
    ;

assign_expression
    : identifier TOKEN_ASSIGN expression
    {
        debug_log_with_green_coloar("[RULE::assign_expression]\t ", "");

        $$ = create_assign_expression($1, $3);
    }
    ;

identifier
    : IDENTIFIER
    {
        debug_log_with_green_coloar("[RULE::identifier]\t identifier(%s)", $1);

    }
    ;

argument_list
    : STRING_LITERAL 
    {
        debug_log_with_green_coloar("[RULE::argument_list:STRING_LITERAL]\t ", "");

        $$ = create_argument_list($1);
    }
    | expression
    {
        debug_log_with_green_coloar("[RULE::argument_list:expression]\t ", "");

        $$ = create_argument_list_from_expression($1);
    }
    ;



%%

extern char *yytext;

// TODO: 需要优化这个错误提示
int yyerror(char const *str){
    complie_err_log("file(%s) \n"
        "    line(%d) column(%d): \n"
        "    %s", 
        get_ring_interpreter_current_file_name(),
        get_ring_interpreter_line_number(), get_ring_interpreter_column_number(), 
        ring_interpreter_get_current_line_content());
    complie_err_log2("%*s^.....%s", get_ring_interpreter_column_number()+4, "", str);

    // printf("%s\n", yytext);

    // va_list ap;
    // va_start(ap, str);
    // if(yylloc.first_line) {

    // }
    
    return 0;
}

