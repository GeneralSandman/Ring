%{
#include <stdio.h>
#include "y.tab.h"
#include "ring.h"

int yywrap(){
    return 1;
}

%}
%start COMMENT STRING_LITERAL_STATE
%%

<INITIAL>"string" return TOKEN_STRING;
<INITIAL>";" return TOKEN_SEMICOLON;
<INITIAL>"=" return TOKEN_ASSIGN;
<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
    yylval.identifier = yytext;
    return IDENTIFIER;
}

<INITIAL>\" {
    init_string_literal_buffer();
    BEGIN STRING_LITERAL_STATE;
}
<INITIAL>\n {
    printf("new line\n");
}
<INITIAL>\r\n {
    printf("new line\n");
}
<INITIAL>"//" BEGIN COMMENT;
<INITIAL>. {
}


<COMMENT>\n {
    BEGIN INITIAL;
}
<COMMENT>\r\n {
    BEGIN INITIAL;
}
<COMMENT>. {
    printf("comment: %c\n", yytext[0]);
};


<STRING_LITERAL_STATE>\" {
    BEGIN INITIAL;
    return STRING_LITERAL;
}
<STRING_LITERAL_STATE>. {
    string_literal_add_char(yytext[0]);
    yylval.string_value = get_string_literal();
    BEGIN STRING_LITERAL_STATE;
}

%%
