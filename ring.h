#ifndef RING_INCLUDE_H
#define RING_INCLUDE_H

#define RING_VERSION "ring-v0.0.3-beat"

typedef struct Ring_Interpreter_Tag Ring_Interpreter;

// struct Statement_Tag;
typedef struct Statement_Tag Statement;

// struct Expression_Tag;
typedef struct Expression_Tag Expression;

typedef struct BinaryExpression_Tag BinaryExpression;

// struct FunctionCallExpression_Tag;
typedef struct FunctionCallExpression_Tag FunctionCallExpression;

typedef struct AssignExpression_Tag AssignExpression;

// struct ArgumentList_Tag;
typedef struct ArgumentList_Tag ArgumentList;

// struct Variable_Tag;
typedef struct Variable_Tag Variable;

typedef struct Identifier_Tag Identifier;

// struct Function_Tag;
typedef struct Function_Tag Function;

typedef void Ring_InnerFunc(int argc, char *string);

struct Ring_Interpreter_Tag {
    char *       current_file_name;
    unsigned int current_line_number;
    unsigned int current_column_number;
    char *       current_line_content;

    unsigned int statement_list_size;
    Statement *  statement_list;

    unsigned int function_list_size;
    Function *   function_list;

    unsigned int variable_list_size;
    Variable *   variable_list;

    unsigned int identifier_list_size;
    Identifier * identifier_list;
};

typedef enum {
    IDENTIFIER_TYPE_UNKNOW = 0,
    IDENTIFIER_TYPE_VARIABLE,
    IDENTIFIER_TYPE_FUNCATION,
} IdentifierType;

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
    EXPRESSION_TYPE_LITERAL_INT,
    EXPRESSION_TYPE_LITERAL_DOUBLE,
    EXPRESSION_TYPE_LITERAL_STRING,
    EXPRESSION_TYPE_FUNCTION_CALL,
    EXPRESSION_TYPE_ASSIGN,
    EXPRESSION_TYPE_ARITHMETIC_ADD,
    EXPRESSION_TYPE_ARITHMETIC_SUB,
    EXPRESSION_TYPE_ARITHMETIC_MUL,
    EXPRESSION_TYPE_ARITHMETIC_DIV,
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
    unsigned int line_number;

    ExpressionType type;
    union {
        int                     int_literal;
        double                  double_literal;
        char *                  string_literal;
        FunctionCallExpression *function_call_expression;
        AssignExpression *      assign_expression;
        BinaryExpression *      binary_expression;
    } u;
};

struct FunctionCallExpression_Tag {
    unsigned int  current_line_number;
    char *        function_name;
    ArgumentList *argument_list;
};

struct Identifier_Tag {
    unsigned int line_number;

    IdentifierType type;
    char *         identifier_name;

    Identifier *next;
};

struct AssignExpression_Tag {
    char *      assign_identifier;
    Expression *expression;
};

struct BinaryExpression_Tag {
    Expression *left_expression;
    Expression *right_expression;
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
    Variable *next;
};

struct Function_Tag {
    char *          function_name;
    Ring_InnerFunc *inner_func;

    Function *next;
};

// typedef struct {
// } ListNode;

// struct List {
//     ListNode *node;
//     ListNode *next;
// };

// struct IdentifierDefinition_Tag {

// };

#define print_debug_info(message) \
    printf("[DEBUG][%s:%d][function:%s]%s\n", __FILE__, __LINE__, __FUNCTION__, message)

Ring_Interpreter *new_ring_interpreter(char *file_name);
Ring_Interpreter *get_ring_interpreter();
char *            get_ring_interpreter_current_file_name();
char *            get_ring_interpreter_current_line_content();
unsigned int      get_ring_interpreter_line_number();
unsigned int      increase_ring_interpreter_line_number();
unsigned int      get_ring_interpreter_column_number();
unsigned int      increase_ring_interpreter_column_number(unsigned int len);
void              reset_ring_interpreter_column_number();
int               ring_interpreter_init_statement_list(Statement *statement);
int               ring_interpreter_add_statement(Statement *statement);
void              ring_interpreter_registe_inner_func();

void  init_string_literal_buffer();
void  reset_string_literal_buffer();
void  string_literal_add_char(char ch);
char *get_string_literal();

void insert_identifier(IdentifierType type, char *name);

Variable *new_variable();

Identifier *new_identifier(IdentifierType type, char *name);

void interpret_statement(Statement *statement);
void interpret_expression(Expression *expression);
void invoke_function(FunctionCallExpression *function_call_expression);
int  interpret_binary_expression(Expression *expression);
void assign(Expression *expression);

#endif
