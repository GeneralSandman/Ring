%{
#include <stdio.h>
#include "ring.h"
#include "y.tab.h"

int yywrap(){
    return 1;
}

%}
%start LINE_COMMENT BLOCK_COMMENT STRING_LITERAL_STATE

%option yylineno

%%



<INITIAL>"typedef"      { ring_compiler_update_line_content(yytext); return TOKEN_TYPEDEF;        }
<INITIAL>"bool"         { ring_compiler_update_line_content(yytext); return TOKEN_BOOL;           }
<INITIAL>"int"          { ring_compiler_update_line_content(yytext); return TOKEN_INT;            }
<INITIAL>"double"       { ring_compiler_update_line_content(yytext); return TOKEN_DOUBLE;         }
<INITIAL>"string"       { ring_compiler_update_line_content(yytext); return TOKEN_STRING;         }
<INITIAL>"struct"       { ring_compiler_update_line_content(yytext); return TOKEN_STRUCT;         }
<INITIAL>"bind"         { ring_compiler_update_line_content(yytext); return TOKEN_BIND;           }
<INITIAL>"lambda"       { ring_compiler_update_line_content(yytext); return TOKEN_LAMBDA;         }
<INITIAL>"return"       { ring_compiler_update_line_content(yytext); return TOKEN_RETURN;         }
<INITIAL>"defer"        { ring_compiler_update_line_content(yytext); return TOKEN_DEFER;          }

<INITIAL>"class"        { ring_compiler_update_line_content(yytext); return TOKEN_CLASS;          }
<INITIAL>"private"      { ring_compiler_update_line_content(yytext); return TOKEN_PRIVATE;        }
<INITIAL>"public"       { ring_compiler_update_line_content(yytext); return TOKEN_PUBLIC;         }
<INITIAL>"self"         { ring_compiler_update_line_content(yytext); return TOKEN_SELF;           }
<INITIAL>"@"            { ring_compiler_update_line_content(yytext); return TOKEN_ATTRIBUTE;      }

<INITIAL>"global"       { ring_compiler_update_line_content(yytext); return TOKEN_GLOBAL;         }
<INITIAL>"if"           { ring_compiler_update_line_content(yytext); return TOKEN_IF;             }
<INITIAL>"elseif"       { ring_compiler_update_line_content(yytext); return TOKEN_ELSEIF;         }
<INITIAL>"else"         { ring_compiler_update_line_content(yytext); return TOKEN_ELSE;           }
<INITIAL>"for"          { ring_compiler_update_line_content(yytext); return TOKEN_FOR;            }
<INITIAL>"do"           { ring_compiler_update_line_content(yytext); return TOKEN_DO;             }
<INITIAL>"while"        { ring_compiler_update_line_content(yytext); return TOKEN_WHILE;          }
<INITIAL>"break"        { ring_compiler_update_line_content(yytext); return TOKEN_BREAK;          }
<INITIAL>"continue"     { ring_compiler_update_line_content(yytext); return TOKEN_CONTINUE;       }
<INITIAL>"null"         { ring_compiler_update_line_content(yytext); return TOKEN_NULL;           }

<INITIAL>"true"         { ring_compiler_update_line_content(yytext); return TOKEN_TRUE;           }
<INITIAL>"false"        { ring_compiler_update_line_content(yytext); return TOKEN_FALSE;          }

<INITIAL>"var"          { ring_compiler_update_line_content(yytext); return TOKEN_VAR;            }
<INITIAL>"auto"         { ring_compiler_update_line_content(yytext); return TOKEN_AUTO;           }
<INITIAL>"const"        { ring_compiler_update_line_content(yytext); return TOKEN_CONST;          }
<INITIAL>"function"     { ring_compiler_update_line_content(yytext); return TOKEN_FUNCTION;       }
<INITIAL>"new"          { ring_compiler_update_line_content(yytext); return TOKEN_NEW;            }
<INITIAL>"delete"       { ring_compiler_update_line_content(yytext); return TOKEN_DELETE;         }
<INITIAL>"."            { ring_compiler_update_line_content(yytext); return TOKEN_DOT;            }
<INITIAL>"->"           { ring_compiler_update_line_content(yytext); return TOKEN_ARROW;          }

<INITIAL>"+"            { ring_compiler_update_line_content(yytext); return TOKEN_ADD;            }
<INITIAL>"-"            { ring_compiler_update_line_content(yytext); return TOKEN_SUB;            }
<INITIAL>"*"            { ring_compiler_update_line_content(yytext); return TOKEN_MUL;            }
<INITIAL>"/"            { ring_compiler_update_line_content(yytext); return TOKEN_DIV;            }
<INITIAL>"%"            { ring_compiler_update_line_content(yytext); return TOKEN_MOD;            }
<INITIAL>"++"           { ring_compiler_update_line_content(yytext); return TOKEN_INCREASE;       }
<INITIAL>"--"           { ring_compiler_update_line_content(yytext); return TOKEN_DECREASE;       }
<INITIAL>"+="           { ring_compiler_update_line_content(yytext); return TOKEN_ADD_ASSIGN;     }
<INITIAL>"-="           { ring_compiler_update_line_content(yytext); return TOKEN_SUB_ASSIGN;     }
<INITIAL>"*="           { ring_compiler_update_line_content(yytext); return TOKEN_MUL_ASSIGN;     }
<INITIAL>"/="           { ring_compiler_update_line_content(yytext); return TOKEN_DIV_ASSIGN;     }
<INITIAL>"%="           { ring_compiler_update_line_content(yytext); return TOKEN_MOD_ASSIGN;     }

<INITIAL>"and"          { ring_compiler_update_line_content(yytext); return TOKEN_AND;            }
<INITIAL>"or"           { ring_compiler_update_line_content(yytext); return TOKEN_OR;             }
<INITIAL>"not"          { ring_compiler_update_line_content(yytext); return TOKEN_NOT;            }

<INITIAL>"=="           { ring_compiler_update_line_content(yytext); return TOKEN_EQ;             }
<INITIAL>"!="           { ring_compiler_update_line_content(yytext); return TOKEN_NE;             }

<INITIAL>">"            { ring_compiler_update_line_content(yytext); return TOKEN_GT;             }
<INITIAL>">="           { ring_compiler_update_line_content(yytext); return TOKEN_GE;             }
<INITIAL>"<"            { ring_compiler_update_line_content(yytext); return TOKEN_LT;             }
<INITIAL>"<="           { ring_compiler_update_line_content(yytext); return TOKEN_LE;             }

<INITIAL>"("            { ring_compiler_update_line_content(yytext); return TOKEN_LP;             }
<INITIAL>")"            { ring_compiler_update_line_content(yytext); return TOKEN_RP;             }
<INITIAL>"{"            { ring_compiler_update_line_content(yytext); return TOKEN_LC;             }
<INITIAL>"}"            { ring_compiler_update_line_content(yytext); return TOKEN_RC;             }
<INITIAL>"["            { ring_compiler_update_line_content(yytext); return TOKEN_LB;             }
<INITIAL>"]"            { ring_compiler_update_line_content(yytext); return TOKEN_RB;             }
<INITIAL>","            { ring_compiler_update_line_content(yytext); return TOKEN_COMMA;          }
<INITIAL>":"            { ring_compiler_update_line_content(yytext); return TOKEN_COLON;          }
<INITIAL>";"            { ring_compiler_update_line_content(yytext); return TOKEN_SEMICOLON;      }
<INITIAL>"?"            { ring_compiler_update_line_content(yytext); return TOKEN_QUESTION_MARK;  }
<INITIAL>"="            { ring_compiler_update_line_content(yytext); return TOKEN_ASSIGN;         }

<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
    debug_log_with_red_coloar("[STATUS:INITIAL]\t line_num(%d),column_num(%d),identifier(%s)",
        get_ring_compiler_line_number(), 
        get_ring_compiler_column_number(), 
        yytext);

    ring_compiler_update_line_content(yytext);

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
        get_ring_compiler_line_number(), 
        get_ring_compiler_column_number(), 
        yytext);

    ring_compiler_update_line_content(yytext);
    yylval.m_literal_interface = yytext;

    return INT_LITERAL;
}
<INITIAL>[0-9]+\.[0-9]+ {
    debug_log_with_red_coloar("[STATUS:INITIAL]\t line_num(%d),column_num(%d),double_literal(%s)",
        get_ring_compiler_line_number(), 
        get_ring_compiler_column_number(), 
        yytext);

    ring_compiler_update_line_content(yytext);
    yylval.m_literal_interface = yytext;

    return DOUBLE_LITERAL;
}

<INITIAL>\" {
    ring_compiler_update_line_content(yytext);

    init_string_literal_buffer();
    BEGIN STRING_LITERAL_STATE;
}
<INITIAL>\n {
    debug_log_with_red_coloar("[STATUS:INITIAL]\t new line(LF) line_number(%d)\n\n", get_ring_compiler_line_number());

    reset_ring_compiler_column_number();
    ring_compiler_reset_current_line_content();
    increase_ring_compiler_line_number();
}
<INITIAL>\r\n {
    debug_log_with_red_coloar("[STATUS:INITIAL]\t new line(CRLF) line_number(%d)\n\n", get_ring_compiler_line_number());

    reset_ring_compiler_column_number();
    ring_compiler_reset_current_line_content();
    increase_ring_compiler_line_number();
}
<INITIAL>"//" BEGIN LINE_COMMENT;
<INITIAL>"/*" BEGIN BLOCK_COMMENT;

<INITIAL>. {
    ring_compiler_update_line_content(yytext);
}


<LINE_COMMENT>\n {
    yylval.m_comment_value = get_string_literal();
    reset_string_literal_buffer();
    reset_ring_compiler_column_number();
    ring_compiler_reset_current_line_content();
    increase_ring_compiler_line_number();
    BEGIN INITIAL;
}
<LINE_COMMENT>\r\n {
    yylval.m_comment_value = get_string_literal();
    reset_string_literal_buffer();
    reset_ring_compiler_column_number();
    ring_compiler_reset_current_line_content();
    increase_ring_compiler_line_number();
    BEGIN INITIAL;
}
<LINE_COMMENT>. {
    string_literal_add_char(yytext[0]);
}


<BLOCK_COMMENT>\n {
    yylval.m_comment_value = get_string_literal();
    reset_string_literal_buffer();
    reset_ring_compiler_column_number();
    ring_compiler_reset_current_line_content();
    increase_ring_compiler_line_number();
}
<BLOCK_COMMENT>\r\n {
    yylval.m_comment_value = get_string_literal();
    reset_string_literal_buffer();
    reset_ring_compiler_column_number();
    ring_compiler_reset_current_line_content();
    increase_ring_compiler_line_number();
}
<BLOCK_COMMENT>. {
    string_literal_add_char(yytext[0]);
}
<BLOCK_COMMENT>"*/" {
    yylval.m_comment_value = get_string_literal();
    reset_string_literal_buffer();
    BEGIN INITIAL;
}


<STRING_LITERAL_STATE>\" {
    ring_compiler_update_line_content(yytext);

    yylval.m_literal_interface = get_string_literal();


    BEGIN INITIAL;
    return STRING_LITERAL;
}
<STRING_LITERAL_STATE>\\n {
    ring_compiler_update_line_content(yytext);

    string_literal_add_char('\n');

    BEGIN STRING_LITERAL_STATE;
}
<STRING_LITERAL_STATE>\\r {
    ring_compiler_update_line_content(yytext);

    string_literal_add_char('\r');

    BEGIN STRING_LITERAL_STATE;
}
<STRING_LITERAL_STATE>\\t {
    ring_compiler_update_line_content(yytext);

    string_literal_add_char('\t');

    BEGIN STRING_LITERAL_STATE;
}
<STRING_LITERAL_STATE>. {
    ring_compiler_update_line_content(yytext);

    string_literal_add_char(yytext[0]);

    BEGIN STRING_LITERAL_STATE;
}

%%
