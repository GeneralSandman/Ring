#ifndef RING_INCLUDE_H
#define RING_INCLUDE_H

#define RING_VERSION "ring-v0.0.14-beat"

typedef struct Ring_Interpreter_Tag Ring_Interpreter;

typedef struct Ring_String_Tag Ring_String;

typedef struct Ring_BasicValue_Tag Ring_BasicValue;

typedef struct Statement_Tag Statement;

typedef struct StatementExecResult_Tag StatementExecResult;

typedef struct Expression_Tag Expression;

typedef struct BinaryExpression_Tag BinaryExpression;

typedef struct FunctionCallExpression_Tag FunctionCallExpression;

typedef struct AssignExpression_Tag AssignExpression;

typedef struct ArgumentList_Tag ArgumentList;

typedef struct Variable_Tag Variable;

typedef struct Identifier_Tag Identifier;

typedef struct Function_Tag Function;

typedef void Ring_InnerFunc(int argc, Ring_BasicValue **value);

struct Ring_Interpreter_Tag {
    char *       current_file_name;
    unsigned int current_line_number;
    unsigned int current_column_number;
    Ring_String *current_line_content;

    unsigned int statement_list_size;
    Statement *  statement_list;

    unsigned int function_list_size;
    Function *   function_list;

    unsigned int variable_list_size;
    Variable *   variable_list; // FIXME: 这里指的是全局变量，需要区分函数中的局部变量。

    unsigned int identifier_list_size;
    Identifier * identifier_list;
};

typedef enum {
    BOOL_FALSE = 0,
    BOOL_TRUE  = 1
} Ring_Bool;

typedef enum {
    IDENTIFIER_TYPE_UNKNOW = 0,
    IDENTIFIER_TYPE_VARIABLE,
    IDENTIFIER_TYPE_FUNCATION,
} IdentifierType;

struct Ring_String_Tag {
    char *buffer;
    int   size;
    int   capacity;
};

// typedef union {
//     int    int_value;
//     double double_value;
//     char   char_value;
//     char * string_value;
// } Ring_BasicValue;

typedef enum {
    STATEMENT_EXEC_RESULT_TYPE_UNKNOW = 0,
    STATEMENT_EXEC_RESULT_TYPE_EXPRESSION,
    STATEMENT_EXEC_RESULT_TYPE_RETURN,
} StatementExecResultType;

typedef enum {
    STATEMENT_TYPE_UNKNOW = 0,
    STATEMENT_TYPE_EXPRESSION,
    STATEMENT_TYPE_VARIABLE_DEFINITION,
    STATEMENT_TYPE_RETURN,
} StatementType;

typedef enum {
    EXPRESSION_TYPE_UNKNOW = 0,
    EXPRESSION_TYPE_LITERAL_BOOL,
    EXPRESSION_TYPE_LITERAL_INT,
    EXPRESSION_TYPE_LITERAL_DOUBLE,
    EXPRESSION_TYPE_LITERAL_STRING,
    EXPRESSION_TYPE_VARIABLE,
    EXPRESSION_TYPE_FUNCTION_CALL,
    EXPRESSION_TYPE_ASSIGN,

    EXPRESSION_TYPE_ARITHMETIC_ADD,
    EXPRESSION_TYPE_ARITHMETIC_SUB,
    EXPRESSION_TYPE_ARITHMETIC_MUL,
    EXPRESSION_TYPE_ARITHMETIC_DIV,
    EXPRESSION_TYPE_ARITHMETIC_UNITARY_MINUS, // 一元操作符 负号
    EXPRESSION_TYPE_LOGICAL_AND,
    EXPRESSION_TYPE_LOGICAL_OR,
    EXPRESSION_TYPE_LOGICAL_UNITARY_NOT, // 一元操作符 非 not
    EXPRESSION_TYPE_RELATIONAL_EQ,
    EXPRESSION_TYPE_RELATIONAL_NE,
    EXPRESSION_TYPE_RELATIONAL_GT,
    EXPRESSION_TYPE_RELATIONAL_GE,
    EXPRESSION_TYPE_RELATIONAL_LT,
    EXPRESSION_TYPE_RELATIONAL_LE,
} ExpressionType;

typedef enum {
    ARGUMENT_TYPE_UNKNOW = 0,
    ARGUMENT_TYPE_RING_BASICVALUE,
    ARGUMENT_TYPE_EXPRESSION,
} ArgumentType;

typedef enum {
    VARIABLE_TYPE_UNKNOW = 0,
    VARIABLE_TYPE_BOOL,
    VARIABLE_TYPE_INT,
    VARIABLE_TYPE_DOUBLE,
    VARIABLE_TYPE_STRING,
} VariableType;

typedef enum {
    FUNCTION_TYPE_UNKNOW = 0,
    FUNCTION_TYPE_INNER_LIB,
    FUNCTION_TYPE_EXTERNAL,
} FunctionType;

typedef enum {
    BASICVALUE_TYPE_UNKNOW = 0,
    BASICVALUE_TYPE_BOOL,
    BASICVALUE_TYPE_INT,
    BASICVALUE_TYPE_DOUBLE,
    BASICVALUE_TYPE_CHAR,
    BASICVALUE_TYPE_STRING,
} BasicValueType;

struct Ring_BasicValue_Tag {
    BasicValueType type;
    union {
        Ring_Bool bool_value;
        int       int_value;
        double    double_value;
        char      char_value;
        char *    string_value;
    } u;
};

struct Statement_Tag {
    StatementType type;
    unsigned int  line_number;
    union {
        Expression *expression;
        Variable *  variable;
        Expression *return_expression;
    } u;
    Statement *next;
};

struct StatementExecResult_Tag {
    StatementExecResultType type;
    union {
        Ring_BasicValue *return_value;
    } u;
};

struct Expression_Tag {
    unsigned int line_number;

    ExpressionType type;
    union {
        Ring_Bool               bool_literal;
        int                     int_literal;
        double                  double_literal;
        char *                  string_literal;
        char *                  variable_identifier;
        FunctionCallExpression *function_call_expression;
        AssignExpression *      assign_expression;
        BinaryExpression *      binary_expression;
        Expression *            unitary_expression;
    } u;

    Expression *next;
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

    Function *parent_scope; //作用域
    /*
    代码如 
    var int a;
    function add() {
        var int b;
    }

    那么 a的作用域为 global
    b的作用域为 local_function_add
    */

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
        Ring_BasicValue ring_basic_value; // TODO: 应该把这个删掉，参数应该全都是表达式
        Expression *    expression;
    } u;
    ArgumentList *next;
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
    unsigned int line_number;

    char *       function_name;
    FunctionType type;

    unsigned int parameter_list_size;
    Variable *   parameter_list;

    unsigned int variable_list_size;
    Variable *   variable_list;

    unsigned int return_list_size;
    // return_list; // TODO:

    unsigned int block_size;
    Statement *  block;

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

#define print_debug_info(format, ...) \
    printf("[DEBUG][%s:%d][function:%s]\t " format "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

#define LOG_COLOR_RED_UNDERLINE "\033[4;31m"
#define LOG_COLOR_GREEN_UNDERLINE "\033[4;32m"
#define LOG_COLOR_YELLOW_UNDERLINE "\033[4;33m"
#define LOG_COLOR_BLUE_UNDERLINE "\033[4;34m"
#define LOG_COLOR_PURPLE_UNDERLINE "\033[4;35m"

#define LOG_COLOR_RED "\033[0;31m"
#define LOG_COLOR_GREEN "\033[0;32m"
#define LOG_COLOR_YELLOW "\033[0;33m"
#define LOG_COLOR_BLUE "\033[0;34m"
#define LOG_COLOR_PURPLE "\033[0;35m"

#define LOG_COLOR_CLEAR "\033[0m"

#define complie_err_log(format, ...) \
    printf("%s" format "%s\n", LOG_COLOR_RED, ##__VA_ARGS__, LOG_COLOR_CLEAR)

#define complie_err_log2(format, ...) \
    printf("%s" format "%s\n", LOG_COLOR_GREEN, ##__VA_ARGS__, LOG_COLOR_CLEAR)

#define runtime_err_log(format, ...) \
    printf("%s" format "%s\n", LOG_COLOR_RED, ##__VA_ARGS__, LOG_COLOR_CLEAR)

#ifdef DEBUG
// 编译错误
#define debug_log_with_red_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_RED, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
// 标示错误的地址
#define debug_log_with_green_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_GREEN, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
//
#define debug_log_with_yellow_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_YELLOW, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
//
#define debug_log_with_blue_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_BLUE, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
// 编译告警
#define debug_log_with_purple_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_PURPLE, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
#else
// 编译错误
#define debug_log_with_red_coloar(format, ...)
// 标示错误的地址
#define debug_log_with_green_coloar(format, ...)
#define debug_log_with_yellow_coloar(format, ...)
#define debug_log_with_blue_coloar(format, ...)
// 编译告警
#define debug_log_with_purple_coloar(format, ...)
#endif

void         init_current_line_content();
Ring_String *get_current_line_content_string();
Ring_String *new_ring_string();
void         reset_ring_string(Ring_String *string);
void         ring_string_add_char(Ring_String *string, char ch);
char *       get_ring_string(Ring_String *string);

Ring_Interpreter *new_ring_interpreter(char *file_name);
Ring_Interpreter *get_ring_interpreter();
char *            get_ring_interpreter_current_file_name();
Ring_String *     get_ring_interpreter_current_line_content();
unsigned int      get_ring_interpreter_line_number();
unsigned int      increase_ring_interpreter_line_number();
unsigned int      get_ring_interpreter_column_number();
unsigned int      increase_ring_interpreter_column_number(unsigned int len);
void              ring_interpreter_update_line_content(char *str);
void              ring_interpreter_reset_current_line_content();
char *            ring_interpreter_get_current_line_content();
void              reset_ring_interpreter_column_number();
int               ring_interpreter_init_statement_list(Statement *statement);
int               ring_interpreter_add_statement(Statement *statement);
void              ring_interpreter_registe_inner_func();

void  init_string_literal_buffer();
void  reset_string_literal_buffer();
void  string_literal_add_char(char ch);
char *get_string_literal();

void insert_identifier(IdentifierType type, char *name);

int       identifier_check_valid(char *identifier);
Variable *variable_list_add_item(Variable *variable_list, Variable *variable);
Variable *new_variable(VariableType type, char *identifier);

Identifier *new_identifier(IdentifierType type, char *name);
void        check_identifier_valid(char *identifier_name);

void                 ring_interpret(Ring_Interpreter *ring_interpreter);
StatementExecResult *interpret_statement(Statement *statement, Function *function);
StatementExecResult *interpret_statement_list(Statement *statement, Function *function);
StatementExecResult *interpret_statement_return(Statement *statement, Function *function);
Ring_BasicValue *    interpret_expression(Expression *expression, Function *function);
Ring_BasicValue *    search_variable_value(char *identifier, Function *origin_function);
StatementExecResult *invoke_function(FunctionCallExpression *function_call_expression, Function *function);
StatementExecResult *invoke_external_function(Function *function);
Ring_BasicValue *    interpret_variable_expression(char *variable_identifier, Function *function);
Ring_BasicValue *    interpret_binary_expression_arithmetic(Expression *expression, Function *origin_function);
Ring_BasicValue *    interpret_binary_expression_realational(Expression *expression, Function *function);
Ring_BasicValue *    interpret_binary_expression_logical(Expression *expression, Function *function);
Ring_BasicValue *    interpret_binary_expression(Expression *expression, Function *origin_function);
Ring_BasicValue *    interpret_unitary_expression(Expression *expression, Function *origin_function);
void                 assign(Expression *expression, Function *function);

// 上下文相关语义检查
int ring_semantic_check(Ring_Interpreter *ring_interpreter);

void                    create_statement_list(Statement *statement);
void                    statement_list_add_item(Statement *statement);
Statement *             statement_list_add_item2(Statement *statement);
Statement *             statement_list_add_item3(Statement *statement_list, Statement *statement);
Statement *             create_statemen_from_expression(Expression *expression);
Statement *             create_statement_from_variable(Variable *variable);
Statement *             create_return_statement(Expression *expression);
void                    add_function_definition(Function *function_definition);
Expression *            create_expression();
Expression *            create_expression_identifier(char *identifier);
Expression *            create_expression_(FunctionCallExpression *function_call_expression);
Expression *            create_expression__(AssignExpression *assign_expression);
Expression *            create_expression_binary(ExpressionType type, Expression *left, Expression *right);
Expression *            create_expression_unitary(ExpressionType type, Expression *unitary_expression);
Expression *            create_expression_literal(ExpressionType type, char *literal_interface);
Expression *            create_expression_bool_literal(ExpressionType type, Ring_Bool value);
AssignExpression *      create_assign_expression(char *identifier, Expression *expression);
FunctionCallExpression *create_function_call_expression(char *identifier, ArgumentList *argument_list);
ArgumentList *          argument_list_add_item3(ArgumentList *argument_list, ArgumentList *argument);
ArgumentList *          create_argument_list(char *argument);
ArgumentList *          create_argument_list_from_expression(Expression *expression);
Identifier *            new_identifier(IdentifierType type, char *name);
Function *              new_function_definition(FunctionType type, char *identifier, Variable *parameter_list, Statement *block);
// Identifier *            create_identifier(IdentifierType type, char *name);
// char **identifier_list_add_item(char **identifier_list, char *identifier);
#endif
