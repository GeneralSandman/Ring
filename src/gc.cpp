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
            if (value->u.array_value != nullptr) {
                value->u.array_value->gc_mark = GC_MARK_COLOR_BLACK;
                gc_mark_array(rvm, value->u.array_value);
            }
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
        switch (class_ob->field_list[field_index].type) {
        case RVM_VALUE_TYPE_STRING:
            class_ob->field_list[field_index].u.string_value->gc_mark = GC_MARK_COLOR_BLACK;
            break;
        case RVM_VALUE_TYPE_CLASS_OB:
            class_ob->field_list[field_index].u.class_ob_value->gc_mark = GC_MARK_COLOR_BLACK;
            break;
        case RVM_VALUE_TYPE_ARRAY:
            class_ob->field_list[field_index].u.array_value->gc_mark = GC_MARK_COLOR_BLACK;
            break;
        case RVM_VALUE_TYPE_CLOSURE:
            // TODO:
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
            array->u.string_array[i].gc_mark = GC_MARK_COLOR_BLACK;
            break;
        case RVM_ARRAY_CLASS_OBJECT:
            array->u.class_ob_array[i].gc_mark = GC_MARK_COLOR_BLACK;
            break;
        case RVM_ARRAY_CLOSURE:
            // TODO:
            break;
        case RVM_ARRAY_A:
            break;
        default:
            break;
        }
    }
}

void rvm_free_object(Ring_VirtualMachine* rvm, RVM_GC_Object* object) {
    assert(object != nullptr);

    size_t           free_size    = 0;

    RVM_String*      string_value = nullptr;
    RVM_Array*       array        = nullptr;
    RVM_ClassObject* class_ob     = nullptr;

    switch (object->gc_type) {
    case RVM_GC_OBJECT_TYPE_STRING:
        string_value = (RVM_String*)object;
        free_size    = rvm_free_string(rvm, string_value);
        break;

    case RVM_GC_OBJECT_TYPE_CLASS_OB:
        class_ob  = (RVM_ClassObject*)object;
        free_size = rvm_free_class_ob(rvm, class_ob);
        break;

    case RVM_GC_OBJECT_TYPE_ARRAY:
        array     = (RVM_Array*)object;
        free_size = rvm_free_array(rvm, array);
        break;

    default:
        break;
    }

    rvm_heap_list_remove_object(rvm, object);
    rvm_heap_alloc_size_decr(rvm, free_size);
}

RVM_String* rvm_gc_new_string_meta(Ring_VirtualMachine* rvm) {
    RVM_String* string = (RVM_String*)mem_alloc(rvm->meta_pool, sizeof(RVM_String));
    string->gc_type    = RVM_GC_OBJECT_TYPE_STRING;
    string->gc_mark    = GC_MARK_COLOR_WHITE;
    string->gc_prev    = nullptr;
    string->gc_next    = nullptr;
    string->length     = 0;
    string->capacity   = 0;
    string->data       = nullptr;

    rvm_heap_list_add_object(rvm, (RVM_GC_Object*)string);

    return string;
}

void rvm_fill_string(Ring_VirtualMachine* rvm, RVM_String* string, unsigned int capacity) {
    if (capacity == 0)
        capacity = 8;
    assert(capacity == ROUND_UP8(capacity));

    unsigned int alloc_size = capacity * sizeof(char);
    string->length          = 0;
    string->capacity        = capacity;
    string->data            = (char*)mem_alloc(rvm->data_pool, alloc_size);

    memset(string->data, 0, alloc_size);

    rvm_heap_alloc_size_incr(rvm, alloc_size);
}


RVM_String* rvm_deep_copy_string(Ring_VirtualMachine* rvm, RVM_String* src) {
    unsigned int alloc_size = 0;
    RVM_String*  string     = rvm_gc_new_string_meta(rvm);

    alloc_size              = sizeof(char) * src->capacity;
    string->length          = src->length;
    string->capacity        = src->capacity;
    string->data            = (char*)mem_alloc(rvm->data_pool, alloc_size);

    memcpy(string->data, src->data, alloc_size);

    rvm_heap_alloc_size_incr(rvm, alloc_size);

    return string;
}

unsigned int rvm_free_string(Ring_VirtualMachine* rvm, RVM_String* string) {
    assert(string != nullptr);

    if (string->data != nullptr) {
        mem_free(rvm->data_pool, (void*)string->data, string->capacity);
    }
    unsigned int free_size = string->capacity * sizeof(char);

    mem_free(rvm->meta_pool, string, sizeof(RVM_String));

    return free_size;
}


RVM_Array* rvm_gc_new_array_meta(Ring_VirtualMachine* rvm,
                                 RVM_Array_Type       array_type,
                                 RVM_ClassDefinition* class_definition,
                                 unsigned int         dimension) {

    RVM_Array* array    = (RVM_Array*)mem_alloc(rvm->meta_pool, sizeof(RVM_Array));
    array->gc_type      = RVM_GC_OBJECT_TYPE_ARRAY;
    array->gc_mark      = GC_MARK_COLOR_WHITE;
    array->gc_prev      = nullptr;
    array->gc_next      = nullptr;
    array->type         = array_type;
    array->dimension    = dimension;
    array->length       = 0;
    array->capacity     = 0;
    array->class_ref    = class_definition;
    array->u.bool_array = nullptr;

    rvm_heap_list_add_object(rvm, (RVM_GC_Object*)array);

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

    array                   = rvm_gc_new_array_meta(rvm,
                                                    array_type, class_definition, dimension_index);
    array->length           = dimension_list[dimension - dimension_index];
    array->capacity         = dimension_list[dimension - dimension_index];

    // 分配一维的数据
    if (dimension_index == 1) {
        array->capacity = ROUND_UP8(dimension_list[dimension - dimension_index]);

        switch (array_type) {
        case RVM_ARRAY_BOOL:
            alloc_size          = sizeof(bool) * array->capacity;
            array->u.bool_array = (bool*)mem_alloc(rvm->data_pool, alloc_size);
            break;
        case RVM_ARRAY_INT:
            alloc_size         = sizeof(int) * array->capacity;
            array->u.int_array = (int*)mem_alloc(rvm->data_pool, alloc_size);
            break;
        case RVM_ARRAY_INT64:
            alloc_size           = sizeof(long long) * array->capacity;
            array->u.int64_array = (long long*)mem_alloc(rvm->data_pool, alloc_size);
            break;
        case RVM_ARRAY_DOUBLE:
            alloc_size            = sizeof(double) * array->capacity;
            array->u.double_array = (double*)mem_alloc(rvm->data_pool, alloc_size);
            break;
        case RVM_ARRAY_STRING:
            array->u.string_array = (RVM_String*)mem_alloc(rvm->data_pool,
                                                           sizeof(RVM_String) * array->capacity);
            for (unsigned int i = 0; i < array->length; i++) {
                RVM_String* string_value = rvm_gc_new_string_meta(rvm);
                rvm_fill_string(rvm, string_value, ROUND_UP8(1));
                array->u.string_array[i] = *string_value;
            }
            break;
        case RVM_ARRAY_CLASS_OBJECT:
            assert(class_definition != nullptr);
            array->u.class_ob_array = (RVM_ClassObject*)mem_alloc(rvm->data_pool,
                                                                  sizeof(RVM_ClassObject) * array->capacity);
            for (unsigned int i = 0; i < array->length; i++) {
                RVM_ClassObject* class_ob = rvm_gc_new_class_ob_meta(rvm);
                rvm_fill_class_ob(rvm, class_ob, class_definition);
                array->u.class_ob_array[i] = *class_ob;
            }
            break;
        default:
            break;
        }
    } else {
        // 递归分配多维数组
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

    rvm_heap_alloc_size_incr(rvm, alloc_size);

    return array;
}


RVM_Array* rvm_deep_copy_array(Ring_VirtualMachine* rvm, RVM_Array* src) {
    RVM_Array* array  = nullptr;

    array             = rvm_gc_new_array_meta(rvm,
                                              src->type, src->class_ref, src->dimension);
    array->length     = src->length;
    array->capacity   = src->capacity;


    size_t alloc_size = 0;

    switch (src->type) {
    case RVM_ARRAY_BOOL:
        alloc_size          = sizeof(bool) * array->capacity;
        array->u.bool_array = (bool*)mem_alloc(rvm->data_pool, alloc_size);
        memcpy(array->u.bool_array, src->u.bool_array, alloc_size);
        break;

    case RVM_ARRAY_INT:
        alloc_size         = sizeof(int) * array->capacity;
        array->u.int_array = (int*)mem_alloc(rvm->data_pool, alloc_size);
        memcpy(array->u.int_array, src->u.int_array, alloc_size);
        break;

    case RVM_ARRAY_INT64:
        alloc_size           = sizeof(long long) * array->capacity;
        array->u.int64_array = (long long*)mem_alloc(rvm->data_pool, alloc_size);
        memcpy(array->u.int64_array, src->u.int64_array, alloc_size);
        break;

    case RVM_ARRAY_DOUBLE:
        alloc_size            = sizeof(double) * array->capacity;
        array->u.double_array = (double*)mem_alloc(rvm->data_pool, alloc_size);
        memcpy(array->u.double_array, src->u.double_array, alloc_size);
        break;

    case RVM_ARRAY_STRING:
        array->u.string_array = (RVM_String*)mem_alloc(rvm->data_pool,
                                                       sizeof(RVM_String) * array->capacity);
        for (unsigned int i = 0; i < array->length; i++) {
            RVM_String* tmp          = rvm_deep_copy_string(rvm, &(src->u.string_array[i]));
            array->u.string_array[i] = *tmp;
        }
        break;

    case RVM_ARRAY_CLASS_OBJECT:
        array->class_ref        = src->class_ref;
        array->u.class_ob_array = (RVM_ClassObject*)mem_alloc(rvm->meta_pool, // FIXME: data_pool
                                                              sizeof(RVM_ClassObject) * array->capacity);
        for (unsigned int i = 0; i < src->length; i++) {
            RVM_ClassObject* tmp       = rvm_deep_copy_class_ob(rvm, &(src->u.class_ob_array[i]));
            array->u.class_ob_array[i] = *tmp;
        }
        break;

    case RVM_ARRAY_A:
        array->u.a_array = (RVM_Array*)mem_alloc(rvm->meta_pool,
                                                 sizeof(RVM_Array) * array->capacity);

        for (unsigned int i = 0; i < array->length; i++) {
            RVM_Array* tmp      = rvm_deep_copy_array(rvm, &(src->u.a_array[i]));
            array->u.a_array[i] = *tmp;
        }
        break;

    default:
        break;
    }


    rvm_heap_alloc_size_incr(rvm, alloc_size);


    return array;
}

unsigned int rvm_free_array(Ring_VirtualMachine* rvm, RVM_Array* array) {
    unsigned int free_size = 0;

    switch (array->type) {
    case RVM_ARRAY_BOOL:
        free_size = sizeof(bool) * array->capacity;
        mem_free(rvm->data_pool, array->u.bool_array, free_size);
        break;
    case RVM_ARRAY_INT:
        free_size = sizeof(int) * array->capacity;
        mem_free(rvm->data_pool, array->u.int_array, free_size);
        break;
    case RVM_ARRAY_INT64:
        free_size = sizeof(long long) * array->capacity;
        mem_free(rvm->data_pool, array->u.int64_array, free_size);
        break;
    case RVM_ARRAY_DOUBLE:
        free_size = sizeof(double) * array->capacity;
        mem_free(rvm->data_pool, array->u.double_array, free_size);
        break;
    case RVM_ARRAY_STRING:
        // TODO:
        break;
    case RVM_ARRAY_CLASS_OBJECT:
        // TODO:
        break;
    case RVM_ARRAY_CLOSURE:
        // TODO:
        break;
    case RVM_ARRAY_A:
        // TODO:
        break;
    default: break;
    }

    return free_size;
}


RVM_ClassObject* rvm_gc_new_class_ob_meta(Ring_VirtualMachine* rvm) {
    RVM_ClassObject* class_object = (RVM_ClassObject*)mem_alloc(rvm->meta_pool, sizeof(RVM_ClassObject));
    class_object->gc_type         = RVM_GC_OBJECT_TYPE_CLASS_OB;
    class_object->gc_mark         = GC_MARK_COLOR_WHITE;
    class_object->gc_prev         = nullptr;
    class_object->gc_next         = nullptr;
    class_object->class_ref       = nullptr;
    class_object->field_count     = 0;
    class_object->field_list      = nullptr;

    rvm_heap_list_add_object(rvm, (RVM_GC_Object*)class_object);

    return class_object;
}


/*
 * create array in heap
 *
 * support create one-dimensional array only.
 *
 */
void rvm_fill_class_ob(Ring_VirtualMachine* rvm,
                       RVM_ClassObject*     class_ob,
                       RVM_ClassDefinition* class_definition) {

    assert(class_definition != nullptr);

    RVM_Value*           field_list             = nullptr;
    RVM_String*          field_string           = nullptr;
    RVM_ClassObject*     field_class_ob         = nullptr;
    RVM_ClassDefinition* field_class_definition = nullptr;
    RVM_Array*           field_array            = nullptr;
    size_t               alloc_meta_size        = 0;
    size_t               alloc_data_size        = 0;

    alloc_meta_size                             = class_definition->field_size * sizeof(RVM_Value);
    field_list                                  = (RVM_Value*)mem_alloc(rvm->meta_pool,
                                                                        alloc_meta_size);
    memset(field_list, 0, alloc_meta_size);

    for (unsigned int field_index = 0;
         field_index < class_definition->field_size;
         field_index++) {

        RVM_TypeSpecifier* type_specifier = class_definition->field_list[field_index].type_specifier;

        switch (type_specifier->kind) {
        case RING_BASIC_TYPE_BOOL:
            field_list[field_index].type         = RVM_VALUE_TYPE_BOOL;
            field_list[field_index].u.bool_value = RVM_FALSE;
            alloc_data_size += 1;
            break;
        case RING_BASIC_TYPE_INT:
            field_list[field_index].type        = RVM_VALUE_TYPE_INT;
            field_list[field_index].u.int_value = 0;
            alloc_data_size += 4;
            break;
        case RING_BASIC_TYPE_INT64:
            field_list[field_index].type          = RVM_VALUE_TYPE_INT64;
            field_list[field_index].u.int64_value = 0;
            alloc_data_size += 8;
            break;
        case RING_BASIC_TYPE_DOUBLE:
            field_list[field_index].type           = RVM_VALUE_TYPE_DOUBLE;
            field_list[field_index].u.double_value = 0.0;
            alloc_data_size += 8;
            break;
        case RING_BASIC_TYPE_STRING:
            field_string = rvm_gc_new_string_meta(rvm);
            rvm_fill_string(rvm, field_string, ROUND_UP8(1));
            field_list[field_index].type           = RVM_VALUE_TYPE_STRING;
            field_list[field_index].u.string_value = field_string;
            break;
        case RING_BASIC_TYPE_CLASS:
            field_class_definition = &(rvm->class_list[type_specifier->u.class_def_index]);
            field_class_ob         = rvm_gc_new_class_ob_meta(rvm);
            rvm_fill_class_ob(rvm, field_class_ob, field_class_definition);
            field_list[field_index].type             = RVM_VALUE_TYPE_CLASS_OB;
            field_list[field_index].u.class_ob_value = field_class_ob;
            break;
        case RING_BASIC_TYPE_ARRAY:
            field_array                           = nullptr;
            field_list[field_index].type          = RVM_VALUE_TYPE_ARRAY;
            field_list[field_index].u.array_value = field_array;
            alloc_data_size += 8;
            break;
        default:
            break;
        }
    }


    class_ob->class_ref   = class_definition;
    class_ob->field_count = class_definition->field_size;
    class_ob->field_list  = field_list;

    rvm_heap_alloc_size_incr(rvm, alloc_data_size);
}


RVM_ClassObject* rvm_deep_copy_class_ob(Ring_VirtualMachine* rvm, RVM_ClassObject* src) {
    RVM_ClassObject*     class_object     = rvm_gc_new_class_ob_meta(rvm);

    RVM_ClassDefinition* class_definition = src->class_ref;

    RVM_Value*           field_list       = nullptr;
    RVM_String*          field_string     = nullptr;
    RVM_ClassObject*     field_class_ob   = nullptr;
    RVM_Array*           field_array      = nullptr;
    size_t               alloc_meta_size  = 0;
    size_t               alloc_data_size  = 0;

    alloc_meta_size                       = class_definition->field_size * sizeof(RVM_Value);
    field_list                            = (RVM_Value*)mem_alloc(rvm->meta_pool,
                                                                  alloc_meta_size);

    memcpy(field_list, src->field_list, src->field_count * sizeof(RVM_Value));

    for (unsigned int field_index = 0;
         field_index < class_definition->field_size;
         field_index++) {

        RVM_TypeSpecifier* type_specifier = class_definition->field_list[field_index].type_specifier;

        switch (type_specifier->kind) {
        case RING_BASIC_TYPE_BOOL:
            // bool 无需重新copy，直接计算空间即可
            alloc_data_size += 1;
            break;
        case RING_BASIC_TYPE_INT:
            // int 无需重新copy，直接计算空间即可
            alloc_data_size += 4;
            break;
        case RING_BASIC_TYPE_INT64:
            // int64 无需重新copy，直接计算空间即可
            alloc_data_size += 8;
            break;
        case RING_BASIC_TYPE_DOUBLE:
            // double 无需重新copy，直接计算空间即可
            alloc_data_size += 8;
            break;
        case RING_BASIC_TYPE_STRING:
            field_string                           = rvm_deep_copy_string(rvm, src->field_list[field_index].u.string_value);
            field_list[field_index].type           = RVM_VALUE_TYPE_STRING;
            field_list[field_index].u.string_value = field_string;
            break;
        case RING_BASIC_TYPE_CLASS:
            field_class_ob                           = rvm_deep_copy_class_ob(rvm, src->field_list[field_index].u.class_ob_value);
            field_list[field_index].type             = RVM_VALUE_TYPE_CLASS_OB;
            field_list[field_index].u.class_ob_value = field_class_ob;
            break;
        case RING_BASIC_TYPE_ARRAY:
            field_array                           = rvm_deep_copy_array(rvm, src->field_list[field_index].u.array_value);
            field_list[field_index].type          = RVM_VALUE_TYPE_ARRAY;
            field_list[field_index].u.array_value = field_array;
            alloc_data_size += 8;
            break;
        default:
            break;
        }
    }

    class_object->class_ref   = src->class_ref;
    class_object->field_count = src->field_count;
    class_object->field_list  = field_list;

    rvm_heap_alloc_size_incr(rvm, alloc_data_size);

    return class_object;
}

unsigned int rvm_free_class_ob(Ring_VirtualMachine* rvm, RVM_ClassObject* class_ob) {
    unsigned int free_size = 0;

    // FIXME: 释放 string class array
    for (unsigned int field_index = 0; field_index < class_ob->field_count; field_index++) {
        switch (class_ob->field_list[field_index].type) {
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
            // TODO:
            break;
        case RVM_VALUE_TYPE_CLASS_OB:
            // TODO:
            break;
        case RVM_VALUE_TYPE_ARRAY:
            // TODO:
            break;
        case RVM_VALUE_TYPE_CLOSURE:
            // TODO:
            break;
        default:
            break;
        }
    }

    if (class_ob->field_list != nullptr) {
        mem_free(rvm->meta_pool,
                 class_ob->field_list,
                 class_ob->field_count * sizeof(RVM_Value));
    }
    free_size = class_ob->field_count * sizeof(RVM_Value);
    mem_free(rvm->meta_pool, class_ob, sizeof(RVM_ClassObject));
    return free_size;
}