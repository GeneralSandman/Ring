%{
#include <stdio.h>
#include "ring.h"
#include "y.tab.h"
#include "parser.h"

int yywrap(){
    return 1;
}

%}
%start COMMENT STRING_LITERAL_STATE
%%

<INITIAL>"string" return TOKEN_STRING;
<INITIAL>"("            return TOKEN_LP;
<INITIAL>")"            return TOKEN_RP;
<INITIAL>","            return TOKEN_COMMA;
<INITIAL>";" return TOKEN_SEMICOLON;
<INITIAL>"=" return TOKEN_ASSIGN;

<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
    #ifdef DEBUG
    printf("[DEBUG][ring.flex.l][STATUS:INITIAL]\tidentifier(%s)\n", yytext);
    #endif

    init_string_literal_buffer();

    int i = 0;
    for (i=0;i<strlen(yytext);i++) {
        string_literal_add_char(yytext[i]);
    }

    yylval.m_identifier = get_string_literal();
    reset_string_literal_buffer();
    return IDENTIFIER;
}

<INITIAL>\" {
    init_string_literal_buffer();
    BEGIN STRING_LITERAL_STATE;
}
<INITIAL>\n {
    #ifdef DEBUG
    printf("[DEBUG][ring.flex.l][STATUS:INITIAL]\tnew line(LF)\n");
    #endif

    increase_ring_interpreter_line_number();
}
<INITIAL>\r\n {
    #ifdef DEBUG
    printf("[DEBUG][ring.flex.l][STATUS:INITIAL]\tnew line(CRLF)\n");
    #endif

    increase_ring_interpreter_line_number();
}
<INITIAL>"//" BEGIN COMMENT;
<INITIAL>. {
}


<COMMENT>\n {
    yylval.m_comment_value = get_string_literal();
    reset_string_literal_buffer();

    #ifdef DEBUG
    printf("[DEBUG][ring.flex.l][STATUS:COMMENT]\tcomment(%s)\n", yylval.m_comment_value);
    #endif

    increase_ring_interpreter_line_number();
    BEGIN INITIAL;
}
<COMMENT>\r\n {
    yylval.m_comment_value = get_string_literal();
    reset_string_literal_buffer();

    #ifdef DEBUG
    printf("[DEBUG][ring.flex.l][STATUS:COMMENT]\tcomment(%s)\n", yylval.m_comment_value);
    #endif

    increase_ring_interpreter_line_number();
    BEGIN INITIAL;
}
<COMMENT>. {
    string_literal_add_char(yytext[0]);
};


<STRING_LITERAL_STATE>\" {
    BEGIN INITIAL;
    return STRING_LITERAL;
}
<STRING_LITERAL_STATE>. {
    string_literal_add_char(yytext[0]);
    yylval.m_string_value = get_string_literal();
    BEGIN STRING_LITERAL_STATE;
}

%%
