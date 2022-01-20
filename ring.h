#ifndef RING_INCLUDE_H
#define RING_INCLUDE_H

typedef struct Ring_Interpreter_Tag Ring_Interpreter;

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

// struct Function_Tag;
typedef struct Function_Tag Function;

typedef void Ring_InnerFunc(int argc, char *string);

struct Ring_Interpreter_Tag {
    unsigned int current_line_number;

    unsigned int statement_list_size;
    Statement *  statement_list;
    Function *   function_list;
};

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
        Ring_BasicValue ring_basic_value;
        Expression *    expression;
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

struct Function_Tag {
    char *          function_name;
    Ring_InnerFunc *inner_func;

    Function *next;
};

Ring_Interpreter *new_ring_interpreter();
Ring_Interpreter *get_ring_interpreter();
unsigned int      get_ring_interpreter_line_number();
unsigned int      increase_ring_interpreter_line_number();
int               ring_interpreter_init_statement_list(Statement *statement);
int               ring_interpreter_add_statement(Statement *statement);
void              ring_interpreter_registe_inner_func();

void  init_string_literal_buffer();
void  reset_string_literal_buffer();
void  string_literal_add_char(char ch);
char *get_string_literal();

Variable *new_variable();

#endif
