#ifndef RING_INCLUDE_H
#define RING_INCLUDE_H

typedef enum {
    EXPRESSION_TYPE_UNKNOW = 0,
    EXPRESSION_TYPE_FUNCTION_CALL,
} ExpressionType;

typedef struct {
    ExpressionType type;
    int line_number;
    union {
    } u;
} Expression;

typedef enum {
    STATEMENT_TYPE_UNKNOW = 0,
    STATEMENT_TYPE_VARIABLE_DEFINITION,
    STATEMENT_TYPE_EXPRESSION,
} StatementType;
typedef struct {
    StatementType type;
    int line_number;
    union {
        Expression *expression;
    } u;

} Statement;

void init_string_literal_buffer();
void reset_string_literal_buffer();
void string_literal_add_char(char ch);
char *get_string_literal();

#endif