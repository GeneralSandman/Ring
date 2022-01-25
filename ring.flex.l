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

%option yylineno

%%



<INITIAL>"int"          { increase_ring_interpreter_column_number(yyleng); return TOKEN_INT;            }
<INITIAL>"double"       { increase_ring_interpreter_column_number(yyleng); return TOKEN_DOUBLE;         }
<INITIAL>"string"       { increase_ring_interpreter_column_number(yyleng); return TOKEN_STRING;         }
<INITIAL>"struct"       { increase_ring_interpreter_column_number(yyleng); return TOKEN_STRUCT;         }

<INITIAL>"true"         { increase_ring_interpreter_column_number(yyleng); return TOKEN_TRUE;           }
<INITIAL>"false"        { increase_ring_interpreter_column_number(yyleng); return TOKEN_FALSE;          }

<INITIAL>"var"          { increase_ring_interpreter_column_number(yyleng); return TOKEN_VAR;            }
<INITIAL>"const"        { increase_ring_interpreter_column_number(yyleng); return TOKEN_CONST;          }
<INITIAL>"function"     { increase_ring_interpreter_column_number(yyleng); return TOKEN_FUNCTION;       }

<INITIAL>"+"            { increase_ring_interpreter_column_number(yyleng); return TOKEN_ADD;            }
<INITIAL>"-"            { increase_ring_interpreter_column_number(yyleng); return TOKEN_SUB;            }
<INITIAL>"*"            { increase_ring_interpreter_column_number(yyleng); return TOKEN_MUL;            }
<INITIAL>"/"            { increase_ring_interpreter_column_number(yyleng); return TOKEN_DIV;            }

<INITIAL>"and"          { increase_ring_interpreter_column_number(yyleng); return TOKEN_AND;            }
<INITIAL>"or"           { increase_ring_interpreter_column_number(yyleng); return TOKEN_OR;             }
<INITIAL>"not"          { increase_ring_interpreter_column_number(yyleng); return TOKEN_NOT;            }

<INITIAL>"=="           { increase_ring_interpreter_column_number(yyleng); return TOKEN_EQ;             }
<INITIAL>"!="           { increase_ring_interpreter_column_number(yyleng); return TOKEN_NE;             }

<INITIAL>">"            { increase_ring_interpreter_column_number(yyleng); return TOKEN_GT;             }
<INITIAL>">="           { increase_ring_interpreter_column_number(yyleng); return TOKEN_GE;             }
<INITIAL>"<"            { increase_ring_interpreter_column_number(yyleng); return TOKEN_LT;             }
<INITIAL>"<="           { increase_ring_interpreter_column_number(yyleng); return TOKEN_LE;             }

<INITIAL>"("            { increase_ring_interpreter_column_number(yyleng); return TOKEN_LP;             }
<INITIAL>")"            { increase_ring_interpreter_column_number(yyleng); return TOKEN_RP;             }
<INITIAL>","            { increase_ring_interpreter_column_number(yyleng); return TOKEN_COMMA;          }
<INITIAL>";"            { increase_ring_interpreter_column_number(yyleng); return TOKEN_SEMICOLON;      }
<INITIAL>"="            { increase_ring_interpreter_column_number(yyleng); return TOKEN_ASSIGN;         }

<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
    debug_log_with_red_coloar("[STATUS:INITIAL]\t line_num(%d),column_num(%d),identifier(%s)",
        get_ring_interpreter_line_number(), 
        get_ring_interpreter_column_number(), 
        yytext);

    increase_ring_interpreter_column_number(yyleng);

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

    increase_ring_interpreter_column_number(yyleng);
    yylval.m_literal_interface = yytext;

    return INT_LITERAL;
}
<INITIAL>[0-9]+\.[0-9]+ {
    debug_log_with_red_coloar("[STATUS:INITIAL]\t line_num(%d),column_num(%d),double_literal(%s)",
        get_ring_interpreter_line_number(), 
        get_ring_interpreter_column_number(), 
        yytext);

    increase_ring_interpreter_column_number(yyleng);
    yylval.m_literal_interface = yytext;

    return DOUBLE_LITERAL;
}

<INITIAL>\" {
    increase_ring_interpreter_column_number(yyleng);

    init_string_literal_buffer();
    BEGIN STRING_LITERAL_STATE;
}
<INITIAL>\n {
    debug_log_with_red_coloar("[STATUS:INITIAL]\t new line(LF)\n\n");

    reset_ring_interpreter_column_number();
    increase_ring_interpreter_line_number();
}
<INITIAL>\r\n {
    debug_log_with_red_coloar("[STATUS:INITIAL]\t new line(CRLF)\n\n");

    reset_ring_interpreter_column_number();
    increase_ring_interpreter_line_number();
}
<INITIAL>"//" BEGIN COMMENT;
<INITIAL>. {
    increase_ring_interpreter_column_number(yyleng);
}


<COMMENT>\n {
    yylval.m_comment_value = get_string_literal();
    reset_string_literal_buffer();

    debug_log_with_red_coloar("[STATUS:COMMENT]\t new comment(%s)", yylval.m_comment_value);

    reset_ring_interpreter_column_number();
    increase_ring_interpreter_line_number();
    BEGIN INITIAL;
}
<COMMENT>\r\n {
    yylval.m_comment_value = get_string_literal();
    reset_string_literal_buffer();

    debug_log_with_red_coloar("[STATUS:COMMENT]\t new comment(%s)", yylval.m_comment_value);

    reset_ring_interpreter_column_number();
    increase_ring_interpreter_line_number();
    BEGIN INITIAL;
}
<COMMENT>. {
    string_literal_add_char(yytext[0]);
};


<STRING_LITERAL_STATE>\" {
    increase_ring_interpreter_column_number(yyleng);

    yylval.m_literal_interface = get_string_literal();


    BEGIN INITIAL;
    return STRING_LITERAL;
}
<STRING_LITERAL_STATE>\\n {
    increase_ring_interpreter_column_number(yyleng);

    string_literal_add_char('\n');

    BEGIN STRING_LITERAL_STATE;
}
<STRING_LITERAL_STATE>\\r {
    increase_ring_interpreter_column_number(yyleng);

    string_literal_add_char('\r');

    BEGIN STRING_LITERAL_STATE;
}
<STRING_LITERAL_STATE>\\t {
    increase_ring_interpreter_column_number(yyleng);

    string_literal_add_char('\t');

    BEGIN STRING_LITERAL_STATE;
}
<STRING_LITERAL_STATE>. {
    increase_ring_interpreter_column_number(yyleng);

    string_literal_add_char(yytext[0]);

    BEGIN STRING_LITERAL_STATE;
}

%%
