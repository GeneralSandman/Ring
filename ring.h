#ifndef RING_INCLUDE_H
#define RING_INCLUDE_H

typedef enum {

} StatementType;

typedef struct {
    StatementType type;
    int line_number;
} Statement;

typedef enum {
    EXPRESSION_TYPE_UNKNOW = 1,

    EXPRESSION_TYPE_Variable_Definition,
    EXPRESSION_TYPE_Function_Call,
} ExpressionType;

typedef struct {
    ExpressionType type;
    int line_number;

} Expression;

void init_string_literal_buffer();
void reset_string_literal_buffer();
void string_literal_add_char(char ch);
char *get_string_literal();

#endif