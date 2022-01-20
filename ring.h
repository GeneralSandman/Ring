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

typedef struct AssignExpression_Tag AssignExpression;

// struct ArgumentList_Tag;
typedef struct ArgumentList_Tag ArgumentList;

// struct Variable_Tag;
typedef struct Variable_Tag Variable;

typedef union {
    int    int_value;
    double double_value;
    char   char_value;
    char * string_value;
} Ring_BasicValue;

typedef enum {
    STATEMENT_TYPE_UNKNOW = 0,
    STATEMENT_TYPE_EXPRESSION,
    STATEMENT_TYPE_VARIABLE_DEFINITION,
} StatementType;

typedef enum {
    EXPRESSION_TYPE_UNKNOW = 0,
    EXPRESSION_TYPE_FUNCTION_CALL,
    EXPRESSION_TYPE_ASSIGN,
} ExpressionType;

typedef enum {
    ARGUMENT_TYPE_UNKNOW = 0,
    ARGUMENT_TYPE_RING_BASICVALUE,
    ARGUMENT_TYPE_EXPRESSION,
} ArgumentType;

typedef enum {
    VARIABLE_TYPE_UNKNOW = 0,
    VARIABLE_TYPE_INT,
    VARIABLE_TYPE_DOUBLE,
    VARIABLE_TYPE_STRING,
} VariableType;

struct Statement_Tag {
    StatementType type;
    unsigned int  line_number;
    union {
        Expression *expression;
        Variable *  variable;
    } u;
    Statement *next;
};

struct Expression_Tag {
    ExpressionType type;
    unsigned int   line_number;
    union {
        FunctionCallExpression *function_call_expression;
        AssignExpression *      assign_expression;
    } u;
};

struct FunctionCallExpression_Tag {
    unsigned int  current_line_number;
    char *        function_name;
    ArgumentList *argument_list;
};

struct AssignExpression_Tag {
    char *assign_identifier;
    char *right_value;
};

struct ArgumentList_Tag {
    ArgumentType type;
    union {
        Ring_BasicValue *ring_basic_value;
        Expression *     expression;
    } u;
    struct ArgumentList_Tag *next;
};

struct Variable_Tag {
    VariableType type;
    char *       variable_identifer;
    union {
        Ring_BasicValue *ring_basic_value;
    } u;
};

void  init_string_literal_buffer();
void  reset_string_literal_buffer();
void  string_literal_add_char(char ch);
char *get_string_literal();

Variable *new_variable();

#endif
