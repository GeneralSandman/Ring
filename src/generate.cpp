#include "ring.hpp"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>


extern RVM_Opcode_Info RVM_Opcode_Infos[];


// init Package-Executer
Package_Executer* package_executer_create(ExecuterEntry* executer_entry,
                                          char*          package_name) {

    Package_Executer* executer                = (Package_Executer*)mem_alloc(NULL_MEM_POOL, sizeof(Package_Executer));
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

// compiler 开发者使用
void print_package_executer(Package_Executer* package_executer) {
    assert(package_executer != nullptr);
    printf("|------------------ Package_Executer-Dump-begin ------------------\n");

    printf("|PackageName: %s%s%s\n", LOG_COLOR_GREEN, package_executer->package_name, LOG_COLOR_CLEAR);
    printf("|PackageIndex: %d\n", package_executer->package_index);

    printf("|FunctionList:\n");

    for (unsigned int i = 0; i < package_executer->function_size; i++) {
        printf("|\t func_name: %s%s%s\n", LOG_COLOR_YELLOW, package_executer->function_list[i].func_name, LOG_COLOR_CLEAR);
    }

    printf("|------------------ Package_Executer-Dump-end   ------------------\n\n");
}

// ring 使用者
void package_executer_dump(Package_Executer* package_executer) {
    // printf("%sPackage:    %s%s\n",
    //        LOG_COLOR_GREEN,
    //        package_executer->package_name,
    //        LOG_COLOR_CLEAR);

    // 1. dump constant
    printf("#Constants:       %d\n", package_executer->constant_pool_size);
    for (unsigned int i = 0; i < package_executer->constant_pool_size; i++) {
        printf(" ├──%6d: %s\n",
               i,
               dump_vm_constant(&(package_executer->constant_pool_list[i])).c_str());
    }
    printf("\n");


    // 2. dump global variables
    printf("#Globals:       %d\n", package_executer->global_variable_size);
    for (unsigned int i = 0; i < package_executer->global_variable_size; i++) {
        printf(" ├──%-20s %-20s\n",
               format_rvm_type_specifier(package_executer,
                                         package_executer->global_variable_list[i].type_specifier)
                   .c_str(),
               package_executer->global_variable_list[i].identifier);
    }
    printf("\n");

    // 3. dump functions
    for (unsigned int i = 0; i < package_executer->function_size; i++) {
        dump_vm_function(package_executer, nullptr, &(package_executer->function_list[i]));
    }

    // 4. dump classes
    for (unsigned int i = 0; i < package_executer->class_size; i++) {
        dump_vm_class(package_executer, &(package_executer->class_list[i]));
    }
}

// 生成 RVM 虚拟机代码
void ring_generate_vm_code(Package* package, Package_Executer* package_executer) {
    debug_generate_info_with_darkgreen("\t");

    add_global_variable(package, package_executer);
    add_functions(package, package_executer);
    add_classes(package, package_executer);
    add_top_level_code(package, package_executer);

#ifdef DEBUG_GENERATE_SUMMARY
    package_executer_dump(package_executer);
#endif
}

// 只生成主包的vm code
void ring_generate_vm_code(CompilerEntry* compiler_entry,
                           ExecuterEntry* executer_entry) {

    debug_generate_info_with_darkgreen("\t");

    Package*          main_package     = compiler_entry->main_package;
    Package_Executer* package_executer = executer_entry->main_package_executer;

    ring_generate_vm_code(main_package, package_executer);
    executer_entry->package_executer_list.push_back(package_executer);

    // for (Package* package : compiler_entry->package_list) {
    //     // FIXME: find duplicate
    //     for (Package_Executer* package_executer : executer_entry->package_executer_list) {
    //         if (str_eq(package_executer->package_name, package->package_name)) {
    //             debug_generate_info_with_darkgreen("\tpackage executer[%s] already register", package->package_name);

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

/*
 * Generate Global Variable Definition for RVM.
 *
 * 1. package->global_declaration_list is list.
 * 2. executer->global_variable_list   is array.
 */
void add_global_variable(Package* package, Package_Executer* executer) {
    debug_generate_info_with_darkgreen("\t");
    // FIXME: 在 Compiler 中大部分是链表：因为在编译的时候不确定存储空间
    // 在 Executer 中 大部分是数组，因为编译完成，存储空间的数量都已经确认了。
    if (package->global_declaration_list.empty()) {
        return;
    }

    executer->global_variable_size = package->global_declaration_list.size();
    executer->global_variable_list = (RVM_Variable*)mem_alloc(NULL_MEM_POOL,
                                                              executer->global_variable_size * sizeof(RVM_Variable));

    Declaration* pos               = nullptr;
    unsigned int i                 = 0;
    for (pos = package->global_declaration_list[i];
         i < package->global_declaration_list.size();
         i++, pos = package->global_declaration_list[i]) {
        executer->global_variable_list[i].identifier     = pos->identifier;
        executer->global_variable_list[i].type_specifier = (RVM_TypeSpecifier*)mem_alloc(NULL_MEM_POOL,
                                                                                         sizeof(RVM_TypeSpecifier));

        type_specifier_deep_copy(executer->global_variable_list[i].type_specifier, pos->type_specifier);
    }
}

// 添加函数定义
void add_functions(Package* package, Package_Executer* executer) {
    debug_generate_info_with_darkgreen("\t");

    executer->function_size = package->function_list.size();
    executer->function_list = (RVM_Function*)mem_alloc(NULL_MEM_POOL,
                                                       sizeof(RVM_Function) * executer->function_size);

    unsigned int i          = 0;
    // 暂时只处理 native function
    for (Function* pos : package->function_list) {
        copy_function(executer, &(executer->function_list[i]), pos);
        // 注册main函数
        if (str_eq(pos->function_name, "main")) {
            // printf("find main:%d\n", i);
            executer->main_func_index = i;
        }
        i++;
    }
}

void add_classes(Package* package, Package_Executer* executer) {
    debug_generate_info_with_darkgreen("\t");

    executer->class_size = package->class_definition_list.size();
    executer->class_list = (RVM_ClassDefinition*)mem_alloc(NULL_MEM_POOL,
                                                           sizeof(RVM_ClassDefinition) * executer->class_size);

    unsigned int i       = 0;
    for (ClassDefinition* pos : package->class_definition_list) {
        class_def_deep_copy(executer, &executer->class_list[i], pos);
        i++;
    }
}


/*
 * Deep copy from ClassDefinition to RVM_ClassDefinition
 *
 * front-end -> back-end
 * front-end: RVM_ClassDefinition
 * back-end:  RVM_ClassDefinition
 *
 * TODO: field is shallow copy
 */
void class_def_deep_copy(Package_Executer*    executer,
                         RVM_ClassDefinition* dst,
                         ClassDefinition*     src) {
    debug_generate_info_with_darkgreen("\t");

    dst->source_file            = src->source_file;
    dst->start_line_number      = src->start_line_number;
    dst->end_line_number        = src->end_line_number;
    dst->identifier             = src->identifier;
    dst->field_size             = 0;
    dst->field_list             = nullptr;
    dst->method_size            = 0;
    dst->method_list            = nullptr;

    ClassMemberDeclaration* pos = src->member;
    for (; pos != nullptr; pos = pos->next) {
        if (pos->type == MEMBER_FIELD) {
            dst->field_size++;
        } else if (pos->type == MEMBER_METHOD) {
            dst->method_size++;
        }
    }

    // error-report ERROR_TOO_MANY_FIELDS_IN_CLASS
    if (dst->field_size > 255) {
        DEFINE_ERROR_REPORT_STR;

        snprintf(compile_err_buf, sizeof(compile_err_buf),
                 "class `%s` has %d fields, greater than 255; E:%d.",
                 dst->identifier, dst->field_size,
                 ERROR_TOO_MANY_FIELDS_IN_CLASS);
        snprintf(compile_adv_buf, sizeof(compile_adv_buf),
                 "delete useless field of class `%s`.",
                 dst->identifier);

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = get_package_unit(),
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(dst->start_line_number),
            .line_number             = dst->start_line_number,
            .column_number           = package_unit_get_column_number(),
            .error_message           = std::string(compile_err_buf),
            .advice                  = std::string(compile_adv_buf),
            .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
            .ring_compiler_file      = (char*)__FILE__,
            .ring_compiler_file_line = __LINE__,
        };
        ring_compile_error_report(&context);
    }

    // error-report ERROR_TOO_MANY_METHODS_IN_CLASS
    if (dst->method_size > 255) {
        DEFINE_ERROR_REPORT_STR;

        snprintf(compile_err_buf, sizeof(compile_err_buf),
                 "class `%s` has %d methods, greater than 255; E:%d.",
                 dst->identifier, dst->method_size,
                 ERROR_TOO_MANY_METHODS_IN_CLASS);
        snprintf(compile_adv_buf, sizeof(compile_adv_buf),
                 "delete useless field of class `%s`.",
                 dst->identifier);

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = get_package_unit(),
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(dst->start_line_number),
            .line_number             = dst->start_line_number,
            .column_number           = package_unit_get_column_number(),
            .error_message           = std::string(compile_err_buf),
            .advice                  = std::string(compile_adv_buf),
            .report_type             = ERROR_REPORT_TYPE_COLL_ERR,
            .ring_compiler_file      = (char*)__FILE__,
            .ring_compiler_file_line = __LINE__,
        };
        ring_compile_error_report(&context);
    }

    dst->field_list           = (RVM_Field*)mem_alloc(NULL_MEM_POOL, sizeof(RVM_Field) * dst->field_size);
    dst->method_list          = (RVM_Method*)mem_alloc(NULL_MEM_POOL, sizeof(RVM_Method) * dst->method_size);

    unsigned int field_index  = 0;
    unsigned int method_index = 0;
    pos                       = src->member;
    for (; pos != nullptr; pos = pos->next) {
        if (pos->type == MEMBER_FIELD) {
            copy_field(executer, &dst->field_list[field_index], pos->u.field);
            field_index++;
        } else if (pos->type == MEMBER_METHOD) {
            copy_method(executer, &dst->method_list[method_index], pos->u.method);
            method_index++;
        }
    }
}

void copy_function(Package_Executer* executer, RVM_Function* dst, Function* src) {
    debug_generate_info_with_darkgreen("\t");

    dst->source_file       = src->source_file;
    dst->start_line_number = src->start_line_number;
    dst->end_line_number   = src->end_line_number;
    dst->func_name         = src->function_name;

    if (src->type == FUNCTION_TYPE_NATIVE) {
        dst->type                = RVM_FUNCTION_TYPE_NATIVE;
        dst->parameter_size      = src->parameter_list_size;
        dst->parameter_list      = nullptr; // TODO:
        dst->local_variable_size = 0;
        dst->local_variable_list = nullptr; // TODO:
    } else if (src->type == FUNCTION_TYPE_DERIVE) {
        dst->type                = RVM_FUNCTION_TYPE_DERIVE;

        dst->parameter_size      = src->parameter_list_size;
        dst->parameter_list      = (RVM_LocalVariable*)mem_alloc(NULL_MEM_POOL,
                                                                 sizeof(RVM_LocalVariable) * dst->parameter_size);

        dst->local_variable_size = src->block->declaration_list_size;
        dst->local_variable_list = (RVM_LocalVariable*)mem_alloc(NULL_MEM_POOL,
                                                                 sizeof(RVM_LocalVariable) * dst->local_variable_size);
        dst->u.derive_func       = (DeriveFunction*)mem_alloc(NULL_MEM_POOL, sizeof(DeriveFunction));

        // deep copy function parameters
        unsigned int i     = 0;
        Parameter*   param = src->parameter_list;
        for (; param != nullptr; param = param->next, i++) {
            dst->parameter_list[i].identifier     = param->identifier;
            dst->parameter_list[i].type_specifier = (RVM_TypeSpecifier*)mem_alloc(NULL_MEM_POOL,
                                                                                  sizeof(RVM_TypeSpecifier));

            type_specifier_deep_copy(dst->parameter_list[i].type_specifier, param->type_specifier);
        }


        // deep copy local variable
        Declaration* pos = src->block->declaration_list;
        i                = 0;
        for (; pos != nullptr; pos = pos->next, i++) {
            dst->local_variable_list[i].identifier     = pos->identifier;
            dst->local_variable_list[i].type_specifier = (RVM_TypeSpecifier*)mem_alloc(NULL_MEM_POOL,
                                                                                       sizeof(RVM_TypeSpecifier));

            type_specifier_deep_copy(dst->local_variable_list[i].type_specifier, pos->type_specifier);
        }
    }

    generate_code_from_function_definition(executer, dst, src);

    dst->estimate_runtime_stack_capacity = 0;
}


void copy_method(Package_Executer* executer, RVM_Method* dst, MethodMember* src) {
    debug_generate_info_with_darkgreen("\t");

    dst->identifier                        = src->identifier;
    dst->rvm_function                      = (RVM_Function*)mem_alloc(NULL_MEM_POOL, sizeof(RVM_Function));

    dst->rvm_function->source_file         = src->source_file;
    dst->rvm_function->start_line_number   = src->start_line_number;
    dst->rvm_function->end_line_number     = src->end_line_number;
    dst->rvm_function->func_name           = src->identifier;
    dst->rvm_function->type                = RVM_FUNCTION_TYPE_DERIVE;

    dst->rvm_function->parameter_size      = src->parameter_list_size;
    dst->rvm_function->parameter_list      = (RVM_LocalVariable*)mem_alloc(NULL_MEM_POOL,
                                                                           sizeof(RVM_LocalVariable) * dst->rvm_function->parameter_size);

    dst->rvm_function->local_variable_size = src->block->declaration_list_size;
    dst->rvm_function->local_variable_list = (RVM_LocalVariable*)mem_alloc(NULL_MEM_POOL,
                                                                           sizeof(RVM_LocalVariable) * dst->rvm_function->local_variable_size);

    dst->rvm_function->u.derive_func       = (DeriveFunction*)mem_alloc(NULL_MEM_POOL, sizeof(DeriveFunction));

    // deep copy method parameters
    unsigned int i     = 0;
    Parameter*   param = src->parameter_list;
    for (; param != nullptr; param = param->next, i++) {
        dst->rvm_function->parameter_list[i].identifier     = param->identifier;
        dst->rvm_function->parameter_list[i].type_specifier = (RVM_TypeSpecifier*)mem_alloc(NULL_MEM_POOL,
                                                                                            sizeof(RVM_TypeSpecifier));

        type_specifier_deep_copy(dst->rvm_function->parameter_list[i].type_specifier, param->type_specifier);
    }

    // deep copy local variable
    Declaration* pos = src->block->declaration_list;
    i                = 0;
    for (; pos != nullptr; pos = pos->next, i++) {
        dst->rvm_function->local_variable_list[i].identifier     = pos->identifier;
        dst->rvm_function->local_variable_list[i].type_specifier = (RVM_TypeSpecifier*)mem_alloc(NULL_MEM_POOL,
                                                                                                 sizeof(RVM_TypeSpecifier));

        type_specifier_deep_copy(dst->rvm_function->local_variable_list[i].type_specifier, pos->type_specifier);
    }

    if (src->block != nullptr)
        generate_code_from_method_definition(executer, dst, src);
}

void copy_field(Package_Executer* executer, RVM_Field* dst, FieldMember* src) {
    dst->identifier     = src->identifier;

    dst->type_specifier = (RVM_TypeSpecifier*)mem_alloc(NULL_MEM_POOL,
                                                        sizeof(RVM_TypeSpecifier));

    type_specifier_deep_copy(dst->type_specifier, src->type_specifier);
}

void add_top_level_code(Package* package, Package_Executer* executer) {
    debug_generate_info_with_darkgreen("\t");

    // FIXME: executer->main_func_index is unsigned int
    if (executer->main_func_index != -1) {
        // printf("executer->main_func_index\n");
        // 生成一下字节码
        // 找到main函数
        // 调用 main 函数
        // exit code
        RVM_OpcodeBuffer* opcode_buffer = new_opcode_buffer();
        // FIXME: (package->compiler_entry->package_list.size() - 1) << 8) 这里要修正一下
        generate_vmcode(executer, opcode_buffer,
                        RVM_CODE_ARGUMENT_NUM, 0, 0);
        generate_vmcode(executer, opcode_buffer,
                        RVM_CODE_PUSH_FUNC,
                        ((package->compiler_entry->package_list.size() - 1) << 8) | executer->main_func_index, 0);
        generate_vmcode(executer, opcode_buffer,
                        RVM_CODE_INVOKE_FUNC, 0, 0);
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

void generate_code_from_function_definition(Package_Executer* executer,
                                            RVM_Function* dst, Function* src) {

    debug_generate_info_with_darkgreen("\t");
    if (src->block == nullptr) {
        return;
    }

    RVM_OpcodeBuffer* opcode_buffer = new_opcode_buffer();
    generate_vmcode_from_statement_list(executer, src->block, src->block->statement_list, opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_FUNCTION_FINISH, 0, src->end_line_number);

    opcode_buffer_fix_label(opcode_buffer);


    dst->u.derive_func->code_list     = opcode_buffer->code_list;
    dst->u.derive_func->code_size     = opcode_buffer->code_size;
    dst->u.derive_func->code_line_map = opcode_buffer->code_line_map;
    // dst->local_variable_size          = 0;
    // dst->local_variable_list          = nullptr;


#ifdef DEBUG_GENERATE_OUTPUT_VMCODE
    dump_vm_function(dst);
#endif
}

void generate_code_from_method_definition(Package_Executer* executer,
                                          RVM_Method* dst, MethodMember* src) {

    debug_generate_info_with_darkgreen("\t");

    RVM_OpcodeBuffer* opcode_buffer = new_opcode_buffer();
    generate_vmcode_from_statement_list(executer,
                                        src->block,
                                        src->block->statement_list,
                                        opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_FUNCTION_FINISH, 0, src->start_line_number);

    opcode_buffer_fix_label(opcode_buffer);

    dst->rvm_function->u.derive_func->code_list     = opcode_buffer->code_list;
    dst->rvm_function->u.derive_func->code_size     = opcode_buffer->code_size;
    dst->rvm_function->u.derive_func->code_line_map = opcode_buffer->code_line_map;
    // TODO: dump method detail
}

void vm_executer_dump(Package_Executer* executer) {
    debug_generate_info_with_darkgreen("\t");
    // CLEAR_SCREEN;
    ring_vm_constantpool_dump(executer);
    ring_vm_code_dump(nullptr, executer->code_list, executer->code_size, 0, 60, 1);
}

RVM_OpcodeBuffer* new_opcode_buffer() {
    debug_generate_info_with_darkgreen("\t");
    RVM_OpcodeBuffer* buffer = (RVM_OpcodeBuffer*)mem_alloc(NULL_MEM_POOL, sizeof(RVM_OpcodeBuffer));

    buffer->code_list        = nullptr;
    buffer->code_size        = 0;
    buffer->code_capacity    = 0;
    buffer->lable_list       = std::vector<RVM_LabelTable>{};
    buffer->code_line_map    = std::vector<RVM_SourceCodeLineMap>{};

    buffer->lable_list.reserve(1024);
    return buffer;
}

void generate_vmcode_from_block(Package_Executer* executer,
                                Block*            block,
                                RVM_OpcodeBuffer* opcode_buffer) {

    if (block == nullptr) {
        return;
    }
    debug_generate_info_with_darkgreen("\t");
    generate_vmcode_from_statement_list(executer, block, block->statement_list, opcode_buffer);
}

void generate_vmcode_from_statement_list(Package_Executer* executer,
                                         Block*            block,
                                         Statement*        statement_list,
                                         RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    for (Statement* statement = statement_list; statement != nullptr; statement = statement->next) {
        switch (statement->type) {
        case STATEMENT_TYPE_EXPRESSION:
            generate_vmcode_from_expression(executer, statement->u.expression, opcode_buffer);
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

void generate_vmcode_from_if_statement(Package_Executer* executer,
                                       IfStatement*      if_statement,
                                       RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    if (if_statement == nullptr) {
        return;
    }

    unsigned int if_false_jump_label = 0;
    unsigned int if_end_label        = 0;

    generate_vmcode_from_expression(executer, if_statement->condition_expression, opcode_buffer);

    if_false_jump_label = opcode_buffer_get_label(opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, if_false_jump_label, if_statement->line_number);

    generate_vmcode_from_block(executer, if_statement->if_block, opcode_buffer);

    if_end_label = opcode_buffer_get_label(opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, if_end_label, if_statement->line_number);


    opcode_buffer_set_label(opcode_buffer, if_false_jump_label, opcode_buffer->code_size);

    // handle elseif list
    ElseIfStatement* pos = if_statement->elseif_list;
    for (; pos; pos = pos->next) {
        generate_vmcode_from_expression(executer, pos->condition_expression, opcode_buffer);

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

void generate_vmcode_from_for_statement(Package_Executer* executer,
                                        ForStatement*     for_statement,
                                        RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    if (for_statement == nullptr) {
        return;
    }

    if (for_statement->type == FOR_STATEMENT_TYPE_TERNARY) {
        generate_vmcode_from_for_ternary_statement(executer, for_statement, opcode_buffer);
    } else if (for_statement->type == FOR_STATEMENT_TYPE_RANGE) {
        generate_vmcode_from_for_range_statement(executer, for_statement, opcode_buffer);
    } else {
        // TODO: error report
    }
}

// TODO: 暂时不支持 break continue
void generate_vmcode_from_for_ternary_statement(Package_Executer* executer,
                                                ForStatement*     for_statement,
                                                RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    assert(for_statement != nullptr);
    assert(for_statement->type == FOR_STATEMENT_TYPE_TERNARY);
    assert(for_statement->u.ternary_statement != nullptr);

    unsigned int         end_label         = 0;
    unsigned int         loop_label        = 0;
    unsigned int         continue_label    = 0;

    ForTernaryStatement* ternary_statement = for_statement->u.ternary_statement;

    // Step-1:
    if (ternary_statement->init_expression) {
        generate_vmcode_from_expression(executer, ternary_statement->init_expression, opcode_buffer);
    }
    loop_label = opcode_buffer_get_label(opcode_buffer);
    opcode_buffer_set_label(opcode_buffer, loop_label, opcode_buffer->code_size);

    // Step-2:
    end_label = opcode_buffer_get_label(opcode_buffer);
    if (ternary_statement->condition_expression) {
        generate_vmcode_from_expression(executer, ternary_statement->condition_expression, opcode_buffer);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, end_label, ternary_statement->condition_expression->line_number);
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
    if (ternary_statement->post_expression) {
        generate_vmcode_from_expression(executer, ternary_statement->post_expression, opcode_buffer);
    }

    // Step-5:
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, loop_label, for_statement->line_number);


    // Step-End:

    opcode_buffer_set_label(opcode_buffer, end_label, opcode_buffer->code_size);
}

void generate_vmcode_from_for_range_statement(Package_Executer* executer,
                                              ForStatement*     for_statement,
                                              RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    assert(for_statement != nullptr);
    assert(for_statement->type == FOR_STATEMENT_TYPE_RANGE);
    assert(for_statement->u.range_statement != nullptr);


    unsigned int       end_label       = 0;
    unsigned int       loop_label      = 0;
    unsigned int       continue_label  = 0;

    ForRangeStatement* range_statement = for_statement->u.range_statement;

    // step-1. range_call
    //       push array-object & array-iter to runtime_stack
    if (range_statement->operand->type != EXPRESSION_TYPE_IDENTIFIER) {
        // TODO: error report
    }

    // push array-object
    generate_vmcode_from_identifier_expression(executer, range_statement->operand->u.identifier_expression, opcode_buffer);
    // push array-iterator
    // FIXME: 这里数组的数量收到限制了
    generate_vmcode(executer, opcode_buffer,
                    RVM_CODE_PUSH_INT_2BYTE, 0,
                    range_statement->operand->u.identifier_expression->line_number);


    loop_label = opcode_buffer_get_label(opcode_buffer);
    opcode_buffer_set_label(opcode_buffer, loop_label, opcode_buffer->code_size);

    // step-2. range_loop
    //       [RVM_CODE_FOR_RANGE_INIT]: push index & value to runtime_stack
    //       [RVM_CODE_FOR_RANGE_INIT]: add array-iter
    //       pop -> index & value

    end_label = opcode_buffer_get_label(opcode_buffer);
    // generate_vmcode(executer, opcode_buffer,
    //                 RVM_CODE_FOR_RANGE_INIT, end_label,
    //                 range_statement->operand->u.identifier_expression->line_number);


    // generate_vmcode(executer, opcode_buffer,
    //                 RVM_CODE_DUPLICATE, (0<<8) | 1 ,
    //                 range_statement->operand->u.identifier_expression->line_number);


    Declaration* declaration = range_statement->operand->u.identifier_expression->u.declaration;
    if (declaration == nullptr) {
        ring_error_report("invalid range operand:%s\n", range_statement->operand->u.identifier_expression->identifier);
    }
    if (declaration->type_specifier->sub->kind == RING_BASIC_TYPE_BOOL) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_FOR_RANGE_ARRAY_BOOL, end_label, range_statement->operand->u.identifier_expression->line_number);
    } else if (declaration->type_specifier->sub->kind == RING_BASIC_TYPE_INT) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_FOR_RANGE_ARRAY_INT, end_label, range_statement->operand->u.identifier_expression->line_number);
    } else if (declaration->type_specifier->sub->kind == RING_BASIC_TYPE_DOUBLE) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_FOR_RANGE_ARRAY_DOUBLE, end_label, range_statement->operand->u.identifier_expression->line_number);
    } else if (declaration->type_specifier->sub->kind == RING_BASIC_TYPE_STRING) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_FOR_RANGE_ARRAY_STRING, end_label, range_statement->operand->u.identifier_expression->line_number);
    } else if (declaration->type_specifier->sub->kind == RING_BASIC_TYPE_CLASS) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_FOR_RANGE_ARRAY_CLASS_OB, end_label, range_statement->operand->u.identifier_expression->line_number);
    } else {
        ring_error_report("error: range expression only support bool[] int[] double[] string[]\n");
    }


    generate_pop_to_leftvalue_reverse(executer, range_statement->left, opcode_buffer);

    // Step-3:
    if (for_statement->block) {
        for_statement->block->block_labels.break_label = end_label;
        for_statement->block->block_labels.continue_label =
            continue_label = opcode_buffer_get_label(opcode_buffer);

        generate_vmcode_from_block(executer, for_statement->block, opcode_buffer);
    }

    opcode_buffer_set_label(opcode_buffer, continue_label, opcode_buffer->code_size);


    // step-4. jump to range_loop
    generate_vmcode(executer, opcode_buffer,
                    RVM_CODE_JUMP, loop_label,
                    range_statement->operand->u.identifier_expression->line_number);

    // step-5. range_finish
    opcode_buffer_set_label(opcode_buffer, end_label, opcode_buffer->code_size);

    generate_vmcode(executer, opcode_buffer,
                    RVM_CODE_FOR_RANGE_FINISH, 0,
                    range_statement->operand->u.identifier_expression->line_number);
}


// TODO: 暂时不支持 break continue
void generate_vmcode_from_dofor_statement(Package_Executer* executer,
                                          DoForStatement*   dofor_statement,
                                          RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    if (dofor_statement == nullptr) {
        return;
    }
    unsigned int end_label      = 0;
    unsigned int loop_label     = 0;
    unsigned int continue_label = 0;


    // Step-1:
    if (dofor_statement->init_expression) {
        generate_vmcode_from_expression(executer, dofor_statement->init_expression, opcode_buffer);
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
        generate_vmcode_from_expression(executer, dofor_statement->condition_expression, opcode_buffer);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, end_label, dofor_statement->condition_expression->line_number);
    }


    // Step-4:
    if (dofor_statement->post_expression) {
        generate_vmcode_from_expression(executer, dofor_statement->post_expression, opcode_buffer);
    }

    // Step-5;
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, loop_label, dofor_statement->line_number);

    // Step-End;
    opcode_buffer_set_label(opcode_buffer, end_label, opcode_buffer->code_size);
}

void generate_vmcode_from_break_statement(Package_Executer* executer,
                                          Block*            block,
                                          BreakStatement*   break_statement,
                                          RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
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
        ring_error_report("generate vm code of `break`\n");
    }

    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, pos->block_labels.break_label, break_statement->line_number);
}

void generate_vmcode_from_continue_statement(Package_Executer*  executer,
                                             Block*             block,
                                             ContinueStatement* continue_statement,
                                             RVM_OpcodeBuffer*  opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
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
        ring_error_report("generate vm code of `continue`\n");
    }

    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, pos->block_labels.continue_label, continue_statement->line_number);
}

void generate_vmcode_from_return_statement(Package_Executer* executer,
                                           Block*            block,
                                           ReturnStatement*  return_statement,
                                           RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    if (return_statement == nullptr) {
        return;
    }


    Expression* pos;
    for (pos = return_statement->return_list; pos; pos = pos->next) {
        generate_vmcode_from_expression(executer, pos, opcode_buffer);
    }


    generate_vmcode(executer, opcode_buffer, RVM_CODE_RETURN, return_statement->return_list_size, return_statement->line_number);
}

void generate_vmcode_from_initializer(Package_Executer* executer,
                                      Block*            block,
                                      Declaration*      declaration,
                                      RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    if (declaration == nullptr) {
        return;
    }

    Declaration* pos = declaration;
    for (; pos; pos = pos->next) {
        if (pos->initializer) {
            generate_vmcode_from_expression(executer, pos->initializer, opcode_buffer);
            RVM_Opcode opcode = RVM_CODE_UNKNOW;
            if (pos->is_local) {
                // 局部变量
                opcode = convert_opcode_by_rvm_type(RVM_CODE_POP_STACK_BOOL, pos->type_specifier);
            } else {
                // 全局变量
                opcode = convert_opcode_by_rvm_type(RVM_CODE_POP_STATIC_BOOL, pos->type_specifier);
            }
            generate_vmcode(executer, opcode_buffer, opcode, pos->variable_index, declaration->line_number);
        }
    }
}

void generate_vmcode_from_jump_tag_statement(Package_Executer* executer, Block* block, JumpTagStatement* jump_tag_statement, RVM_OpcodeBuffer* opcode_buffer) {
    debug_generate_info_with_darkgreen("\t");
    if (jump_tag_statement == nullptr) {
        return;
    }
}

void generate_vmcode_from_expression(Package_Executer* executer,
                                     Expression*       expression,
                                     RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
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

    case EXPRESSION_TYPE_UNITARY_INCREASE:
    case EXPRESSION_TYPE_UNITARY_DECREASE:
        generate_vmcode_from_increase_decrease_expression(executer, expression, opcode_buffer);
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

    case EXPRESSION_TYPE_CLASS_OBJECT_LITERAL:
        generate_vmcode_from_class_object_literal_expreesion(executer, expression->u.class_object_literal_expression, opcode_buffer);
        break;

    default:
        break;
    }
}

void generate_vmcode_from_assign_expression(Package_Executer* executer,
                                            AssignExpression* expression,
                                            RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    assert(expression != nullptr);


    // += -= *= /= %= .=
    if (expression->type == ASSIGN_EXPRESSION_TYPE_ADD_ASSIGN
        || expression->type == ASSIGN_EXPRESSION_TYPE_SUB_ASSIGN
        || expression->type == ASSIGN_EXPRESSION_TYPE_MUL_ASSIGN
        || expression->type == ASSIGN_EXPRESSION_TYPE_DIV_ASSIGN
        || expression->type == ASSIGN_EXPRESSION_TYPE_MOD_ASSIGN
        || expression->type == ASSIGN_EXPRESSION_TYPE_CONCAT_ASSIGN) {
        generate_vmcode_from_expression(executer, expression->left, opcode_buffer);
    }


    // operand
    unsigned int operand_num = 0;
    Expression*  pos         = nullptr;
    for (pos = expression->operand; pos; pos = pos->next, operand_num++) {
        generate_vmcode_from_expression(executer, pos, opcode_buffer);
    }


    // += -= *= /= %= .=
    unsigned int opcode_offset = 0;
    if (expression->operand->convert_type != nullptr && expression->operand->convert_type->kind == RING_BASIC_TYPE_DOUBLE) {
        opcode_offset += 1;
    }
    switch (expression->type) {
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


    // dp
    for (unsigned int i = 0; i < operand_num; i++) {
        unsigned int offset  = i + 1;
        unsigned int operand = (offset << 8) | offset;
        // printf("-RVM_CODE_DEEP_COPY: i:%d offset: %d, dst_offset: %d, src_offset: %d, operand: %d, operand: %X\n", i, offset, offset, offset, operand, operand);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_DEEP_COPY, operand, expression->line_number);
    }


    // assign
    if (expression->type == ASSIGN_EXPRESSION_TYPE_MULTI_ASSIGN) {
        generate_pop_to_leftvalue_reverse(executer, expression->left, opcode_buffer);
    } else {
        generate_pop_to_leftvalue(executer, expression->left, opcode_buffer);
    }
}

void generate_pop_to_leftvalue_reverse(Package_Executer* executer,
                                       Expression*       expression,
                                       RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    if (expression == nullptr) {
        return;
    }

    generate_pop_to_leftvalue_reverse(executer, expression->next, opcode_buffer);
    generate_pop_to_leftvalue(executer, expression, opcode_buffer);
}

void generate_pop_to_leftvalue(Package_Executer* executer,
                               Expression*       expression,
                               RVM_OpcodeBuffer* opcode_buffer) {

    if (expression->type == EXPRESSION_TYPE_IDENTIFIER) {
        generate_pop_to_leftvalue_identifier(executer, expression->u.identifier_expression, opcode_buffer);
    } else if (expression->type == EXPRESSION_TYPE_MEMBER) {
        generate_pop_to_leftvalue_member(executer, expression->u.member_expression, opcode_buffer);
    } else if (expression->type == EXPRESSION_TYPE_ARRAY_INDEX) {
        generate_pop_to_leftvalue_array_index(executer, expression->u.array_index_expression, opcode_buffer);
    } else {
        ring_error_report("not support assign to left-value\n");
    }
}

/*
 * 给变量赋值
 */
void generate_pop_to_leftvalue_identifier(Package_Executer*     executer,
                                          IdentifierExpression* identifier_expression,
                                          RVM_OpcodeBuffer*     opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    assert(identifier_expression != nullptr);

    Declaration* declaration    = identifier_expression->u.declaration;

    unsigned int variable_index = declaration->variable_index;
    RVM_Opcode   opcode         = RVM_CODE_UNKNOW;
    if (declaration->is_local) {
        opcode = convert_opcode_by_rvm_type(RVM_CODE_POP_STACK_BOOL, declaration->type_specifier);
    } else {
        opcode = convert_opcode_by_rvm_type(RVM_CODE_POP_STATIC_BOOL, declaration->type_specifier);
    }
    generate_vmcode(executer, opcode_buffer, opcode, variable_index, identifier_expression->line_number);
}

/*
 * 用于给成员变量赋值
 */
void generate_pop_to_leftvalue_member(Package_Executer* executer,
                                      MemberExpression* member_expression,
                                      RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    if (member_expression == nullptr) {
        return;
    }

    RVM_Opcode opcode        = RVM_CODE_UNKNOW;
    opcode                   = convert_opcode_by_rvm_type(RVM_CODE_POP_FIELD_BOOL, member_expression->member_declaration->u.field->type_specifier);
    unsigned int field_index = member_expression->member_declaration->u.field->index_of_class;

    generate_vmcode_from_expression(executer, member_expression->object_expression, opcode_buffer);
    generate_vmcode(executer, opcode_buffer, opcode, field_index, member_expression->line_number);
}

/*
 * 给数组元素赋值
 */
void generate_pop_to_leftvalue_array_index(Package_Executer*     executer,
                                           ArrayIndexExpression* array_index_expression,
                                           RVM_OpcodeBuffer*     opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    assert(array_index_expression != nullptr);
    assert(array_index_expression->array_expression != nullptr);
    assert(array_index_expression->index_expression != nullptr);

    Declaration* declaration = array_index_expression->array_expression->u.identifier_expression->u.declaration;
    if (declaration == nullptr) {
        ring_error_report("invalid operator[] in identifier:%s\n",
                          array_index_expression->array_expression->u.identifier_expression->identifier);
    }
    if (declaration->type_specifier->kind != RING_BASIC_TYPE_ARRAY) {
        ring_error_report("invalid declaration in operation[] identifier:%s\n",
                          array_index_expression->array_expression->u.identifier_expression->identifier);
    }

    // push array-object to runtime_stack
    RVM_Opcode opcode = RVM_CODE_UNKNOW;
    if (declaration->is_local) {
        opcode = RVM_CODE_PUSH_STACK_ARRAY;
    } else {
        opcode = RVM_CODE_PUSH_STATIC_ARRAY;
    }
    generate_vmcode(executer, opcode_buffer, opcode, declaration->variable_index, array_index_expression->line_number);

    // push index-expression to runtime_stack
    // generate_vmcode_from_expression(executer, index, opcode_buffer, 0);


    SubDimensionExpression* pos_index = array_index_expression->index_expression->dimension_list;
    for (unsigned int i = 0; i < declaration->type_specifier->dimension - 1; i++, pos_index = pos_index->next) {
        generate_vmcode_from_expression(executer, pos_index->num_expression, opcode_buffer);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_ARRAY_A, 0, array_index_expression->line_number);
    }

    // 最后一个纬度
    generate_vmcode_from_expression(executer, pos_index->num_expression, opcode_buffer);


    // assign
    if (declaration->type_specifier->sub->kind == RING_BASIC_TYPE_BOOL) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_POP_ARRAY_BOOL, 0, array_index_expression->line_number);
    } else if (declaration->type_specifier->sub->kind == RING_BASIC_TYPE_INT) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_POP_ARRAY_INT, 0, array_index_expression->line_number);
    } else if (declaration->type_specifier->sub->kind == RING_BASIC_TYPE_DOUBLE) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_POP_ARRAY_DOUBLE, 0, array_index_expression->line_number);
    } else if (declaration->type_specifier->sub->kind == RING_BASIC_TYPE_STRING) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_POP_ARRAY_STRING, 0, array_index_expression->line_number);
    } else if (declaration->type_specifier->sub->kind == RING_BASIC_TYPE_CLASS) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_POP_ARRAY_CLASS_OB, 0, array_index_expression->line_number);
    } else {
        ring_error_report("error: assign to item of array only support bool[] int[] double[] string[] class[]\n");
    }
}

void generate_vmcode_from_logical_expression(Package_Executer* executer,
                                             BinaryExpression* expression,
                                             RVM_OpcodeBuffer* opcode_buffer,
                                             RVM_Opcode        opcode) {

    debug_generate_info_with_darkgreen("\t");
    if (expression == nullptr) {
        return;
    }

    Expression*  left      = expression->left_expression;
    Expression*  right     = expression->right_expression;
    unsigned int end_label = 0;

    if (opcode == RVM_CODE_LOGICAL_AND) {
        generate_vmcode_from_expression(executer, left, opcode_buffer);

        generate_vmcode(executer, opcode_buffer, RVM_CODE_DUPLICATE, (0 << 8) | 1, expression->line_number);
        end_label = opcode_buffer_get_label(opcode_buffer);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, end_label, expression->line_number);

        generate_vmcode_from_expression(executer, right, opcode_buffer);

        generate_vmcode(executer, opcode_buffer, opcode, 0, expression->line_number);
    } else if (opcode == RVM_CODE_LOGICAL_OR) {
        generate_vmcode_from_expression(executer, left, opcode_buffer);

        generate_vmcode(executer, opcode_buffer, RVM_CODE_DUPLICATE, (0 << 8) | 1, expression->line_number);
        end_label = opcode_buffer_get_label(opcode_buffer);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_TRUE, end_label, expression->line_number);

        generate_vmcode_from_expression(executer, right, opcode_buffer);

        generate_vmcode(executer, opcode_buffer, opcode, 0, expression->line_number);
    }

    opcode_buffer_set_label(opcode_buffer, end_label, opcode_buffer->code_size);
}

void generate_vmcode_from_binary_expression(Package_Executer* executer,
                                            BinaryExpression* expression,
                                            RVM_OpcodeBuffer* opcode_buffer,
                                            RVM_Opcode        opcode) {

    debug_generate_info_with_darkgreen("\t");
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
    generate_vmcode_from_expression(executer, left, opcode_buffer);
    generate_vmcode_from_expression(executer, right, opcode_buffer);

    generate_vmcode(executer, opcode_buffer, opcode, 0, expression->line_number);
}

void generate_vmcode_from_increase_decrease_expression(Package_Executer* executer,
                                                       Expression*       expression,
                                                       RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    if (expression == nullptr) {
        return;
    }

    Expression* unitary_expression = expression->u.unitary_expression;
    generate_vmcode_from_expression(executer, unitary_expression, opcode_buffer);

    switch (expression->type) {
    case EXPRESSION_TYPE_UNITARY_INCREASE:
        generate_vmcode(executer, opcode_buffer, RVM_CODE_SELF_INCREASE, 0, expression->line_number);
        break;

    case EXPRESSION_TYPE_UNITARY_DECREASE:
        generate_vmcode(executer, opcode_buffer, RVM_CODE_SELF_DECREASE, 0, expression->line_number);
        break;

    default: break;
    }


    generate_pop_to_leftvalue(executer, unitary_expression, opcode_buffer);
}

void generate_vmcode_from_unitary_minus_expression(Package_Executer* executer,
                                                   Expression*       expression,
                                                   RVM_OpcodeBuffer* opcode_buffer,
                                                   RVM_Opcode        opcode) {

    debug_generate_info_with_darkgreen("\t");
    if (expression == nullptr) {
        return;
    }

    generate_vmcode_from_expression(executer, expression, opcode_buffer);

    switch (expression->type) {
    case EXPRESSION_TYPE_LITERAL_INT:
        opcode = RVM_CODE_MINUS_INT;
        break;
    case EXPRESSION_TYPE_LITERAL_DOUBLE:
        opcode = RVM_CODE_MINUS_DOUBLE;
        break;
    default: {
        // error-report ERROR_MINUS_OPER_INVALID_USE
        char error_message_buffer[1024];
        char advice_buffer[1024];
        snprintf(error_message_buffer, 1024, "%sError:%s "
                                             "minus operator only be used in int/double literal; E:%d",
                 LOG_COLOR_RED,
                 LOG_COLOR_CLEAR,
                 ERROR_MINUS_OPER_INVALID_USE);
        snprintf(advice_buffer, 1024, "%sTip:%s "
                                      "minus operator used like: -1, -1.345",
                 LOG_COLOR_YELLOW,
                 LOG_COLOR_CLEAR);

        ErrorReportContext context = {
            .package                 = nullptr,
            .package_unit            = nullptr,
            .source_file_name        = get_package_unit()->current_file_name,
            .line_content            = package_unit_get_line_content(expression->line_number),
            .line_number             = expression->line_number,
            .column_number           = 0,
            .error_message           = std::string(error_message_buffer),
            .advice                  = std::string(advice_buffer),
            .report_type             = ERROR_REPORT_TYPE_EXIT_NOW,
            .ring_compiler_file      = (char*)__FILE__,
            .ring_compiler_file_line = __LINE__,
        };
        ring_compile_error_report(&context);
    }
    // TODO: 可以将 minus运算符 运用在 非 literal上
    break;
    }

    generate_vmcode(executer, opcode_buffer, opcode, 0, expression->line_number);
}

void generate_vmcode_from_unitary_not_expression(Package_Executer* executer,
                                                 Expression*       expression,
                                                 RVM_OpcodeBuffer* opcode_buffer,
                                                 RVM_Opcode        opcode) {

    debug_generate_info_with_darkgreen("\t");
    if (expression == nullptr) {
        return;
    }

    generate_vmcode_from_expression(executer, expression, opcode_buffer);

    generate_vmcode(executer, opcode_buffer, opcode, 0, expression->line_number);
}

void generate_vmcode_from_identifier_expression(Package_Executer*     executer,
                                                IdentifierExpression* identifier_expression,
                                                RVM_OpcodeBuffer*     opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
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
            opcode = convert_opcode_by_rvm_type(RVM_CODE_PUSH_STACK_BOOL, identifier_expression->u.declaration->type_specifier);
        } else {
            opcode = convert_opcode_by_rvm_type(RVM_CODE_PUSH_STATIC_BOOL, identifier_expression->u.declaration->type_specifier);
        }
        offset = identifier_expression->u.declaration->variable_index;
        generate_vmcode(executer, opcode_buffer, opcode, offset, identifier_expression->line_number);
        break;

    case IDENTIFIER_EXPRESSION_TYPE_FUNCTION:
        // find package & function index
        package_offset = identifier_expression->u.function->package->package_index;
        offset         = identifier_expression->u.function->func_index;
        operand        = (package_offset << 8) | offset;
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_FUNC, operand, identifier_expression->line_number);
        break;

    default:
        break;
    }
}

void generate_vmcode_from_bool_expression(Package_Executer* executer,
                                          Expression*       expression,
                                          RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    if (expression == nullptr) {
        return;
    }
    if (!expression->u.bool_literal) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_BOOL, RVM_FALSE, expression->line_number);
    } else {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_BOOL, RVM_TRUE, expression->line_number);
    }
}

void generate_vmcode_from_int_expression(Package_Executer* executer,
                                         Expression*       expression,
                                         RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
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

void generate_vmcode_from_double_expression(Package_Executer* executer,
                                            Expression*       expression,
                                            RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    if (expression == nullptr) {
        return;
    }
    assert(expression->type == EXPRESSION_TYPE_LITERAL_DOUBLE);

    int constant_index = constant_pool_add_double(executer, expression->u.double_literal);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_DOUBLE, constant_index, expression->line_number);
}

void generate_vmcode_from_string_expression(Package_Executer* executer,
                                            Expression*       expression,
                                            RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    // 都放在常量区
    assert(expression->type == EXPRESSION_TYPE_LITERAL_STRING);
    int constant_index = constant_pool_add_string(executer, expression->u.string_literal);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_STRING, constant_index, expression->line_number);
}

void generate_vmcode_from_function_call_expression(Package_Executer*       executer,
                                                   FunctionCallExpression* function_call_expression,
                                                   RVM_OpcodeBuffer*       opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    if (function_call_expression == nullptr) {
        return;
    }

    Expression* function_identifier = function_call_expression->function_identifier_expression;
    if (function_identifier->type == EXPRESSION_TYPE_IDENTIFIER) {
        if (is_native_function_identifier(function_identifier->u.identifier_expression->package_posit, function_identifier->u.identifier_expression->identifier)) {
            generate_vmcode_from_native_function_call_expression(executer, function_call_expression, opcode_buffer);
            return;
        }
    }

    ArgumentList* pos                = function_call_expression->argument_list;
    unsigned int  argument_list_size = 0;
    for (; pos != nullptr; pos = pos->next) {
        generate_vmcode_from_expression(executer, pos->expression, opcode_buffer);
        argument_list_size++;
    }

    generate_vmcode(executer, opcode_buffer, RVM_CODE_ARGUMENT_NUM, argument_list_size, function_call_expression->line_number);

    generate_vmcode_from_expression(executer, function_call_expression->function_identifier_expression, opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_INVOKE_FUNC, 0, function_call_expression->line_number);
}

// native function 这个函数名起的 不太好
// 容易跟 std-package 混淆
// TODO: 这里需要重新设计一下 跟 is_native_function_identifier
void generate_vmcode_from_native_function_call_expression(Package_Executer*       executer,
                                                          FunctionCallExpression* function_call_expression,
                                                          RVM_OpcodeBuffer*       opcode_buffer) {

    ArgumentList* pos                     = nullptr;
    Expression*   function_identifier_exp = function_call_expression->function_identifier_expression;
    char*         function_identifier     = function_identifier_exp->u.identifier_expression->identifier;

    if (str_eq(function_identifier, "len")) {
        if (function_call_expression->argument_list->expression->convert_type->kind == RING_BASIC_TYPE_STRING) {
            generate_vmcode_from_expression(executer, function_call_expression->argument_list->expression, opcode_buffer);
            generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_STRING_LEN, 0, function_call_expression->line_number);
        } else if (function_call_expression->argument_list->expression->convert_type->kind == RING_BASIC_TYPE_ARRAY) {
            generate_vmcode_from_expression(executer, function_call_expression->argument_list->expression, opcode_buffer);
            generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_ARRAY_LEN, 0, function_call_expression->line_number);
        } else {
            // TODO: 应该在语义检查的过程中报错
            ring_error_report("function `len()` argument is not string or array\n");
        }
    } else if (str_eq(function_identifier, "capacity")) {
        if (function_call_expression->argument_list->expression->convert_type->kind == RING_BASIC_TYPE_STRING) {
            generate_vmcode_from_expression(executer, function_call_expression->argument_list->expression, opcode_buffer);
            generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_STRING_CAPACITY, 0, function_call_expression->line_number);
        } else if (function_call_expression->argument_list->expression->convert_type->kind == RING_BASIC_TYPE_ARRAY) {
            generate_vmcode_from_expression(executer, function_call_expression->argument_list->expression, opcode_buffer);
            generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_ARRAY_CAPACITY, 0, function_call_expression->line_number);
        } else {
            // TODO: 应该在语义检查的过程中报错
            ring_error_report("function `capacity()` argument is not string or array\n");
        }
    } else if (str_eq(function_identifier, "push")) {
        pos = function_call_expression->argument_list;
        for (; pos != nullptr; pos = pos->next) {
            generate_vmcode_from_expression(executer, pos->expression, opcode_buffer);
        }

        if (function_call_expression->argument_list->expression->convert_type->kind != RING_BASIC_TYPE_ARRAY) {
            ring_error_report("error: push() only used to append value to array\n");
        }

        if (function_call_expression->argument_list->expression->convert_type->sub->kind == RING_BASIC_TYPE_BOOL) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_ARRAY_APPEND_BOOL, 0, function_call_expression->line_number);
        } else if (function_call_expression->argument_list->expression->convert_type->sub->kind == RING_BASIC_TYPE_INT) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_ARRAY_APPEND_INT, 0, function_call_expression->line_number);
        } else if (function_call_expression->argument_list->expression->convert_type->sub->kind == RING_BASIC_TYPE_DOUBLE) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_ARRAY_APPEND_DOUBLE, 0, function_call_expression->line_number);
        } else if (function_call_expression->argument_list->expression->convert_type->sub->kind == RING_BASIC_TYPE_STRING) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_ARRAY_APPEND_STRING, 0, function_call_expression->line_number);
        } else if (function_call_expression->argument_list->expression->convert_type->sub->kind == RING_BASIC_TYPE_CLASS) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_ARRAY_APPEND_CLASS_OB, 0, function_call_expression->line_number);
        } else {
            ring_error_report("error: push() is only be used by bool[] int[] double[] string[] class[]\n");
        }

    } else if (str_eq(function_identifier, "pop")) {
        pos = function_call_expression->argument_list;
        generate_vmcode_from_expression(executer, pos->expression, opcode_buffer);

        if (pos->expression->convert_type->kind != RING_BASIC_TYPE_ARRAY) {
            ring_error_report("error: pop() only used to append value to array\n");
        }

        if (pos->expression->convert_type->sub->kind == RING_BASIC_TYPE_BOOL) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_ARRAY_POP_BOOL, 0, function_call_expression->line_number);
        } else if (pos->expression->convert_type->sub->kind == RING_BASIC_TYPE_INT) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_ARRAY_POP_INT, 0, function_call_expression->line_number);
        } else if (pos->expression->convert_type->sub->kind == RING_BASIC_TYPE_DOUBLE) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_ARRAY_POP_DOUBLE, 0, function_call_expression->line_number);
        } else if (pos->expression->convert_type->sub->kind == RING_BASIC_TYPE_STRING) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_ARRAY_POP_STRING, 0, function_call_expression->line_number);
        } else if (function_call_expression->argument_list->expression->convert_type->sub->kind == RING_BASIC_TYPE_CLASS) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_ARRAY_POP_CLASS_OB, 0, function_call_expression->line_number);
        } else {
            ring_error_report("error: pop() is only be used by bool[] int[] double[] string[] class[]\n");
        }
    } else if (str_eq(function_identifier, "to_string")) {
        pos = function_call_expression->argument_list;
        generate_vmcode_from_expression(executer, pos->expression, opcode_buffer);


        if (pos->expression->convert_type->kind == RING_BASIC_TYPE_BOOL) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_BOOL_2_STRING, 0, function_call_expression->line_number);
        } else if (pos->expression->convert_type->kind == RING_BASIC_TYPE_INT) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_INT_2_STRING, 0, function_call_expression->line_number);
        } else if (pos->expression->convert_type->kind == RING_BASIC_TYPE_DOUBLE) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_DOUBLE_2_STRING, 0, function_call_expression->line_number);
        } else {
            ring_error_report("error: to_string() only be used by bool/int/double\n");
        }
    }
}

void generate_vmcode_from_method_call_expression(Package_Executer*     executer,
                                                 MethodCallExpression* method_call_expression,
                                                 RVM_OpcodeBuffer*     opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    if (method_call_expression == nullptr) {
        return;
    }
    ArgumentList* pos                = method_call_expression->argument_list;
    unsigned int  argument_list_size = 0;
    for (; pos != nullptr; pos = pos->next) {
        generate_vmcode_from_expression(executer, pos->expression, opcode_buffer);
        argument_list_size++;
    }

    // argument
    generate_vmcode(executer, opcode_buffer, RVM_CODE_ARGUMENT_NUM, argument_list_size, method_call_expression->line_number);

    // object
    generate_vmcode_from_expression(executer, method_call_expression->object_expression, opcode_buffer);

    // generate_vmcode_from_expression(executer, function_call_expression->function_identifier_expression, opcode_buffer, 1);
    ClassMemberDeclaration* member_declaration  = method_call_expression->member_declaration;
    unsigned                member_method_index = member_declaration->u.method->index_of_class;
    generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_METHOD, member_method_index, method_call_expression->line_number);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_INVOKE_METHOD, 0, method_call_expression->line_number);
}

void generate_vmcode_from_cast_expression(Package_Executer* executer,
                                          CastExpression*   cast_expression,
                                          RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    if (cast_expression == nullptr) {
        return;
    }

    generate_vmcode_from_expression(executer, cast_expression->operand, opcode_buffer);
    // RVM_Opcode opcode = RVM_CODE_UNKNOW;

    // FIXME: derive type
    switch (cast_expression->type_specifier->kind) {
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

/*
 * 用于访问成员变量
 */
void generate_vmcode_from_member_expression(Package_Executer* executer,
                                            MemberExpression* member_expression,
                                            RVM_OpcodeBuffer* opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    if (member_expression == nullptr) {
        return;
    }

    // object
    generate_vmcode_from_expression(executer, member_expression->object_expression, opcode_buffer);

    // member
    ClassMemberDeclaration* member_declaration = member_expression->member_declaration;
    RVM_Opcode              opcode             = convert_opcode_by_rvm_type(RVM_CODE_PUSH_FIELD_BOOL, member_declaration->u.field->type_specifier);
    unsigned                member_field_index = member_declaration->u.field->index_of_class;
    generate_vmcode(executer, opcode_buffer, opcode, member_field_index, member_expression->line_number);
}

void generate_vmcode_from_ternary_condition_expression(Package_Executer*  executer,
                                                       TernaryExpression* ternary_expression,
                                                       RVM_OpcodeBuffer*  opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    assert(ternary_expression != nullptr);

    unsigned int if_false_jump_label = 0;
    unsigned int if_end_label        = 0;

    generate_vmcode_from_expression(executer, ternary_expression->condition_expression, opcode_buffer);

    if_false_jump_label = opcode_buffer_get_label(opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP_IF_FALSE, if_false_jump_label, ternary_expression->line_number);

    generate_vmcode_from_expression(executer, ternary_expression->true_expression, opcode_buffer);

    if_end_label = opcode_buffer_get_label(opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, if_end_label, ternary_expression->line_number);


    opcode_buffer_set_label(opcode_buffer, if_false_jump_label, opcode_buffer->code_size);

    generate_vmcode_from_expression(executer, ternary_expression->false_expression, opcode_buffer);
    generate_vmcode(executer, opcode_buffer, RVM_CODE_JUMP, if_end_label, ternary_expression->line_number);

    opcode_buffer_set_label(opcode_buffer, if_end_label, opcode_buffer->code_size);
}

void generate_vmcode_from_new_array_expression(Package_Executer*   executer,
                                               NewArrayExpression* new_array_expression,
                                               RVM_OpcodeBuffer*   opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    assert(new_array_expression != nullptr);
    assert(new_array_expression->dimension_expression != nullptr);

    // TODO: 继续支持多维数组
    // dimension 当前只能是1
    unsigned int dimension = new_array_expression->dimension_expression->dimension;

    // 将每个维度的size push stack
    SubDimensionExpression* pos = new_array_expression->dimension_expression->dimension_list;
    for (unsigned int i = 0; i < dimension; i++, pos = pos->next) {
        // generate_vmcode(executer, opcode_buffer,
        //                 RVM_CODE_PUSH_INT_2BYTE, pos->num,
        //                 new_array_expression->line_number);
        generate_vmcode_from_expression(executer, pos->num_expression, opcode_buffer);
    }

    // 将维度 push stack 中

    // unsigned int size = new_array_expression->dimension_expression->dimension_list->num;

    if (new_array_expression->type_specifier->kind == RING_BASIC_TYPE_BOOL) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_NEW_ARRAY_BOOL, dimension, new_array_expression->line_number);
    } else if (new_array_expression->type_specifier->kind == RING_BASIC_TYPE_INT) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_NEW_ARRAY_INT, dimension, new_array_expression->line_number);
    } else if (new_array_expression->type_specifier->kind == RING_BASIC_TYPE_DOUBLE) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_NEW_ARRAY_DOUBLE, dimension, new_array_expression->line_number);
    } else if (new_array_expression->type_specifier->kind == RING_BASIC_TYPE_STRING) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_NEW_ARRAY_STRING, dimension, new_array_expression->line_number);
    } else if (new_array_expression->type_specifier->kind == RING_BASIC_TYPE_CLASS) {
        ClassDefinition* class_definition = new_array_expression->type_specifier->u.class_type->class_definition;
        generate_vmcode(executer, opcode_buffer, RVM_CODE_NEW_ARRAY_CLASS_OB, (dimension << 8) | (class_definition->class_index), new_array_expression->line_number);
    } else {
        ring_error_report("error: new array only support bool[] int[] double[] string[] class[]\n");
    }
}

void generate_vmcode_from_class_object_literal_expreesion(Package_Executer*             executer,
                                                          ClassObjectLiteralExpression* literal_expression,
                                                          RVM_OpcodeBuffer*             opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    assert(literal_expression != nullptr);
    assert(literal_expression->type_specifier != nullptr);
    assert(literal_expression->field_init_expression_list != nullptr);


    // TODO: 这里要做强制检查
    ClassDefinition* class_definition = literal_expression->type_specifier->u.class_type->class_definition;

    // 0. new class-object
    generate_vmcode(executer, opcode_buffer, RVM_CODE_NEW_CLASS_OB_LITERAL, class_definition->class_index, literal_expression->line_number);


    FieldInitExpression* pos = literal_expression->field_init_expression_list;
    for (; pos != nullptr; pos = pos->next) {

        // 1. push init-expression
        generate_vmcode_from_expression(executer, pos->init_expression, opcode_buffer);


        // 2. shallow duplicate class-object
        unsigned int oper_num = 0;
        oper_num              = (0 << 8) | 2;
        generate_vmcode(executer, opcode_buffer, RVM_CODE_DUPLICATE, oper_num, pos->line_number);


        FieldMember* field_member = pos->field_member;
        assert(field_member != nullptr);


        // 3. pop_field_xxx
        RVM_Opcode opcode = RVM_CODE_UNKNOW;
        opcode            = convert_opcode_by_rvm_type(RVM_CODE_POP_FIELD_BOOL, field_member->type_specifier);

        generate_vmcode(executer, opcode_buffer, opcode, field_member->index_of_class, pos->line_number);
    }
}


void generate_vmcode_from_array_literal_expreesion(Package_Executer*       executer,
                                                   ArrayLiteralExpression* array_literal_expression,
                                                   RVM_OpcodeBuffer*       opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    assert(array_literal_expression != nullptr);
    assert(array_literal_expression->expression_list != nullptr);

    int         size = 0;
    Expression* pos  = array_literal_expression->expression_list;
    for (; pos != nullptr; pos = pos->next) {
        generate_vmcode_from_expression(executer, pos, opcode_buffer);
        size++;
    }

    unsigned int oper_num = 0;

    if (array_literal_expression->dimension_expression->dimension == 1) {
        if (array_literal_expression->type_specifier->kind == RING_BASIC_TYPE_BOOL) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_NEW_ARRAY_LITERAL_BOOL, size, array_literal_expression->line_number);
        } else if (array_literal_expression->type_specifier->kind == RING_BASIC_TYPE_INT) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_NEW_ARRAY_LITERAL_INT, size, array_literal_expression->line_number);
        } else if (array_literal_expression->type_specifier->kind == RING_BASIC_TYPE_DOUBLE) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_NEW_ARRAY_LITERAL_DOUBLE, size, array_literal_expression->line_number);
        } else if (array_literal_expression->type_specifier->kind == RING_BASIC_TYPE_STRING) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_NEW_ARRAY_LITERAL_STRING, size, array_literal_expression->line_number);
        } else if (array_literal_expression->type_specifier->kind == RING_BASIC_TYPE_CLASS) {
            ClassDefinition* class_definition = array_literal_expression->type_specifier->u.class_type->class_definition;
            oper_num                          = (class_definition->class_index << 16) | size;
            generate_vmcode(executer, opcode_buffer, RVM_CODE_NEW_ARRAY_LITERAL_CLASS_OB, oper_num, array_literal_expression->line_number);
        } else {
            ring_error_report("error: array literal expression not support bool[] int[] double[] string[] <class>[]\n");
        }
    } else {
        oper_num = (array_literal_expression->dimension_expression->dimension << 16) | size;
        generate_vmcode(executer, opcode_buffer, RVM_CODE_NEW_ARRAY_LITERAL_A, oper_num, array_literal_expression->line_number);
    }
}

void generate_vmcode_from_array_index_expression(Package_Executer*     executer,
                                                 ArrayIndexExpression* array_index_expression,
                                                 RVM_OpcodeBuffer*     opcode_buffer) {

    debug_generate_info_with_darkgreen("\t");
    assert(array_index_expression != nullptr);
    assert(array_index_expression->array_expression != nullptr);
    assert(array_index_expression->index_expression != nullptr);

    // TODO：需要处理一下字符串 通过索引寻址
    // 这里暂时只处理数组
    // 暂时只处理一维数组
    // 要通过变量的类型来决定 push_array_int push_array_double push_array_object
    Declaration* declaration = array_index_expression->array_expression->u.identifier_expression->u.declaration;
    if (declaration == nullptr) {
        ring_error_report("invalid operator[] in identifier:%s\n", array_index_expression->array_expression->u.identifier_expression->identifier);
    }
    if (declaration->type_specifier->kind != RING_BASIC_TYPE_ARRAY) {
        ring_error_report("invalid declaration in operation[] identifier:%s\n", array_index_expression->array_expression->u.identifier_expression->identifier);
    }

    // push array-object to runtime_stack
    RVM_Opcode opcode = RVM_CODE_UNKNOW;
    if (declaration->is_local) {
        opcode = RVM_CODE_PUSH_STACK_ARRAY;
    } else {
        opcode = RVM_CODE_PUSH_STATIC_ARRAY;
    }
    generate_vmcode(executer, opcode_buffer, opcode, declaration->variable_index, array_index_expression->line_number);

    // push index-expression to runtime_stack
    // generate_vmcode_from_expression(executer, index, opcode_buffer, 0);

    SubDimensionExpression* pos_index = array_index_expression->index_expression->dimension_list;
    for (unsigned int i = 0; i < declaration->type_specifier->dimension - 1 && pos_index != nullptr; i++, pos_index = pos_index->next) {
        generate_vmcode_from_expression(executer, pos_index->num_expression, opcode_buffer);
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_ARRAY_A, 0, array_index_expression->line_number);
    }

    // 最后一个纬度
    if (pos_index != nullptr) {
        generate_vmcode_from_expression(executer, pos_index->num_expression, opcode_buffer);

        // access value by array-object and index-expression
        if (declaration->type_specifier->sub->kind == RING_BASIC_TYPE_BOOL) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_ARRAY_BOOL, 0, array_index_expression->line_number);
        } else if (declaration->type_specifier->sub->kind == RING_BASIC_TYPE_INT) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_ARRAY_INT, 0, array_index_expression->line_number);
        } else if (declaration->type_specifier->sub->kind == RING_BASIC_TYPE_DOUBLE) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_ARRAY_DOUBLE, 0, array_index_expression->line_number);
        } else if (declaration->type_specifier->sub->kind == RING_BASIC_TYPE_STRING) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_ARRAY_STRING, 0, array_index_expression->line_number);
        } else if (declaration->type_specifier->sub->kind == RING_BASIC_TYPE_CLASS) {
            generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_ARRAY_CLASS_OB, 0, array_index_expression->line_number);
        } else {
            ring_error_report("error: array index expression only support bool[] int[] double[] string[] class[]\n");
        }
    }
}

void generate_vmcode(Package_Executer* executer,
                     RVM_OpcodeBuffer* opcode_buffer,
                     RVM_Opcode        opcode,
                     unsigned int      operand,
                     unsigned int      line_number) {

    debug_generate_info_with_darkgreen("\t");
    if (opcode_buffer->code_capacity == opcode_buffer->code_size) {
        size_t old_alloc_size = opcode_buffer->code_capacity * sizeof(RVM_Byte);
        opcode_buffer->code_capacity += 3000;
        size_t new_alloc_size    = opcode_buffer->code_capacity * sizeof(RVM_Byte);
        opcode_buffer->code_list = (RVM_Byte*)mem_realloc(NULL_MEM_POOL, opcode_buffer->code_list, old_alloc_size, new_alloc_size);
    }

    RVM_Opcode_Info opcode_info                          = RVM_Opcode_Infos[opcode];
    unsigned int    start_pc                             = opcode_buffer->code_size;

    opcode_buffer->code_list[opcode_buffer->code_size++] = opcode; // 操作码

    switch (opcode_info.operand_type) {
    case OPCODE_OPERAND_TYPE_0BYTE:
        break;

    case OPCODE_OPERAND_TYPE_1BYTE:
        opcode_buffer->code_list[opcode_buffer->code_size++] = operand;
        break;

    case OPCODE_OPERAND_TYPE_2BYTE_As:
    case OPCODE_OPERAND_TYPE_2BYTE_AB:
        opcode_buffer->code_list[opcode_buffer->code_size++] = (RVM_Byte)((operand >> 8) & 0XFF);
        opcode_buffer->code_list[opcode_buffer->code_size++] = (RVM_Byte)(operand & 0XFF);
        break;

    case OPCODE_OPERAND_TYPE_3BYTE_ABs:
        opcode_buffer->code_list[opcode_buffer->code_size++] = (RVM_Byte)((operand >> 16) & 0XFF);
        opcode_buffer->code_list[opcode_buffer->code_size++] = (RVM_Byte)((operand >> 8) & 0XFF);
        opcode_buffer->code_list[opcode_buffer->code_size++] = (RVM_Byte)(operand & 0XFF);
        break;

    default: break;
    }

    if (line_number)
        add_code_line_map(opcode_buffer, line_number, start_pc, opcode_buffer->code_size - start_pc);
}

int constant_pool_grow(Package_Executer* executer, unsigned int growth_size) {
    debug_generate_info_with_darkgreen("\t");
    int    old_size       = executer->constant_pool_size;

    size_t old_alloc_size = executer->constant_pool_size * sizeof(RVM_ConstantPool);
    executer->constant_pool_size += growth_size;
    size_t new_alloc_size        = executer->constant_pool_size * sizeof(RVM_ConstantPool);


    executer->constant_pool_list = (RVM_ConstantPool*)mem_realloc(NULL_MEM_POOL,
                                                                  executer->constant_pool_list,
                                                                  old_alloc_size,
                                                                  new_alloc_size);

    return old_size;
}

int constant_pool_add_int(Package_Executer* executer, int int_literal) {
    debug_generate_info_with_darkgreen("\t");
    int index                                       = constant_pool_grow(executer, 1);

    executer->constant_pool_list[index].type        = CONSTANTPOOL_TYPE_INT;
    executer->constant_pool_list[index].u.int_value = int_literal;
    return index;
}

int constant_pool_add_double(Package_Executer* executer, double double_literal) {
    debug_generate_info_with_darkgreen("\t");
    int index                                          = constant_pool_grow(executer, 1);

    executer->constant_pool_list[index].type           = CONSTANTPOOL_TYPE_DOUBLE;
    executer->constant_pool_list[index].u.double_value = double_literal;
    return index;
}

int constant_pool_add_string(Package_Executer* executer, char* string_literal) {
    debug_generate_info_with_darkgreen("\t");
    int index                                          = constant_pool_grow(executer, 1);

    executer->constant_pool_list[index].type           = CONSTANTPOOL_TYPE_STRING;
    executer->constant_pool_list[index].u.string_value = string_literal;
    return index;
}


unsigned int opcode_buffer_get_label(RVM_OpcodeBuffer* opcode_buffer) {
    debug_generate_info_with_darkgreen("\t");
    unsigned int old_index = opcode_buffer->lable_list.size();

    opcode_buffer->lable_list.push_back(RVM_LabelTable());

    return old_index;
}

void opcode_buffer_set_label(RVM_OpcodeBuffer* opcode_buffer,
                             unsigned int      label,
                             unsigned int      label_address) {

    debug_generate_info_with_darkgreen("\t");
    opcode_buffer->lable_list[label].label_address = label_address;
}

void opcode_buffer_fix_label(RVM_OpcodeBuffer* opcode_buffer) {
    debug_generate_info_with_darkgreen("\t");

    unsigned int label;
    unsigned int label_address;

    for (unsigned int i = 0; i < opcode_buffer->code_size;) {
        RVM_Byte opcode = opcode_buffer->code_list[i];
        if (opcode <= RVM_CODE_UNKNOW || opcode >= RVM_CODES_NUM) {
            ring_error_report("generate vm code: opcode_buffer_fix_label(opcode is valid:%d)\n", opcode);
        }
        RVM_Opcode_Info opcode_info = RVM_Opcode_Infos[opcode];

        switch (opcode) {
        case RVM_CODE_JUMP:
        case RVM_CODE_JUMP_IF_FALSE:
        case RVM_CODE_JUMP_IF_TRUE:
        case RVM_CODE_FOR_RANGE_ARRAY_BOOL:
        case RVM_CODE_FOR_RANGE_ARRAY_INT:
        case RVM_CODE_FOR_RANGE_ARRAY_DOUBLE:
        case RVM_CODE_FOR_RANGE_ARRAY_STRING:
        case RVM_CODE_FOR_RANGE_ARRAY_CLASS_OB:
        case RVM_CODE_FOR_RANGE_STRING:
            label                           = (opcode_buffer->code_list[i + 1] << 8) + (opcode_buffer->code_list[i + 2]);
            label_address                   = opcode_buffer->lable_list[label].label_address;

            opcode_buffer->code_list[i + 1] = (RVM_Byte)(label_address >> 8);
            opcode_buffer->code_list[i + 2] = (RVM_Byte)(label_address & 0Xff);
            break;

        default:
            break;
        }


        switch (opcode_info.operand_type) {
        case OPCODE_OPERAND_TYPE_0BYTE:
            i++;
            break;

        case OPCODE_OPERAND_TYPE_1BYTE:
            i += 2;
            break;

        case OPCODE_OPERAND_TYPE_2BYTE_As:
        case OPCODE_OPERAND_TYPE_2BYTE_AB:
            i += 3;
            break;

        case OPCODE_OPERAND_TYPE_3BYTE_ABs:
            i += 4;
            break;

        default:
            ring_error_report("opcode_buffer_fix_label(opcode is valid:%d)\n", opcode);
            break;
        }
    }
}

RVM_Opcode convert_opcode_by_rvm_type(RVM_Opcode opcode, TypeSpecifier* type) {
    debug_generate_info_with_darkgreen("\t");
    assert(type != nullptr);

    if (!(opcode == RVM_CODE_POP_STATIC_BOOL
          || opcode == RVM_CODE_PUSH_STATIC_BOOL
          || opcode == RVM_CODE_POP_STACK_BOOL
          || opcode == RVM_CODE_PUSH_STACK_BOOL
          || opcode == RVM_CODE_POP_FIELD_BOOL
          || opcode == RVM_CODE_PUSH_FIELD_BOOL)) {
        ring_error_report("convert_opcode_by_rvm_type error:opcode is valid:%d\n", opcode);
    }

    switch (type->kind) {
    case RING_BASIC_TYPE_BOOL:
        // RVM_CODE_POP_STATIC_BOOL
        // RVM_CODE_PUSH_STATIC_BOOL
        // RVM_CODE_POP_STACK_BOOL
        // RVM_CODE_PUSH_STACK_BOOL
        // RVM_CODE_POP_FIELD_BOOL
        // RVM_CODE_PUSH_FIELD_BOOL
        return opcode;
        break;
    case RING_BASIC_TYPE_INT:
        // RVM_CODE_POP_STATIC_INT
        // RVM_CODE_PUSH_STATIC_INT
        // RVM_CODE_POP_STACK_INT
        // RVM_CODE_PUSH_STACK_INT
        // RVM_CODE_POP_FIELD_INT
        // RVM_CODE_PUSH_FIELD_INT
        return RVM_Opcode(opcode + 1);
        break;
    case RING_BASIC_TYPE_DOUBLE:
        // RVM_CODE_POP_STATIC_DOUBLE
        // RVM_CODE_PUSH_STATIC_DOUBLE
        // RVM_CODE_POP_STACK_DOUBLE
        // RVM_CODE_PUSH_STACK_DOUBLE
        // RVM_CODE_POP_FIELD_DOUBLE
        // RVM_CODE_PUSH_FIELD_DOUBLE
        return RVM_Opcode(opcode + 2);
        break;
    case RING_BASIC_TYPE_STRING:
        // RVM_CODE_POP_STATIC_STRING
        // RVM_CODE_PUSH_STATIC_STRING
        // RVM_CODE_POP_STACK_STRING
        // RVM_CODE_PUSH_STACK_STRING
        // RVM_CODE_POP_FIELD_STRING
        // RVM_CODE_PUSH_FIELD_STRING
        return RVM_Opcode(opcode + 3);
        break;
    case RING_BASIC_TYPE_CLASS:
        // RVM_CODE_POP_STATIC_CLASS_OB
        // RVM_CODE_PUSH_STATIC_CLASS_OB
        // RVM_CODE_POP_STACK_CLASS_OB
        // RVM_CODE_PUSH_STACK_CLASS_OB
        // RVM_CODE_POP_FIELD_CLASS_OB
        // RVM_CODE_PUSH_FIELD_CLASS_OB
        return RVM_Opcode(opcode + 4);
        break;
    case RING_BASIC_TYPE_ARRAY:
        // RVM_CODE_POP_STATIC_ARRAY
        // RVM_CODE_PUSH_STATIC_ARRAY
        // RVM_CODE_POP_STACK_ARRAY
        // RVM_CODE_PUSH_STACK_ARRAY
        // RVM_CODE_POP_FIELD_ARRAY
        // RVM_CODE_PUSH_FIELD_ARRAY
        return RVM_Opcode(opcode + 5);
        break;

    default:
        ring_error_report("convert_opcode_by_rvm_type error: unknow kind:%d\n", type->kind);
        break;
    }

    return RVM_CODE_UNKNOW;
}

unsigned int calc_runtime_stack_capacity(RVM_Byte* code_list, unsigned int code_size) {
    return 0;
}


// TODO:
// 这里实现完成了, 但是有点bug, 还未测试
// 因为 executer 和 rvm 有点耦合, 所以这里设计的有点问题, 需要重新设计
void add_code_line_map(RVM_OpcodeBuffer* opcode_buffer, unsigned int line_number, unsigned int start_pc, unsigned int opcode_size) {
    if (opcode_buffer->code_line_map.empty()
        || opcode_buffer->code_line_map.rbegin()->line_number != line_number) {
        RVM_SourceCodeLineMap tmp = {
            line_number,
            start_pc,
            opcode_size,
        };

        opcode_buffer->code_line_map.push_back(tmp);

    } else {
        opcode_buffer->code_line_map.rbegin()->opcode_size += opcode_size;
    }
}

// TODO:
// 这里实现完成了, 但是有点bug, 还未测试
// 因为 executer 和 rvm 有点耦合, 所以这里设计的有点问题, 需要重新设计
void dump_code_line_map(std::vector<RVM_SourceCodeLineMap>& code_line_map) {
    printf("------------------ CodeLineMap-Dump-begin ------------------\n");
    printf("    line_number       start_pc           size\n");
    for (RVM_SourceCodeLineMap& code_line : code_line_map) {
        printf("%15d  %15d %15d\n",
               code_line.line_number,
               code_line.opcode_begin_index,
               code_line.opcode_size);
    }

    printf("------------------ CodeLineMap-Dump-begin ------------------\n");
}

/*
 * Deep copy from TypeSpecifier to RVM_TypeSpecifier
 *
 * front-end -> back-end
 * front-end: TypeSpecifier
 * back-end:  RVM_TypeSpecifier
 *
 */
void type_specifier_deep_copy(RVM_TypeSpecifier* dst, TypeSpecifier* src) {
    assert(dst != nullptr);
    assert(src != nullptr);

    dst->kind = src->kind;

    if (src->kind == RING_BASIC_TYPE_CLASS) {
        // class_index 在 type_specifier_deep_copy 没有修正
        // TODO: 后期修正
        dst->u.class_def_index = src->u.class_type->class_definition->class_index;
    }

    if (src->kind == RING_BASIC_TYPE_ARRAY) {
        dst->dimension = src->dimension;
        if (src->sub != nullptr) {
            dst->sub = (RVM_TypeSpecifier*)mem_alloc(NULL_MEM_POOL, sizeof(RVM_TypeSpecifier));
            type_specifier_deep_copy(dst->sub, src->sub);
        }
    }
}