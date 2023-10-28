#include "ring.h"


/*
 * Garbage Collection
 *
 * 目前采用最简单的: mark&sweep算法
 * 1. gc 的过程会暂停程序
 */

void gc(Ring_VirtualMachine* rvm) {
#ifdef DEBUG_RVM_GC_DETAIL
    printf("============Debug RVM GC Detail============\n");
    gc_summary(rvm);
#endif

    gc_mark(rvm);
    gc_sweep(rvm);

#ifdef DEBUG_RVM_GC_DETAIL
    printf("%s-----------------GC Action-----------------%s\n", LOG_COLOR_YELLOW, LOG_COLOR_CLEAR);
    gc_summary(rvm);
    printf("============Debug RVM GC Detail============\n\n");
#endif
}

void gc_summary(Ring_VirtualMachine* rvm) {
    printf("%sHeap:%s\n", LOG_COLOR_GREEN, LOG_COLOR_CLEAR);
    for (RVM_Object* pos = rvm->runtime_heap->list; pos != nullptr; pos = pos->next) {
        std::string type;
        switch (pos->type) {
        case RVM_OBJECT_TYPE_STRING:
            type = "string";
            break;
        case RVM_OBJECT_TYPE_ARRAY:
            type = "array";
            break;
        case RVM_OBJECT_TYPE_CLASS:
            type = "class";
            break;
        default:
            break;
        }
        printf("\tRVM_Object: %s\n", type.c_str());
    }

    printf("%sStack:%s\n", LOG_COLOR_GREEN, LOG_COLOR_CLEAR);

    for (int stack_index = 0; stack_index < rvm->runtime_stack->top_index; stack_index++) {
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
        case RVM_VALUE_TYPE_CALLINFO:
            type = "callinfo";
            break;
        default:
            type = "unknow";
            break;
        }

        // 不展示目前 函数调用写死 的 20 local_variable_size
        if (0 != strcmp(type.c_str(), "callinfo")
            && 0 != strcmp(type.c_str(), "unknow")) {
            printf("\tRVM_Value type:%s\n", type.c_str());
        }
    }


    printf("%sHead Size:%s %d\n", LOG_COLOR_GREEN, LOG_COLOR_CLEAR, rvm->runtime_heap->size);
}

/*
 * 对动态分配的内存进行标记
 *
 * 1. static 变量指向的位置 需要标记
 * 2. runtime stack 变量 指向的位置 需要标记
 */
void gc_mark(Ring_VirtualMachine* rvm) {
    // 1. static 变量指向的位置 需要标记
    for (int i = 0; i < rvm->runtime_static->size; i++) {
        RVM_Value* value = &(rvm->runtime_static->data[i]);
        if (value->type == RVM_VALUE_TYPE_OBJECT) {
            value->u.object->gc_mark = GC_MARK_COLOR_BLACK;
        }
    }

    //  2. runtime stack 变量 指向的位置 需要标记
    for (int stack_index = 0; stack_index < rvm->runtime_stack->top_index; stack_index++) {
        RVM_Value* value = &(rvm->runtime_stack->data[stack_index]);
        if (value->type == RVM_VALUE_TYPE_OBJECT) {
            value->u.object->gc_mark = GC_MARK_COLOR_BLACK;
        }
    }
}

void gc_sweep(Ring_VirtualMachine* rvm) {
    RVM_Object* head   = rvm->runtime_heap->list;
    RVM_Object* sentry = (RVM_Object*)malloc(sizeof(RVM_Object));
    sentry->prev       = nullptr;
    sentry->next       = head;
    if (head != nullptr) {
        head->prev = sentry;
    }


    RVM_Object* prev = sentry;
    RVM_Object* next = nullptr;
    for (; head != nullptr; head = next) {
        next = head->next;
        prev = head->prev;

        if (head->gc_mark == GC_MARK_COLOR_BLACK) {
            // 不需要被清除
            continue;
        }
        head->gc_mark = GC_MARK_COLOR_WHITE;

        prev->next    = next;
        if (next != nullptr) {
            next->prev = prev;
        }

        /*
         * 这里有个遗留问题
         *
         * 1. free object 并没有把实际的内存释放掉
         *      free object->u.array
         *      free object->u.string
         *      free object->u.class_object
         * 2. free 过程中 需要更新 heap_size
         */
        free(head);
    }


    rvm->runtime_heap->list = sentry->next;
    free(sentry);
}
