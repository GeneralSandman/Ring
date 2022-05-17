%{
#include <stdio.h>
#include "ring.h"
#define YYDEBUG 1

int yylex();
int yyerror(char const *str);

%}

%glr-parser     // 使用 GLR 解析
%expect 1       // TODO: legitimate 0 shift/reduce conflicts
%expect-rr 0    // legitimate 0 reduce/reduce conflicts

%union {
    char*                       m_comment_value;
    char*                       m_literal_interface;
    char*                       m_identifier; // TODO: 以后不用这个，用下边的
    Identifier*                 m_identifier_list;
    Statement*                  m_statement_list;
    Expression*                 m_expression;
    AssignExpression*           m_assign_expression;
    FunctionCallExpression*     m_function_call_expression;
    ArgumentList*               m_argument_list;
    Variable*                   m_variable;
    VariableType                m_variable_type;
    Function*                   m_function_definition;
    Variable*                   m_parameter_list;
    IfStatement*                m_if_statement;
    ElseIfStatement*            m_elseif_statement;
    ForStatement*               m_for_statement;
    DoForStatement*             m_dofor_statement;
    FunctionReturnList*         m_return_list;
    Block*                      m_block;

    TypeSpecifier*              m_type_specifier;
    Ring_BasicType              m_basic_type_specifier;
}

%token TOKEN_TYPEDEF
%token TOKEN_BOOL
%token TOKEN_INT 
%token TOKEN_DOUBLE 
%token TOKEN_STRING 
%token TOKEN_STRUCT 
%token TOKEN_BIND 
%token TOKEN_LAMBDA 
%token TOKEN_RETURN
%token TOKEN_DEFER

%token TOKEN_CLASS
%token TOKEN_PRIVATE
%token TOKEN_PUBLIC
%token TOKEN_SELF
%token TOKEN_ATTRIBUTE

%token TOKEN_GLOBAL
%token TOKEN_IF
%token TOKEN_ELSEIF
%token TOKEN_ELSE
%token TOKEN_FOR
%token TOKEN_DO
%token TOKEN_WHILE
%token TOKEN_BREAK
%token TOKEN_CONTINUE
%token TOKEN_NULL

%token TOKEN_TRUE
%token TOKEN_FALSE

%token TOKEN_VAR
%token TOKEN_AUTO
%token TOKEN_CONST
%token TOKEN_FUNCTION
%token TOKEN_NEW
%token TOKEN_DELETE
%token TOKEN_DOT
%token TOKEN_ARROW

%token TOKEN_ADD
%token TOKEN_SUB
%token TOKEN_MUL
%token TOKEN_DIV
%token TOKEN_MOD
%token TOKEN_INCREASE
%token TOKEN_DECREASE
%token TOKEN_ADD_ASSIGN
%token TOKEN_SUB_ASSIGN
%token TOKEN_MUL_ASSIGN
%token TOKEN_DIV_ASSIGN
%token TOKEN_MOD_ASSIGN

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
%token TOKEN_QUESTION_MARK
%token TOKEN_ASSIGN

%token INT_LITERAL
%token DOUBLE_LITERAL
%token STRING_LITERAL
%token IDENTIFIER

%type <m_literal_interface> INT_LITERAL DOUBLE_LITERAL STRING_LITERAL TOKEN_TRUE TOKEN_FALSE
%type <m_identifier> identifier IDENTIFIER
%type <m_identifier_list> identifier_list
%type <m_statement_list> statement statement_list
%type <m_statement_list> variable_definition_statement
%type <m_expression> expression expression_list
%type <m_expression> literal_term
%type <m_expression> expression_arithmetic_operation_additive 
%type <m_expression> expression_arithmetic_operation_multiplicative 
%type <m_expression> logical_expression_or
%type <m_expression> logical_expression_and
%type <m_expression> relational_expression
%type <m_expression> equality_expression
%type <m_expression> maybe_empty_expression
%type <m_assign_expression> assign_expression
%type <m_function_call_expression> function_call_expression
%type <m_argument_list> argument_list argument
%type <m_variable> variable_definition
%type <m_variable_type> variable_type
%type <m_function_definition> function_definition
%type <m_parameter_list> parameter_list
%type <m_if_statement> if_statement
%type <m_for_statement> for_statement
%type <m_dofor_statement> dofor_statement
%type <m_elseif_statement> elseif_statement_list
%type <m_elseif_statement> elseif_statement
%type <m_return_list> return_list
%type <m_block> block

%type <m_type_specifier>        type_specifier
%type <m_basic_type_specifier>  basic_type_specifier


%%

translation_unit
    : definition_or_statement
    {
        debug_log_with_green_coloar("[RULE::translation_unit:definition_or_statement]\t ");
    }
    | translation_unit definition_or_statement
    {
        debug_log_with_green_coloar("[RULE::translation_unit:translation_unit]\t ");
    }
    ;

definition_or_statement
    : function_definition
    {
        debug_log_with_green_coloar("[RULE::statement:function_definition]\t ");
        add_function_definition($1);
    }
    | statement
    {
        debug_log_with_green_coloar("[RULE::statement:statement]\t ");
        ring_compiler_add_statement($1);
    }
    ;

statement_list
    : statement
    {
        debug_log_with_green_coloar("[RULE::statement:statement]\t ");
        // $$ = statement_list_add_item2($1);
    }
    | statement_list statement
    {
        // 这个地方不应该加在全局的 statment_list 中
        // 应该只放到函数的 statement_list 中
        debug_log_with_green_coloar("[RULE::statement:statement_list]\t ");
        $$ = statement_list_add_item3($1, $2);
    }
    ;

maybe_empty_expression
    :
    {
        $$ = NULL;
    }
    | expression
    | assign_expression
    {
        debug_log_with_green_coloar("[RULE:expression-assign_expression]\t ");
        
        $$ = create_expression__($1);
    }
    ;

statement
    : maybe_empty_expression TOKEN_SEMICOLON
    {
        debug_log_with_green_coloar("[RULE::statement:expression]\t ");

        $$ = create_statemen_from_expression($1);
    }
    | variable_definition_statement TOKEN_SEMICOLON
    | TOKEN_RETURN expression_list TOKEN_SEMICOLON
    {
        debug_log_with_green_coloar("[RULE::statement:return_statement]\t ");
        $$ = create_return_statement($2);
    }
    | TOKEN_RETURN TOKEN_SEMICOLON
    {
        debug_log_with_green_coloar("[RULE::statement:return_statement]\t ");
        $$ = create_return_statement(NULL);
    }
    | if_statement
    {
        debug_log_with_green_coloar("[RULE::statement:if_statement]\t ");
        $$ = create_statement_from_if($1);
    }
    | for_statement
    {
        debug_log_with_green_coloar("[RULE::statement:for_statement]\t ");
        $$ = create_statement_from_for($1);
    }
    | dofor_statement TOKEN_SEMICOLON
    {
        debug_log_with_green_coloar("[RULE::statement:dofor_statement]\t ");
        $$ = create_statement_from_dofor($1);
    }
    | break_statement TOKEN_SEMICOLON
    {
        $$ = create_statement_from_break();

    }
    | continue_statement TOKEN_SEMICOLON
    {
        $$ = create_statement_from_continue();

    }
    ;

if_statement
    : TOKEN_IF TOKEN_LP expression TOKEN_RP block // if () {}
    {
        debug_log_with_green_coloar("[RULE::if_statement]\t ");
        $$ = create_if_statement($3, $5, NULL, NULL);
    }
    | TOKEN_IF TOKEN_LP expression TOKEN_RP block TOKEN_ELSE block // if () {} else {}
    {
        debug_log_with_green_coloar("[RULE::if_statement]\t ");
        $$ = create_if_statement($3, $5, NULL, $7);
    }
    | TOKEN_IF TOKEN_LP expression TOKEN_RP block elseif_statement_list // if () {} elseif() {} elseif {}
    {
        debug_log_with_green_coloar("[RULE::if_statement]\t ");
        $$ = create_if_statement($3, $5, $6, NULL);
    }
    | TOKEN_IF TOKEN_LP expression TOKEN_RP block elseif_statement_list TOKEN_ELSE block // if () {} elseif() {} elseif {} else {}
    {
        debug_log_with_green_coloar("[RULE::if_statement]\t ");
        $$ = create_if_statement($3, $5, $6, $8);
    }
    ;

elseif_statement_list
    : elseif_statement
    {
        debug_log_with_green_coloar("[RULE::elseif_list_statement]\t ");
    }
    | elseif_statement_list elseif_statement
    {
        debug_log_with_green_coloar("[RULE::elseif_list_statement]\t ");
        $$ = elseif_statement_add_item($1, $2);
    }
    ;

elseif_statement
    : TOKEN_ELSEIF TOKEN_LP expression TOKEN_RP block // elseif () {}
    {
        debug_log_with_green_coloar("[RULE::if_statement]\t ");
        $$ = create_elseif_statement($3, $5);
    }
    ;

for_statement
    : TOKEN_FOR TOKEN_LP maybe_empty_expression TOKEN_SEMICOLON maybe_empty_expression TOKEN_SEMICOLON maybe_empty_expression TOKEN_RP block
    {
        debug_log_with_green_coloar("[RULE::for_statement]\t ");
        $$ = create_for_statement($3, $5, $7, $9);

    }
    ;

dofor_statement
    : TOKEN_DO TOKEN_LP maybe_empty_expression TOKEN_RP block TOKEN_FOR TOKEN_LP maybe_empty_expression TOKEN_SEMICOLON maybe_empty_expression TOKEN_RP
    {
        debug_log_with_green_coloar("[RULE::for_statement]\t ");
        $$ = create_dofor_statement($3, $5, $8, $10);
    }
    ;


break_statement
    : TOKEN_BREAK ;

continue_statement
    : TOKEN_CONTINUE ;


variable_definition_statement
    : TOKEN_VAR type_specifier IDENTIFIER
    {
        debug_log_with_green_coloar("[RULE::variable_definition_statement]\t ");
        $$ = create_declaration_statement($2, $3, NULL);
    }
    | TOKEN_VAR type_specifier IDENTIFIER TOKEN_ASSIGN expression
    {
        debug_log_with_green_coloar("[RULE::variable_definition_statement]\t ");
        $$ = create_declaration_statement($2, $3, $5);
    }
    ;

// TODO: 以后删除调
variable_definition
    : TOKEN_VAR variable_type identifier
    {
        debug_log_with_green_coloar("[RULE::variable_definition]\t ");

        $$ = new_variable($2, $3, NULL, 0);
    }
    | TOKEN_VAR variable_type TOKEN_LB literal_term TOKEN_RB identifier
    {
        debug_log_with_green_coloar("[RULE::variable_definition]\t ");

        $$ = new_variable_array($2, $4, $6, NULL, 0);

    }
    ;


function_definition
    : TOKEN_FUNCTION identifier TOKEN_LP TOKEN_RP block
    {
        debug_log_with_green_coloar("[RULE::function_definition]\t ");

        $$ = new_function_definition(FUNCTION_TYPE_DERIVE, $2, NULL, NULL, $5);

    }
    | TOKEN_FUNCTION identifier TOKEN_LP TOKEN_RP TOKEN_SEMICOLON
    {
        debug_log_with_green_coloar("[RULE::function_definition]\t ");

        $$ = new_function_definition(FUNCTION_TYPE_DERIVE, $2, NULL, NULL, NULL);

    }
    | TOKEN_FUNCTION identifier TOKEN_LP parameter_list TOKEN_RP block
    {
        debug_log_with_green_coloar("[RULE::function_definition]\t ");

        $$ = new_function_definition(FUNCTION_TYPE_DERIVE, $2, $4, NULL, $6);

    }
    | TOKEN_FUNCTION identifier TOKEN_LP parameter_list TOKEN_RP TOKEN_SEMICOLON
    {
        debug_log_with_green_coloar("[RULE::function_definition]\t ");

        $$ = new_function_definition(FUNCTION_TYPE_DERIVE, $2, $4, NULL, NULL);

    }
    | TOKEN_FUNCTION identifier TOKEN_LP TOKEN_RP TOKEN_ARROW TOKEN_LP return_list TOKEN_RP block
    {
        debug_log_with_green_coloar("[RULE::function_definition]\t ");

        $$ = new_function_definition(FUNCTION_TYPE_DERIVE, $2, NULL, $7, $9);

    }
    | TOKEN_FUNCTION identifier TOKEN_LP parameter_list TOKEN_RP TOKEN_ARROW TOKEN_LP return_list TOKEN_RP block
    {
        debug_log_with_green_coloar("[RULE::function_definition]\t ");

        $$ = new_function_definition(FUNCTION_TYPE_DERIVE, $2, $4, $8, $10);

    }
    ;

parameter_list
    : variable_definition
    {
        debug_log_with_green_coloar("[RULE::parameter_list]\t ");

    }
    | parameter_list TOKEN_COMMA variable_definition 
    {
        debug_log_with_green_coloar("[RULE::parameter_list:parameter_list]\t ");
        $$ = variable_list_add_item($1, $3);

    }
    ;

return_list
    : variable_type
    {
        $$ = create_function_return_list($1);
    }
    | return_list TOKEN_COMMA variable_type
    {
        $$ = function_return_list_add_item($1, $3);
    }
    ;

block
    : TOKEN_LC { $<m_block>$ = start_new_block(); } statement_list TOKEN_RC
    {
        debug_log_with_green_coloar("[RULE::block: statment_list]\t ");
        $<m_block>$ = finish_block($<m_block>2, $3);
    }
    | TOKEN_LC TOKEN_RC
    {
        debug_log_with_green_coloar("[RULE::block: empty statement_list]\t ");
        $$ = finish_block(start_new_block(), NULL);
    }
    ;


variable_type
    : TOKEN_BOOL
    {
        debug_log_with_green_coloar("[RULE::variable_type]\t variable_type(TOKEN_BOOL) ");

        $$ = VARIABLE_TYPE_BOOL;
    }
    | TOKEN_INT
    {
        debug_log_with_green_coloar("[RULE::variable_type]\t variable_type(TOKEN_INT) ");

        $$ = VARIABLE_TYPE_INT;
    }
    | TOKEN_DOUBLE
    {
        debug_log_with_green_coloar("[RULE::variable_type]\t variable_type(TOKEN_DOUBLE) ");

        $$ = VARIABLE_TYPE_DOUBLE;
    }
    | TOKEN_STRING
    {
        debug_log_with_green_coloar("[RULE::variable_type]\t variable_type(TOKEN_STRING) ");

        $$ = VARIABLE_TYPE_STRING;
    }
    ;

type_specifier
    : basic_type_specifier
    {
        debug_log_with_green_coloar("[RULE::type_specifier]");
        $$ = create_type_specifier($1);
    }
    ;

basic_type_specifier
    : TOKEN_BOOL
    {
        debug_log_with_green_coloar("[RULE::basic_type_specifier]\t variable_type(TOKEN_BOOL) ");
        $$ = RING_BASIC_TYPE_BOOL;
    }
    | TOKEN_INT
    {
        debug_log_with_green_coloar("[RULE::basic_type_specifier]\t variable_type(TOKEN_INT) ");
        $$ = RING_BASIC_TYPE_INT;
    }
    | TOKEN_DOUBLE
    {
        debug_log_with_green_coloar("[RULE::basic_type_specifier]\t variable_type(TOKEN_DOUBLE) ");
        $$ = RING_BASIC_TYPE_DOUBLE;
    }
    | TOKEN_STRING
    {
        debug_log_with_green_coloar("[RULE::basic_type_specifier]\t variable_type(TOKEN_STRING) ");
        $$ = RING_BASIC_TYPE_STRING;
    }
    ;

expression
    : function_call_expression 
    {
        debug_log_with_green_coloar("[RULE::expression:function_call_expression]\t ");

        $$ = create_expression_($1);
    }
    | logical_expression_or
    {
        debug_log_with_green_coloar("[RULE::expression:logical_expression]\t ");

    }
    | expression TOKEN_QUESTION_MARK expression TOKEN_COLON expression
    {
        debug_log_with_green_coloar("[RULE::expression ? : ]\t ");
        $$ = create_expression_ternary($1, $3, $5);
    }
    ;

logical_expression_or
    : logical_expression_and
    {
        debug_log_with_green_coloar("[RULE::logical_expression_or]\t ");
        // $$ = create_expression_binary(EXPRESSION_TYPE_LOGICAL_AND, $1, $3);

    }
    | logical_expression_or TOKEN_OR logical_expression_and
    {
        debug_log_with_green_coloar("[RULE::logical_expression_or]\t ");
        $$ = create_expression_binary(EXPRESSION_TYPE_LOGICAL_OR, $1, $3);

    }
    ;

logical_expression_and
    : equality_expression
    {
        debug_log_with_green_coloar("[RULE::logical_expression_and]\t ");
        // $$ = create_expression_binary(EXPRESSION_TYPE_LOGICAL_OR, $1, $3);

    }
    | logical_expression_and TOKEN_AND equality_expression
    {
        debug_log_with_green_coloar("[RULE::logical_expression_and]\t ");
        $$ = create_expression_binary(EXPRESSION_TYPE_LOGICAL_AND, $1, $3);
        
    }
    ;

equality_expression
        : relational_expression
        | equality_expression TOKEN_EQ relational_expression
        {
            debug_log_with_green_coloar("[RULE::equality_expression]\t ");
            $$ = create_expression_binary(EXPRESSION_TYPE_RELATIONAL_EQ, $1, $3);
        }
        | equality_expression TOKEN_NE relational_expression
        {
            debug_log_with_green_coloar("[RULE::equality_expression]\t ");
            $$ = create_expression_binary(EXPRESSION_TYPE_RELATIONAL_NE, $1, $3);
        }
        ;

relational_expression
    : expression_arithmetic_operation_additive
    {
        debug_log_with_green_coloar("[RULE::relational_expression]\t ");

    }
    | relational_expression TOKEN_GT expression_arithmetic_operation_additive
    {
        debug_log_with_green_coloar("[RULE::relational_expression]\t ");
        $$ = create_expression_binary(EXPRESSION_TYPE_RELATIONAL_GT, $1, $3);

    }
    | relational_expression TOKEN_GE expression_arithmetic_operation_additive
    {
        debug_log_with_green_coloar("[RULE::relational_expression]\t ");
        $$ = create_expression_binary(EXPRESSION_TYPE_RELATIONAL_GE, $1, $3);

    }
    | relational_expression TOKEN_LT expression_arithmetic_operation_additive
    {
        debug_log_with_green_coloar("[RULE::relational_expression]\t ");
        $$ = create_expression_binary(EXPRESSION_TYPE_RELATIONAL_LT, $1, $3);

    }
    | relational_expression TOKEN_LE expression_arithmetic_operation_additive
    {
        debug_log_with_green_coloar("[RULE::relational_expression]\t ");
        $$ = create_expression_binary(EXPRESSION_TYPE_RELATIONAL_LE, $1, $3);

    }
    ;

expression_arithmetic_operation_additive
    : expression_arithmetic_operation_multiplicative 
    {
        debug_log_with_green_coloar("[RULE::expression_arithmetic_operation_additive]\t ");

    }
    | expression_arithmetic_operation_additive TOKEN_ADD expression_arithmetic_operation_multiplicative
    {
        debug_log_with_green_coloar("[RULE::expression_arithmetic_operation_additive]\t ");

        $$ = create_expression_binary(EXPRESSION_TYPE_ARITHMETIC_ADD, $1, $3);
    }
    | expression_arithmetic_operation_additive TOKEN_SUB expression_arithmetic_operation_multiplicative
    {
        debug_log_with_green_coloar("[RULE::expression_arithmetic_operation_additive]\t ");

        $$ = create_expression_binary(EXPRESSION_TYPE_ARITHMETIC_SUB, $1, $3);
    }
    ;

expression_arithmetic_operation_multiplicative
    : literal_term
    {
        debug_log_with_green_coloar("[RULE::expression_arithmetic_operation_multiplicative]\t ");

    }
    | expression_arithmetic_operation_multiplicative TOKEN_MUL literal_term
    {
        debug_log_with_green_coloar("[RULE::expression_arithmetic_operation_multiplicative]\t ");

        $$ = create_expression_binary(EXPRESSION_TYPE_ARITHMETIC_MUL, $1, $3);
    }
    | expression_arithmetic_operation_multiplicative TOKEN_DIV literal_term
    {
        debug_log_with_green_coloar("[RULE::expression_arithmetic_operation_multiplicative]\t ");

        $$ = create_expression_binary(EXPRESSION_TYPE_ARITHMETIC_DIV, $1, $3);
    }
    | expression_arithmetic_operation_multiplicative TOKEN_MOD literal_term
    {
        debug_log_with_green_coloar("[RULE::expression_arithmetic_operation_multiplicative]\t ");

        $$ = create_expression_binary(EXPRESSION_TYPE_ARITHMETIC_MOD, $1, $3);
    }
    ;

literal_term
    : variable_type TOKEN_LP literal_term TOKEN_RP
    {
        debug_log_with_green_coloar("[RULE::literal_term:convert_type]\t ");
        $$ = create_expression_unitary_with_convert_type($1, $3);
    }
    | TOKEN_NOT literal_term
    {
        debug_log_with_green_coloar("[RULE::literal_term:TOKEN_NOT]\t ");

        $$ = create_expression_unitary(EXPRESSION_TYPE_LOGICAL_UNITARY_NOT, $2);
    }
    | TOKEN_SUB literal_term
    {
        debug_log_with_green_coloar("[RULE::literal_term:TOKEN_SUB]\t ");

        $$ = create_expression_unitary(EXPRESSION_TYPE_ARITHMETIC_UNITARY_MINUS, $2);
    }
    | INT_LITERAL
    {
        debug_log_with_green_coloar("[RULE::literal_term:INT_LITERAL]\t ");

        $$ = create_expression_literal(EXPRESSION_TYPE_LITERAL_INT, $1);
    }
    | DOUBLE_LITERAL
    {
        debug_log_with_green_coloar("[RULE::literal_term:DOUBLE_LITERAL]\t ");

        $$ = create_expression_literal(EXPRESSION_TYPE_LITERAL_DOUBLE, $1);
    }
    | STRING_LITERAL
    {
        debug_log_with_green_coloar("[RULE::literal_term:STRING_LITERAL]\t ");

        $$ = create_expression_literal(EXPRESSION_TYPE_LITERAL_STRING, $1);
    }
    | TOKEN_TRUE
    {
        debug_log_with_green_coloar("[RULE::literal_term:TOKEN_TRUE]\t ");

        $$ = create_expression_bool_literal(EXPRESSION_TYPE_LITERAL_BOOL, BOOL_TRUE);
    }
    | TOKEN_FALSE
    {
        debug_log_with_green_coloar("[RULE::literal_term:TOKEN_FALSE]\t ");

        $$ = create_expression_bool_literal(EXPRESSION_TYPE_LITERAL_BOOL, BOOL_FALSE);
    }
    | identifier
    {
        debug_log_with_green_coloar("[RULE::literal_term:identifier]\t ");
        $$ = create_expression_identifier($1);
    }
    | identifier TOKEN_INCREASE
    {
        debug_log_with_green_coloar("[RULE::literal_term:TOKEN_INCREASE]\t ");
        $$ = create_expression_unitary(EXPRESSION_TYPE_UNITARY_INCREASE_SUFFIX, create_expression_identifier($1));
    }
    | TOKEN_INCREASE identifier
    {
        debug_log_with_green_coloar("[RULE::literal_term:TOKEN_INCREASE]\t ");
        $$ = create_expression_unitary(EXPRESSION_TYPE_UNITARY_INCREASE_PREFIX, create_expression_identifier($2));
    }
    | identifier TOKEN_DECREASE
    {
        debug_log_with_green_coloar("[RULE::literal_term:TOKEN_INCREASE]\t ");
        $$ = create_expression_unitary(EXPRESSION_TYPE_UNITARY_DECREASE_SUFFIX, create_expression_identifier($1));
    }
    | TOKEN_DECREASE identifier
    {
        debug_log_with_green_coloar("[RULE::literal_term:TOKEN_INCREASE]\t ");
        $$ = create_expression_unitary(EXPRESSION_TYPE_UNITARY_DECREASE_PREFIX, create_expression_identifier($2));
    }
    | identifier TOKEN_LB expression TOKEN_RB
    {
        $$ = create_expression_identifier_with_index($1, $3);

    }
    ;

function_call_expression
    : identifier TOKEN_LP argument_list TOKEN_RP
    {
        debug_log_with_green_coloar("[RULE::function_call_expression]\t ");

        $$ = create_function_call_expression($1, $3);
    }
    | identifier TOKEN_LP TOKEN_RP
    {
        debug_log_with_green_coloar("[RULE::function_call_expression]\t ");

        $$ = create_function_call_expression($1, NULL);
    }
    ;

assign_expression
    : identifier TOKEN_ASSIGN expression
    {
        debug_log_with_green_coloar("[RULE::assign_expression]\t ");

        $$ = create_assign_expression(ASSIGN_EXPRESSION_TYPE_ASSIGN, create_expression_identifier($1), $3);
    }
    | identifier TOKEN_ADD_ASSIGN expression
    {
        debug_log_with_green_coloar("[RULE::assign_expression]\t ");

        $$ = create_assign_expression(ASSIGN_EXPRESSION_TYPE_ADD_ASSIGN, create_expression_identifier($1), $3);
    }
    | identifier TOKEN_SUB_ASSIGN expression
    {
        debug_log_with_green_coloar("[RULE::assign_expression]\t ");

        $$ = create_assign_expression(ASSIGN_EXPRESSION_TYPE_SUB_ASSIGN, create_expression_identifier($1), $3);
    }
    | identifier TOKEN_MUL_ASSIGN expression
    {
        debug_log_with_green_coloar("[RULE::assign_expression]\t ");

        $$ = create_assign_expression(ASSIGN_EXPRESSION_TYPE_MUL_ASSIGN, create_expression_identifier($1), $3);
    }
    | identifier TOKEN_DIV_ASSIGN expression
    {
        debug_log_with_green_coloar("[RULE::assign_expression]\t ");

        $$ = create_assign_expression(ASSIGN_EXPRESSION_TYPE_DIV_ASSIGN, create_expression_identifier($1), $3);
    }
    | identifier TOKEN_MOD_ASSIGN expression
    {
        debug_log_with_green_coloar("[RULE::assign_expression]\t ");

        $$ = create_assign_expression(ASSIGN_EXPRESSION_TYPE_MOD_ASSIGN, create_expression_identifier($1), $3);
    }
    | identifier TOKEN_COMMA identifier_list TOKEN_ASSIGN expression_list
    {
        debug_log_with_green_coloar("[RULE::assign_expression]\t ");
        $$ = create_multi_assign_expression($1, $3, NULL, $5);
    }
    | identifier TOKEN_LB expression TOKEN_RB TOKEN_ASSIGN expression
    {
        // $$ = create_multi_

    }
    ;

identifier_list
    : identifier
    {
        debug_log_with_green_coloar("[RULE::identifier_list]\t ");
        $$ = new_identifier(IDENTIFIER_TYPE_VARIABLE, $1);
    }
    | identifier_list TOKEN_COMMA identifier
    {
        debug_log_with_green_coloar("[RULE::identifier_list]\t ");
        $$ = identifier_list_add_item($1, new_identifier(IDENTIFIER_TYPE_VARIABLE, $3));
    }
    ;

expression_list
    : expression
    | expression_list TOKEN_COMMA expression
    {
        debug_log_with_green_coloar("[RULE::expression_list]\t ");
        $$ = expression_list_add_item($1, $3);
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
    : expression
    {
        debug_log_with_green_coloar("[RULE::argument_list:expression]\t ");

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
        get_ring_compiler_current_file_name(),
        get_ring_compiler_line_number(), get_ring_compiler_column_number(), 
        ring_compiler_get_current_line_content());
    complie_err_log2("%*s^.....%s", get_ring_compiler_column_number()+4, "", str);

    // printf("%s\n", yytext);

    // va_list ap;
    // va_start(ap, str);
    // if(yylloc.first_line) {

    // }
    
    return 0;
}

