#ifndef RING_INCLUDE_H
#define RING_INCLUDE_H

#include <stdio.h>

#define RING_VERSION "ring-v0.1.19-beta"

typedef struct Ring_Compiler_Tag Ring_Compiler;

typedef struct Ring_VirtualMachine_Tag Ring_VirtualMachine;

typedef struct Ring_VirtualMachine_Executer_Tag Ring_VirtualMachine_Executer;

typedef struct ImportPackageList_Tag ImportPackageList;

typedef struct PackageInfo_Tag PackageInfo;

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

typedef struct ClassDefinition_Tag ClassDefinition;

typedef struct ClassMemberDeclaration_Tag ClassMemberDeclaration;

typedef struct FieldMember_Tag FieldMember;

typedef struct MethodMember_Tag MethodMember;

typedef struct Statement_Tag Statement;

typedef struct StatementExecResult_Tag StatementExecResult;

typedef struct Expression_Tag Expression;

typedef struct ArrayIndexExpression_Tag ArrayIndexExpression;

typedef struct CastExpression_Tag CastExpression;

typedef struct MemberExpression_Tag MemberExpression;

typedef struct BinaryExpression_Tag BinaryExpression;

typedef struct TernaryExpression_Tag TernaryExpression;

typedef struct FunctionCallExpression_Tag FunctionCallExpression;

typedef struct AssignExpression_Tag AssignExpression;

typedef struct ArgumentList_Tag ArgumentList;

typedef struct Variable_Tag Variable;

typedef struct Parameter_Tag Parameter;

typedef struct Identifier_Tag Identifier;

typedef struct Function_Tag Function;

typedef struct Block_Tag Block;

typedef struct FunctionReturnList_Tag FunctionReturnList;

typedef struct IfStatement_Tag IfStatement;

typedef struct ElseIfStatement_Tag ElseIfStatement;

typedef struct ForStatement_Tag ForStatement;

typedef struct DoForStatement_Tag DoForStatement;

typedef struct BreakStatement_Tag BreakStatement;

typedef struct ReturnStatement_Tag ReturnStatement;

typedef struct ContinueStatement_Tag ContinueStatement;

typedef struct Ring_DeriveType_Tag Ring_DeriveType;

typedef struct Declaration_Tag Declaration;

typedef struct TypeSpecifier_Tag TypeSpecifier;

typedef struct RVM_DebugConfig_Tag RVM_DebugConfig;

typedef struct IdentifierExpression_Tag IdentifierExpression;

typedef struct RVM_String_Tag      RVM_String;
typedef struct RVM_Array_Tag       RVM_Array;
typedef struct RVM_ClassObject_Tag RVM_ClassObject;
typedef struct RVM_Object_Tag      RVM_Object;

typedef void Ring_InnerFunc(int argc, Ring_BasicValue** value);

typedef struct RVM_LocalVariable RVM_LocalVariable;
typedef struct NativeFunction    NativeFunction;
typedef struct DeriveFunction    DeriveFunction;
typedef struct RVM_Function      RVM_Function;

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
    Variable*    variable_list; // FIXME: ?????????????????????????????????????????????????????????????????????

    unsigned int identifier_list_size; // TODO:???????????????
    Identifier*  identifier_list;      // TODO:???????????????

    unsigned int declaration_list_size;
    Declaration* declaration_list;

    Block* current_block;

    unsigned int compile_error_num;
};

typedef unsigned char RVM_Byte;

typedef enum {
    RVM_VALUE_TYPE_UNKNOW,

    RVM_VALUE_TYPE_BOOL,
    RVM_VALUE_TYPE_INT,
    RVM_VALUE_TYPE_DOUBLE,
    RVM_VALUE_TYPE_STRING,
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

struct Ring_VirtualMachine_Tag {
    Ring_VirtualMachine_Executer* executer;

    RVM_RuntimeStatic* runtime_static;
    RVM_RuntimeStack*  runtime_stack;
    RVM_RuntimeHeap*   runtime_heap;
    unsigned int       pc;

    RVM_Function* function_list;
    unsigned int  function_size;

    RVM_DebugConfig* debug_config;
};

struct ImportPackageList_Tag {
    PackageInfo*       package_info;
    ImportPackageList* next;
};

struct PackageInfo_Tag {
    unsigned int line_number;

    char* package_name;
    char* package_path;
    char* rename;
};

typedef RVM_Value RVM_NativeFuncProc(Ring_VirtualMachine* rvm, unsigned int arg_cout, RVM_Value* args);

typedef enum {
    RVM_FUNCTION_TYPE_UNKNOW,
    RVM_FUNCTION_TYPE_NATIVE, // ????????????
    RVM_FUNCTION_TYPE_DERIVE, // ???????????????????????????Ring??????????????????
} RVMFunctionType;

struct RVM_LocalVariable {
    char* identifier;
    // TODO:
};

struct NativeFunction {
    RVM_NativeFuncProc* func_proc;
    int                 arg_count; // -1 ??????????????????
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


// generate.c

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
    // ????????????????????????
    unsigned int  global_variable_size;
    RVM_Variable* global_variable_list;

    // ????????????????????????
    unsigned int  function_size;
    RVM_Function* function_list;

    // ????????????????????????
    unsigned int code_size;
    RVM_Byte*    code_list;

    unsigned int estimate_runtime_stack_capacity;
};


// generate.c


struct RVM_Variable_Tag {
    char*          identifier;
    TypeSpecifier* type;
};


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

struct RVM_ClassObject_Tag {
    unsigned int filed_count;
    RVM_Value*   fields;
};

struct RVM_Object_Tag {
    RVM_Object_Type type;
    union {
        RVM_String      string;
        RVM_Array       array;
        RVM_ClassObject class_object;
    } u;
};

// ??????????????????
struct RVM_RuntimeStack_Tag {
    RVM_Value*   data;
    unsigned int top_index;
    unsigned int size;
    unsigned int capacity;
};

struct RVM_RuntimeStatic_Tag {
    RVM_Value*   data;
    unsigned int size;
    unsigned int capacity;
};

struct RVM_RuntimeHeap_Tag {
    // TODO: ????????????
    unsigned int i;
};

struct RVM_LabelTable_Tag {
    char*        label_name;
    unsigned int label_address;
};

typedef struct {
    char*        source_file_name;
    unsigned int source_code_line_number; // ??????Ring????????????????????????

    unsigned int opcode_begin_index; // ?????? opcode ??? ????????????
    unsigned int opcode_size;        // ??????Ring????????? ?????? opcode size
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
    OPCODE_OPERAND_TYPE_0BYTE, // ?????????????????????
    OPCODE_OPERAND_TYPE_1BYTE,
    OPCODE_OPERAND_TYPE_2BYTE,
} OpcodeOperandType;

struct RVM_Opcode_Info_Tag {
    RVM_Byte          code;
    char*             name;
    OpcodeOperandType type;
    int               runtime_stack_increment; // estimate runtime stack capacity
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
    RVM_CODE_PUSH_FIELD_BOOL,
    RVM_CODE_PUSH_FIELD_INT,
    RVM_CODE_PUSH_FIELD_DOUBLE,
    RVM_CODE_POP_FIELD_BOOL,
    RVM_CODE_POP_FIELD_INT,
    RVM_CODE_POP_FIELD_DOUBLE,

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
    RVM_CODE_ARGUMENT_NUM,
    RVM_CODE_INVOKE_FUNC,
    RVM_CODE_RETURN,
    RVM_CODE_FUNCTION_FINISH,

    // ????????????????????????????????????
    RVM_CODES_NUM, // ????????????RVM CODE ?????????
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
    unsigned int  caller_pc; // ????????????????????????
    unsigned int  caller_stack_base;
    unsigned int  callee_argument_size; // ??????????????????????????????????????????
} RVM_CallInfo;

#define CALL_INFO_MAGIC_NUMBER (0x8421) // 33852
#define CALL_INFO_SIZE ((sizeof(RVM_CallInfo) - 1) / sizeof(RVM_Value) + 1)

struct Ring_String_Tag {
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
    EXPRESSION_TYPE_ASSIGN,

    EXPRESSION_TYPE_TERNARY, // ????????????

    EXPRESSION_TYPE_CONCAT,
    EXPRESSION_TYPE_ARITHMETIC_ADD,
    EXPRESSION_TYPE_ARITHMETIC_SUB,
    EXPRESSION_TYPE_ARITHMETIC_MUL,
    EXPRESSION_TYPE_ARITHMETIC_DIV,
    EXPRESSION_TYPE_ARITHMETIC_MOD,
    EXPRESSION_TYPE_ARITHMETIC_UNITARY_MINUS, // ??????????????? ??????
    EXPRESSION_TYPE_LOGICAL_AND,
    EXPRESSION_TYPE_LOGICAL_OR,
    EXPRESSION_TYPE_LOGICAL_UNITARY_NOT,     // ??????????????? ?????? ??? not
    EXPRESSION_TYPE_UNITARY_INCREASE_SUFFIX, // ??????????????? i++
    EXPRESSION_TYPE_UNITARY_INCREASE_PREFIX, // ??????????????? ++i
    EXPRESSION_TYPE_UNITARY_DECREASE_SUFFIX, // ??????????????? i--
    EXPRESSION_TYPE_UNITARY_DECREASE_PREFIX, // ??????????????? --i
    EXPRESSION_TYPE_RELATIONAL_EQ,
    EXPRESSION_TYPE_RELATIONAL_NE,
    EXPRESSION_TYPE_RELATIONAL_GT,
    EXPRESSION_TYPE_RELATIONAL_GE,
    EXPRESSION_TYPE_RELATIONAL_LT,
    EXPRESSION_TYPE_RELATIONAL_LE,

    EXPRESSION_TYPE_ARRAY_INDEX,

    EXPRESSION_TYPE_CAST,
    EXPRESSION_TYPE_MEMBER,
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

struct Ring_BasicValue_Tag {
    BasicValueType type;
    BasicValueType array_member_type;

    union {
        Ring_Bool   bool_value;
        int         int_value;
        double      double_value;
        char        char_value;
        char*       string_value; // ???????????????
        Ring_Array* array_value;
    } u;
    Ring_BasicValue* next; // FIXME: ???????????? return ??????????????? return 1,2; ??? interpret_binary_expression:invoke_function
    // FIXME: ????????????????????????
};

struct Ring_Array_Tag {
    unsigned int     size;
    Ring_BasicValue* data;
};

// ----------------------------------
// class define
// ----------------------------------


struct ClassDefinition_Tag {
    unsigned int line_number;

    char*                   name;
    ClassMemberDeclaration* member;

    ClassDefinition* next;
};

typedef enum {
    MEMBER_UNKNOW = 0,
    MEMBER_FIELD,
    MEMBER_METHOD,
} ClassMemberType;

struct ClassMemberDeclaration_Tag {
    unsigned int line_number;

    // ??????
    // ?????? / ??????

    ClassMemberType type;
    union {
        FieldMember*  field;
        MethodMember* method;
    } u;

    ClassMemberDeclaration* next;
};

// ???????????????
struct FieldMember_Tag {
    unsigned int line_number;

    TypeSpecifier* type;
    char*          identifier;
    unsigned int   index_of_class; // fix it in fix_ast
};

// ?????????
struct MethodMember_Tag {
    unsigned int line_number;

    char*        identifier;
    unsigned int index_of_class; // fix it in fix_ast
};


// ----------------------------------
// class define
// ----------------------------------

struct Statement_Tag {
    unsigned int line_number;

    StatementType type;
    union {
        Expression*        expression;
        Variable*          variable; // TODO: ???????????? ?????? declaration_statement
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

struct StatementExecResult_Tag {
    StatementExecResultType type;
    union {
        Ring_BasicValue* return_value;
    } u; // TODO: ???????????????????????? ??????????????????????????????????????????return_value_list_size & return_value_list
    unsigned int      return_value_list_size;
    Ring_BasicValue** return_value_list;
};

struct Expression_Tag {
    unsigned int line_number;

    TypeSpecifier* convert_type; // ?????????????????????????????????????????????, update in fix_ast
    ExpressionType type;
    union {
        Ring_Bool               bool_literal;
        int                     int_literal;
        double                  double_literal;
        char*                   string_literal;
        IdentifierExpression*   identifier_expression;
        FunctionCallExpression* function_call_expression;
        AssignExpression*       assign_expression;
        TernaryExpression*      ternary_expression;
        BinaryExpression*       binary_expression;
        Expression*             unitary_expression;
        ArrayIndexExpression*   array_index_expression;
        CastExpression*         cast_expression;
        MemberExpression*       member_expression;
    } u;

    Expression* next;
};

typedef enum {
    IDENTIFIER_EXPRESSION_TYPE_UNKNOW,
    IDENTIFIER_EXPRESSION_TYPE_VARIABLE,
    IDENTIFIER_EXPRESSION_TYPE_VARIABLE_ARRAY,
    IDENTIFIER_EXPRESSION_TYPE_FUNCTION,
} IdentifierExpressionType;

struct IdentifierExpression_Tag {
    unsigned int line_number;

    IdentifierExpressionType type;
    char*                    identifier;
    union {
        Declaration* declaration;
        Function*    function;
    } u;
};

struct ArrayIndexExpression_Tag {
    unsigned int line_number;

    char*       variable_identifier;
    Expression* index_expression;
};

// TODO: ?????????????????????????????? ????????? basic type??????
// ??????
typedef enum {
    CAST_TYPE_UNKNOW,

    CAST_TYPE_TO_BOOL,
    CAST_TYPE_TO_INT,
    CAST_TYPE_TO_DOUBLE,
    CAST_TYPE_TO_STRING,
} CastType;

struct CastExpression_Tag {
    unsigned int line_number;

    TypeSpecifier* type;
    Expression*    operand;
};

struct MemberExpression_Tag {
    unsigned int line_number;

    Expression*             object_expression;
    char*                   member_identifier;
    ClassMemberDeclaration* member_declaration; // fix it in fix_ast.c
};

struct FunctionCallExpression_Tag {
    unsigned int line_number;

    Expression*   function_identifier_expression;
    ArgumentList* argument_list;
};

struct Identifier_Tag { // TODO: ????????????????????????
    unsigned int line_number;

    IdentifierType type;
    char*          identifier_name;
    unsigned int   array_index; // ?????????????????????????????????????????????????????????

    Function* parent_scope; //?????????

    Identifier* next;
};

// TODO: ?????????????????? ??????????????????
struct AssignExpression_Tag {
    unsigned int line_number;

    AssignExpressionType type;
    Expression*          left;
    Expression*          operand;
};

struct BinaryExpression_Tag {
    Expression* left_expression;
    Expression* right_expression;
};

// ???????????????
struct TernaryExpression_Tag {
    Expression* condition_expression;
    Expression* true_expression;
    Expression* false_expression;
};

struct ArgumentList_Tag {
    Expression*   expression;
    ArgumentList* next;
};

struct Variable_Tag {
    unsigned int line_number;

    char* variable_identifer;
    int   is_const;

    VariableType type;
    VariableType array_member_type; // ????????????????????????

    union {
        Ring_BasicValue* ring_basic_value;
    } u;
    Expression* init_expression;
    Variable*   next;
};

struct Parameter_Tag {
    unsigned int line_number;

    TypeSpecifier* type;
    char*          identifier;
    Parameter*     next;
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

struct Block_Tag {
    unsigned int line_number;

    BlockType type;

    unsigned int declaration_list_size;
    Declaration* declaration_list;

    unsigned int statement_list_size;
    Statement*   statement_list;

    Block* parent_block;

    BlockLabels block_labels;
};

struct Function_Tag {
    unsigned int line_number;

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

struct FunctionReturnList_Tag {
    VariableType        variable_type;
    FunctionReturnList* next;
};

struct IfStatement_Tag {
    unsigned int line_number;

    Expression* condition_expression;

    Block*           if_block;
    ElseIfStatement* elseif_list;
    Block*           else_block;
};

struct ElseIfStatement_Tag {
    unsigned int line_number;

    Expression* condition_expression; // TODO: ???????????????????????? conidtion_expression;

    Block* elseif_block;

    ElseIfStatement* next;
};

struct ForStatement_Tag {
    unsigned int line_number;

    Expression* init_expression;
    Expression* condition_expression;
    Expression* post_expression;

    Block* block;
};

struct DoForStatement_Tag {
    unsigned int line_number;

    Expression* init_expression;
    Block*      block;
    Expression* condition_expression;
    Expression* post_expression;
};


struct BreakStatement_Tag {
    unsigned int line_number;

    unsigned int break_loop_num; // break; break 1; break 2;
};

struct ContinueStatement_Tag {
    unsigned int line_number;
};

struct ReturnStatement_Tag {
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

    // TODO: ??????????????????, ??????????????????typedef???????????????
};


typedef enum {
    RVM_DEBUG_MODE_UNKNOW,

    RVM_DEBUG_MODE_STEPINTO,
    RVM_DEBUG_MODE_STEPOVER,
    RVM_DEBUG_MODE_STEPOUT,

} RVM_DebugMode;

struct RVM_DebugConfig_Tag {
    RVM_DebugMode debug_mode;
};

typedef enum {
    ERROR_CODE_SUCCESS,

    // ?????????????????????
    ERROR_CODE_COMMAND_ERROR,

    // ????????????
    ERROR_CODE_COMPILE_ERROR,

    // ??????????????????
    ERROR_CODE_SEMANTIC_CHECH_ERROR,

    // ??????AST??????
    ERROR_CODE_OPTIMIZATION_AST_ERROR,


    // ???????????????????????????
    ERROR_CODE_GENERATE_OPCODE_ERROR,
    ERROR_CODE_FIX_LABEL,
    ERROR_CODE_INVALID_OPCODE,
    ERROR_CODE_INVALID_OPCODE_TYPE,

    // ???????????????????????????
    ERROR_CODE_LOAD_OPCODE_ERROR,

    // ?????????????????????
    ERROR_CODE_RUN_VM_ERROR,
} ErrorCode;

struct ErrorMessageInfo {
    ErrorCode error_code;
    char*     error_messaage;
};

typedef enum {
    SYNTAX_VARIABLE_DEFINITION,

} SyntaxType;

struct SyntaxInfo {
    SyntaxType syntax_type;
    char*      bnf;
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
// debug ????????????
#define debug_log_with_red_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_RED, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
// debug ????????????
#define debug_log_with_green_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_GREEN, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
// debug ??????????????????AST
#define debug_log_with_yellow_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_YELLOW, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
// debug ????????????AST
#define debug_log_with_blue_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_BLUE, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
// debug ?????? vm opcode
#define debug_log_with_purple_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_PURPLE, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
// debug ?????? vm opcode
#define debug_log_with_darkgreen_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_DARKGREEN, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
// debug ?????? vm opcode
#define debug_log_with_white_coloar(format, ...) \
    printf("%s[DEBUG][%s:%d][function:%s]" format "%s\n", LOG_COLOR_WHITE, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__, LOG_COLOR_CLEAR)
#else
// ????????????
#define debug_log_with_red_coloar(format, ...)
// ?????????????????????
#define debug_log_with_green_coloar(format, ...)
#define debug_log_with_yellow_coloar(format, ...)
#define debug_log_with_blue_coloar(format, ...)
// ????????????
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
void           ring_compiler_error(SyntaxType syntax_type, int exit);
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

// ???????????????????????????
int ring_semantic_check(Ring_Compiler* ring_compiler);

void                    create_statement_list(Statement* statement);
void                    statement_list_add_item(Statement* statement);
Statement*              statement_list_add_item2(Statement* statement);
Statement*              statement_list_add_item3(Statement* statement_list, Statement* statement);
Statement*              create_statemen_from_expression(Expression* expression);
Statement*              create_statement_from_variable(Variable* variable);
void                    add_function_definition(Function* function_definition);
Expression*             create_expression();
Expression*             create_expression_identifier(char* identifier);
Expression*             create_expression_identifier2(char* identifier, IdentifierExpressionType type);
Expression*             create_expression_identifier_with_index(char* identifier, Expression* index);
Expression*             create_expression_(FunctionCallExpression* function_call_expression);
Expression*             create_expression__(AssignExpression* assign_expression);
Expression*             create_expression_ternary(Expression* condition, Expression* true_expression, Expression* false_expression);
Expression*             create_expression_binary(ExpressionType type, Expression* left, Expression* right);
Expression*             create_expression_unitary(ExpressionType type, Expression* unitary_expression);
Expression*             create_expression_unitary_with_convert_type(BasicValueType convert_type, Expression* expression);
Expression*             create_expression_literal(ExpressionType type, char* literal_interface);
Expression*             create_expression_bool_literal(ExpressionType type, Ring_Bool value);
Expression*             create_cast_expression(TypeSpecifier* cast_type, Expression* operand);
Expression*             create_member_expression();
AssignExpression*       create_assign_expression(AssignExpressionType type, Expression* left, Expression* operand);
AssignExpression*       create_multi_assign_expression(char* first_identifier, Identifier* identifier_list, Expression* operand);
FunctionCallExpression* create_function_call_expression(char* identifier, ArgumentList* argument_list);
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

PackageInfo*       create_package_info(char* package_name, char* rename);
ImportPackageList* create_import_package_list(PackageInfo* package_info);
ImportPackageList* import_package_list_add_item(ImportPackageList* import_package_list, PackageInfo* package_info);


ClassDefinition* start_class_definition(char* name);
ClassDefinition* finish_class_definition(ClassDefinition* class, ClassMemberDeclaration* class_member_declar);

FieldMember* create_field_member(TypeSpecifier* type_specifier, Identifier* identifier_list);

TypeSpecifier* create_class_type_specifier(char* identifier);
// create_ast.c

// fix.c
void           ring_compiler_fix_ast(Ring_Compiler* ring_compiler);
void           fix_statement_list(Statement* statement_list, Block* block, Function* func);
void           fix_statement(Statement* statement, Block* block, Function* func);
void           fix_expression(Expression* expression, Block* block, Function* func);
void           add_declaration(Declaration* declaration, Block* block, Function* func);
void           fix_block(Block* block, Function* func);
void           fix_if_statement(IfStatement* if_statement, Block* block, Function* func);
void           fix_for_statement(ForStatement* for_statement, Block* block, Function* func);
void           fix_dofor_statement(DoForStatement* dofor_statement, Block* block, Function* func);
void           fix_return_statement(ReturnStatement* return_statement, Block* block, Function* func);
TypeSpecifier* fix_identifier_expression(IdentifierExpression* expression, Block* block);
void           fix_assign_expression(AssignExpression* expression, Block* block, Function* func);
void           fix_binary_expression(Expression* expression, Block* block, Function* func);
void           fix_function_call_expression(FunctionCallExpression* function_call_expression, Block* block, Function* func);
void           fix_ternary_condition_expression(TernaryExpression* ternary_expression, Block* block, Function* func);
void           add_parameter_to_declaration(Parameter* parameter, Block* block);
Declaration*   search_declaration(char* identifier, Block* block);
Function*      search_function(char* identifier);

// generate.c
Ring_VirtualMachine_Executer* new_ring_vm_executer();

void              ring_generate_vm_code(Ring_Compiler* compiler, Ring_VirtualMachine_Executer* executer);
void              add_global_variable(Ring_Compiler* compiler, Ring_VirtualMachine_Executer* executer);
void              add_functions(Ring_Compiler* compiler, Ring_VirtualMachine_Executer* executer);
void              copy_function(Function* src, RVM_Function* dest);
void              add_top_level_code(Ring_Compiler* compiler, Ring_VirtualMachine_Executer* executer);
void              generate_code_from_function_definition(Ring_VirtualMachine_Executer* executer, Function* src, RVM_Function* dest);
void              vm_executer_dump(Ring_VirtualMachine_Executer* executer);
RVM_OpcodeBuffer* new_opcode_buffer();
void              generate_vmcode_from_block(Ring_VirtualMachine_Executer* executer, Block* block, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_statement_list(Ring_VirtualMachine_Executer* executer, Block* block, Statement* statement_list, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_if_statement(Ring_VirtualMachine_Executer* executer, IfStatement* if_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_for_statement(Ring_VirtualMachine_Executer* executer, ForStatement* for_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_dofor_statement(Ring_VirtualMachine_Executer* executer, DoForStatement* dofor_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_break_statement(Ring_VirtualMachine_Executer* executer, Block* block, BreakStatement* break_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_continue_statement(Ring_VirtualMachine_Executer* executer, Block* block, ContinueStatement* continue_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_return_statement(Ring_VirtualMachine_Executer* executer, Block* block, ReturnStatement* return_statement, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_initializer(Ring_VirtualMachine_Executer* executer, Block* block, Declaration* declaration, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer, int need_duplicate);
void              generate_vmcode_from_assign_expression(Ring_VirtualMachine_Executer* executer, AssignExpression* expression, RVM_OpcodeBuffer* new_opcode_buffer);
void              generate_pop_to_leftvalue_reverse(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_pop_to_leftvalue(Ring_VirtualMachine_Executer* executer, IdentifierExpression* identifier_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_logical_expression(Ring_VirtualMachine_Executer* executer, BinaryExpression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode);
void              generate_vmcode_from_binary_expression(Ring_VirtualMachine_Executer* executer, BinaryExpression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode);
void              generate_vmcode_from_unitary_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode);
void              generate_vmcode_from_increase_decrease_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer, int need_duplicate);
void              generate_vmcode_from_identifier_expression(Ring_VirtualMachine_Executer* executer, IdentifierExpression* identifier_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_bool_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_int_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_double_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_string_expression(Ring_VirtualMachine_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_function_call_expression(Ring_VirtualMachine_Executer* executer, FunctionCallExpression* function_call_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_cast_expression(Ring_VirtualMachine_Executer* executer, CastExpression* cast_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_member_expression(Ring_VirtualMachine_Executer* executer, MemberExpression* member_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode_from_ternary_condition_expression(Ring_VirtualMachine_Executer* executer, TernaryExpression* ternary_expression, RVM_OpcodeBuffer* opcode_buffer);
void              generate_vmcode(Ring_VirtualMachine_Executer* executer, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode, unsigned int int_literal);

int constant_pool_grow(Ring_VirtualMachine_Executer* executer, unsigned int growth_size);
int constant_pool_add_int(Ring_VirtualMachine_Executer* executer, int int_literal);
int constant_pool_add_double(Ring_VirtualMachine_Executer* executer, double double_literal);
int constant_pool_add_string(Ring_VirtualMachine_Executer* executer, char* string_literal);


unsigned int opcode_buffer_get_label(RVM_OpcodeBuffer* opcode_buffer);
void         opcode_buffer_set_label(RVM_OpcodeBuffer* opcode_buffer, unsigned int label, unsigned int label_address);
void         opcode_buffer_fix_label(RVM_OpcodeBuffer* opcode_buffer);
RVM_Opcode   convert_opcode_by_rvm_type(RVM_Opcode opcode, TypeSpecifier* type);
unsigned int calc_runtime_stack_capacity(RVM_Byte* code_list, unsigned int code_size);
// generate.c

// execute.c

inline void STACK_SET_INT_INDEX(Ring_VirtualMachine* rvm, unsigned int index, int value);
inline void STACK_SET_DOUBLE_INDEX(Ring_VirtualMachine* rvm, unsigned int index, double value);
inline void STACK_SET_OBJECT_INDEX(Ring_VirtualMachine* rvm, unsigned int index, RVM_Object* value);

RVM_RuntimeStack*    new_runtime_stack();
RVM_RuntimeStatic*   new_runtime_static();
Ring_VirtualMachine* new_ring_virtualmachine(Ring_VirtualMachine_Executer* executer);
void                 rvm_add_static_variable(Ring_VirtualMachine_Executer* executer, RVM_RuntimeStatic* runtime_static);
void                 rvm_add_derive_functions(Ring_VirtualMachine_Executer* executer, Ring_VirtualMachine* rvm);
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
void      rvm_register_native_function(Ring_VirtualMachine* rvm, char* func_name, RVM_NativeFuncProc* func_proc, int arg_count);
void      rvm_register_native_functions(Ring_VirtualMachine* rvm);
// execute.c


// bytecode.c
void ring_bytecode_dump(Ring_VirtualMachine_Executer* executer, FILE* output);
void ring_bytecode_load(Ring_VirtualMachine_Executer* executer, FILE* input);
// bytecode.c


// interactive.c
void ring_interactive_program();
int  write_tmp_source_file(char* tmp_source_file_name, int start_line_num, int line_size, char** input_line_content);
// interactive.c

// utils.c
void ring_compiler_functions_dump(Ring_Compiler* compiler);
void ring_vm_constantpool_dump(Ring_VirtualMachine_Executer* executer);
void ring_vm_code_dump(RVM_Function* function, RVM_Byte* code_list, unsigned int code_size, unsigned int pc, unsigned int screen_row, unsigned int screen_col);
void ring_vm_dump_runtime_stack(RVM_RuntimeStack* runtime_stack, unsigned int caller_stack_base, unsigned int screen_row, unsigned int screen_col);
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
