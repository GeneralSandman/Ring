#include "ring.hpp"
#include <assert.h>
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
        RVM_Value*  value = &(VM_STATIC_DATA[i]);

        std::string type;
        type = format_rvm_type(rvm, value);
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


    printf("%sHead Size:%s %lld\n", LOG_COLOR_GREEN, LOG_COLOR_CLEAR, rvm->runtime_heap->alloc_size);
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
        RVM_Value* value = &(VM_STATIC_DATA[i]);
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
            // ring_error_report("mark static error, type:%d", value->type);
            break;
        }
    }

    //  2. runtime stack 变量 指向的位置 需要标记
    for (unsigned int stack_index = 0; stack_index < VM_CUR_CO_STACK_TOP_INDEX; stack_index++) {
        RVM_Value* value = &(VM_CUR_CO_STACK_DATA[stack_index]);
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
        case RVM_ARRAY_INT64:
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


RVM_String* new_string(Ring_VirtualMachine* rvm) {
    RVM_String* string = (RVM_String*)mem_alloc(rvm->meta_pool, sizeof(RVM_String));
    string->gc_type    = RVM_GC_OBJECT_TYPE_STRING;
    string->gc_mark    = GC_MARK_COLOR_WHITE;
    string->gc_prev    = nullptr;
    string->gc_next    = nullptr;
    string->length     = 0;
    string->capacity   = 0;
    string->data       = nullptr;
    return string;
}

unsigned int init_string(Ring_VirtualMachine* rvm, RVM_String* string, unsigned int capacity) {
    assert(capacity == ROUND_UP8(capacity));

    unsigned int alloc_size = capacity * sizeof(char);
    string->length          = 0;
    string->capacity        = capacity;
    string->data            = (char*)calloc(1, alloc_size);

    return alloc_size;
}


RVM_String* rvm_deep_copy_string(Ring_VirtualMachine* rvm, RVM_String* src) {
    unsigned int alloc_size = 0;
    RVM_String*  string     = new_string(rvm);

    alloc_size              = sizeof(char) * src->capacity;
    string->length          = src->length;
    string->capacity        = src->capacity;
    string->data            = (char*)calloc(1, alloc_size);

    memcpy(string->data, src->data, alloc_size);

    rvm_heap_list_add_object(rvm, (RVM_GC_Object*)string);
    rvm_heap_alloc_size_incr(rvm, alloc_size);

    return string;
}


RVM_Array* new_array(Ring_VirtualMachine* rvm) {
    RVM_Array* array    = (RVM_Array*)mem_alloc(rvm->meta_pool, sizeof(RVM_Array));
    array->gc_type      = RVM_GC_OBJECT_TYPE_ARRAY;
    array->gc_mark      = GC_MARK_COLOR_WHITE;
    array->gc_prev      = nullptr;
    array->gc_next      = nullptr;
    array->type         = RVM_ARRAY_UNKNOW;
    array->dimension    = 0;
    array->length       = 0;
    array->capacity     = 0;
    array->class_ref    = nullptr;
    array->u.bool_array = nullptr;
    return array;
}

// dimension_index 为 2 代表分配2维数组
RVM_Array* rvm_new_array(Ring_VirtualMachine* rvm,
                         unsigned int         dimension,
                         unsigned int*        dimension_list,
                         unsigned int         dimension_index,
                         RVM_Array_Type       array_type,
                         RVM_ClassDefinition* class_definition) {

    if (dimension_index == 0) {
        return nullptr;
    }
    RVM_Array*   array      = nullptr;
    unsigned int alloc_size = 0;

    array                   = new_array(rvm);
    array->type             = array_type;
    array->dimension        = dimension_index;
    array->length           = dimension_list[dimension - dimension_index];
    array->capacity         = dimension_list[dimension - dimension_index];

    // 分配一维的数据
    if (dimension_index == 1) {
        array->capacity = ROUND_UP8(dimension_list[dimension - dimension_index]);

        switch (array_type) {
        case RVM_ARRAY_BOOL:
            alloc_size          = sizeof(bool) * array->capacity;
            array->u.bool_array = (bool*)calloc(1, alloc_size);
            break;
        case RVM_ARRAY_INT:
            alloc_size         = sizeof(int) * array->capacity;
            array->u.int_array = (int*)calloc(1, alloc_size);
            break;
        case RVM_ARRAY_INT64:
            alloc_size           = sizeof(long long) * array->capacity;
            array->u.int64_array = (long long*)calloc(1, alloc_size);
            break;
        case RVM_ARRAY_DOUBLE:
            alloc_size            = sizeof(double) * array->capacity;
            array->u.double_array = (double*)calloc(1, alloc_size);
            break;
        case RVM_ARRAY_STRING:
            // FIXME: 这里内存的增长写的不太好
            alloc_size            = sizeof(RVM_String*) * array->capacity;
            array->u.string_array = (RVM_String**)mem_alloc(rvm->data_pool, alloc_size);
            for (unsigned int i = 0; i < array->length; i++) {
                array->u.string_array[i] = new_string(rvm);
                alloc_size               = init_string(rvm, array->u.string_array[i], ROUND_UP8(1));
                rvm_heap_list_add_object(rvm, (RVM_GC_Object*)(array->u.string_array[i]));
                rvm_heap_alloc_size_incr(rvm, alloc_size);
            }
            alloc_size = 0;
            break;
        case RVM_ARRAY_CLASS_OBJECT:
            assert(class_definition != nullptr);
            array->class_ref        = class_definition;
            array->u.class_ob_array = (RVM_ClassObject*)mem_alloc(rvm->data_pool,
                                                                  sizeof(RVM_ClassObject) * array->capacity);
            for (unsigned int i = 0; i < array->length; i++) {
                array->u.class_ob_array[i] = *rvm_new_class_object(rvm, class_definition);
            }
            break;
        default:
            break;
        }
    } else {
        array->type      = RVM_ARRAY_A;
        array->u.a_array = (RVM_Array*)mem_alloc(rvm->meta_pool,
                                                 sizeof(RVM_Array) * array->capacity);

        for (unsigned int i = 0; i < array->length; i++) {
            array->u.a_array[i] = *rvm_new_array(rvm,
                                                 dimension,
                                                 dimension_list,
                                                 dimension_index - 1,
                                                 array_type,
                                                 class_definition);
        }
    }

    rvm_heap_list_add_object(rvm, (RVM_GC_Object*)array);
    if (alloc_size > 0) {
        rvm_heap_alloc_size_incr(rvm, alloc_size);
    }

    return array;
}


RVM_Array* rvm_deep_copy_array(Ring_VirtualMachine* rvm, RVM_Array* src) {
    RVM_Array* array  = nullptr;

    array             = new_array(rvm);
    array->type       = src->type;
    array->dimension  = src->dimension;
    array->length     = src->length;
    array->capacity   = src->capacity;
    array->class_ref  = src->class_ref;


    size_t alloc_size = 0;

    switch (src->type) {
    case RVM_ARRAY_BOOL:
        alloc_size          = sizeof(bool) * array->capacity;
        array->u.bool_array = (bool*)calloc(1, alloc_size); // TODO: 分配在内存池上
        memcpy(array->u.bool_array, src->u.bool_array, alloc_size);
        break;

    case RVM_ARRAY_INT:
        alloc_size         = sizeof(int) * array->capacity;
        array->u.int_array = (int*)calloc(1, alloc_size); // TODO: 分配在内存池上
        memcpy(array->u.int_array, src->u.int_array, alloc_size);
        break;

    case RVM_ARRAY_INT64:
        alloc_size           = sizeof(long long) * array->capacity;
        array->u.int64_array = (long long*)calloc(1, alloc_size); // TODO: 分配在内存池上
        memcpy(array->u.int64_array, src->u.int64_array, alloc_size);
        break;

    case RVM_ARRAY_DOUBLE:
        alloc_size            = sizeof(double) * array->capacity;
        array->u.double_array = (double*)calloc(1, alloc_size); // TODO: 分配在内存池上
        memcpy(array->u.double_array, src->u.double_array, alloc_size);
        break;

    case RVM_ARRAY_STRING:
        alloc_size            = sizeof(RVM_String*) * array->capacity;
        array->u.string_array = (RVM_String**)mem_alloc(rvm->data_pool, alloc_size);
        for (unsigned int i = 0; i < array->length; i++) {
            array->u.string_array[i]           = new_string(rvm);
            array->u.string_array[i]->length   = src->u.string_array[i]->length;
            array->u.string_array[i]->capacity = src->u.string_array[i]->capacity;
            array->u.string_array[i]->data     = src->u.string_array[i]->data; // TODO: 这里的string是 shallow copy

            alloc_size                         = array->u.string_array[i]->capacity * sizeof(char);
            rvm_heap_list_add_object(rvm, (RVM_GC_Object*)((array->u.string_array[i])));
            rvm_heap_alloc_size_incr(rvm, alloc_size);
        }
        alloc_size = 0;
        break;

    case RVM_ARRAY_CLASS_OBJECT: {
        array->class_ref        = src->class_ref;
        array->u.class_ob_array = (RVM_ClassObject*)mem_alloc(rvm->meta_pool,
                                                              sizeof(RVM_ClassObject) * array->capacity);
        rvm_heap_alloc_size_incr(rvm, 0);

        for (unsigned int i = 0; i < src->length; i++) {
            // TODO: 这里的写法不太好, 还是直接 strcpy 的那种形式最好, 结果通过 指针传入
            RVM_ClassObject* tmp                   = rvm_deep_copy_class_object(rvm, &(src->u.class_ob_array[i]));
            array->u.class_ob_array[i].class_ref   = tmp->class_ref;
            array->u.class_ob_array[i].field_count = tmp->field_count;
            array->u.class_ob_array[i].field       = tmp->field;
        }

    } break;

    case RVM_ARRAY_A:
        array->u.a_array = (RVM_Array*)mem_alloc(rvm->meta_pool,
                                                 sizeof(RVM_Array) * array->capacity);

        for (unsigned int i = 0; i < array->length; i++) {
            array->u.a_array[i] = *rvm_deep_copy_array(rvm, &(src->u.a_array[i]));
        }
        break;

    default:
        break;
    }


    rvm_heap_list_add_object(rvm, (RVM_GC_Object*)array);
    rvm_heap_alloc_size_incr(rvm, alloc_size);


    return array;
}


void rvm_free_object(Ring_VirtualMachine* rvm, RVM_GC_Object* object) {
    assert(object != nullptr);

    size_t     free_size = 0;

    RVM_Array* array     = nullptr;

    switch (object->gc_type) {
    case RVM_GC_OBJECT_TYPE_STRING:
        free_size = ((RVM_String*)object)->capacity * sizeof(char);
        debug_exec_info_with_white("\t string::free_size:%ld", free_size);
        break;

    case RVM_GC_OBJECT_TYPE_CLASS_OB: {
        RVM_ClassObject* class_ob = (RVM_ClassObject*)object;
        for (unsigned int field_index = 0; field_index < class_ob->field_count; field_index++) {
            switch (class_ob->field[field_index].type) {
            case RVM_VALUE_TYPE_BOOL:
                free_size += 1;
                break;
            case RVM_VALUE_TYPE_INT:
                free_size += 4;
                break;
            case RVM_VALUE_TYPE_INT64:
                free_size += 8;
                break;
            case RVM_VALUE_TYPE_DOUBLE:
                free_size += 8;
                break;
            case RVM_VALUE_TYPE_STRING:
                break;
            default: break;
            }
        }
        debug_exec_info_with_white("\t class-object::free_size:%ld", free_size);
    } break;

    case RVM_GC_OBJECT_TYPE_ARRAY:
        array = (RVM_Array*)object;
        switch (array->type) {
        case RVM_ARRAY_BOOL:
            free_size = sizeof(bool) * array->capacity;
            free(array->u.bool_array);
            break;
        case RVM_ARRAY_INT:
            free_size = sizeof(int) * array->capacity;
            free(array->u.int_array);
            break;
        case RVM_ARRAY_INT64:
            free_size = sizeof(long long) * array->capacity;
            free(array->u.int64_array);
            break;
        case RVM_ARRAY_DOUBLE:
            free_size = sizeof(double) * array->capacity;
            free(array->u.double_array);
            break;
        case RVM_ARRAY_STRING: break;
        case RVM_ARRAY_CLASS_OBJECT: break;
        case RVM_ARRAY_A: break;
        default: break;
        }
        break;

    default:
        break;
    }

    rvm_heap_list_remove_object(rvm, object);
    rvm_heap_alloc_size_decr(rvm, free_size);
}

unsigned int rvm_free_string(Ring_VirtualMachine* rvm, RVM_String* string) {
    assert(string != nullptr);

    if (string->data != nullptr) {
        free(string->data);
    }
    unsigned int free_size = string->capacity * sizeof(char);

    mem_free(rvm->meta_pool, string, sizeof(RVM_String));

    return free_size;
}

unsigned int rvm_free_class_object(Ring_VirtualMachine* rvm, RVM_ClassObject* class_object) {
    unsigned int free_size = 0;

    if (class_object->field != nullptr) {
        mem_free(rvm->meta_pool, class_object->field, class_object->field_count * sizeof(RVM_Value));
    }
    free_size = class_object->field_count * sizeof(RVM_Value);
    mem_free(rvm->meta_pool, class_object, sizeof(RVM_ClassObject));
    return free_size;
}


RVM_ClassObject* rvm_heap_new_class_object(Ring_VirtualMachine* rvm) {
    RVM_ClassObject* class_object = (RVM_ClassObject*)mem_alloc(rvm->meta_pool, sizeof(RVM_ClassObject));
    class_object->gc_type         = RVM_GC_OBJECT_TYPE_CLASS_OB;
    class_object->gc_mark         = GC_MARK_COLOR_WHITE;
    class_object->gc_prev         = nullptr;
    class_object->gc_next         = nullptr;
    class_object->class_ref       = nullptr;
    class_object->field_count     = 0;
    class_object->field           = nullptr;

    rvm_heap_list_add_object(rvm, (RVM_GC_Object*)class_object);

    return class_object;
}


/*
 * create array in heap
 *
 * support create one-dimensional array only.
 *
 */
RVM_ClassObject* rvm_new_class_object(Ring_VirtualMachine* rvm,
                                      RVM_ClassDefinition* class_definition) {

    assert(class_definition != nullptr);

    RVM_String*      string          = nullptr;
    RVM_ClassObject* class_ob        = nullptr;
    RVM_Value*       field           = nullptr;

    size_t           alloc_meta_size = 0;
    size_t           alloc_data_size = 0;

    class_ob                         = rvm_heap_new_class_object(rvm);
    alloc_meta_size                  = class_definition->field_size * sizeof(RVM_Value);
    field                            = (RVM_Value*)mem_alloc(rvm->meta_pool,
                                                             alloc_meta_size);
    memset(field, 0, alloc_meta_size);

    for (unsigned int field_index = 0; field_index < class_definition->field_size; field_index++) {
        RVM_TypeSpecifier* type_specifier = class_definition->field_list[field_index].type_specifier;

        switch (type_specifier->kind) {
        case RING_BASIC_TYPE_BOOL:
            field[field_index].type         = RVM_VALUE_TYPE_BOOL;
            field[field_index].u.bool_value = RVM_FALSE;
            alloc_data_size += 1;
            break;
        case RING_BASIC_TYPE_INT:
            field[field_index].type        = RVM_VALUE_TYPE_INT;
            field[field_index].u.int_value = 0;
            alloc_data_size += 4;
            break;
        case RING_BASIC_TYPE_INT64:
            field[field_index].type          = RVM_VALUE_TYPE_INT64;
            field[field_index].u.int64_value = 0;
            alloc_data_size += 8;
            break;
        case RING_BASIC_TYPE_DOUBLE:
            field[field_index].type           = RVM_VALUE_TYPE_DOUBLE;
            field[field_index].u.double_value = 0.0;
            alloc_data_size += 8;
            break;
        case RING_BASIC_TYPE_STRING: {
            unsigned alloc_size = 0;
            // 在这里: string 的控制权不在 class-object的手上
            string     = new_string(rvm);
            alloc_size = init_string(rvm, string, ROUND_UP8(1));
            rvm_heap_list_add_object(rvm, (RVM_GC_Object*)string);
            rvm_heap_alloc_size_incr(rvm, alloc_size);

            field[field_index].type           = RVM_VALUE_TYPE_STRING;
            field[field_index].u.string_value = string;
        } break;
        case RING_BASIC_TYPE_CLASS: {
            RVM_ClassDefinition* sub_class_definition = &(rvm->class_list[type_specifier->u.class_def_index]);
            field[field_index].type                   = RVM_VALUE_TYPE_CLASS_OB;
            field[field_index].u.class_ob_value       = rvm_new_class_object(rvm, sub_class_definition);
        } break;
        case RING_BASIC_TYPE_ARRAY:
            field[field_index].type          = RVM_VALUE_TYPE_ARRAY;
            field[field_index].u.array_value = nullptr;
            alloc_data_size += 8;
            break;
        default:
            break;
        }
    }


    class_ob->class_ref   = class_definition;
    class_ob->field_count = class_definition->field_size;
    class_ob->field       = field;

    rvm_heap_alloc_size_incr(rvm, alloc_data_size);

    return class_ob;
}


RVM_ClassObject* rvm_deep_copy_class_object(Ring_VirtualMachine* rvm, RVM_ClassObject* src) {
    RVM_ClassObject* class_object = rvm_heap_new_class_object(rvm);
    class_object->class_ref       = src->class_ref;
    class_object->field_count     = src->field_count;
    class_object->field           = nullptr;

    // FIXME: 这里还要继续完善深度copy
    RVM_Value* field = nullptr;
    field            = (RVM_Value*)mem_alloc(rvm->meta_pool,
                                             src->field_count * sizeof(RVM_Value));
    memcpy(field, src->field, src->field_count * sizeof(RVM_Value));
    class_object->field = field;
    return class_object;
}