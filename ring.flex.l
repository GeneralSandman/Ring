%{
#include <stdio.h>
#include "ring.h"
#include "y.tab.h"

int yywrap(){
    return 1;
}

%}
%start COMMENT STRING_LITERAL_STATE

%option yylineno

%%



<INITIAL>"int"          { ring_interpreter_update_line_content(yytext); return TOKEN_INT;            }
<INITIAL>"double"       { ring_interpreter_update_line_content(yytext); return TOKEN_DOUBLE;         }
<INITIAL>"string"       { ring_interpreter_update_line_content(yytext); return TOKEN_STRING;         }
<INITIAL>"struct"       { ring_interpreter_update_line_content(yytext); return TOKEN_STRUCT;         }
<INITIAL>"bind"         { ring_interpreter_update_line_content(yytext); return TOKEN_BIND;           }
<INITIAL>"lambda"       { ring_interpreter_update_line_content(yytext); return TOKEN_LAMBDA;         }

<INITIAL>"true"         { ring_interpreter_update_line_content(yytext); return TOKEN_TRUE;           }
<INITIAL>"false"        { ring_interpreter_update_line_content(yytext); return TOKEN_FALSE;          }

<INITIAL>"var"          { ring_interpreter_update_line_content(yytext); return TOKEN_VAR;            }
<INITIAL>"const"        { ring_interpreter_update_line_content(yytext); return TOKEN_CONST;          }
<INITIAL>"function"     { ring_interpreter_update_line_content(yytext); return TOKEN_FUNCTION;       }

<INITIAL>"+"            { ring_interpreter_update_line_content(yytext); return TOKEN_ADD;            }
<INITIAL>"-"            { ring_interpreter_update_line_content(yytext); return TOKEN_SUB;            }
<INITIAL>"*"            { ring_interpreter_update_line_content(yytext); return TOKEN_MUL;            }
<INITIAL>"/"            { ring_interpreter_update_line_content(yytext); return TOKEN_DIV;            }

<INITIAL>"and"          { ring_interpreter_update_line_content(yytext); return TOKEN_AND;            }
<INITIAL>"or"           { ring_interpreter_update_line_content(yytext); return TOKEN_OR;             }
<INITIAL>"not"          { ring_interpreter_update_line_content(yytext); return TOKEN_NOT;            }

<INITIAL>"=="           { ring_interpreter_update_line_content(yytext); return TOKEN_EQ;             }
<INITIAL>"!="           { ring_interpreter_update_line_content(yytext); return TOKEN_NE;             }

<INITIAL>">"            { ring_interpreter_update_line_content(yytext); return TOKEN_GT;             }
<INITIAL>">="           { ring_interpreter_update_line_content(yytext); return TOKEN_GE;             }
<INITIAL>"<"            { ring_interpreter_update_line_content(yytext); return TOKEN_LT;             }
<INITIAL>"<="           { ring_interpreter_update_line_content(yytext); return TOKEN_LE;             }

<INITIAL>"("            { ring_interpreter_update_line_content(yytext); return TOKEN_LP;             }
<INITIAL>")"            { ring_interpreter_update_line_content(yytext); return TOKEN_RP;             }
<INITIAL>"{"            { ring_interpreter_update_line_content(yytext); return TOKEN_LC;             }
<INITIAL>"}"            { ring_interpreter_update_line_content(yytext); return TOKEN_RC;             }
<INITIAL>","            { ring_interpreter_update_line_content(yytext); return TOKEN_COMMA;          }
<INITIAL>";"            { ring_interpreter_update_line_content(yytext); return TOKEN_SEMICOLON;      }
<INITIAL>"="            { ring_interpreter_update_line_content(yytext); return TOKEN_ASSIGN;         }

<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
    debug_log_with_red_coloar("[STATUS:INITIAL]\t line_num(%d),column_num(%d),identifier(%s)",
        get_ring_interpreter_line_number(), 
        get_ring_interpreter_column_number(), 
        yytext);

    ring_interpreter_update_line_content(yytext);

    init_string_literal_buffer();

    int i = 0;
    for (i=0;i<strlen(yytext);i++) {
        string_literal_add_char(yytext[i]);
    }

    yylval.m_identifier = get_string_literal();
    reset_string_literal_buffer();

    
    return IDENTIFIER;
}
<INITIAL>([1-9][0-9]*)|"0" {
    debug_log_with_red_coloar("[STATUS:INITIAL]\t line_num(%d),column_num(%d),int_literal(%s)",
        get_ring_interpreter_line_number(), 
        get_ring_interpreter_column_number(), 
        yytext);

    ring_interpreter_update_line_content(yytext);
    yylval.m_literal_interface = yytext;

    return INT_LITERAL;
}
<INITIAL>[0-9]+\.[0-9]+ {
    debug_log_with_red_coloar("[STATUS:INITIAL]\t line_num(%d),column_num(%d),double_literal(%s)",
        get_ring_interpreter_line_number(), 
        get_ring_interpreter_column_number(), 
        yytext);

    ring_interpreter_update_line_content(yytext);
    yylval.m_literal_interface = yytext;

    return DOUBLE_LITERAL;
}

<INITIAL>\" {
    ring_interpreter_update_line_content(yytext);

    init_string_literal_buffer();
    BEGIN STRING_LITERAL_STATE;
}
<INITIAL>\n {
    debug_log_with_red_coloar("[STATUS:INITIAL]\t new line(LF) line_number(%d)\n\n", get_ring_interpreter_line_number());

    reset_ring_interpreter_column_number();
    ring_interpreter_reset_current_line_content();
    increase_ring_interpreter_line_number();
}
<INITIAL>\r\n {
    debug_log_with_red_coloar("[STATUS:INITIAL]\t new line(CRLF) line_number(%d)\n\n", get_ring_interpreter_line_number());

    reset_ring_interpreter_column_number();
    ring_interpreter_reset_current_line_content();
    increase_ring_interpreter_line_number();
}
<INITIAL>"//" BEGIN COMMENT;
<INITIAL>. {
    ring_interpreter_update_line_content(yytext);
}


<COMMENT>\n {
    yylval.m_comment_value = get_string_literal();
    reset_string_literal_buffer();

    debug_log_with_red_coloar("[STATUS:COMMENT]\t new comment(%s) line_number(%d)", yylval.m_comment_value, get_ring_interpreter_line_number());

    reset_ring_interpreter_column_number();
    ring_interpreter_reset_current_line_content();
    increase_ring_interpreter_line_number();
    BEGIN INITIAL;
}
<COMMENT>\r\n {
    yylval.m_comment_value = get_string_literal();
    reset_string_literal_buffer();

    debug_log_with_red_coloar("[STATUS:COMMENT]\t new comment(%s) line_number(%d)", yylval.m_comment_value, get_ring_interpreter_line_number());

    reset_ring_interpreter_column_number();
    ring_interpreter_reset_current_line_content();
    increase_ring_interpreter_line_number();
    BEGIN INITIAL;
}
<COMMENT>. {
    string_literal_add_char(yytext[0]);
};


<STRING_LITERAL_STATE>\" {
    ring_interpreter_update_line_content(yytext);

    yylval.m_literal_interface = get_string_literal();


    BEGIN INITIAL;
    return STRING_LITERAL;
}
<STRING_LITERAL_STATE>\\n {
    ring_interpreter_update_line_content(yytext);

    string_literal_add_char('\n');

    BEGIN STRING_LITERAL_STATE;
}
<STRING_LITERAL_STATE>\\r {
    ring_interpreter_update_line_content(yytext);

    string_literal_add_char('\r');

    BEGIN STRING_LITERAL_STATE;
}
<STRING_LITERAL_STATE>\\t {
    ring_interpreter_update_line_content(yytext);

    string_literal_add_char('\t');

    BEGIN STRING_LITERAL_STATE;
}
<STRING_LITERAL_STATE>. {
    ring_interpreter_update_line_content(yytext);

    string_literal_add_char(yytext[0]);

    BEGIN STRING_LITERAL_STATE;
}

%%
