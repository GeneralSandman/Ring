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
        return fmt_string(value->u.string_value);
        break;
    case RVM_VALUE_TYPE_CLASS_OB:
        return fmt_class(value->u.class_ob_value);
        break;
    case RVM_VALUE_TYPE_ARRAY:
        return fmt_array(value->u.array_value);
        break;
    case RVM_VALUE_TYPE_CLOSURE:
        return fmt_closure(value->u.closure_value);
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

std::string fmt_string(RVM_String* string_value) {
    std::string res;
    res.assign(string_value->data, string_value->length);
    return res;
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
        result += fmt_any(&class_object->field_list[i]);
    }

    result += "}";

    return result;
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
            if (array_value->u.bool_array[i]) {
                result += "true";
            } else {
                result += "false";
            }
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
            tmp.assign(array_value->u.string_array[i].data, array_value->u.string_array[i].length);
            result += tmp;
        } break;
        case RVM_ARRAY_CLASS_OBJECT:
            result += fmt_class(&array_value->u.class_ob_array[i]);
            break;
        case RVM_ARRAY_CLOSURE:
            result += fmt_closure(&array_value->u.closure_array[i]);
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


std::string fmt_closure(RVM_Closure* closure) {
    if (closure == nullptr || closure->anonymous_func == nullptr) {
        return "nil";
    }
    return sprintf_string("closure(%p)", closure);
}

std::string var_dump_any(Package_Executer* package_executer,
                         RVM_Value*        value,
                         unsigned int      indent) {

    switch (value->type) {
    case RVM_VALUE_TYPE_BOOL:
        return var_dump_bool(value);
        break;
    case RVM_VALUE_TYPE_INT:
        return var_dump_int(value);
        break;
    case RVM_VALUE_TYPE_INT64:
        return var_dump_int64(value);
        break;
    case RVM_VALUE_TYPE_DOUBLE:
        return var_dump_double(value);
        break;
    case RVM_VALUE_TYPE_STRING:
        return var_dump_string(value->u.string_value);
        break;
    case RVM_VALUE_TYPE_CLASS_OB:
        return var_dump_class(package_executer, value->u.class_ob_value, indent);
        break;
    case RVM_VALUE_TYPE_ARRAY:
        return var_dump_array(package_executer, value->u.array_value, indent);
        break;
    case RVM_VALUE_TYPE_CLOSURE:
        return var_dump_closure(package_executer, value->u.closure_value);
        break;
    default:
        break;
    }

    return "";
}


std::string var_dump_bool(RVM_Value* value) {
    std::string res;
    res = sprintf_string("bool(%s)", fmt_bool(value).c_str());
    return res;
}

std::string var_dump_int(RVM_Value* value) {
    std::string res;
    res = sprintf_string("int(%s)", fmt_int(value).c_str());
    return res;
}


std::string var_dump_int64(RVM_Value* value) {
    std::string res;
    res = sprintf_string("int64(%s)", fmt_int64(value).c_str());
    return res;
}

std::string var_dump_double(RVM_Value* value) {
    std::string res;
    res = sprintf_string("double(%s)", fmt_double(value).c_str());
    return res;
}

std::string var_dump_string(RVM_String* string_value) {
    std::string res;
    res = sprintf_string("string(len:%u, cap:%u) => \"%s\"",
                         string_value->length,
                         string_value->capacity,
                         fmt_string(string_value).c_str());
    return res;
}

// TODO: 缩进展示
std::string var_dump_class(Package_Executer* package_executer,
                           RVM_ClassObject*  class_object,
                           unsigned int      indent) {

    RVM_ClassDefinition* class_def = class_object->class_ref;
    std::string          detail;
    std::string          line_prefix = build_indent(indent + 1, "    ");

    detail += "{";
    for (unsigned int i = 0; i < class_def->field_size; i++) {
        detail += "\n" + line_prefix;
        detail += class_def->field_list[i].identifier;
        detail += ": ";
        detail += var_dump_any(package_executer, &class_object->field_list[i], indent + 1);
    }
    if (class_def->field_size) {
        detail += "\n" + build_indent(indent, "    ");
        detail += "}";
    }


    std::string res;
    res = sprintf_string("%s(fields:%u, methods:%u) => %s",
                         formate_class_type(class_object).c_str(),
                         class_def->field_size,
                         class_def->method_size,
                         detail.c_str());
    return res;
}

std::string var_dump_array(Package_Executer* package_executer,
                           RVM_Array*        array_value,
                           unsigned int      indent) {

    std::string result;
    std::string line_prefix = build_indent(indent + 1, "    ");

    result += "[";
    for (unsigned int i = 0; array_value != nullptr && i < array_value->length; i++) {
        result += "\n" + line_prefix;
        result += sprintf_string("[%u] -> ", i);

        switch (array_value->type) {
        case RVM_ARRAY_BOOL:
            if (array_value->u.bool_array[i]) {
                result += "true";
            } else {
                result += "false";
            }
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
        case RVM_ARRAY_STRING:
            result += var_dump_string(&array_value->u.string_array[i]);
            break;
        case RVM_ARRAY_CLASS_OBJECT:
            result += var_dump_class(package_executer, &array_value->u.class_ob_array[i], indent + 1);
            break;
        case RVM_ARRAY_CLOSURE:
            result += var_dump_closure(package_executer, &array_value->u.closure_array[i]);
            break;
        case RVM_ARRAY_A:
            result += var_dump_array(package_executer, &array_value->u.a_array[i], indent + 1);
            break;

        default:
            break;
        }
    }

    if (array_value != nullptr && array_value->length) {
        result += "\n" + build_indent(indent, "    ");
        result += "]";
    }


    std::string res;
    res = sprintf_string("%s(len:%u cap:%u) => %s",
                         formate_array_type(array_value).c_str(),
                         array_value->length,
                         array_value->capacity,
                         result.c_str());
    return res;
}

std::string var_dump_closure(Package_Executer* package_executer, RVM_Closure* closure) {
    std::string res;

    if (closure == nullptr || closure->anonymous_func == nullptr) {
        return "closure(nil)";
    }

    res = sprintf_string("closure(fn%s) => %p",
                         format_rvm_function_type(package_executer, closure->anonymous_func).c_str(),
                         closure);

    return res;
}

std::string build_indent(unsigned int indent, std::string indent_str) {
    std::string res;
    for (unsigned int i = 0; i < indent; i++) {
        res += indent_str;
    }
    return res;
}