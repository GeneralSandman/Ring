#ifndef RING_INCLUDE_H
#define RING_INCLUDE_H

#include <stdio.h>

#define RING_VERSION "ring-v0.1.0-beat"

typedef struct Ring_Compiler_Tag Ring_Compiler;

typedef struct Ring_VirtualMachine_Tag Ring_VirtualMachine;

typedef struct Ring_VirtualMachine_Executer_Tag Ring_VirtualMachine_Executer;

typedef struct RVM_Variable_Tag RVM_Variable;

typedef struct RVM_RuntimeStack_Tag RVM_RuntimeStack;

typedef struct RVM_RuntimeStatic_Tag RVM_RuntimeStatic;

typedef struct RVM_RuntimeHeap_Tag RVM_RuntimeHeap;

typedef struct RVM_OpcodeBuffer_Tag RVM_OpcodeBuffer;

typedef struct RVM_Opcode_Info_Tag RVM_Opcode_Info;

typedef struct RVM_LabelTable_Tag RVM_LabelTable;

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

typedef struct DoForStatement_Tag DoForStatement;

typedef struct DoWhileStatement_Tag DoWhileStatement;

typedef struct BreakStatement_Tag BreakStatement;

typedef struct ContinueStatement_Tag ContinueStatement;

typedef struct Ring_DeriveType_Tag Ring_DeriveType;

typedef struct Declaration_Tag Declaration;

typedef struct TypeSpecifier_Tag TypeSpecifier;

typedef struct IdentifierExpression_Tag IdentifierExpression;

typedef struct RVM_String_Tag RVM_String;
typedef struct RVM_Array_Tag  RVM_Array;
typedef struct RVM_Object_Tag RVM_Object;

typedef void Ring_InnerFunc(int argc, Ring_BasicValue** value);


struct Ring_Compiler_Tag {
    char*        current_file_name;
    unsigned int current_line_number;
    unsigned int current_column_number;
    Ring_String* current_line_content;

    unsigned int statement_list_size;
    Statement*   statement_list;

    unsigned int function_list_size;
    Function*    function_list;

    unsigned int variable_list_size;
    Variable*    variable_list; // FIXME: 这里指的是全局变量，需要区分函数中的局部变量。

    unsigned int identifier_list_size; // TODO:后续删除调
    Identifier*  identifier_list;      // TODO:后续删除调

    unsigned int declaration_list_size;
    Declaration* declaration_list;
};

struct Ring_VirtualMachine_Tag {
    Ring_VirtualMachine_Executer* executer;

    RVM_RuntimeStatic* runtime_static;
    RVM_RuntimeStack*  runtime_stack;
    RVM_RuntimeHeap*   runtime_heap;
    unsigned int       pc; // pc 用来偏移 executer->code_list[pc]
};

// generate.c
typedef unsigned char RVM_Byte;

typedef enum {
    CONSTANTPOOL_TYPE_UNKNOW,
    CONSTANTPOOL_TYPE_INT,
    CONSTANTPOOL_TYPE_DOUBLE,
    CONSTANTPOOL_TYPE_STRING,
} ConstantPoolType;

typedef struct {
    ConstantPoolType type;
    union {
        int    int_value;
        double double_value;
        char*  string_value;
    } u;
} RVM_ConstantPool;

struct Ring_VirtualMachine_Executer_Tag {
    unsigned int      constant_pool_size;
    RVM_ConstantPool* constant_pool_list;
    // 连续数组，非链表
    unsigned int  global_variable_size;
    RVM_Variable* global_variable_list;

    // 连续数组，非链表
    unsigned int function_size;
    Function*    function_list;

    // 连续数组，非链表
    unsigned int code_size;
    RVM_Byte*    code_list;
};


// generate.c


struct RVM_Variable_Tag {
    char*          identifier;
    TypeSpecifier* type;
};

typedef union {
    // TODO: 补充 bool
    int         int_value;
    double      double_value;
    RVM_Object* object;
} RVM_Value; // 这个名字得改一改

typedef enum {
    RVM_OBJECT_TYPE_UNKNOW,
    RVM_OBJECT_TYPE_STRING,
    RVM_OBJECT_TYPE_ARRAY,
} RVM_Object_Type;


struct RVM_String_Tag {
    // TODO:
    char* data;
};

struct RVM_Array_Tag {
    // TODO:
    unsigned int i;
};

struct RVM_Object_Tag {
    RVM_Object_Type type;
    union {
        RVM_String* string;
        RVM_Array*  array;
    } u;
};

// 支持线性寻址
struct RVM_RuntimeStack_Tag {
    RVM_Value*   data;
    unsigned int top_index;
    unsigned int size;
    unsigned int capacity;
};

struct RVM_RuntimeStatic_Tag {
    RVM_Value*   data;
    unsigned int size;
};

struct RVM_RuntimeHeap_Tag {
    // TODO: 稍后实现
    unsigned int i;
};

struct RVM_LabelTable_Tag {
    char*        label_name;
    unsigned int label_address;
};

typedef struct {
    char*        source_file_name;
    unsigned int source_code_line_number; // 对应Ring源代码文件的行数

    unsigned int opcode_begin_index; // 对应 opcode 的 开始索引
    unsigned int opcode_size;        // 一行Ring源代码 对应 opcode size
} RVM_LineMap;

struct RVM_OpcodeBuffer_Tag {
    RVM_Byte*    code_list;
    unsigned int code_size;
    unsigned int code_capacity;

    RVM_LabelTable* lable_list;
    unsigned int    lable_size;
    unsigned int    lable_capacity;
};

typedef enum {
    OPCODE_OPERAND_TYPE_UNKNOW,
    OPCODE_OPERAND_TYPE_0BYTE, // 后边没有操作数
    OPCODE_OPERAND_TYPE_1BYTE,
    OPCODE_OPERAND_TYPE_2BYTE,
} OpcodeOperandType;

struct RVM_Opcode_Info_Tag {
    RVM_Byte          code;
    char*             name;
    OpcodeOperandType type;
};

typedef enum {
    RVM_CODE_UNKNOW = 0,

    // push
    RVM_CODE_PUSH_INT_1BYTE, // operand 0-255
    RVM_CODE_PUSH_INT_2BYTE, // operand 256-65535
    RVM_CODE_PUSH_INT,       // bigger 65535

    RVM_CODE_PUSH_DOUBLE,

    RVM_CODE_PUSH_STRING,

    // pop
    RVM_CODE_POP_STATIC_INT,

    // push
    RVM_CODE_PUSH_STATIC_INT,

    //
    RVM_CODE_ADD_INT,
    RVM_CODE_SUB_INT,
    RVM_CODE_MUL_INT,
    RVM_CODE_DIV_INT,
    RVM_CODE_MOD_INT,

    //
    RVM_CODE_JUMP,
    RVM_CODE_JUMP_IF_FALSE,

} RVM_Opcode;

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
    char* buffer;
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
    STATEMENT_TYPE_DOFOR,
    STATEMENT_TYPE_DOWHILE,
    STATEMENT_TYPE_BREAK,
    STATEMENT_TYPE_CONTINUE,
    STATEMENT_TYPE_DECLARATION,
} StatementType;

typedef enum {
    EXPRESSION_TYPE_UNKNOW = 0,
    EXPRESSION_TYPE_LITERAL_BOOL,
    EXPRESSION_TYPE_LITERAL_INT,
    EXPRESSION_TYPE_LITERAL_DOUBLE,
    EXPRESSION_TYPE_LITERAL_STRING,
    EXPRESSION_TYPE_VARIABLE,
    EXPRESSION_TYPE_IDENTIFIER,
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
        char*       string_value; // 暂时没用到
        Ring_Array* array_value;
    } u;
    Ring_BasicValue* next; // FIXME: 这个用在 return 多个的时候 return 1,2; 见 interpret_binary_expression:invoke_function
    // FIXME: 以后更改这个地方
};

struct Ring_String {
    unsigned int size;
    unsigned int capacity;
    char*        data;
};

struct Ring_Array_Tag {
    unsigned int     size;
    Ring_BasicValue* data;
};

struct Statement_Tag {
    unsigned int line_number;

    StatementType type;
    union {
        Expression*        expression;
        Variable*          variable; // TODO: 以后废弃 使用 declaration_statement
        Expression*        return_expression;
        IfStatement*       if_statement;
        ForStatement*      for_statement;
        DoForStatement*    dofor_statement;
        DoWhileStatement*  dowhile_statement;
        BreakStatement*    break_statement;
        ContinueStatement* continue_statement;
        Declaration*       declaration_statement;
    } u;
    Statement* next;
};

struct StatementExecResult_Tag {
    StatementExecResultType type;
    union {
        Ring_BasicValue* return_value;
    } u; // TODO: 这个没办法兼容多 返回值，重构的时候废弃，使用return_value_list_size & return_value_list
    unsigned int      return_value_list_size;
    Ring_BasicValue** return_value_list;
};

struct Expression_Tag {
    unsigned int line_number;

    BasicValueType convert_type;
    ExpressionType type;
    union {
        Ring_Bool               bool_literal;
        int                     int_literal;
        double                  double_literal;
        char*                   string_literal;
        char*                   variable_identifier; // 后续废弃，使用下边的
        IdentifierExpression*   identifier_expression;
        FunctionCallExpression* function_call_expression;
        AssignExpression*       assign_expression;
        TernaryExpression*      ternary_expression;
        BinaryExpression*       binary_expression;
        Expression*             unitary_expression;
        ArrayIndexExpression*   array_index_expression;
    } u;

    Expression* next;
};

typedef enum {
    IDENTIFIER_EXPRESSION_TYPE_UNKNOW,
    IDENTIFIER_EXPRESSION_TYPE_VARIABLE,
    IDENTIFIER_EXPRESSION_TYPE_FUNCTION,
} IdentifierExpressionType;

struct IdentifierExpression_Tag {
    unsigned int line_number;

    IdentifierExpressionType type;
    char*                    identifier;
    union {
        Declaration* declaration;
        // Function // TODO:
    } u;
};

struct ArrayIndexExpression_Tag {
    unsigned int line_number;

    char*       variable_identifier;
    Expression* index_expression;
};

struct FunctionCallExpression_Tag {
    unsigned int line_number;

    char*         function_name;
    ArgumentList* argument_list;
};

struct Identifier_Tag { // TODO: 以后废弃这个东西
    unsigned int line_number;

    IdentifierType type;
    char*          identifier_name;
    unsigned int   array_index; // 供数组使用，还要考虑一下负值索引的问题

    Function* parent_scope; //作用域
    /*
    代码如 
    var int a;
    function add() {
        var int b;
    }

    那么 a的作用域为 global
    b的作用域为 local_function_add
    */

    Identifier* next;
};

// TODO: 这里还要兼容 数组元素赋值
struct AssignExpression_Tag {
    unsigned int line_number;

    AssignExpressionType type;


    char*        assign_identifier;      // TODO: delete
    unsigned int assign_identifier_size; // TODO: delete
    char**       assign_identifiers;     // TODO: delete
    // Identifier * assign_identifier_list;// TODO: delete
    Expression* expression; // TODO: delete
    // Expression *expression_list; // TODO: delete

    // 上边的4个以后都不要使用，全部使用下边最新的
    // 只使用 line_number type left operand
    Expression* left;
    Expression* operand;
};

struct BinaryExpression_Tag {
    Expression* left_expression;
    Expression* right_expression;
};

// 三元运算符
struct TernaryExpression_Tag {
    Expression* condition_expression;
    Expression* true_expression;
    Expression* false_expression;
};

struct ArgumentList_Tag {
    ArgumentType type;
    union {
        Ring_BasicValue ring_basic_value; // TODO: 应该把这个删掉，参数应该全都是表达式
        Expression*     expression;
    } u;
    ArgumentList* next;
};

struct Variable_Tag {
    unsigned int line_number;

    char* variable_identifer;
    int   is_const;

    VariableType type;
    VariableType array_member_type; // 数组里的内置类型

    union {
        Ring_BasicValue* ring_basic_value;
    } u;
    Expression* init_expression;
    Variable*   next;
};

struct Declaration_Tag {
    unsigned int line_number;

    TypeSpecifier* type;
    char*          identifier;
    Expression*    initializer;
    int            is_const;
    int            is_local;
    int            variable_index;
    Declaration*   next;
};

struct Function_Tag {
    unsigned int line_number;

    char*        function_name;
    FunctionType type;

    unsigned int parameter_list_size;
    Variable*    parameter_list;

    unsigned int        return_list_size;
    FunctionReturnList* return_list;

    unsigned int variable_list_size;
    Variable*    variable_list;

    // unsigned int return_list_size;
    // return_list; // TODO:

    unsigned int block_size;
    Statement*   block;

    Ring_InnerFunc* inner_func;

    Function* next;
};

struct FunctionReturnList_Tag {
    VariableType        variable_type;
    FunctionReturnList* next;
};

struct IfStatement_Tag {
    unsigned int line_number;

    Expression* condition_expression;

    unsigned int if_block_size;
    Statement*   if_block;

    unsigned int     elseif_statement_size; // TODO: 以后在 create_ast 中更新这个值
    ElseIfStatement* elseif_statement_list;

    // unsigned int else_block_size; // 这个删掉。只能是 1
    Statement* else_block;
};

struct ElseIfStatement_Tag {
    unsigned int line_number;

    Expression* condition_expression; // TODO: 这个名字得改一下 conidtion_expression;

    unsigned int elseif_block_size;
    Statement*   elseif_block;

    ElseIfStatement* next;
};

struct ForStatement_Tag {
    unsigned int line_number;

    Expression* init_expression;
    Expression* condition_expression;
    Expression* post_expression;

    unsigned int block_size;
    Statement*   block;
};

struct DoForStatement_Tag {
    unsigned int line_number;

    Expression*  init_expression;
    unsigned int block_size;
    Statement*   block;
    Expression*  condition_expression;
    Expression*  post_expression;
};

struct DoWhileStatement_Tag {
    unsigned int line_number;

    Expression* condition_expression;

    unsigned int block_size;
    Statement*   block;
};

struct BreakStatement_Tag {
    unsigned int line_number;
};

struct ContinueStatement_Tag {
    unsigned int line_number;
};


typedef enum {
    RING_BASIC_TYPE_UNKNOW,
    RING_BASIC_TYPE_BOOL,
    RING_BASIC_TYPE_INT,
    RING_BASIC_TYPE_DOUBLE,
    RING_BASIC_TYPE_STRING,
    RING_BASIC_TYPE_NULL,
} Ring_BasicType;

typedef enum {
    RING_DERIVE_TYPE_UNKNOW,
    RING_DERIVE_TYPE_FUNCTION,
    RING_DERIVE_TYPE_ARRAY,
} Ring_DeriveTypeKind;

struct Ring_DeriveType_Tag {
    Ring_DeriveTypeKind kind;
    Ring_DeriveType*    next;
};

struct TypeSpecifier_Tag {
    Ring_BasicType   basic_type;
    Ring_DeriveType* derive_type;
};

typedef enum {
    ERROR_CODE_SUCCESS,
    ERROR_CODE_COMPILE_ERROR,          // 编译错误
    ERROR_CODE_SEMANTIC_CHECH_ERROR,   // 语义分析错误
    ERROR_CODE_OPTIMIZATION_AST_ERROR, // 优化AST错误
    ERROR_CODE_GENERATE_OPCODE_ERROR,  // 生成虚拟机代码错误
    ERROR_CODE_LOAD_OPCODE_ERROR,      // 加载虚拟机代码错误
    ERROR_CODE_RUN_VM_ERROR,           // 虚拟机执行失败
} ErrorCode;

struct ErrorMessageInfo {
    ErrorCode error_code;
    char*     error_messaage;
};

#define CLEAR_SCREEN printf("\e[1;1H\e[2J")

#define MOVE_CURSOR(row, col) printf("%c[%d;%dH", 27, (row), (col))

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
#define LOG_COLOR_DARKGREEN "\033[0;36m"
#define LOG_COLOR_WHITE "\033[0;37m"

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
// debug 词法分析
#define debug_log_with_red_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_RED, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
// debug 语法分析
#define debug_log_with_green_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_GREEN, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
// debug 语法分析构建AST
#define debug_log_with_yellow_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_YELLOW, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
// debug 解释执行AST
#define debug_log_with_blue_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_BLUE, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
// debug 生成 vm opcode
#define debug_log_with_purple_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_PURPLE, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
// debug 生成 vm opcode
#define debug_log_with_darkgreen_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_DARKGREEN, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
// debug 生成 vm opcode
#define debug_log_with_white_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_WHITE, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
#else
// 编译错误
#define debug_log_with_red_coloar(format, ...)
// 标示错误的地址
#define debug_log_with_green_coloar(format, ...)
#define debug_log_with_yellow_coloar(format, ...)
#define debug_log_with_blue_coloar(format, ...)
// 编译告警
#define debug_log_with_purple_coloar(format, ...)
#define debug_log_with_darkgreen_coloar(format, ...)
#define debug_log_with_white_coloar(format, ...)
#endif

void         init_current_line_content();
Ring_String* get_current_line_content_string();
Ring_String* new_ring_string();
void         reset_ring_string(Ring_String* string);
void         ring_string_add_char(Ring_String* string, char ch);
char*        get_ring_string(Ring_String* string);

Ring_Compiler* new_ring_compiler(char* file_name);
Ring_Compiler* get_ring_compiler();
void           ring_compiler_compile(Ring_Compiler* ring_compiler, FILE* fp);
char*          get_ring_compiler_current_file_name();
Ring_String*   get_ring_compiler_current_line_content();
unsigned int   get_ring_compiler_line_number();
unsigned int   increase_ring_compiler_line_number();
unsigned int   get_ring_compiler_column_number();
unsigned int   increase_ring_compiler_column_number(unsigned int len);
void           ring_compiler_update_line_content(char* str);
void           ring_compiler_reset_current_line_content();
char*          ring_compiler_get_current_line_content();
void           reset_ring_compiler_column_number();
int            ring_compiler_init_statement_list(Statement* statement);
int            ring_compiler_add_statement(Statement* statement);
void           ring_compiler_registe_inner_func();

void  init_string_literal_buffer();
void  reset_string_literal_buffer();
void  string_literal_add_char(char ch);
char* get_string_literal();

void insert_identifier(IdentifierType type, char* name);

int       identifier_check_valid(char* identifier);
Variable* variable_list_add_item(Variable* variable_list, Variable* variable);
Variable* new_variable(VariableType type, char* identifier, Expression* init_expression, int is_const);
Variable* new_variable_array(VariableType type, Expression* size, char* identifier, Expression* init_expression, int is_const);

Identifier*         new_identifier(IdentifierType type, char* name);
Identifier*         identifier_list_add_item(Identifier* identifier_list, Identifier* identifier);
FunctionReturnList* create_function_return_list(VariableType variable_type);
FunctionReturnList* function_return_list_add_item(FunctionReturnList* return_list, VariableType variable_type);
void                check_identifier_valid(char* identifier_name);

void                 ring_interpret(Ring_Compiler* ring_compiler);
StatementExecResult* interpret_statement(Statement* statement, Function* function);
StatementExecResult* interpret_statement_list(Statement* statement, Function* function);
StatementExecResult* interpret_statement_break(BreakStatement* statement, Function* function);
StatementExecResult* interpret_statement_continue(ContinueStatement* statement, Function* function);
StatementExecResult* interpret_statement_return(Statement* statement, Function* function);
StatementExecResult* interpret_statement_if(IfStatement* if_statement, Function* function);
StatementExecResult* interpret_statement_for(ForStatement* for_statement, Function* function);
StatementExecResult* interpret_statement_dowhile(DoWhileStatement* dowhile_statement, Function* function);
Ring_BasicValue*     interpret_expression(Expression* expression, Function* function);
Ring_BasicValue*     search_variable_value(char* identifier, Function* origin_function);
StatementExecResult* invoke_function(FunctionCallExpression* function_call_expression, Function* function);
StatementExecResult* invoke_external_function(Function* function);
Ring_BasicValue*     interpret_variable_expression(char* variable_identifier, Function* function);
Ring_BasicValue*     interpret_array_index_expression(ArrayIndexExpression* expression, Function* function);
Ring_BasicValue*     interpret_binary_expression_arithmetic(Expression* expression, Function* origin_function);
Ring_BasicValue*     interpret_binary_expression_realational(Expression* expression, Function* function);
Ring_BasicValue*     interpret_binary_expression_logical(Expression* expression, Function* function);
Ring_BasicValue*     interpret_ternary_condition_expression(Expression* expression, Function* origin_function);
Ring_BasicValue*     interpret_binary_expression(Expression* expression, Function* origin_function);
Ring_BasicValue*     interpret_unitary_expression(Expression* expression, Function* origin_function);
Ring_BasicValue*     interpret_unitary_expression_(Expression* expression, Function* origin_function);
void                 interpret_assign_expression(Expression* expression, Function* function);
void                 assign_identifier(Variable* variable, Ring_BasicValue* new_value, AssignExpressionType type);
Variable*            search_variable(char* variable_identifier, Function* function);

// 上下文相关语义检查
int ring_semantic_check(Ring_Compiler* ring_compiler);

void                    create_statement_list(Statement* statement);
void                    statement_list_add_item(Statement* statement);
Statement*              statement_list_add_item2(Statement* statement);
Statement*              statement_list_add_item3(Statement* statement_list, Statement* statement);
Statement*              create_statemen_from_expression(Expression* expression);
Statement*              create_statement_from_variable(Variable* variable);
Statement*              create_return_statement(Expression* expression);
void                    add_function_definition(Function* function_definition);
Expression*             create_expression();
Expression*             create_expression_identifier(char* identifier);
Expression*             create_expression_identifier_with_index(char* identifier, Expression* index);
Expression*             create_expression_(FunctionCallExpression* function_call_expression);
Expression*             create_expression__(AssignExpression* assign_expression);
Expression*             create_expression_ternary(Expression* condition, Expression * true, Expression * false);
Expression*             create_expression_binary(ExpressionType type, Expression* left, Expression* right);
Expression*             create_expression_unitary(ExpressionType type, Expression* unitary_expression);
Expression*             create_expression_unitary_with_convert_type(BasicValueType convert_type, Expression* expression);
Expression*             create_expression_literal(ExpressionType type, char* literal_interface);
Expression*             create_expression_bool_literal(ExpressionType type, Ring_Bool value);
AssignExpression*       create_assign_expression(AssignExpressionType type, Expression* left, Expression* operand);
AssignExpression*       create_multi_assign_expression(char* first_identifier, Identifier* identifier_list, Expression* first_expression, Expression* expression_list);
FunctionCallExpression* create_function_call_expression(char* identifier, ArgumentList* argument_list);
Expression*             expression_list_add_item(Expression* expression_list, Expression* expression);
ArgumentList*           argument_list_add_item3(ArgumentList* argument_list, ArgumentList* argument);
ArgumentList*           create_argument_list(char* argument);
ArgumentList*           create_argument_list_from_expression(Expression* expression);
Identifier*             new_identifier(IdentifierType type, char* name);
Function*               new_function_definition(FunctionType type, char* identifier, Variable* parameter_list, FunctionReturnList* return_list, Statement* block);
Statement*              create_statement_from_if(IfStatement* if_statement);
IfStatement*            create_if_statement(Expression* expression, Statement* if_block, ElseIfStatement* elseif_statement_list, Statement* else_block);
ElseIfStatement*        create_elseif_statement(Expression* expression, Statement* elseif_block);
ElseIfStatement*        elseif_statement_add_item(ElseIfStatement* list, ElseIfStatement* elseif_statement);
Statement*              create_statement_from_for(ForStatement* for_statement);
ForStatement*           create_for_statement(Expression* init_expression, Expression* condition_expression, Expression* post_expression, Statement* block);
Statement*              create_statement_from_dofor(DoForStatement* dofor_statement);
DoForStatement*         create_dofor_statement(Expression* init_expression, Statement* block, Expression* condition_expression, Expression* post_expression);
Statement*              create_statement_from_dowhile(DoWhileStatement* dowhile_statement);
DoWhileStatement*       create_dowhile_statement(Statement* block, Expression* condition_expression);
Statement*              create_statement_from_break();
Statement*              create_statement_from_continue();
// Identifier *            create_identifier(IdentifierType type, char *name);
// char **identifier_list_add_item(char **identifier_list, char *identifier);

TypeSpecifier* create_type_specifier(Ring_BasicType basic_type);
Declaration*   create_declaration(TypeSpecifier* type, char* identifier, Expression* initializer);
Declaration*   declaration_list_add_item(Declaration* head, Declaration* declaration);
Statement*     create_declaration_statement(TypeSpecifier* type_specifier, char* identifier, Expression* initializer);
// create_ast.c

// fix.c
void         ring_compiler_fix_ast(Ring_Compiler* ring_compiler);
void         fix_statement_list(Statement* statement_list);
void         fix_statement(Statement* statement);
void         fix_expression(Expression* expression);
void         fix_declaration(Declaration* declaration);
void         fix_if_statement(IfStatement* if_statement);
void         fix_for_statement(ForStatement* for_statement);
void         fix_dofor_statement(DoForStatement* dofor_statement);
void         fix_identifier_expression(IdentifierExpression* expression);
void         fix_assign_expression(AssignExpression* expression);
void         fix_binary_expression(BinaryExpression* expression);
Declaration* search_declaration(char* identifier);

// generate.c
Ring_VirtualMachine_Executer* new_ring_vm_executer();

void              ring_generate_vm_code(Ring_Compiler* ring_compiler, Ring_VirtualMachine_Executer* ring_executer);
void              add_global_variable(Ring_Compiler* ring_compiler, Ring_VirtualMachine_Executer* executer);
void              add_functions(Ring_Compiler* ring_compiler, Ring_VirtualMachine_Executer* executer);
void              add_top_level_code(Ring_Compiler* ring_compiler, Ring_VirtualMachine_Executer* executer);
void              vm_executer_dump(Ring_VirtualMachine_Executer* vm_executer);
RVM_OpcodeBuffer* new_opcode_buffer();
void              generate_vmcode_from_statement_list(Ring_VirtualMachine_Executer* vm_executer, Statement* statement_list, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_if_statement(Ring_VirtualMachine_Executer* executer, IfStatement* if_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_for_statement(Ring_VirtualMachine_Executer* executer, ForStatement* for_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_dofor_statement(Ring_VirtualMachine_Executer* executer, DoForStatement* dofor_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_assign_expression(Ring_VirtualMachine_Executer* executer, AssignExpression* expression, RVM_OpcodeBuffer* new_opcode_buffer);
void              generate_pop_to_leftvalue(Ring_VirtualMachine_Executer* executer, IdentifierExpression* identifier_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_binary_expression(Ring_VirtualMachine_Executer* executer, BinaryExpression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode);
void              generate_vmcode_from_identifier_expression(Ring_VirtualMachine_Executer* executer, IdentifierExpression* identifier_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_bool_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_int_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_double_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_string_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode(Ring_VirtualMachine_Executer* executer, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode, unsigned int int_literal);

int constant_pool_grow(Ring_VirtualMachine_Executer* executer, unsigned int growth_size);
int constant_pool_add_int(Ring_VirtualMachine_Executer* executer, int int_literal);
int constant_pool_add_double(Ring_VirtualMachine_Executer* executer, double double_literal);
int constant_pool_add_string(Ring_VirtualMachine_Executer* executer, char* string_literal);


unsigned int opcode_buffer_get_label(RVM_OpcodeBuffer* opcode_buffer);
void         opcode_buffer_set_label(RVM_OpcodeBuffer* opcode_buffer, unsigned int label, unsigned int label_address);
void         opcode_buffer_fix_label(RVM_OpcodeBuffer* opcode_buffer);
// generate.c

// execute.c
RVM_RuntimeStack*    new_runtime_stack();
Ring_VirtualMachine* new_ring_virtualmachine();
void                 add_static_variable(Ring_VirtualMachine_Executer* executer, RVM_RuntimeStatic* runtime_static);
void                 ring_execute_vm_code(Ring_VirtualMachine* ring_vm);
void                 debug_rvm(Ring_VirtualMachine* rvm);
void                 dump_runtime_stack(RVM_RuntimeStack* runtime_stack);
// execute.c

// utils.c
void ring_vm_constantpool_dump(Ring_VirtualMachine_Executer* executer);
void ring_vm_code_dump(Ring_VirtualMachine_Executer* executer, unsigned int pc, unsigned int screen_row, unsigned int screen_col);
void ring_vm_dump_runtime_stack(RVM_RuntimeStack* runtime_stack, unsigned int screen_row, unsigned int screen_col);
// utils.c

#endif
