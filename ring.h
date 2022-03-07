#ifndef RING_INCLUDE_H
#define RING_INCLUDE_H

#define RING_VERSION "ring-v0.0.36-beat"

typedef struct Ring_Compiler_Tag Ring_Compiler;

typedef struct Ring_VirtualMachine_Executer_Tag Ring_VirtualMachine_Executer;

typedef struct Ring_String_Tag Ring_String;

typedef struct Ring_BasicValue_Tag Ring_BasicValue;

typedef struct Ring_Array_Tag Ring_Array;

typedef struct Statement_Tag Statement;

typedef struct StatementExecResult_Tag StatementExecResult;

typedef struct Expression_Tag Expression;

typedef struct ArrayIndexExpression_Tag ArrayIndexExpression;

typedef struct BinaryExpression_Tag BinaryExpression;

typedef struct TernaryExpression_Tag TernaryExpression;

typedef struct FunctionCallExpression_Tag FunctionCallExpression;

typedef struct AssignExpression_Tag AssignExpression;

typedef struct ArgumentList_Tag ArgumentList;

typedef struct Variable_Tag Variable;

typedef struct Identifier_Tag Identifier;

typedef struct Function_Tag Function;

typedef struct FunctionReturnList_Tag FunctionReturnList;

typedef struct IfStatement_Tag IfStatement;

typedef struct ElseIfStatement_Tag ElseIfStatement;

typedef struct ForStatement_Tag ForStatement;

typedef struct DoWhileStatement_Tag DoWhileStatement;

typedef struct BreakStatement_Tag BreakStatement;

typedef struct ContinueStatement_Tag ContinueStatement;

typedef void Ring_InnerFunc(int argc, Ring_BasicValue **value);

struct Ring_Compiler_Tag {
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

struct Ring_VirtualMachine_Executer_Tag {
};

typedef enum {
    BOOL_FALSE = 0,
    BOOL_TRUE  = 1
} Ring_Bool;

typedef enum {
    IDENTIFIER_TYPE_UNKNOW = 0,
    IDENTIFIER_TYPE_VARIABLE,
    IDENTIFIER_TYPE_VARIABLE_ARRAY,
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
    STATEMENT_EXEC_RESULT_TYPE_NORMAL,
    STATEMENT_EXEC_RESULT_TYPE_EXPRESSION,
    STATEMENT_EXEC_RESULT_TYPE_RETURN,
    STATEMENT_EXEC_RESULT_TYPE_BREAK,
    STATEMENT_EXEC_RESULT_TYPE_CONTINUE,
} StatementExecResultType;

typedef enum {
    STATEMENT_TYPE_UNKNOW = 0,
    STATEMENT_TYPE_EXPRESSION,
    STATEMENT_TYPE_VARIABLE_DEFINITION,
    STATEMENT_TYPE_RETURN,
    STATEMENT_TYPE_IF,
    STATEMENT_TYPE_FOR,
    STATEMENT_TYPE_DOWHILE,
    STATEMENT_TYPE_BREAK,
    STATEMENT_TYPE_CONTINUE,
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

    EXPRESSION_TYPE_TERNARY, // 三目运算

    EXPRESSION_TYPE_ARITHMETIC_ADD,
    EXPRESSION_TYPE_ARITHMETIC_SUB,
    EXPRESSION_TYPE_ARITHMETIC_MUL,
    EXPRESSION_TYPE_ARITHMETIC_DIV,
    EXPRESSION_TYPE_ARITHMETIC_MOD,
    EXPRESSION_TYPE_ARITHMETIC_UNITARY_MINUS, // 一元操作符 负号
    EXPRESSION_TYPE_LOGICAL_AND,
    EXPRESSION_TYPE_LOGICAL_OR,
    EXPRESSION_TYPE_LOGICAL_UNITARY_NOT,     // 一元操作符 逻辑 非 not
    EXPRESSION_TYPE_UNITARY_INCREASE_SUFFIX, // 一元操作符 i++
    EXPRESSION_TYPE_UNITARY_INCREASE_PREFIX, // 一元操作符 ++i
    EXPRESSION_TYPE_UNITARY_DECREASE_SUFFIX, // 一元操作符 i--
    EXPRESSION_TYPE_UNITARY_DECREASE_PREFIX, // 一元操作符 --i
    EXPRESSION_TYPE_RELATIONAL_EQ,
    EXPRESSION_TYPE_RELATIONAL_NE,
    EXPRESSION_TYPE_RELATIONAL_GT,
    EXPRESSION_TYPE_RELATIONAL_GE,
    EXPRESSION_TYPE_RELATIONAL_LT,
    EXPRESSION_TYPE_RELATIONAL_LE,

    EXPRESSION_TYPE_ARRAY_INDEX,
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
    VARIABLE_TYPE_CHAR,
    VARIABLE_TYPE_STRING,
    VARIABLE_TYPE_ARRAY,
    VARIABLE_TYPE_CLASS,
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
    BASICVALUE_TYPE_ARRAY,
} BasicValueType;

typedef enum {
    ASSIGN_EXPRESSION_TYPE_UNKNOW = 0,
    ASSIGN_EXPRESSION_TYPE_ASSIGN,     // =
    ASSIGN_EXPRESSION_TYPE_ADD_ASSIGN, // +=
    ASSIGN_EXPRESSION_TYPE_SUB_ASSIGN, // -=
    ASSIGN_EXPRESSION_TYPE_MUL_ASSIGN, // *=
    ASSIGN_EXPRESSION_TYPE_DIV_ASSIGN, // /=
    ASSIGN_EXPRESSION_TYPE_MOD_ASSIGN, // %=
} AssignExpressionType;

struct Ring_BasicValue_Tag {
    BasicValueType type;
    BasicValueType array_member_type;

    union {
        Ring_Bool   bool_value;
        int         int_value;
        double      double_value;
        char        char_value;
        char *      string_value; // 暂时没用到
        Ring_Array *array_value;
    } u;
    Ring_BasicValue *next; // FIXME: 这个用在 return 多个的时候 return 1,2; 见 interpret_binary_expression:invoke_function
    // FIXME: 以后更改这个地方
};

struct Ring_String {
    unsigned int size;
    unsigned int capacity;
    char *       data;
};

struct Ring_Array_Tag {
    unsigned int     size;
    Ring_BasicValue *data;
};

struct Statement_Tag {
    unsigned int line_number;

    StatementType type;
    union {
        Expression *       expression;
        Variable *         variable;
        Expression *       return_expression;
        IfStatement *      if_statement;
        ForStatement *     for_statement;
        DoWhileStatement * dowhile_statement;
        BreakStatement *   break_statement;
        ContinueStatement *continue_statement;
    } u;
    Statement *next;
};

struct StatementExecResult_Tag {
    StatementExecResultType type;
    union {
        Ring_BasicValue *return_value;
    } u; // TODO: 这个没办法兼容多 返回值，重构的时候废弃，使用return_value_list_size & return_value_list
    unsigned int      return_value_list_size;
    Ring_BasicValue **return_value_list;
};

struct Expression_Tag {
    unsigned int line_number;

    BasicValueType convert_type;
    ExpressionType type;
    union {
        Ring_Bool               bool_literal;
        int                     int_literal;
        double                  double_literal;
        char *                  string_literal;
        char *                  variable_identifier;
        FunctionCallExpression *function_call_expression;
        AssignExpression *      assign_expression;
        TernaryExpression *     ternary_expression;
        BinaryExpression *      binary_expression;
        Expression *            unitary_expression;
        ArrayIndexExpression *  array_index_expression;
    } u;

    Expression *next;
};

struct ArrayIndexExpression_Tag {
    unsigned int line_number;

    char *      variable_identifier;
    Expression *index_expression;
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
    unsigned int   array_index; // 供数组使用，还要考虑一下负值索引的问题

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

// TODO: 这里还要兼容 数组元素赋值
struct AssignExpression_Tag {
    AssignExpressionType type;
    char *               assign_identifier; // TODO: 以后不应该使用这个 删除调
    unsigned int         assign_identifier_size;
    char **              assign_identifiers;
    // Identifier * assign_identifier_list;// TODO: 重构 最后都使用这个
    Expression *expression;
    // Expression *expression_list; // TODO: 重构 最后都使用这个
};

struct BinaryExpression_Tag {
    Expression *left_expression;
    Expression *right_expression;
};

// 三元运算符
struct TernaryExpression_Tag {
    Expression *condition_expression;
    Expression *true_expression;
    Expression *false_expression;
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
    unsigned int line_number;

    char *variable_identifer;
    int   is_const;

    VariableType type;
    VariableType array_member_type; // 数组里的内置类型

    union {
        Ring_BasicValue *ring_basic_value;
    } u;
    Expression *init_expression;
    Variable *  next;
};

struct Function_Tag {
    unsigned int line_number;

    char *       function_name;
    FunctionType type;

    unsigned int parameter_list_size;
    Variable *   parameter_list;

    unsigned int        return_list_size;
    FunctionReturnList *return_list;

    unsigned int variable_list_size;
    Variable *   variable_list;

    // unsigned int return_list_size;
    // return_list; // TODO:

    unsigned int block_size;
    Statement *  block;

    Ring_InnerFunc *inner_func;

    Function *next;
};

struct FunctionReturnList_Tag {
    VariableType        variable_type;
    FunctionReturnList *next;
};

struct IfStatement_Tag {
    unsigned int line_number;

    Expression *expression;

    unsigned int if_block_size;
    Statement *  if_block;

    ElseIfStatement *elseif_statement_list;

    unsigned int else_block_size;
    Statement *  else_block;
};

struct ElseIfStatement_Tag {
    unsigned int line_number;

    Expression *expression;

    unsigned int elseif_block_size;
    Statement *  elseif_block;

    ElseIfStatement *next;
};

struct ForStatement_Tag {
    unsigned int line_number;

    Expression *init_expression;
    Expression *condition_expression;
    Expression *post_expression;

    unsigned int block_size;
    Statement *  block;
};

struct DoWhileStatement_Tag {
    unsigned int line_number;

    Expression *condition_expression;

    unsigned int block_size;
    Statement *  block;
};

struct BreakStatement_Tag {
    unsigned int line_number;
};

struct ContinueStatement_Tag {
    unsigned int line_number;
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

#define printf_witch_red(format, ...) \
    printf("%s" format "%s", LOG_COLOR_RED, ##__VA_ARGS__, LOG_COLOR_CLEAR)
#define printf_witch_green(format, ...) \
    printf("%s" format "%s", LOG_COLOR_GREEN, ##__VA_ARGS__, LOG_COLOR_CLEAR)
#define printf_witch_blue(format, ...) \
    printf("%s" format "%s", LOG_COLOR_BLUE, ##__VA_ARGS__, LOG_COLOR_CLEAR)

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

Ring_Compiler *new_ring_compiler(char *file_name);
Ring_Compiler *get_ring_compiler();
char *         get_ring_compiler_current_file_name();
Ring_String *  get_ring_compiler_current_line_content();
unsigned int   get_ring_compiler_line_number();
unsigned int   increase_ring_compiler_line_number();
unsigned int   get_ring_compiler_column_number();
unsigned int   increase_ring_compiler_column_number(unsigned int len);
void           ring_compiler_update_line_content(char *str);
void           ring_compiler_reset_current_line_content();
char *         ring_compiler_get_current_line_content();
void           reset_ring_compiler_column_number();
int            ring_compiler_init_statement_list(Statement *statement);
int            ring_compiler_add_statement(Statement *statement);
void           ring_compiler_registe_inner_func();

void  init_string_literal_buffer();
void  reset_string_literal_buffer();
void  string_literal_add_char(char ch);
char *get_string_literal();

void insert_identifier(IdentifierType type, char *name);

int       identifier_check_valid(char *identifier);
Variable *variable_list_add_item(Variable *variable_list, Variable *variable);
Variable *new_variable(VariableType type, char *identifier, Expression *init_expression, int is_const);
Variable *new_variable_array(VariableType type, Expression *size, char *identifier, Expression *init_expression, int is_const);

Identifier *        new_identifier(IdentifierType type, char *name);
Identifier *        identifier_list_add_item(Identifier *identifier_list, Identifier *identifier);
FunctionReturnList *create_function_return_list(VariableType variable_type);
FunctionReturnList *function_return_list_add_item(FunctionReturnList *return_list, VariableType variable_type);
void                check_identifier_valid(char *identifier_name);

void                 ring_interpret(Ring_Compiler *ring_compiler);
StatementExecResult *interpret_statement(Statement *statement, Function *function);
StatementExecResult *interpret_statement_list(Statement *statement, Function *function);
StatementExecResult *interpret_statement_break(BreakStatement *statement, Function *function);
StatementExecResult *interpret_statement_continue(ContinueStatement *statement, Function *function);
StatementExecResult *interpret_statement_return(Statement *statement, Function *function);
StatementExecResult *interpret_statement_if(IfStatement *if_statement, Function *function);
StatementExecResult *interpret_statement_for(ForStatement *for_statement, Function *function);
StatementExecResult *interpret_statement_dowhile(DoWhileStatement *dowhile_statement, Function *function);
Ring_BasicValue *    interpret_expression(Expression *expression, Function *function);
Ring_BasicValue *    search_variable_value(char *identifier, Function *origin_function);
StatementExecResult *invoke_function(FunctionCallExpression *function_call_expression, Function *function);
StatementExecResult *invoke_external_function(Function *function);
Ring_BasicValue *    interpret_variable_expression(char *variable_identifier, Function *function);
Ring_BasicValue *    interpret_array_index_expression(ArrayIndexExpression *expression, Function *function);
Ring_BasicValue *    interpret_binary_expression_arithmetic(Expression *expression, Function *origin_function);
Ring_BasicValue *    interpret_binary_expression_realational(Expression *expression, Function *function);
Ring_BasicValue *    interpret_binary_expression_logical(Expression *expression, Function *function);
Ring_BasicValue *    interpret_ternary_condition_expression(Expression *expression, Function *origin_function);
Ring_BasicValue *    interpret_binary_expression(Expression *expression, Function *origin_function);
Ring_BasicValue *    interpret_unitary_expression(Expression *expression, Function *origin_function);
Ring_BasicValue *    interpret_unitary_expression_(Expression *expression, Function *origin_function);
void                 interpret_assign_expression(Expression *expression, Function *function);
void                 assign_identifier(Variable *variable, Ring_BasicValue *new_value, AssignExpressionType type);
Variable *           search_variable(char *variable_identifier, Function *function);

// 上下文相关语义检查
int ring_semantic_check(Ring_Compiler *ring_compiler);

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
Expression *            create_expression_identifier_with_index(char *identifier, Expression *index);
Expression *            create_expression_(FunctionCallExpression *function_call_expression);
Expression *            create_expression__(AssignExpression *assign_expression);
Expression *            create_expression_ternary(Expression *condition, Expression * true, Expression * false);
Expression *            create_expression_binary(ExpressionType type, Expression *left, Expression *right);
Expression *            create_expression_unitary(ExpressionType type, Expression *unitary_expression);
Expression *            create_expression_unitary_with_convert_type(BasicValueType convert_type, Expression *expression);
Expression *            create_expression_literal(ExpressionType type, char *literal_interface);
Expression *            create_expression_bool_literal(ExpressionType type, Ring_Bool value);
AssignExpression *      create_assign_expression(AssignExpressionType type, char *identifier, Expression *expression);
AssignExpression *      create_multi_assign_expression(char *first_identifier, Identifier *identifier_list, Expression *first_expression, Expression *expression_list);
FunctionCallExpression *create_function_call_expression(char *identifier, ArgumentList *argument_list);
Expression *            expression_list_add_item(Expression *expression_list, Expression *expression);
ArgumentList *          argument_list_add_item3(ArgumentList *argument_list, ArgumentList *argument);
ArgumentList *          create_argument_list(char *argument);
ArgumentList *          create_argument_list_from_expression(Expression *expression);
Identifier *            new_identifier(IdentifierType type, char *name);
Function *              new_function_definition(FunctionType type, char *identifier, Variable *parameter_list, FunctionReturnList *return_list, Statement *block);
Statement *             create_statement_from_if(IfStatement *if_statement);
IfStatement *           create_if_statement(Expression *expression, Statement *if_block, ElseIfStatement *elseif_statement_list, Statement *else_block);
ElseIfStatement *       create_elseif_statement(Expression *expression, Statement *elseif_block);
ElseIfStatement *       elseif_statement_add_item(ElseIfStatement *list, ElseIfStatement *elseif_statement);
Statement *             create_statement_from_for(ForStatement *for_statement);
ForStatement *          create_for_statement(Expression *init_expression, Expression *condition_expression, Expression *post_expression, Statement *block);
Statement *             create_statement_from_dowhile(DoWhileStatement *dowhile_statement);
DoWhileStatement *      create_dowhile_statement(Statement *block, Expression *condition_expression);
Statement *             create_statement_from_break();
Statement *             create_statement_from_continue();
// Identifier *            create_identifier(IdentifierType type, char *name);
// char **identifier_list_add_item(char **identifier_list, char *identifier);

// generate.c
void ring_fix_ast(Ring_Compiler *ring_compiler);
// generate.c

#endif
