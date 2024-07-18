
#ifndef RING_INCLUDE_H
#define RING_INCLUDE_H

#include "linenoise.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define RING_VERSION "ring-v0.2.15-beta Copyright (C) 2021-2024 ring.wiki, ZhenhuLi"


typedef struct Ring_Command_Arg             Ring_Command_Arg;
typedef struct Ring_VirtualMachine          Ring_VirtualMachine;
typedef struct ImportPackageInfo            ImportPackageInfo;
typedef struct CompilerEntry                CompilerEntry;
typedef struct ExecuterEntry                ExecuterEntry;
typedef struct Package_Executer             Package_Executer;
typedef struct Package                      Package;
typedef struct PackageUnit                  PackageUnit;
typedef struct RingFileStat                 RingFileStat;
typedef struct SourceLineInfo               SourceLineInfo;

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
typedef struct KeyExpression                KeyExpression;
typedef struct MemberExpression             MemberExpression;
typedef struct MemberExpressionV2           MemberExpressionV2;
typedef struct DimensionExpression          DimensionExpression;
typedef struct SubDimensionExpression       SubDimensionExpression;
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
typedef struct FunctionTuple                FunctionTuple;
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
typedef struct RDB_Command                  RDB_Command;
typedef struct RVM_DebugConfig              RVM_DebugConfig;
typedef struct RVM_BreakPoint               RVM_BreakPoint;
typedef struct RVM_Frame                    RVM_Frame;
typedef struct ErrorMessageInfo             ErrorMessageInfo;
typedef struct ErrorReportContext           ErrorReportContext;

typedef struct AttributeInfo                AttributeInfo;

typedef struct RVM_ConstantPool             RVM_ConstantPool;
typedef struct RVM_String                   RVM_String;
typedef struct RVM_Array                    RVM_Array;
typedef struct RVM_ClassObject              RVM_ClassObject;
typedef struct RVM_GC_Object                RVM_GC_Object;
typedef struct RVM_BasicTypeSpecifier       RVM_BasicTypeSpecifier;
typedef struct RVM_TypeSpecifier            RVM_TypeSpecifier;

typedef struct RVM_Parameter                RVM_Parameter;
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

typedef enum : unsigned char {
    RVM_VALUE_TYPE_UNKNOW,

    RVM_VALUE_TYPE_BOOL,
    RVM_VALUE_TYPE_INT,
    RVM_VALUE_TYPE_INT64,
    RVM_VALUE_TYPE_DOUBLE,
    RVM_VALUE_TYPE_STRING,
    RVM_VALUE_TYPE_CLASS_OB,
    RVM_VALUE_TYPE_ARRAY,

} RVM_Value_Type;

typedef enum : int {
    RVM_FALSE,
    RVM_TRUE,
} RVM_Bool;

/*
 * 在这里有个问题:
 * 如果没有 RVM_Value.type 的时候, size(RVM_Value)=8,
 * 如果有 RVM_Value.type 的时候, size(RVM_Value)=16,
 * 因为内存对齐的原因导致8字节被浪费了, 这里需要优化一下
 *
 * TIP-1: 为什么 bool_value 的类型为 int
 *        这样在 vm实现字节码的时候, 可以少实现一个, bool_value int_value 比较方法一致
 */
typedef struct {
    RVM_Value_Type type;
    union {
        RVM_Bool         bool_value;
        int              int_value;
        long long        int64_value;
        double           double_value;
        RVM_String*      string_value;
        RVM_ClassObject* class_ob_value;
        RVM_Array*       array_value;
    } u;

} RVM_Value;


// Ring 源代码的相关信息
struct RingFileStat {
    std::string dir;           // 文件path的绝对路径
    std::string file_name;     // 文件的名称
    std::string abs_path;      // 文件全路径的绝对路径
    long long   last_modified; // last_modified 时间戳, 后续使用md5

    FILE*       fp; // 随机访问 fp

    // 该文件每行的偏移量，用于快速获取某行的内容
    // line_offset_map[0] 没有意义，因为文件都是从第1行开始的
    // line_offset_map[3] 表示第3行开始的文件字节偏移量 和 字节大小
    // 可通过 fseek() 快速获取某行的内容
    std::vector<SourceLineInfo> line_offset_map;
};

typedef int (*TraceDispacth)(RVM_Frame* frame, const char* event, const char* arg);

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

    bool                 exist_main_func;
    unsigned int         main_func_index;
    bool                 exist_global_init_func;
    unsigned int         global_init_func_index;

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
    CompilerEntry*           compiler_entry;
    unsigned int             package_index; // 在 CompilerEntry 中的 index
    char*                    package_name;
    char*                    package_path;

    std::vector<std::string> source_file_list;

    // 当前 一个 package中只能有一个源文件，所以当前的设计是符合要求的
    // 如果后续 一个packag中含有多个源文件，可能得需要这样设计：
    // std::vecotr<<std::pair<unsigned int, Statment*>>  global_decl_list;
    // 代表了 该package下所有的 global变量，分布在 多个 global{} 块中。
    // pair.first 是 size
    // pair.second 就是 global_statement_list
    std::vector<std::pair<unsigned int, Statement*>>  global_block_statement_list;
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

    std::vector<std::string>                          shell_args;
    // shell_args 只有 main-package 才会用到
    // e.g.  ./bin/ring run ./test.ring args1 args2
    // shell_args 就是 [args1, args2]
};

struct SourceLineInfo {
    off_t        start_offset; // 某行相对于文件开始的偏移
    unsigned int size;         // 某行的字符数量
};

/*
 * PackageUnit 与 Package 的逻辑关系
 *
 * 一个PackageUnit 对应一个 Ring 源码文件
 * 每个 PackageUnit 都有一个对应的 Package
 * 一个 Package 可以有多个 PackageUnit
 */
struct PackageUnit {
    Package*      parent_package;

    RingFileStat* ring_file_stat; // ring源代码文件信息
    std::string   current_file_name;
    FILE*         current_file_fp; // 这个 FILE* 只能给 bison使用
    FILE*         file_fp_random;  // 用来随机fseek并获取文件内容

    unsigned int  current_line_number;
    unsigned int  current_column_number;
    Ring_String*  current_line_content;

    // 该文件每行的偏移量，用于快速获取某行的内容
    // line_offset_map[0] 没有意义，因为文件都是从第1行开始的
    // line_offset_map[3] 表示第3行开始的文件字节偏移量 和 字节大小
    // 可通过 fseek() 快速获取某行的内容
    off_t                           current_line_start_offset;
    off_t                           current_offset;
    std::vector<SourceLineInfo>     line_offset_map;

    std::vector<ImportPackageInfo*> import_package_list;

    unsigned int                    global_block_statement_list_size;
    Statement*                      global_block_statement_list;

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
    RING_BASIC_TYPE_INT64,
    RING_BASIC_TYPE_DOUBLE,
    RING_BASIC_TYPE_STRING,
    RING_BASIC_TYPE_CLASS,
    RING_BASIC_TYPE_ARRAY,

    RING_BASIC_TYPE_ANY,

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
    ClassDefinition* class_definition; // UPDATED_BY_FIX_AST
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
    // 只有当 kind == array, sub才用了指明数组中元素的类型,
    // TODO: 后续应该把 sub放在 array_type中
};

#define TYPE_IS_STRING_ARRAY_1(type_specifier)         \
    (((type_specifier)->kind == RING_BASIC_TYPE_ARRAY) \
     && ((type_specifier)->dimension == 1)             \
     && ((type_specifier)->sub != nullptr)             \
     && ((type_specifier)->sub->kind == RING_BASIC_TYPE_STRING))

typedef RVM_Value RVM_NativeFuncProc(Ring_VirtualMachine* rvm, unsigned int arg_cout, RVM_Value* args);

typedef enum {
    RVM_FUNCTION_TYPE_UNKNOW,
    RVM_FUNCTION_TYPE_NATIVE, // 原生函数
    RVM_FUNCTION_TYPE_DERIVE, // 派生函数，库函数，Ring编写的库函数
} RVMFunctionType;

struct RVM_Parameter {
    RVM_TypeSpecifier* type_specifier;
    bool               is_variadic; // variadic parameter function can be called with any number of trailing arguments.
    char*              identifier;
};

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

    RingFileStat*      ring_file_stat; // 所属的 ring 源代码文件,

    char*              identifier;
    RVMFunctionType    type;

    unsigned int       parameter_size;
    RVM_Parameter*     parameter_list; // TODO: parameter_list 保存的信息还不是特别多, 需要继续优化

    unsigned int       local_variable_size;
    RVM_LocalVariable* local_variable_list; // TODO: parameter_list 保存的信息还不是特别多, 需要继续优化
    // local_variable_list 是包含 parameter_list的, 因为 会通过访问局部变量的方式 访问 parameter

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


typedef enum {
    CONSTANTPOOL_TYPE_UNKNOW,
    CONSTANTPOOL_TYPE_INT,
    CONSTANTPOOL_TYPE_INT64,
    CONSTANTPOOL_TYPE_DOUBLE,
    CONSTANTPOOL_TYPE_STRING,
} ConstantPoolType;

struct RVM_ConstantPool {
    ConstantPoolType type;
    union {
        int         int_value;
        long long   int64_value;
        double      double_value;
        const char* string_value;
    } u;
};

struct RVM_Variable {
    char*              identifier;
    RVM_TypeSpecifier* type_specifier;
};


typedef enum {
    RVM_OBJECT_TYPE_UNKNOW,
    RVM_GC_OBJECT_TYPE_STRING,
    RVM_GC_OBJECT_TYPE_CLASS_OB,
    RVM_GC_OBJECT_TYPE_ARRAY,
} RVM_GC_Object_Type;

typedef enum {
    GC_MARK_COLOR_UNKNOW,
    GC_MARK_COLOR_WHITE, // 需要被回收
    GC_MARK_COLOR_BLACK, // 不需要被回收
} GC_Mark;


#define RVM_GC_Object_Header    \
    RVM_GC_Object_Type gc_type; \
    GC_Mark            gc_mark; \
    RVM_GC_Object*     gc_prev; \
    RVM_GC_Object*     gc_next;

struct RVM_GC_Object {
    RVM_GC_Object_Header;
};


struct RVM_String {
    RVM_GC_Object_Header;

    char*        data;
    unsigned int length;
    unsigned int capacity;
};

typedef enum {
    RVM_ARRAY_UNKNOW,
    RVM_ARRAY_BOOL,         // bool 数组
    RVM_ARRAY_INT,          // int 数组
    RVM_ARRAY_INT64,        // int64 数组
    RVM_ARRAY_DOUBLE,       // double 数组
    RVM_ARRAY_STRING,       // string 数组
    RVM_ARRAY_CLASS_OBJECT, // 类 数组
    RVM_ARRAY_A,            // 多维数组的中间态， 感觉有必要删除
} RVM_Array_Type;


struct RVM_Array {
    RVM_GC_Object_Header;

    RVM_Array_Type type;
    unsigned char  dimension;
    unsigned int   length;
    unsigned int   capacity;

    // 这里实现的不太好，信息冗余了
    // 只有当 type == RVM_ARRAY_CLASS_OBJECT 才有意义
    RVM_ClassDefinition* class_ref;


    union {
        bool*            bool_array;
        int*             int_array;
        long long*       int64_array;
        double*          double_array;
        RVM_String**     string_array;
        RVM_ClassObject* class_ob_array;
        RVM_Array*       a_array; // 多维数组
    } u;
};


struct RVM_ClassObject {
    RVM_GC_Object_Header;

    RVM_ClassDefinition* class_ref;
    unsigned int         field_count;
    RVM_Value*           field;
};


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
    unsigned int   alloc_size;
    unsigned int   threshold;
    RVM_GC_Object* list;
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
    OPCODE_OPERAND_TYPE_1BYTE_A,   // 后边1BYTE操作数, pc+2
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
     * usage_comment:    简要描述一个字节码相关的操作
     * stack_top_change: 对 runtime_stack 的操作变化
     * math_formula:     通过一个数学公式描述字节码操作
     */
    std::string usage_comment;
    std::string stack_top_change;
    std::string math_formula;
};

typedef enum {
    RVM_CODE_UNKNOW = 0,

    // int double string const
    RVM_CODE_PUSH_BOOL,
    RVM_CODE_PUSH_INT_1BYTE, // operand 0-255
    RVM_CODE_PUSH_INT_2BYTE, // operand 256-65535
    RVM_CODE_PUSH_INT,       // bigger 65535
    RVM_CODE_PUSH_INT64,     // bigger 65535
    RVM_CODE_PUSH_DOUBLE,
    RVM_CODE_PUSH_STRING,

    // static
    RVM_CODE_POP_STATIC_BOOL,
    RVM_CODE_POP_STATIC_INT,
    RVM_CODE_POP_STATIC_INT64,
    RVM_CODE_POP_STATIC_DOUBLE,
    RVM_CODE_POP_STATIC_STRING,
    RVM_CODE_POP_STATIC_CLASS_OB,
    RVM_CODE_POP_STATIC_ARRAY,
    RVM_CODE_PUSH_STATIC_BOOL,
    RVM_CODE_PUSH_STATIC_INT,
    RVM_CODE_PUSH_STATIC_INT64,
    RVM_CODE_PUSH_STATIC_DOUBLE,
    RVM_CODE_PUSH_STATIC_STRING,
    RVM_CODE_PUSH_STATIC_CLASS_OB,
    RVM_CODE_PUSH_STATIC_ARRAY,


    // stack
    RVM_CODE_POP_STACK_BOOL,
    RVM_CODE_POP_STACK_INT,
    RVM_CODE_POP_STACK_INT64,
    RVM_CODE_POP_STACK_DOUBLE,
    RVM_CODE_POP_STACK_STRING,
    RVM_CODE_POP_STACK_CLASS_OB,
    RVM_CODE_POP_STACK_ARRAY,
    RVM_CODE_PUSH_STACK_BOOL,
    RVM_CODE_PUSH_STACK_INT,
    RVM_CODE_PUSH_STACK_INT64,
    RVM_CODE_PUSH_STACK_DOUBLE,
    RVM_CODE_PUSH_STACK_STRING,
    RVM_CODE_PUSH_STACK_CLASS_OB,
    RVM_CODE_PUSH_STACK_ARRAY,

    // array
    RVM_CODE_PUSH_ARRAY_A,
    RVM_CODE_PUSH_ARRAY_BOOL,
    RVM_CODE_PUSH_ARRAY_INT,
    RVM_CODE_PUSH_ARRAY_INT64,
    RVM_CODE_PUSH_ARRAY_DOUBLE,
    RVM_CODE_PUSH_ARRAY_STRING,
    RVM_CODE_PUSH_ARRAY_CLASS_OB,

    RVM_CODE_POP_ARRAY_A,
    RVM_CODE_POP_ARRAY_BOOL,
    RVM_CODE_POP_ARRAY_INT,
    RVM_CODE_POP_ARRAY_INT64,
    RVM_CODE_POP_ARRAY_DOUBLE,
    RVM_CODE_POP_ARRAY_STRING,
    RVM_CODE_POP_ARRAY_CLASS_OB,

    // array append
    RVM_CODE_ARRAY_APPEND_BOOL,
    RVM_CODE_ARRAY_APPEND_INT,
    RVM_CODE_ARRAY_APPEND_INT64,
    RVM_CODE_ARRAY_APPEND_DOUBLE,
    RVM_CODE_ARRAY_APPEND_STRING,
    RVM_CODE_ARRAY_APPEND_CLASS_OB,
    // array pop
    RVM_CODE_ARRAY_POP_BOOL,
    RVM_CODE_ARRAY_POP_INT,
    RVM_CODE_ARRAY_POP_INT64,
    RVM_CODE_ARRAY_POP_DOUBLE,
    RVM_CODE_ARRAY_POP_STRING,
    RVM_CODE_ARRAY_POP_CLASS_OB,

    // class
    RVM_CODE_POP_FIELD_BOOL,
    RVM_CODE_POP_FIELD_INT,
    RVM_CODE_POP_FIELD_INT64,
    RVM_CODE_POP_FIELD_DOUBLE,
    RVM_CODE_POP_FIELD_STRING,
    RVM_CODE_POP_FIELD_CLASS_OB,
    RVM_CODE_POP_FIELD_ARRAY,
    RVM_CODE_PUSH_FIELD_BOOL,
    RVM_CODE_PUSH_FIELD_INT,
    RVM_CODE_PUSH_FIELD_INT64,
    RVM_CODE_PUSH_FIELD_DOUBLE,
    RVM_CODE_PUSH_FIELD_STRING,
    RVM_CODE_PUSH_FIELD_CLASS_OB,
    RVM_CODE_PUSH_FIELD_ARRAY,

    // arithmetic
    RVM_CODE_ADD_INT,
    RVM_CODE_ADD_INT64,
    RVM_CODE_ADD_DOUBLE,

    RVM_CODE_SUB_INT,
    RVM_CODE_SUB_INT64,
    RVM_CODE_SUB_DOUBLE,

    RVM_CODE_MUL_INT,
    RVM_CODE_MUL_INT64,
    RVM_CODE_MUL_DOUBLE,

    RVM_CODE_DIV_INT,
    RVM_CODE_DIV_INT64,
    RVM_CODE_DIV_DOUBLE,

    RVM_CODE_MOD_INT,
    RVM_CODE_MOD_INT64,
    RVM_CODE_MOD_DOUBLE,

    RVM_CODE_MINUS_INT,
    RVM_CODE_MINUS_INT64,
    RVM_CODE_MINUS_DOUBLE,

    RVM_CODE_SELF_INCREASE_INT,
    RVM_CODE_SELF_INCREASE_INT64,
    RVM_CODE_SELF_INCREASE_DOUBLE,
    RVM_CODE_SELF_DECREASE_INT,
    RVM_CODE_SELF_DECREASE_INT64,
    RVM_CODE_SELF_DECREASE_DOUBLE,

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
    RVM_CODE_RELATIONAL_EQ_INT64,
    RVM_CODE_RELATIONAL_EQ_DOUBLE,
    RVM_CODE_RELATIONAL_EQ_STRING,

    RVM_CODE_RELATIONAL_NE_INT,
    RVM_CODE_RELATIONAL_NE_INT64,
    RVM_CODE_RELATIONAL_NE_DOUBLE,
    RVM_CODE_RELATIONAL_NE_STRING,

    RVM_CODE_RELATIONAL_GT_INT,
    RVM_CODE_RELATIONAL_GT_INT64,
    RVM_CODE_RELATIONAL_GT_DOUBLE,
    RVM_CODE_RELATIONAL_GT_STRING,

    RVM_CODE_RELATIONAL_GE_INT,
    RVM_CODE_RELATIONAL_GE_INT64,
    RVM_CODE_RELATIONAL_GE_DOUBLE,
    RVM_CODE_RELATIONAL_GE_STRING,

    RVM_CODE_RELATIONAL_LT_INT,
    RVM_CODE_RELATIONAL_LT_INT64,
    RVM_CODE_RELATIONAL_LT_DOUBLE,
    RVM_CODE_RELATIONAL_LT_STRING,

    RVM_CODE_RELATIONAL_LE_INT,
    RVM_CODE_RELATIONAL_LE_INT64,
    RVM_CODE_RELATIONAL_LE_DOUBLE,
    RVM_CODE_RELATIONAL_LE_STRING,

    // jump
    RVM_CODE_JUMP,
    RVM_CODE_JUMP_IF_FALSE,
    RVM_CODE_JUMP_IF_TRUE,

    // duplicate
    RVM_CODE_SHALLOW_COPY,
    RVM_CODE_DEEP_COPY,

    // func
    RVM_CODE_ARGUMENT_NUM,
    RVM_CODE_PUSH_FUNC,
    RVM_CODE_PUSH_METHOD,
    RVM_CODE_INVOKE_FUNC_NATIVE,
    RVM_CODE_INVOKE_FUNC,
    RVM_CODE_INVOKE_METHOD,
    RVM_CODE_RETURN,
    RVM_CODE_FUNCTION_FINISH,

    RVM_CODE_EXIT,

    // array
    RVM_CODE_NEW_ARRAY_BOOL,
    RVM_CODE_NEW_ARRAY_INT,
    RVM_CODE_NEW_ARRAY_INT64,
    RVM_CODE_NEW_ARRAY_DOUBLE,
    RVM_CODE_NEW_ARRAY_STRING,
    RVM_CODE_NEW_ARRAY_CLASS_OB,

    RVM_CODE_NEW_ARRAY_LITERAL_BOOL,
    RVM_CODE_NEW_ARRAY_LITERAL_INT,
    RVM_CODE_NEW_ARRAY_LITERAL_INT64,
    RVM_CODE_NEW_ARRAY_LITERAL_DOUBLE,
    RVM_CODE_NEW_ARRAY_LITERAL_STRING,
    RVM_CODE_NEW_ARRAY_LITERAL_CLASS_OB,

    RVM_CODE_NEW_ARRAY_LITERAL_A,


    RVM_CODE_PUSH_ARRAY_LEN,
    RVM_CODE_PUSH_ARRAY_CAPACITY,
    RVM_CODE_PUSH_STRING_LEN,
    RVM_CODE_PUSH_STRING_CAPACITY,

    // class
    RVM_CODE_NEW_CLASS_OB_LITERAL,

    // range
    RVM_CODE_FOR_RANGE_ARRAY_A,
    RVM_CODE_FOR_RANGE_ARRAY_BOOL,
    RVM_CODE_FOR_RANGE_ARRAY_INT,
    RVM_CODE_FOR_RANGE_ARRAY_INT64,
    RVM_CODE_FOR_RANGE_ARRAY_DOUBLE,
    RVM_CODE_FOR_RANGE_ARRAY_STRING,
    RVM_CODE_FOR_RANGE_ARRAY_CLASS_OB,
    RVM_CODE_FOR_RANGE_STRING,
    RVM_CODE_FOR_RANGE_FINISH,

    // convert
    RVM_CODE_BOOL_2_STRING,
    RVM_CODE_INT_2_STRING,
    RVM_CODE_INT64_2_STRING,
    RVM_CODE_DOUBLE_2_STRING,
    RVM_CODE_INT_2_INT64,

    // 不对应实际的字节码, 不能在生成代码的时候使用
    RVM_CODES_NUM, // 用来标记RVM CODE 的数量
} RVM_Opcode;


typedef enum {
    IDENTIFIER_TYPE_UNKNOW = 0,
    IDENTIFIER_TYPE_VARIABLE,
    IDENTIFIER_TYPE_VARIABLE_ARRAY,
    IDENTIFIER_TYPE_FUNCTION,
} IdentifierType;

struct RVM_CallInfo {
    unsigned int     magic_number;

    RVM_ClassObject* caller_object;
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
    EXPRESSION_TYPE_LITERAL_INT64,
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
    EXPRESSION_TYPE_LOGICAL_AND,
    EXPRESSION_TYPE_LOGICAL_OR,
    EXPRESSION_TYPE_RELATIONAL_EQ,
    EXPRESSION_TYPE_RELATIONAL_NE,
    EXPRESSION_TYPE_RELATIONAL_GT,
    EXPRESSION_TYPE_RELATIONAL_GE,
    EXPRESSION_TYPE_RELATIONAL_LT,
    EXPRESSION_TYPE_RELATIONAL_LE,

    EXPRESSION_TYPE_ARITHMETIC_UNITARY_MINUS, // 一元操作符 负号
    EXPRESSION_TYPE_LOGICAL_UNITARY_NOT,      // 一元操作符 逻辑 非 not
    EXPRESSION_TYPE_UNITARY_INCREASE,         // 一元操作符 i++
    EXPRESSION_TYPE_UNITARY_DECREASE,         // 一元操作符 i--

    EXPRESSION_TYPE_NEW_ARRAY,
    EXPRESSION_TYPE_ARRAY_LITERAL,
    EXPRESSION_TYPE_CLASS_OBJECT_LITERAL,

    EXPRESSION_TYPE_ARRAY_INDEX,
    EXPRESSION_TYPE_MEMBER,
    EXPRESSION_TYPE_ELEMENT_ACCESS,

    EXPRESSION_TYPE_CAST,


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


typedef void (*BuildinFuncFix)(Expression*             expression,
                               FunctionCallExpression* function_call_expression,
                               Block*                  block,
                               Function*               func);


typedef enum {
    RING_BUILD_IN_FNC_UNKNOW = 0,
    RING_BUILD_IN_FNC_LEN,
    RING_BUILD_IN_FNC_CAPACITY,
    RING_BUILD_IN_FNC_PUSH,
    RING_BUILD_IN_FNC_POP,
    RING_BUILD_IN_FNC_TO_STRING,
    RING_BUILD_IN_FNC_TO_INT64,
} RING_BUILD_IN_FUNC_ID;

typedef struct {
    const char*                 identifier;

    int                         param_size;
    std::vector<TypeSpecifier*> param_types;

    int                         return_size;
    std::vector<TypeSpecifier*> return_types;

    BuildinFuncFix              buildin_func_fix;

} Ring_Buildin_Func;


struct ClassDefinition {
    std::string      source_file;
    unsigned int     start_line_number; // 源码的开始行
    unsigned int     end_line_number;   // 源码的结束行

    unsigned int     class_index;
    char*            identifier;


    unsigned int     field_size;
    FieldMember*     field_list;

    unsigned int     method_size;
    MethodMember*    method_list;

    ClassDefinition* next;
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

// ClassMemberDeclaration 只用来 在 create_ast的时候, 收集 field method的列表
// create_ast 之后边不再使用
struct ClassMemberDeclaration {
    unsigned int    line_number;

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

    unsigned int   index_of_class; // UPDATED_BY_FIX_AST
    TypeSpecifier* type_specifier;
    char*          identifier;

    FieldMember*   next;
};


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
    unsigned int line_number;


    /*
     * 一个表达式肯定是有返回值的(除了assign 表达式)(所以 assign是不是应该是个语句, 而不是表达式)
     * 需要通过返回值与后续的操作进行比对, 数据的类型要保持一致, string不能赋值给int变量
     * 对于 function-call/method-call 这种的, 返回值可能有多个, 所以convert_type_size > 1
     *
     * convert_type 统一在 fix_ast中进行更新.
     * fix_ast 中不对 TypeSpecifier进行内存分配, 支持保存指针
     *
     * 但是这里可能很大部分 convert_type_size 都为1, 如果选择
     */
    unsigned int    convert_type_size;
    TypeSpecifier** convert_type;

    ExpressionType  type;
    union {
        bool                          bool_literal;
        int                           int_literal;   // 注意这里是 unsigned
        long long                     int64_literal; // 注意这里是 unsigned
        double                        double_literal;
        const char*                   string_literal;
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
        FieldInitExpression*          field_init_expression;
    } u;

    Expression* next;
};


// 清除 expression 所代表的 convert_type_size 和 convert_type
#define EXPRESSION_CLEAR_CONVERT_TYPE(expression) \
    (expression)->convert_type_size = 0;          \
    (expression)->convert_type      = nullptr;

// 添加 expression 所代表的 convert_type_size 和 convert_type
// 其实 只有 function-call/method-call 表达式: convert_type_size > 1
// 其余的都是 convert_type_size = 1
#define EXPRESSION_ADD_CONVERT_TYPE(expression, type_specifier)                             \
    (expression)->convert_type_size = (expression)->convert_type_size + 1;                  \
    (expression)->convert_type =                                                            \
        (TypeSpecifier**)realloc((expression)->convert_type,                                \
                                 (expression)->convert_type_size * sizeof(TypeSpecifier*)); \
    (expression)->convert_type[(expression)->convert_type_size - 1] = (type_specifier);


typedef enum {
    IDENTIFIER_EXPRESSION_TYPE_UNKNOW,
    IDENTIFIER_EXPRESSION_TYPE_VARIABLE,
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


typedef enum {
    UNKNOW_COPY,
    SHALLOW_COPY,
    DEEP_COPY,
} RVM_Value_Copy_Type;


struct ArrayIndexExpression {
    unsigned int         line_number;

    Expression*          array_expression;
    DimensionExpression* index_expression;
};

struct MemberExpression {
    unsigned int line_number;

    Expression*  object_expression;
    char*        member_identifier;
    FieldMember* field_member; // UPDATED_BY_FIX_AST
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


struct FunctionCallExpression {
    unsigned int  line_number;

    char*         package_posit;
    char*         func_identifier;
    Function*     function;

    unsigned int  argument_list_size;
    ArgumentList* argument_list;
};

struct MethodCallExpression {
    unsigned int  line_number;

    Expression*   object_expression;
    char*         member_identifier;
    MethodMember* method_member;
    ArgumentList* argument_list;
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
    FieldMember*         field_member; // UPDATED_BY_FIX_AST
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


#define FUNCTION_TUPLE_HEADER                                                    \
    std::string         source_file;       /*ring source file*/                  \
    unsigned int        start_line_number; /*start line no in ring source file*/ \
    unsigned int        end_line_number;   /*end   line no in ring source file*/ \
    Package*            package;           /*function's package*/                \
    RingFileStat*       ring_file_stat;    /*ring source file stat*/             \
    char*               identifier;                                              \
    unsigned int        parameter_list_size;                                     \
    Parameter*          parameter_list;                                          \
    unsigned int        return_list_size;                                        \
    FunctionReturnList* return_list;                                             \
    Block*              block;                                                   \
    FunctionTuple*      next;


struct FunctionTuple {
    FUNCTION_TUPLE_HEADER;
};

struct Function {
    FUNCTION_TUPLE_HEADER;

    unsigned int func_index;
    FunctionType type;
};

struct MethodMember {
    FUNCTION_TUPLE_HEADER;

    unsigned int index_of_class; // UPDATED_BY_FIX_AST
};

struct FunctionReturnList {
    unsigned int        line_number;

    TypeSpecifier*      type_specifier;
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

    unsigned int break_loop_num;
    // 语法:  break; break 1; break 2;
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
    char*               identifier;
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


#define RING_CMD_T_RUN "run"
#define RING_CMD_T_DUMP "dump"
#define RING_CMD_T_RDB "rdb"
#define RING_CMD_T_MAN "man"
#define RING_CMD_T_VERSION "version"
#define RING_CMD_T_HELP "help"

enum RING_COMMAND_TYPE {
    RING_COMMAND_UNKNOW,

    RING_COMMAND_RUN,
    RING_COMMAND_DUMP,
    RING_COMMAND_RDB,

    RING_COMMAND_MAN,
    RING_COMMAND_VERSION,
    RING_COMMAND_HELP,
};

struct Ring_Command_Arg {
    RING_COMMAND_TYPE        cmd;

    std::string              input_file_name; // run/dump/rdb
    std::string              keyword;         // man
    unsigned int             optimize_level;
    std::vector<std::string> shell_args;
};

// rdb cmd token
#define VM_DB_CMD_T_HELP "help"
#define VM_DB_CMD_T_CLEAR "clear"
#define VM_DB_CMD_T_QUIT "quit"

#define VM_DB_CMD_T_STACK "stack"

enum VM_DB_COMMAND_TYPE {
    VM_DB_COMMAND_UNKNOW,

    VM_DB_COMMAND_HELP,
    VM_DB_COMMAND_CLEAR,
    VM_DB_COMMAND_QUIT,

    VM_DB_COMMAND_STACK,
};
struct VM_DB_Arg {
    VM_DB_COMMAND_TYPE cmd;

    std::string        argument;
};


// rdb cmd token
#define RDB_CMD_T_HELP "help"
#define RDB_CMD_T_CLEAR "clear"
#define RDB_CMD_T_QUIT "quit"

#define RDB_CMD_T_GLOBAL "global"
#define RDB_CMD_T_LOCAL "local"
#define RDB_CMD_T_RUN "run"
#define RDB_CMD_T_CONT "cont"
#define RDB_CMD_T_BT "bt"

#define RDB_CMD_T_BREAK "break"
#define RDB_CMD_T_BREAK_SET "set"
#define RDB_CMD_T_BREAK_UNSET "unset"
#define RDB_CMD_T_BREAK_LIST "list"
#define RDB_CMD_T_BREAK_CLEAR "clear"

#define RDB_CMD_T_STEP "step"
#define RDB_CMD_T_STEP_OVER "over"
#define RDB_CMD_T_STEP_INTO "into"
#define RDB_CMD_T_STEP_OUT "out"


#define RDB_CMD_T_CODE "code"
#define RDB_CMD_T_CODE_LIST "list"


enum RDB_COMMAND_TYPE {
    RDB_COMMAND_UNKNOW,

    RDB_COMMAND_HELP,
    RDB_COMMAND_CLEAR,
    RDB_COMMAND_QUIT,

    RDB_COMMAND_GLOBAL,
    RDB_COMMAND_LOCAL,
    RDB_COMMAND_CONT,
    RDB_COMMAND_BT,

    RDB_COMMAND_BREAK,

    RDB_COMMAND_STEP,

    RDB_COMMAND_CODE,

};

enum RDB_COMMAND_BREAK_TYPE {
    RDB_COMMAND_BREAK_UNKNOW,
    RDB_COMMAND_BREAK_SET,
    RDB_COMMAND_BREAK_UNSET,
    RDB_COMMAND_BREAK_LIST,
    RDB_COMMAND_BREAK_CLEAR,
};

enum RDB_COMMAND_STEP_TYPE {
    RDB_COMMAND_STEP_UNKNOW,
    RDB_COMMAND_STEP_OVER,
    RDB_COMMAND_STEP_INTO,
    RDB_COMMAND_STEP_OUT,
};

enum RDB_COMMAND_CODE_TYPE {
    RDB_COMMAND_CODE_UNKNOW,
    RDB_COMMAND_CODE_LIST,
};

struct RDB_Command {
    std::string              token;
    std::vector<std::string> rule;
    std::string              description;

    std::vector<RDB_Command> sub_command;
};


struct RDB_Arg {
    RDB_COMMAND_TYPE       cmd;
    RDB_COMMAND_BREAK_TYPE break_cmd;
    RDB_COMMAND_STEP_TYPE  step_cmd;
    RDB_COMMAND_CODE_TYPE  code_cmd;

    std::string            argument;
};


#define TRACE_EVENT_SAE "stop-at-entry"
#define TRACE_EVENT_OPCODE "opcode"
#define TRACE_EVENT_LINE "line"
#define TRACE_EVENT_CALL "call"
#define TRACE_EVENT_RETURN "return"
#define TRACE_EVENT_EXIT "exit"


#define ENABLE_TRACE_EVENT_SAE (1 << 0)
#define ENABLE_TRACE_EVENT_OPCODE (1 << 1)
#define ENABLE_TRACE_EVENT_LINE (1 << 2)
#define ENABLE_TRACE_EVENT_CALL (1 << 3)
#define ENABLE_TRACE_EVENT_RETURN (1 << 4)
#define ENABLE_TRACE_EVENT_EXIT (1 << 5)
#define ENABLE_TRACE_EVENT_ALL (ENABLE_TRACE_EVENT_SAE      \
                                | ENABLE_TRACE_EVENT_OPCODE \
                                | ENABLE_TRACE_EVENT_LINE   \
                                | ENABLE_TRACE_EVENT_CALL   \
                                | ENABLE_TRACE_EVENT_RETURN \
                                | ENABLE_TRACE_EVENT_EXIT)

#define DISABLE_TRACE_EVENT_SAE (~ENABLE_TRACE_EVENT_SAE)
#define DISABLE_TRACE_EVENT_OPCODE (~ENABLE_TRACE_EVENT_OPCODE)
#define DISABLE_TRACE_EVENT_LINE (~ENABLE_TRACE_EVENT_LINE)
#define DISABLE_TRACE_EVENT_CALL (~ENABLE_TRACE_EVENT_CALL)
#define DISABLE_TRACE_EVENT_RETURN (~ENABLE_TRACE_EVENT_RETURN)
#define DISABLE_TRACE_EVENT_EXIT (~ENABLE_TRACE_EVENT_EXIT)
#define DISABLE_TRACE_EVENT_ALL (~ENABLE_TRACE_EVENT_ALL)

#define SET_TRACE_EVENT_SAE(debug_config) ((debug_config)->enable_trace_event |= ENABLE_TRACE_EVENT_SAE)
#define SET_TRACE_EVENT_OPCODE(debug_config) ((debug_config)->enable_trace_event |= ENABLE_TRACE_EVENT_OPCODE)
#define SET_TRACE_EVENT_LINE(debug_config) ((debug_config)->enable_trace_event |= ENABLE_TRACE_EVENT_LINE)
#define SET_TRACE_EVENT_CALL(debug_config) ((debug_config)->enable_trace_event |= ENABLE_TRACE_EVENT_CALL)
#define SET_TRACE_EVENT_RETURN(debug_config) ((debug_config)->enable_trace_event |= ENABLE_TRACE_EVENT_RETURN)
#define SET_TRACE_EVENT_EXIT(debug_config) ((debug_config)->enable_trace_event |= ENABLE_TRACE_EVENT_EXIT)
#define SET_TRACE_EVENT_ALL(debug_config) ((debug_config)->enable_trace_event |= ENABLE_TRACE_EVENT_ALL)

#define UNSET_TRACE_EVENT_SAE(debug_config) ((debug_config)->enable_trace_event &= DISABLE_TRACE_EVENT_SAE)
#define UNSET_TRACE_EVENT_OPCODE(debug_config) ((debug_config)->enable_trace_event &= DISABLE_TRACE_EVENT_OPCODE)
#define UNSET_TRACE_EVENT_LINE(debug_config) ((debug_config)->enable_trace_event &= DISABLE_TRACE_EVENT_LINE)
#define UNSET_TRACE_EVENT_CALL(debug_config) ((debug_config)->enable_trace_event &= DISABLE_TRACE_EVENT_CALL)
#define UNSET_TRACE_EVENT_RETURN(debug_config) ((debug_config)->enable_trace_event &= DISABLE_TRACE_EVENT_RETURN)
#define UNSET_TRACE_EVENT_EXIT(debug_config) ((debug_config)->enable_trace_event &= DISABLE_TRACE_EVENT_EXIT)
#define UNSET_TRACE_EVENT_ALL(debug_config) ((debug_config)->enable_trace_event &= DISABLE_TRACE_EVENT_ALL)


#define ISSET_TRACE_EVENT_SAE(debug_config) ((debug_config)->enable_trace_event & ENABLE_TRACE_EVENT_SAE)
#define ISSET_TRACE_EVENT_OPCODE(debug_config) ((debug_config)->enable_trace_event & ENABLE_TRACE_EVENT_OPCODE)
#define ISSET_TRACE_EVENT_LINE(debug_config) ((debug_config)->enable_trace_event & ENABLE_TRACE_EVENT_LINE)
#define ISSET_TRACE_EVENT_CALL(debug_config) ((debug_config)->enable_trace_event & ENABLE_TRACE_EVENT_CALL)
#define ISSET_TRACE_EVENT_RETURN(debug_config) ((debug_config)->enable_trace_event & ENABLE_TRACE_EVENT_RETURN)
#define ISSET_TRACE_EVENT_EXIT(debug_config) ((debug_config)->enable_trace_event & ENABLE_TRACE_EVENT_EXIT)
#define ISSET_TRACE_EVENT_ALL(debug_config) ((debug_config)->enable_trace_event == ENABLE_TRACE_EVENT_ALL)

struct RVM_DebugConfig {
    bool                  enable;
    TraceDispacth         trace_dispatch;
    unsigned char         enable_trace_event;


    bool                  stop_at_entry;
    bool                  display_globals;
    bool                  display_locals;
    bool                  display_call_stack;

    RDB_COMMAND_STEP_TYPE step_cmd;
    unsigned int          call_func_deep_count;
    unsigned int          step_over_deep_count; // 记录刚才 step-over 操作的位置
    unsigned int          step_out_deep_count;  // 记录刚才 step—out 操作的位置


    // break_points 先简单实现, 只能在 main package 中设置断点
    std::vector<RVM_BreakPoint> break_points;
    // RVM_DebugMode debug_mode;
};

struct RVM_BreakPoint {
    char*        package;
    char*        file_name;
    char*        func_name;
    unsigned int line_number;
};

struct RVM_Frame {
    Ring_VirtualMachine*                            rvm;
    RVM_CallInfo*                                   call_info;

    unsigned int                                    next_pc;
    RVM_Opcode                                      next_opcode;
    unsigned int                                    source_line_number;

    std::vector<std::pair<std::string, RVM_Value*>> globals;
    std::vector<std::pair<std::string, RVM_Value*>> locals;
};

typedef enum {
    ERROR_CODE_SUCCESS,

    // 命令行参数错误
    ERROR_CODE_COMMAND_ERROR,

    // 编译错误
    ERROR_CODE_COMPILE_ERROR,

    // 语义分析错误
    ERROR_CODE_SEMANTIC_CHECH_ERROR,


    ERROR_CODE_GRAMMAR_ERROR                  = 100000, // 语法错误


    ERROR_UNDEFINITE_VARIABLE                 = 200000,
    ERROR_REDEFINITE_GLOBAL_VARIABLE          = 200001, // 重复定义全局变量
    ERROR_REDEFINITE_FUNCTION                 = 200002, // 重复定义函数
    ERROR_OPER_INVALID_USE                    = 200003, // - 符号 不合法使用
    ERROR_DUPLICATE_IMPORT_PACKAGE            = 200004, // 重复 import package
    ERROR_INVALID_VARIABLE_IDENTIFIER         = 200005, // 不合法的变量标识符
    ERROR_TOO_MANY_LOCAL_VARIABLES            = 200006, // 局部变量数量超过限制
    ERROR_TOO_MANY_FIELDS_IN_CLASS            = 200007, // class 中 field 的数量超过限制
    ERROR_TOO_MANY_METHODS_IN_CLASS           = 200008, // class 中 method 的数量超过限制
    ERROR_MISS_CLASS_DEFINITION               = 200009, // 缺少 class 定义
    ERROR_INVALID_FIELD_IN_CLASS              = 200010, // field 不合法
    ERROR_ARRAY_DIMENSION_INVALID             = 200011, // 数组维度不合法
    ERROR_ASSIGN_TO_METHOD_OF_CLASS           = 200012, // 不能给 class中 method赋值
    ERROR_INVALID_NOT_FOUND_CLASS_FIELD       = 200013, // 找不到 class field
    ERROR_INVALID_NOT_FOUND_CLASS_METHOD      = 200014, // 找不到 class field
    ERROR_UNCLOSED_STRING_LITERAL             = 200015, // 未关闭的字符串常量

    ERROR_FUNCTION_CALL_IN_MULTIPLE_OPERANDS  = 200016, // 函数调用用到 多项赋值中

    ERROR_ASSIGNMENT_MISMATCH_NUM             = 200017, // 赋值时, 左值和右值的数量不匹配
    ERROR_ASSIGNMENT_MISMATCH_TYPE            = 200018, // 赋值时, 左值和右值的类型不匹配
    ERROR_CONCAT_OPERATOR_MISMATCH_TYPE       = 200019, // string .. 操作数类型不不匹配
    ERROR_MATH_OPERATOR_MISMATCH_TYPE         = 200020, // 数学运算操作数不是 int/int64/double 类型

    ERROR_OVERFLOWS                           = 200051, // 溢出

    ERROR_UNDEFINITE_FUNCTION                 = 300000,
    ERROR_ARGUMENT_MISMATCH_NUM               = 300001, // 函数调用参数数量类型不匹配
    ERROR_ARGUMENT_MISMATCH_TYPE              = 300002, // 函数调用参数数量类型不匹配
    ERROR_FUNCTION_INVALID_VARIADIC_PARAMETER = 300003, // 函数定义中不合法的 可变参数

    ERROR_FUNCTION_MISMATCH_RETURN_NUM        = 300004, // 函数定义的返回值和return中的返回值类型不匹配
    ERROR_FUNCTION_MISMATCH_RETURN_TYPE       = 300005, // 函数定义的返回值和return中的返回值类型不匹配

    ERROR_FUNCTION_MAIN_INVALID               = 300006, // main函数定义不合法

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


    char*           ring_compiler_file;
    unsigned int    ring_compiler_file_line;
    /*
     * ring_compiler_file
     * ring_compiler_file_line
     *     Ring 编译器开发者专用
     *     ring 编译器的源文件, 可以快速定位 error-report 所在的位置
     */
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
#define MEM_MAX_BUCKET_NUM 4096
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

/*
 * DEFINE_ERROR_REPORT_STR ring 语法报错str
 *
 * 这里使用的局部变量，每次都分配
 * TODO: 这里应该优化一下使用全局变量，不需要每次都分配
 * 1. 目前没有做报错恢复，所以遇到一次错误就退出，不会分配很多次
 * 2. 如果要改成 全局变量，那么在并发编译的时候要考虑这个问题
 */
#define DEFINE_ERROR_REPORT_STR                          \
    char compile_err_buf[2048];                          \
    char compile_adv_buf[2048];                          \
    memset(compile_err_buf, 0, sizeof(compile_err_buf)); \
    memset(compile_adv_buf, 0, sizeof(compile_adv_buf));


#define str_eq(str1, str2) (strcmp((str1), (str2)) == 0)
#define str_eq_n(str1, str2, len) (strncmp((str1), (str2), (len)) == 0)

// clear terminal printf
#define STDOUT_CLEAR_SCREEN fprintf(stdout, "\e[1;1H\e[2J")
#define STDERR_CLEAR_SCREEN fprintf(stderr, "\e[1;1H\e[2J")

// move cursor to terminal (row, col) location
#define STDOUT_MOVE_CURSOR(row, col) fprintf(stdout, "%c[%d;%dH", 27, (row), (col))
#define STDERR_MOVE_CURSOR(row, col) fprintf(stderr, "%c[%d;%dH", 27, (row), (col))

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

#define ring_exec_err_report(format, ...)                                       \
    fprintf(stderr, "%s[Ring Core Panic][%s:%d]\n" format "%s\n",               \
            LOG_COLOR_RED, __FILE__, __LINE__, ##__VA_ARGS__, LOG_COLOR_CLEAR); \
    exit(1);

// TODO: 在虚拟机执行字节码的过程中，判断内部指针的合法性
// 如果不合法的话，在开启Debug的时候，应该抛出堆栈信息，便于定位
// #define vm_assert()


#define DEBUG_RVM_INTERACTIVE_STDOUT_FILE "/tmp/ring-debug-vm.stdout.log"

int   ring_repl();
void  ring_repl_completion(const char* buf, linenoiseCompletions* lc);
char* ring_repl_hints(const char* buf, int* color, int* bold);
int   register_debugger(Ring_VirtualMachine* rvm, Ring_Command_Arg args);


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

const char*    get_string_constant_literal(const char* str1, const char* str2);

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
Expression*                   create_expression_identifier_with_index(Expression* array_expression, DimensionExpression* index);
Expression*                   create_member_expression(Expression* object_expression, char* member_identifier);
Expression*                   create_expression_from_function_call(FunctionCallExpression* function_call_expression);
Expression*                   create_expression_from_method_call(MethodCallExpression* method_call_expression);
Expression*                   create_expression_from_array_literal(ArrayLiteralExpression* array_literal);
Expression*                   create_expression_from_class_object_literal(ClassObjectLiteralExpression* object_literal);
Expression*                   create_expression_assign(AssignExpression* assign_expression);
Expression*                   create_expression_ternary(Expression* condition, Expression* true_expression, Expression* false_expression);
Expression*                   create_expression_binary(ExpressionType type, Expression* left, Expression* right);
Expression*                   create_expression_unitary(ExpressionType type, Expression* unitary_expression);
Expression*                   create_expression_literal(ExpressionType type, char* literal_interface);
Expression*                   create_expression_bool_literal(ExpressionType type, bool value);
Expression*                   create_cast_expression(TypeSpecifier* cast_type, Expression* operand);
Expression*                   create_new_array_expression(TypeSpecifier*       sub_type,
                                                          DimensionExpression* dimension_expression);

FieldInitExpression*          create_field_init_expression(char* field_identifier, Expression* init_expression);
FieldInitExpression*          field_init_list_add_item(FieldInitExpression* list, FieldInitExpression* item);
AssignExpression*             create_assign_expression(AssignExpressionType type, Expression* left, Expression* operand);
AssignExpression*             create_multi_assign_expression(Expression* first_left_value_exp,
                                                             Expression* left_value_exp_list,
                                                             Expression* operand);
FunctionCallExpression*       create_function_call_expression(char* identifier, ArgumentList* argument_list);
MethodCallExpression*         create_method_call_expression(Expression* object_expression, char* member_identifier, ArgumentList* argument_list);
ArrayLiteralExpression*       create_array_literal_expression(TypeSpecifier* sub_type, DimensionExpression* dimension_expression, Expression* expression_list);
ClassObjectLiteralExpression* create_class_object_literal_expression(TypeSpecifier* type_specifier, FieldInitExpression* field_init_expression_list);
Expression*                   expression_list_add_item(Expression* expression_list, Expression* expression);
ArgumentList*                 argument_list_add_item(ArgumentList* argument_list, ArgumentList* argument);
ArgumentList*                 create_argument_list_from_expression(Expression* expression);
Identifier*                   create_identifier(IdentifierType type, char* name);
Identifier*                   identifier_list_add_item(Identifier* identifier_list, Identifier* identifier);
FunctionReturnList*           create_function_return_list(TypeSpecifier* type_specifier);
FunctionReturnList*           function_return_list_add_item(FunctionReturnList* return_list,
                                                            TypeSpecifier*      type_specifier);
Function*                     create_function_definition(FunctionType type, Identifier* identifier, Parameter* parameter_list, FunctionReturnList* return_list, Block* block);

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
TypeSpecifier*                create_type_specifier_array(TypeSpecifier* sub_type, DimensionExpression* dimension);
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
void check_function_call(FunctionCallExpression* function_call_expression, Function* function);

void ring_compiler_check_exit(Package* package);
// --------------------


/* --------------------
 * fix.cpp
 * function definition
 *
 */
void             ring_compiler_fix_ast(Package* package);
Function*        create_global_init_func(Package* package);
void             fix_function_definition(Function* func);
void             fix_statement_list(Statement* statement_list, Block* block, FunctionTuple* func);
void             fix_statement(Statement* statement, Block* block, FunctionTuple* func);
void             fix_expression(Expression* expression, Block* block, FunctionTuple* func);
void             add_local_declaration(Declaration* declaration, Block* block, FunctionTuple* func);
void             fix_type_specfier(TypeSpecifier* type_specifier);
void             fix_block(Block* block, FunctionTuple* func);
void             fix_if_statement(IfStatement* if_statement, Block* block, FunctionTuple* func);
void             fix_for_statement(ForStatement* for_statement, Block* block, FunctionTuple* func);
void             fix_dofor_statement(DoForStatement* dofor_statement, Block* block, FunctionTuple* func);
void             fix_return_statement(ReturnStatement* return_statement, Block* block, FunctionTuple* func);
void             fix_identifier_expression(Expression*           expression,
                                           IdentifierExpression* identifier_expression,
                                           Block*                block);
void             fix_assign_expression(AssignExpression* expression, Block* block, FunctionTuple* func);
void             fix_binary_concat_expression(Expression*       expression,
                                              BinaryExpression* binary_expression,
                                              Block* block, FunctionTuple* func);
void             fix_binary_math_expression(Expression*       expression,
                                            ExpressionType    expression_type,
                                            BinaryExpression* binary_expression,
                                            Block* block, FunctionTuple* func);
void             fix_binary_logical_expression(Expression*       expression,
                                               ExpressionType    expression_type,
                                               BinaryExpression* binary_expression,
                                               Block* block, FunctionTuple* func);
void             fix_binary_relational_expression(Expression*       expression,
                                                  ExpressionType    expression_type,
                                                  BinaryExpression* binary_expression,
                                                  Block* block, FunctionTuple* func);

void             fix_unitary_expression(Expression* expression,
                                        Expression* unitary_expression,
                                        Block* block, FunctionTuple* func);
void             fix_unitary_minus_expression(Expression* expression,
                                              Expression* unitary_expression,
                                              Block* block, FunctionTuple* func);
void             fix_unitary_not_expression(Expression* expression,
                                            Expression* unitary_expression,
                                            Block* block, FunctionTuple* func);
void             fix_unitary_increase_decrease_expression(Expression* expression,
                                                          Expression* unitary_expression,
                                                          Block* block, FunctionTuple* func);

void             fix_function_call_expression(Expression*             expression,
                                              FunctionCallExpression* function_call_expression,
                                              Block*                  block,
                                              FunctionTuple*          func);
void             fix_method_call_expression(Expression*           expression,
                                            MethodCallExpression* method_call_expression,
                                            Block*                block,
                                            FunctionTuple*        func);
void             fix_class_definition(ClassDefinition* class_definition);
void             fix_class_field(ClassDefinition* class_definition, FieldMember* field);
void             fix_class_method(ClassDefinition* class_definition, MethodMember* method);


void             fix_array_index_expression(Expression*           expression,
                                            ArrayIndexExpression* array_index_expression,
                                            Block*                block,
                                            FunctionTuple*        func);
void             fix_new_array_expression(Expression* expression, NewArrayExpression* new_array_expression, Block* block, FunctionTuple* func);
void             fix_dimension_expression(DimensionExpression* dimension_expression, Block* block, FunctionTuple* func);
void             fix_array_literal_expression(Expression* expression, ArrayLiteralExpression* array_literal_expression, Block* block, FunctionTuple* func);

void             fix_class_object_literal_expression(Expression* expression, ClassObjectLiteralExpression* literal_expression, Block* block, FunctionTuple* func);
void             fix_field_member_expression(Expression* expression, MemberExpression* member_expression, Block* block, FunctionTuple* func);
void             fix_class_member_expression(MemberExpression* member_expression, Expression* object_expression, char* member_identifier);
ClassDefinition* search_class_definition(char* class_identifier);
FieldMember*     search_class_field(ClassDefinition* class_definition, char* identifier);
MethodMember*    search_class_method(ClassDefinition* class_definition, char* identifier);

void             fix_ternary_condition_expression(Expression*        expression,
                                                  TernaryExpression* ternary_expression,
                                                  Block*             block,
                                                  FunctionTuple*     func);
void             add_parameter_to_declaration(Parameter* parameter, Block* block);
Declaration*     search_declaration(char* package_posit, char* identifier, Block* block);
Function*        search_function(char* package_posit, char* identifier);

// --------------------

/* --------------------
 * crop_ast.cpp
 * function definition
 *
 */

void crop_if_statement(IfStatement* if_statement, Block* block, FunctionTuple* func);
void crop_for_statement(ForStatement* for_statement, Block* block, FunctionTuple* func);

void crop_ternary_condition_expression(Expression*        expression,
                                       TernaryExpression* ternary_expression,
                                       Block*             block,
                                       FunctionTuple*     func);
void crop_binary_logical_expression(Expression*       expression,
                                    ExpressionType    expression_type,
                                    BinaryExpression* binary_expression,
                                    Block* block, FunctionTuple* func);
void crop_binary_relational_expression(Expression*       expression,
                                       ExpressionType    expression_type,
                                       BinaryExpression* binary_expression,
                                       Block* block, FunctionTuple* func);
void crop_binary_concat_expression(Expression*       expression,
                                   BinaryExpression* binary_expression,
                                   Block* block, FunctionTuple* func);
void crop_binary_match_expression(Expression*       expression,
                                  BinaryExpression* binary_expression,
                                  Block* block, FunctionTuple* func);
void crop_unitary_expression(Expression* expression,
                             Expression* unitary_expression,
                             Block* block, FunctionTuple* func);
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
void              generate_vmcode_from_relational_expression(Package_Executer* executer,
                                                             ExpressionType    expression_type,
                                                             BinaryExpression* expression,
                                                             RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_unitary_minus_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode);
void              generate_vmcode_from_unitary_not_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode);
void              generate_vmcode_from_increase_decrease_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_identifier_expression(Package_Executer* executer, IdentifierExpression* identifier_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_bool_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_int_expression(Package_Executer* executer,
                                                      Expression*       expression,
                                                      RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_int64_expression(Package_Executer* executer,
                                                        Expression*       expression,
                                                        RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_double_expression(Package_Executer* executer,
                                                         Expression*       expression,
                                                         RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_string_expression(Package_Executer* executer,
                                                         Expression*       expression,
                                                         RVM_OpcodeBuffer* opcode_buffer);
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

void              generate_vmcode(Package_Executer* executer, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode, unsigned int operand, unsigned int line_number);

int               constant_pool_grow(Package_Executer* executer, unsigned int growth_size);
int               constant_pool_add_int(Package_Executer* executer, int int_literal);
int               constant_pool_add_int64(Package_Executer* executer, long long int64_literal);
int               constant_pool_add_double(Package_Executer* executer, double double_literal);
int               constant_pool_add_string(Package_Executer* executer, const char* string_literal);

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
void                 ring_virtualmachine_init(Ring_VirtualMachine* rvm);

void                 rvm_add_static_variable(Package_Executer* executer, RVM_RuntimeStatic* runtime_static);
void                 rvm_init_static_variable(Ring_VirtualMachine* rvm, Package_Executer* executer, RVM_RuntimeStatic* runtime_static);

int                  ring_execute_vm_code(Ring_VirtualMachine* rvm);

void                 invoke_native_function(Ring_VirtualMachine* rvm, RVM_Function* function, unsigned int argument_list_size);
void                 invoke_derive_function(Ring_VirtualMachine* rvm,
                                            RVM_ClassObject** caller_object, RVM_Function** caller_function,
                                            RVM_ClassObject* callee_object, RVM_Function* callee_function,
                                            RVM_Byte** code_list, unsigned int* code_size,
                                            unsigned int* pc,
                                            unsigned int* caller_stack_base,
                                            unsigned int  argument_list_size);
void                 derive_function_return(Ring_VirtualMachine* rvm,
                                            RVM_Function** caller_function, RVM_Function* callee_function,
                                            RVM_Byte** code_list, unsigned int* code_size,
                                            unsigned int* pc,
                                            unsigned int* caller_stack_base,
                                            unsigned int  return_value_list_size);
void                 derive_function_finish(Ring_VirtualMachine* rvm,
                                            RVM_ClassObject** caller_object, RVM_Function** caller_function,
                                            RVM_Function* callee_function,
                                            RVM_Byte** code_list, unsigned int* code_size,
                                            unsigned int* pc,
                                            unsigned int* caller_stack_base,
                                            unsigned int  return_value_list_size);
void                 store_callinfo(Ring_VirtualMachine* rvm, RVM_CallInfo* call_info);
void                 restore_callinfo(Ring_VirtualMachine* rvm, RVM_CallInfo** call_info);
void                 init_derive_function_local_variable(Ring_VirtualMachine* rvm,
                                                         RVM_ClassObject*     callee_object,
                                                         RVM_Function*        function,
                                                         unsigned int         argument_list_size);

RVM_String*          string_literal_to_rvm_string(Ring_VirtualMachine* rvm, const char* string_literal);
RVM_String*          concat_string(Ring_VirtualMachine* rvm, RVM_String* a, RVM_String* b);


RVM_Array*           rvm_new_array_literal_bool(Ring_VirtualMachine* rvm, unsigned int size);
RVM_Array*           rvm_new_array_literal_int(Ring_VirtualMachine* rvm, unsigned int size);
RVM_Array*           rvm_new_array_literal_int64(Ring_VirtualMachine* rvm, unsigned int size);
RVM_Array*           rvm_new_array_literal_double(Ring_VirtualMachine* rvm, unsigned int size);
RVM_Array*           rvm_new_array_literal_string(Ring_VirtualMachine* rvm, unsigned int size);
RVM_Array*           rvm_new_array_literal_class_object(Ring_VirtualMachine* rvm,
                                                        unsigned int         size,
                                                        RVM_ClassDefinition* class_definition);
RVM_Array*           rvm_new_array_literal_a(Ring_VirtualMachine* rvm,
                                             unsigned int         dimension,
                                             unsigned int         size);

void                 rvm_array_get_length(Ring_VirtualMachine* rvm, RVM_Array* array, int* value);
void                 rvm_array_get_capacity(Ring_VirtualMachine* rvm, RVM_Array* array, int* value);

void                 rvm_string_get_length(Ring_VirtualMachine* rvm, RVM_String* string, int* value);
void                 rvm_string_get_capacity(Ring_VirtualMachine* rvm, RVM_String* string, int* value);

ErrorCode            rvm_array_get_array(Ring_VirtualMachine* rvm, RVM_Array* array, int index, RVM_Array** value);
ErrorCode            rvm_array_set_array(Ring_VirtualMachine* rvm, RVM_Array* array, int index, RVM_Array* value);

ErrorCode            rvm_array_get_bool(Ring_VirtualMachine* rvm, RVM_Array* array, int index, bool* value);
ErrorCode            rvm_array_set_bool(Ring_VirtualMachine* rvm, RVM_Array* array, int index, bool* value);
ErrorCode            rvm_array_append_bool(Ring_VirtualMachine* rvm, RVM_Array* array, bool* value);
ErrorCode            rvm_array_pop_bool(Ring_VirtualMachine* rvm, RVM_Array* array, bool* value);

ErrorCode            rvm_array_get_int(Ring_VirtualMachine* rvm, RVM_Array* array, int index, int* value);
ErrorCode            rvm_array_set_int(Ring_VirtualMachine* rvm, RVM_Array* array, int index, int* value);
ErrorCode            rvm_array_append_int(Ring_VirtualMachine* rvm, RVM_Array* array, int* value);
ErrorCode            rvm_array_pop_int(Ring_VirtualMachine* rvm, RVM_Array* array, int* value);

ErrorCode            rvm_array_get_int64(Ring_VirtualMachine* rvm, RVM_Array* array, int index, long long* value);
ErrorCode            rvm_array_set_int64(Ring_VirtualMachine* rvm, RVM_Array* array, int index, long long* value);
ErrorCode            rvm_array_append_int64(Ring_VirtualMachine* rvm, RVM_Array* array, long long* value);
ErrorCode            rvm_array_pop_int64(Ring_VirtualMachine* rvm, RVM_Array* array, long long* value);


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


RVM_String*          rvm_bool_2_string(Ring_VirtualMachine* rvm, bool value);
RVM_String*          rvm_int_2_string(Ring_VirtualMachine* rvm, int value);
RVM_String*          rvm_int64_2_string(Ring_VirtualMachine* rvm, long long value);
RVM_String*          rvm_double_2_string(Ring_VirtualMachine* rvm, double value);

int                  rvm_string_cmp(RVM_String* string1, RVM_String* string2);

void                 rvm_heap_alloc_size_incr(Ring_VirtualMachine* rvm, unsigned int size);
void                 rvm_heap_alloc_size_decr(Ring_VirtualMachine* rvm, unsigned int size);
void                 rvm_heap_list_add_object(Ring_VirtualMachine* rvm, RVM_GC_Object* object);
void                 rvm_heap_list_remove_object(Ring_VirtualMachine* rvm, RVM_GC_Object* object);


int                  rvm_heap_size(Ring_VirtualMachine* rvm);

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
RVM_Value std_lib_fmt_println_int64(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value std_lib_fmt_println_double(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value std_lib_fmt_println_string(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value std_lib_fmt_println_pointer(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value std_lib_fmt_println(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);
RVM_Value std_lib_fmt_printf(Ring_VirtualMachine* rvm, unsigned int arg_count, RVM_Value* args);

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
std::string format_rvm_function(Package_Executer* package_executer,
                                RVM_Function*     function);
std::string format_rvm_type_specifier(Package_Executer*  package_executer,
                                      RVM_TypeSpecifier* type_specifier);
// --------------------

/* --------------------
 * utils.cpp
 * function definition
 *
 */
std::string              formate_expression(Expression* expression);

void                     ring_compiler_functions_dump(PackageUnit* package_unit);
void                     ring_vm_constantpool_dump(Package_Executer* executer);
void                     ring_vm_code_dump(RVM_Function* function, RVM_Byte* code_list, unsigned int code_size, unsigned int pc, unsigned int screen_row, unsigned int screen_col);
void                     ring_vm_dump_runtime_stack(RVM_RuntimeStack* runtime_stack, unsigned int caller_stack_base, unsigned int screen_row, unsigned int screen_col);
void                     ring_vm_dump_stdout_log(Ring_VirtualMachine* rvm);
std::vector<std::string> list_files_of_dir(char* dir);
RingFileStat*            create_ring_file_stat(std::string& file_name);
std::vector<std::string> get_file_contents(RingFileStat* file_stat, unsigned int start_line, unsigned int end_line);
std::string              get_file_content(RingFileStat* file_stat, unsigned int line_number);

void                     dump_vm_function(Package_Executer*    package_executer,
                                          RVM_ClassDefinition* class_definition,
                                          RVM_Function*        function);
void                     dump_vm_class(Package_Executer*    package_executer,
                                       RVM_ClassDefinition* class_definition);
std::string              dump_vm_constant(RVM_ConstantPool* constant);

unsigned int             get_source_line_number_by_pc(RVM_Function* function, unsigned int pc);

std::string              format_rvm_type(RVM_Value* value);
std::string              format_rvm_value(RVM_Value* value);
std::string              format_rvm_call_stack(Ring_VirtualMachine* rvm);
std::string              format_rvm_current_func(Ring_VirtualMachine* rvm, unsigned int source_line_number);

std::string              format_type_specifier(TypeSpecifier* type_specifier);
std::string              format_function_parameters(Parameter* parameter);
std::string              format_function_arguments(ArgumentList* argument);

std::vector<std::string> splitargs(const char* line);
static int               hex_digit_to_int(char c);

std::string              strings_join(const std::vector<std::string>& lst, const std::string& delim);
int                      string_compare(const char* str1, unsigned int str1_len, const char* str2, unsigned int str2_len);

std::string              formate_array_type(RVM_Array* array_value);
std::string              formate_array_item_type(RVM_Array* array_value);
// --------------------


/* --------------------
 * man_help.cpp
 * function definition
 *
 */
void ring_give_man_help(const char* keyword);
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
void             gc(Ring_VirtualMachine* rvm);
void             gc_summary(Ring_VirtualMachine* rvm);
void             gc_mark(Ring_VirtualMachine* rvm);
void             gc_sweep(Ring_VirtualMachine* rvm);

void             gc_mark_class_ob(Ring_VirtualMachine* rvm, RVM_ClassObject* class_ob);
void             gc_mark_array(Ring_VirtualMachine* rvm, RVM_Array* array);


RVM_String*      new_string(Ring_VirtualMachine* rvm);
unsigned int     init_string(Ring_VirtualMachine* rvm, RVM_String* string, unsigned int capacity);
RVM_String*      rvm_deep_copy_string(Ring_VirtualMachine* rvm, RVM_String* src);

RVM_Array*       new_array(Ring_VirtualMachine* rvm);
RVM_Array*       rvm_new_array(Ring_VirtualMachine* rvm,
                               unsigned int         dimension,
                               unsigned int*        dimension_list,
                               unsigned int         dimension_index,
                               RVM_Array_Type       array_type,
                               RVM_ClassDefinition* class_definition);
RVM_Array*       rvm_deep_copy_array(Ring_VirtualMachine* rvm, RVM_Array* src);


void             rvm_free_object(Ring_VirtualMachine* rvm, RVM_GC_Object* object);
unsigned int     rvm_free_string(Ring_VirtualMachine* rvm, RVM_String* string);
unsigned int     rvm_free_class_object(Ring_VirtualMachine* rvm, RVM_ClassObject* class_object);

RVM_ClassObject* rvm_heap_new_class_object(Ring_VirtualMachine* rvm);
RVM_ClassObject* rvm_new_class_object(Ring_VirtualMachine* rvm, RVM_ClassDefinition* class_definition);
RVM_ClassObject* rvm_deep_copy_class_object(Ring_VirtualMachine* rvm, RVM_ClassObject* src);

// --------------------


/* --------------------
 * debug.cpp
 * function definition
 *
 */

int     debug_trace_dispatch(RVM_Frame* frame, const char* event, const char* arg);
int     dispath_sae(RVM_Frame* frame, const char* event, const char* arg);
int     dispath_opcode(RVM_Frame* frame, const char* event, const char* arg);
int     dispath_line(RVM_Frame* frame, const char* event, const char* arg);
int     dispath_call(RVM_Frame* frame, const char* event, const char* arg);
int     dispath_return(RVM_Frame* frame, const char* event, const char* arg);
int     dispath_exit(RVM_Frame* frame, const char* event, const char* arg);

int     rdb_cli(RVM_Frame* frame, const char* event, const char* arg);
RDB_Arg rdb_parse_command(const char* line);

void    rdb_input_completion(const char* buf, linenoiseCompletions* lc);
char*   rdb_input_hints(const char* buf, int* color, int* bold);


// --------------------

/* --------------------
 * vm-debug.cpp
 * function definition
 *
 */

int       debug_rvm_interactive(Ring_VirtualMachine* rvm, RVM_Function* function, RVM_Byte* code_list, unsigned int code_size, unsigned int pc, unsigned int caller_stack_base);
int       vm_debugger_cli(Ring_VirtualMachine* rvm);
VM_DB_Arg vm_db_parse_command(const char* line);
// --------------------


/* --------------------
 * buildin.cpp
 * function definition
 *
 */


void                  fix_buildin_func_len(Expression*             expression,
                                           FunctionCallExpression* function_call_expression,
                                           Block*                  block,
                                           Function*               func);
void                  fix_buildin_func_capacity(Expression*             expression,
                                                FunctionCallExpression* function_call_expression,
                                                Block*                  block,
                                                Function*               func);
void                  fix_buildin_func_push(Expression*             expression,
                                            FunctionCallExpression* function_call_expression,
                                            Block*                  block,
                                            Function*               func);
void                  fix_buildin_func_pop(Expression*             expression,
                                           FunctionCallExpression* function_call_expression,
                                           Block*                  block,
                                           Function*               func);
void                  fix_buildin_func_to_string(Expression*             expression,
                                                 FunctionCallExpression* function_call_expression,
                                                 Block*                  block,
                                                 Function*               func);
void                  fix_buildin_func_to_int64(Expression*             expression,
                                                FunctionCallExpression* function_call_expression,
                                                Block*                  block,
                                                Function*               func);

RING_BUILD_IN_FUNC_ID is_buildin_function_identifier(char* package_posit, char* identifier);
void                  fix_buildin_func(Expression*             expression,
                                       FunctionCallExpression* function_call_expression,
                                       Block*                  block,
                                       FunctionTuple*          func);

// --------------------


/* --------------------
 * fmt.cpp
 * function definition
 *
 */
std::string fmt_any(RVM_Value* value);
std::string fmt_bool(RVM_Value* value);
std::string fmt_int(RVM_Value* value);
std::string fmt_int64(RVM_Value* value);
std::string fmt_double(RVM_Value* value);
std::string fmt_string(RVM_Value* value);
std::string fmt_class(RVM_Value* value);
std::string fmt_class(RVM_ClassObject* class_object);
std::string fmt_array(RVM_Value* value);
std::string fmt_array(RVM_Array* array_value);

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
