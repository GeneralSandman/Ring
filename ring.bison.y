%{
#include <stdio.h>
#include "ring.h"
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
    Variable*                   m_parameter_list;
}

%token TOKEN_BOOL
%token TOKEN_INT 
%token TOKEN_DOUBLE 
%token TOKEN_STRING 
%token TOKEN_STRUCT 
%token TOKEN_BIND 
%token TOKEN_LAMBDA 
%token TOKEN_RETURN

%token TOKEN_CLASS
%token TOKEN_PRIVATE
%token TOKEN_PUBLIC
%token TOKEN_THIS

%token TOKEN_GLOBAL
%token TOKEN_IF
%token TOKEN_ELSEIF
%token TOKEN_ELSE
%token TOKEN_BREAK
%token TOKEN_CONTINUE
%token TOKEN_NULL

%token TOKEN_TRUE
%token TOKEN_FALSE

%token TOKEN_VAR
%token TOKEN_AUTO
%token TOKEN_CONST
%token TOKEN_FUNCTION
%token TOKEN_DOT

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
%token TOKEN_LB 
%token TOKEN_RB 
%token TOKEN_COMMA 
%token TOKEN_COLON
%token TOKEN_SEMICOLON 
%token TOKEN_ASSIGN

%token INT_LITERAL
%token DOUBLE_LITERAL
%token STRING_LITERAL
%token IDENTIFIER

%type <m_literal_interface> INT_LITERAL DOUBLE_LITERAL STRING_LITERAL TOKEN_TRUE TOKEN_FALSE
%type <m_identifier> identifier IDENTIFIER
%type <m_statement_list> statement statement_list block
%type <m_expression> expression
%type <m_expression> literal_term
%type <m_expression> expression_arithmetic_operation_additive 
%type <m_expression> expression_arithmetic_operation_multiplicative 
%type <m_expression> logical_expression_or
%type <m_expression> logical_expression_and
%type <m_expression> relational_expression
%type <m_expression> equality_expression
%type <m_assign_expression> assign_expression
%type <m_function_call_expression> function_call_expression
%type <m_argument_list> argument_list argument
%type <m_variable> variable_definition
%type <m_variable_type> variable_type
%type <m_function_definition> function_definition
%type <m_parameter_list> parameter_list


%%

translation_unit
    : definition_or_statement
    {
        debug_log_with_green_coloar("[RULE::translation_unit:definition_or_statement]\t ", "");
    }
    | translation_unit definition_or_statement
    {
        debug_log_with_green_coloar("[RULE::translation_unit:translation_unit]\t ", "");
    }
    ;

definition_or_statement
    : function_definition
    {
        debug_log_with_green_coloar("[RULE::statement:function_definition]\t ", "");
        add_function_definition($1);
    }
    | statement
    {
        debug_log_with_green_coloar("[RULE::statement:statement]\t ", "");
        ring_interpreter_add_statement($1);
    }
    ;

statement_list
    : statement
    {
        debug_log_with_green_coloar("[RULE::statement:statement]\t ", "");
        // $$ = statement_list_add_item2($1);
    }
    | statement_list statement
    {
        // 这个地方不应该加在全局的 statment_list 中
        // 应该只放到函数的 statement_list 中
        debug_log_with_green_coloar("[RULE::statement:statement_list]\t ", "");
        $$ = statement_list_add_item3($1, $2);
    }
    ;

statement
    : expression TOKEN_SEMICOLON
    {
        debug_log_with_green_coloar("[RULE::statement:expression]\t ", "");

        $$ = create_statemen_from_expression($1);
    }
    | variable_definition TOKEN_SEMICOLON
    {
        debug_log_with_green_coloar("[RULE::statement]\t ", "");

        $$ = create_statement_from_variable($1);
    }
    | TOKEN_RETURN expression TOKEN_SEMICOLON
    {
        debug_log_with_green_coloar("[RULE::statement:return_statement]\t ", "");
        $$ = create_return_statement($2);
    }
    | TOKEN_RETURN TOKEN_SEMICOLON
    {
        debug_log_with_green_coloar("[RULE::statement:return_statement]\t ", "");
        $$ = create_return_statement(NULL);
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

        $$ = new_function_definition(FUNCTION_TYPE_EXTERNAL, $2, NULL, $5);

    }
    | TOKEN_FUNCTION identifier TOKEN_LP parameter_list TOKEN_RP block
    {
        debug_log_with_green_coloar("[RULE::function_definition]\t ", "");

        $$ = new_function_definition(FUNCTION_TYPE_EXTERNAL, $2, $4, $6);

    }
    | TOKEN_FUNCTION identifier TOKEN_LP TOKEN_RP TOKEN_LP return_list TOKEN_RP block
    {
        debug_log_with_green_coloar("[RULE::function_definition]\t ", "");

        $$ = new_function_definition(FUNCTION_TYPE_EXTERNAL, $2, NULL, $8);

    }
    | TOKEN_FUNCTION identifier TOKEN_LP parameter_list TOKEN_RP TOKEN_LP return_list TOKEN_RP block
    {
        debug_log_with_green_coloar("[RULE::function_definition]\t ", "");

        $$ = new_function_definition(FUNCTION_TYPE_EXTERNAL, $2, $4, $9);

    }
    ;

parameter_list
    : variable_definition
    {
        debug_log_with_green_coloar("[RULE::parameter_list]\t ", "");

    }
    | parameter_list TOKEN_COMMA variable_definition 
    {
        debug_log_with_green_coloar("[RULE::parameter_list:parameter_list]\t ", "");
        $$ = variable_list_add_item($1, $3);

    }
    ;

return_list
    : variable_type
    {
        debug_log_with_green_coloar("[RULE::return_list]\t ", "");
    }
    ;

block
    : TOKEN_LC statement_list TOKEN_RC
    {
        debug_log_with_green_coloar("[RULE::block: statment_list]\t ", "");
        // TODO: 这里不要直接赋值，要扫描statment_list 把变量加到当前变量列表中
        $$ = $2;
    }
    | TOKEN_LC TOKEN_RC
    {
        debug_log_with_green_coloar("[RULE::block: empty statement_list]\t ", "");
    }
    ;


variable_type
    : TOKEN_BOOL
    {
        debug_log_with_green_coloar("[RULE::variable_type]\t variable_type(TOKEN_BOOL) ", "");

        $$ = VARIABLE_TYPE_BOOL;
    }
    | TOKEN_INT
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
    | logical_expression_or
    {
        debug_log_with_green_coloar("[RULE::expression:logical_expression]\t ", "");

    }
    ;

logical_expression_or
    : logical_expression_and
    {
        debug_log_with_green_coloar("[RULE::logical_expression_or]\t ", "");
        // $$ = create_expression_binary(EXPRESSION_TYPE_LOGICAL_AND, $1, $3);

    }
    | logical_expression_or TOKEN_OR logical_expression_and
    {
        debug_log_with_green_coloar("[RULE::logical_expression_or]\t ", "");
        $$ = create_expression_binary(EXPRESSION_TYPE_LOGICAL_OR, $1, $3);

    }
    ;

logical_expression_and
    : equality_expression
    {
        debug_log_with_green_coloar("[RULE::logical_expression_and]\t ", "");
        // $$ = create_expression_binary(EXPRESSION_TYPE_LOGICAL_OR, $1, $3);

    }
    | logical_expression_and TOKEN_AND equality_expression
    {
        debug_log_with_green_coloar("[RULE::logical_expression_and]\t ", "");
        $$ = create_expression_binary(EXPRESSION_TYPE_LOGICAL_AND, $1, $3);
        
    }
    ;

equality_expression
        : relational_expression
        | equality_expression TOKEN_EQ relational_expression
        {
            debug_log_with_green_coloar("[RULE::equality_expression]\t ", "");
            $$ = create_expression_binary(EXPRESSION_TYPE_RELATIONAL_EQ, $1, $3);
        }
        | equality_expression TOKEN_NE relational_expression
        {
            debug_log_with_green_coloar("[RULE::equality_expression]\t ", "");
            $$ = create_expression_binary(EXPRESSION_TYPE_RELATIONAL_NE, $1, $3);
        }
        ;

relational_expression
    : expression_arithmetic_operation_additive
    {
        debug_log_with_green_coloar("[RULE::relational_expression]\t ", "");

    }
    | relational_expression TOKEN_GT expression_arithmetic_operation_additive
    {
        debug_log_with_green_coloar("[RULE::relational_expression]\t ", "");
        $$ = create_expression_binary(EXPRESSION_TYPE_RELATIONAL_GT, $1, $3);

    }
    | relational_expression TOKEN_GE expression_arithmetic_operation_additive
    {
        debug_log_with_green_coloar("[RULE::relational_expression]\t ", "");
        $$ = create_expression_binary(EXPRESSION_TYPE_RELATIONAL_GE, $1, $3);

    }
    | relational_expression TOKEN_LT expression_arithmetic_operation_additive
    {
        debug_log_with_green_coloar("[RULE::relational_expression]\t ", "");
        $$ = create_expression_binary(EXPRESSION_TYPE_RELATIONAL_LT, $1, $3);

    }
    | relational_expression TOKEN_LE expression_arithmetic_operation_additive
    {
        debug_log_with_green_coloar("[RULE::relational_expression]\t ", "");
        $$ = create_expression_binary(EXPRESSION_TYPE_RELATIONAL_LE, $1, $3);

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
    : TOKEN_NOT literal_term
    {
        debug_log_with_green_coloar("[RULE::literal_term:TOKEN_SUB]\t ", "");

        // $$ = create_expression_unitary(EXPRESSION_TYPE_ARITHMETIC_DIV, $1, $3);
    }
    | INT_LITERAL
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
    | TOKEN_TRUE
    {
        debug_log_with_green_coloar("[RULE::literal_term:TOKEN_TRUE]\t ", "");

        $$ = create_expression_bool_literal(EXPRESSION_TYPE_LITERAL_BOOL, BOOL_TRUE);
    }
    | TOKEN_FALSE
    {
        debug_log_with_green_coloar("[RULE::literal_term:TOKEN_FALSE]\t ", "");

        $$ = create_expression_bool_literal(EXPRESSION_TYPE_LITERAL_BOOL, BOOL_FALSE);
    }
    | identifier
    {
        debug_log_with_green_coloar("[RULE::literal_term:identifier]\t ", "");
        $$ = create_expression_identifier($1);
    }
    ;

function_call_expression
    : identifier TOKEN_LP argument_list TOKEN_RP
    {
        debug_log_with_green_coloar("[RULE::function_call_expression]\t ", "");

        $$ = create_function_call_expression($1, $3);
    }
    | identifier TOKEN_LP TOKEN_RP
    {
        debug_log_with_green_coloar("[RULE::function_call_expression]\t ", "");

        $$ = create_function_call_expression($1, NULL);
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
    : argument 
    {

    }
    | argument_list TOKEN_COMMA argument
    {
        $$ = argument_list_add_item3($1, $3);

    }
    ;


argument
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

