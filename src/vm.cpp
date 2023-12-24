#include "ring.hpp"
#include <cassert>
#include <string>


RVM_Opcode_Info RVM_Opcode_Infos[] = {
    {RVM_CODE_UNKNOW, "", OPCODE_OPERAND_TYPE_0BYTE, 0, 0, "", ""},


    // init double string const
    {RVM_CODE_PUSH_BOOL, "push_bool", OPCODE_OPERAND_TYPE_1BYTE, 1, 2, "push constant bool value to stack", "[]-->[int]"},
    {RVM_CODE_PUSH_INT_1BYTE, "push_int_1byte", OPCODE_OPERAND_TYPE_1BYTE, 1, 2, "push 1byte int constant value to stack", "[]-->[int]"},    // 后边紧跟 int 常量 1 type
    {RVM_CODE_PUSH_INT_2BYTE, "push_int_2byte", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "push 2byte int constant value to stack", "[]-->[int]"}, // 后边紧跟 int 常量 2 type
    {RVM_CODE_PUSH_INT, "push_int", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "push constant int value to stack", "[]-->[int]"},                   // 后边紧跟 int 常量 2 的索引 这里的还要 改一下 OPCODE_OPERAND_TYPE_2BYTE
    {RVM_CODE_PUSH_DOUBLE, "push_double", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "push constant double value to stack", "[]-->[double]"},       // 后边紧跟 double 常量
    {RVM_CODE_PUSH_STRING, "push_string", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "push constant string value to stack", "[]-->[object]"},       // 后边紧跟 string 常量


    // static
    {RVM_CODE_POP_STATIC_BOOL, "pop_static_bool", OPCODE_OPERAND_TYPE_2BYTE_As, -1, 3, "", ""},
    {RVM_CODE_POP_STATIC_INT, "pop_static_int", OPCODE_OPERAND_TYPE_2BYTE_As, -1, 3, "", ""},
    {RVM_CODE_POP_STATIC_DOUBLE, "pop_static_double", OPCODE_OPERAND_TYPE_2BYTE_As, -1, 3, "", ""},
    {RVM_CODE_POP_STATIC_OBJECT, "pop_static_object", OPCODE_OPERAND_TYPE_2BYTE_As, -1, 3, "", ""},
    {RVM_CODE_PUSH_STATIC_BOOL, "push_static_bool", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""},
    {RVM_CODE_PUSH_STATIC_INT, "push_static_int", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""},
    {RVM_CODE_PUSH_STATIC_DOUBLE, "push_static_double", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""},
    {RVM_CODE_PUSH_STATIC_OBJECT, "push_static_object", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""},


    // stack
    {RVM_CODE_POP_STACK_BOOL, "pop_stack_bool", OPCODE_OPERAND_TYPE_2BYTE_As, -1, 3, "", ""},
    {RVM_CODE_POP_STACK_INT, "pop_stack_int", OPCODE_OPERAND_TYPE_2BYTE_As, -1, 3, "", ""},
    {RVM_CODE_POP_STACK_DOUBLE, "pop_stack_double", OPCODE_OPERAND_TYPE_2BYTE_As, -1, 3, "", ""},
    {RVM_CODE_POP_STACK_OBJECT, "pop_stack_object", OPCODE_OPERAND_TYPE_2BYTE_As, -1, 3, "", ""},
    {RVM_CODE_PUSH_STACK_BOOL, "push_stack_bool", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""},
    {RVM_CODE_PUSH_STACK_INT, "push_stack_int", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""},
    {RVM_CODE_PUSH_STACK_DOUBLE, "push_stack_double", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""},
    {RVM_CODE_PUSH_STACK_OBJECT, "push_stack_object", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""},


    // array
    {RVM_CODE_PUSH_ARRAY_BOOL, "push_array_bool", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},
    {RVM_CODE_PUSH_ARRAY_INT, "push_array_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},
    {RVM_CODE_PUSH_ARRAY_DOUBLE, "push_array_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},
    {RVM_CODE_PUSH_ARRAY_STRING, "push_array_string", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},
    {RVM_CODE_PUSH_ARRAY_OBJECT, "push_array_object", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},
    {RVM_CODE_POP_ARRAY_BOOL, "pop_array_bool", OPCODE_OPERAND_TYPE_0BYTE, -3, 1, "assign to bool array by index", "[int,object,int]->[]"},
    {RVM_CODE_POP_ARRAY_INT, "pop_array_int", OPCODE_OPERAND_TYPE_0BYTE, -3, 1, "assign to int array by index", "[int,object,int]->[]"},
    {RVM_CODE_POP_ARRAY_DOUBLE, "pop_array_double", OPCODE_OPERAND_TYPE_0BYTE, -3, 1, "assign to double array by index", "[int,object,int]->[]"},
    {RVM_CODE_POP_ARRAY_STRING, "pop_array_string", OPCODE_OPERAND_TYPE_0BYTE, -3, 1, "assign to string array by index", "[int,object,int]->[]"},
    {RVM_CODE_POP_ARRAY_OBJECT, "pop_array_object", OPCODE_OPERAND_TYPE_0BYTE, -3, 1, "assign to object array by index", "[int,object,int]->[]"},

    // array append
    {RVM_CODE_ARRAY_APPEND_BOOL, "array_append_bool", OPCODE_OPERAND_TYPE_0BYTE, -2, 1, "assign to object array by index", "[object,bool]->[]"},
    {RVM_CODE_ARRAY_APPEND_INT, "array_append_int", OPCODE_OPERAND_TYPE_0BYTE, -2, 1, "assign to object array by index", "[object,int]->[]"},
    {RVM_CODE_ARRAY_APPEND_DOUBLE, "array_append_double", OPCODE_OPERAND_TYPE_0BYTE, -2, 1, "assign to object array by index", "[object,double]->[]"},
    {RVM_CODE_ARRAY_APPEND_STRING, "array_append_string", OPCODE_OPERAND_TYPE_0BYTE, -2, 1, "assign to object array by index", "[object,string]->[]"},
    {RVM_CODE_ARRAY_APPEND_OBJECT, "array_append_object", OPCODE_OPERAND_TYPE_0BYTE, -2, 1, "assign to object array by index", "[object,object]->[]"},
    // array pop
    {RVM_CODE_ARRAY_POP_BOOL, "array_pop_bool", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "assign to object array by index", "[object]->[bool]"},
    {RVM_CODE_ARRAY_POP_INT, "array_pop_int", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "assign to object array by index", "[object]->[int]"},
    {RVM_CODE_ARRAY_POP_DOUBLE, "array_pop_double", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "assign to object array by index", "[object]->[double]"},
    {RVM_CODE_ARRAY_POP_STRING, "array_pop_string", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "assign to object array by index", "[object]->[string]"},
    {RVM_CODE_ARRAY_POP_OBJECT, "array_pop_object", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "assign to object array by index", "[object]->[object]"},


    // class
    {RVM_CODE_POP_FIELD_BOOL, "pop_field_bool", OPCODE_OPERAND_TYPE_2BYTE_As, -1, 3, "assign to class field whith bool", "[bool,object]->[]"},
    {RVM_CODE_POP_FIELD_INT, "pop_field_int", OPCODE_OPERAND_TYPE_2BYTE_As, -1, 3, "", "[int,object]->[]"},
    {RVM_CODE_POP_FIELD_DOUBLE, "pop_field_double", OPCODE_OPERAND_TYPE_2BYTE_As, -1, 3, "", "[double,object]->[]"},
    {RVM_CODE_PUSH_FIELD_BOOL, "push_field_bool", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", "[object]->[bool]"},
    {RVM_CODE_PUSH_FIELD_INT, "push_field_int", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", "[object]->[int]"},
    {RVM_CODE_PUSH_FIELD_DOUBLE, "push_field_double", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", "[object]->[double]"},


    // arithmetic
    {RVM_CODE_ADD_INT, "add_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", "[int,int]->[int]"},
    {RVM_CODE_ADD_DOUBLE, "add_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", "[double,double]->[double]"},

    {RVM_CODE_SUB_INT, "sub_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", "[int,int]->[int]"},
    {RVM_CODE_SUB_DOUBLE, "sub_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", "[double,double]->[double]"},

    {RVM_CODE_MUL_INT, "mul_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", "[int,int]->[int]"},
    {RVM_CODE_MUL_DOUBLE, "mul_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", "[double,double]->[double]"},

    {RVM_CODE_DIV_INT, "div_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", "[int,int]->[int]"},
    {RVM_CODE_DIV_DOUBLE, "div_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", "[double,double]->[double]"},

    {RVM_CODE_MOD_INT, "mod_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", "[int,int]->[int]"},
    {RVM_CODE_MOD_DOUBLE, "mod_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", "[double,double]->[double]"},

    {RVM_CODE_MINUS_INT, "minus_int", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "", "[int,int]->[int]"},
    {RVM_CODE_MINUS_DOUBLE, "minus_double", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "", "[double,double]->[double]"},

    {RVM_CODE_INCREASE_SUFFIX, "increase_suffix", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "", ""},
    {RVM_CODE_INCREASE_PREFIX, "increase_prefix", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "", ""},
    {RVM_CODE_DECREASE_SUFFIX, "decrease_suffix", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "", ""},
    {RVM_CODE_DECREASE_PREFIX, "decrease_prefix", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "", ""},

    {RVM_CODE_CONCAT, "concat", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},

    // type cast
    {RVM_CODE_CAST_BOOL_TO_INT, "cast_bool_to_int", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "", ""},
    {RVM_CODE_CAST_INT_TO_DOUBLE, "cast_int_to_double", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "", ""},

    {RVM_CODE_CAST_INT_TO_BOOL, "cast_int_to_bool", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "", ""},
    {RVM_CODE_CAST_DOUBLE_TO_INT, "cast_double_to_int", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "", ""},


    // logical
    {RVM_CODE_LOGICAL_AND, "logical_and", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},
    {RVM_CODE_LOGICAL_OR, "logical_or", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},
    {RVM_CODE_LOGICAL_NOT, "logical_not", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "", ""},

    // relational
    {RVM_CODE_RELATIONAL_EQ_INT, "eq_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},
    {RVM_CODE_RELATIONAL_EQ_DOUBLE, "eq_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},
    {RVM_CODE_RELATIONAL_EQ_STRING, "eq_string", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},

    {RVM_CODE_RELATIONAL_NE_INT, "ne_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},
    {RVM_CODE_RELATIONAL_NE_DOUBLE, "ne_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},
    {RVM_CODE_RELATIONAL_NE_STRING, "ne_string", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},

    {RVM_CODE_RELATIONAL_GT_INT, "gt_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},
    {RVM_CODE_RELATIONAL_GT_DOUBLE, "gt_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},
    {RVM_CODE_RELATIONAL_GT_STRING, "gt_string", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},

    {RVM_CODE_RELATIONAL_GE_INT, "ge_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},
    {RVM_CODE_RELATIONAL_GE_DOUBLE, "ge_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},
    {RVM_CODE_RELATIONAL_GE_STRING, "ge_string", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},

    {RVM_CODE_RELATIONAL_LT_INT, "lt_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},
    {RVM_CODE_RELATIONAL_LT_DOUBLE, "lt_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},
    {RVM_CODE_RELATIONAL_LT_STRING, "lt_string", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},

    {RVM_CODE_RELATIONAL_LE_INT, "le_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},
    {RVM_CODE_RELATIONAL_LE_DOUBLE, "le_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},
    {RVM_CODE_RELATIONAL_LE_STRING, "le_string", OPCODE_OPERAND_TYPE_0BYTE, -1, 1, "", ""},

    // jump
    {RVM_CODE_JUMP, "jump", OPCODE_OPERAND_TYPE_2BYTE_As, 0, 0, "", ""},
    {RVM_CODE_JUMP_IF_FALSE, "jump_if_false", OPCODE_OPERAND_TYPE_2BYTE_As, -1, 0, "", ""},
    {RVM_CODE_JUMP_IF_TRUE, "jump_if_true", OPCODE_OPERAND_TYPE_2BYTE_As, -1, 0, "", ""},

    // duplicate
    {RVM_CODE_DUPLICATE, "duplicate", OPCODE_OPERAND_TYPE_0BYTE, 1, 1, "", ""},


    // func
    {RVM_CODE_PUSH_FUNC, "push_func", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""},     // TODO: update to 2 byte
    {RVM_CODE_PUSH_METHOD, "push_method", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""}, // TODO:
    {RVM_CODE_ARGUMENT_NUM, "argument_num", OPCODE_OPERAND_TYPE_1BYTE, 0, 2, "", ""},
    {RVM_CODE_INVOKE_FUNC, "invoke_func", OPCODE_OPERAND_TYPE_0BYTE, -1, 0, "", ""},
    {RVM_CODE_INVOKE_METHOD, "invoke_method", OPCODE_OPERAND_TYPE_0BYTE, -2, 0, "", ""},
    {RVM_CODE_RETURN, "return", OPCODE_OPERAND_TYPE_2BYTE_As, 0, 3, "", ""}, // 操作数代表返回值的数量，ex；return int, double, string;  操作数就是3 FIXME:runtime_stack_increment
    {RVM_CODE_FUNCTION_FINISH, "function_finish", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "", ""},

    {RVM_CODE_EXIT, "exit", OPCODE_OPERAND_TYPE_1BYTE, 0, 2, "", ""},

    // new heap memory
    {RVM_CODE_NEW_ARRAY_BOOL, "new_array_bool", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""},
    {RVM_CODE_NEW_ARRAY_INT, "new_array_int", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""},
    {RVM_CODE_NEW_ARRAY_DOUBLE, "new_array_double", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""},
    {RVM_CODE_NEW_ARRAY_STRING, "new_array_string", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""},
    {RVM_CODE_NEW_ARRAY_OBJECT, "new_array_object", OPCODE_OPERAND_TYPE_3BYTE_ABs, 1, 4, "", ""},
    {RVM_CODE_NEW_ARRAY_LITERAL_BOOL, "new_array_literal_bool", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""},
    {RVM_CODE_NEW_ARRAY_LITERAL_INT, "new_array_literal_int", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""},
    {RVM_CODE_NEW_ARRAY_LITERAL_DOUBLE, "new_array_literal_double", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""},
    {RVM_CODE_NEW_ARRAY_LITERAL_STRING, "new_array_literal_string", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""},
    {RVM_CODE_NEW_ARRAY_LITERAL_OBJECT, "new_array_literal_object", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""},

    {RVM_CODE_PUSH_ARRAY_LEN, "push_array_len", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "", ""},
    {RVM_CODE_PUSH_ARRAY_CAPACITY, "push_array_capacity", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "", ""},
    {RVM_CODE_PUSH_STRING_LEN, "push_string_len", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "", ""},
    {RVM_CODE_PUSH_STRING_CAPACITY, "push_string_capacity", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "", ""},

    // class
    {RVM_CODE_NEW_CLASS_OBJECT_LITERAL, "new_class_object_literal", OPCODE_OPERAND_TYPE_2BYTE_AB, 1, 3, "", ""},

    // range
    {RVM_CODE_FOR_RANGE_ARRAY_BOOL, "range_array_bool", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "range bool value for array", ""},
    {RVM_CODE_FOR_RANGE_ARRAY_INT, "range_array_int", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "range int value for array", ""},
    {RVM_CODE_FOR_RANGE_ARRAY_DOUBLE, "range_array_double", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "range double value for array", ""},
    {RVM_CODE_FOR_RANGE_ARRAY_STRING, "range_array_string", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "range string value for array", ""},
    {RVM_CODE_FOR_RANGE_ARRAY_OBJECT, "range_array_object", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "range object value for array", ""},
    {RVM_CODE_FOR_RANGE_STRING, "range_string", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "range char value for string", ""},
    {RVM_CODE_FOR_RANGE_FINISH, "for_range_finish", OPCODE_OPERAND_TYPE_2BYTE_As, 1, 3, "", ""},

    // convert
    {RVM_CODE_BOOL_2_STRING, "bool_2_string", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "convert bool to string", "[bool]->[string]"},
    {RVM_CODE_INT_2_STRING, "int_2_string", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "convert int to string", "[int]->[string]"},
    {RVM_CODE_DOUBLE_2_STRING, "double_2_string", OPCODE_OPERAND_TYPE_0BYTE, 0, 1, "convert double to string", "[double]->[string]"},


    {RVM_CODES_NUM, "", OPCODE_OPERAND_TYPE_0BYTE, 0, 0, "", ""},
};

// TODO: 这里直接使用Cpp::string, 后续需要改成 Ring_String
std::string format_rvm_function(RVM_Function* function) {
    assert(function != nullptr);

    std::string result;

    result += std::string(function->func_name);
    result += "(";
    // formate parameters
    for (unsigned int i = 0; i < function->parameter_size; i++) {
        if (i != 0) {
            result += ", ";
        }
        result += format_rvm_type_specifier(function->parameter_list[i].type_specifier);
    }
    result += ")";

    return result;
}


// TODO: 这里直接使用Cpp::string, 后续需要改成 Ring_String
// TODO: 这里暂时 只能 formate 参数为 bool, int, double, string 其余的类型需要继续支持
std::string format_rvm_type_specifier(RVM_TypeSpecifier* type_specifier) {
    assert(type_specifier != nullptr);

    switch (type_specifier->kind) {
    case RING_BASIC_TYPE_BOOL:
        return "var bool";
    case RING_BASIC_TYPE_INT:
        return "var int";
    case RING_BASIC_TYPE_DOUBLE:
        return "var double";
    case RING_BASIC_TYPE_STRING:
        return "var string";
    case RING_BASIC_TYPE_CLASS:
        // TODO: 这里要获取类的真实名称
        return "var class";
    default:
        // TODO:  后续还要处理 数组
        return "var .unknow";
        break;
    }
    return "";
}