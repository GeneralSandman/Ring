#include "ring.hpp"
#include <cstring>


/*
 * Garbage Collection
 *
 * 目前采用最简单的: mark&sweep算法
 * 1. gc 的过程会暂停程序
 */

void gc(Ring_VirtualMachine* rvm) {
#ifdef DEBUG_RVM_GC_DETAIL
    printf("============Debug RVM GC Detail(Begin)============\n");
    gc_summary(rvm);
#endif

    gc_mark(rvm);
    gc_sweep(rvm);

#ifdef DEBUG_RVM_GC_DETAIL
    printf("%s-----------------GC Action-----------------%s\n", LOG_COLOR_YELLOW, LOG_COLOR_CLEAR);
    gc_summary(rvm);
    printf("============Debug RVM GC Detail(End)============\n\n");
#endif
}

void gc_summary(Ring_VirtualMachine* rvm) {
    printf("%sStatic:%s\n", LOG_COLOR_GREEN, LOG_COLOR_CLEAR);
    for (unsigned int i = 0; i < rvm->runtime_static->size; i++) {
        RVM_Value*  value = &(rvm->runtime_static->data[i]);

        std::string type;
        switch (value->type) {
        case RVM_VALUE_TYPE_BOOL:
            type = "bool";
            break;
        case RVM_VALUE_TYPE_INT:
            type = "int";
            break;
        case RVM_VALUE_TYPE_DOUBLE:
            type = "double";
            break;
        case RVM_VALUE_TYPE_STRING:
            type = "string";
            break;
        case RVM_VALUE_TYPE_CLASS_OB:
            type = "class";
            break;
        case RVM_VALUE_TYPE_OBJECT:
            type = "object";
            break;
        default:
            type = "unknow";
            break;
        }
        printf("\tRVM_Value: %s\n", type.c_str());
    }

    printf("%sHeap:%s\n", LOG_COLOR_GREEN, LOG_COLOR_CLEAR);
    for (RVM_GC_Object* pos = rvm->runtime_heap->list; pos != nullptr; pos = pos->gc_next) {
        switch (pos->gc_type) {
        case RVM_GC_OBJECT_TYPE_STRING:
            printf("\tRVM_GC_Object: string\n");
            break;
        case RVM_GC_OBJECT_TYPE_CLASS_OB:
            printf("\tRVM_GC_Object: class-object\n");
            break;
        case RVM_GC_OBJECT_TYPE_ARRAY:
            printf("\tRVM_GC_Object: array\n");
            break;
        default:
            break;
        }
    }

    printf("%sStack:%s\n", LOG_COLOR_GREEN, LOG_COLOR_CLEAR);
    for (unsigned int stack_index = 0; stack_index < rvm->runtime_stack->top_index; stack_index++) {
        RVM_Value*  value = &(rvm->runtime_stack->data[stack_index]);
        std::string type;
        switch (value->type) {
        case RVM_VALUE_TYPE_BOOL:
            type = "bool";
            break;
        case RVM_VALUE_TYPE_INT:
            type = "int";
            break;
        case RVM_VALUE_TYPE_DOUBLE:
            type = "double";
            break;
        case RVM_VALUE_TYPE_STRING:
            type = "string";
            break;
        case RVM_VALUE_TYPE_OBJECT:
            type = "object";
            break;
        default:
            type = "unknow";
            break;
        }

        // 不展示目前 函数调用写死 的 20 local_variable_size
        if (!str_eq(type.c_str(), "callinfo")
            && !str_eq(type.c_str(), "unknow")) {
            printf("\tRVM_Value type:%s\n", type.c_str());
        }
    }


    printf("%sHead Size:%s %d\n", LOG_COLOR_GREEN, LOG_COLOR_CLEAR, rvm->runtime_heap->alloc_size);
}

/*
 * 对动态分配的内存进行标记
 *
 * 1. static 变量指向的位置 需要标记
 * 2. runtime stack 变量 指向的位置 需要标记
 */
void gc_mark(Ring_VirtualMachine* rvm) {
    // 1. static 变量指向的位置 需要标记
    for (unsigned int i = 0; i < rvm->runtime_static->size; i++) {
        RVM_Value* value = &(rvm->runtime_static->data[i]);
        // TODO:
        switch (value->type) {
        case RVM_VALUE_TYPE_STRING:
            value->u.string_value->gc_mark = GC_MARK_COLOR_BLACK;
            break;
        case RVM_VALUE_TYPE_CLASS_OB:
            value->u.class_ob_value->gc_mark = GC_MARK_COLOR_BLACK;
            gc_mark_class_ob(rvm, value->u.class_ob_value);
            break;
        case RVM_VALUE_TYPE_ARRAY:
            value->u.array_value->gc_mark = GC_MARK_COLOR_BLACK;
            gc_mark_array(rvm, value->u.array_value);
            break;
        default:
            ring_error_report("mark static error, type:%d", value->type);
            break;
        }
    }

    //  2. runtime stack 变量 指向的位置 需要标记
    for (unsigned int stack_index = 0; stack_index < rvm->runtime_stack->top_index; stack_index++) {
        RVM_Value* value = &(rvm->runtime_stack->data[stack_index]);
        // TODO:
        switch (value->type) {
        case RVM_VALUE_TYPE_STRING:
            value->u.string_value->gc_mark = GC_MARK_COLOR_BLACK;
            break;
        case RVM_VALUE_TYPE_CLASS_OB:
            value->u.class_ob_value->gc_mark = GC_MARK_COLOR_BLACK;
            gc_mark_class_ob(rvm, value->u.class_ob_value);
            break;
        case RVM_VALUE_TYPE_ARRAY:
            value->u.array_value->gc_mark = GC_MARK_COLOR_BLACK;
            gc_mark_array(rvm, value->u.array_value);
            break;
        default:
            // ring_error_report("mark stack error, type:%d", value->type);
            break;
        }
    }
}

void gc_sweep(Ring_VirtualMachine* rvm) {
    RVM_GC_Object* head = rvm->runtime_heap->list;
    RVM_GC_Object* next = nullptr;
    for (; head != nullptr; head = next) {
        next = head->gc_next;

        if (head->gc_mark == GC_MARK_COLOR_BLACK) {
            head->gc_mark = GC_MARK_COLOR_WHITE;
            // not need to clean
            continue;
        }
        rvm_free_object(rvm, head);
    }
}

void gc_mark_class_ob(Ring_VirtualMachine* rvm, RVM_ClassObject* class_ob) {
    debug_exec_info_with_white("\t mark:class-object %p", class_ob);

    for (unsigned int field_index = 0; field_index < class_ob->field_count; field_index++) {
        switch (class_ob->field[field_index].type) {
        case RVM_VALUE_TYPE_STRING:
            class_ob->field[field_index].u.string_value->gc_mark = GC_MARK_COLOR_BLACK;
            break;
        case RVM_VALUE_TYPE_ARRAY:
            break;
        default:
            break;
        }
    }
}

void gc_mark_array(Ring_VirtualMachine* rvm, RVM_Array* array) {

    for (unsigned int i = 0; i < array->length; i++) {
        switch (array->type) {
        case RVM_ARRAY_BOOL:
            break;
        case RVM_ARRAY_INT:
            break;
        case RVM_ARRAY_DOUBLE:
            break;
        case RVM_ARRAY_STRING:
            array->u.string_array[i]->gc_mark = GC_MARK_COLOR_BLACK;
            break;
        case RVM_ARRAY_CLASS_OBJECT:
            array->u.class_ob_array[i].gc_mark = GC_MARK_COLOR_BLACK;
            break;
        case RVM_ARRAY_A:
            break;
        default:
            break;
        }
    }
}
