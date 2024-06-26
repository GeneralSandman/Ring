#include "ring.hpp"


struct ErrorMessageInfo ErrorMessageInfos[] = {
    {ERROR_CODE_SUCCESS, "SUCCESS"},

    {ERROR_CODE_COMMAND_ERROR, "COMMAND_ERROR"},

    {ERROR_CODE_COMPILE_ERROR, "COMPILE_ERROR"},

    {ERROR_CODE_SEMANTIC_CHECH_ERROR, "SEMANTIC_CHECH_ERROR"},

    {ERROR_CODE_OPTIMIZATION_AST_ERROR, "OPTIMIZATION_AST_ERROR"},

    {ERROR_CODE_GENERATE_OPCODE_ERROR, "GENERATE_OPCODE_ERROR"},
    {ERROR_CODE_FIX_LABEL, "GENERATE_OPCODE_ERROR"},
    {ERROR_CODE_INVALID_OPCODE, "INVALID_OPCODE"},
    {ERROR_CODE_INVALID_OPCODE_TYPE, "INVALID_OPCODE_TYPE"},

    {ERROR_CODE_LOAD_OPCODE_ERROR, "LOAD_OPCODE_ERROR"},

    {ERROR_CODE_RUN_VM_ERROR, "RUN_VM_ERROR"},
};

// 定义Ring的语法，当发生语法错误时，可以作为TIP抛出
struct SyntaxInfo SyntaxInfos[] = {
    {
        SYNTAX_VARIABLE_DEFINITION,
        (char*)"[Variable Definition]: var type identifier [ = value];",
    },
    {
        SYNTAX_VARIABLE_DEFINITION,
        (char*)"[Variable Definition]: var type identifier [ = value];",
    },
};
