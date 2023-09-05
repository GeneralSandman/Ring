#include "ring.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

RVM_Opcode_Info RVM_Opcode_Infos[] = {
    {RVM_CODE_UNKNOW, "", OPCODE_OPERAND_TYPE_UNKNOW, 0, 0},


    // init double string const
    {RVM_CODE_PUSH_BOOL, "push_bool", OPCODE_OPERAND_TYPE_1BYTE, 1, 2},
    {RVM_CODE_PUSH_INT_1BYTE, "push_int_1byte", OPCODE_OPERAND_TYPE_1BYTE, 1, 2}, // 后边紧跟 int 常量 1 type
    {RVM_CODE_PUSH_INT_2BYTE, "push_int_2byte", OPCODE_OPERAND_TYPE_2BYTE, 1, 3}, // 后边紧跟 int 常量 2 type
    {RVM_CODE_PUSH_INT, "push_int", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},             // 后边紧跟 int 常量 2 的索引 这里的还要 改一下 OPCODE_OPERAND_TYPE_2BYTE
    {RVM_CODE_PUSH_DOUBLE, "push_double", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},       // 后边紧跟 double 常量
    {RVM_CODE_PUSH_STRING, "push_string", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},       // 后边紧跟 string 常量


    // static
    {RVM_CODE_POP_STATIC_BOOL, "pop_static_bool", OPCODE_OPERAND_TYPE_2BYTE, -1, 3},
    {RVM_CODE_POP_STATIC_INT, "pop_static_int", OPCODE_OPERAND_TYPE_2BYTE, -1, 3},
    {RVM_CODE_POP_STATIC_DOUBLE, "pop_static_double", OPCODE_OPERAND_TYPE_2BYTE, -1, 3},
    {RVM_CODE_POP_STATIC_OBJECT, "pop_static_object", OPCODE_OPERAND_TYPE_2BYTE, -1, 3},
    {RVM_CODE_PUSH_STATIC_BOOL, "push_static_bool", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},
    {RVM_CODE_PUSH_STATIC_INT, "push_static_int", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},
    {RVM_CODE_PUSH_STATIC_DOUBLE, "push_static_double", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},
    {RVM_CODE_PUSH_STATIC_OBJECT, "push_static_object", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},


    // stack
    {RVM_CODE_POP_STACK_BOOL, "pop_stack_bool", OPCODE_OPERAND_TYPE_2BYTE, -1, 3},
    {RVM_CODE_POP_STACK_INT, "pop_stack_int", OPCODE_OPERAND_TYPE_2BYTE, -1, 3},
    {RVM_CODE_POP_STACK_DOUBLE, "pop_stack_double", OPCODE_OPERAND_TYPE_2BYTE, -1, 3},
    {RVM_CODE_POP_STACK_OBJECT, "pop_stack_object", OPCODE_OPERAND_TYPE_2BYTE, -1, 3},
    {RVM_CODE_PUSH_STACK_BOOL, "push_stack_bool", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},
    {RVM_CODE_PUSH_STACK_INT, "push_stack_int", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},
    {RVM_CODE_PUSH_STACK_DOUBLE, "push_stack_double", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},
    {RVM_CODE_PUSH_STACK_OBJECT, "push_stack_object", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},


    // array
    {RVM_CODE_PUSH_ARRAY_INT, "push_array_int", OPCODE_OPERAND_TYPE_0BYTE, 0, 1},
    {RVM_CODE_PUSH_ARRAY_DOUBLE, "push_array_double", OPCODE_OPERAND_TYPE_0BYTE, 0, 1},
    {RVM_CODE_PUSH_ARRAY_OBJECT, "push_array_object", OPCODE_OPERAND_TYPE_0BYTE, 0, 1},


    // class
    {RVM_CODE_POP_FIELD_BOOL, "pop_field_bool", OPCODE_OPERAND_TYPE_2BYTE, -1, 3},
    {RVM_CODE_POP_FIELD_INT, "pop_field_int", OPCODE_OPERAND_TYPE_2BYTE, -1, 3},
    {RVM_CODE_POP_FIELD_DOUBLE, "pop_field_double", OPCODE_OPERAND_TYPE_2BYTE, -1, 3},
    {RVM_CODE_PUSH_FIELD_BOOL, "push_field_bool", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},
    {RVM_CODE_PUSH_FIELD_INT, "push_field_int", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},
    {RVM_CODE_PUSH_FIELD_DOUBLE, "push_field_double", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},


    // arithmetic
    {RVM_CODE_ADD_INT, "add_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},
    {RVM_CODE_ADD_DOUBLE, "add_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},

    {RVM_CODE_SUB_INT, "sub_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},
    {RVM_CODE_SUB_DOUBLE, "sub_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},

    {RVM_CODE_MUL_INT, "mul_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},
    {RVM_CODE_MUL_DOUBLE, "mul_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},

    {RVM_CODE_DIV_INT, "div_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},
    {RVM_CODE_DIV_DOUBLE, "div_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},

    {RVM_CODE_MOD_INT, "mod_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},
    {RVM_CODE_MOD_DOUBLE, "mod_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},

    {RVM_CODE_MINUS_INT, "minus_int", OPCODE_OPERAND_TYPE_0BYTE, 0, 1},
    {RVM_CODE_MINUS_DOUBLE, "minus_double", OPCODE_OPERAND_TYPE_0BYTE, 0, 1},

    {RVM_CODE_INCREASE_SUFFIX, "increase_suffix", OPCODE_OPERAND_TYPE_0BYTE, 0, 1},
    {RVM_CODE_INCREASE_PREFIX, "increase_prefix", OPCODE_OPERAND_TYPE_0BYTE, 0, 1},
    {RVM_CODE_DECREASE_SUFFIX, "decrease_suffix", OPCODE_OPERAND_TYPE_0BYTE, 0, 1},
    {RVM_CODE_DECREASE_PREFIX, "decrease_prefix", OPCODE_OPERAND_TYPE_0BYTE, 0, 1},

    {RVM_CODE_CONCAT, "concat", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},

    // type cast
    {RVM_CODE_CAST_BOOL_TO_INT, "cast_bool_to_int", OPCODE_OPERAND_TYPE_0BYTE, 0, 1},
    {RVM_CODE_CAST_INT_TO_DOUBLE, "cast_int_to_double", OPCODE_OPERAND_TYPE_0BYTE, 0, 1},

    {RVM_CODE_CAST_INT_TO_BOOL, "cast_int_to_bool", OPCODE_OPERAND_TYPE_0BYTE, 0, 1},
    {RVM_CODE_CAST_DOUBLE_TO_INT, "cast_double_to_int", OPCODE_OPERAND_TYPE_0BYTE, 0, 1},


    // logical
    {RVM_CODE_LOGICAL_AND, "logical_and", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},
    {RVM_CODE_LOGICAL_OR, "logical_or", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},
    {RVM_CODE_LOGICAL_NOT, "logical_not", OPCODE_OPERAND_TYPE_0BYTE, 0, 1},

    // relational
    {RVM_CODE_RELATIONAL_EQ_INT, "eq_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},
    {RVM_CODE_RELATIONAL_EQ_DOUBLE, "eq_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},
    {RVM_CODE_RELATIONAL_EQ_STRING, "eq_string", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},

    {RVM_CODE_RELATIONAL_NE_INT, "ne_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},
    {RVM_CODE_RELATIONAL_NE_DOUBLE, "ne_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},
    {RVM_CODE_RELATIONAL_NE_STRING, "ne_string", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},

    {RVM_CODE_RELATIONAL_GT_INT, "gt_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},
    {RVM_CODE_RELATIONAL_GT_DOUBLE, "gt_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},
    {RVM_CODE_RELATIONAL_GT_STRING, "gt_string", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},

    {RVM_CODE_RELATIONAL_GE_INT, "ge_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},
    {RVM_CODE_RELATIONAL_GE_DOUBLE, "ge_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},
    {RVM_CODE_RELATIONAL_GE_STRING, "ge_string", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},

    {RVM_CODE_RELATIONAL_LT_INT, "lt_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},
    {RVM_CODE_RELATIONAL_LT_DOUBLE, "lt_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},
    {RVM_CODE_RELATIONAL_LT_STRING, "lt_string", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},

    {RVM_CODE_RELATIONAL_LE_INT, "le_int", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},
    {RVM_CODE_RELATIONAL_LE_DOUBLE, "le_double", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},
    {RVM_CODE_RELATIONAL_LE_STRING, "le_string", OPCODE_OPERAND_TYPE_0BYTE, -1, 1},

    // jump
    {RVM_CODE_JUMP, "jump", OPCODE_OPERAND_TYPE_2BYTE, 0, 0},
    {RVM_CODE_JUMP_IF_FALSE, "jump_if_false", OPCODE_OPERAND_TYPE_2BYTE, -1, 0},
    {RVM_CODE_JUMP_IF_TRUE, "jump_if_true", OPCODE_OPERAND_TYPE_2BYTE, -1, 0},

    // duplicate
    {RVM_CODE_DUPLICATE, "duplicate", OPCODE_OPERAND_TYPE_0BYTE, 1, 1},


    // func
    {RVM_CODE_PUSH_FUNC, "push_func", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},     // TODO: update to 2 byte
    {RVM_CODE_PUSH_METHOD, "push_method", OPCODE_OPERAND_TYPE_2BYTE, 1, 3}, // TODO:
    {RVM_CODE_ARGUMENT_NUM, "argument_num", OPCODE_OPERAND_TYPE_1BYTE, 0, 2},
    {RVM_CODE_INVOKE_FUNC, "invoke_func", OPCODE_OPERAND_TYPE_0BYTE, -1, 0},
    {RVM_CODE_INVOKE_METHOD, "invoke_method", OPCODE_OPERAND_TYPE_0BYTE, -2, 0},
    {RVM_CODE_RETURN, "return", OPCODE_OPERAND_TYPE_2BYTE, 0, 3}, // 操作数代表返回值的数量，ex；return int, double, string;  操作数就是3 FIXME:runtime_stack_increment
    {RVM_CODE_FUNCTION_FINISH, "function_finish", OPCODE_OPERAND_TYPE_0BYTE, 0},

    {RVM_CODE_EXIT, "exit", OPCODE_OPERAND_TYPE_1BYTE, 0},

    // new heap memory
    {RVM_CODE_NEW_ARRAY_INT, "new_array_int", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},
    {RVM_CODE_NEW_ARRAY_DOUBLE, "new_array_double", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},
    {RVM_CODE_NEW_ARRAY_OBJECT, "new_array_object", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},
    {RVM_CODE_NEW_ARRAY_LITERAL_INT, "new_array_literal_int", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},
    {RVM_CODE_NEW_ARRAY_LITERAL_DOUBLE, "new_array_literal_double", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},
    {RVM_CODE_NEW_ARRAY_LITERAL_OBJECT, "new_array_literal_object", OPCODE_OPERAND_TYPE_2BYTE, 1, 3},


    {RVM_CODES_NUM, "", OPCODE_OPERAND_TYPE_0BYTE, 0, 0},
};

Package_Executer* package_executer_create(ExecuterEntry* executer_entry, char* package_name) {
    Package_Executer* executer                = (Package_Executer*)malloc(sizeof(Package_Executer));
    executer->executer_entry                  = executer_entry;
    executer->package_index                   = -1;
    executer->package_name                    = package_name;
    executer->constant_pool_size              = 0;
    executer->constant_pool_list              = nullptr;
    executer->global_variable_size            = 0;
    executer->global_variable_list            = nullptr;
    executer->function_size                   = 0;
    executer->function_list                   = nullptr;
    executer->code_size                       = 0;
    executer->code_list                       = nullptr;
    executer->main_func_index                 = -1;
    executer->estimate_runtime_stack_capacity = 0;
    return executer;
}

void package_executer_dump(Package_Executer* package_executer) {
    assert(package_executer != nullptr);
    printf("|------------------ Package_Executer-Dump-begin ------------------\n");

    printf("|PackageIndex:%d\n", package_executer->package_index);
    printf("|PackageName:%s\n", package_executer->package_name);

    printf("|FunctionList:\n");

    for (int i = 0; i < package_executer->function_size; i++) {
        printf("|\t func_name:%s\n", package_executer->function_list[i].func_name);
    }

    printf("|------------------ Package_Executer-Dump-begin ------------------\n\n");
}

// 生成 RVM 虚拟机代码
void ring_generate_vm_code(Package* package, Package_Executer* package_executer) {
    debug_log_with_darkgreen_coloar("\t");

    add_global_variable(package, package_executer);
    add_functions(package, package_executer);
    add_classes(package, package_executer);
    add_top_level_code(package, package_executer);

#ifdef DEBUG_GENERATE_SUMMARY
    package_executer_dump(package_executer);
#endif
}

// 只生成主包的vm code
void ring_generate_vm_code(CompilerEntry* compiler_entry, ExecuterEntry* executer_entry) {
    debug_log_with_darkgreen_coloar("\t");

    Package*          main_package     = compiler_entry->main_package;
    Package_Executer* package_executer = executer_entry->main_package_executer;

    ring_generate_vm_code(main_package, package_executer);
    executer_entry->package_executer_list.push_back(package_executer);

    // for (Package* package : compiler_entry->package_list) {
    //     // FIXME: find duplicate
    //     for (Package_Executer* package_executer : executer_entry->package_executer_list) {
    //         if (0 == strcmp(package_executer->package_name, package->package_name)) {
    //             debug_log_with_darkgreen_coloar("\tpackage executer[%s] already register", package->package_name);

    //             continue;
    //         }
    //     }
    //     Package_Executer* package_executer = package_executer_create(executer_entry, package->package_name);
    //     ring_generate_vm_code(package, package_executer);
    //     executer_entry->package_executer_list.push_back(package_executer);
    // }

#ifdef DEBUG_GENERATE_SUMMARY
    executer_entry_dump(executer_entry);
#endif
}

// 添加全局变量
void add_global_variable(Package* package, Package_Executer* executer) {
    debug_log_with_darkgreen_coloar("\t");
    // FIXME: 在 Compiler 中大部分是链表：因为在编译的时候不确定存储空间
    // 在 Executer 中 大部分是数组，因为编译完成，存储空间的数量都已经确认了。
    if (package->global_declaration_list.empty()) {
        return;
    }

    executer->global_variable_size = package->global_declaration_list.size();
    executer->global_variable_list = (RVM_Variable*)malloc(executer->global_variable_size * sizeof(RVM_Variable));

    int i                          = 0;
    for (Declaration* pos : package->global_declaration_list) {
        executer->global_variable_list[i].identifier = pos->identifier;
        executer->global_variable_list[i].type       = pos->type; // TODO: 这里考虑要深度复制
        i++;
    }
}

// 添加函数定义
void add_functions(Package* package, Package_Executer* executer) {
    debug_log_with_darkgreen_coloar("\t");

    executer->function_size = package->function_list.size();
    executer->function_list = (RVM_Function*)malloc(sizeof(RVM_Function) * package->function_list.size());

    unsigned int i          = 0;
    // 暂时只处理 native function
    for (Function* pos : package->function_list) {
        copy_function(pos, &executer->function_list[i]);
        generate_code_from_function_definition(executer, pos, &executer->function_list[i]);
        // TODO: FIXME:
        // 注册main函数
        if (0 == strcmp(pos->function_name, "main")) {
            // printf("find main:%d\n", i);
            executer->main_func_index = i;
        }
        i++;
    }
}

void add_classes(Package* package, Package_Executer* executer) {
    debug_log_with_darkgreen_coloar("\t");

    executer->class_size = package->class_definition_list.size();
    executer->class_list = (RVM_Class*)malloc(sizeof(RVM_Class) * package->class_definition_list.size());

    unsigned int i       = 0;
    for (ClassDefinition* pos : package->class_definition_list) {
        copy_class(executer, pos, &executer->class_list[i]);
        i++;
    }
}

void copy_class(Package_Executer* executer, ClassDefinition* src, RVM_Class* dest) {
    debug_log_with_darkgreen_coloar("\t");

    dest->identifier            = src->class_identifier;
    dest->field_size            = 0;
    dest->field_list            = nullptr;
    dest->method_size           = 0;
    dest->method_list           = nullptr;

    ClassMemberDeclaration* pos = src->member;
    for (; pos != nullptr; pos = pos->next) {
        if (pos->type == MEMBER_FIELD) {
            dest->field_size++;
        } else if (pos->type == MEMBER_METHOD) {
            dest->method_size++;
        }
    }

    dest->method_list = (RVM_Method*)malloc(sizeof(RVM_Method) * dest->method_size);

    unsigned int i    = 0;
    pos               = src->member;
    for (; pos != nullptr; pos = pos->next) {
        if (pos->type == MEMBER_FIELD) {
        } else if (pos->type == MEMBER_METHOD) {
            copy_method(pos->u.method, &dest->method_list[i]);
            if (pos->u.method->block != nullptr)
                generate_code_from_method_definition(executer, pos->u.method, &dest->method_list[i]);
            i++;
        }
    }

    // unsigned int index = 0;
    // for(;index <  dest->method_size; index++) {
    //     RVM_Method* tmp =  &dest->method_list[index];
    //     printf("debug method_size:%s\n",  tmp->identifier);
    // }
}

void copy_function(Function* src, RVM_Function* dest) {
    debug_log_with_darkgreen_coloar("\t");

    dest->func_name = src->function_name;
    if (src->type == FUNCTION_TYPE_NATIVE) {
        dest->type                = RVM_FUNCTION_TYPE_NATIVE;
        dest->parameter_size      = src->parameter_list_size;
        dest->parameter_list      = nullptr; // TODO:
        dest->local_variable_size = 0;
        dest->local_variable_list = nullptr; // TODO:
    } else if (src->type == FUNCTION_TYPE_DERIVE) {
        dest->type                = RVM_FUNCTION_TYPE_DERIVE;
        dest->parameter_size      = src->parameter_list_size;
        dest->parameter_list      = nullptr; // TODO:
        dest->local_variable_size = src->block->declaration_list_size;
        dest->local_variable_list = (RVM_LocalVariable*)malloc(sizeof(RVM_LocalVariable) * src->block->declaration_list_size); // TODO:
        dest->u.derive_func       = (DeriveFunction*)malloc(sizeof(DeriveFunction));

        Declaration* pos          = src->block->declaration_list;
        unsigned int i            = 0;
        for (; pos != nullptr; pos = pos->next, i++) {
            dest->local_variable_list[i].identifier     = pos->identifier;
            dest->local_variable_list[i].type_specifier = pos->type;
        }
    }

    dest->estimate_runtime_stack_capacity = 0;
}

void copy_method(MethodMember* src, RVM_Method* dest) {
    dest->identifier                  = src->identifier;
    dest->rvm_function                = (RVM_Function*)malloc(sizeof(RVM_Function));
    dest->rvm_function->u.derive_func = (DeriveFunction*)malloc(sizeof(DeriveFunction));
}

void add_top_level_code(Package* package, Package_Executer* executer) {
    debug_log_with_darkgreen_coloar("\t");

    if (executer->main_func_index != -1) {
        // printf("executer->main_func_index\n");
        // 生成一下字节码
        // 找到main函数
        // 调用 main 函数
        // exit code
        RVM_OpcodeBuffer* opcode_buffer = new_opcode_buffer();
        // FIXME: (package->compiler_entry->package_list.size() - 1) << 8) 这里要修正一下
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_FUNC, ((package->compiler_entry->package_list.size() - 1) << 8) | executer->main_func_index, 0);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_INVOKE_FUNC, 0, 0);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_EXIT, 0, 0);

        executer->code_list = opcode_buffer->code_list;
        executer->code_size = opcode_buffer->code_size;
    } else {
        // 必须有main函数
        // RVM_OpcodeBuffer* opcode_buffer = new_opcode_buffer();
        // generate_vmcode_from_statement_list(executer, nullptr, package->statement_list, opcode_buffer);
        // opcode_buffer_fix_label(opcode_buffer);

        // executer->code_list = opcode_buffer->code_list;
        // executer->code_size = opcode_buffer->code_size;
    }
}

void generate_code_from_function_definition(Package_Executer* executer, Function* src, RVM_Function* dest) {
    debug_log_with_darkgreen_coloar("\t");
    if (src->block == nullptr) {
        return;
    }

    RVM_OpcodeBuffer* opcode_buffer = new_opcode_buffer();
    generate_vmcode_from_statement_list(executer, src->block, src->block->statement_list, opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_FUNCTION_FINISH, 0, src->line_number);

    opcode_buffer_fix_label(opcode_buffer);


    dest->u.derive_func->code_list = opcode_buffer->code_list;
    dest->u.derive_func->code_size = opcode_buffer->code_size;

#ifdef DEBUG
    ring_vm_code_dump(dest, opcode_buffer->code_list, opcode_buffer->code_size, 0, 60, 1);
    dump_code_line_map(opcode_buffer->code_line_map);
#endif
}

void generate_code_from_method_definition(Package_Executer* executer, MethodMember* src, RVM_Method* dest) {
    debug_log_with_darkgreen_coloar("\t");

    RVM_OpcodeBuffer* opcode_buffer = new_opcode_buffer();
    generate_vmcode_from_statement_list(executer, src->block, src->block->statement_list, opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_FUNCTION_FINISH, 0, src->line_number);

    opcode_buffer_fix_label(opcode_buffer);

    dest->rvm_function->u.derive_func->code_list = opcode_buffer->code_list;
    dest->rvm_function->u.derive_func->code_size = opcode_buffer->code_size;
    dest->rvm_function->local_variable_size      = src->block->declaration_list_size;
}

void vm_executer_dump(Package_Executer* executer) {
    debug_log_with_darkgreen_coloar("\t");
    // CLEAR_SCREEN;
    ring_vm_constantpool_dump(executer);
    ring_vm_code_dump(nullptr, executer->code_list, executer->code_size, 0, 60, 1);
}

RVM_OpcodeBuffer* new_opcode_buffer() {
    debug_log_with_darkgreen_coloar("\t");
    RVM_OpcodeBuffer* buffer = (RVM_OpcodeBuffer*)malloc(sizeof(RVM_OpcodeBuffer));
    buffer->code_list        = nullptr;
    buffer->code_size        = 0;
    buffer->code_capacity    = 0;
    buffer->lable_list       = nullptr;
    buffer->lable_size       = 0;
    buffer->lable_capacity   = 0;
    buffer->code_line_map    = std::vector<RVM_SourceCodeLineMap>{};
    return buffer;
}

void generate_vmcode_from_block(Package_Executer* executer, Block* block, RVM_OpcodeBuffer* opcode_buffer) {
    if (block == nullptr) {
        return;
    }
    debug_log_with_darkgreen_coloar("\t");
    generate_vmcode_from_statement_list(executer, block, block->statement_list, opcode_buffer);
}

void generate_vmcode_from_statement_list(Package_Executer* executer, Block* block, Statement* statement_list, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    for (Statement* statement = statement_list; statement != nullptr; statement = statement->next) {
        switch (statement->type) {
        case STATEMENT_TYPE_EXPRESSION:
            generate_vmcode_from_expression(executer, statement->u.expression, opcode_buffer, 0);
            break;

        case STATEMENT_TYPE_IF:
            generate_vmcode_from_if_statement(executer, statement->u.if_statement, opcode_buffer);
            break;

        case STATEMENT_TYPE_FOR:
            generate_vmcode_from_for_statement(executer, statement->u.for_statement, opcode_buffer);
            break;

        case STATEMENT_TYPE_DOFOR:
            generate_vmcode_from_dofor_statement(executer, statement->u.dofor_statement, opcode_buffer);
            break;

        case STATEMENT_TYPE_BREAK:
            generate_vmcode_from_break_statement(executer, block, statement->u.break_statement, opcode_buffer);
            break;

        case STATEMENT_TYPE_CONTINUE:
            generate_vmcode_from_continue_statement(executer, block, statement->u.continue_statement, opcode_buffer);
            break;

        case STATEMENT_TYPE_RETURN:
            generate_vmcode_from_return_statement(executer, block, statement->u.return_statement, opcode_buffer);
            break;

        case STATEMENT_TYPE_DECLARATION:
            generate_vmcode_from_initializer(executer, block, statement->u.declaration_statement, opcode_buffer);
            break;

        case STATEMENT_TYPE_TAG_DEFINITION:
            break;

        case STATEMENT_TYPE_JUMP_TAG:
            generate_vmcode_from_jump_tag_statement(executer, block, statement->u.jump_tag_statement, opcode_buffer);
            break;


        default: break;
        }
    }
}

void generate_vmcode_from_if_statement(Package_Executer* executer, IfStatement* if_statement, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (if_statement == nullptr) {
        return;
    }

    unsigned int if_false_jump_label = 0;
    unsigned int if_end_label        = 0;

    generate_vmcode_from_expression(executer, if_statement->condition_expression, opcode_buffer, 1);

    if_false_jump_label = opcode_buffer_get_label(opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, if_false_jump_label, if_statement->line_number);

    generate_vmcode_from_block(executer, if_statement->if_block, opcode_buffer);

    if_end_label = opcode_buffer_get_label(opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, if_end_label, if_statement->line_number);


    opcode_buffer_set_label(opcode_buffer, if_false_jump_label, opcode_buffer->code_size);

    // handle elseif list
    ElseIfStatement* pos = if_statement->elseif_list;
    for (; pos; pos = pos->next) {
        generate_vmcode_from_expression(executer, pos->condition_expression, opcode_buffer, 0);

        unsigned int elseif_false_jump_label = 0;
        elseif_false_jump_label              = opcode_buffer_get_label(opcode_buffer);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, elseif_false_jump_label, pos->line_number);

        generate_vmcode_from_block(executer, pos->elseif_block, opcode_buffer);

        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, if_end_label, pos->line_number);

        opcode_buffer_set_label(opcode_buffer, elseif_false_jump_label, opcode_buffer->code_size);
    }

    // handle else
    if (if_statement->else_block != nullptr) {
        generate_vmcode_from_block(executer, if_statement->else_block, opcode_buffer);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, if_end_label, if_statement->else_block->line_number);
    }


    opcode_buffer_set_label(opcode_buffer, if_end_label, opcode_buffer->code_size);
}

// TODO: 暂时不支持 break continue
void generate_vmcode_from_for_statement(Package_Executer* executer, ForStatement* for_statement, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (for_statement == nullptr) {
        return;
    }
    unsigned int end_label      = 0;
    unsigned int loop_label     = 0;
    unsigned int continue_label = 0;

    // Step-1:
    if (for_statement->init_expression) {
        generate_vmcode_from_expression(executer, for_statement->init_expression, opcode_buffer, 0);
    }
    loop_label = opcode_buffer_get_label(opcode_buffer);
    opcode_buffer_set_label(opcode_buffer, loop_label, opcode_buffer->code_size);

    // Step-2:
    end_label = opcode_buffer_get_label(opcode_buffer);
    if (for_statement->condition_expression) {
        generate_vmcode_from_expression(executer, for_statement->condition_expression, opcode_buffer, 0);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, end_label, for_statement->condition_expression->line_number);
    }


    // Step-3:
    if (for_statement->block) {
        for_statement->block->block_labels.break_label = end_label;
        for_statement->block->block_labels.continue_label =
            continue_label = opcode_buffer_get_label(opcode_buffer);

        generate_vmcode_from_block(executer, for_statement->block, opcode_buffer);
    }

    opcode_buffer_set_label(opcode_buffer, continue_label, opcode_buffer->code_size);

    // Step-4:
    if (for_statement->post_expression) {
        generate_vmcode_from_expression(executer, for_statement->post_expression, opcode_buffer, 0);
    }

    // Step-5:
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, loop_label, for_statement->line_number);


    // Step-End:

    opcode_buffer_set_label(opcode_buffer, end_label, opcode_buffer->code_size);
}

// TODO: 暂时不支持 break continue
void generate_vmcode_from_dofor_statement(Package_Executer* executer, DoForStatement* dofor_statement, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (dofor_statement == nullptr) {
        return;
    }
    unsigned int end_label      = 0;
    unsigned int loop_label     = 0;
    unsigned int continue_label = 0;


    // Step-1:
    if (dofor_statement->init_expression) {
        generate_vmcode_from_expression(executer, dofor_statement->init_expression, opcode_buffer, 0);
    }
    loop_label = opcode_buffer_get_label(opcode_buffer);
    opcode_buffer_set_label(opcode_buffer, loop_label, opcode_buffer->code_size);


    // Step-2:
    end_label = opcode_buffer_get_label(opcode_buffer);
    if (dofor_statement->block) {
        dofor_statement->block->block_labels.break_label = end_label;
        dofor_statement->block->block_labels.continue_label =
            continue_label = opcode_buffer_get_label(opcode_buffer);

        generate_vmcode_from_block(executer, dofor_statement->block, opcode_buffer);
    }


    opcode_buffer_set_label(opcode_buffer, continue_label, opcode_buffer->code_size);


    // Step-3:
    if (dofor_statement->condition_expression) {
        generate_vmcode_from_expression(executer, dofor_statement->condition_expression, opcode_buffer, 0);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, end_label, dofor_statement->condition_expression->line_number);
    }


    // Step-4:
    if (dofor_statement->post_expression) {
        generate_vmcode_from_expression(executer, dofor_statement->post_expression, opcode_buffer, 0);
    }

    // Step-5;
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, loop_label, dofor_statement->line_number);

    // Step-End;
    opcode_buffer_set_label(opcode_buffer, end_label, opcode_buffer->code_size);
}

void generate_vmcode_from_break_statement(Package_Executer* executer, Block* block, BreakStatement* break_statement, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (break_statement == nullptr) {
        return;
    }

    unsigned int break_loop_num = break_statement->break_loop_num;

    Block*       pos            = block;
    unsigned int loop_num       = 1;
    for (; pos; pos = pos->parent_block) {
        if (pos->type == BLOCK_TYPE_FOR) {
        } else if (pos->type == BLOCK_TYPE_DOFOR) {
        } else {
            continue;
        }

        if (break_loop_num == loop_num) {
            break;
        }
        loop_num++;
    }


    if (pos == nullptr) {
        printf("generate_vmcode_from_break_statement error------------\n");
        exit(ERROR_CODE_GENERATE_OPCODE_ERROR);
    }

    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, pos->block_labels.break_label, break_statement->line_number);
}

void generate_vmcode_from_continue_statement(Package_Executer* executer, Block* block, ContinueStatement* continue_statement, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (continue_statement == nullptr) {
        return;
    }

    Block* pos = block;
    for (; pos; pos = pos->parent_block) {
        if (pos->type == BLOCK_TYPE_FOR) {
            break;
        } else if (pos->type == BLOCK_TYPE_DOFOR) {
            break;
        } else {
            continue;
        }
    }


    if (pos == nullptr) {
        printf("generate_vmcode_from_continue_statement error------------\n");
        exit(ERROR_CODE_GENERATE_OPCODE_ERROR);
    }

    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, pos->block_labels.continue_label, continue_statement->line_number);
}

void generate_vmcode_from_return_statement(Package_Executer* executer, Block* block, ReturnStatement* return_statement, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (return_statement == nullptr) {
        return;
    }


    Expression* pos;
    for (pos = return_statement->return_list; pos; pos = pos->next) {
        generate_vmcode_from_expression(executer, pos, opcode_buffer, 1);
    }


    generate_vmcode(executer, opcode_buffer, RVM_CODE_RETURN, return_statement->return_list_size, return_statement->line_number);
}

void generate_vmcode_from_initializer(Package_Executer* executer, Block* block, Declaration* declaration, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (declaration == nullptr) {
        return;
    }

    Declaration* pos = declaration;
    for (; pos; pos = pos->next) {
        if (pos->initializer) {
            generate_vmcode_from_expression(executer, pos->initializer, opcode_buffer, 1);
            RVM_Opcode opcode = RVM_CODE_UNKNOW;
            if (pos->is_local) {
                // 局部变量
                opcode = convert_opcode_by_rvm_type(RVM_CODE_POP_STACK_BOOL, pos->type);
            } else {
                // 全局变量
                opcode = convert_opcode_by_rvm_type(RVM_CODE_POP_STATIC_BOOL, pos->type);
            }
            generate_vmcode(executer, opcode_buffer, opcode, pos->variable_index, declaration->line_number);
        }
    }
}

void generate_vmcode_from_jump_tag_statement(Package_Executer* executer, Block* block, JumpTagStatement* jump_tag_statement, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (jump_tag_statement == nullptr) {
        return;
    }
}

void generate_vmcode_from_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer, int need_duplicate) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == nullptr) {
        return;
    }

    switch (expression->type) {
    case EXPRESSION_TYPE_LITERAL_BOOL:
        generate_vmcode_from_bool_expression(executer, expression, opcode_buffer);
        break;
    case EXPRESSION_TYPE_LITERAL_INT:
        generate_vmcode_from_int_expression(executer, expression, opcode_buffer);
        break;
    case EXPRESSION_TYPE_LITERAL_DOUBLE:
        generate_vmcode_from_double_expression(executer, expression, opcode_buffer);
        break;
    case EXPRESSION_TYPE_LITERAL_STRING:
        generate_vmcode_from_string_expression(executer, expression, opcode_buffer);
        break;
    case EXPRESSION_TYPE_IDENTIFIER:
        generate_vmcode_from_identifier_expression(executer, expression->u.identifier_expression, opcode_buffer);
        break;
    case EXPRESSION_TYPE_CONCAT:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_CONCAT);
        break;
    case EXPRESSION_TYPE_ARITHMETIC_ADD:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_ADD_INT);
        break;

    case EXPRESSION_TYPE_ARITHMETIC_SUB:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_SUB_INT);
        break;

    case EXPRESSION_TYPE_ARITHMETIC_MUL:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_MUL_INT);
        break;

    case EXPRESSION_TYPE_ARITHMETIC_DIV:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_DIV_INT);
        break;

    case EXPRESSION_TYPE_ARITHMETIC_MOD:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_MOD_INT);
        break;

    case EXPRESSION_TYPE_ARITHMETIC_UNITARY_MINUS:
        generate_vmcode_from_unitary_minus_expression(executer, expression->u.unitary_expression, opcode_buffer, RVM_CODE_MINUS_INT);
        break;

    case EXPRESSION_TYPE_LOGICAL_AND:
        generate_vmcode_from_logical_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_LOGICAL_AND);
        break;
    case EXPRESSION_TYPE_LOGICAL_OR:
        generate_vmcode_from_logical_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_LOGICAL_OR);
        break;
    case EXPRESSION_TYPE_LOGICAL_UNITARY_NOT:
        generate_vmcode_from_unitary_not_expression(executer, expression->u.unitary_expression, opcode_buffer, RVM_CODE_LOGICAL_NOT);
        break;

    case EXPRESSION_TYPE_UNITARY_INCREASE_SUFFIX:
    case EXPRESSION_TYPE_UNITARY_INCREASE_PREFIX:
    case EXPRESSION_TYPE_UNITARY_DECREASE_SUFFIX:
    case EXPRESSION_TYPE_UNITARY_DECREASE_PREFIX:
        generate_vmcode_from_increase_decrease_expression(executer, expression, opcode_buffer, need_duplicate);
        break;

    case EXPRESSION_TYPE_RELATIONAL_EQ:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_RELATIONAL_EQ_INT);
        break;
    case EXPRESSION_TYPE_RELATIONAL_NE:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_RELATIONAL_NE_INT);
        break;
    case EXPRESSION_TYPE_RELATIONAL_GT:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_RELATIONAL_GT_INT);
        break;
    case EXPRESSION_TYPE_RELATIONAL_GE:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_RELATIONAL_GE_INT);
        break;
    case EXPRESSION_TYPE_RELATIONAL_LT:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_RELATIONAL_LT_INT);
        break;
    case EXPRESSION_TYPE_RELATIONAL_LE:
        generate_vmcode_from_binary_expression(executer, expression->u.binary_expression, opcode_buffer, RVM_CODE_RELATIONAL_LE_INT);
        break;

    case EXPRESSION_TYPE_ASSIGN:
        generate_vmcode_from_assign_expression(executer, expression->u.assign_expression, opcode_buffer);
        break;

    case EXPRESSION_TYPE_FUNCTION_CALL:
        generate_vmcode_from_function_call_expression(executer, expression->u.function_call_expression, opcode_buffer);
        break;
    case EXPRESSION_TYPE_METHOD_CALL:
        generate_vmcode_from_method_call_expression(executer, expression->u.method_call_expression, opcode_buffer);
        break;

    case EXPRESSION_TYPE_CAST:
        generate_vmcode_from_cast_expression(executer, expression->u.cast_expression, opcode_buffer);
        break;

    case EXPRESSION_TYPE_MEMBER:
        generate_vmcode_from_member_expression(executer, expression->u.member_expression, opcode_buffer);
        break;

    case EXPRESSION_TYPE_TERNARY:
        generate_vmcode_from_ternary_condition_expression(executer, expression->u.ternary_expression, opcode_buffer);
        break;

    case EXPRESSION_TYPE_ARRAY_INDEX:
        generate_vmcode_from_array_index_expression(executer, expression->u.array_index_expression, opcode_buffer);
        break;

    case EXPRESSION_TYPE_NEW_ARRAY:
        generate_vmcode_from_new_array_expression(executer, expression->u.new_array_expression, opcode_buffer);
        break;

    case EXPRESSION_TYPE_ARRAY_LITERAL:
        generate_vmcode_from_array_literal_expreesion(executer, expression->u.array_literal_expression, opcode_buffer);
        break;

    default:
        break;
    }
}

void generate_vmcode_from_assign_expression(Package_Executer* executer, AssignExpression* expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    assert(expression != nullptr);

    // TODO:
    if (expression->type != ASSIGN_EXPRESSION_TYPE_ASSIGN && expression->type != ASSIGN_EXPRESSION_TYPE_MULTI_ASSIGN) {
        // += -= *= /=
        generate_vmcode_from_expression(executer, expression->left, opcode_buffer, 1);
    }

    if (expression->type == ASSIGN_EXPRESSION_TYPE_MULTI_ASSIGN) {
        Expression* pos;
        for (pos = expression->operand; pos; pos = pos->next) {
            generate_vmcode_from_expression(executer, pos, opcode_buffer, 1);
        }
    } else {
        generate_vmcode_from_expression(executer, expression->operand, opcode_buffer, 1);
    }

    unsigned int opcode_offset = 0;
    if (expression->operand->convert_type != nullptr && expression->operand->convert_type->kind == RING_BASIC_TYPE_DOUBLE) {
        opcode_offset += 1;
    }

    switch (expression->type) {
    case ASSIGN_EXPRESSION_TYPE_ASSIGN:
        /* code */
        break;
    case ASSIGN_EXPRESSION_TYPE_MULTI_ASSIGN:
        break;

    case ASSIGN_EXPRESSION_TYPE_ADD_ASSIGN:
        generate_vmcode(executer, opcode_buffer, RVM_Opcode(RVM_CODE_ADD_INT + opcode_offset), 0, expression->line_number);
        break;
    case ASSIGN_EXPRESSION_TYPE_SUB_ASSIGN:
        generate_vmcode(executer, opcode_buffer, RVM_Opcode(RVM_CODE_SUB_INT + opcode_offset), 0, expression->line_number);
        break;
    case ASSIGN_EXPRESSION_TYPE_MUL_ASSIGN:
        generate_vmcode(executer, opcode_buffer, RVM_Opcode(RVM_CODE_MUL_INT + opcode_offset), 0, expression->line_number);
        break;
    case ASSIGN_EXPRESSION_TYPE_DIV_ASSIGN:
        generate_vmcode(executer, opcode_buffer, RVM_Opcode(RVM_CODE_DIV_INT + opcode_offset), 0, expression->line_number);
        break;
    case ASSIGN_EXPRESSION_TYPE_MOD_ASSIGN:
        generate_vmcode(executer, opcode_buffer, RVM_Opcode(RVM_CODE_MOD_INT + opcode_offset), 0, expression->line_number);
        break;

    default:
        break;
    }

    // if (expression->left->type != EXPRESSION_TYPE_IDENTIFIER) {
    //     fprintf(stderr, "generate opcode error1\n");
    //     exit(ERROR_CODE_GENERATE_OPCODE_ERROR);
    // }

    if (expression->type == ASSIGN_EXPRESSION_TYPE_MULTI_ASSIGN) {
        // access identifier in reverse order.
        // TODO: FIXME:
        generate_pop_to_leftvalue_reverse(executer, expression->left, opcode_buffer);
    } else {
        // TODO: FIXME:
        generate_pop_to_leftvalue(executer, expression->left, opcode_buffer);
    }
}

// TODO: FIXME:
void generate_pop_to_leftvalue_reverse(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == nullptr) {
        return;
    }

    generate_pop_to_leftvalue_reverse(executer, expression->next, opcode_buffer);
    generate_pop_to_leftvalue(executer, expression, opcode_buffer);
}

// TODO:  处理 赋值给 标识符、array[index]、成员变量 a.b
void generate_pop_to_leftvalue(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer) {
    if (expression->type == EXPRESSION_TYPE_IDENTIFIER) {
        generate_pop_to_leftvalue_identifier(executer, expression->u.identifier_expression, opcode_buffer);
    } else if (expression->type == EXPRESSION_TYPE_MEMBER) {
        generate_pop_to_leftvalue_member(executer, expression->u.member_expression, opcode_buffer);
    }
}

void generate_pop_to_leftvalue_identifier(Package_Executer* executer, IdentifierExpression* identifier_expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    assert(identifier_expression != nullptr);

    Declaration* declaration    = identifier_expression->u.declaration;

    unsigned int variable_index = declaration->variable_index;
    RVM_Opcode   opcode         = RVM_CODE_UNKNOW;
    if (declaration->is_local) {
        opcode = convert_opcode_by_rvm_type(RVM_CODE_POP_STACK_BOOL, declaration->type);
    } else {
        opcode = convert_opcode_by_rvm_type(RVM_CODE_POP_STATIC_BOOL, declaration->type);
    }
    generate_vmcode(executer, opcode_buffer, opcode, variable_index, identifier_expression->line_number);
}

void generate_pop_to_leftvalue_member(Package_Executer* executer, MemberExpression* member_expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (member_expression == nullptr) {
        return;
    }

    RVM_Opcode opcode        = RVM_CODE_UNKNOW;
    opcode                   = convert_opcode_by_rvm_type(RVM_CODE_POP_FIELD_BOOL, member_expression->member_declaration->u.field->type);
    unsigned int field_index = member_expression->member_declaration->u.field->index_of_class;

    generate_vmcode_from_expression(executer, member_expression->object_expression, opcode_buffer, 0);
    generate_vmcode(executer, opcode_buffer, opcode, field_index, member_expression->line_number);
}

void generate_vmcode_from_logical_expression(Package_Executer* executer, BinaryExpression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == nullptr) {
        return;
    }

    Expression*  left      = expression->left_expression;
    Expression*  right     = expression->right_expression;
    unsigned int end_label = 0;

    if (opcode == RVM_CODE_LOGICAL_AND) {
        generate_vmcode_from_expression(executer, left, opcode_buffer, 1);

        generate_vmcode(executer, opcode_buffer, RVM_CODE_DUPLICATE, 0, expression->line_number);
        end_label = opcode_buffer_get_label(opcode_buffer);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, end_label, expression->line_number);

        generate_vmcode_from_expression(executer, right, opcode_buffer, 1);

        generate_vmcode(executer, opcode_buffer, opcode, 0, expression->line_number);
    } else if (opcode == RVM_CODE_LOGICAL_OR) {
        generate_vmcode_from_expression(executer, left, opcode_buffer, 1);

        generate_vmcode(executer, opcode_buffer, RVM_CODE_DUPLICATE, 0, expression->line_number);
        end_label = opcode_buffer_get_label(opcode_buffer);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_TRUE, end_label, expression->line_number);

        generate_vmcode_from_expression(executer, right, opcode_buffer, 1);

        generate_vmcode(executer, opcode_buffer, opcode, 0, expression->line_number);
    }

    opcode_buffer_set_label(opcode_buffer, end_label, opcode_buffer->code_size);
}

void generate_vmcode_from_binary_expression(Package_Executer* executer, BinaryExpression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == nullptr) {
        return;
    }
    Expression* left  = expression->left_expression;
    Expression* right = expression->right_expression;


    if (opcode == RVM_CODE_CONCAT) {
        goto END;
    }

    if (left->convert_type != nullptr && left->convert_type->kind == RING_BASIC_TYPE_STRING
        && right->convert_type != nullptr && right->convert_type->kind == RING_BASIC_TYPE_STRING) {
        // TODO: 要在语义检查里严格检查
        // 肯定是eq ne gt ge lt le
        opcode = RVM_Opcode(opcode + 2);
        goto END;
    }


    if (left->type == EXPRESSION_TYPE_LITERAL_DOUBLE
        || right->type == EXPRESSION_TYPE_LITERAL_DOUBLE) {
        opcode = RVM_Opcode(opcode + 1);
    } else if ((left->convert_type != nullptr && left->convert_type->kind == RING_BASIC_TYPE_DOUBLE)
               || (right->convert_type != nullptr && right->convert_type->kind == RING_BASIC_TYPE_DOUBLE)) {
        opcode = RVM_Opcode(opcode + 1);
    }

END:
    generate_vmcode_from_expression(executer, left, opcode_buffer, 1);
    generate_vmcode_from_expression(executer, right, opcode_buffer, 1);

    generate_vmcode(executer, opcode_buffer, opcode, 0, expression->line_number);
}

void generate_vmcode_from_increase_decrease_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer, int need_duplicate) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == nullptr) {
        return;
    }

    Expression* unitary_expression = expression->u.unitary_expression;
    generate_vmcode_from_expression(executer, unitary_expression, opcode_buffer, 1);

    switch (expression->type) {
    case EXPRESSION_TYPE_UNITARY_INCREASE_SUFFIX:
        /* generate_vmcode(executer, opcode_buffer, ); */
        if (need_duplicate) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_DUPLICATE, 0, expression->line_number);
        }
        generate_vmcode(executer, opcode_buffer, RVM_CODE_INCREASE_SUFFIX, 0, expression->line_number);
        break;
    case EXPRESSION_TYPE_UNITARY_INCREASE_PREFIX:
        generate_vmcode(executer, opcode_buffer, RVM_CODE_INCREASE_PREFIX, 0, expression->line_number);
        if (need_duplicate) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_DUPLICATE, 0, expression->line_number);
        }
        break;
    case EXPRESSION_TYPE_UNITARY_DECREASE_SUFFIX:
        if (need_duplicate) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_DUPLICATE, 0, expression->line_number);
        }
        generate_vmcode(executer, opcode_buffer, RVM_CODE_DECREASE_SUFFIX, 0, expression->line_number);
        break;
    case EXPRESSION_TYPE_UNITARY_DECREASE_PREFIX:
        generate_vmcode(executer, opcode_buffer, RVM_CODE_DECREASE_PREFIX, 0, expression->line_number);
        if (need_duplicate) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_DUPLICATE, 0, expression->line_number);
        }
        break;
    default: break;
    }


    generate_pop_to_leftvalue(executer, unitary_expression, opcode_buffer);
}

void generate_vmcode_from_unitary_minus_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == nullptr) {
        return;
    }

    generate_vmcode_from_expression(executer, expression, opcode_buffer, 1);

    switch (expression->type) {
    case EXPRESSION_TYPE_LITERAL_INT:
        opcode = RVM_CODE_MINUS_INT;
        break;
    case EXPRESSION_TYPE_LITERAL_DOUBLE:
        opcode = RVM_CODE_MINUS_DOUBLE;
        break;
    default: {
        char error_message_buffer[1024];
        char advice_buffer[1024];
        snprintf(error_message_buffer, 1024, "%sError:%s "
                                             "minus operator only be used in int/double literal; E:%d",
                 LOG_COLOR_RED,
                 LOG_COLOR_CLEAR,
                 ERROR_MINUS_OPER_INVALID_USE);
        snprintf(advice_buffer, 1024, "%sNotice:%s "
                                      "minus operator used like: -1, -1.345",
                 LOG_COLOR_YELLOW,
                 LOG_COLOR_CLEAR);

        ErrorReportContext context = {
            nullptr,
            get_package_unit()->current_file_name,
            package_unit_get_line_content(expression->line_number),
            expression->line_number,
            0,
            std::string(error_message_buffer),
            std::string(advice_buffer),
            ERROR_REPORT_TYPE_EXIT_NOW,
        };
        ring_compile_error_report(&context);
    }
    // TODO: 可以将 minus运算符 运用在 非 literal上
    break;
    }

    generate_vmcode(executer, opcode_buffer, opcode, 0, expression->line_number);
}

void generate_vmcode_from_unitary_not_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == nullptr) {
        return;
    }

    generate_vmcode_from_expression(executer, expression, opcode_buffer, 1);

    generate_vmcode(executer, opcode_buffer, opcode, 0, expression->line_number);
}

void generate_vmcode_from_identifier_expression(Package_Executer* executer, IdentifierExpression* identifier_expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (identifier_expression == nullptr) {
        return;
    }
    RVM_Opcode   opcode         = RVM_CODE_UNKNOW;
    unsigned int package_offset = 0;
    unsigned int offset         = 0;
    unsigned int operand        = 0;
    switch (identifier_expression->type) {
    case IDENTIFIER_EXPRESSION_TYPE_VARIABLE:
        if (identifier_expression->u.declaration->is_local) {
            opcode = convert_opcode_by_rvm_type(RVM_CODE_PUSH_STACK_BOOL, identifier_expression->u.declaration->type);
        } else {
            opcode = convert_opcode_by_rvm_type(RVM_CODE_PUSH_STATIC_BOOL, identifier_expression->u.declaration->type);
        }
        offset = identifier_expression->u.declaration->variable_index;
        generate_vmcode(executer, opcode_buffer, opcode, offset, identifier_expression->line_number);
        break;

    case IDENTIFIER_EXPRESSION_TYPE_FUNCTION:
        // find package & function index
        package_offset = identifier_expression->u.function->package->package_index; // FIXME:
        offset         = identifier_expression->u.function->func_index;
        operand        = (package_offset << 8) | offset;
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_FUNC, operand, identifier_expression->line_number);
        break;

    default:
        break;
    }
}

void generate_vmcode_from_bool_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == nullptr) {
        return;
    }
    if (!expression->u.bool_literal) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_BOOL, RVM_FALSE, expression->line_number);
    } else {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_BOOL, RVM_TRUE, expression->line_number);
    }
}

void generate_vmcode_from_int_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == nullptr) {
        return;
    }
    assert(expression->type == EXPRESSION_TYPE_LITERAL_INT);

    if (0 <= expression->u.int_literal && expression->u.int_literal < 256) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_INT_1BYTE, expression->u.int_literal, expression->line_number);
    } else if (256 <= expression->u.int_literal && expression->u.int_literal < 65536) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_INT_2BYTE, expression->u.int_literal, expression->line_number);
    } else {
        int constant_index = constant_pool_add_int(executer, expression->u.int_literal);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_INT, constant_index, expression->line_number);
    }
}

void generate_vmcode_from_double_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (expression == nullptr) {
        return;
    }
    assert(expression->type == EXPRESSION_TYPE_LITERAL_DOUBLE);

    int constant_index = constant_pool_add_double(executer, expression->u.double_literal);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_DOUBLE, constant_index, expression->line_number);
}

void generate_vmcode_from_string_expression(Package_Executer* executer, Expression* expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    // 都放在常量区
    assert(expression->type == EXPRESSION_TYPE_LITERAL_STRING);
    int constant_index = constant_pool_add_string(executer, expression->u.string_literal);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_STRING, constant_index, expression->line_number);
}

void generate_vmcode_from_function_call_expression(Package_Executer* executer, FunctionCallExpression* function_call_expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (function_call_expression == nullptr) {
        return;
    }
    ArgumentList* pos                = function_call_expression->argument_list;
    unsigned int  argument_list_size = 0;
    for (; pos != nullptr; pos = pos->next) {
        generate_vmcode_from_expression(executer, pos->expression, opcode_buffer, 1);
        argument_list_size++;
    }

    generate_vmcode(executer, opcode_buffer, RVM_CODE_ARGUMENT_NUM, argument_list_size, function_call_expression->line_number);

    generate_vmcode_from_expression(executer, function_call_expression->function_identifier_expression, opcode_buffer, 1);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_INVOKE_FUNC, 0, function_call_expression->line_number);
}

void generate_vmcode_from_method_call_expression(Package_Executer* executer, MethodCallExpression* method_call_expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (method_call_expression == nullptr) {
        return;
    }
    ArgumentList* pos                = method_call_expression->argument_list;
    unsigned int  argument_list_size = 0;
    for (; pos != nullptr; pos = pos->next) {
        generate_vmcode_from_expression(executer, pos->expression, opcode_buffer, 1);
        argument_list_size++;
    }

    // argument
    generate_vmcode(executer, opcode_buffer, RVM_CODE_ARGUMENT_NUM, argument_list_size, method_call_expression->line_number);

    // object
    generate_vmcode_from_expression(executer, method_call_expression->object_expression, opcode_buffer, 1);

    // generate_vmcode_from_expression(executer, function_call_expression->function_identifier_expression, opcode_buffer, 1);
    ClassMemberDeclaration* member_declaration  = method_call_expression->member_declaration;
    unsigned                member_method_index = member_declaration->u.method->index_of_class;
    generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_METHOD, member_method_index, method_call_expression->line_number);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_INVOKE_METHOD, 0, method_call_expression->line_number);
}

void generate_vmcode_from_cast_expression(Package_Executer* executer, CastExpression* cast_expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (cast_expression == nullptr) {
        return;
    }

    generate_vmcode_from_expression(executer, cast_expression->operand, opcode_buffer, 1);
    // RVM_Opcode opcode = RVM_CODE_UNKNOW;

    // FIXME: derive type
    switch (cast_expression->type->kind) {
    case RING_BASIC_TYPE_BOOL:
        if (cast_expression->operand->convert_type != nullptr
            && cast_expression->operand->convert_type->kind == RING_BASIC_TYPE_INT) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_CAST_INT_TO_BOOL, 0, cast_expression->line_number);
        } else if (cast_expression->operand->convert_type != nullptr
                   && cast_expression->operand->convert_type->kind == RING_BASIC_TYPE_DOUBLE) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_CAST_DOUBLE_TO_INT, 0, cast_expression->line_number);
            generate_vmcode(executer, opcode_buffer, RVM_CODE_CAST_INT_TO_BOOL, 0, cast_expression->line_number);
        }
        break;
    case RING_BASIC_TYPE_INT:
        if (cast_expression->operand->convert_type != nullptr
            && cast_expression->operand->convert_type->kind == RING_BASIC_TYPE_BOOL) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_CAST_BOOL_TO_INT, 0, cast_expression->line_number);
        } else if (cast_expression->operand->convert_type != nullptr
                   && cast_expression->operand->convert_type->kind == RING_BASIC_TYPE_DOUBLE) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_CAST_DOUBLE_TO_INT, 0, cast_expression->line_number);
        }
        break;

    case RING_BASIC_TYPE_DOUBLE:
        if (cast_expression->operand->convert_type != nullptr
            && cast_expression->operand->convert_type->kind == RING_BASIC_TYPE_BOOL) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_CAST_BOOL_TO_INT, 0, cast_expression->line_number);
            generate_vmcode(executer, opcode_buffer, RVM_CODE_CAST_INT_TO_DOUBLE, 0, cast_expression->line_number);
        } else if (cast_expression->operand->convert_type != nullptr
                   && cast_expression->operand->convert_type->kind == RING_BASIC_TYPE_INT) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_CAST_INT_TO_DOUBLE, 0, cast_expression->line_number);
        }
        break;
    default:
        break;
    }
    // generate_vmcode(executer, opcode_buffer, opcode, 0);
}

void generate_vmcode_from_member_expression(Package_Executer* executer, MemberExpression* member_expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    if (member_expression == nullptr) {
        return;
    }

    // object
    generate_vmcode_from_expression(executer, member_expression->object_expression, opcode_buffer, 0);

    // member
    ClassMemberDeclaration* member_declaration = member_expression->member_declaration;
    RVM_Opcode              opcode             = convert_opcode_by_rvm_type(RVM_CODE_PUSH_FIELD_BOOL, member_declaration->u.field->type);
    unsigned                member_field_index = member_declaration->u.field->index_of_class;
    generate_vmcode(executer, opcode_buffer, opcode, member_field_index, member_expression->line_number);
}

void generate_vmcode_from_ternary_condition_expression(Package_Executer* executer, TernaryExpression* ternary_expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    assert(ternary_expression != nullptr);

    unsigned int if_false_jump_label = 0;
    unsigned int if_end_label        = 0;

    generate_vmcode_from_expression(executer, ternary_expression->condition_expression, opcode_buffer, 1);

    if_false_jump_label = opcode_buffer_get_label(opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, if_false_jump_label, ternary_expression->line_number);

    generate_vmcode_from_expression(executer, ternary_expression->true_expression, opcode_buffer, 1);

    if_end_label = opcode_buffer_get_label(opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, if_end_label, ternary_expression->line_number);


    opcode_buffer_set_label(opcode_buffer, if_false_jump_label, opcode_buffer->code_size);

    generate_vmcode_from_expression(executer, ternary_expression->false_expression, opcode_buffer, 1);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, if_end_label, ternary_expression->line_number);

    opcode_buffer_set_label(opcode_buffer, if_end_label, opcode_buffer->code_size);
}

void generate_vmcode_from_new_array_expression(Package_Executer* executer, NewArrayExpression* new_array_expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    assert(new_array_expression != nullptr);
    assert(new_array_expression->dimension_expression != nullptr);

    unsigned int dimension = new_array_expression->dimension_expression->dimension;

    if (new_array_expression->type_specifier->kind == RING_BASIC_TYPE_INT) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_NEW_ARRAY_INT, dimension, new_array_expression->line_number);
    } else if (new_array_expression->type_specifier->kind == RING_BASIC_TYPE_DOUBLE) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_NEW_ARRAY_DOUBLE, dimension, new_array_expression->line_number);
    } else {
        printf("error: only support int[] double[]\n");
        exit(1);
    }
}

void generate_vmcode_from_array_literal_expreesion(Package_Executer* executer, ArrayLiteralExpression* array_literal_expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    assert(array_literal_expression != nullptr);
    assert(array_literal_expression->expression_list != nullptr);

    int         size = 0;
    Expression* pos  = array_literal_expression->expression_list;
    for (; pos != nullptr; pos = pos->next) {
        generate_vmcode_from_expression(executer, pos, opcode_buffer, 0);
        size++;
    }

    if (array_literal_expression->type_specifier->kind == RING_BASIC_TYPE_INT) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_NEW_ARRAY_LITERAL_INT, size, array_literal_expression->line_number);
    } else if (array_literal_expression->type_specifier->kind == RING_BASIC_TYPE_DOUBLE) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_NEW_ARRAY_LITERAL_DOUBLE, size, array_literal_expression->line_number);
    } else {
        printf("error: only support int[] double[]\n");
        exit(1);
    }
}

void generate_vmcode_from_array_index_expression(Package_Executer* executer, ArrayIndexExpression* array_index_expression, RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    assert(array_index_expression != nullptr);
    assert(array_index_expression->array_expression != nullptr);
    assert(array_index_expression->index_expression != nullptr);

    // Expression* array = array_index_expression->array_expression;
    Expression* index = array_index_expression->index_expression;
    // FIXME: 这里处理 array_expression 不对，需要修正，目前暂时写死
    generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_STATIC_OBJECT, 1, array_index_expression->line_number);
    generate_vmcode_from_expression(executer, index, opcode_buffer, 0);

    // TODO：需要处理一下字符串 通过索引寻址
    // 这里暂时只处理数组
    // 暂时只处理一维数组
    // 要通过变量的类型来决定 push_array_int push_array_double push_array_object
    Declaration* declaration = array_index_expression->array_expression->u.identifier_expression->u.declaration;
    if (declaration == nullptr) {
        printf("invalid operator[] in identifier:%s\n", array_index_expression->array_expression->u.identifier_expression->identifier);
        exit(1);
    }


    if (declaration->type->next->kind == RING_BASIC_TYPE_INT) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_ARRAY_INT, 0, array_index_expression->line_number);
    } else if (declaration->type->next->kind == RING_BASIC_TYPE_DOUBLE) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_ARRAY_DOUBLE, 0, array_index_expression->line_number);
    }
}

void generate_vmcode(Package_Executer* executer, RVM_OpcodeBuffer* opcode_buffer, RVM_Opcode opcode, unsigned int oper_num, unsigned int line_number) {
    debug_log_with_darkgreen_coloar("\t");
    if (opcode_buffer->code_capacity == opcode_buffer->code_size) {
        // FIXME:
        opcode_buffer->code_capacity += 3000;
    }

    unsigned int    start_pc                             = opcode_buffer->code_size;
    RVM_Opcode_Info opcode_info                          = RVM_Opcode_Infos[opcode];
    opcode_buffer->code_list                             = (RVM_Byte*)realloc(opcode_buffer->code_list, opcode_buffer->code_capacity * sizeof(RVM_Byte));
    opcode_buffer->code_list[opcode_buffer->code_size++] = opcode; // 操作码

    switch (opcode_info.type) {
    case OPCODE_OPERAND_TYPE_0BYTE:
        break;

    case OPCODE_OPERAND_TYPE_1BYTE:
        opcode_buffer->code_list[opcode_buffer->code_size++] = oper_num;
        break;

    case OPCODE_OPERAND_TYPE_2BYTE:
        opcode_buffer->code_list[opcode_buffer->code_size++] = (RVM_Byte)(oper_num >> 8);
        opcode_buffer->code_list[opcode_buffer->code_size++] = (RVM_Byte)(oper_num & 0Xff);
        break;

    default: break;
    }

    if (line_number)
        add_code_line_map(opcode_buffer, line_number, start_pc, opcode_buffer->code_size - start_pc);
}

int constant_pool_grow(Package_Executer* executer, unsigned int growth_size) {
    debug_log_with_darkgreen_coloar("\t");
    int old_size = executer->constant_pool_size;
    executer->constant_pool_size += growth_size;

    executer->constant_pool_list = (RVM_ConstantPool*)realloc(executer->constant_pool_list,
                                                              executer->constant_pool_size * sizeof(RVM_ConstantPool));

    return old_size;
}

int constant_pool_add_int(Package_Executer* executer, int int_literal) {
    debug_log_with_darkgreen_coloar("\t");
    int index                                       = constant_pool_grow(executer, 1);

    executer->constant_pool_list[index].type        = CONSTANTPOOL_TYPE_INT;
    executer->constant_pool_list[index].u.int_value = int_literal;
    return index;
}

int constant_pool_add_double(Package_Executer* executer, double double_literal) {
    debug_log_with_darkgreen_coloar("\t");
    int index                                          = constant_pool_grow(executer, 1);

    executer->constant_pool_list[index].type           = CONSTANTPOOL_TYPE_DOUBLE;
    executer->constant_pool_list[index].u.double_value = double_literal;
    return index;
}

int constant_pool_add_string(Package_Executer* executer, char* string_literal) {
    debug_log_with_darkgreen_coloar("\t");
    int              index = constant_pool_grow(executer, 1);

    RVM_ConstantPool new_value;
    new_value.type                                     = CONSTANTPOOL_TYPE_STRING;
    new_value.u.string_value                           = string_literal;
    executer->constant_pool_list[index]                = new_value;

    executer->constant_pool_list[index].type           = CONSTANTPOOL_TYPE_STRING;
    executer->constant_pool_list[index].u.string_value = string_literal;
    return index;
}


unsigned int opcode_buffer_get_label(RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");
    unsigned int old_index = opcode_buffer->lable_size;

    if (opcode_buffer->lable_capacity <= opcode_buffer->code_size) {
        opcode_buffer->lable_capacity += 1024;
        opcode_buffer->lable_list = (RVM_LabelTable*)realloc(opcode_buffer->lable_list,
                                                             sizeof(RVM_LabelTable) * opcode_buffer->lable_capacity);
    }

    opcode_buffer->lable_list[opcode_buffer->lable_size].label_name    = nullptr;
    opcode_buffer->lable_list[opcode_buffer->lable_size].label_address = 0; // update in opcode_buffer_set_label
    opcode_buffer->lable_size++;


    return old_index;
}

void opcode_buffer_set_label(RVM_OpcodeBuffer* opcode_buffer, unsigned int label, unsigned int label_address) {
    debug_log_with_darkgreen_coloar("\t");
    opcode_buffer->lable_list[label].label_address = label_address;
}

void opcode_buffer_fix_label(RVM_OpcodeBuffer* opcode_buffer) {
    debug_log_with_darkgreen_coloar("\t");

    unsigned int label;
    unsigned int label_address;

    for (unsigned int i = 0; i < opcode_buffer->code_size;) {
        RVM_Byte opcode = opcode_buffer->code_list[i];
        if (opcode <= RVM_CODE_UNKNOW || opcode >= RVM_CODES_NUM) {
            fprintf(stderr, "generate vm code: opcode_buffer_fix_label(opcode is valid:%d)\n", opcode);
            exit(ERROR_CODE_GENERATE_OPCODE_ERROR);
        }
        RVM_Opcode_Info opcode_info = RVM_Opcode_Infos[opcode];

        switch (opcode) {
        case RVM_CODE_JUMP:
        case RVM_CODE_JUMP_IF_FALSE:
        case RVM_CODE_JUMP_IF_TRUE:
            label                           = (opcode_buffer->code_list[i + 1] << 8) + (opcode_buffer->code_list[i + 2]);
            label_address                   = opcode_buffer->lable_list[label].label_address;

            opcode_buffer->code_list[i + 1] = (RVM_Byte)(label_address >> 8);
            opcode_buffer->code_list[i + 2] = (RVM_Byte)(label_address & 0Xff);
            break;

        default:
            break;
        }


        switch (opcode_info.type) {
        case OPCODE_OPERAND_TYPE_0BYTE:
            i++;
            break;

        case OPCODE_OPERAND_TYPE_1BYTE:
            i += 2;
            break;

        case OPCODE_OPERAND_TYPE_2BYTE:
            i += 3;
            break;

        default:
            fprintf(stderr, "opcode_buffer_fix_label(opcode is valid:%d)\n", opcode);
            exit(ERROR_CODE_GENERATE_OPCODE_ERROR);
            break;
        }
    }
}

RVM_Opcode convert_opcode_by_rvm_type(RVM_Opcode opcode, TypeSpecifier* type) {
    debug_log_with_darkgreen_coloar("\t");
    assert(type != nullptr);

    if (!(opcode == RVM_CODE_POP_STATIC_BOOL
          || opcode == RVM_CODE_PUSH_STATIC_BOOL
          || opcode == RVM_CODE_POP_STACK_BOOL
          || opcode == RVM_CODE_PUSH_STACK_BOOL
          || opcode == RVM_CODE_PUSH_FIELD_BOOL
          || opcode == RVM_CODE_POP_FIELD_BOOL)) {
        fprintf(stderr, "convert_opcode_by_rvm_type error(opcode is valid:%d)\n", opcode);
        exit(ERROR_CODE_GENERATE_OPCODE_ERROR);
        return RVM_CODE_UNKNOW;
    }

    switch (type->kind) {
    case RING_BASIC_TYPE_BOOL:
        return opcode;
        break;
    case RING_BASIC_TYPE_INT:
        return RVM_Opcode(opcode + 1);
        break;
    case RING_BASIC_TYPE_DOUBLE:
        return RVM_Opcode(opcode + 2);
        break;
    case RING_BASIC_TYPE_STRING:
        return RVM_Opcode(opcode + 3);
        break;
    case RING_BASIC_TYPE_CLASS:
        return RVM_Opcode(opcode + 3);
        break;
    case RING_BASIC_TYPE_ARRAY:
        return RVM_Opcode(opcode + 3);
        break;

    default:
        fprintf(stderr, "generate opcode error\n");
        exit(ERROR_CODE_GENERATE_OPCODE_ERROR);
        break;
    }

    return RVM_CODE_UNKNOW;
}

unsigned int calc_runtime_stack_capacity(RVM_Byte* code_list, unsigned int code_size) {
    return 0;
}


// 这里实现完成了：但是有点bug，还未测试  因为 executer 和 rvm 有点耦合，所以这里设计的有点问题，需要重新设计
// FIXME:
void add_code_line_map(RVM_OpcodeBuffer* opcode_buffer, unsigned int line_number, unsigned int start_pc, unsigned int opcode_size) {
    if (opcode_buffer->code_line_map.empty()
        || opcode_buffer->code_line_map.rbegin()->line_number != line_number) {
        RVM_SourceCodeLineMap tmp = RVM_SourceCodeLineMap{
            nullptr,
            line_number,
            start_pc,
            opcode_size,
        };

        opcode_buffer->code_line_map.push_back(tmp);

    } else {
        opcode_buffer->code_line_map.rbegin()->opcode_size += opcode_size;
    }
}
// 这里实现完成了：但是有点bug，还未测试  因为 executer 和 rvm 有点耦合，所以这里设计的有点问题，需要重新设计
// FIXME:
void dump_code_line_map(std::vector<RVM_SourceCodeLineMap>& code_line_map) {
    printf("|------------------ CodeLineMap-Dump-begin ------------------\n");

    for (RVM_SourceCodeLineMap& code_line : code_line_map) {
        printf("source_file_name:%10s line_number:%10d start_pc:%10d size:%10d\n",
               code_line.source_file_name,
               code_line.line_number,
               code_line.opcode_begin_index,
               code_line.opcode_size);
    }

    printf("|------------------ CodeLineMap-Dump-begin ------------------\n");
}
