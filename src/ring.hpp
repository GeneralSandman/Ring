
#ifndef RING_INCLUDE_H
#define RING_INCLUDE_H

#include <cstdio>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define RING_VERSION "ring-v0.2.13-beta Copyright (C) 2021-2023 ring.wiki, ZhenhuLi"


typedef struct Ring_VirtualMachine          Ring_VirtualMachine;
typedef struct ImportPackageInfo            ImportPackageInfo;
typedef struct CompilerEntry                CompilerEntry;
typedef struct ExecuterEntry                ExecuterEntry;
typedef struct Package_Executer             Package_Executer;
typedef struct Package                      Package;
typedef struct PackageUnit                  PackageUnit;

typedef struct RVM_Variable                 RVM_Variable;
typedef struct RVM_RuntimeStack             RVM_RuntimeStack;
typedef struct RVM_RuntimeStatic            RVM_RuntimeStatic;
typedef struct RVM_RuntimeHeap              RVM_RuntimeHeap;
typedef struct RVM_OpcodeBuffer             RVM_OpcodeBuffer;
typedef struct RVM_Opcode_Info              RVM_Opcode_Info;

typedef struct RVM_LabelTable               RVM_LabelTable;
typedef struct RVM_SourceCodeLineMap        RVM_SourceCodeLineMap;
typedef struct Ring_String                  Ring_String;
typedef struct Ring_BasicValue              Ring_BasicValue;
typedef struct Ring_Array                   Ring_Array;

typedef struct ClassDefinition              ClassDefinition;
typedef struct ClassMemberDeclaration       ClassMemberDeclaration;
typedef struct FieldMember                  FieldMember;
typedef struct MethodMember                 MethodMember;
typedef struct Statement                    Statement;
typedef struct StatementExecResult          StatementExecResult;
typedef struct Expression                   Expression;
typedef struct ArrayIndexExpression         ArrayIndexExpression;
typedef struct NewArrayExpression           NewArrayExpression;
typedef struct ArrayLiteralExpression       ArrayLiteralExpression;
typedef struct ClassObjectLiteralExpression ClassObjectLiteralExpression;
typedef struct CastExpression               CastExpression;
typedef struct MemberExpression             MemberExpression;
typedef struct DimensionExpression          DimensionExpression;
typedef struct SubDimensionExpression       SubDimensionExpression;
typedef struct DotExpression                DotExpression;
typedef struct BinaryExpression             BinaryExpression;
typedef struct TernaryExpression            TernaryExpression;
typedef struct FunctionCallExpression       FunctionCallExpression;
typedef struct MethodCallExpression         MethodCallExpression;
typedef struct AssignExpression             AssignExpression;
typedef struct FieldInitExpression          FieldInitExpression;
typedef struct IdentifierExpression         IdentifierExpression;

typedef struct ArgumentList                 ArgumentList;
typedef struct Parameter                    Parameter;
typedef struct Identifier                   Identifier;
typedef struct Function                     Function;
typedef struct Block                        Block;
typedef struct FunctionReturnList           FunctionReturnList;

typedef struct IfStatement                  IfStatement;
typedef struct ElseIfStatement              ElseIfStatement;
typedef struct ForStatement                 ForStatement;
typedef struct ForTernaryStatement          ForTernaryStatement;
typedef struct ForRangeStatement            ForRangeStatement;
typedef struct DoForStatement               DoForStatement;
typedef struct BreakStatement               BreakStatement;
typedef struct ReturnStatement              ReturnStatement;
typedef struct ContinueStatement            ContinueStatement;

typedef struct Ring_DeriveType_Array        Ring_DeriveType_Array;
typedef struct Ring_DeriveType_Class        Ring_DeriveType_Class;
typedef struct Declaration                  Declaration;
typedef struct TagDefinitionStatement       TagDefinitionStatement;
typedef struct JumpTagStatement             JumpTagStatement;
typedef struct TypeSpecifier                TypeSpecifier;
typedef struct StdPackageNativeFunction     StdPackageNativeFunction;

typedef struct StdPackageInfo               StdPackageInfo;
typedef struct RVM_DebugConfig              RVM_DebugConfig;
typedef struct ErrorMessageInfo             ErrorMessageInfo;
typedef struct ErrorReportContext           ErrorReportContext;

typedef struct AttributeInfo                AttributeInfo;

typedef struct RVM_ConstantPool             RVM_ConstantPool;
typedef struct RVM_String                   RVM_String;
typedef struct RVM_Array                    RVM_Array;
typedef struct RVM_ClassObject              RVM_ClassObject;
typedef struct RVM_Object                   RVM_Object;
typedef struct RVM_BasicTypeSpecifier       RVM_BasicTypeSpecifier;
typedef struct RVM_TypeSpecifier            RVM_TypeSpecifier;

typedef struct RVM_LocalVariable            RVM_LocalVariable;
typedef struct NativeFunction               NativeFunction;
typedef struct DeriveFunction               DeriveFunction;
typedef struct RVM_Function                 RVM_Function;
typedef struct RVM_Field                    RVM_Field;
typedef struct RVM_Method                   RVM_Method;
typedef struct RVM_ClassDefinition          RVM_ClassDefinition;
typedef struct RVM_CallInfo                 RVM_CallInfo;

typedef struct RVM_GC_Object                RVM_GC_Object;

typedef unsigned char                       RVM_Byte;

typedef struct MemPool                      MemPool;
typedef struct MemBlock                     MemBlock;

typedef struct Ring_Grammar_Info            Ring_Grammar_Info;

typedef enum {
    GRAMMAR_UNKNOW = 0,
    GRAMMAR_IMPORT_PACKAGE,
    GRAMMAR_FUNCTION_DEFIN,
    GRAMMAR_CLASS_DEFIN,

} RING_GRAMMAR_ID;

struct Ring_Grammar_Info {
    RING_GRAMMAR_ID          id;
    std::vector<std::string> grammar;
};

typedef enum {
    RVM_VALUE_TYPE_UNKNOW,

    RVM_VALUE_TYPE_BOOL,
    RVM_VALUE_TYPE_INT,
    RVM_VALUE_TYPE_DOUBLE,
    RVM_VALUE_TYPE_STRING,
    RVM_VALUE_TYPE_CLASS_OB,
    RVM_VALUE_TYPE_ARRAY,

    RVM_VALUE_TYPE_OBJECT, // TODO: 删除

} RVM_Value_Type;

typedef enum {
    RVM_FALSE,
    RVM_TRUE,
} RVM_Bool;

// TODO: 修改一下
typedef struct {
    RVM_Value_Type type;
    union {
        RVM_Bool         bool_value;
        int              int_value;
        double           double_value;
        RVM_String*      string_value;
        RVM_ClassObject* class_ob_value;
        RVM_Array*       array_value;

        RVM_Object*      object; // TODO: 删除
    } u;

} RVM_Value;

struct Ring_VirtualMachine {
    Package_Executer*    executer;
    ExecuterEntry*       executer_entry;

    RVM_RuntimeStatic*   runtime_static; // TODO: 暂时只支持main包的 全局变量
    RVM_RuntimeStack*    runtime_stack;
    RVM_RuntimeHeap*     runtime_heap;
    unsigned int         pc;

    RVM_CallInfo*        call_info;

    RVM_ClassDefinition* class_list;
    unsigned int         class_size;

    MemPool*             meta_pool;
    MemPool*             data_pool;

    RVM_DebugConfig*     debug_config;

#ifdef DEBUG_RVM_INTERACTIVE
    std::vector<std::string> stdout_logs;
#endif
};

struct ImportPackageInfo {
    unsigned int line_number;

    char*        package_name;
    char*        package_path;
    char*        rename;
    std::string  package_md5;

    /*
     * package_name:
     *     用户 import : 是包含远程路径的/也可以是一个标准包/也可以是个本项目包,
     *     e.g. github.com/G/P
     *     主要通过这个来裁定是否重复编译了
     *
     * package_path:
     *     可以 重定向到本地 Pakcage 的路径
     *
     * rename:
     *     多个package 可能有重复, 支持用户重命名 package
     *
     * package_md5:
     *     用于链接使用, 主要为编译和链接 生成一个唯一ID
     */
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
    ExecuterEntry*       executer_entry;
    unsigned int         package_index; // 在 ExecuterEntry 中的 index
    char*                package_name;

    unsigned int         constant_pool_size;
    RVM_ConstantPool*    constant_pool_list;

    unsigned int         global_variable_size;
    RVM_Variable*        global_variable_list;

    unsigned int         function_size;
    RVM_Function*        function_list;

    unsigned int         class_size;
    RVM_ClassDefinition* class_list;

    unsigned int         code_size;
    RVM_Byte*            code_list;

    unsigned int         main_func_index;

    unsigned int         estimate_runtime_stack_capacity;
};

/*
 * PackageUnit 与 Package 的逻辑关系
 *
 * 一个PackageUnit 对应一个 Ring 源码文件
 * 每个 PackageUnit 都有一个对应的 Package
 * 一个 Package 可以有多个 PackageUnit
 */
struct Package {
    CompilerEntry*                                    compiler_entry;
    unsigned int                                      package_index; // 在 CompilerEntry 中的 index
    char*                                             package_name;
    char*                                             package_path;

    std::vector<std::string>                          source_file_list;

    std::vector<Declaration*>                         global_declaration_list;
    std::vector<ClassDefinition*>                     class_definition_list;
    std::vector<Function*>                            function_list;

    std::unordered_set<std::string>                   global_identifier_map;
    std::unordered_map<std::string, Declaration*>     global_declaration_map;
    std::unordered_map<std::string, ClassDefinition*> class_definition_map;
    std::unordered_map<std::string, Function*>        function_map;
    std::unordered_map<std::string, std::string>      import_package_map;

    std::vector<PackageUnit*>                         package_unit_list;

    unsigned int                                      compile_error_num;
};

typedef struct SourceLineInfo {
    off_t        start_offset; // 某行相对于文件开始的偏移
    unsigned int size;         // 某行的字符数量
} SourceLineInfo;

/*
 * PackageUnit 与 Package 的逻辑关系
 *
 * 一个PackageUnit 对应一个 Ring 源码文件
 * 每个 PackageUnit 都有一个对应的 Package
 * 一个 Package 可以有多个 PackageUnit
 */
struct PackageUnit {
    Package*     parent_package;

    std::string  current_file_name;
    FILE*        current_file_fp; // 这个 FILE* 只能给 bison使用
    FILE*        file_fp_random;  // 用来获取文件内容

    unsigned int current_line_number;
    unsigned int current_column_number;
    Ring_String* current_line_content;

    // 该文件每行的偏移量，用于快速获取某行的内容
    // line_offset_map[0] 没有意义，因为文件都是从第1行开始的
    // line_offset_map[3] 表示第3行开始的文件字节偏移量
    // 可通过 lseek() 快速获取某行的内容
    off_t                           current_line_start_offset;
    off_t                           current_offset;
    std::vector<SourceLineInfo>     line_offset_map;

    std::vector<ImportPackageInfo*> import_package_list;

    unsigned int                    global_block_statement_list_size;
    Statement*                      global_block_statement_list;
    std::vector<Declaration*>       global_declaration_list;

    std::vector<ClassDefinition*>   class_definition_list;
    std::vector<Function*>          function_list;

    Block*                          current_block;

    unsigned int                    compile_error_num;
};


/*
 * TypeSpecifier
 *
 * 基础类型：
 *     - bool
 *     - int
 *     - double
 * 对象类型：
 *     - string
 *     - array
 *     - class
 * 范型推导
 *     - any
 *
 */
typedef enum {
    RING_BASIC_TYPE_UNKNOW,

    RING_BASIC_TYPE_BOOL,
    RING_BASIC_TYPE_INT,
    RING_BASIC_TYPE_DOUBLE,
    RING_BASIC_TYPE_STRING,
    RING_BASIC_TYPE_CLASS,
    RING_BASIC_TYPE_ARRAY,

    RING_BASIC_TYPE_ANY,

    RING_BASIC_TYPE_NULL,
} Ring_BasicType;


typedef enum {
    RING_DERIVE_TYPE_UNKNOW,
    RING_DERIVE_TYPE_ARRAY,
    RING_DERIVE_TYPE_CLASS,
} Ring_DeriveTypeKind;


struct Ring_DeriveType_Array {
};

struct Ring_DeriveType_Class {
    char*            class_identifier;
    ClassDefinition* class_definition; // FIX_AST_UPDATE
};


// Only used by front-end of compiler.
struct TypeSpecifier {
    unsigned int   line_number;

    Ring_BasicType kind;
    union {
        Ring_DeriveType_Array* array_type;
        Ring_DeriveType_Class* class_type;
    } u;
    unsigned int   dimension; // 维度，用来指明sub
    TypeSpecifier* sub;
};

typedef RVM_Value RVM_NativeFuncProc(Ring_VirtualMachine* rvm, unsigned int arg_cout, RVM_Value* args);

typedef enum {
    RVM_FUNCTION_TYPE_UNKNOW,
    RVM_FUNCTION_TYPE_NATIVE, // 原生函数
    RVM_FUNCTION_TYPE_DERIVE, // 派生函数，库函数，Ring编写的库函数
} RVMFunctionType;

struct RVM_LocalVariable {
    RVM_TypeSpecifier* type_specifier;
    char*              identifier;
};

struct NativeFunction {
    RVM_NativeFuncProc* func_proc;
    int                 arg_count;         // -1 表示可变参数
    int                 return_list_count; // 返回值的数量
};
struct DeriveFunction {
    unsigned int                       code_size;
    RVM_Byte*                          code_list;

    std::vector<RVM_SourceCodeLineMap> code_line_map;
    // 一行Ring源代码 对应 一个 RVM_SourceCodeLineMap
    // 空行、注释行 没有对应的 RVM_SourceCodeLineMap
    // RVM_SourceCodeLineMap.opcode_begin_index 是单调递增的
};
struct RVM_Function {
    std::string        source_file;
    unsigned int       start_line_number; // 源码的开始行
    unsigned int       end_line_number;   // 源码的结束行

    char*              func_name;
    RVMFunctionType    type;

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
    char*              identifier;
    RVM_TypeSpecifier* type_specifier;
};

// 他的本质就是一个 函数
// 只不过他可以引用 field
// TODO: RVM_Method 需要简化一下, 跟 RVM_Function其实是一样的
struct RVM_Method {
    char*         identifier;
    RVM_Function* rvm_function;
};

struct RVM_ClassDefinition {
    std::string  source_file;
    unsigned int start_line_number; // 源码的开始行
    unsigned int end_line_number;   // 源码的结束行

    char*        identifier;

    unsigned int class_index;

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
    char*              identifier;
    RVM_TypeSpecifier* type_specifier;
};


typedef enum {
    RVM_OBJECT_TYPE_UNKNOW,
} RVM_Object_Type;

typedef enum {
    GC_MARK_COLOR_UNKNOW,
    GC_MARK_COLOR_WHITE, // 需要被回收
    GC_MARK_COLOR_BLACK, // 不需要被回收
} GC_Mark;

/*
 * RVM 中 string 运行时表示, 专用
 */
struct RVM_String {
    RVM_Object_Type type;
    GC_Mark         gc_mark;
    RVM_Object*     prev;
    RVM_Object*     next;

    char*           data;
    unsigned int    length;
    unsigned int    capacity;
};

typedef enum {
    RVM_ARRAY_UNKNOW,
    RVM_ARRAY_BOOL,         // bool 数组
    RVM_ARRAY_INT,          // int 数组
    RVM_ARRAY_DOUBLE,       // double 数组
    RVM_ARRAY_STRING,       // string 数组
    RVM_ARRAY_CLASS_OBJECT, // 类 数组
    RVM_ARRAY_A,            // 多维数组的中间态， 感觉有必要删除
} RVM_Array_Type;

struct RVM_Array {
    RVM_Array_Type type;
    unsigned char  dimension;
    unsigned int   length;
    unsigned int   capacity;
    union {
        bool*            bool_array;
        int*             int_array;
        double*          double_array;
        RVM_String*      string_array;
        RVM_ClassObject* class_ob_array;
        RVM_Array*       a_array; // 多维数组
    } u;
};

struct RVM_ClassObject {
    RVM_ClassDefinition* class_ref;
    unsigned int         field_count;
    RVM_Value*           field;
};


struct RVM_Object {
    RVM_Object_Type type;
    GC_Mark         gc_mark;
    RVM_Object*     prev;
    RVM_Object*     next;
};

#define RVM_GC_Object_Header \
    RVM_Object_Type type;    \
    GC_Mark         gc_mark; \
    RVM_Object*     prev;    \
    RVM_Object*     next;

// Only used by back-end of compiler.
struct RVM_TypeSpecifier {
    Ring_BasicType kind;

    union {
        unsigned int class_def_index;
    } u;

    unsigned int       dimension; // 维度，用来指明sub
    RVM_TypeSpecifier* sub;
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
    unsigned int alloc_size;
    unsigned int threshold;
    RVM_Object*  list;
    // RVM_MemoryPoll
    // TODO: 是否需要使用内存池
};

struct RVM_LabelTable {
    char*        label_name;
    unsigned int label_address;
};

struct RVM_SourceCodeLineMap {
    unsigned int line_number;        // 对应Ring源代码文件的行数
    unsigned int opcode_begin_index; // 对应 opcode 的 开始索引
    unsigned int opcode_size;        // 一行Ring源代码 对应 opcode size
};

struct RVM_OpcodeBuffer {
    RVM_Byte*                          code_list;
    unsigned int                       code_size;
    unsigned int                       code_capacity;

    std::vector<RVM_LabelTable>        lable_list;

    std::vector<RVM_SourceCodeLineMap> code_line_map;
    // 一行Ring源代码 对应 一个 RVM_SourceCodeLineMap
    // 空行、注释行 没有对应的 RVM_SourceCodeLineMap
    // RVM_SourceCodeLineMap.opcode_begin_index 是单调递增的
};

typedef enum {
    OPCODE_OPERAND_TYPE_0BYTE,     // 后边没有操作数, pc+1
    OPCODE_OPERAND_TYPE_1BYTE,     // 后边1BYTE操作数, pc+2
    OPCODE_OPERAND_TYPE_2BYTE_As,  // 后边2BYTE操作数 两个字节组合成一个操作数, pc+3
    OPCODE_OPERAND_TYPE_2BYTE_AB,  // 后边2BYTE操作数 两个字节分别为两个不同的操作数, pc+3
    OPCODE_OPERAND_TYPE_3BYTE_ABs, // 后边3BYTE操作数 第1个字节为一个操作数, 第2,3个字节为一个操作数, pc+4


} OpcodeOperandType;

struct RVM_Opcode_Info {
    RVM_Byte          code;                    // 字节码枚举
    std::string       name;                    // 字节码字符串
    OpcodeOperandType operand_type;            // 字节码后边的操作数所占字节数量
    int               runtime_stack_increment; // 对运行时栈空间的增长 可为负值

    /*
     * 字节码的注释, 放在结构体里边, 用于快速生成文档, 目前暂无使用意义, 后续放在debug控制
     *
     * usage_comment: 字节码注释
     * stack_top_change: 对 runtime_stack 的操作变化
     */
    std::string usage_comment;
    std::string stack_top_change;
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
    RVM_CODE_POP_STATIC_STRING,
    RVM_CODE_POP_STATIC_CLASS_OB,
    RVM_CODE_POP_STATIC_ARRAY,
    RVM_CODE_PUSH_STATIC_BOOL,
    RVM_CODE_PUSH_STATIC_INT,
    RVM_CODE_PUSH_STATIC_DOUBLE,
    RVM_CODE_PUSH_STATIC_STRING,
    RVM_CODE_PUSH_STATIC_CLASS_OB,
    RVM_CODE_PUSH_STATIC_ARRAY,


    // stack
    RVM_CODE_POP_STACK_BOOL,
    RVM_CODE_POP_STACK_INT,
    RVM_CODE_POP_STACK_DOUBLE,
    RVM_CODE_POP_STACK_STRING,
    RVM_CODE_POP_STACK_CLASS_OB,
    RVM_CODE_POP_STACK_ARRAY,
    RVM_CODE_PUSH_STACK_BOOL,
    RVM_CODE_PUSH_STACK_INT,
    RVM_CODE_PUSH_STACK_DOUBLE,
    RVM_CODE_PUSH_STACK_STRING,
    RVM_CODE_PUSH_STACK_CLASS_OB,
    RVM_CODE_PUSH_STACK_ARRAY,

    // array
    RVM_CODE_PUSH_ARRAY_A,

    RVM_CODE_PUSH_ARRAY_BOOL,
    RVM_CODE_PUSH_ARRAY_INT,
    RVM_CODE_PUSH_ARRAY_DOUBLE,
    RVM_CODE_PUSH_ARRAY_STRING,
    RVM_CODE_PUSH_ARRAY_CLASS_OBJECT,
    RVM_CODE_POP_ARRAY_BOOL,
    RVM_CODE_POP_ARRAY_INT,
    RVM_CODE_POP_ARRAY_DOUBLE,
    RVM_CODE_POP_ARRAY_STRING,
    RVM_CODE_POP_ARRAY_CLASS_OBJECT,

    // array append
    RVM_CODE_ARRAY_APPEND_BOOL,
    RVM_CODE_ARRAY_APPEND_INT,
    RVM_CODE_ARRAY_APPEND_DOUBLE,
    RVM_CODE_ARRAY_APPEND_STRING,
    RVM_CODE_ARRAY_APPEND_CLASS_OBJECT,
    // array pop
    RVM_CODE_ARRAY_POP_BOOL,
    RVM_CODE_ARRAY_POP_INT,
    RVM_CODE_ARRAY_POP_DOUBLE,
    RVM_CODE_ARRAY_POP_STRING,
    RVM_CODE_ARRAY_POP_CLASS_OBJECT,

    // class
    RVM_CODE_POP_FIELD_BOOL,
    RVM_CODE_POP_FIELD_INT,
    RVM_CODE_POP_FIELD_DOUBLE,
    RVM_CODE_POP_FIELD_STRING,
    RVM_CODE_POP_FIELD_CLASS_OB,
    RVM_CODE_POP_FIELD_ARRAY,
    RVM_CODE_PUSH_FIELD_BOOL,
    RVM_CODE_PUSH_FIELD_INT,
    RVM_CODE_PUSH_FIELD_DOUBLE,
    RVM_CODE_PUSH_FIELD_STRING,
    RVM_CODE_PUSH_FIELD_CLASS_OB,
    RVM_CODE_PUSH_FIELD_ARRAY,

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

    RVM_CODE_SELF_INCREASE,
    RVM_CODE_SELF_DECREASE,

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

    // array
    RVM_CODE_NEW_ARRAY_BOOL,
    RVM_CODE_NEW_ARRAY_INT,
    RVM_CODE_NEW_ARRAY_DOUBLE,
    RVM_CODE_NEW_ARRAY_STRING,
    RVM_CODE_NEW_ARRAY_CLASS_OBJECT,
    RVM_CODE_NEW_ARRAY_LITERAL_BOOL,
    RVM_CODE_NEW_ARRAY_LITERAL_INT,
    RVM_CODE_NEW_ARRAY_LITERAL_DOUBLE,
    RVM_CODE_NEW_ARRAY_LITERAL_STRING,
    RVM_CODE_NEW_ARRAY_LITERAL_CLASS_OBJECT,

    RVM_CODE_PUSH_ARRAY_LEN,
    RVM_CODE_PUSH_ARRAY_CAPACITY,
    RVM_CODE_PUSH_STRING_LEN,
    RVM_CODE_PUSH_STRING_CAPACITY,

    // class
    RVM_CODE_NEW_CLASS_OBJECT_LITERAL,

    // range
    RVM_CODE_FOR_RANGE_ARRAY_BOOL,
    RVM_CODE_FOR_RANGE_ARRAY_INT,
    RVM_CODE_FOR_RANGE_ARRAY_DOUBLE,
    RVM_CODE_FOR_RANGE_ARRAY_STRING,
    RVM_CODE_FOR_RANGE_ARRAY_CLASS_OBJECT,
    RVM_CODE_FOR_RANGE_STRING,
    RVM_CODE_FOR_RANGE_FINISH,

    // convert
    RVM_CODE_BOOL_2_STRING,
    RVM_CODE_INT_2_STRING,
    RVM_CODE_DOUBLE_2_STRING,

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

struct RVM_CallInfo {
    unsigned int     magic_number;
    RVM_Function*    caller_function;
    unsigned int     caller_pc; // 调用者的返回地址
    unsigned int     caller_stack_base;

    RVM_ClassObject* callee_object;
    RVM_Function*    callee_function;
    unsigned int     callee_argument_size; // 函数调用的参数数量，可变参数

    RVM_CallInfo*    prev;
    RVM_CallInfo*    next;
};

#define CALL_INFO_MAGIC_NUMBER (0x8421) // 33852
#define CALL_INFO_SIZE ((sizeof(RVM_CallInfo) - 1) / sizeof(RVM_Value) + 1)

#define CALL_INFO_SIZE_V2 1

/*
 * Ring_String 是专门给源信息使用的
 * 不是 虚拟机使用的
 * 虚拟机使用 RVM_String
 */
struct Ring_String {
    char*        data;
    unsigned int length;
    unsigned int capacity;
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
    STATEMENT_TYPE_TAG_DEFINITION,
    STATEMENT_TYPE_JUMP_TAG,
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
    EXPRESSION_TYPE_LOGICAL_UNITARY_NOT, // 一元操作符 逻辑 非 not
    EXPRESSION_TYPE_UNITARY_INCREASE,    // 一元操作符 i++
    EXPRESSION_TYPE_UNITARY_DECREASE,    // 一元操作符 i--
    EXPRESSION_TYPE_RELATIONAL_EQ,
    EXPRESSION_TYPE_RELATIONAL_NE,
    EXPRESSION_TYPE_RELATIONAL_GT,
    EXPRESSION_TYPE_RELATIONAL_GE,
    EXPRESSION_TYPE_RELATIONAL_LT,
    EXPRESSION_TYPE_RELATIONAL_LE,

    EXPRESSION_TYPE_ARRAY_INDEX,
    EXPRESSION_TYPE_NEW_ARRAY,
    EXPRESSION_TYPE_ARRAY_LITERAL,
    EXPRESSION_TYPE_CLASS_OBJECT_LITERAL,

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
    std::string             source_file;
    unsigned int            start_line_number; // 源码的开始行
    unsigned int            end_line_number;   // 源码的结束行

    unsigned int            class_index;
    char*                   identifier;
    ClassMemberDeclaration* member;

    ClassDefinition*        next;
};

typedef enum {
    ATTRIBUTE_NONE = 0,
    ACCESS_PUBLIC  = 0x01,
    ACCESS_PRIVATE = 0x01 << 1,
    ACCESS_DELETE  = 0x01 << 2,

    CONSTRUCTOR    = 0x01 << 4,
    DESTRUCTOR     = 0x01 << 5,
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
    unsigned int    line_number;

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
    unsigned int   line_number;

    unsigned int   index_of_class; // fix it in fix_ast
    TypeSpecifier* type_specifier;
    char*          identifier;
};

// 类方法
struct MethodMember {
    std::string         source_file;
    unsigned int        start_line_number; // 源码的开始行
    unsigned int        end_line_number;   // 源码的结束行

    Package*            package; // 所属的package

    AttributeInfo*      attribute_info;

    unsigned int        index_of_class; // fix it in fix_ast

    char*               identifier;

    unsigned int        parameter_list_size;
    Parameter*          parameter_list;

    unsigned int        return_list_size;
    FunctionReturnList* return_list;

    Block*              block;
};


// ----------------------------------
// class define
// ----------------------------------

struct Statement {
    unsigned int  line_number;

    StatementType type;
    union {
        Expression*             expression;
        IfStatement*            if_statement;
        ForStatement*           for_statement;
        DoForStatement*         dofor_statement;
        BreakStatement*         break_statement;
        ContinueStatement*      continue_statement;
        ReturnStatement*        return_statement;
        Declaration*            declaration_statement;
        TagDefinitionStatement* tag_definition_statement;
        JumpTagStatement*       jump_tag_statement;
    } u;
    Statement* next;
};

struct StatementExecResult {
    StatementExecResultType type;
    unsigned int            return_value_list_size;
    Ring_BasicValue**       return_value_list;
};

struct Expression {
    unsigned int   line_number;

    char*          package_posit;
    TypeSpecifier* convert_type; // 一个复杂表达式最后结果值的类型, FIX_AST_UPDATE
    ExpressionType type;
    union {
        Ring_Bool                     bool_literal;
        int                           int_literal;
        double                        double_literal;
        char*                         string_literal;
        IdentifierExpression*         identifier_expression;
        FunctionCallExpression*       function_call_expression;
        MethodCallExpression*         method_call_expression;
        AssignExpression*             assign_expression;
        TernaryExpression*            ternary_expression;
        BinaryExpression*             binary_expression;
        Expression*                   unitary_expression;
        ArrayIndexExpression*         array_index_expression;
        NewArrayExpression*           new_array_expression;
        ArrayLiteralExpression*       array_literal_expression;
        ClassObjectLiteralExpression* class_object_literal_expression;
        CastExpression*               cast_expression;
        MemberExpression*             member_expression;
        DotExpression*                dot_expression;
        FieldInitExpression*          field_init_expression;
    } u;

    Expression* next;
};

typedef enum {
    IDENTIFIER_EXPRESSION_TYPE_UNKNOW,
    IDENTIFIER_EXPRESSION_TYPE_VARIABLE,
    IDENTIFIER_EXPRESSION_TYPE_FUNCTION,
} IdentifierExpressionType;

struct IdentifierExpression {
    unsigned int             line_number;
    unsigned int             row_number;

    char*                    package_posit;

    IdentifierExpressionType type;
    char*                    identifier;
    union {
        Declaration* declaration;
        Function*    function;
    } u;
};

struct ArrayIndexExpression {
    unsigned int         line_number;

    Expression*          array_expression;
    DimensionExpression* index_expression;

    /*
     * e.g.  students[1,2,3];
     *
     * array_expression: students
     * index_expression: [1,2,3]
     */
};

struct NewArrayExpression {
    unsigned int         line_number;

    TypeSpecifier*       type_specifier;
    DimensionExpression* dimension_expression;
};

struct ArrayLiteralExpression {
    unsigned int         line_number;

    TypeSpecifier*       type_specifier;
    DimensionExpression* dimension_expression;
    Expression*          expression_list;
};

struct ClassObjectLiteralExpression {
    unsigned int         line_number;

    TypeSpecifier*       type_specifier;
    FieldInitExpression* field_init_expression_list;
};

struct CastExpression {
    unsigned int   line_number;

    TypeSpecifier* type_specifier;
    Expression*    operand;
};

struct MemberExpression {
    unsigned int            line_number;

    Expression*             object_expression;
    char*                   member_identifier;
    ClassMemberDeclaration* member_declaration; // FIX_AST_UPDATE
};
/*
 * NOTE FOR MemberExpression
 *
 * e.g.
 * var Job job1;
 * job1.JobID;
 *
 * job1 : object_expression
 * JobID : member_identifier
 * JobID : member_declaration
 */


/*
 * DimensionExpression
 *
 * Dimension是有语法糖的，
 *
 * [,,] 是一个三维数组, 可以用来指示变量的类型
 * [!3] 是一个三维数组, 可以用来指示变量的类型
 *
 * [,,] [!3] 不能用来 new 数组
 *
 *
 * [1,2,3] 只能用这种形式new数组
 *
 * TODO: 要在语义分析的层面做细致的检测
 */
struct DimensionExpression {
    unsigned int            line_number;

    unsigned char           dimension;
    SubDimensionExpression* dimension_list;
};
struct SubDimensionExpression {
    unsigned int            line_number;
    unsigned char           index;
    Expression*             num_expression;
    SubDimensionExpression* next;

    // field: index
    // index = 2 为二维数组

    // field: num_expression
    // when new array, num_expression is array size.
    // when access array, num_expression is index.
};

struct DotExpression {
    unsigned int line_number;

    Expression*  prefix_expression;
    Expression*  suffix_expression;
};
/*
 * NOTE FOR DotExpression
 *
 * e.g.
 * object.member
 * object.member()
 *
 * object -> prefix_expression
 * member -> suffix_expression
 */


struct FunctionCallExpression {
    unsigned int  line_number;

    char*         package_posit;

    Expression*   function_identifier_expression;
    ArgumentList* argument_list;
};

struct MethodCallExpression {
    unsigned int            line_number;

    Expression*             object_expression;
    char*                   member_identifier;
    ClassMemberDeclaration* member_declaration; // FIX_AST_UPDATE
    ArgumentList*           argument_list;
};

struct Identifier {
    unsigned int   line_number;

    IdentifierType type;
    char*          name;
    unsigned int   array_index;  // 供数组使用，还要考虑一下负值索引的问题
    Function*      parent_scope; // 作用域

    Identifier*    next;
};

struct AssignExpression {
    unsigned int         line_number;

    AssignExpressionType type;
    Expression*          left;
    Expression*          operand;
};

struct FieldInitExpression {
    unsigned int         line_number;

    char*                field_identifier;
    FieldMember*         field_member; // 在 fix_ast 中修正
    Expression*          init_expression;
    FieldInitExpression* next;
};

struct BinaryExpression {
    unsigned int line_number;

    Expression*  left_expression;
    Expression*  right_expression;
};

// 三元运算符
struct TernaryExpression {
    unsigned int line_number;

    Expression*  condition_expression;
    Expression*  true_expression;
    Expression*  false_expression;
};

struct ArgumentList {
    unsigned int  line_number;

    Expression*   expression;
    ArgumentList* next;
};

struct Parameter {
    unsigned int   line_number;

    TypeSpecifier* type_specifier;
    bool           is_variadic; // variadic parameter function can be called with any number of trailing arguments.
    char*          identifier;
    Parameter*     next;
};

struct Declaration {
    unsigned int   line_number;

    TypeSpecifier* type_specifier;
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

    BlockType    type;

    unsigned int declaration_list_size;
    Declaration* declaration_list;

    unsigned int statement_list_size;
    Statement*   statement_list;

    Block*       parent_block;

    BlockLabels  block_labels;
};

struct Function {
    std::string         source_file;
    unsigned int        start_line_number; // 源码的开始行
    unsigned int        end_line_number;   // 源码的结束行

    Package*            package; // 所属的package

    AttributeInfo*      attribute_info;

    unsigned int        func_index;

    char*               function_name;
    FunctionType        type;

    unsigned int        parameter_list_size;
    Parameter*          parameter_list;

    unsigned int        return_list_size;
    FunctionReturnList* return_list;

    Block*              block;

    Function*           next;
};

struct FunctionReturnList {
    VariableType        variable_type;
    FunctionReturnList* next;
};

struct IfStatement {
    unsigned int     line_number;

    Expression*      condition_expression;

    Block*           if_block;
    ElseIfStatement* elseif_list;
    Block*           else_block;
};

struct ElseIfStatement {
    unsigned int     line_number;

    Expression*      condition_expression;

    Block*           elseif_block;

    ElseIfStatement* next;
};


typedef enum {
    FOR_STATEMENT_TYPE_UNKNOW = 0,
    FOR_STATEMENT_TYPE_TERNARY,
    FOR_STATEMENT_TYPE_RANGE,
} ForStatementType;
/*
 * ForStatement 有两种形式
 *
 * 1. c语言传统 三元For语句
 *    for(index = 0; index < 10; index++) {
 *
 *    }
 *
 * `index = 0`   : ternary_statement.init_expression
 * `index < 10`  : ternary_statement.condition_expression
 * `index++`     : ternary_statement.post_expression
 *
 * 2. 较为现代的 rang语句
 *    for(index, value = range(int_array)) {
 *
 *    }
 *
 * `index, value` : range_statement.assign_identifier_list
 * `int_array`    : range_statement.array_identifier
 */

struct ForStatement {
    unsigned int     line_number;

    ForStatementType type;

    union {
        ForTernaryStatement* ternary_statement;
        ForRangeStatement*   range_statement;
    } u;

    Block* block;
};

struct ForTernaryStatement {
    Expression* init_expression;
    Expression* condition_expression;
    Expression* post_expression;
};

// 类似于 AssignExpression
struct ForRangeStatement {
    Expression* left;
    Expression* operand;
};

struct DoForStatement {
    unsigned int line_number;

    Expression*  init_expression;
    Block*       block;
    Expression*  condition_expression;
    Expression*  post_expression;
};


struct BreakStatement {
    unsigned int line_number;

    unsigned int break_loop_num; // break; break 1; break 2;
};

struct TagDefinitionStatement {
    unsigned int line_number;

    char*        identifier;
};

struct JumpTagStatement {
    unsigned int line_number;

    char*        identifier;
};

struct ContinueStatement {
    unsigned int line_number;
};

struct ReturnStatement {
    unsigned int line_number;

    unsigned int return_list_size;
    Expression*  return_list;
};


struct StdPackageNativeFunction {
    char*               func_name;
    RVM_NativeFuncProc* func_proc;
    int                 arg_count;
    int                 return_list_count;
};

struct StdPackageInfo {
    char*                                 package_name;
    char*                                 path;

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


    ERROR_CODE_GRAMMAR_ERROR            = 100000, // 语法错误


    ERROR_UNDEFINITE_VARIABLE           = 200000,
    ERROR_REDEFINITE_GLOBAL_VARIABLE    = 200001, // 重复定义全局变量
    ERROR_REDEFINITE_FUNCTION           = 200002, // 重复定义函数
    ERROR_MINUS_OPER_INVALID_USE        = 200003, // - 符号 不合法使用
    ERROR_DUPLICATE_IMPORT_PACKAGE      = 200004, // 重复 import package
    ERROR_INVALID_VARIABLE_IDENTIFIER   = 200005, // 不合法的变量标识符
    ERROR_TOO_MANY_LOCAL_VARIABLES      = 200006, // 局部变量数量超过限制
    ERROR_TOO_MANY_FIELDS_IN_CLASS      = 200007, // class 中 field 的数量超过限制
    ERROR_TOO_MANY_METHODS_IN_CLASS     = 200008, // class 中 method 的数量超过限制
    ERROR_MISS_CLASS_DEFINITION         = 200009, // 缺少 class 定义
    ERROR_INVALID_FIELD_IN_CLASS        = 200010, // field 不合法
    ERROR_ARRAY_DIMENSION_INVALID       = 200011, // 数组维度不合法
    ERROR_ASSIGN_TO_METHOD_OF_CLASS     = 200012, // 不能给 class中 method赋值
    ERROR_INVALID_NOT_FOUND_CLASS_FIELD = 200013, // 找不到 class field

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

    RUNTIME_ERR_OUT_OF_ARRAY_RANGE,
} ErrorCode;

struct ErrorMessageInfo {
    ErrorCode   error_code;
    std::string error_messaage;
};

/*
 * */
typedef enum {
    ERROR_REPORT_TYPE_UNKNOW,
    ERROR_REPORT_TYPE_EXIT_NOW, // 立即退出
    ERROR_REPORT_TYPE_COLL_ERR, // 收集错误，等error的数量到达20, 然后再退出
} ErrorReportType;

struct ErrorReportContext {
    Package*        package;
    PackageUnit*    package_unit;

    std::string     source_file_name;
    std::string     line_content;
    unsigned int    line_number;
    unsigned int    column_number;

    std::string     error_message;
    std::string     advice;

    ErrorReportType report_type;


    /*
    ring_compiler_file
    ring_compiler_file_line
        ring 编译器的源文件, 可以快速定位 error-report 所在的位置
    */
    char*        ring_compiler_file;
    unsigned int ring_compiler_file_line;
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

#define MAX_DIMENSION_NUM (8)

/*
 * 默认初始化 64个 bucket
 * 每个bucket 有 1000 个 block
 */
#define MEM_MAX_BUCKET_NUM 2048
#define MEM_INIT_BUCKET_NUM 512

#define MEM_BLOCK_NUM 8
#define MEM_BLOCK_MAX_SIZE (MEM_MAX_BUCKET_NUM * 8)

#define MEM_ALIGN 8
#define MEM_ALIGN_LARGE 16

#define ROUND_UP8(n) \
    (((n) + MEM_ALIGN - 1) & ~(MEM_ALIGN - 1))

#define ROUND_UP16(n) \
    (((n) + MEM_ALIGN_LARGE - 1) & ~(MEM_ALIGN_LARGE - 1))

#define NULL_MEM_POOL nullptr

struct MemPool {
    char*                             name;

    std::vector<MemBlock*>            free_buckets;
    std::vector<MemBlock*>            active_buckets;

    std::unordered_map<void*, size_t> active_mem_map;

    size_t                            free_mem_size;
    size_t                            active_mem_size;

    size_t                            all_mem_size; // 整个生命周期都不变, 用于校验


    /*
     * free_buckets[0]: bucket size = 8;
     * free_buckets[1]: bucket size = 16;
     * free_buckets[2]: bucket size = 24;
     * free_buckets[3]: bucket size = 32;
     * ......
     * free_buckets[63]: bucket size = 512;
     */
};

struct MemBlock {
    void*     data;
    MemBlock* next;
};

// ring 语法报错str
#define DEFINE_ERROR_REPORT_STR                          \
    char compile_err_buf[2048];                          \
    char compile_adv_buf[2048];                          \
    memset(compile_err_buf, 0, sizeof(compile_err_buf)); \
    memset(compile_adv_buf, 0, sizeof(compile_adv_buf));


#define str_eq(str1, str2) (strcmp((str1), (str2)) == 0)

// clear terminal printf
#define CLEAR_SCREEN printf("\e[1;1H\e[2J")

// move cursor to terminal (row, col) location
#define MOVE_CURSOR(row, col) printf("%c[%d;%dH", 27, (row), (col))

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
#define printf_witch_yellow(format, ...) \
    printf("%s" format "%s", LOG_COLOR_YELLOW, ##__VA_ARGS__, LOG_COLOR_CLEAR)
#define printf_witch_blue(format, ...) \
    printf("%s" format "%s", LOG_COLOR_BLUE, ##__VA_ARGS__, LOG_COLOR_CLEAR)
#define printf_witch_purple(format, ...) \
    printf("%s" format "%s", LOG_COLOR_PURPLE, ##__VA_ARGS__, LOG_COLOR_CLEAR)
#define printf_witch_darkgreen(format, ...) \
    printf("%s" format "%s", LOG_COLOR_DARKGREEN, ##__VA_ARGS__, LOG_COLOR_CLEAR)
#define printf_witch_white(format, ...) \
    printf("%s" format "%s", LOG_COLOR_WHITE, ##__VA_ARGS__, LOG_COLOR_CLEAR)


#define complie_err_log(format, ...) \
    printf("%s" format "%s\n", LOG_COLOR_RED, ##__VA_ARGS__, LOG_COLOR_CLEAR)


// debug flex 词法分析
#ifdef DEBUG_FLEX
#define debug_flex_info_with_red(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_RED, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
#else
#define debug_flex_info_with_red(format, ...)
#endif

// debug bison 语法分析
#ifdef DEBUG_BISON
#define debug_bison_info_with_green(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_GREEN, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
#else
#define debug_bison_info_with_green(format, ...)
#endif

// debug 语法分析构建AST
#ifdef DEBUG_CREATE_AST
#define debug_ast_info_with_yellow(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_YELLOW, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
#else
#define debug_ast_info_with_yellow(format, ...)
#endif

// debug 生成 vm opcode
#ifdef DEBUG_GENERATE_DETAIL
#define debug_generate_info_with_darkgreen(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_DARKGREEN, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
#else
#define debug_generate_info_with_darkgreen(format, ...)
#endif

#ifdef DEBUG_EXEC_VM
#define debug_exec_info_with_white(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_WHITE, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
#else
#define debug_exec_info_with_white(format, ...)
#endif


// 以后通用的错误提示统一使用这个
#define ring_error_report(format, ...)                                          \
    fprintf(stderr, "%s[ERROR][%s:%d]\t " format "%s\n",                        \
            LOG_COLOR_RED, __FILE__, __LINE__, ##__VA_ARGS__, LOG_COLOR_CLEAR); \
    exit(1);

/* --------------------
 * string.cpp
 * function definition
 *
 */
Ring_String* new_ring_string();
void         reset_ring_string(Ring_String* string);
void         ring_string_add_char(Ring_String* string, char ch);
char*        get_ring_string(Ring_String* string);
void         init_string_literal_buffer();
void         reset_string_literal_buffer();
void         string_literal_add_char(char ch);
char*        get_string_literal();
// --------------------


/* --------------------
 * compiler.cpp
 * function definition
 *
 */
void           init_front_mem_pool();
MemPool*       get_front_mem_pool();
void           destory_front_mem_pool();

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
std::string    package_unit_get_file_name();
Ring_String*   get_package_unit_current_line_content();
unsigned int   package_unit_get_line_number();
unsigned int   package_unit_increa_line_number();
unsigned int   package_unit_get_column_number();
unsigned int   package_unit_increa_column_number(unsigned int len);
void           package_unit_update_line_content(char* str);
void           package_unit_reset_line_content();
char*          package_unit_get_current_line_content();
void           package_unit_reset_column_number();
std::string    package_unit_get_line_content(unsigned int line_number);
int            package_unit_add_class_definition(ClassDefinition* class_definition);

void           ring_grammar_error(RING_GRAMMAR_ID grammar_id);
int            yyerror(char const* str, ...);

void           ring_compile_error_report(ErrorReportContext* context);
void           ring_check_exit_immediately();
std::string    trans_flex_token_to_human_char(std::string str);
std::string    str_replace_all(std::string        subject,
                               const std::string& search,
                               const std::string& replace);
void           yyin_move_to_next_line();
// --------------------


/* --------------------
 * create_ast.cpp
 * function definition
 *
 */
void                          finish_global_block(Statement* global_statement_list);

Statement*                    statement_list_add_item(Statement* statement_list, Statement* statement);
Statement*                    create_statemen_from_expression(Expression* expression);
void                          add_function_definition(AttributeInfo* attribute_info, Function* function_definition);

Expression*                   expression_add_package_posit(Expression* expression, char* package_posit);
Expression*                   create_expression_identifier(char* identifier);
Expression*                   create_expression_identifier2(char* identifier, IdentifierExpressionType type);
Expression*                   create_expression_identifier_with_index(Expression* array_expression, DimensionExpression* index);
Expression*                   create_expression_from_function_call(FunctionCallExpression* function_call_expression);
Expression*                   create_expression_from_method_call(MethodCallExpression* method_call_expression);
Expression*                   create_expression_from_array_literal(ArrayLiteralExpression* array_literal);
Expression*                   create_expression_from_class_object_literal(ClassObjectLiteralExpression* object_literal);
Expression*                   create_expression_assign(AssignExpression* assign_expression);
Expression*                   create_expression_ternary(Expression* condition, Expression* true_expression, Expression* false_expression);
Expression*                   create_expression_binary(ExpressionType type, Expression* left, Expression* right);
Expression*                   create_expression_unitary(ExpressionType type, Expression* unitary_expression);
Expression*                   create_expression_unitary_with_convert_type(BasicValueType convert_type, Expression* expression);
Expression*                   create_expression_literal(ExpressionType type, char* literal_interface);
Expression*                   create_expression_bool_literal(ExpressionType type, Ring_Bool value);
Expression*                   create_cast_expression(TypeSpecifier* cast_type, Expression* operand);
Expression*                   create_member_expression(Expression* object_expression, char* member_identifier);
Expression*                   create_dot_expression(Expression* prefix_expression, Expression* suffix_expression);
Expression*                   create_new_array_expression(TypeSpecifier* type_specifier, DimensionExpression* dimension_expression);

FieldInitExpression*          create_field_init_expression(char* field_identifier, Expression* init_expression);
FieldInitExpression*          field_init_list_add_item(FieldInitExpression* list, FieldInitExpression* item);
AssignExpression*             create_assign_expression(AssignExpressionType type, Expression* left, Expression* operand);
AssignExpression*             create_multi_assign_expression(Expression* first_left_value_exp,
                                                             Expression* left_value_exp_list,
                                                             Expression* operand);
FunctionCallExpression*       create_function_call_expression(char* identifier, ArgumentList* argument_list);
MethodCallExpression*         create_method_call_expression(Expression* object_expression, char* member_identifier, ArgumentList* argument_list);
ArrayLiteralExpression*       create_array_literal_expression(TypeSpecifier* type_specifier, DimensionExpression* dimension_expression, Expression* expression_list);
ClassObjectLiteralExpression* create_class_object_literal_expression(TypeSpecifier* type_specifier, FieldInitExpression* field_init_expression_list);
Expression*                   expression_list_add_item(Expression* expression_list, Expression* expression);
ArgumentList*                 argument_list_add_item(ArgumentList* argument_list, ArgumentList* argument);
ArgumentList*                 create_argument_list_from_expression(Expression* expression);
Identifier*                   new_identifier(IdentifierType type, char* name);
Identifier*                   identifier_list_add_item(Identifier* identifier_list, Identifier* identifier);
FunctionReturnList*           create_function_return_list(VariableType variable_type);
FunctionReturnList*           function_return_list_add_item(FunctionReturnList* return_list, VariableType variable_type);
Function*                     new_function_definition(FunctionType type, Identifier* identifier, Parameter* parameter_list, FunctionReturnList* return_list, Block* block);

Statement*                    create_statement_from_if(IfStatement* if_statement);
IfStatement*                  create_if_statement(Expression* expression, Block* if_block, ElseIfStatement* elseif_statement_list, Block* else_block);
ElseIfStatement*              create_elseif_statement(Expression* expression, Block* elseif_block);
ElseIfStatement*              elseif_statement_add_item(ElseIfStatement* list, ElseIfStatement* elseif_statement);
Statement*                    create_statement_from_for(ForStatement* for_statement);
ForStatement*                 create_for_ternary_statement(Expression* init_expression, Expression* condition_expression, Expression* post_expression, Block* block);
ForStatement*                 create_for_range_statement(Expression* left, Expression* operand, Block* block);
Statement*                    create_statement_from_dofor(DoForStatement* dofor_statement);
DoForStatement*               create_dofor_statement(Expression* init_expression, Block* block, Expression* condition_expression, Expression* post_expression);
Statement*                    create_statement_from_break(BreakStatement* break_statement);
BreakStatement*               create_break_statement(char* literal_interface);
TagDefinitionStatement*       create_tag_definition_statement(char* identifier);
JumpTagStatement*             create_jump_tag_statement(char* identifier);
Statement*                    create_statement_from_continue(ContinueStatement* continue_statement);
ContinueStatement*            create_continue_statement();
Statement*                    create_statement_from_return(ReturnStatement* return_statement);
Statement*                    create_statement_from_tag_definition(TagDefinitionStatement* tag_def);
Statement*                    create_statement_from_jump_tag(JumpTagStatement* jump_tag_statement);
ReturnStatement*              create_return_statement(Expression* expression);

Block*                        start_new_block();
Block*                        finish_block(Block* block, Statement* statement_list);

DimensionExpression*          create_dimension_expression(SubDimensionExpression* dimension_list);
DimensionExpression*          create_dimension_expression_with_exclam(char* dimension_literal);
SubDimensionExpression*       create_sub_dimension_expression(Expression* num_expression);
SubDimensionExpression*       sub_dimension_expression_list_add_item(SubDimensionExpression* list, SubDimensionExpression* item);

TypeSpecifier*                create_type_specifier(Ring_BasicType basic_type);
TypeSpecifier*                create_type_specifier_array(TypeSpecifier* type, DimensionExpression* dimension);
TypeSpecifier*                create_class_type_specifier(char* identifier);

Declaration*                  create_declaration(TypeSpecifier* type, char* identifier, Expression* initializer);
Declaration*                  declaration_list_add_item(Declaration* head, Declaration* declaration);

Statement*                    create_multi_declaration_statement(TypeSpecifier* type_specifier, Identifier* identifier_list, Expression* initializer_list);
Statement*                    create_declaration_statement(TypeSpecifier* type_specifier, char* identifier, Expression* initializer);

Parameter*                    create_parameter(TypeSpecifier* type, char* identifier, bool is_variadic);
Parameter*                    parameter_list_add_statement(Parameter* head, Parameter* parameter);

Package*                      create_package_info(char* package_name);
void                          import_package_list_add_item(char* package_name, char* rename);

ClassDefinition*              start_class_definition(char* class_identifier);
ClassDefinition*              finish_class_definition(ClassDefinition* class_def, ClassMemberDeclaration* class_member_declar);

ClassMemberDeclaration*       class_member_declaration_list_add_item(ClassMemberDeclaration* list, ClassMemberDeclaration* decl);
ClassMemberDeclaration*       create_class_member_field_declaration(Attribute attribute, FieldMember* field_member);
ClassMemberDeclaration*       create_class_member_method_declaration(Attribute attribute, MethodMember* method_member);
FieldMember*                  create_class_member_field(TypeSpecifier* type_specifier, Identifier* identifier_list);
MethodMember*                 create_class_member_method(FunctionType type, Identifier* identifier, Parameter* parameter_list, FunctionReturnList* return_list, Block* block);


AttributeInfo*                create_attribute_info(char* name);
AttributeInfo*                attribute_info_add_item(AttributeInfo* list, AttributeInfo* item);

Attribute                     add_attribute(Attribute attribute, AttributeType type);
int                           attribute_is_public(Attribute attribute);
int                           attribute_is_private(Attribute attribute);
int                           attribute_is_constructor(Attribute attribute);
int                           attribute_is_destructor(Attribute attribute);
// --------------------


/* --------------------
 * semantic_check.cpp
 * function definition
 *
 */
void ring_compiler_semantic_analysis(Package* package);

void ring_compiler_analysis_import_package(Package* package);
void ring_compiler_analysis_global_variable(Package* package);
void ring_compiler_analysis_function(Package* package);
void ring_compiler_analysis_class(Package* package);

void ring_compiler_check_exit(Package* package);
// --------------------


/* --------------------
 * fix.cpp
 * function definition
 *
 */
void                    ring_compiler_fix_ast(Package* package);
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
void                    fix_class_field(ClassDefinition* class_definition, FieldMember* field);
void                    fix_class_method(ClassDefinition* class_definition, MethodMember* method);


void                    fix_array_index_expression(Expression*           expression,
                                                   ArrayIndexExpression* array_index_expression,
                                                   Block*                block,
                                                   Function*             func);
void                    fix_new_array_expression(Expression* expression, NewArrayExpression* new_array_expression, Block* block, Function* func);
void                    fix_dimension_expression(DimensionExpression* dimension_expression, Block* block, Function* func);
void                    fix_array_literal_expression(Expression* expression, ArrayLiteralExpression* array_literal_expression, Block* block, Function* func);

void                    fix_class_object_literal_expression(Expression* expression, ClassObjectLiteralExpression* literal_expression, Block* block, Function* func);
void                    fix_member_expression(Expression* expression, MemberExpression* member_expression, Block* block, Function* func);
void                    fix_dot_expression(Expression* expression, DotExpression* dot_expression, Block* block, Function* func);
void                    fix_class_member_expression(MemberExpression* member_expression, Expression* object_expression, char* member_identifier);
ClassDefinition*        search_class_definition(char* class_identifier);
ClassMemberDeclaration* search_class_member(ClassDefinition* class_definition, char* member_identifier);
void                    fix_ternary_condition_expression(TernaryExpression* ternary_expression, Block* block, Function* func);
void                    add_parameter_to_declaration(Parameter* parameter, Block* block);
Declaration*            search_declaration(char* package_posit, char* identifier, Block* block);
Function*               search_function(char* package_posit, char* identifier);
int                     is_native_function_identifier(char* package_posit, char* identifier);
// --------------------


/* --------------------
 * generate.cpp
 * function definition
 *
 */
Package_Executer* package_executer_create(ExecuterEntry* executer_entry, char* package_name);
void              print_package_executer(Package_Executer* package_executer);
void              package_executer_dump(Package_Executer* package_executer);

void              ring_generate_vm_code(Package* package, Package_Executer* executer);
void              ring_generate_vm_code(CompilerEntry* compiler_entry, ExecuterEntry* executer_entry);
void              add_global_variable(Package* package, Package_Executer* executer);
void              add_functions(Package* package, Package_Executer* executer);
void              add_classes(Package* package, Package_Executer* executer);
void              class_def_deep_copy(Package_Executer* executer, RVM_ClassDefinition* dst, ClassDefinition* src);

void              copy_function(Package_Executer* executer, RVM_Function* dst, Function* src);
void              copy_method(Package_Executer* executer, RVM_Method* dst, MethodMember* src);
void              copy_field(Package_Executer* executer, RVM_Field* dst, FieldMember* src);

void              add_top_level_code(Package* package, Package_Executer* executer);
void              generate_code_from_function_definition(Package_Executer* executer, RVM_Function* dst, Function* src);
void              generate_code_from_method_definition(Package_Executer* executer, RVM_Method* dst, MethodMember* src);
void              vm_executer_dump(Package_Executer* executer);
RVM_OpcodeBuffer* new_opcode_buffer();

void              generate_vmcode_from_block(Package_Executer* executer, Block* block, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_statement_list(Package_Executer* executer, Block* block, Statement* statement_list, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_if_statement(Package_Executer* executer, IfStatement* if_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_for_statement(Package_Executer* executer, ForStatement* for_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_for_ternary_statement(Package_Executer* executer, ForStatement* for_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_for_range_statement(Package_Executer* executer, ForStatement* for_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_dofor_statement(Package_Executer* executer, DoForStatement* dofor_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_break_statement(Package_Executer* executer, Block* block, BreakStatement* break_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_continue_statement(Package_Executer* executer, Block* block, ContinueStatement* continue_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_return_statement(Package_Executer* executer, Block* block, ReturnStatement* return_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_initializer(Package_Executer* executer, Block* block, Declaration* declaration, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_jump_tag_statement(Package_Executer* executer, Block* block, JumpTagStatement* jump_tag_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_assign_expression(Package_Executer* executer, AssignExpression* expression, RVM_OpcodeBuffer* new_opcode_buffer);
void              generate_pop_to_leftvalue_reverse(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_pop_to_leftvalue(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_pop_to_leftvalue_identifier(Package_Executer* executer, IdentifierExpression* identifier_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_pop_to_leftvalue_member(Package_Executer* executer, MemberExpression* member_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_pop_to_leftvalue_array_index(Package_Executer* executer, ArrayIndexExpression* array_index_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_logical_expression(Package_Executer* executer, BinaryExpression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode);
void              generate_vmcode_from_binary_expression(Package_Executer* executer, BinaryExpression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode);
void              generate_vmcode_from_unitary_minus_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode);
void              generate_vmcode_from_unitary_not_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode);
void              generate_vmcode_from_increase_decrease_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_identifier_expression(Package_Executer* executer, IdentifierExpression* identifier_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_bool_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_int_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_double_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_string_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_function_call_expression(Package_Executer* executer, FunctionCallExpression* function_call_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_native_function_call_expression(Package_Executer* executer, FunctionCallExpression* function_call_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_method_call_expression(Package_Executer* executer, MethodCallExpression* method_call_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_cast_expression(Package_Executer* executer, CastExpression* cast_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_member_expression(Package_Executer* executer, MemberExpression* member_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_ternary_condition_expression(Package_Executer* executer, TernaryExpression* ternary_expression, RVM_OpcodeBuffer* opcode_buffer);

void              generate_vmcode_from_new_array_expression(Package_Executer* executer, NewArrayExpression* new_array_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_class_object_literal_expreesion(Package_Executer* executer, ClassObjectLiteralExpression* literal_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_array_literal_expreesion(Package_Executer* executer, ArrayLiteralExpression* array_literal_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_array_index_expression(Package_Executer* executer, ArrayIndexExpression* array_index_expression, RVM_OpcodeBuffer* opcode_buffer);

void              generate_vmcode(Package_Executer* executer, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode, unsigned int int_literal, unsigned int line_number);

int               constant_pool_grow(Package_Executer* executer, unsigned int growth_size);
int               constant_pool_add_int(Package_Executer* executer, int int_literal);
int               constant_pool_add_double(Package_Executer* executer, double double_literal);
int               constant_pool_add_string(Package_Executer* executer, char* string_literal);

unsigned int      opcode_buffer_get_label(RVM_OpcodeBuffer* opcode_buffer);
void              opcode_buffer_set_label(RVM_OpcodeBuffer* opcode_buffer, unsigned int label, unsigned int label_address);
void              opcode_buffer_fix_label(RVM_OpcodeBuffer* opcode_buffer);
RVM_Opcode        convert_opcode_by_rvm_type(RVM_Opcode opcode, TypeSpecifier* type);
unsigned int      calc_runtime_stack_capacity(RVM_Byte* code_list, unsigned int code_size);
void              add_code_line_map(RVM_OpcodeBuffer* opcode_buffer, unsigned int line_number, unsigned int start_pc, unsigned int opcode_size);
void              dump_code_line_map(std::vector<RVM_SourceCodeLineMap>& code_line_map);
void              type_specifier_deep_copy(RVM_TypeSpecifier* dst, TypeSpecifier* src);
// --------------------


/* --------------------
 * execute.cpp
 * function definition
 *
 */

RVM_RuntimeStack*    new_runtime_stack();
RVM_RuntimeStatic*   new_runtime_static();
RVM_RuntimeHeap*     new_runtime_heap();
Ring_VirtualMachine* ring_virtualmachine_create();

void                 ring_virtualmachine_load_executer(Ring_VirtualMachine* rvm, ExecuterEntry* executer_entry);
void                 rvm_add_static_variable(Package_Executer* executer, RVM_RuntimeStatic* runtime_static);
void                 ring_virtualmachine_init(Ring_VirtualMachine* rvm);
void                 rvm_add_static_variable(Package_Executer* executer, RVM_RuntimeStatic* runtime_static);
void                 rvm_init_static_variable(Ring_VirtualMachine* rvm, Package_Executer* executer, RVM_RuntimeStatic* runtime_static);
RVM_String*          new_string_object(Ring_VirtualMachine* rvm);
void                 ring_execute_vm_code(Ring_VirtualMachine* rvm);
void                 invoke_native_function(Ring_VirtualMachine* rvm, RVM_Function* function, unsigned int argument_list_size);
void                 invoke_derive_function(Ring_VirtualMachine* rvm,
                                            RVM_Function**       caller_function,
                                            RVM_ClassObject* callee_object, RVM_Function* callee_function,
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
void                 store_callinfo(Ring_VirtualMachine* rvm, RVM_CallInfo* call_info);
void                 restore_callinfo(Ring_VirtualMachine* rvm, RVM_CallInfo** call_info);
void                 init_derive_function_local_variable(Ring_VirtualMachine* rvm,
                                                         RVM_ClassObject* callee_object, RVM_Function* function);

RVM_String*          string_literal_to_rvm_string(Ring_VirtualMachine* rvm, const char* string_literal);
RVM_String*          concat_string(Ring_VirtualMachine* rvm, RVM_String* a, RVM_String* b);

RVM_Array*           rvm_new_array(Ring_VirtualMachine* rvm,
                                   unsigned int         dimension,
                                   unsigned int*        dimension_list,
                                   unsigned int         dimension_index,
                                   RVM_Array_Type       array_type,
                                   RVM_ClassDefinition* class_definition);

RVM_Array*           rvm_new_array_bool(Ring_VirtualMachine* rvm,
                                        unsigned int         dimension,
                                        unsigned int*        dimension_list);
RVM_Array*           rvm_new_array_int(Ring_VirtualMachine* rvm,
                                       unsigned int         dimension,
                                       unsigned int*        dimension_list);
RVM_Array*           rvm_new_array_double(Ring_VirtualMachine* rvm,
                                          unsigned int         dimension,
                                          unsigned int*        dimension_list);
RVM_Array*           rvm_new_array_string(Ring_VirtualMachine* rvm,
                                          unsigned int         dimension,
                                          unsigned int*        dimension_list);
RVM_Array*           rvm_new_array_class_object(Ring_VirtualMachine* rvm,
                                                RVM_ClassDefinition* class_definition,
                                                unsigned int         dimension,
                                                unsigned int*        dimension_list);

RVM_ClassObject*     rvm_new_class_object(Ring_VirtualMachine* rvm, RVM_ClassDefinition* class_definition);
RVM_Array*           rvm_new_array_literal_bool(Ring_VirtualMachine* rvm, unsigned int size);
RVM_Array*           rvm_new_array_literal_int(Ring_VirtualMachine* rvm, unsigned int size);
RVM_Array*           rvm_new_array_literal_double(Ring_VirtualMachine* rvm, unsigned int size);
RVM_Array*           rvm_new_array_literal_string(Ring_VirtualMachine* rvm, unsigned int size);


void                 rvm_array_get_length(Ring_VirtualMachine* rvm, RVM_Array* array, int* value);
void                 rvm_array_get_capacity(Ring_VirtualMachine* rvm, RVM_Array* array, int* value);

void                 rvm_string_get_length(Ring_VirtualMachine* rvm, RVM_String* string, int* value);
void                 rvm_string_get_capacity(Ring_VirtualMachine* rvm, RVM_String* string, int* value);

ErrorCode            rvm_array_get_array(Ring_VirtualMachine* rvm, RVM_Array* array, int index, RVM_Array** value);

ErrorCode            rvm_array_get_bool(Ring_VirtualMachine* rvm, RVM_Array* array, int index, bool* value);
ErrorCode            rvm_array_set_bool(Ring_VirtualMachine* rvm, RVM_Array* array, int index, bool* value);
ErrorCode            rvm_array_append_bool(Ring_VirtualMachine* rvm, RVM_Array* array, bool* value);
ErrorCode            rvm_array_pop_bool(Ring_VirtualMachine* rvm, RVM_Array* array, bool* value);

ErrorCode            rvm_array_get_int(Ring_VirtualMachine* rvm, RVM_Array* array, int index, int* value);
ErrorCode            rvm_array_set_int(Ring_VirtualMachine* rvm, RVM_Array* array, int index, int* value);
ErrorCode            rvm_array_append_int(Ring_VirtualMachine* rvm, RVM_Array* array, int* value);
ErrorCode            rvm_array_pop_int(Ring_VirtualMachine* rvm, RVM_Array* array, int* value);

ErrorCode            rvm_array_get_double(Ring_VirtualMachine* rvm, RVM_Array* array, int index, double* value);
ErrorCode            rvm_array_set_double(Ring_VirtualMachine* rvm, RVM_Array* array, int index, double* value);
ErrorCode            rvm_array_append_double(Ring_VirtualMachine* rvm, RVM_Array* array, double* value);
ErrorCode            rvm_array_pop_double(Ring_VirtualMachine* rvm, RVM_Array* array, double* value);

ErrorCode            rvm_array_get_string(Ring_VirtualMachine* rvm, RVM_Array* array, int index, RVM_String** value);
ErrorCode            rvm_array_set_string(Ring_VirtualMachine* rvm, RVM_Array* array, int index, RVM_String** value);
ErrorCode            rvm_array_append_string(Ring_VirtualMachine* rvm, RVM_Array* array, RVM_String** value);
ErrorCode            rvm_array_pop_string(Ring_VirtualMachine* rvm, RVM_Array* array, RVM_String** value);

ErrorCode            rvm_array_get_class_object(Ring_VirtualMachine* rvm, RVM_Array* array, int index, RVM_ClassObject** value);
ErrorCode            rvm_array_set_class_object(Ring_VirtualMachine* rvm, RVM_Array* array, int index, RVM_ClassObject** value);
ErrorCode            rvm_array_append_class_object(Ring_VirtualMachine* rvm, RVM_Array* array, RVM_ClassObject** value);
ErrorCode            rvm_array_pop_class_object(Ring_VirtualMachine* rvm, RVM_Array* array, RVM_ClassObject** value);


RVM_String*          rvm_heap_new_string(Ring_VirtualMachine* rvm);
RVM_String*          rvm_deep_copy_string(Ring_VirtualMachine* rvm, RVM_String* src);

RVM_String*          rvm_bool_2_string(Ring_VirtualMachine* rvm, bool value);
RVM_String*          rvm_int_2_string(Ring_VirtualMachine* rvm, int value);
RVM_String*          rvm_double_2_string(Ring_VirtualMachine* rvm, double value);

RVM_Array*           rvm_heap_new_empty_array(Ring_VirtualMachine* rvm);
RVM_Array*           rvm_deep_copy_array(Ring_VirtualMachine* rvm, RVM_Array* src);
RVM_ClassObject*     rvm_heap_new_class_object(Ring_VirtualMachine* rvm);
RVM_ClassObject*     rvm_deep_copy_class_object(Ring_VirtualMachine* rvm, RVM_ClassObject* src);
int                  rvm_string_cmp(RVM_String* string1, RVM_String* string2);

void                 rvm_free_object(Ring_VirtualMachine* rvm, RVM_Object* object);
unsigned int         rvm_free_string(Ring_VirtualMachine* rvm, RVM_String* string);
unsigned int         rvm_free_array(Ring_VirtualMachine* rvm, RVM_Array* array);
unsigned int         rvm_free_class_object(Ring_VirtualMachine* rvm, RVM_ClassObject* class_object);


int                  rvm_heap_size(Ring_VirtualMachine* rvm);

void                 debug_rvm(Ring_VirtualMachine* rvm, RVM_Function* function, RVM_Byte* code_list, unsigned int code_size, unsigned int pc, unsigned int caller_stack_base);
// --------------------


/* --------------------
 * bytecode.cpp
 * function definition
 *
 */
void ring_bytecode_dump(Package_Executer* executer, FILE* output);
void ring_bytecode_load(Package_Executer* executer, FILE* input);
// --------------------


/* --------------------
 * std_lib.cpp
 * function definition
 *
 */
void      register_lib(Package_Executer* package_executer, char* func_name, RVM_NativeFuncProc* func_proc, int arg_count, int return_list_count);

RVM_Value std_lib_os_exit(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);

RVM_Value std_lib_io_write(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);

RVM_Value std_lib_fmt_println_bool(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value std_lib_fmt_println_int(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value std_lib_fmt_println_double(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value std_lib_fmt_println_string(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value std_lib_fmt_println_pointer(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value std_lib_fmt_println(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);

RVM_Value std_lib_debug_debug_assert(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value std_lib_debug_print_call_stack(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);

RVM_Value std_lib_vm_heap_size(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value std_lib_vm_garbage_collect(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);

RVM_Value std_lib_reflect_typeof(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);

RVM_Value std_lib_math_sqrt(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
// --------------------


/* --------------------
 * vm.cpp
 * function definition
 *
 */
std::string format_rvm_function(RVM_Function* function);
std::string format_rvm_type_specifier(RVM_TypeSpecifier* type_specifier);
// --------------------

/* --------------------
 * utils.cpp
 * function definition
 *
 */
void                     ring_compiler_functions_dump(PackageUnit* package_unit);
void                     ring_vm_constantpool_dump(Package_Executer* executer);
void                     ring_vm_code_dump(RVM_Function* function, RVM_Byte* code_list, unsigned int code_size, unsigned int pc, unsigned int screen_row, unsigned int screen_col);
void                     ring_vm_dump_runtime_stack(RVM_RuntimeStack* runtime_stack, unsigned int caller_stack_base, unsigned int screen_row, unsigned int screen_col);
void                     ring_vm_dump_stdout_log(Ring_VirtualMachine* rvm);
std::vector<std::string> list_files_of_dir(char* dir);

void                     dump_vm_function(RVM_ClassDefinition* class_definition, RVM_Function* function);
void                     dump_vm_class(RVM_ClassDefinition* class_definition);
std::string              dump_vm_constant(RVM_ConstantPool* constant);

unsigned int             get_source_line_number_by_pc(RVM_Function* function, unsigned int pc);
// --------------------


/* --------------------
 * man_help.cpp
 * function definition
 *
 */
void ring_give_man_help(char* keyword);
// --------------------

/* --------------------
 * mem_pool.cpp
 * function definition
 *
 */
MemPool* create_mem_pool(char* name);
void     destory_mem_pool(MemPool* pool);

void     dump_mem_pool(MemPool* pool);
void*    mem_alloc(MemPool* pool, size_t size);
void*    mem_realloc(MemPool* pool, void* ptr, size_t old_size, size_t new_size);
void     mem_free(MemPool* pool, void* ptr, size_t size);
void     test_mem_pool();
// --------------------

/* --------------------
 * gc.cpp
 * function definition
 *
 */
void gc(Ring_VirtualMachine* rvm);
void gc_summary(Ring_VirtualMachine* rvm);
void gc_mark(Ring_VirtualMachine* rvm);
void gc_sweep(Ring_VirtualMachine* rvm);
// --------------------


/* --------------------
 * thread_pool.c
 * function definition
 *
 */
typedef struct thpool_* threadpool;
threadpool              thpool_init(int num_threads);
int                     thpool_add_work(threadpool, void (*function_p)(void*), void* arg_p);
void                    thpool_wait(threadpool);
void                    thpool_pause(threadpool);
void                    thpool_resume(threadpool);
void                    thpool_destroy(threadpool);
int                     thpool_num_threads_working(threadpool);
// --------------------


#endif // RING_INCLUDE_H
