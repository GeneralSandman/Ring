#include "ring.hpp"

void debug_gc_summary(Ring_VirtualMachine* rvm, std::string stage) {
    printf("%s-Static:%s\n", LOG_COLOR_GREEN, LOG_COLOR_CLEAR);
    for (unsigned int i = 0; i < rvm->runtime_static->size; i++) {
        RVM_Value*  value = &(VM_STATIC_DATA[i]);

        std::string type;
        type = format_rvm_type(rvm, value);
        printf("\tRVM_Value: %s\n", type.c_str());
    }

    printf("%s-Heap:%s\n", LOG_COLOR_GREEN, LOG_COLOR_CLEAR);
    for (RVM_GC_Object* pos = rvm->runtime_heap->list; pos != nullptr; pos = pos->gc_next) {
        switch (pos->gc_type) {
        case RVM_GC_OBJECT_TYPE_STRING:
            printf("\tRVM_GC_Object: string %p\n", pos);
            break;
        case RVM_GC_OBJECT_TYPE_CLASS_OB:
            printf("\tRVM_GC_Object: class-object\n");
            break;
        case RVM_GC_OBJECT_TYPE_ARRAY:
            printf("\tRVM_GC_Object: array %p\n", pos);
            break;
        case RVM_GC_OBJECT_TYPE_CLOSURE:
            printf("\tRVM_GC_Object: closure\n");
            break;
        default:
            break;
        }
    }

    printf("%s-Stack:%s\n", LOG_COLOR_GREEN, LOG_COLOR_CLEAR);
    for (unsigned int stack_index = 0; stack_index < VM_CUR_CO_STACK_TOP_INDEX; stack_index++) {
        RVM_Value*  value = &(VM_CUR_CO_STACK_DATA[stack_index]);

        std::string type;
        type = format_rvm_type(rvm, value);

        // 不展示目前 函数调用写死 的 20 local_variable_size
        if (!str_eq(type.c_str(), "callinfo")
            && !str_eq(type.c_str(), "unknow")) {
            printf("\tRVM_Value type:%s\n", type.c_str());
        }
    }


    printf("%s+Head Size:%s %lld\n", LOG_COLOR_GREEN, LOG_COLOR_CLEAR, rvm->runtime_heap->alloc_size);
}
