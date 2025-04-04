#include "ring.hpp"

void debug_gc_summary(Ring_VirtualMachine* rvm, std::string stage) {
    printf("%s-Static:%s\n", LOG_COLOR_GREEN, LOG_COLOR_CLEAR);
    for (unsigned int i = 0; i < rvm->runtime_static->size; i++) {
        RVM_Value* value = &(VM_STATIC_DATA[i]);

        if (value->type == RVM_VALUE_TYPE_STRING
            || value->type == RVM_VALUE_TYPE_CLASS_OB
            || value->type == RVM_VALUE_TYPE_ARRAY
            || value->type == RVM_VALUE_TYPE_CLOSURE) {

            std::string type;
            type = format_rvm_type(rvm, value);
            printf("\tRVM_Value:     %10s %p\n", type.c_str(), (void*)(value->u.string_value));
        }
    }

    printf("%s-Stack:%s\n", LOG_COLOR_GREEN, LOG_COLOR_CLEAR);
    for (unsigned int stack_index = 0; stack_index < VM_CUR_CO_STACK_TOP_INDEX; stack_index++) {
        RVM_Value* value = &(VM_CUR_CO_STACK_DATA[stack_index]);

        if (value->type == RVM_VALUE_TYPE_STRING
            || value->type == RVM_VALUE_TYPE_CLASS_OB
            || value->type == RVM_VALUE_TYPE_ARRAY
            || value->type == RVM_VALUE_TYPE_CLOSURE) {

            std::string type;
            type = format_rvm_type(rvm, value);
            printf("\tRVM_Value:     %10s %p\n", type.c_str(), (void*)(value->u.string_value));
        }
    }

    printf("%s-Heap:%s\n", LOG_COLOR_GREEN, LOG_COLOR_CLEAR);
    for (RVM_GC_Object* pos = rvm->runtime_heap->list; pos != nullptr; pos = pos->gc_next) {
        std::string gc_type;
        switch (pos->gc_type) {
        case RVM_GC_OBJECT_TYPE_STRING:
            gc_type = "string";
            break;
        case RVM_GC_OBJECT_TYPE_CLASS_OB:
            gc_type = "class-ob";
            break;
        case RVM_GC_OBJECT_TYPE_ARRAY:
            gc_type = "array";
            break;
        case RVM_GC_OBJECT_TYPE_CLOSURE:
            gc_type = "closure";
            break;
        default:
            break;
        }

        printf("\tRVM_GC_Object: %10s %p\n", gc_type.c_str(), pos);
    }

    printf("%s+Head Size:%s %lld\n", LOG_COLOR_GREEN, LOG_COLOR_CLEAR, rvm->runtime_heap->alloc_size);
}
