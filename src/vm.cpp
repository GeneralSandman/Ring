#include "ring.hpp"
#include <cassert>
#include <string>


std::string operand_desc =
    "- 0Byte: 无操作数\n\n"
    "- 1Byte_A: 1字节操作数A\n\n"
    "- 2Byte_As: 2字节操作数A\n\n"
    "- 2Byte_AB: 1字节操作数A和1字节操作数B\n\n"
    "- 3Byte_ABs: 1字节操作数A和2字节操作数B\n\n";

std::string math_formula_desc =
    "\n"
    "math_formula 字段是如何通过数学公式描述一个字节码所对应的 VirtualMachine 操作行为\n"
    "\n"
    "K(1)  通过index 1 , 来操作 static 空间\n"
    "Si(1) 通过 index 1 , 来操作 stack 空间\n"
    "So(1) 通过 offset 1 , 来操作 stack 空间\n"
    "Fi(1) 通过 index 1 , 来操作 free-value 空间\n"
    "C(1)  通过index 1, 从ConstantPool  Constant\n"
    "\n"
    "Field(object, As).int 将object的第As个Field作为int\n"
    "\n"
    "A As AB Bs 分别代表字节码后边的操作数\n"
    "FSB 代表 FunctionStackBase\n"
    "\n";

RVM_Opcode_Info RVM_Opcode_Infos[] = {
    {RVM_CODE_UNKNOW, "", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "", ""},


    // push int/int64/double/string const to stack
    {RVM_CODE_PUSH_BOOL, "push_bool", OPCODE_OPERAND_TYPE_1BYTE_A, 1, "push constant bool value to stack", "[]-->[int]", "So(0).bool = A.bool"},
    {RVM_CODE_PUSH_INT_1BYTE, "push_int_1byte", OPCODE_OPERAND_TYPE_1BYTE_A, 1, "push 1byte int constant value to stack", "[]-->[int]", "So(0).int = A.int"},
    {RVM_CODE_PUSH_INT_2BYTE, "push_int_2byte", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push 2byte int constant value to stack", "[]-->[int]", "So(0).int = As.int"},
    {RVM_CODE_PUSH_INT, "push_int", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push constant int value to stack", "[]-->[int]", "So(0).int = C(As).int"},
    {RVM_CODE_PUSH_INT64, "push_int64", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push constant int64 value to stack", "[]-->[int]", "So(0).int64 = C(As).int64"},
    {RVM_CODE_PUSH_DOUBLE, "push_double", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push constant double value to stack", "[]-->[double]", "So(0).double = C(As).double"},
    {RVM_CODE_PUSH_STRING, "push_string", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push constant string value to stack", "[]-->[string]", "So(0).string = C(As).string"},


    // static
    {RVM_CODE_POP_STATIC_BOOL, "pop_static_bool", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "bool assign to global-variable", "[bool]-->[]", "K(As) = So(-1).bool"},
    {RVM_CODE_POP_STATIC_INT, "pop_static_int", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "int assign to global-variable", "[int]-->[]", "K(As) = So(-1).int"},
    {RVM_CODE_POP_STATIC_INT64, "pop_static_int64", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "int64 assign to global-variable", "[int64]-->[]", "K(As) = So(-1).int64"},
    {RVM_CODE_POP_STATIC_DOUBLE, "pop_static_double", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "double assign to global-variable", "[double]-->[]", "K(As) = So(-1).double"},
    {RVM_CODE_POP_STATIC_STRING, "pop_static_string", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "string assign to global-variable", "[string]-->[]", "K(As) = So(-1).string"},
    {RVM_CODE_POP_STATIC_CLASS_OB, "pop_static_class_ob", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "class-object assign to global-variable", "[object]-->[]", "K(As) = So(-1).object"},
    {RVM_CODE_POP_STATIC_ARRAY, "pop_static_array", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "array assign to global-variable", "[array]-->[]", "K(As) = So(-1).array"},

    {RVM_CODE_PUSH_STATIC_BOOL, "push_static_bool", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push global-variable's bool to stack", "[]-->[bool]", "So(0).bool = K(As)"},
    {RVM_CODE_PUSH_STATIC_INT, "push_static_int", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push global-variable's int to stack", "[]-->[int]", "So(0).int = K(As)"},
    {RVM_CODE_PUSH_STATIC_INT64, "push_static_int64", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push global-variable's int64 to stack", "[]-->[int64]", "So(0).int64 = K(As)"},
    {RVM_CODE_PUSH_STATIC_DOUBLE, "push_static_double", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push global-variable's double to stack", "[]-->[double]", "So(0).double = K(As)"},
    {RVM_CODE_PUSH_STATIC_STRING, "push_static_string", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push global-variable's string to stack", "[]-->[string]", "So(0).string = K(As)"},
    {RVM_CODE_PUSH_STATIC_CLASS_OB, "push_static_class_ob", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push global-variable's class-object to stack", "[]-->[object]", "So(0).object = K(As)"},
    {RVM_CODE_PUSH_STATIC_ARRAY, "push_static_array", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push global-variable's array to stack", "[]-->[array]", "So(0).array = K(As)"},


    // stack
    {RVM_CODE_POP_STACK_BOOL, "pop_stack_bool", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "bool assign to local-variable", "", "Si(FSB+As).bool = S(-1).bool"},
    {RVM_CODE_POP_STACK_INT, "pop_stack_int", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "int assign to local-variable", "", "Si(FSB+As).int = S(-1).int"},
    {RVM_CODE_POP_STACK_INT64, "pop_stack_int64", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "int64 assign to local-variable", "", "Si(FSB+As).int64 = S(-1).int64"},
    {RVM_CODE_POP_STACK_DOUBLE, "pop_stack_double", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "double assign to local-variable", "", "Si(FSB+As).double = S(-1).double"},
    {RVM_CODE_POP_STACK_STRING, "pop_stack_string", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "string assign to local-variable", "", "Si(FSB+As).string = S(-1).string"},
    {RVM_CODE_POP_STACK_CLASS_OB, "pop_stack_class_ob", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "class-object assign to local-variable", "", "Si(FSB+As).object = S(-1).object"},
    {RVM_CODE_POP_STACK_ARRAY, "pop_stack_array", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "array assign to local-variable", "", "Si(FSB+As).array = S(-1).array"},
    {RVM_CODE_POP_STACK_CLOSURE, "pop_stack_closure", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "closure assign to local-variable", "", "Si(FSB+As).func = S(-1).func"},

    {RVM_CODE_PUSH_STACK_BOOL, "push_stack_bool", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push local-variable's bool to stack", "", "So(0).bool = Si(FSB+As).bool"},
    {RVM_CODE_PUSH_STACK_INT, "push_stack_int", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push local-variable's int to stack", "", "So(0).int = Si(FSB+As).int"},
    {RVM_CODE_PUSH_STACK_INT64, "push_stack_int64", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push local-variable's int64 to stack", "", "So(0).int64 = Si(FSB+As).int64"},
    {RVM_CODE_PUSH_STACK_DOUBLE, "push_stack_double", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push local-variable's double to stack", "", "So(0).double = Si(FSB+As).double"},
    {RVM_CODE_PUSH_STACK_STRING, "push_stack_string", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push local-variable's string to stack", "", "So(0).string = Si(FSB+As).string"},
    {RVM_CODE_PUSH_STACK_CLASS_OB, "push_stack_class_ob", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push local-variable's class-object to stack", "", "So(0).object = Si(FSB+As).object"},
    {RVM_CODE_PUSH_STACK_ARRAY, "push_stack_array", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push local-variable's array to stack", "", "So(0).array = Si(FSB+As).array"},
    {RVM_CODE_PUSH_STACK_CLOSURE, "push_stack_closure", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push local-variable's closure to stack", "", "So(0).closure = Si(FSB+As).closure"},

    // free value
    {RVM_CODE_POP_FREE_BOOL, "pop_free_bool", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "bool assign to local-variable", "", "Fi(FSB+As).bool = S(-1).bool"},
    {RVM_CODE_POP_FREE_INT, "pop_free_int", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "int assign to local-variable", "", "Fi(FSB+As).int = S(-1).int"},
    {RVM_CODE_POP_FREE_INT64, "pop_free_int64", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "int64 assign to local-variable", "", "Fi(FSB+As).int64 = S(-1).int64"},
    {RVM_CODE_POP_FREE_DOUBLE, "pop_free_double", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "double assign to local-variable", "", "Fi(FSB+As).double = S(-1).double"},
    {RVM_CODE_POP_FREE_STRING, "pop_free_string", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "string assign to local-variable", "", "Fi(FSB+As).string = S(-1).string"},


    {RVM_CODE_PUSH_FREE_BOOL, "push_free_bool", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push local-variable's bool to stack", "", "So(0).bool = Fi(FSB+As).bool"},
    {RVM_CODE_PUSH_FREE_INT, "push_free_int", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push local-variable's int to stack", "", "So(0).int = Fi(FSB+As).int"},
    {RVM_CODE_PUSH_FREE_INT64, "push_free_int64", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push local-variable's int64 to stack", "", "So(0).int64 = Fi(FSB+As).int64"},
    {RVM_CODE_PUSH_FREE_DOUBLE, "push_free_double", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push local-variable's double to stack", "", "So(0).double = Fi(FSB+As).double"},
    {RVM_CODE_PUSH_FREE_STRING, "push_free_string", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "push local-variable's string to stack", "", "So(0).string = Fi(FSB+As).string"},


    // array
    {RVM_CODE_PUSH_ARRAY_A, "push_array_a", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "", ""},
    {RVM_CODE_PUSH_ARRAY_BOOL, "push_array_bool", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "", ""},
    {RVM_CODE_PUSH_ARRAY_INT, "push_array_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "", ""},
    {RVM_CODE_PUSH_ARRAY_INT64, "push_array_int64", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "", ""},
    {RVM_CODE_PUSH_ARRAY_DOUBLE, "push_array_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "", ""},
    {RVM_CODE_PUSH_ARRAY_STRING, "push_array_string", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "", ""},
    {RVM_CODE_PUSH_ARRAY_CLASS_OB, "push_array_class_ob", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "", ""},

    {RVM_CODE_POP_ARRAY_A, "pop_array_a", OPCODE_OPERAND_TYPE_0BYTE, -3, "", "", ""},
    {RVM_CODE_POP_ARRAY_BOOL, "pop_array_bool", OPCODE_OPERAND_TYPE_0BYTE, -3, "assign to bool array by index", "[int,object,int]->[]", ""},
    {RVM_CODE_POP_ARRAY_INT, "pop_array_int", OPCODE_OPERAND_TYPE_0BYTE, -3, "assign to int array by index", "[int,object,int]->[]", ""},
    {RVM_CODE_POP_ARRAY_INT64, "pop_array_int64", OPCODE_OPERAND_TYPE_0BYTE, -3, "assign to int64 array by index", "[int,object,int]->[]", ""},
    {RVM_CODE_POP_ARRAY_DOUBLE, "pop_array_double", OPCODE_OPERAND_TYPE_0BYTE, -3, "assign to double array by index", "[int,object,int]->[]", ""},
    {RVM_CODE_POP_ARRAY_STRING, "pop_array_string", OPCODE_OPERAND_TYPE_0BYTE, -3, "assign to string array by index", "[int,object,int]->[]", ""},
    {RVM_CODE_POP_ARRAY_CLASS_OB, "pop_array_class_ob", OPCODE_OPERAND_TYPE_0BYTE, -3, "assign to object array by index", "[int,object,int]->[]", ""},


    // array append
    {RVM_CODE_ARRAY_APPEND_BOOL, "array_append_bool", OPCODE_OPERAND_TYPE_0BYTE, -2, "assign to object array by index", "[object,bool]->[]", ""},
    {RVM_CODE_ARRAY_APPEND_INT, "array_append_int", OPCODE_OPERAND_TYPE_0BYTE, -2, "assign to object array by index", "[object,int]->[]", ""},
    {RVM_CODE_ARRAY_APPEND_INT64, "array_append_int64", OPCODE_OPERAND_TYPE_0BYTE, -2, "assign to object array by index", "[object,int64]->[]", ""},
    {RVM_CODE_ARRAY_APPEND_DOUBLE, "array_append_double", OPCODE_OPERAND_TYPE_0BYTE, -2, "assign to object array by index", "[object,double]->[]", ""},
    {RVM_CODE_ARRAY_APPEND_STRING, "array_append_string", OPCODE_OPERAND_TYPE_0BYTE, -2, "assign to object array by index", "[object,string]->[]", ""},
    {RVM_CODE_ARRAY_APPEND_CLASS_OB, "array_append_class_ob", OPCODE_OPERAND_TYPE_0BYTE, -2, "assign to object array by index", "[object,object]->[]", ""},
    // array pop
    {RVM_CODE_ARRAY_POP_BOOL, "array_pop_bool", OPCODE_OPERAND_TYPE_0BYTE, 0, "assign to object array by index", "[object]->[bool]", ""},
    {RVM_CODE_ARRAY_POP_INT, "array_pop_int", OPCODE_OPERAND_TYPE_0BYTE, 0, "assign to object array by index", "[object]->[int]", ""},
    {RVM_CODE_ARRAY_POP_INT64, "array_pop_int64", OPCODE_OPERAND_TYPE_0BYTE, 0, "assign to object array by index", "[object]->[int64]", ""},
    {RVM_CODE_ARRAY_POP_DOUBLE, "array_pop_double", OPCODE_OPERAND_TYPE_0BYTE, 0, "assign to object array by index", "[object]->[double]", ""},
    {RVM_CODE_ARRAY_POP_STRING, "array_pop_string", OPCODE_OPERAND_TYPE_0BYTE, 0, "assign to object array by index", "[object]->[string]", ""},
    {RVM_CODE_ARRAY_POP_CLASS_OB, "array_pop_class_ob", OPCODE_OPERAND_TYPE_0BYTE, 0, "assign to object array by index", "[object]->[object]", ""},


    // class
    {RVM_CODE_POP_FIELD_BOOL, "pop_field_bool", OPCODE_OPERAND_TYPE_2BYTE_As, -2, "assign to class field whith bool", "[bool,object]->[]", "Field(So(-1).object, As).bool = So(-2).bool"},
    {RVM_CODE_POP_FIELD_INT, "pop_field_int", OPCODE_OPERAND_TYPE_2BYTE_As, -2, "", "[int,object]->[]", "Field(So(-1).object, As).int = So(-2).int"},
    {RVM_CODE_POP_FIELD_INT64, "pop_field_int64", OPCODE_OPERAND_TYPE_2BYTE_As, -2, "", "[int64,object]->[]", "Field(So(-1).object, As).int64 = So(-2).int64"},
    {RVM_CODE_POP_FIELD_DOUBLE, "pop_field_double", OPCODE_OPERAND_TYPE_2BYTE_As, -2, "", "[double,object]->[]", "Field(So(-1).object, As).double = So(-2).double"},
    {RVM_CODE_POP_FIELD_STRING, "pop_field_string", OPCODE_OPERAND_TYPE_2BYTE_As, -2, "", "[string,object]->[]", "Field(So(-1).object, As).string = So(-2).string"},
    {RVM_CODE_POP_FIELD_CLASS_OB, "pop_field_class_ob", OPCODE_OPERAND_TYPE_2BYTE_As, -2, "", "[object,object]->[]", "Field(So(-1).object, As).object = So(-2).object"},
    {RVM_CODE_POP_FIELD_ARRAY, "pop_field_array", OPCODE_OPERAND_TYPE_2BYTE_As, -2, "", "[array,object]->[]", "Field(So(-1).object, As).array = So(-2).array"},

    {RVM_CODE_PUSH_FIELD_BOOL, "push_field_bool", OPCODE_OPERAND_TYPE_2BYTE_As, 0, "", "[object]->[bool]", "S(-1).bool = Field(So(-1).object, As).bool"},
    {RVM_CODE_PUSH_FIELD_INT, "push_field_int", OPCODE_OPERAND_TYPE_2BYTE_As, 0, "", "[object]->[int]", "S(-1).int = Field(So(-1).object, As).int"},
    {RVM_CODE_PUSH_FIELD_INT64, "push_field_int64", OPCODE_OPERAND_TYPE_2BYTE_As, 0, "", "[object]->[int64]", "S(-1).int64 = Field(So(-1).object, As).int64"},
    {RVM_CODE_PUSH_FIELD_DOUBLE, "push_field_double", OPCODE_OPERAND_TYPE_2BYTE_As, 0, "", "[object]->[double]", "S(-1).double = Field(So(-1).object, As).double"},
    {RVM_CODE_PUSH_FIELD_STRING, "push_field_string", OPCODE_OPERAND_TYPE_2BYTE_As, 0, "", "[object]->[string]", "S(-1).string = Field(So(-1).object, As).string"},
    {RVM_CODE_PUSH_FIELD_CLASS_OB, "push_field_class_ob", OPCODE_OPERAND_TYPE_2BYTE_As, 0, "", "[object]->[object]", "S(-1).object = Field(So(-1).object, As).object"},
    {RVM_CODE_PUSH_FIELD_ARRAY, "push_field_array", OPCODE_OPERAND_TYPE_2BYTE_As, 0, "", "[object]->[array]", "S(-1).array = Field(So(-1).object, As).array"},


    // arithmetic
    {RVM_CODE_ADD_INT, "add_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int,int]->[int]", ""},
    {RVM_CODE_ADD_INT64, "add_int64", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int64,int64]->[int64]", ""},
    {RVM_CODE_ADD_DOUBLE, "add_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[double,double]->[double]", ""},

    {RVM_CODE_SUB_INT, "sub_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int,int]->[int]", ""},
    {RVM_CODE_SUB_INT64, "sub_int64", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int64,int64]->[int64]", ""},
    {RVM_CODE_SUB_DOUBLE, "sub_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[double,double]->[double]", ""},

    {RVM_CODE_MUL_INT, "mul_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int,int]->[int]", ""},
    {RVM_CODE_MUL_INT64, "mul_int64", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int64,int64]->[int64]", ""},
    {RVM_CODE_MUL_DOUBLE, "mul_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[double,double]->[double]", ""},

    {RVM_CODE_DIV_INT, "div_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int,int]->[int]", ""},
    {RVM_CODE_DIV_INT64, "div_int64", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int64,int64]->[int64]", ""},
    {RVM_CODE_DIV_DOUBLE, "div_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[double,double]->[double]", ""},

    {RVM_CODE_MOD_INT, "mod_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int,int]->[int]", ""},
    {RVM_CODE_MOD_INT64, "mod_int64", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int64,int64]->[int64]", ""},
    {RVM_CODE_MOD_DOUBLE, "mod_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[double,double]->[double]", ""},

    {RVM_CODE_MINUS_INT, "minus_int", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "[int,int]->[int]", ""},
    {RVM_CODE_MINUS_INT64, "minus_int64", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "[int64,int64]->[int64]", ""},
    {RVM_CODE_MINUS_DOUBLE, "minus_double", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "[double,double]->[double]", ""},

    {RVM_CODE_SELF_INCREASE_INT, "self_increase_int", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "", ""},
    {RVM_CODE_SELF_INCREASE_INT64, "self_increase_int64", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "", ""},
    {RVM_CODE_SELF_INCREASE_DOUBLE, "self_increase_double", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "", ""},
    {RVM_CODE_SELF_DECREASE_INT, "self_decrease_int", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "", ""},
    {RVM_CODE_SELF_DECREASE_INT64, "self_decrease_int64", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "", ""},
    {RVM_CODE_SELF_DECREASE_DOUBLE, "self_decrease_double", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "", ""},

    {RVM_CODE_CONCAT, "concat", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "", ""},


    // type cast
    {RVM_CODE_CAST_BOOL_TO_INT, "cast_bool_to_int", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "", ""},
    {RVM_CODE_CAST_INT_TO_DOUBLE, "cast_int_to_double", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "", ""},

    {RVM_CODE_CAST_INT_TO_BOOL, "cast_int_to_bool", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "", ""},
    {RVM_CODE_CAST_DOUBLE_TO_INT, "cast_double_to_int", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "", ""},


    // logical
    {RVM_CODE_LOGICAL_AND, "logical_and", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[bool,bool]->[bool]", ""},
    {RVM_CODE_LOGICAL_OR, "logical_or", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[bool,bool]->[bool]", ""},
    {RVM_CODE_LOGICAL_NOT, "logical_not", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "[bool,bool]->[bool]", ""},


    // relational
    {RVM_CODE_RELATIONAL_EQ_INT, "eq_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int,int]->[bool]", ""},
    {RVM_CODE_RELATIONAL_EQ_INT64, "eq_int64", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int64,int64]->[bool]", ""},
    {RVM_CODE_RELATIONAL_EQ_DOUBLE, "eq_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[double,double]->[bool]", ""},
    {RVM_CODE_RELATIONAL_EQ_STRING, "eq_string", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[string,string]->[bool]", ""},

    {RVM_CODE_RELATIONAL_NE_INT, "ne_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int,int]->[bool]", ""},
    {RVM_CODE_RELATIONAL_NE_INT64, "ne_int64", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int64,int64]->[bool]", ""},
    {RVM_CODE_RELATIONAL_NE_DOUBLE, "ne_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[double,double]->[bool]", ""},
    {RVM_CODE_RELATIONAL_NE_STRING, "ne_string", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[string,string]->[bool]", ""},

    {RVM_CODE_RELATIONAL_GT_INT, "gt_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int,int]->[bool]", ""},
    {RVM_CODE_RELATIONAL_GT_INT64, "gt_int64", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int64,int64]->[bool]", ""},
    {RVM_CODE_RELATIONAL_GT_DOUBLE, "gt_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[double,double]->[bool]", ""},
    {RVM_CODE_RELATIONAL_GT_STRING, "gt_string", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[string,string]->[bool]", ""},

    {RVM_CODE_RELATIONAL_GE_INT, "ge_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int,int]->[bool]", ""},
    {RVM_CODE_RELATIONAL_GE_INT64, "ge_int64", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int64,int64]->[bool]", ""},
    {RVM_CODE_RELATIONAL_GE_DOUBLE, "ge_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[double,double]->[bool]", ""},
    {RVM_CODE_RELATIONAL_GE_STRING, "ge_string", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[string,string]->[bool]", ""},

    {RVM_CODE_RELATIONAL_LT_INT, "lt_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int,int]->[bool]", ""},
    {RVM_CODE_RELATIONAL_LT_INT64, "lt_int64", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int64,int64]->[bool]", ""},
    {RVM_CODE_RELATIONAL_LT_DOUBLE, "lt_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[double,double]->[bool]", ""},
    {RVM_CODE_RELATIONAL_LT_STRING, "lt_string", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[string,string]->[bool]", ""},

    {RVM_CODE_RELATIONAL_LE_INT, "le_int", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int,int]->[bool]", ""},
    {RVM_CODE_RELATIONAL_LE_INT64, "le_int64", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[int64,int64]->[bool]", ""},
    {RVM_CODE_RELATIONAL_LE_DOUBLE, "le_double", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[double,double]->[bool]", ""},
    {RVM_CODE_RELATIONAL_LE_STRING, "le_string", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "[string,string]->[bool]", ""},


    // jump
    {RVM_CODE_JUMP, "jump", OPCODE_OPERAND_TYPE_2BYTE_As, 0, "", "", ""},
    {RVM_CODE_JUMP_IF_FALSE, "jump_if_false", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "", "", ""},
    {RVM_CODE_JUMP_IF_TRUE, "jump_if_true", OPCODE_OPERAND_TYPE_2BYTE_As, -1, "", "", ""},


    // duplicate
    {RVM_CODE_SHALLOW_COPY, "duplicate", OPCODE_OPERAND_TYPE_2BYTE_AB, 1, "", "shallow copy value from B to A.", ""},
    {RVM_CODE_DEEP_COPY, "deep_copy", OPCODE_OPERAND_TYPE_2BYTE_AB, 1, "", "deep copy value from B to A.", ""},


    // func
    {RVM_CODE_ARGUMENT_NUM, "argument_num", OPCODE_OPERAND_TYPE_1BYTE_A, 1, "", "", ""},
    {RVM_CODE_PUSH_FUNC, "push_func", OPCODE_OPERAND_TYPE_2BYTE_AB, 1, "", "", ""},
    {RVM_CODE_PUSH_METHOD, "push_method", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "", "", ""},
    {RVM_CODE_INVOKE_CLOSURE, "invoke_closure", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "", ""},
    {RVM_CODE_INVOKE_FUNC_NATIVE, "invoke_func_native", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "", ""},
    {RVM_CODE_INVOKE_FUNC, "invoke_func", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "", ""},
    {RVM_CODE_INVOKE_METHOD, "invoke_method", OPCODE_OPERAND_TYPE_0BYTE, -2, "", "", ""},
    {RVM_CODE_RETURN, "return", OPCODE_OPERAND_TYPE_2BYTE_As, 0, "", "", ""},
    {RVM_CODE_FUNCTION_FINISH, "function_finish", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "", ""},

    // defer
    {RVM_CODE_PUSH_DEFER, "push_defer", OPCODE_OPERAND_TYPE_0BYTE, -1, "-", "-", "-"},
    {RVM_CODE_POP_DEFER, "pop_defer", OPCODE_OPERAND_TYPE_0BYTE, -1, "-", "-", "-"},

    {RVM_CODE_EXIT, "exit", OPCODE_OPERAND_TYPE_0BYTE, -1, "", "", ""},


    // array
    {RVM_CODE_NEW_ARRAY_BOOL, "new_array_bool", OPCODE_OPERAND_TYPE_1BYTE_A, 1, "create an array of bool with dimension", "", ""},
    {RVM_CODE_NEW_ARRAY_INT, "new_array_int", OPCODE_OPERAND_TYPE_1BYTE_A, 1, "create an array of int with dimension", "", ""},
    {RVM_CODE_NEW_ARRAY_INT64, "new_array_int64", OPCODE_OPERAND_TYPE_1BYTE_A, 1, "create an array of int64 with dimension", "", ""},
    {RVM_CODE_NEW_ARRAY_DOUBLE, "new_array_double", OPCODE_OPERAND_TYPE_1BYTE_A, 1, "create an array of double with dimension", "", ""},
    {RVM_CODE_NEW_ARRAY_STRING, "new_array_string", OPCODE_OPERAND_TYPE_1BYTE_A, 1, "create an array of string with dimension", "", ""},
    {RVM_CODE_NEW_ARRAY_CLASS_OB, "new_array_class_ob", OPCODE_OPERAND_TYPE_2BYTE_AB, 1, "create an array of object with dimension", "", ""},

    {RVM_CODE_NEW_ARRAY_LITERAL_BOOL, "new_array_literal_bool", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "create an array of bool with literal", "", ""},
    {RVM_CODE_NEW_ARRAY_LITERAL_INT, "new_array_literal_int", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "create an array of int with literal", "", ""},
    {RVM_CODE_NEW_ARRAY_LITERAL_INT64, "new_array_literal_int64", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "create an array of int64 with literal", "", ""},
    {RVM_CODE_NEW_ARRAY_LITERAL_DOUBLE, "new_array_literal_double", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "create an array of double with literal", "", ""},
    {RVM_CODE_NEW_ARRAY_LITERAL_STRING, "new_array_literal_string", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "create an array of string with literal", "", ""},
    {RVM_CODE_NEW_ARRAY_LITERAL_CLASS_OB, "new_array_literal_class_ob", OPCODE_OPERAND_TYPE_3BYTE_ABs, 1, "create an array of object with literal", "", ""},

    {RVM_CODE_NEW_ARRAY_LITERAL_A, "new_array_literal_a", OPCODE_OPERAND_TYPE_3BYTE_ABs, 1, "", "", ""},

    {RVM_CODE_PUSH_ARRAY_LEN, "push_array_len", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "", ""},
    {RVM_CODE_PUSH_ARRAY_CAPACITY, "push_array_capacity", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "", ""},
    {RVM_CODE_PUSH_STRING_LEN, "push_string_len", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "", ""},
    {RVM_CODE_PUSH_STRING_CAPACITY, "push_string_capacity", OPCODE_OPERAND_TYPE_0BYTE, 0, "", "", ""},


    // class
    {RVM_CODE_NEW_CLASS_OB_LITERAL, "new_class_ob_literal", OPCODE_OPERAND_TYPE_1BYTE_A, 1, "", "", ""},


    // range
    {RVM_CODE_FOR_RANGE_ARRAY_A, "range_array_a", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "range array value for array", "", ""},
    {RVM_CODE_FOR_RANGE_ARRAY_BOOL, "range_array_bool", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "range bool value for array", "", ""},
    {RVM_CODE_FOR_RANGE_ARRAY_INT, "range_array_int", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "range int value for array", "", ""},
    {RVM_CODE_FOR_RANGE_ARRAY_INT64, "range_array_int64", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "range int64 value for array", "", ""},
    {RVM_CODE_FOR_RANGE_ARRAY_DOUBLE, "range_array_double", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "range double value for array", "", ""},
    {RVM_CODE_FOR_RANGE_ARRAY_STRING, "range_array_string", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "range string value for array", "", ""},
    {RVM_CODE_FOR_RANGE_ARRAY_CLASS_OB, "range_array_class_ob", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "range object value for array", "", ""},
    {RVM_CODE_FOR_RANGE_STRING, "range_string", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "range char value for string", "", ""},
    {RVM_CODE_FOR_RANGE_FINISH, "for_range_finish", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "", "", ""},

    // convert
    {RVM_CODE_BOOL_2_STRING, "bool_2_string", OPCODE_OPERAND_TYPE_0BYTE, 0, "convert bool to string", "[bool]->[string]", "So(-1).string = So(-1).bool"},
    {RVM_CODE_INT_2_STRING, "int_2_string", OPCODE_OPERAND_TYPE_0BYTE, 0, "convert int to string", "[int]->[string]", "So(-1).string = So(-1).int"},
    {RVM_CODE_INT64_2_STRING, "int64_2_string", OPCODE_OPERAND_TYPE_0BYTE, 0, "convert int64 to string", "[int]->[string]", "So(-1).string = So(-1).int64"},
    {RVM_CODE_DOUBLE_2_STRING, "double_2_string", OPCODE_OPERAND_TYPE_0BYTE, 0, "convert double to string", "[double]->[string]", "So(-1).string = So(-1).double"},
    {RVM_CODE_INT_2_INT64, "int_2_int64", OPCODE_OPERAND_TYPE_0BYTE, 0, "convert int to int64", "[int]->[int64]", "So(-1).int64 = So(-1).int"},


    // coroutine
    {RVM_CODE_LAUNCH, "launch", OPCODE_OPERAND_TYPE_0BYTE, 0, "usage_comment", "stack_top_change", "math_formula"},
    {RVM_CODE_LAUNCH_CLOSURE, "launch_closure", OPCODE_OPERAND_TYPE_0BYTE, 0, "usage_comment", "stack_top_change", "math_formula"},
    {RVM_CODE_LAUNCH_METHOD, "launch_method", OPCODE_OPERAND_TYPE_0BYTE, 0, "usage_comment", "stack_top_change", "math_formula"},
    {RVM_CODE_RESUME, "resume", OPCODE_OPERAND_TYPE_0BYTE, 0, "usage_comment", "stack_top_change", "math_formula"},
    {RVM_CODE_YIELD, "yield", OPCODE_OPERAND_TYPE_0BYTE, 0, "usage_comment", "stack_top_change", "math_formula"},

    // closure
    {RVM_CODE_NEW_CLOSURE, "new_closure", OPCODE_OPERAND_TYPE_2BYTE_As, 1, "instantiated a closure by anonymous function", "stack_top_change", "math_formula"},


    {RVM_CODES_NUM, "num", OPCODE_OPERAND_TYPE_0BYTE, 0, "usage_comment", "stack_top_change", "math_formula"},
};
