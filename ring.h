#ifndef RING_INCLUDE_H
#define RING_INCLUDE_H

#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

#define RING_VERSION "ring-v0.2.0-beta"

typedef struct Ring_Compiler Ring_Compiler;

typedef struct Ring_VirtualMachine Ring_VirtualMachine;

typedef struct ImportPackageInfo ImportPackageInfo;

typedef struct CompilerEntry CompilerEntry;

typedef struct ExecuterEntry ExecuterEntry;

typedef struct Package_Executer Package_Executer;

typedef struct Package Package;

typedef struct PackageUnit PackageUnit;

typedef struct RVM_Variable RVM_Variable;

typedef struct RVM_RuntimeStack RVM_RuntimeStack;

typedef struct RVM_RuntimeStatic RVM_RuntimeStatic;

typedef struct RVM_RuntimeHeap RVM_RuntimeHeap;

typedef struct RVM_OpcodeBuffer RVM_OpcodeBuffer;

typedef struct RVM_Opcode_Info RVM_Opcode_Info;

typedef struct RVM_LabelTable RVM_LabelTable;

typedef struct Ring_String Ring_String;

typedef struct Ring_BasicValue Ring_BasicValue;

typedef struct Ring_Array Ring_Array;

typedef struct ClassDefinition ClassDefinition;

typedef struct ClassMemberDeclaration ClassMemberDeclaration;

typedef struct FieldMember FieldMember;

typedef struct MethodMember MethodMember;

typedef struct Statement Statement;

typedef struct StatementExecResult StatementExecResult;

typedef struct Expression Expression;

typedef struct ArrayIndexExpression ArrayIndexExpression;

typedef struct CastExpression CastExpression;

typedef struct MemberExpression MemberExpression;

typedef struct DotExpression DotExpression;

typedef struct BinaryExpression BinaryExpression;

typedef struct TernaryExpression TernaryExpression;

typedef struct FunctionCallExpression FunctionCallExpression;

typedef struct MethodCallExpression MethodCallExpression;

typedef struct AssignExpression AssignExpression;

typedef struct ArgumentList ArgumentList;

typedef struct Variable Variable;

typedef struct Parameter Parameter;

typedef struct Identifier Identifier;

typedef struct Function Function;

typedef struct Block Block;

typedef struct FunctionReturnList FunctionReturnList;

typedef struct IfStatement IfStatement;

typedef struct ElseIfStatement ElseIfStatement;

typedef struct ForStatement ForStatement;

typedef struct DoForStatement DoForStatement;

typedef struct BreakStatement BreakStatement;

typedef struct ReturnStatement ReturnStatement;

typedef struct ContinueStatement ContinueStatement;

typedef struct Ring_DeriveType_Class Ring_DeriveType_Class;

typedef struct Ring_DeriveType Ring_DeriveType;

typedef struct Declaration Declaration;

typedef struct TypeSpecifier TypeSpecifier;

typedef struct StdPackageNativeFunction StdPackageNativeFunction;

typedef struct StdPackageInfo StdPackageInfo;

typedef struct RVM_DebugConfig RVM_DebugConfig;

typedef struct IdentifierExpression IdentifierExpression;

typedef struct AttributeInfo AttributeInfo;

typedef struct RVM_ConstantPool RVM_ConstantPool;

typedef struct RVM_String      RVM_String;
typedef struct RVM_Array       RVM_Array;
typedef struct RVM_ClassObject RVM_ClassObject;
typedef struct RVM_Object      RVM_Object;

typedef void Ring_InnerFunc(int argc, Ring_BasicValue** value);

typedef struct RVM_LocalVariable RVM_LocalVariable;
typedef struct NativeFunction    NativeFunction;
typedef struct DeriveFunction    DeriveFunction;
typedef struct RVM_Function      RVM_Function;
typedef struct RVM_Field         RVM_Field;
typedef struct RVM_Method        RVM_Method;
typedef struct RVM_Class         RVM_Class;

struct Ring_Compiler {
    /*
    char*        current_file_name;
    unsigned int current_line_number;
    unsigned int current_column_number;
    Ring_String* current_line_content;

    unsigned int    import_package_size;
    ImportPackageInfo*    import_package_list;

    unsigned int statement_list_size;
    Statement*   statement_list;

    unsigned int function_list_size;
    Function*    function_list;

    unsigned int identifier_list_size; // TODO:后续删除调
    Identifier*  identifier_list;      // TODO:后续删除调

    unsigned int declaration_list_size;
    Declaration* declaration_list;

    Block* current_block;

    unsigned int     class_definition_list_size;
    ClassDefinition* class_definition_list;

    unsigned int compile_error_num;
    */
};

typedef unsigned char RVM_Byte;

typedef enum {
    RVM_VALUE_TYPE_UNKNOW,

    RVM_VALUE_TYPE_BOOL,
    RVM_VALUE_TYPE_INT,
    RVM_VALUE_TYPE_DOUBLE,
    RVM_VALUE_TYPE_STRING,
    RVM_VALUE_TYPE_OBJECT,
} RVM_Value_Type;

typedef enum {
    RVM_FALSE,
    RVM_TRUE,
} RVM_Bool;

typedef struct {
    RVM_Value_Type type;
    union {
        RVM_Bool    bool_value;
        int         int_value;
        double      double_value;
        RVM_Object* object;
    } u;

} RVM_Value;

struct Ring_VirtualMachine {
    Package_Executer* executer;
    ExecuterEntry*    executer_entry;

    RVM_RuntimeStatic* runtime_static; // TODO: 暂时只支持main包的 全局变量
    RVM_RuntimeStack*  runtime_stack;
    RVM_RuntimeHeap*   runtime_heap;
    unsigned int       pc;

    // RVM_Function* function_list; // TODO: 删除掉
    // unsigned int  function_size; // TODO: 删除掉

    RVM_Class*   class_list; // TODO: 删除掉
    unsigned int class_size; // TODO: 删除掉

    RVM_DebugConfig* debug_config;
};

struct ImportPackageInfo {
    unsigned int line_number;

    char* package_name;
    char* package_path;
    char* rename;
};

struct CompilerEntry {
    // std::unordered_map<std::string, Package*> package_map;
    std::vector<Package*> package_list;
    Package*              main_package;
};

struct ExecuterEntry {
    std::vector<Package_Executer*> package_executer_list;
    Package_Executer*              main_package_executer;
};

struct Package_Executer {
    ExecuterEntry* executer_entry;
    unsigned int   package_index; // 在 ExecuterEntry 中的 index
    char*          package_name;
    // char*          package_path;

    unsigned int      constant_pool_size;
    RVM_ConstantPool* constant_pool_list;

    unsigned int  global_variable_size;
    RVM_Variable* global_variable_list;

    unsigned int  function_size;
    RVM_Function* function_list;

    unsigned int class_size;
    RVM_Class*   class_list;

    unsigned int code_size;
    RVM_Byte*    code_list;

    unsigned int main_func_index;

    unsigned int estimate_runtime_stack_capacity;
};

// Pacage 对应一个源代码的逻辑包  也就是一个路径
// 其实它就是 就是将 PackageUnit 打包在一块
struct Package {
    CompilerEntry* compiler_entry;
    unsigned int   package_index; // 在 CompilerEntry 中的 index
    char*          package_name;
    char*          package_path;

    std::vector<std::string> source_file_list;

    std::vector<Declaration*> global_declaration_list; // global变量 TODO:以后不使用 declaration_list
    // TODO: 保留 global_declaration_list 删除 declaration_list
    std::vector<Declaration*>     declaration_list;
    std::vector<ClassDefinition*> class_definition_list;
    std::vector<Function*>        function_list;
    unsigned int                  statement_list_size; // TODO: delete 只能在函数内写语句
    Statement*                    statement_list;      // TODO: delete 只能在函数内写语句

    std::vector<PackageUnit*> package_unit_list;
};

// 一个Package 有多个 编译单元
// 也就是一个包内有多个Ring源码文件
// 一个编译单元 对应一个Ring源码文件
struct PackageUnit {
    Package* parent_package;

    std::string  current_file_name;
    FILE*        current_file_fp;
    unsigned int current_line_number;
    unsigned int current_column_number;
    Ring_String* current_line_content;

    std::vector<ImportPackageInfo*> import_package_list;

    unsigned int              global_block_statement_list_size;
    Statement*                global_block_statement_list;
    std::vector<Declaration*> global_declaration_list; // global变量 TODO:以后不使用 declaration_list
    // TODO: 保留 global_declaration_list 删除 declaration_list
    unsigned int declaration_list_size;
    Declaration* declaration_list;

    std::vector<ClassDefinition*> class_definition_list;
    std::vector<Function*>        function_list;

    unsigned int statement_list_size; // TODO: 删除
    Statement*   statement_list;      // TODO: 删除

    Block* current_block;

    unsigned int compile_error_num;
};


typedef RVM_Value RVM_NativeFuncProc(Ring_VirtualMachine* rvm, unsigned int arg_cout, RVM_Value* args);

typedef enum {
    RVM_FUNCTION_TYPE_UNKNOW,
    RVM_FUNCTION_TYPE_NATIVE, // 原生函数
    RVM_FUNCTION_TYPE_DERIVE, // 派生函数，库函数，Ring编写的库函数
} RVMFunctionType;

struct RVM_LocalVariable {
    char* identifier;
    // TODO:
};

struct NativeFunction {
    RVM_NativeFuncProc* func_proc;
    int                 arg_count; // -1 表示可变参数
};
struct DeriveFunction {
    unsigned int code_size;
    RVM_Byte*    code_list;


    unsigned int local_variable_size;
};
struct RVM_Function {
    char*           func_name;
    RVMFunctionType type;

    unsigned int       parameter_size;
    RVM_LocalVariable* parameter_list;

    unsigned int       local_variable_size;
    RVM_LocalVariable* local_variable_list;

    union {
        NativeFunction* native_func;
        DeriveFunction* derive_func;
    } u;

    unsigned int estimate_runtime_stack_capacity;
};

struct RVM_Field {
    char* identifier;
};

// 他的本质就是一个 函数
// 只不过他可以引用 field
struct RVM_Method {
    char*         identifier;
    RVM_Function* rvm_function;
};

struct RVM_Class {
    char* identifier;

    unsigned int field_size;
    RVM_Field*   field_list;

    unsigned int method_size;
    RVM_Method*  method_list;
};

// generate.c

typedef enum {
    CONSTANTPOOL_TYPE_UNKNOW,
    CONSTANTPOOL_TYPE_INT,
    CONSTANTPOOL_TYPE_DOUBLE,
    CONSTANTPOOL_TYPE_STRING,
} ConstantPoolType;

struct RVM_ConstantPool {
    ConstantPoolType type;
    union {
        int    int_value;
        double double_value;
        char*  string_value;
    } u;
};

struct RVM_Variable {
    char*          identifier;
    TypeSpecifier* type;
};


typedef enum {
    RVM_OBJECT_TYPE_UNKNOW,
    RVM_OBJECT_TYPE_STRING,
    RVM_OBJECT_TYPE_ARRAY,
    RVM_OBJECT_TYPE_CLASS,
} RVM_Object_Type;


struct RVM_String {
    // TODO:
    char* data;
};

struct RVM_Array {
    // TODO:
    unsigned int i;
};

struct RVM_ClassObject {
    ClassDefinition* class_def;
    unsigned int     field_count;
    RVM_Value*       field;
};

struct RVM_Object {
    RVM_Object_Type type;
    union {
        RVM_String      string;
        RVM_Array       array;
        RVM_ClassObject class_object;
    } u;
};

// 支持线性寻址
struct RVM_RuntimeStack {
    RVM_Value*   data;
    unsigned int top_index;
    unsigned int size;
    unsigned int capacity;
};

struct RVM_RuntimeStatic {
    RVM_Value*   data;
    unsigned int size;
    unsigned int capacity;
};

struct RVM_RuntimeHeap {
    // TODO: 稍后实现
    unsigned int i;
};

struct RVM_LabelTable {
    char*        label_name;
    unsigned int label_address;
};

typedef struct {
    char*        source_file_name;
    unsigned int line_number; // 对应Ring源代码文件的行数

    unsigned int opcode_begin_index; // 对应 opcode 的 开始索引
    unsigned int opcode_size;        // 一行Ring源代码 对应 opcode size
} RVM_SourceCodeLineMap;

struct RVM_OpcodeBuffer {
    RVM_Byte*    code_list;
    unsigned int code_size;
    unsigned int code_capacity;

    RVM_LabelTable* lable_list;
    unsigned int    lable_size;
    unsigned int    lable_capacity;

    RVM_SourceCodeLineMap* code_line_map;
    unsigned int           code_line_size;
};

typedef enum {
    OPCODE_OPERAND_TYPE_UNKNOW,
    OPCODE_OPERAND_TYPE_0BYTE, // 后边没有操作数
    OPCODE_OPERAND_TYPE_1BYTE,
    OPCODE_OPERAND_TYPE_2BYTE,
} OpcodeOperandType;

struct RVM_Opcode_Info {
    RVM_Byte          code;                    // 字节码枚举
    std::string       name;                    // 字节码字符串
    OpcodeOperandType type;                    // 操作数的类型
    int               runtime_stack_increment; // 对运行时栈空间的增长 可为负值
    int               pc_increment;            // 读取完本字节码，程序计数器的增长 ，便于读取下一字节码
    // 有的指令 pc_increment 是可以确定的
    // 有的指令 类似于 jump  只能运行时确定，所以会先配置0
};

typedef enum {
    RVM_CODE_UNKNOW = 0,

    // int double string const
    RVM_CODE_PUSH_BOOL,
    RVM_CODE_PUSH_INT_1BYTE, // operand 0-255
    RVM_CODE_PUSH_INT_2BYTE, // operand 256-65535
    RVM_CODE_PUSH_INT,       // bigger 65535
    RVM_CODE_PUSH_DOUBLE,
    RVM_CODE_PUSH_STRING,

    // static
    RVM_CODE_POP_STATIC_BOOL,
    RVM_CODE_POP_STATIC_INT,
    RVM_CODE_POP_STATIC_DOUBLE,
    RVM_CODE_POP_STATIC_OBJECT,
    RVM_CODE_PUSH_STATIC_BOOL,
    RVM_CODE_PUSH_STATIC_INT,
    RVM_CODE_PUSH_STATIC_DOUBLE,
    RVM_CODE_PUSH_STATIC_OBJECT,


    // stack
    RVM_CODE_POP_STACK_BOOL,
    RVM_CODE_POP_STACK_INT,
    RVM_CODE_POP_STACK_DOUBLE,
    RVM_CODE_POP_STACK_OBJECT,
    RVM_CODE_PUSH_STACK_BOOL,
    RVM_CODE_PUSH_STACK_INT,
    RVM_CODE_PUSH_STACK_DOUBLE,
    RVM_CODE_PUSH_STACK_OBJECT,


    // class
    RVM_CODE_POP_FIELD_BOOL,
    RVM_CODE_POP_FIELD_INT,
    RVM_CODE_POP_FIELD_DOUBLE,
    RVM_CODE_PUSH_FIELD_BOOL,
    RVM_CODE_PUSH_FIELD_INT,
    RVM_CODE_PUSH_FIELD_DOUBLE,

    // arithmetic
    RVM_CODE_ADD_INT,
    RVM_CODE_ADD_DOUBLE,

    RVM_CODE_SUB_INT,
    RVM_CODE_SUB_DOUBLE,

    RVM_CODE_MUL_INT,
    RVM_CODE_MUL_DOUBLE,

    RVM_CODE_DIV_INT,
    RVM_CODE_DIV_DOUBLE,

    RVM_CODE_MOD_INT,
    RVM_CODE_MOD_DOUBLE,

    RVM_CODE_MINUS_INT,
    RVM_CODE_MINUS_DOUBLE,

    RVM_CODE_INCREASE_SUFFIX,
    RVM_CODE_INCREASE_PREFIX,
    RVM_CODE_DECREASE_SUFFIX,
    RVM_CODE_DECREASE_PREFIX,

    RVM_CODE_CONCAT,

    // type cast
    RVM_CODE_CAST_BOOL_TO_INT,
    RVM_CODE_CAST_INT_TO_DOUBLE,

    RVM_CODE_CAST_INT_TO_BOOL,
    RVM_CODE_CAST_DOUBLE_TO_INT,

    // logical
    RVM_CODE_LOGICAL_AND,
    RVM_CODE_LOGICAL_OR,
    RVM_CODE_LOGICAL_NOT,

    // relational
    RVM_CODE_RELATIONAL_EQ_INT,
    RVM_CODE_RELATIONAL_EQ_DOUBLE,
    RVM_CODE_RELATIONAL_EQ_STRING,

    RVM_CODE_RELATIONAL_NE_INT,
    RVM_CODE_RELATIONAL_NE_DOUBLE,
    RVM_CODE_RELATIONAL_NE_STRING,

    RVM_CODE_RELATIONAL_GT_INT,
    RVM_CODE_RELATIONAL_GT_DOUBLE,
    RVM_CODE_RELATIONAL_GT_STRING,

    RVM_CODE_RELATIONAL_GE_INT,
    RVM_CODE_RELATIONAL_GE_DOUBLE,
    RVM_CODE_RELATIONAL_GE_STRING,

    RVM_CODE_RELATIONAL_LT_INT,
    RVM_CODE_RELATIONAL_LT_DOUBLE,
    RVM_CODE_RELATIONAL_LT_STRING,

    RVM_CODE_RELATIONAL_LE_INT,
    RVM_CODE_RELATIONAL_LE_DOUBLE,
    RVM_CODE_RELATIONAL_LE_STRING,

    // jump
    RVM_CODE_JUMP,
    RVM_CODE_JUMP_IF_FALSE,
    RVM_CODE_JUMP_IF_TRUE,

    // duplicate
    RVM_CODE_DUPLICATE,

    // func
    RVM_CODE_PUSH_FUNC,
    RVM_CODE_PUSH_METHOD,
    RVM_CODE_ARGUMENT_NUM,
    RVM_CODE_INVOKE_FUNC,
    RVM_CODE_INVOKE_METHOD,
    RVM_CODE_RETURN,
    RVM_CODE_FUNCTION_FINISH,

    RVM_CODE_EXIT,

    // 不能在生成代码的时候使用
    RVM_CODES_NUM, // 用来标记RVM CODE 的数量
} RVM_Opcode;

typedef enum {
    BOOL_FALSE = 0,
    BOOL_TRUE  = 1
} Ring_Bool;

typedef enum {
    IDENTIFIER_TYPE_UNKNOW = 0,
    IDENTIFIER_TYPE_VARIABLE,
    IDENTIFIER_TYPE_VARIABLE_ARRAY,
    IDENTIFIER_TYPE_FUNCTION,
} IdentifierType;

typedef struct {
    unsigned int  magic_number;
    RVM_Function* caller_function;
    unsigned int  caller_pc; // 调用者的返回地址
    unsigned int  caller_stack_base;
    unsigned int  callee_argument_size; // 函数调用的参数数量，可变参数
} RVM_CallInfo;

#define CALL_INFO_MAGIC_NUMBER (0x8421) // 33852
#define CALL_INFO_SIZE ((sizeof(RVM_CallInfo) - 1) / sizeof(RVM_Value) + 1)

struct Ring_String {
    char* buffer;
    int   size;
    int   capacity;
};

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
    STATEMENT_TYPE_IF,
    STATEMENT_TYPE_FOR,
    STATEMENT_TYPE_DOFOR,
    STATEMENT_TYPE_BREAK,
    STATEMENT_TYPE_CONTINUE,
    STATEMENT_TYPE_RETURN,
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
    EXPRESSION_TYPE_METHOD_CALL,
    EXPRESSION_TYPE_ASSIGN,

    EXPRESSION_TYPE_TERNARY, // 三目运算

    EXPRESSION_TYPE_CONCAT,
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

    EXPRESSION_TYPE_CAST,
    EXPRESSION_TYPE_MEMBER,
    EXPRESSION_TYPE_DOT,
} ExpressionType;

typedef enum {
    VARIABLE_TYPE_UNKNOW = 0,
    VARIABLE_TYPE_BOOL,
    VARIABLE_TYPE_INT,
    VARIABLE_TYPE_DOUBLE,
    VARIABLE_TYPE_STRING,
    VARIABLE_TYPE_ARRAY,
    VARIABLE_TYPE_CLASS,
} VariableType;

typedef enum {
    FUNCTION_TYPE_UNKNOW = 0,
    FUNCTION_TYPE_NATIVE,
    FUNCTION_TYPE_DERIVE,
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
    ASSIGN_EXPRESSION_TYPE_ASSIGN,        // =
    ASSIGN_EXPRESSION_TYPE_MULTI_ASSIGN,  // a, b = 1, 2
    ASSIGN_EXPRESSION_TYPE_ADD_ASSIGN,    // +=
    ASSIGN_EXPRESSION_TYPE_SUB_ASSIGN,    // -=
    ASSIGN_EXPRESSION_TYPE_MUL_ASSIGN,    // *=
    ASSIGN_EXPRESSION_TYPE_DIV_ASSIGN,    // /=
    ASSIGN_EXPRESSION_TYPE_MOD_ASSIGN,    // %=
    ASSIGN_EXPRESSION_TYPE_CONCAT_ASSIGN, // .=
} AssignExpressionType;

struct Ring_BasicValue {
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

struct Ring_Array {
    unsigned int     size;
    Ring_BasicValue* data;
};

// ----------------------------------
// class define
// ----------------------------------


struct ClassDefinition {
    unsigned int line_number;

    unsigned int            class_index;
    char*                   class_identifier;
    ClassMemberDeclaration* member;

    ClassDefinition* next;
};

typedef enum {
    ATTRIBUTE_NONE = 0,
    ACCESS_PUBLIC  = 0x01,
    ACCESS_PRIVATE = 0x01 << 1,
    ACCESS_DELETE  = 0x01 << 2,

    CONSTRUCTOR = 0x01 << 4,
    DESTRUCTOR  = 0x01 << 5,
} AttributeType;

typedef unsigned int Attribute;

struct AttributeInfo {
    char*          name;
    AttributeInfo* next;
};

typedef enum {
    MEMBER_UNKNOW = 0,
    MEMBER_FIELD,
    MEMBER_METHOD,
} ClassMemberType;

struct ClassMemberDeclaration {
    unsigned int line_number;

    Attribute       attribute;
    ClassMemberType type;
    union {
        FieldMember*  field;
        MethodMember* method;
    } u;

    ClassMemberDeclaration* next;
};

// 类成员变量
struct FieldMember {
    unsigned int line_number;

    unsigned int   index_of_class; // fix it in fix_ast
    TypeSpecifier* type;
    char*          identifier;
};

// 类方法
struct MethodMember {
    unsigned int line_number;

    unsigned int index_of_class; // fix it in fix_ast
    char*        identifier;

    unsigned int parameter_list_size;
    Parameter*   parameter_list;

    unsigned int        return_list_size;
    FunctionReturnList* return_list;

    Block* block;
};


// ----------------------------------
// class define
// ----------------------------------

struct Statement {
    unsigned int line_number;

    StatementType type;
    union {
        Expression*        expression;
        Variable*          variable; // TODO: 以后废弃 使用 declaration_statement
        IfStatement*       if_statement;
        ForStatement*      for_statement;
        DoForStatement*    dofor_statement;
        BreakStatement*    break_statement;
        ContinueStatement* continue_statement;
        ReturnStatement*   return_statement;
        Declaration*       declaration_statement;
    } u;
    Statement* next;
};

struct StatementExecResult {
    StatementExecResultType type;
    union {
        Ring_BasicValue* return_value;
    } u; // TODO: 这个没办法兼容多 返回值，重构的时候废弃，使用return_value_list_size & return_value_list
    unsigned int      return_value_list_size;
    Ring_BasicValue** return_value_list;
};

struct Expression {
    unsigned int line_number;

    char*          package_posit;
    TypeSpecifier* convert_type; // 一个复杂表达式最后结果值的类型, FIX_AST_UPDATE
    ExpressionType type;
    union {
        Ring_Bool               bool_literal;
        int                     int_literal;
        double                  double_literal;
        char*                   string_literal;
        IdentifierExpression*   identifier_expression;
        FunctionCallExpression* function_call_expression;
        MethodCallExpression*   method_call_expression;
        AssignExpression*       assign_expression;
        TernaryExpression*      ternary_expression;
        BinaryExpression*       binary_expression;
        Expression*             unitary_expression;
        ArrayIndexExpression*   array_index_expression;
        CastExpression*         cast_expression;
        MemberExpression*       member_expression;
        DotExpression*          dot_expression;
    } u;

    Expression* next;
};

typedef enum {
    IDENTIFIER_EXPRESSION_TYPE_UNKNOW,
    IDENTIFIER_EXPRESSION_TYPE_VARIABLE,
    IDENTIFIER_EXPRESSION_TYPE_VARIABLE_ARRAY,
    IDENTIFIER_EXPRESSION_TYPE_FUNCTION,
} IdentifierExpressionType;

struct IdentifierExpression {
    unsigned int line_number;

    char* package_posit;

    IdentifierExpressionType type;
    char*                    identifier;
    union {
        Declaration* declaration;
        Function*    function;
    } u;
};

struct ArrayIndexExpression {
    unsigned int line_number;

    char*       variable_identifier;
    Expression* index_expression;
};

// TODO: 这里应该是设计重复了 应该跟 basic type一致
// 统一
typedef enum {
    CAST_TYPE_UNKNOW,

    CAST_TYPE_TO_BOOL,
    CAST_TYPE_TO_INT,
    CAST_TYPE_TO_DOUBLE,
    CAST_TYPE_TO_STRING,
} CastType;

struct CastExpression {
    unsigned int line_number;

    TypeSpecifier* type;
    Expression*    operand;
};

struct MemberExpression {
    unsigned int line_number;

    Expression*             object_expression;
    char*                   member_identifier;
    ClassMemberDeclaration* member_declaration; // FIX_AST_UPDATE

    // e.g.
    // var Job job1;
    // job1.JobID;
    // job1 is object_expression
    // JobID is member_identifier
    // JobID is member_declaration
};

struct DotExpression {
    unsigned int line_number;

    Expression* prefix_expression;
    Expression* suffix_expression;

    // e.g.
    // object.member
    // object.member()
    // object -> prefix_expression
    // member -> suffix_expression
};

struct FunctionCallExpression {
    unsigned int line_number;

    char* package_posit;

    Expression*   function_identifier_expression;
    ArgumentList* argument_list;
};

struct MethodCallExpression {
    unsigned int line_number;

    Expression*             object_expression;
    char*                   member_identifier;
    ClassMemberDeclaration* member_declaration; // FIX_AST_UPDATE
    ArgumentList*           argument_list;
};

struct Identifier { // TODO: 以后废弃这个东西
    unsigned int line_number;

    IdentifierType type;
    char*          identifier_name;
    unsigned int   array_index; // 供数组使用，还要考虑一下负值索引的问题

    Function* parent_scope; // 作用域

    Identifier* next;
};

// TODO: 这里还要兼容 数组元素赋值
struct AssignExpression {
    unsigned int line_number;

    AssignExpressionType type;
    Expression*          left;
    Expression*          operand;
};

struct BinaryExpression {
    unsigned int line_number;

    Expression* left_expression;
    Expression* right_expression;
};

// 三元运算符
struct TernaryExpression {
    unsigned int line_number;

    Expression* condition_expression;
    Expression* true_expression;
    Expression* false_expression;
};

struct ArgumentList {
    unsigned int line_number;

    Expression*   expression;
    ArgumentList* next;
};

struct Variable {
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

struct Parameter {
    unsigned int line_number;

    TypeSpecifier* type;
    char*          identifier;
    Parameter*     next;
};

struct Declaration {
    unsigned int line_number;

    TypeSpecifier* type;
    char*          identifier;
    Expression*    initializer;
    int            is_const;
    int            is_local;
    int            variable_index;
    Declaration*   next;
};

typedef enum {
    BLOCK_TYPE_UNKNOW,
    BLOCK_TYPE_IF,
    BLOCK_TYPE_FOR,
    BLOCK_TYPE_DOFOR,
    BLOCK_TYPE_FUNCTION,
    // BLOCK_TYPE_OTHER,
} BlockType;

typedef struct BlockLabels {
    unsigned int break_label;
    unsigned int continue_label;
} BlockLabels;

struct Block {
    unsigned int line_number;

    BlockType type;

    unsigned int declaration_list_size;
    Declaration* declaration_list;

    unsigned int statement_list_size;
    Statement*   statement_list;

    Block* parent_block;

    BlockLabels block_labels;
};

struct Function {
    unsigned int line_number;

    Package* package; // 所属的package

    AttributeInfo* attribute_info;

    unsigned int func_index;

    char*        function_name;
    FunctionType type;

    unsigned int parameter_list_size;
    Parameter*   parameter_list;

    unsigned int        return_list_size;
    FunctionReturnList* return_list;

    Block* block;

    Function* next;
};

struct FunctionReturnList {
    VariableType        variable_type;
    FunctionReturnList* next;
};

struct IfStatement {
    unsigned int line_number;

    Expression* condition_expression;

    Block*           if_block;
    ElseIfStatement* elseif_list;
    Block*           else_block;
};

struct ElseIfStatement {
    unsigned int line_number;

    Expression* condition_expression; // TODO: 这个名字得改一下 conidtion_expression;

    Block* elseif_block;

    ElseIfStatement* next;
};

struct ForStatement {
    unsigned int line_number;

    Expression* init_expression;
    Expression* condition_expression;
    Expression* post_expression;

    Block* block;
};

struct DoForStatement {
    unsigned int line_number;

    Expression* init_expression;
    Block*      block;
    Expression* condition_expression;
    Expression* post_expression;
};


struct BreakStatement {
    unsigned int line_number;

    unsigned int break_loop_num; // break; break 1; break 2;
};

struct ContinueStatement {
    unsigned int line_number;
};

struct ReturnStatement {
    unsigned int line_number;

    unsigned int return_list_size;
    Expression*  return_list;
};


typedef enum {
    RING_BASIC_TYPE_UNKNOW,
    RING_BASIC_TYPE_ANY,
    RING_BASIC_TYPE_BOOL,
    RING_BASIC_TYPE_INT,
    RING_BASIC_TYPE_DOUBLE,
    RING_BASIC_TYPE_STRING,
    RING_BASIC_TYPE_CLASS,
    RING_BASIC_TYPE_NULL,
} Ring_BasicType;

typedef enum {
    RING_DERIVE_TYPE_UNKNOW,
    RING_DERIVE_TYPE_CLASS,
} Ring_DeriveTypeKind;


struct Ring_DeriveType_Class {
    char*            class_identifier;
    ClassDefinition* class_definition; // FIX_AST_UPDATE
};

struct Ring_DeriveType {
    Ring_DeriveTypeKind kind;
    union {
        Ring_DeriveType_Class* class_type;
    } u;
};

struct TypeSpecifier {
    Ring_BasicType   basic_type;
    Ring_DeriveType* derive_type;
};

struct StdPackageNativeFunction {
    char*               func_name;
    RVM_NativeFuncProc* func_proc;
    int                 arg_count;
};

struct StdPackageInfo {
    char* package_name;
    char* path;

    std::vector<StdPackageNativeFunction> native_function_list;
};


typedef enum {
    RVM_DEBUG_MODE_UNKNOW,

    RVM_DEBUG_MODE_STEPINTO,
    RVM_DEBUG_MODE_STEPOVER,
    RVM_DEBUG_MODE_STEPOUT,

} RVM_DebugMode;

struct RVM_DebugConfig {
    RVM_DebugMode debug_mode;
};

typedef enum {
    ERROR_CODE_SUCCESS,

    // 命令行参数错误
    ERROR_CODE_COMMAND_ERROR,

    // 编译错误
    ERROR_CODE_COMPILE_ERROR,

    // 语义分析错误
    ERROR_CODE_SEMANTIC_CHECH_ERROR,

    // 优化AST错误
    ERROR_CODE_OPTIMIZATION_AST_ERROR,


    // 生成虚拟机代码错误
    ERROR_CODE_GENERATE_OPCODE_ERROR,
    ERROR_CODE_FIX_LABEL,
    ERROR_CODE_INVALID_OPCODE,
    ERROR_CODE_INVALID_OPCODE_TYPE,

    // 加载虚拟机代码错误
    ERROR_CODE_LOAD_OPCODE_ERROR,

    // 虚拟机执行失败
    ERROR_CODE_RUN_VM_ERROR,
} ErrorCode;

struct ErrorMessageInfo {
    ErrorCode   error_code;
    std::string error_messaage;
};

typedef enum {
    SYNTAX_VARIABLE_DEFINITION,

} SyntaxType;

struct SyntaxInfo {
    SyntaxType syntax_type;
    char*      bnf;
};

struct BinaryChunk {
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

void           ring_compiler_error(SyntaxType syntax_type, int exit);
CompilerEntry* compiler_entry_create();
CompilerEntry* get_compiler_entry();
void           compiler_entry_dump(CompilerEntry* compiler_entry);
Package*       search_package(CompilerEntry* compiler_entry, char* package_name);
ExecuterEntry* executer_entry_create();
void           executer_entry_dump(ExecuterEntry* executer_entry);
Package*       package_create(CompilerEntry* compiler_entry, char* package_name, char* package_path);
Package*       package_create_input_file(CompilerEntry* compiler_entry, char* package_name, char* input_main_file);
void           package_compile(Package* package);
void           package_dump(Package* package);
void           compile_std_lib(CompilerEntry* compiler_entry, ExecuterEntry* executer_entry);
PackageUnit*   package_unit_create(Package* parent_package, std::string file_name);
PackageUnit*   get_package_unit();
void           package_unit_compile(PackageUnit* package_unit);
void           package_unit_dump(PackageUnit* package_unit);
const char*    package_unit_get_file_name();
Ring_String*   get_package_unit_current_line_content();
unsigned int   package_unit_get_line_number();
unsigned int   package_unit_increa_line_number();
unsigned int   package_unit_get_column_number();
unsigned int   package_unit_increa_column_number(unsigned int len);
void           package_unit_update_line_content(char* str);
void           package_unit_reset_line_content();
char*          package_unit_get_current_line_content();
void           package_unit_reset_column_number();
int            package_unit_add_statement(Statement* statement);
int            package_unit_add_class_definition(ClassDefinition* class_definition);


void  init_string_literal_buffer();
void  reset_string_literal_buffer();
void  string_literal_add_char(char ch);
char* get_string_literal();

Identifier*         new_identifier(IdentifierType type, char* name);
Identifier*         identifier_list_add_item(Identifier* identifier_list, Identifier* identifier);
FunctionReturnList* create_function_return_list(VariableType variable_type);
FunctionReturnList* function_return_list_add_item(FunctionReturnList* return_list, VariableType variable_type);

void                    finish_global_block(Statement* global_statement_list);
Statement*              statement_list_add_item(Statement* statement_list, Statement* statement);
Statement*              create_statemen_from_expression(Expression* expression);
void                    add_function_definition(AttributeInfo* attribute_info, Function* function_definition);
Expression*             expression_add_package_posit(Expression* expression, char* package_posit);
Expression*             create_expression_identifier(char* identifier);
Expression*             create_expression_identifier2(char* identifier, IdentifierExpressionType type);
Expression*             create_expression_identifier_with_index(char* identifier, Expression* index);
Expression*             create_expression_from_function_call(FunctionCallExpression* function_call_expression);
Expression*             create_expression_from_method_call(MethodCallExpression* method_call_expression);
Expression*             create_expression_assign(AssignExpression* assign_expression);
Expression*             create_expression_ternary(Expression* condition, Expression* true_expression, Expression* false_expression);
Expression*             create_expression_binary(ExpressionType type, Expression* left, Expression* right);
Expression*             create_expression_unitary(ExpressionType type, Expression* unitary_expression);
Expression*             create_expression_unitary_with_convert_type(BasicValueType convert_type, Expression* expression);
Expression*             create_expression_literal(ExpressionType type, char* literal_interface);
Expression*             create_expression_bool_literal(ExpressionType type, Ring_Bool value);
Expression*             create_cast_expression(TypeSpecifier* cast_type, Expression* operand);
Expression*             create_member_expression(Expression* object_expression, char* member_identifier);
Expression*             create_dot_expression(Expression* prefix_expression, Expression* suffix_expression);
AssignExpression*       create_assign_expression(AssignExpressionType type, Expression* left, Expression* operand);
AssignExpression*       create_multi_assign_expression(char* first_identifier, Identifier* identifier_list, Expression* operand);
FunctionCallExpression* create_function_call_expression(char* identifier, ArgumentList* argument_list);
MethodCallExpression*   create_method_call_expression(Expression* object_expression, char* member_identifier, ArgumentList* argument_list);
Expression*             expression_list_add_item(Expression* expression_list, Expression* expression);
ArgumentList*           argument_list_add_item3(ArgumentList* argument_list, ArgumentList* argument);
ArgumentList*           create_argument_list_from_expression(Expression* expression);
Identifier*             new_identifier(IdentifierType type, char* name);
Function*               new_function_definition(FunctionType type, char* identifier, Parameter* parameter_list, FunctionReturnList* return_list, Block* block);
Statement*              create_statement_from_if(IfStatement* if_statement);
IfStatement*            create_if_statement(Expression* expression, Block* if_block, ElseIfStatement* elseif_statement_list, Block* else_block);
ElseIfStatement*        create_elseif_statement(Expression* expression, Block* elseif_block);
ElseIfStatement*        elseif_statement_add_item(ElseIfStatement* list, ElseIfStatement* elseif_statement);
Statement*              create_statement_from_for(ForStatement* for_statement);
ForStatement*           create_for_statement(Expression* init_expression, Expression* condition_expression, Expression* post_expression, Block* block);
Statement*              create_statement_from_dofor(DoForStatement* dofor_statement);
DoForStatement*         create_dofor_statement(Expression* init_expression, Block* block, Expression* condition_expression, Expression* post_expression);
Statement*              create_statement_from_break(BreakStatement* break_statement);
BreakStatement*         create_break_statement(char* literal_interface);
Statement*              create_statement_from_continue(ContinueStatement* continue_statement);
ContinueStatement*      create_continue_statement();
Statement*              create_statement_from_return(ReturnStatement* return_statement);
ReturnStatement*        create_return_statement(Expression* expression);
Block*                  start_new_block();
Block*                  finish_block(Block* block, Statement* statement_list);
// Identifier *            create_identifier(IdentifierType type, char *name);
// char **identifier_list_add_item(char **identifier_list, char *identifier);

TypeSpecifier* create_type_specifier(Ring_BasicType basic_type);
Declaration*   create_declaration(TypeSpecifier* type, char* identifier, Expression* initializer);
Declaration*   declaration_list_add_item(Declaration* head, Declaration* declaration);
Statement*     create_declaration_statement(TypeSpecifier* type_specifier, char* identifier, Expression* initializer);

Statement* create_multi_declaration_statement(TypeSpecifier* type_specifier, Identifier* identifier_list, Expression* initializer_list);

Parameter* create_parameter(TypeSpecifier* type, char* identifier);
Parameter* parameter_list_add_statement(Parameter* head, Parameter* parameter);

Package* create_package_info(char* package_name);
void     import_package_list_add_item(char* package_name, char* rename);

ClassDefinition* start_class_definition(char* class_identifier);
ClassDefinition* finish_class_definition(ClassDefinition* class_def, ClassMemberDeclaration* class_member_declar);

ClassMemberDeclaration* class_member_declaration_list_add_item(ClassMemberDeclaration* list, ClassMemberDeclaration* decl);
ClassMemberDeclaration* create_class_member_field_declaration(Attribute attribute, FieldMember* field_member);
ClassMemberDeclaration* create_class_member_method_declaration(Attribute attribute, MethodMember* method_member);
FieldMember*            create_class_member_field(TypeSpecifier* type_specifier, Identifier* identifier_list);
MethodMember*           create_class_member_method(FunctionType type, char* identifier, Parameter* parameter_list, FunctionReturnList* return_list, Block* block);

TypeSpecifier* create_class_type_specifier(char* identifier);

AttributeInfo* create_attribute_info(char* name);
AttributeInfo* attribute_info_add_item(AttributeInfo* list, AttributeInfo* item);


Attribute add_attribute(Attribute attribute, AttributeType type);
int       attribute_is_public(Attribute attribute);
int       attribute_is_private(Attribute attribute);
int       attribute_is_constructor(Attribute attribute);
int       attribute_is_destructor(Attribute attribute);
// create_ast.c

// fix.c
void                    ring_compiler_fix_ast(PackageUnit* package_unit);
void                    fix_statement_list(Statement* statement_list, Block* block, Function* func);
void                    fix_statement(Statement* statement, Block* block, Function* func);
void                    fix_expression(Expression* expression, Block* block, Function* func);
void                    add_declaration(Declaration* declaration, Block* block, Function* func);
void                    fix_type_specfier(TypeSpecifier* type_specifier);
void                    fix_block(Block* block, Function* func);
void                    fix_if_statement(IfStatement* if_statement, Block* block, Function* func);
void                    fix_for_statement(ForStatement* for_statement, Block* block, Function* func);
void                    fix_dofor_statement(DoForStatement* dofor_statement, Block* block, Function* func);
void                    fix_return_statement(ReturnStatement* return_statement, Block* block, Function* func);
TypeSpecifier*          fix_identifier_expression(IdentifierExpression* expression, Block* block);
void                    fix_assign_expression(AssignExpression* expression, Block* block, Function* func);
void                    fix_binary_expression(Expression* expression, Block* block, Function* func);
void                    fix_function_call_expression(FunctionCallExpression* function_call_expression, Block* block, Function* func);
void                    fix_method_call_expression(MethodCallExpression* method_call_expression, Block* block, Function* func);
void                    fix_class_definition(ClassDefinition* class_definition);
void                    fix_member_expression(Expression* expression, MemberExpression* member_expression, Block* block, Function* func);
void                    fix_dot_expression(Expression* expression, DotExpression* dot_expression, Block* block, Function* func);
void                    fix_class_member_expression(MemberExpression* member_expression, Expression* object_expression, char* member_identifier);
ClassDefinition*        search_class_definition(char* class_identifier);
ClassMemberDeclaration* search_class_member(ClassDefinition* class_definition, char* member_identifier);
void                    fix_ternary_condition_expression(TernaryExpression* ternary_expression, Block* block, Function* func);
void                    add_parameter_to_declaration(Parameter* parameter, Block* block);
Declaration*            search_declaration(char* package_posit, char* identifier, Block* block);
Function*               search_function(char* package_posit, char* identifier);

// generate.c
// PackageExecuter* package_executer_create();
// void             package_generate_vm_code(Package* package, PackageExecuter* executer);

Package_Executer* package_executer_create(ExecuterEntry* executer_entry, char* package_name);
void              package_executer_dump(Package_Executer* package_executer);

void              ring_generate_vm_code(Package* package, Package_Executer* executer);
void              ring_generate_vm_code(CompilerEntry* compiler_entry, ExecuterEntry* executer_entry);
void              add_global_variable(Package* package, Package_Executer* executer);
void              add_functions(Package* package, Package_Executer* executer);
void              add_classes(Package* package, Package_Executer* executer);
void              copy_class(Package_Executer* executer, ClassDefinition* src, RVM_Class* dest);
void              copy_function(Function* src, RVM_Function* dest);
void              copy_method(MethodMember* src, RVM_Method* dest);
void              add_top_level_code(PackageUnit* package_unit, Package_Executer* executer);
void              add_top_level_code(Package* package, Package_Executer* executer);
void              generate_code_from_function_definition(Package_Executer* executer, Function* src, RVM_Function* dest);
void              generate_code_from_method_definition(Package_Executer* executer, MethodMember* src, RVM_Method* dest);
void              vm_executer_dump(Package_Executer* executer);
RVM_OpcodeBuffer* new_opcode_buffer();
void              generate_vmcode_from_block(Package_Executer* executer, Block* block, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_statement_list(Package_Executer* executer, Block* block, Statement* statement_list, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_if_statement(Package_Executer* executer, IfStatement* if_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_for_statement(Package_Executer* executer, ForStatement* for_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_dofor_statement(Package_Executer* executer, DoForStatement* dofor_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_break_statement(Package_Executer* executer, Block* block, BreakStatement* break_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_continue_statement(Package_Executer* executer, Block* block, ContinueStatement* continue_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_return_statement(Package_Executer* executer, Block* block, ReturnStatement* return_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_initializer(Package_Executer* executer, Block* block, Declaration* declaration, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer, int need_duplicate);
void              generate_vmcode_from_assign_expression(Package_Executer* executer, AssignExpression* expression, RVM_OpcodeBuffer* new_opcode_buffer);
void              generate_pop_to_leftvalue_reverse(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_pop_to_leftvalue(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_pop_to_leftvalue_identifier(Package_Executer* executer, IdentifierExpression* identifier_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_pop_to_leftvalue_member(Package_Executer* executer, MemberExpression* member_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_logical_expression(Package_Executer* executer, BinaryExpression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode);
void              generate_vmcode_from_binary_expression(Package_Executer* executer, BinaryExpression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode);
void              generate_vmcode_from_unitary_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode);
void              generate_vmcode_from_increase_decrease_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer, int need_duplicate);
void              generate_vmcode_from_identifier_expression(Package_Executer* executer, IdentifierExpression* identifier_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_bool_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_int_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_double_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_string_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_function_call_expression(Package_Executer* executer, FunctionCallExpression* function_call_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_method_call_expression(Package_Executer* executer, MethodCallExpression* method_call_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_cast_expression(Package_Executer* executer, CastExpression* cast_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_member_expression(Package_Executer* executer, MemberExpression* member_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_ternary_condition_expression(Package_Executer* executer, TernaryExpression* ternary_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode(Package_Executer* executer, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode, unsigned int int_literal, unsigned int line_number);

int constant_pool_grow(Package_Executer* executer, unsigned int growth_size);
int constant_pool_add_int(Package_Executer* executer, int int_literal);
int constant_pool_add_double(Package_Executer* executer, double double_literal);
int constant_pool_add_string(Package_Executer* executer, char* string_literal);


unsigned int opcode_buffer_get_label(RVM_OpcodeBuffer* opcode_buffer);
void         opcode_buffer_set_label(RVM_OpcodeBuffer* opcode_buffer, unsigned int label, unsigned int label_address);
void         opcode_buffer_fix_label(RVM_OpcodeBuffer* opcode_buffer);
RVM_Opcode   convert_opcode_by_rvm_type(RVM_Opcode opcode, TypeSpecifier* type);
unsigned int calc_runtime_stack_capacity(RVM_Byte* code_list, unsigned int code_size);
void         add_code_line_map(RVM_OpcodeBuffer* opcode_buffer, unsigned int line_number, unsigned int start_pc, unsigned int opcode_size);
void         dump_code_line_map(RVM_SourceCodeLineMap* code_line_map, unsigned int code_line_size);
// generate.c

// execute.c

inline void STACK_SET_INT_INDEX(Ring_VirtualMachine* rvm, unsigned int index, int value);
inline void STACK_SET_DOUBLE_INDEX(Ring_VirtualMachine* rvm, unsigned int index, double value);
inline void STACK_SET_OBJECT_INDEX(Ring_VirtualMachine* rvm, unsigned int index, RVM_Object* value);

RVM_RuntimeStack*    new_runtime_stack();
RVM_RuntimeStatic*   new_runtime_static();
Ring_VirtualMachine* ring_virtualmachine_create();
void                 ring_virtualmachine_load_executer(Ring_VirtualMachine* rvm, Package_Executer* executer);
void                 ring_virtualmachine_load_executer(Ring_VirtualMachine* rvm, ExecuterEntry* executer_entry);
void                 rvm_add_static_variable(Package_Executer* executer, RVM_RuntimeStatic* runtime_static);
RVM_Object*          new_class_object(ClassDefinition* class_definition);
void                 rvm_add_classs(Package_Executer* executer, Ring_VirtualMachine* rvm);
void                 rvm_add_derive_functions(Package_Executer* executer, Ring_VirtualMachine* rvm);
void                 ring_execute_vm_code(Ring_VirtualMachine* rvm);
void                 invoke_native_function(Ring_VirtualMachine* rvm, RVM_Function* function, unsigned int argument_list_size);
void                 invoke_derive_function(Ring_VirtualMachine* rvm,
                                            RVM_Function** caller_function, RVM_Function* callee_function,
                                            RVM_Byte** code_list, unsigned int* code_size,
                                            unsigned int* pc,
                                            unsigned int* caller_stack_base);
void                 derive_function_return(Ring_VirtualMachine* rvm,
                                            RVM_Function** caller_function, RVM_Function* callee_function,
                                            RVM_Byte** code_list, unsigned int* code_size,
                                            unsigned int* pc,
                                            unsigned int* caller_stack_base,
                                            unsigned int  return_value_list_size);
void                 derive_function_finish(Ring_VirtualMachine* rvm,
                                            RVM_Function** caller_function, RVM_Function* callee_function,
                                            RVM_Byte** code_list, unsigned int* code_size,
                                            unsigned int* pc,
                                            unsigned int* caller_stack_base,
                                            unsigned int  return_value_list_size);
void                 init_derive_function_local_variable(Ring_VirtualMachine* rvm, RVM_Function* function);
void                 debug_rvm(Ring_VirtualMachine* rvm, RVM_Function* function, RVM_Byte* code_list, unsigned int code_size, unsigned int pc, unsigned int caller_stack_base);

RVM_Object* create_rvm_object();
RVM_Object* string_literal_to_rvm_object(char* string_literal);
RVM_Object* concat_string(RVM_Object* a, RVM_Object* b);

void store_callinfo(RVM_RuntimeStack* runtime_stack, RVM_CallInfo* callinfo);
void restore_callinfo(RVM_RuntimeStack* runtime_stack, RVM_CallInfo** callinfo);


// RVM_Value native_proc_to_string(Ring_VirtualMachine* rvm, unsigned int arg_cout, RVM_Value* args);
// RVM_Value native_proc_print(Ring_VirtualMachine* rvm, unsigned int arg_cout, RVM_Value* args);
// RVM_Value native_proc_println(Ring_VirtualMachine* rvm, unsigned int arg_cout, RVM_Value* args);
RVM_Value native_proc_println_bool(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value native_proc_println_int(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value native_proc_println_double(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value native_proc_println_string(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value native_proc_debug_assert(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value native_proc_exit(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
// void      rvm_register_native_function(Ring_VirtualMachine* rvm, char* func_name, RVM_NativeFuncProc* func_proc, int arg_count);
// void      rvm_register_native_functions(Ring_VirtualMachine* rvm);
// execute.c


// bytecode.c
void ring_bytecode_dump(Package_Executer* executer, FILE* output);
void ring_bytecode_load(Package_Executer* executer, FILE* input);
// bytecode.c

// std_lib.cpp
void      register_lib(Package_Executer* package_executer, char* func_name, RVM_NativeFuncProc* func_proc, int arg_count);
RVM_Value std_fmt_lib_println_bool(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value std_fmt_lib_println_int(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value std_fmt_lib_println_double(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value std_fmt_lib_println_string(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);

RVM_Value std_debug_lib_debug_assert(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);

RVM_Value std_math_lib_sqrt(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
// std_lib.cpp

// interactive.c
// interactive.c

// utils.c
void                     ring_compiler_functions_dump(PackageUnit* package_unit);
void                     ring_vm_constantpool_dump(Package_Executer* executer);
void                     ring_vm_code_dump(RVM_Function* function, RVM_Byte* code_list, unsigned int code_size, unsigned int pc, unsigned int screen_row, unsigned int screen_col);
void                     ring_vm_dump_runtime_stack(RVM_RuntimeStack* runtime_stack, unsigned int caller_stack_base, unsigned int screen_row, unsigned int screen_col);
std::vector<std::string> list_file(char* path);
// utils.c

// thread_pool.c
typedef struct thpool_* threadpool;
threadpool              thpool_init(int num_threads);
int                     thpool_add_work(threadpool, void (*function_p)(void*), void* arg_p);
void                    thpool_wait(threadpool);
void                    thpool_pause(threadpool);
void                    thpool_resume(threadpool);
void                    thpool_destroy(threadpool);
int                     thpool_num_threads_working(threadpool);
// thread_pool.c

#endif
