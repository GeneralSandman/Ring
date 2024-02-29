#include "ring.hpp"
#include <cassert>
#include <string>


RVM_Opcode_Info RVM_Opcode_Infos[] = {
    {RVM_CODE_UNKNOW, "", OPCODE_OPERAND_TYPE_0BYTE, 0, "", ""},


    // init double string const
    {RVM_CODE_PUSH_BOOL, "push_bool", OPCODE_OPERAND_TYPE_1BYTE, 1, "push constant bool value to stack", "[]-->[int]"},
    {RVM_CODE_PUSH_INT_1BYTE, "push_int_1byte", OPCODE_OPERAND_TYPE_1BYTE, 1, "push 1byte int constant value to stack", "[]-->[int]"},    // 后边紧跟 int 常量 1 type
    {RVM_CODE_PUSH_INT_2BYTE, "push_int_2byte", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push 2byte int constant value to stack", "[]-->[int]"}, // 后边紧跟 int 常量 2 type
    {RVM_CODE_PUSH_INT, "push_int", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push constant int value to stack", "[]-->[int]"},                   // 后边紧跟 int 常量 2 的索引 这里的还要 改一下 OPCODE_OPERAND_TYPE_2BYTE
    {RVM_CODE_PUSH_DOUBLE, "push_double", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push constant double value to stack", "[]-->[double]"},       // 后边紧跟 double 常量
    {RVM_CODE_PUSH_STRING, "push_string", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push constant string value to stack", "[]-->[object]"},       // 后边紧跟 string 常量


    // static
    {RVM_CODE_POP_STATIC_BOOL, "pop_static_bool", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "bool assign to global-variable", ""},
    {RVM_CODE_POP_STATIC_INT, "pop_static_int", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "int assign to global-variable", ""},
    {RVM_CODE_POP_STATIC_DOUBLE, "pop_static_double", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "double assign to global-variable", ""},
    {RVM_CODE_POP_STATIC_STRING, "pop_static_string", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "string assign to global-variable", ""},
    {RVM_CODE_POP_STATIC_CLASS_OB, "pop_static_class_ob", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "class-object assign to global-variable", ""},
    {RVM_CODE_POP_STATIC_ARRAY, "pop_static_array", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "array assign to global-variable", ""},
    {RVM_CODE_PUSH_STATIC_BOOL, "push_static_bool", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push global-variable's bool to stack", ""},
    {RVM_CODE_PUSH_STATIC_INT, "push_static_int", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push global-variable's int to stack", ""},
    {RVM_CODE_PUSH_STATIC_DOUBLE, "push_static_double", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push global-variable's double to stack", ""},
    {RVM_CODE_PUSH_STATIC_STRING, "push_static_string", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push global-variable's string to stack", ""},
    {RVM_CODE_PUSH_STATIC_CLASS_OB, "push_static_class_ob", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push global-variable's class-object to stack", ""},
    {RVM_CODE_PUSH_STATIC_ARRAY, "push_static_array", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push global-variable's array to stack", ""},


    // stack
    {RVM_CODE_POP_STACK_BOOL, "pop_stack_bool", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "bool assign to local-variable", ""},
    {RVM_CODE_POP_STACK_INT, "pop_stack_int", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "int assign to local-variable", ""},
    {RVM_CODE_POP_STACK_DOUBLE, "pop_stack_double", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "double assign to local-variable", ""},
    {RVM_CODE_POP_STACK_STRING, "pop_stack_string", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "string assign to local-variable", ""},
    {RVM_CODE_POP_STACK_CLASS_OB, "pop_stack_class_ob", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "class-object assign to local-variable", ""},
    {RVM_CODE_POP_STACK_ARRAY, "pop_stack_array", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "array assign to local-variable", ""},
    {RVM_CODE_PUSH_STACK_BOOL, "push_stack_bool", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push local-variable's bool to stack", ""},
    {RVM_CODE_PUSH_STACK_INT, "push_stack_int", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push local-variable's int to stack", ""},
    {RVM_CODE_PUSH_STACK_DOUBLE, "push_stack_double", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push local-variable's double to stack", ""},
    {RVM_CODE_PUSH_STACK_STRING, "push_stack_string", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push local-variable's string to stack", ""},
    {RVM_CODE_PUSH_STACK_CLASS_OB, "push_stack_class_ob", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push local-variable's class-object to stack", ""},
    {RVM_CODE_PUSH_STACK_ARRAY, "push_stack_array", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push local-variable's array to stack", ""},


    // array
    {RVM_CODE_PUSH_ARRAY_A, "push_array_a", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},

    {RVM_CODE_PUSH_ARRAY_BOOL, "push_array_bool", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_PUSH_ARRAY_INT, "push_array_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_PUSH_ARRAY_DOUBLE, "push_array_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_PUSH_ARRAY_STRING, "push_array_string", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_PUSH_ARRAY_CLASS_OBJECT, "push_array_class_object", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_POP_ARRAY_BOOL, "pop_array_bool", OPCODE_OPERAND_TYPE_0BYTE, -3, "assign to bool array by index", "[int,object,int]->[]"},
    {RVM_CODE_POP_ARRAY_INT, "pop_array_int", OPCODE_OPERAND_TYPE_0BYTE, -3, "assign to int array by index", "[int,object,int]->[]"},
    {RVM_CODE_POP_ARRAY_DOUBLE, "pop_array_double", OPCODE_OPERAND_TYPE_0BYTE, -3, "assign to double array by index", "[int,object,int]->[]"},
    {RVM_CODE_POP_ARRAY_STRING, "pop_array_string", OPCODE_OPERAND_TYPE_0BYTE, -3, "assign to string array by index", "[int,object,int]->[]"},
    {RVM_CODE_POP_ARRAY_CLASS_OBJECT, "pop_array_class_object", OPCODE_OPERAND_TYPE_0BYTE, -3, "assign to object array by index", "[int,object,int]->[]"},

    // array append
    {RVM_CODE_ARRAY_APPEND_BOOL, "array_append_bool", OPCODE_OPERAND_TYPE_0BYTE, -2, "assign to object array by index", "[object,bool]->[]"},
    {RVM_CODE_ARRAY_APPEND_INT, "array_append_int", OPCODE_OPERAND_TYPE_0BYTE, -2, "assign to object array by index", "[object,int]->[]"},
    {RVM_CODE_ARRAY_APPEND_DOUBLE, "array_append_double", OPCODE_OPERAND_TYPE_0BYTE, -2, "assign to object array by index", "[object,double]->[]"},
    {RVM_CODE_ARRAY_APPEND_STRING, "array_append_string", OPCODE_OPERAND_TYPE_0BYTE, -2, "assign to object array by index", "[object,string]->[]"},
    {RVM_CODE_ARRAY_APPEND_CLASS_OBJECT, "array_append_class_object", OPCODE_OPERAND_TYPE_0BYTE, -2, "assign to object array by index", "[object,object]->[]"},
    // array pop
    {RVM_CODE_ARRAY_POP_BOOL, "array_pop_bool", OPCODE_OPERAND_TYPE_0BYTE, 0, "assign to object array by index", "[object]->[bool]"},
    {RVM_CODE_ARRAY_POP_INT, "array_pop_int", OPCODE_OPERAND_TYPE_0BYTE, 0, "assign to object array by index", "[object]->[int]"},
    {RVM_CODE_ARRAY_POP_DOUBLE, "array_pop_double", OPCODE_OPERAND_TYPE_0BYTE, 0, "assign to object array by index", "[object]->[double]"},
    {RVM_CODE_ARRAY_POP_STRING, "array_pop_string", OPCODE_OPERAND_TYPE_0BYTE, 0, "assign to object array by index", "[object]->[string]"},
    {RVM_CODE_ARRAY_POP_CLASS_OBJECT, "array_pop_class_object", OPCODE_OPERAND_TYPE_0BYTE, 0, "assign to object array by index", "[object]->[object]"},


    // class
    {RVM_CODE_POP_FIELD_BOOL, "pop_field_bool", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "assign to class field whith bool", "[bool,object]->[]"},
    {RVM_CODE_POP_FIELD_INT, "pop_field_int", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "", "[int,object]->[]"},
    {RVM_CODE_POP_FIELD_DOUBLE, "pop_field_double", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "", "[double,object]->[]"},
    {RVM_CODE_POP_FIELD_STRING, "pop_field_string", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "", "[string,object]->[]"},
    {RVM_CODE_POP_FIELD_CLASS_OB, "pop_field_class_ob", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "", "[object,object]->[]"},
    {RVM_CODE_POP_FIELD_ARRAY, "pop_field_array", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "", "[array,object]->[]"},
    {RVM_CODE_PUSH_FIELD_BOOL, "push_field_bool", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "", "[object]->[bool]"},
    {RVM_CODE_PUSH_FIELD_INT, "push_field_int", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "", "[object]->[int]"},
    {RVM_CODE_PUSH_FIELD_DOUBLE, "push_field_double", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "", "[object]->[double]"},
    {RVM_CODE_PUSH_FIELD_STRING, "push_field_string", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "", "[object]->[string]"},
    {RVM_CODE_PUSH_FIELD_CLASS_OB, "push_field_class_ob", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "", "[object]->[string]"},
    {RVM_CODE_PUSH_FIELD_ARRAY, "push_field_array", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "", "[object]->[string]"},

    // arithmetic
    {RVM_CODE_ADD_INT, "add_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int,int]->[int]"},
    {RVM_CODE_ADD_DOUBLE, "add_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[double,double]->[double]"},

    {RVM_CODE_SUB_INT, "sub_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int,int]->[int]"},
    {RVM_CODE_SUB_DOUBLE, "sub_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[double,double]->[double]"},

    {RVM_CODE_MUL_INT, "mul_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int,int]->[int]"},
    {RVM_CODE_MUL_DOUBLE, "mul_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[double,double]->[double]"},

    {RVM_CODE_DIV_INT, "div_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int,int]->[int]"},
    {RVM_CODE_DIV_DOUBLE, "div_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[double,double]->[double]"},

    {RVM_CODE_MOD_INT, "mod_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int,int]->[int]"},
    {RVM_CODE_MOD_DOUBLE, "mod_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[double,double]->[double]"},

    {RVM_CODE_MINUS_INT, "minus_int", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "[int,int]->[int]"},
    {RVM_CODE_MINUS_DOUBLE, "minus_double", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "[double,double]->[double]"},

    {RVM_CODE_SELF_INCREASE, "self_increase", OPCODE_OPERAND_TYPE_0BYTE, 0, "", ""},
    {RVM_CODE_SELF_DECREASE, "self_decrease", OPCODE_OPERAND_TYPE_0BYTE, 0, "", ""},

    {RVM_CODE_CONCAT, "concat", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},

    // type cast
    {RVM_CODE_CAST_BOOL_TO_INT, "cast_bool_to_int", OPCODE_OPERAND_TYPE_0BYTE, 0, "", ""},
    {RVM_CODE_CAST_INT_TO_DOUBLE, "cast_int_to_double", OPCODE_OPERAND_TYPE_0BYTE, 0, "", ""},

    {RVM_CODE_CAST_INT_TO_BOOL, "cast_int_to_bool", OPCODE_OPERAND_TYPE_0BYTE, 0, "", ""},
    {RVM_CODE_CAST_DOUBLE_TO_INT, "cast_double_to_int", OPCODE_OPERAND_TYPE_0BYTE, 0, "", ""},


    // logical
    {RVM_CODE_LOGICAL_AND, "logical_and", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_LOGICAL_OR, "logical_or", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_LOGICAL_NOT, "logical_not", OPCODE_OPERAND_TYPE_0BYTE, 0, "", ""},

    // relational
    {RVM_CODE_RELATIONAL_EQ_INT, "eq_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_RELATIONAL_EQ_DOUBLE, "eq_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_RELATIONAL_EQ_STRING, "eq_string", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},

    {RVM_CODE_RELATIONAL_NE_INT, "ne_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_RELATIONAL_NE_DOUBLE, "ne_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_RELATIONAL_NE_STRING, "ne_string", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},

    {RVM_CODE_RELATIONAL_GT_INT, "gt_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_RELATIONAL_GT_DOUBLE, "gt_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_RELATIONAL_GT_STRING, "gt_string", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},

    {RVM_CODE_RELATIONAL_GE_INT, "ge_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_RELATIONAL_GE_DOUBLE, "ge_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_RELATIONAL_GE_STRING, "ge_string", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},

    {RVM_CODE_RELATIONAL_LT_INT, "lt_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_RELATIONAL_LT_DOUBLE, "lt_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_RELATIONAL_LT_STRING, "lt_string", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},

    {RVM_CODE_RELATIONAL_LE_INT, "le_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_RELATIONAL_LE_DOUBLE, "le_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_RELATIONAL_LE_STRING, "le_string", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},

    // jump
    {RVM_CODE_JUMP, "jump", OPCODE_OPERAND_TYPE_2BYTE_As, 0, "", ""},
    {RVM_CODE_JUMP_IF_FALSE, "jump_if_false", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "", ""},
    {RVM_CODE_JUMP_IF_TRUE, "jump_if_true", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "", ""},

    // duplicate
    {RVM_CODE_DUPLICATE, "duplicate", OPCODE_OPERAND_TYPE_2BYTE_AB, 1, "", ""},


    // func
    {RVM_CODE_PUSH_FUNC, "push_func", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "", ""},
    {RVM_CODE_PUSH_METHOD, "push_method", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "", ""},
    {RVM_CODE_ARGUMENT_NUM, "argument_num", OPCODE_OPERAND_TYPE_1BYTE, 0, "", ""},
    {RVM_CODE_INVOKE_FUNC, "invoke_func", OPCODE_OPERAND_TYPE_0BYTE, -1, "", ""},
    {RVM_CODE_INVOKE_METHOD, "invoke_method", OPCODE_OPERAND_TYPE_0BYTE, -2, "", ""},
    {RVM_CODE_RETURN, "return", OPCODE_OPERAND_TYPE_2BYTE_As, 0, "", ""},
    {RVM_CODE_FUNCTION_FINISH, "function_finish", OPCODE_OPERAND_TYPE_0BYTE, 0, "", ""},

    {RVM_CODE_EXIT, "exit", OPCODE_OPERAND_TYPE_1BYTE, 0, "", ""},

    // new heap memory
    {RVM_CODE_NEW_ARRAY_BOOL, "new_array_bool", OPCODE_OPERAND_TYPE_1BYTE, 1, "", ""},
    {RVM_CODE_NEW_ARRAY_INT, "new_array_int", OPCODE_OPERAND_TYPE_1BYTE, 1, "", ""},
    {RVM_CODE_NEW_ARRAY_DOUBLE, "new_array_double", OPCODE_OPERAND_TYPE_1BYTE, 1, "", ""},
    {RVM_CODE_NEW_ARRAY_STRING, "new_array_string", OPCODE_OPERAND_TYPE_1BYTE, 1, "", ""},
    {RVM_CODE_NEW_ARRAY_CLASS_OBJECT, "new_array_class_object", OPCODE_OPERAND_TYPE_2BYTE_AB, 1, "", ""},
    {RVM_CODE_NEW_ARRAY_LITERAL_BOOL, "new_array_literal_bool", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "", ""},
    {RVM_CODE_NEW_ARRAY_LITERAL_INT, "new_array_literal_int", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "", ""},
    {RVM_CODE_NEW_ARRAY_LITERAL_DOUBLE, "new_array_literal_double", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "", ""},
    {RVM_CODE_NEW_ARRAY_LITERAL_STRING, "new_array_literal_string", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "", ""},
    {RVM_CODE_NEW_ARRAY_LITERAL_CLASS_OBJECT, "new_array_literal_class_object", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "", ""},
    {RVM_CODE_NEW_ARRAY_LITERAL_A, "new_array_literal_a", OPCODE_OPERAND_TYPE_3BYTE_ABs, 1, "", ""},

    {RVM_CODE_PUSH_ARRAY_LEN, "push_array_len", OPCODE_OPERAND_TYPE_0BYTE, 0, "", ""},
    {RVM_CODE_PUSH_ARRAY_CAPACITY, "push_array_capacity", OPCODE_OPERAND_TYPE_0BYTE, 0, "", ""},
    {RVM_CODE_PUSH_STRING_LEN, "push_string_len", OPCODE_OPERAND_TYPE_0BYTE, 0, "", ""},
    {RVM_CODE_PUSH_STRING_CAPACITY, "push_string_capacity", OPCODE_OPERAND_TYPE_0BYTE, 0, "", ""},

    // class
    {RVM_CODE_NEW_CLASS_OBJECT_LITERAL, "new_class_object_literal", OPCODE_OPERAND_TYPE_1BYTE, 1, "", ""},

    // range
    {RVM_CODE_FOR_RANGE_ARRAY_BOOL, "range_array_bool", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "range bool value for array", ""},
    {RVM_CODE_FOR_RANGE_ARRAY_INT, "range_array_int", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "range int value for array", ""},
    {RVM_CODE_FOR_RANGE_ARRAY_DOUBLE, "range_array_double", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "range double value for array", ""},
    {RVM_CODE_FOR_RANGE_ARRAY_STRING, "range_array_string", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "range string value for array", ""},
    {RVM_CODE_FOR_RANGE_ARRAY_CLASS_OBJECT, "range_array_class_object", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "range object value for array", ""},
    {RVM_CODE_FOR_RANGE_STRING, "range_string", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "range char value for string", ""},
    {RVM_CODE_FOR_RANGE_FINISH, "for_range_finish", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "", ""},

    // convert
    {RVM_CODE_BOOL_2_STRING, "bool_2_string", OPCODE_OPERAND_TYPE_0BYTE, 0, "convert bool to string", "[bool]->[string]"},
    {RVM_CODE_INT_2_STRING, "int_2_string", OPCODE_OPERAND_TYPE_0BYTE, 0, "convert int to string", "[int]->[string]"},
    {RVM_CODE_DOUBLE_2_STRING, "double_2_string", OPCODE_OPERAND_TYPE_0BYTE, 0, "convert double to string", "[double]->[string]"},


    {RVM_CODES_NUM, "", OPCODE_OPERAND_TYPE_0BYTE, 0, "", ""},
};

// TODO: 这里直接使用Cpp::string, 后续需要改成 Ring_String
std::string format_rvm_function(RVM_Function* function) {
    assert(function != nullptr);

    std::string result;

    // 1. funtion identifier
    result += std::string(function->func_name);
    result += "(";

    // 2. function parameters
    for (unsigned int i = 0; i < function->parameter_size; i++) {
        if (i != 0) {
            result += ", ";
        }
        result += format_rvm_type_specifier(function->parameter_list[i].type_specifier);
    }
    result += ")";

    // 3. function return values
    // TODO:


    return result;
}


// TODO: 这里直接使用Cpp::string, 后续需要改成 Ring_String
// TODO: 这里暂时 只能 formate 参数为 bool, int, double, string 其余的类型需要继续支持
std::string format_rvm_type_specifier(RVM_TypeSpecifier* type_specifier) {
    assert(type_specifier != nullptr);

    std::string str = "";

    switch (type_specifier->kind) {
    case RING_BASIC_TYPE_BOOL:
        str = "bool";
        break;
    case RING_BASIC_TYPE_INT:
        str = "int";
        break;
    case RING_BASIC_TYPE_DOUBLE:
        str = "double";
        break;
    case RING_BASIC_TYPE_STRING:
        str = "string";
        break;
    case RING_BASIC_TYPE_ARRAY:
        // TODO: 目前还不支持多维数组, 所以说这样写是没有问题的
        switch (type_specifier->sub->kind) {
        case RING_BASIC_TYPE_BOOL: str = "bool"; break;
        case RING_BASIC_TYPE_INT: str = "int"; break;
        case RING_BASIC_TYPE_DOUBLE: str = "double"; break;
        case RING_BASIC_TYPE_STRING: str = "string"; break;
        case RING_BASIC_TYPE_CLASS: str = "class"; break;
        default: str = "unknow"; break;
        }
        str = str + "[!" + std::to_string(type_specifier->dimension) + "]";
        break;
    case RING_BASIC_TYPE_CLASS:
        // TODO: 这里要获取类的真实名称
        str = "class";
        break;
    default:
        // TODO:  后续还要处理 数组
        str = ".unknow";
        break;
    }

    str = "var " + str;

    return str;
}