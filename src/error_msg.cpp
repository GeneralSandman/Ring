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


// TODO: 这里是个静态变量，后续优化掉
static std::string runtime_exception_str;
//
RuntimeException::RuntimeException(ErrorEnum            error_num,
                                   std::string          message,
                                   Ring_VirtualMachine* rvm) {
    this->error_num = error_num;
    this->message   = message;
    this->rvm       = rvm;
}
const char* RuntimeException::what() const noexcept {

    std::string error_num_str;
    switch (this->error_num) {
    case RING_INTERNAL_ERROR: error_num_str = "InternalError"; break;
    case RING_NIL_ERROR: error_num_str = "NilError"; break;
    case RING_RANGE_ERROR: error_num_str = "RangeError"; break;
    case RING_INVALID_OPCODE_ERROR: error_num_str = "InvalidOpcodeError"; break;
    }

    std::string call_stack = format_rvm_call_stack(this->rvm);

    runtime_exception_str  = sprintf_string("runtime error: %s: %s\n"
                                             "call stack:\n%s",
                                            error_num_str.c_str(),
                                            message.c_str(),
                                            call_stack.c_str());
    return runtime_exception_str.c_str();
}

void throw_nil_error(Ring_VirtualMachine* rvm, const char* fmt, ...) {
    std::string message = sprintf_string(fmt);
    throw RuntimeException(RING_NIL_ERROR, message, rvm);
}
void throw_range_error(Ring_VirtualMachine* rvm, const char* fmt, ...) {
    std::string message = sprintf_string(fmt);
    throw RuntimeException(RING_RANGE_ERROR, message, rvm);
}

void throw_invalid_opcode_error(Ring_VirtualMachine* rvm, const char* fmt, ...) {
    std::string message = sprintf_string(fmt);
    throw RuntimeException(RING_INVALID_OPCODE_ERROR, message, rvm);
}