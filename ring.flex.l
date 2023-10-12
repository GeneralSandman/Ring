%{
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "ring.h"
#include "y.tab.hpp"

char linebuf[500];

extern "C" int yywrap(){
    return 1;
}

%}
%start LINE_COMMENT BLOCK_COMMENT STRING_LITERAL_STATE

%option yylineno

%%



<INITIAL>"typedef"      { package_unit_update_line_content(yytext); return TOKEN_TYPEDEF;        }
<INITIAL>"bool"         { package_unit_update_line_content(yytext); return TOKEN_BOOL;           }
<INITIAL>"int"          { package_unit_update_line_content(yytext); return TOKEN_INT;            }
<INITIAL>"double"       { package_unit_update_line_content(yytext); return TOKEN_DOUBLE;         }
<INITIAL>"string"       { package_unit_update_line_content(yytext); return TOKEN_STRING;         }
<INITIAL>"struct"       { package_unit_update_line_content(yytext); return TOKEN_STRUCT;         }
<INITIAL>"bind"         { package_unit_update_line_content(yytext); return TOKEN_BIND;           }
<INITIAL>"lambda"       { package_unit_update_line_content(yytext); return TOKEN_LAMBDA;         }
<INITIAL>"return"       { package_unit_update_line_content(yytext); return TOKEN_RETURN;         }
<INITIAL>"defer"        { package_unit_update_line_content(yytext); return TOKEN_DEFER;          }
<INITIAL>"range"        { package_unit_update_line_content(yytext); return TOKEN_RANGE;          }

<INITIAL>"class"        { package_unit_update_line_content(yytext); return TOKEN_CLASS;          }
<INITIAL>"private"      { package_unit_update_line_content(yytext); return TOKEN_PRIVATE;        }
<INITIAL>"public"       { package_unit_update_line_content(yytext); return TOKEN_PUBLIC;         }
<INITIAL>"@"            { package_unit_update_line_content(yytext); return TOKEN_ATTRIBUTE;      }
<INITIAL>"field"        { package_unit_update_line_content(yytext); return TOKEN_FIELD;          }
<INITIAL>"method"       { package_unit_update_line_content(yytext); return TOKEN_METHOD;         }
<INITIAL>"constructor"  { package_unit_update_line_content(yytext); return TOKEN_CONSTRUCTOR;    }

<INITIAL>"global"       { package_unit_update_line_content(yytext); return TOKEN_GLOBAL;         }
<INITIAL>"if"           { package_unit_update_line_content(yytext); return TOKEN_IF;             }
<INITIAL>"elseif"       { package_unit_update_line_content(yytext); return TOKEN_ELSEIF;         }
<INITIAL>"else"         { package_unit_update_line_content(yytext); return TOKEN_ELSE;           }
<INITIAL>"for"          { package_unit_update_line_content(yytext); return TOKEN_FOR;            }
<INITIAL>"do"           { package_unit_update_line_content(yytext); return TOKEN_DO;             }
<INITIAL>"break"        { package_unit_update_line_content(yytext); return TOKEN_BREAK;          }
<INITIAL>"jump"         { package_unit_update_line_content(yytext); return TOKEN_JUMP;           }
<INITIAL>"continue"     { package_unit_update_line_content(yytext); return TOKEN_CONTINUE;       }
<INITIAL>"null"         { package_unit_update_line_content(yytext); return TOKEN_NULL;           }

<INITIAL>"true"         { package_unit_update_line_content(yytext); return TOKEN_TRUE;           }
<INITIAL>"false"        { package_unit_update_line_content(yytext); return TOKEN_FALSE;          }

<INITIAL>"var"          { package_unit_update_line_content(yytext); return TOKEN_VAR;            }
<INITIAL>"auto"         { package_unit_update_line_content(yytext); return TOKEN_AUTO;           }
<INITIAL>"any"          { package_unit_update_line_content(yytext); return TOKEN_ANY;            }
<INITIAL>"const"        { package_unit_update_line_content(yytext); return TOKEN_CONST;          }
<INITIAL>"function"     { package_unit_update_line_content(yytext); return TOKEN_FUNCTION;       }
<INITIAL>"new"          { package_unit_update_line_content(yytext); return TOKEN_NEW;            }
<INITIAL>"delete"       { package_unit_update_line_content(yytext); return TOKEN_DELETE;         }
<INITIAL>"."            { package_unit_update_line_content(yytext); return TOKEN_DOT;            }
<INITIAL>".."           { package_unit_update_line_content(yytext); return TOKEN_2DOT;           }
<INITIAL>"..."          { package_unit_update_line_content(yytext); return TOKEN_3DOT;           }
<INITIAL>"->"           { package_unit_update_line_content(yytext); return TOKEN_ARROW;          }

<INITIAL>"package"      { package_unit_update_line_content(yytext); return TOKEN_PACKAGE;        }
<INITIAL>"import"       { package_unit_update_line_content(yytext); return TOKEN_IMPORT;         }

<INITIAL>"+"            { package_unit_update_line_content(yytext); return TOKEN_ADD;            }
<INITIAL>"-"            { package_unit_update_line_content(yytext); return TOKEN_SUB;            }
<INITIAL>"*"            { package_unit_update_line_content(yytext); return TOKEN_MUL;            }
<INITIAL>"/"            { package_unit_update_line_content(yytext); return TOKEN_DIV;            }
<INITIAL>"%"            { package_unit_update_line_content(yytext); return TOKEN_MOD;            }
<INITIAL>"++"           { package_unit_update_line_content(yytext); return TOKEN_INCREASE;       }
<INITIAL>"--"           { package_unit_update_line_content(yytext); return TOKEN_DECREASE;       }
<INITIAL>"+="           { package_unit_update_line_content(yytext); return TOKEN_ADD_ASSIGN;     }
<INITIAL>"-="           { package_unit_update_line_content(yytext); return TOKEN_SUB_ASSIGN;     }
<INITIAL>"*="           { package_unit_update_line_content(yytext); return TOKEN_MUL_ASSIGN;     }
<INITIAL>"/="           { package_unit_update_line_content(yytext); return TOKEN_DIV_ASSIGN;     }
<INITIAL>"%="           { package_unit_update_line_content(yytext); return TOKEN_MOD_ASSIGN;     }

<INITIAL>"and"          { package_unit_update_line_content(yytext); return TOKEN_AND;            }
<INITIAL>"or"           { package_unit_update_line_content(yytext); return TOKEN_OR;             }
<INITIAL>"not"          { package_unit_update_line_content(yytext); return TOKEN_NOT;            }

<INITIAL>"=="           { package_unit_update_line_content(yytext); return TOKEN_EQ;             }
<INITIAL>"!="           { package_unit_update_line_content(yytext); return TOKEN_NE;             }

<INITIAL>">"            { package_unit_update_line_content(yytext); return TOKEN_GT;             }
<INITIAL>">="           { package_unit_update_line_content(yytext); return TOKEN_GE;             }
<INITIAL>"<"            { package_unit_update_line_content(yytext); return TOKEN_LT;             }
<INITIAL>"<="           { package_unit_update_line_content(yytext); return TOKEN_LE;             }

<INITIAL>"("            { package_unit_update_line_content(yytext); return TOKEN_LP;             }
<INITIAL>")"            { package_unit_update_line_content(yytext); return TOKEN_RP;             }
<INITIAL>"{"            { package_unit_update_line_content(yytext); return TOKEN_LC;             }
<INITIAL>"}"            { package_unit_update_line_content(yytext); return TOKEN_RC;             }
<INITIAL>"["            { package_unit_update_line_content(yytext); return TOKEN_LB;             }
<INITIAL>"]"            { package_unit_update_line_content(yytext); return TOKEN_RB;             }
<INITIAL>","            { package_unit_update_line_content(yytext); return TOKEN_COMMA;          }
<INITIAL>":"            { package_unit_update_line_content(yytext); return TOKEN_COLON;          }
<INITIAL>"::"           { package_unit_update_line_content(yytext); return TOKEN_2COLON;         }
<INITIAL>";"            { package_unit_update_line_content(yytext); return TOKEN_SEMICOLON;      }
<INITIAL>"?"            { package_unit_update_line_content(yytext); return TOKEN_QUESTION_MARK;  }
<INITIAL>"="            { package_unit_update_line_content(yytext); return TOKEN_ASSIGN;         }
<INITIAL>"#"            { package_unit_update_line_content(yytext); return TOKEN_NUM_SIGN;       }

<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
    debug_log_with_red_coloar("[STATUS:INITIAL]\t line_num(%d),column_num(%d),identifier(%s)",
        package_unit_get_line_number(), 
        package_unit_get_column_number(), 
        yytext);

    package_unit_update_line_content(yytext);

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
        package_unit_get_line_number(), 
        package_unit_get_column_number(), 
        yytext);

    package_unit_update_line_content(yytext);
    yylval.m_literal_interface = yytext;

    return INT_LITERAL;
}
<INITIAL>[0-9]+\.[0-9]+ {
    debug_log_with_red_coloar("[STATUS:INITIAL]\t line_num(%d),column_num(%d),double_literal(%s)",
        package_unit_get_line_number(), 
        package_unit_get_column_number(), 
        yytext);

    package_unit_update_line_content(yytext);
    yylval.m_literal_interface = yytext;

    return DOUBLE_LITERAL;
}

<INITIAL>\" {
    package_unit_update_line_content(yytext);

    init_string_literal_buffer();
    BEGIN STRING_LITERAL_STATE;
}
<INITIAL>\n.* {
    debug_log_with_red_coloar("[STATUS:INITIAL]\t new line(LF) line_number(%d)\n\n", package_unit_get_line_number());

    package_unit_update_line_content((char*)"\n");

    package_unit_reset_column_number();
    package_unit_reset_line_content();
    package_unit_increa_line_number();
    strncpy(linebuf, yytext+1, sizeof(linebuf));
    yyless(1);
}
<INITIAL>\r\n.* {
    debug_log_with_red_coloar("[STATUS:INITIAL]\t new line(CRLF) line_number(%d)\n\n", package_unit_get_line_number());

    package_unit_update_line_content((char*)"\r\n");

    package_unit_reset_column_number();
    package_unit_reset_line_content();
    package_unit_increa_line_number();
    strncpy(linebuf, yytext+1, sizeof(linebuf));
    yyless(2);
}
<INITIAL>"//" {
    package_unit_update_line_content(yytext);
    BEGIN LINE_COMMENT;
}
<INITIAL>"/*" {
    package_unit_update_line_content(yytext);
    BEGIN BLOCK_COMMENT;
}

<INITIAL>. {
    package_unit_update_line_content(yytext);
}


<LINE_COMMENT>\n {
    package_unit_update_line_content(yytext);
    yylval.m_comment_value = get_string_literal();
    reset_string_literal_buffer();
    package_unit_reset_column_number();
    package_unit_reset_line_content();
    package_unit_increa_line_number();
    BEGIN INITIAL;
}
<LINE_COMMENT>\r\n {
    package_unit_update_line_content(yytext);
    yylval.m_comment_value = get_string_literal();
    reset_string_literal_buffer();
    package_unit_reset_column_number();
    package_unit_reset_line_content();
    package_unit_increa_line_number();
    BEGIN INITIAL;
}
<LINE_COMMENT>. {
    package_unit_update_line_content(yytext);
    string_literal_add_char(yytext[0]);
}


<BLOCK_COMMENT>\n {
    package_unit_update_line_content(yytext);
    yylval.m_comment_value = get_string_literal();
    reset_string_literal_buffer();
    package_unit_reset_column_number();
    package_unit_reset_line_content();
    package_unit_increa_line_number();
}
<BLOCK_COMMENT>\r\n {
    package_unit_update_line_content(yytext);
    yylval.m_comment_value = get_string_literal();
    reset_string_literal_buffer();
    package_unit_reset_column_number();
    package_unit_reset_line_content();
    package_unit_increa_line_number();
}
<BLOCK_COMMENT>. {
    package_unit_update_line_content(yytext);
    string_literal_add_char(yytext[0]);
}
<BLOCK_COMMENT>"*/" {
    package_unit_update_line_content(yytext);
    yylval.m_comment_value = get_string_literal();
    reset_string_literal_buffer();
    BEGIN INITIAL;
}


<STRING_LITERAL_STATE>\" {
    package_unit_update_line_content(yytext);

    yylval.m_literal_interface = get_string_literal();


    BEGIN INITIAL;
    return STRING_LITERAL;
}
<STRING_LITERAL_STATE>\\n {
    package_unit_update_line_content(yytext);

    string_literal_add_char('\n');

    BEGIN STRING_LITERAL_STATE;
}
<STRING_LITERAL_STATE>\\r {
    package_unit_update_line_content(yytext);

    string_literal_add_char('\r');

    BEGIN STRING_LITERAL_STATE;
}
<STRING_LITERAL_STATE>\\t {
    package_unit_update_line_content(yytext);

    string_literal_add_char('\t');

    BEGIN STRING_LITERAL_STATE;
}
<STRING_LITERAL_STATE>. {
    package_unit_update_line_content(yytext);

    string_literal_add_char(yytext[0]);

    BEGIN STRING_LITERAL_STATE;
}

%%


extern char *yytext;

int yyerror(char const *str, ...){
    // 调用 ring_compiler_error 
    // 在这里捕获详细信息

    printf("\n%s:%d:%d: ", package_unit_get_file_name(), package_unit_get_line_number(), package_unit_get_column_number());
    complie_err_log("error: compiler error, syntax error");
    complie_err_log("        %s", linebuf);
    complie_err_log2("%*s^.....%s\n", package_unit_get_column_number() + 8, "", str);

    return 0;
}




