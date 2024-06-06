#include <iostream>

#include "ring.hpp"

std::string fmt_any(RVM_Value* value) {
    switch (value->type) {
    case RVM_VALUE_TYPE_BOOL:
        return fmt_bool(value);
        break;
    case RVM_VALUE_TYPE_INT:
        return fmt_int(value);
        break;
    case RVM_VALUE_TYPE_INT64:
        return fmt_int64(value);
        break;
    case RVM_VALUE_TYPE_DOUBLE:
        return fmt_double(value);
        break;
    case RVM_VALUE_TYPE_STRING:
        return fmt_string(value);
        break;
    case RVM_VALUE_TYPE_CLASS_OB:
        return fmt_class(value);
        break;
    case RVM_VALUE_TYPE_ARRAY:
        return fmt_array(value);
        break;
    default:
        break;
    }

    return "";
}

std::string fmt_bool(RVM_Value* value) {
    if (value->u.bool_value) {
        return "true";
    } else {
        return "false";
    }
}

std::string fmt_int(RVM_Value* value) {
    return std::to_string(value->u.int_value);
}


std::string fmt_int64(RVM_Value* value) {
    return std::to_string(value->u.int64_value);
}

std::string fmt_double(RVM_Value* value) {
    return std::to_string(value->u.double_value);
}

std::string fmt_string(RVM_Value* value) {
    std::string res;
    res.assign(value->u.string_value->data, value->u.string_value->length);
    return res;
}

std::string fmt_class(RVM_Value* value) {
    return fmt_class(value->u.class_ob_value);
}

std::string fmt_class(RVM_ClassObject* class_object) {
    RVM_ClassDefinition* class_def = class_object->class_ref;

    std::string          result;

    result += "{";
    for (unsigned int i = 0; i < class_def->field_size; i++) {
        if (i != 0) {
            result += " ";
        }

        result += class_def->field_list[i].identifier;
        result += ":";
        result += fmt_any(&class_object->field[i]);
    }

    result += "}";

    return result;
}

std::string fmt_array(RVM_Value* value) {
    return fmt_array(value->u.array_value);
}

std::string fmt_array(RVM_Array* array_value) {
    std::string result;

    result += "[";
    for (unsigned int i = 0; array_value != nullptr && i < array_value->length; i++) {
        if (i != 0) {
            result += " ";
        }

        switch (array_value->type) {
        case RVM_ARRAY_BOOL:
            result += array_value->u.bool_array[i];
            break;
        case RVM_ARRAY_INT:
            result += std::to_string(array_value->u.int_array[i]);
            break;
        case RVM_ARRAY_INT64:
            result += std::to_string(array_value->u.int64_array[i]);
            break;
        case RVM_ARRAY_DOUBLE:
            result += std::to_string(array_value->u.double_array[i]);
            break;
        case RVM_ARRAY_STRING: {
            std::string tmp;
            tmp.assign(array_value->u.string_array[i]->data, array_value->u.string_array[i]->length);
            result += tmp;
        } break;
        case RVM_ARRAY_CLASS_OBJECT:
            result += fmt_class(&array_value->u.class_ob_array[i]);
            break;
        case RVM_ARRAY_A:
            result += fmt_array(&array_value->u.a_array[i]);
            break;

        default:
            break;
        }
    }

    result += "]";

    return result;
}
