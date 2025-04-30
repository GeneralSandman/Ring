#include "ring.hpp"
#include <assert.h>
#include <cstring>
#include <ctime>


void rvm_heap_alloc_size_incr(Ring_VirtualMachine* rvm, long long size) {
    rvm->runtime_heap->alloc_size += size;
}

long long rvm_heap_size(Ring_VirtualMachine* rvm) {
    return rvm->runtime_heap->alloc_size;
}

void rvm_heap_list_add_object(Ring_VirtualMachine* rvm, RVM_GC_Object* object) {
    assert(object != nullptr);

    object->gc_next = rvm->runtime_heap->list;
    if (rvm->runtime_heap->list != nullptr) {
        rvm->runtime_heap->list->gc_prev = object;
    }

    rvm->runtime_heap->list = object;

#ifdef DEBUG_RVM_HEAP_ALLOC
    unsigned int count = 0;
    for (RVM_GC_Object* obj = rvm->runtime_heap->list; obj != nullptr; obj = obj->gc_next) {
        count++;
    }
    debug_rvm_heap_alloc_with_green("heap_list gc_type:%d gc_object:%p heap_list_count:%u",
                                    object->gc_type,
                                    object,
                                    count);
#endif
}

void rvm_heap_list_remove_object(Ring_VirtualMachine* rvm, RVM_GC_Object* object) {
    assert(rvm != nullptr);
    assert(rvm->runtime_heap != nullptr);
    assert(object != nullptr);

    if (object->gc_prev != nullptr) {
        object->gc_prev->gc_next = object->gc_next;
    }
    if (object->gc_next != nullptr) {
        object->gc_next->gc_prev = object->gc_prev;
    }
    // new head
    if (object->gc_prev == nullptr) {
        rvm->runtime_heap->list = object->gc_next;
    }

    object->gc_prev = nullptr;
    object->gc_next = nullptr;

#ifdef DEBUG_RVM_HEAP_ALLOC
    unsigned int count = 0;
    for (RVM_GC_Object* obj = rvm->runtime_heap->list; obj != nullptr; obj = obj->gc_next) {
        count++;
    }
    debug_rvm_heap_alloc_with_green("heap_list gc_type:%d gc_object:%p heap_list_count: %u",
                                    object->gc_type,
                                    object,
                                    count);
#endif
}

/*
 * 基于三色标记的增量式垃圾回收机制
 */
void gc_incremental(Ring_VirtualMachine* rvm) {
}

/*
 * Garbage Collection
 *
 * 目前采用最简单的: mark&sweep算法
 * 1. gc 的过程会暂停程序
 */

void gc_make_sweep(Ring_VirtualMachine* rvm) {
#ifdef DEBUG_RVM_GC_DETAIL
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    long long start_timestamp = (long long)(ts.tv_sec) * 1000000000 + ts.tv_nsec;
    printf_witch_red("============Debug RVM GC Detail(Begin)============\n");
    debug_gc_summary(rvm, "BeforeMark");
#endif

#ifdef DEBUG_RVM_GC_DETAIL
    printf_witch_yellow("-----------------GC Mark -----------------\n");
#endif
    gc_mark(rvm);

#ifdef DEBUG_RVM_GC_DETAIL
    printf_witch_yellow("-----------------GC Sweep-----------------\n");
#endif
    gc_sweep(rvm);

#ifdef DEBUG_RVM_GC_DETAIL
    clock_gettime(CLOCK_REALTIME, &ts);
    long long end_timestamp = (long long)(ts.tv_sec) * 1000000000 + ts.tv_nsec;
    printf_witch_yellow("gc use time:%f ms\n", double(end_timestamp - start_timestamp) / 1000000.0);
    debug_gc_summary(rvm, "AfterSweep");
    printf_witch_red("============Debug RVM GC Detail(End)==============\n\n");
#endif
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
        gc_mark_rvm_value(value);
    }

    //  2. runtime stack 变量 指向的位置 需要标记
    // TODO: 这里是收集的当前协程的空间
    for (unsigned int stack_index = 0; stack_index < VM_CUR_CO_STACK_TOP_INDEX; stack_index++) {
        RVM_Value* value = &(VM_CUR_CO_STACK_DATA[stack_index]);
        gc_mark_rvm_value(value);
    }
}

void gc_sweep(Ring_VirtualMachine* rvm) {
    RVM_GC_Object* head = rvm->runtime_heap->list;
    RVM_GC_Object* next = nullptr;
    for (; head != nullptr; head = next) {
        next = head->gc_next;

        if (head->gc_mark == GC_MARK_COLOR_BLACK) {
            head->gc_mark = GC_MARK_COLOR_WHITE;
            continue;
        }
        rvm_free_object(rvm, head);
    }
}

void gc_mark_rvm_value(RVM_Value* value) {
    std::string type;

    switch (value->type) {
    case RVM_VALUE_TYPE_STRING:
        type = "string";
        //
        value->u.string_value->gc_mark = GC_MARK_COLOR_BLACK;
        break;
    case RVM_VALUE_TYPE_CLASS_OB:
        type = "class-ob";
        gc_mark_class_ob(value->u.class_ob_value);
        break;
    case RVM_VALUE_TYPE_ARRAY:
        type = "array";
        gc_mark_array(value->u.array_value);
        break;
    case RVM_VALUE_TYPE_CLOSURE:
        type = "closure";
        gc_mark_closure(value->u.closure_value);
        break;
    default:
        return;
        break;
    }

    debug_rvm_heap_alloc_with_green("mark %10s %p", type.c_str(), (void*)(value->u.string_value));
}

void gc_mark_class_ob(RVM_ClassObject* class_ob) {
    class_ob->gc_mark = GC_MARK_COLOR_BLACK;

    for (unsigned int field_index = 0;
         field_index < class_ob->field_count;
         field_index++) {
        RVM_Value* value = &class_ob->field_list[field_index];
        gc_mark_rvm_value(value);
    }
}

void gc_mark_array(RVM_Array* array) {
    array->gc_mark = GC_MARK_COLOR_BLACK;

    for (unsigned int i = 0; i < array->length; i++) {
        switch (array->type) {
        case RVM_ARRAY_STRING:
            debug_rvm_heap_alloc_with_green("mark array:string %p", array->u.string_array[i]);
            array->u.string_array[i]->gc_mark = GC_MARK_COLOR_BLACK;
            break;
        case RVM_ARRAY_CLASS_OBJECT:
            debug_rvm_heap_alloc_with_green("mark array:class-ob %p", array->u.class_ob_array[i]);
            array->u.class_ob_array[i]->gc_mark = GC_MARK_COLOR_BLACK;
            gc_mark_class_ob(array->u.class_ob_array[i]);
            break;
        case RVM_ARRAY_CLOSURE:
            debug_rvm_heap_alloc_with_green("mark array:closure %p", array->u.closure_array[i]);
            array->u.closure_array[i]->gc_mark = GC_MARK_COLOR_BLACK;
            break;
        case RVM_ARRAY_A:
            array->u.a_array[i]->gc_mark = GC_MARK_COLOR_BLACK;
            gc_mark_array(array->u.a_array[i]);
            break;
        default:
            break;
        }
    }
}

void gc_mark_closure(RVM_Closure* closure) {
    debug_rvm_heap_alloc_with_green("mark closure %p", closure);

    if (closure->gc_mark == GC_MARK_COLOR_BLACK) {
        return;
    }

    closure->gc_mark = GC_MARK_COLOR_BLACK;

    if (closure->fvb == nullptr) {
        return;
    }

    gc_mark_fvb(closure->fvb);
}

void gc_mark_fvb(RVM_FreeValueBlock* fvb) {
    if (fvb->gc_mark == GC_MARK_COLOR_BLACK) {
        return;
    }

    fvb->gc_mark = GC_MARK_COLOR_BLACK;

    for (unsigned int i = 0;
         i < fvb->size;
         i++) {
        gc_mark_free_value(&fvb->list[i]);
    }
}

void gc_mark_free_value(RVM_FreeValue* free_value) {
    if (free_value->is_recur) {
        gc_mark_free_value(free_value->u.recur);
    } else {
        if (free_value->belong_closure != nullptr) {
            gc_mark_closure(free_value->belong_closure);
        }

        gc_mark_rvm_value(free_value->u.p);
    }
}

void rvm_free_object(Ring_VirtualMachine* rvm, RVM_GC_Object* object) {
    assert(object != nullptr);

    size_t      free_size = 0;

    std::string type;

    // 一定先从heap中移除
    rvm_heap_list_remove_object(rvm, object);

    switch (object->gc_type) {
    case RVM_GC_OBJECT_TYPE_STRING:
        type      = "string";
        free_size = rvm_free_string(rvm, (RVM_String*)object);
        break;

    case RVM_GC_OBJECT_TYPE_CLASS_OB:
        type      = "class-ob";
        free_size = rvm_free_class_ob(rvm, (RVM_ClassObject*)object);
        break;

    case RVM_GC_OBJECT_TYPE_ARRAY:
        type      = "array";
        free_size = rvm_free_array(rvm, (RVM_Array*)object);
        break;

    case RVM_GC_OBJECT_TYPE_CLOSURE:
        type      = "closure";
        free_size = rvm_free_closure(rvm, (RVM_Closure*)object);
        break;

    case RVM_GC_OBJECT_TYPE_FVB:
        type      = "fvb";
        free_size = rvm_free_fvb(rvm, (RVM_FreeValueBlock*)object);
        break;

    default:
        break;
    }

    debug_rvm_heap_alloc_with_green("rvm_free_object: %10s %p free_size:%zu", type.c_str(), object, free_size);

    rvm_heap_alloc_size_incr(rvm, -free_size);
}

RVM_String* new_string_meta() {
    RVM_String* string = (RVM_String*)mem_alloc(NULL_MEM_POOL, sizeof(RVM_String));
    string->gc_type    = RVM_GC_OBJECT_TYPE_STRING;
    string->gc_mark    = GC_MARK_COLOR_WHITE;
    string->gc_prev    = nullptr;
    string->gc_next    = nullptr;
    string->length     = 0;
    string->capacity   = 0;
    string->data       = nullptr;
    return string;
}

// 不分配在 heap上
RVM_String* string_literal_to_rvm_string(const char* string_literal) {

    RVM_String* string    = new_string_meta();

    size_t      length    = 0;
    length                = (string_literal != nullptr) ? strlen(string_literal) : 0;
    unsigned int capacity = ROUND_UP8(length);
    if (capacity == 0)
        capacity = 8;

    unsigned int alloc_size = capacity * sizeof(char);
    string->length          = 0;
    string->capacity        = capacity;
    string->data            = (char*)mem_alloc(NULL_MEM_POOL, alloc_size);
    memset(string->data, 0, alloc_size);

    strncpy(string->data, string_literal, length);
    string->length = length;

    return string;
}

RVM_String* rvm_gc_new_rvm_string(Ring_VirtualMachine* rvm, const char* string_literal) {
    RVM_String* string    = rvm_gc_new_string_meta(rvm);

    size_t      length    = 0;
    length                = (string_literal != nullptr) ? strlen(string_literal) : 0;
    unsigned int capacity = ROUND_UP8(length);
    if (capacity == 0)
        capacity = 8;

    rvm_fill_string(rvm, string, capacity);

    strncpy(string->data, string_literal, length);
    string->length = length;

    return string;
}

RVM_String* rvm_gc_new_string_meta(Ring_VirtualMachine* rvm) {
    RVM_String* string = (RVM_String*)mem_alloc(rvm->data_pool, sizeof(RVM_String));
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
    debug_rvm_heap_alloc_with_green("rvm_fill_string: %p alloc_size:%u  [heap_size:%lld]",
                                    string,
                                    alloc_size,
                                    rvm_heap_size(rvm));
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
    debug_rvm_heap_alloc_with_green("rvm_deep_copy_string: %p alloc_size:%u  [heap_size:%lld]",
                                    string,
                                    alloc_size,
                                    rvm_heap_size(rvm));

    return string;
}

RVM_String* concat_string(Ring_VirtualMachine* rvm, RVM_String* a, RVM_String* b) {
    assert(a != nullptr);
    assert(b != nullptr);

    RVM_String* string;

    string = rvm_gc_new_string_meta(rvm);
    rvm_fill_string(rvm, string, ROUND_UP8(a->length + b->length));

    string->length = a->length + b->length;
    strncpy(string->data, a->data, a->length);
    strncpy(string->data + a->length, b->data, b->length);

    return string;
}

unsigned int rvm_free_string(Ring_VirtualMachine* rvm, RVM_String* string) {
    assert(string != nullptr);

    // 释放真正的数据
    if (string->data != nullptr) {
        mem_free(rvm->data_pool, (void*)string->data, string->capacity * sizeof(char));
    }
    unsigned int free_size = string->capacity * sizeof(char);
    // 释放元信息
    mem_free(rvm->data_pool, string, sizeof(RVM_String));

    return free_size;
}


RVM_Array* rvm_gc_new_array_meta(Ring_VirtualMachine* rvm,
                                 RVM_Array_Type       array_type,
                                 Ring_BasicType       item_type_kind,
                                 RVM_ClassDefinition* class_definition,
                                 unsigned int         dimension) {

    RVM_Array* array      = (RVM_Array*)mem_alloc(rvm->data_pool, sizeof(RVM_Array));
    array->gc_type        = RVM_GC_OBJECT_TYPE_ARRAY;
    array->gc_mark        = GC_MARK_COLOR_WHITE;
    array->gc_prev        = nullptr;
    array->gc_next        = nullptr;
    array->type           = array_type;
    array->dimension      = dimension;
    array->length         = 0;
    array->capacity       = 0;
    array->item_type_kind = item_type_kind;
    array->class_ref      = class_definition;
    array->u.bool_array   = nullptr;

    rvm_heap_list_add_object(rvm, (RVM_GC_Object*)array);

    return array;
}

// dimension 为 len(dimension_list) , 也就是总共要分配的维度
// dimension_list 为 {3,4,5} 代表分配一个3维数组，从外到内每个维度为3,4,5, 即为 new bool[3,4,5]
// dimension_index 为 2 代表分配2维数组，会递归减小
//
// dimension_list 为 {4, 0, 0}, dimension = 3, 表示只分配最外围的源信息，size 为4
RVM_Array* rvm_new_array(Ring_VirtualMachine* rvm,
                         unsigned int         dimension,
                         unsigned int*        dimension_list,
                         unsigned int         dimension_index,
                         RVM_Array_Type       array_type,
                         Ring_BasicType       item_type_kind,
                         RVM_ClassDefinition* class_definition) {

    if (dimension_index == 0) {
        return nullptr;
    }
    assert(0 <= dimension - dimension_index && dimension - dimension_index < dimension);
    RVM_Array*   array      = nullptr;
    unsigned int alloc_size = 0;

    array                   = rvm_gc_new_array_meta(rvm,
                                                    array_type,
                                                    item_type_kind,
                                                    class_definition,
                                                    dimension_index);
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
            alloc_size            = sizeof(RVM_String*) * array->capacity;
            array->u.string_array = (RVM_String**)mem_alloc(rvm->data_pool, alloc_size);
            alloc_size            = 0; // gc-object 元信息不计入 heap的空间
            for (unsigned int i = 0; i < array->length; i++) {
                RVM_String* string_value = rvm_gc_new_string_meta(rvm);
                rvm_fill_string(rvm, string_value, ROUND_UP8(1));
                array->u.string_array[i] = string_value;
            }
            break;
        case RVM_ARRAY_CLASS_OBJECT:
            assert(class_definition != nullptr);
            alloc_size              = sizeof(RVM_ClassObject*) * array->capacity;
            array->u.class_ob_array = (RVM_ClassObject**)mem_alloc(rvm->data_pool, alloc_size);
            alloc_size              = 0; // gc-object 元信息不计入 heap的空间
            for (unsigned int i = 0; i < array->length; i++) {
                RVM_ClassObject* class_ob = rvm_gc_new_class_ob_meta(rvm);
                rvm_fill_class_ob(rvm, class_ob, class_definition);
                array->u.class_ob_array[i] = class_ob;
            }
            break;

        case RVM_ARRAY_A:
            // 不会出现这种情况
            break;

        case RVM_ARRAY_CLOSURE:
            alloc_size             = sizeof(RVM_Closure*) * array->capacity;
            array->u.closure_array = (RVM_Closure**)mem_alloc(rvm->data_pool, alloc_size);
            alloc_size             = 0; // gc-object 元信息不计入 heap的空间
            for (unsigned int i = 0; i < array->length; i++) {
                array->u.closure_array[i] = rvm_gc_new_closure_meta(rvm);
            }
            break;
        default:
            break;
        }
    } else {
        // 递归分配多维数组
        array->type      = RVM_ARRAY_A;
        alloc_size       = sizeof(RVM_Array*) * array->capacity;
        array->u.a_array = (RVM_Array**)mem_alloc(rvm->data_pool, alloc_size);
        alloc_size       = 0; // gc-object 元信息不计入 heap的空间

        // 预测下一个维度是否需要分配，如果不需要，则跳过
        if (dimension - (dimension_index - 1) < dimension
            && dimension_list[dimension - (dimension_index - 1)] != 0) {

            for (unsigned int i = 0; i < array->length; i++) {
                array->u.a_array[i] = rvm_new_array(rvm,
                                                    dimension,
                                                    dimension_list,
                                                    dimension_index - 1,
                                                    array_type,
                                                    item_type_kind,
                                                    class_definition);
            }
        }
    }

    rvm_heap_alloc_size_incr(rvm, alloc_size);
    debug_rvm_heap_alloc_with_green("rvm_new_array array_type:%d array->capacity:%d alloc_size:%u   [heap_size:%lld]",
                                    array_type,
                                    array->capacity,
                                    alloc_size,
                                    rvm_heap_size(rvm));

    return array;
}


RVM_Array* rvm_deep_copy_array(Ring_VirtualMachine* rvm, RVM_Array* src) {
    RVM_Array* array        = nullptr;

    array                   = rvm_gc_new_array_meta(rvm,
                                                    src->type,
                                                    src->item_type_kind,
                                                    src->class_ref,
                                                    src->dimension);
    array->length           = src->length;
    array->capacity         = src->capacity;


    unsigned int alloc_size = 0;

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
        alloc_size            = sizeof(RVM_String*) * array->capacity;
        array->u.string_array = (RVM_String**)mem_alloc(rvm->data_pool, alloc_size);
        alloc_size            = 0; // gc-object 元信息不计入 heap的空间
        for (unsigned int i = 0; i < array->length; i++) {
            array->u.string_array[i] = rvm_deep_copy_string(rvm, src->u.string_array[i]);
        }
        break;

    case RVM_ARRAY_CLASS_OBJECT:
        array->class_ref        = src->class_ref;
        alloc_size              = sizeof(RVM_ClassObject*) * array->capacity;
        array->u.class_ob_array = (RVM_ClassObject**)mem_alloc(rvm->data_pool, alloc_size);
        alloc_size              = 0; // gc-object 元信息不计入 heap的空间
        for (unsigned int i = 0; i < array->length; i++) {
            array->u.class_ob_array[i] = rvm_deep_copy_class_ob(rvm, src->u.class_ob_array[i]);
        }
        break;

    case RVM_ARRAY_A:
        alloc_size       = sizeof(RVM_Array*) * array->capacity;
        array->u.a_array = (RVM_Array**)mem_alloc(rvm->data_pool, alloc_size);
        alloc_size       = 0; // gc-object 元信息不计入 heap的空间
        for (unsigned int i = 0; i < array->length; i++) {
            array->u.a_array[i] = rvm_deep_copy_array(rvm, src->u.a_array[i]);
        }
        break;

    case RVM_ARRAY_CLOSURE:
        alloc_size             = sizeof(RVM_Closure*) * array->capacity;
        array->u.closure_array = (RVM_Closure**)mem_alloc(rvm->data_pool, alloc_size);
        alloc_size             = 0; // gc-object 元信息不计入 heap的空间
        for (unsigned int i = 0; i < array->length; i++) {
            array->u.closure_array[i] = rvm_deep_copy_closure(rvm, src->u.closure_array[i]);
        }
        break;

    default:
        break;
    }

    rvm_heap_alloc_size_incr(rvm, alloc_size);
    debug_rvm_heap_alloc_with_green("rvm_deep_copy_array array_type:%d array->capacity:%d alloc_size:%u    [heap_size:%lld]",
                                    src->type,
                                    array->capacity,
                                    alloc_size,
                                    rvm_heap_size(rvm));

    return array;
}

// 两倍增长，默认为8
void rvm_array_growth(Ring_VirtualMachine* rvm, RVM_Array* array) {
    size_t       old_alloc_size = 0;
    size_t       new_alloc_size = 0;

    unsigned int old_cap        = array->capacity;
    if (array->capacity == 0) {
        array->capacity = 8;
    } else {
        array->capacity *= 2;
    }
    unsigned int new_cap = array->capacity;

    switch (array->type) {
    case RVM_ARRAY_BOOL:
        old_alloc_size      = old_cap * sizeof(bool);
        new_alloc_size      = new_cap * sizeof(bool);
        array->u.bool_array = (bool*)mem_realloc(rvm->data_pool,
                                                 array->u.bool_array,
                                                 old_alloc_size,
                                                 new_alloc_size);
        break;
    case RVM_ARRAY_INT:
        old_alloc_size     = old_cap * sizeof(int);
        new_alloc_size     = new_cap * sizeof(int);
        array->u.int_array = (int*)mem_realloc(rvm->data_pool,
                                               array->u.int_array,
                                               old_alloc_size,
                                               new_alloc_size);
        break;
    case RVM_ARRAY_INT64:
        old_alloc_size       = old_cap * sizeof(long long);
        new_alloc_size       = new_cap * sizeof(long long);
        array->u.int64_array = (long long*)mem_realloc(rvm->data_pool,
                                                       array->u.int64_array,
                                                       old_alloc_size,
                                                       new_alloc_size);
        break;
    case RVM_ARRAY_DOUBLE:
        old_alloc_size        = old_cap * sizeof(double);
        new_alloc_size        = new_cap * sizeof(double);
        array->u.double_array = (double*)mem_realloc(rvm->data_pool,
                                                     array->u.double_array,
                                                     old_alloc_size,
                                                     new_alloc_size);
        break;
    case RVM_ARRAY_STRING:
        old_alloc_size        = old_cap * sizeof(RVM_String*);
        new_alloc_size        = new_cap * sizeof(RVM_String*);
        array->u.string_array = (RVM_String**)mem_realloc(rvm->data_pool,
                                                          array->u.string_array,
                                                          old_alloc_size,
                                                          new_alloc_size);
        break;
    case RVM_ARRAY_CLASS_OBJECT:
        old_alloc_size          = old_cap * sizeof(RVM_ClassObject*);
        new_alloc_size          = new_cap * sizeof(RVM_ClassObject*);
        array->u.class_ob_array = (RVM_ClassObject**)mem_realloc(rvm->data_pool,
                                                                 array->u.class_ob_array,
                                                                 old_alloc_size,
                                                                 new_alloc_size);
        break;
    case RVM_ARRAY_A:
        old_alloc_size   = old_cap * sizeof(RVM_Array*);
        new_alloc_size   = new_cap * sizeof(RVM_Array*);
        array->u.a_array = (RVM_Array**)mem_realloc(rvm->data_pool,
                                                    array->u.a_array,
                                                    old_alloc_size,
                                                    new_alloc_size);
        break;
    case RVM_ARRAY_CLOSURE:
        old_alloc_size         = old_cap * sizeof(RVM_Closure*);
        new_alloc_size         = new_cap * sizeof(RVM_Closure*);
        array->u.closure_array = (RVM_Closure**)mem_realloc(rvm->data_pool,
                                                            array->u.closure_array,
                                                            old_alloc_size,
                                                            new_alloc_size);
        break;
    default:
        break;
    }

    rvm_heap_alloc_size_incr(rvm, new_alloc_size - old_alloc_size);
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
        free_size = sizeof(RVM_String*) * array->capacity;
        mem_free(rvm->data_pool, array->u.string_array, free_size);
        free_size = 0; // gc-object 元信息不计入 heap的空间
        // 不必递归向下释放
        break;
    case RVM_ARRAY_CLASS_OBJECT:
        free_size = sizeof(RVM_ClassObject*) * array->capacity;
        mem_free(rvm->data_pool, array->u.class_ob_array, free_size);
        free_size = 0; // gc-object 元信息不计入 heap的空间
        // 不必递归向下释放
        break;
    case RVM_ARRAY_CLOSURE:
        free_size = sizeof(RVM_Closure*) * array->capacity;
        mem_free(rvm->data_pool, array->u.closure_array, free_size);
        free_size = 0; // gc-object 元信息不计入 heap的空间
        // 不必递归向下释放
        break;
    case RVM_ARRAY_A:
        free_size = sizeof(RVM_Array*) * array->capacity;
        mem_free(rvm->data_pool, array->u.a_array, free_size);
        free_size = 0; // gc-object 元信息不计入 heap的空间
        break;
    default: break;
    }

    // 释放元信息
    mem_free(rvm->data_pool, array, sizeof(RVM_Array));

    return free_size;
}


RVM_ClassObject* rvm_gc_new_class_ob_meta(Ring_VirtualMachine* rvm) {
    RVM_ClassObject* class_object = (RVM_ClassObject*)mem_alloc(rvm->data_pool, sizeof(RVM_ClassObject));
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


void rvm_fill_class_ob(Ring_VirtualMachine* rvm,
                       RVM_ClassObject*     class_ob,
                       RVM_ClassDefinition* class_definition) {

    assert(class_definition != nullptr);

    RVM_Value*           field_list             = nullptr;
    RVM_String*          field_string           = nullptr;
    RVM_ClassObject*     field_class_ob         = nullptr;
    RVM_ClassDefinition* field_class_definition = nullptr;
    RVM_Array*           field_array            = nullptr;
    RVM_Closure*         field_closure          = nullptr;

    size_t               alloc_meta_size        = 0;
    unsigned int         alloc_data_size        = 0;

    alloc_meta_size                             = class_definition->field_size * sizeof(RVM_Value);
    field_list                                  = (RVM_Value*)mem_alloc(rvm->data_pool,
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
            alloc_data_size += 0; // 由 string 负责增加
            break;
        case RING_BASIC_TYPE_CLASS:
            field_class_definition = &(rvm->class_list[type_specifier->u.class_def_index]);
            field_class_ob         = rvm_gc_new_class_ob_meta(rvm);
            rvm_fill_class_ob(rvm, field_class_ob, field_class_definition);
            field_list[field_index].type             = RVM_VALUE_TYPE_CLASS_OB;
            field_list[field_index].u.class_ob_value = field_class_ob;
            break;
        case RING_BASIC_TYPE_ARRAY: {
            // 这里没有分配空间, 只分配了一下meta
            // array_type 强制转化一下
            RVM_TypeSpecifier*   sub_type_specifier   = type_specifier->u.array_t->sub;
            RVM_Array_Type       array_type           = convert_rvm_array_type(type_specifier);
            RVM_ClassDefinition* sub_class_definition = nullptr;
            if (sub_type_specifier->kind == RING_BASIC_TYPE_CLASS) {
                sub_class_definition = &(rvm->class_list[sub_type_specifier->u.class_def_index]);
            }

            field_array                           = rvm_gc_new_array_meta(rvm,
                                                                          array_type,
                                                                          sub_type_specifier->kind,
                                                                          sub_class_definition,
                                                                          type_specifier->u.array_t->dimension);
            field_list[field_index].type          = RVM_VALUE_TYPE_ARRAY;
            field_list[field_index].u.array_value = field_array;
            alloc_data_size += 0; // 由 array 负责增加
        } break;
        case RING_BASIC_TYPE_FUNC:
            field_closure                           = nullptr;
            field_list[field_index].type            = RVM_VALUE_TYPE_CLOSURE;
            field_list[field_index].u.closure_value = field_closure;
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
    debug_rvm_heap_alloc_with_green("rvm_fill_class_ob alloc_size:%u   [heap_size:%lld]",
                                    alloc_data_size,
                                    rvm_heap_size(rvm));
}


RVM_ClassObject* rvm_deep_copy_class_ob(Ring_VirtualMachine* rvm, RVM_ClassObject* src) {
    RVM_ClassObject*     class_object     = rvm_gc_new_class_ob_meta(rvm);

    RVM_ClassDefinition* class_definition = src->class_ref;

    RVM_Value*           field_list       = nullptr;
    RVM_String*          field_string     = nullptr;
    RVM_ClassObject*     field_class_ob   = nullptr;
    RVM_Array*           field_array      = nullptr;
    RVM_Closure*         field_closure    = nullptr;

    size_t               alloc_meta_size  = 0;
    size_t               alloc_data_size  = 0;

    alloc_meta_size                       = class_definition->field_size * sizeof(RVM_Value);
    field_list                            = (RVM_Value*)mem_alloc(rvm->data_pool,
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
        case RING_BASIC_TYPE_FUNC:
            field_closure                           = rvm_deep_copy_closure(rvm, src->field_list[field_index].u.closure_value);
            field_list[field_index].type            = RVM_VALUE_TYPE_CLOSURE;
            field_list[field_index].u.closure_value = field_closure;
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
    unsigned int free_meta_size = 0;
    unsigned int free_data_size = 0;

    // TODO: 释放 string class array
    for (unsigned int field_index = 0; field_index < class_ob->field_count; field_index++) {
        switch (class_ob->field_list[field_index].type) {
        case RVM_VALUE_TYPE_BOOL:
            free_data_size += 1;
            break;
        case RVM_VALUE_TYPE_INT:
            free_data_size += 4;
            break;
        case RVM_VALUE_TYPE_INT64:
            free_data_size += 8;
            break;
        case RVM_VALUE_TYPE_DOUBLE:
            free_data_size += 8;
            break;
        case RVM_VALUE_TYPE_STRING:
            free_data_size += 0;
            // 不必递归向下释放
            // string 自己控制生命周期
            break;
        case RVM_VALUE_TYPE_CLASS_OB:
            free_data_size += 0;
            // 不必递归向下释放
            // class 自己控制生命周期
            break;
        case RVM_VALUE_TYPE_ARRAY:
            free_data_size += 0;
            // 不必递归向下释放
            // array 自己控制生命周期
            break;
        case RVM_VALUE_TYPE_CLOSURE:
            free_data_size += rvm_free_closure(rvm, class_ob->field_list[field_index].u.closure_value);
            // TODO: 需要递归释放么
            break;
        default:
            break;
        }
    }

    if (class_ob->field_list != nullptr) {
        free_meta_size = class_ob->field_count * sizeof(RVM_Value);
        mem_free(rvm->data_pool,
                 class_ob->field_list,
                 free_meta_size);
    }
    // 释放元信息
    mem_free(rvm->data_pool, class_ob, sizeof(RVM_ClassObject));
    return free_data_size;
}

RVM_Closure* rvm_gc_new_closure_meta(Ring_VirtualMachine* rvm) {
    RVM_Closure* closure     = (RVM_Closure*)mem_alloc(rvm->data_pool, sizeof(RVM_Closure));
    closure->gc_type         = RVM_GC_OBJECT_TYPE_CLOSURE;
    closure->gc_mark         = GC_MARK_COLOR_WHITE;
    closure->gc_prev         = nullptr;
    closure->gc_next         = nullptr;
    closure->anonymous_func  = nullptr;
    closure->fvb             = nullptr;
    closure->is_root_closure = false;

    rvm_heap_list_add_object(rvm, (RVM_GC_Object*)closure);
    rvm_heap_alloc_size_incr(rvm, 8); // 8字节的元信息
    debug_rvm_heap_alloc_with_green("rvm_gc_new_closure_meta alloc_size:%u   [heap_size:%lld]",
                                    8,
                                    rvm_heap_size(rvm));

    return closure;
}

void rvm_fill_closure(Ring_VirtualMachine* rvm,
                      RVM_Closure*         closure,
                      RVM_Function*        callee_function) {

    assert(callee_function != nullptr);

    closure->anonymous_func = callee_function;

    if (callee_function->free_value_size == 0) {
        return;
    }

    if (closure->fvb == nullptr) {
        closure->fvb = rvm_gc_new_fvb_meta(rvm);
    }

    rvm_fill_fvb(rvm, closure->fvb, callee_function->free_value_size);
}

RVM_Closure* rvm_deep_copy_closure(Ring_VirtualMachine* rvm, RVM_Closure* src) {
    return src;
}

unsigned int rvm_free_closure(Ring_VirtualMachine* rvm, RVM_Closure* closure) {

    debug_rvm_heap_alloc_with_green("closure %p", closure);
    // 释放元信息
    mem_free(rvm->data_pool, closure, sizeof(RVM_Closure));
    unsigned int free_data_size = 0;
    free_data_size += 8; // 释放元信息
    return free_data_size;
}

RVM_FreeValueBlock* rvm_gc_new_fvb_meta(Ring_VirtualMachine* rvm) {
    RVM_FreeValueBlock* fvb = (RVM_FreeValueBlock*)mem_alloc(rvm->data_pool, sizeof(RVM_FreeValueBlock));
    fvb->gc_type            = RVM_GC_OBJECT_TYPE_FVB;
    fvb->gc_mark            = GC_MARK_COLOR_WHITE;
    fvb->gc_prev            = nullptr;
    fvb->gc_next            = nullptr;
    fvb->size               = 0;
    fvb->list               = nullptr;

    rvm_heap_list_add_object(rvm, (RVM_GC_Object*)fvb);
    rvm_heap_alloc_size_incr(rvm, 8); // 8字节的元信息
    debug_rvm_heap_alloc_with_green("rvm_gc_new_fvb_meta alloc_size:%u   [heap_size:%lld]",
                                    8,
                                    rvm_heap_size(rvm));

    return fvb;
}

void rvm_fill_fvb(Ring_VirtualMachine* rvm,
                  RVM_FreeValueBlock*  fvb,
                  unsigned int         free_value_size) {

    unsigned int alloc_data_size = free_value_size * sizeof(RVM_FreeValue);

    fvb->size                    = free_value_size;
    fvb->list                    = (RVM_FreeValue*)mem_alloc(rvm->data_pool, alloc_data_size);

    rvm_heap_alloc_size_incr(rvm, alloc_data_size);
    debug_rvm_heap_alloc_with_green("rvm_fill_fvb alloc_size:%u   [heap_size:%lld]",
                                    alloc_data_size,
                                    rvm_heap_size(rvm));
}

unsigned int rvm_free_fvb(Ring_VirtualMachine* rvm, RVM_FreeValueBlock* fvb) {
    // 释放 free_value
    for (unsigned int i = 0;
         i < fvb->size;
         i++) {
        // TODO: 释放具体的 free_value实际数据
    }

    unsigned int alloc_data_size = fvb->size * sizeof(RVM_FreeValue);
    mem_free(rvm->data_pool,
             fvb->list, alloc_data_size);

    return alloc_data_size;
}