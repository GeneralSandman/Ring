#ifndef RING_INCLUDE_H
#define RING_INCLUDE_H

// union Ring_BasicValue_Tag;
// typedef union Ring_BasicValue_Tag Ring_BasicValue;

// struct StatementList_Tag;
// typedef struct StatementList_Tag StatementList;

// struct Statement_Tag;
typedef struct Statement_Tag Statement;

// struct Expression_Tag;
typedef struct Expression_Tag Expression;

// struct FunctionCallExpression_Tag;
typedef struct FunctionCallExpression_Tag FunctionCallExpression;

// struct ArgumentList_Tag;
typedef struct ArgumentList_Tag ArgumentList;

typedef union {
    int    int_value;
    double double_value;
    char   char_value;
    char * string_value;
} Ring_BasicValue;

typedef enum {
    STATEMENT_TYPE_UNKNOW = 0,
    STATEMENT_TYPE_EXPRESSION,
} StatementType;

typedef enum {
    EXPRESSION_TYPE_UNKNOW = 0,
    EXPRESSION_TYPE_FUNCTION_CALL,
} ExpressionType;

typedef enum {
    ARGUMENT_TYPE_UNKNOW = 0,
    ARGUMENT_TYPE_RING_BASICVALUE,
    ARGUMENT_TYPE_EXPRESSION,
} ArgumentType;

struct Statement_Tag {
    StatementType type;
    unsigned int  line_number;
    union {
        Expression *expression;
    } u;
    Statement *next;
};

struct Expression_Tag {
    ExpressionType type;
    unsigned int   line_number;
    union {
        FunctionCallExpression *function_call_expression;
    } u;
};

struct FunctionCallExpression_Tag {
    unsigned int  current_line_number;
    char *        function_name;
    ArgumentList *argument_list;
};

struct ArgumentList_Tag {
    ArgumentType type;
    union {
        Ring_BasicValue *ring_basic_value;
        Expression *     expression;
    } u;
    struct ArgumentList_Tag *next;
};

void  init_string_literal_buffer();
void  reset_string_literal_buffer();
void  string_literal_add_char(char ch);
char *get_string_literal();

#endif
