
#ifndef RING_JSON_INCLUDE_H
#define RING_JSON_INCLUDE_H

#include <nlohmann/json.hpp>
#include <variant>
using json = nlohmann::json;

// 首先为 std::optional 添加支持（放在全局命名空间）
namespace nlohmann {
template <typename T>
struct adl_serializer<std::optional<T>> {
    static void to_json(json& j, const std::optional<T>& opt) {
        if (opt.has_value()) {
            j = *opt;
        } else {
            j = nullptr;
        }
    }

    static void from_json(const json& j, std::optional<T>& opt) {
        if (j.is_null()) {
            opt = std::nullopt;
        } else {
            opt = j.get<T>();
        }
    }
};
} // namespace nlohmann

struct JsonError {
    std::string message;
    enum class Type {
        InvalidJson,
        TypeMismatch,
        OutOfRange,
        ParseError,
        Unknown
    } type;

    explicit JsonError(const std::string& msg, Type t = Type::Unknown) :
        message(msg), type(t) {
    }

    operator std::string() const {
        return message;
    }
};

template <typename T>
using DeserializeResult = std::variant<T, JsonError>;

using SerializeResult   = std::variant<std::string, JsonError>;

template <typename T>
DeserializeResult<T> json_decode(const std::string& json_str) {
    if (!json::accept(json_str)) {
        return JsonError{"Invalid JSON format", JsonError::Type::InvalidJson};
    }

    try {
        json j = json::parse(json_str);
        return j.get<T>();
    } catch (const json::type_error& e) {
        return JsonError{std::string("Type error: ") + e.what(),
                         JsonError::Type::TypeMismatch};
    } catch (const json::out_of_range& e) {
        return JsonError{std::string("Out of range: ") + e.what(),
                         JsonError::Type::OutOfRange};
    } catch (const json::parse_error& e) {
        return JsonError{std::string("Parse error: ") + e.what(),
                         JsonError::Type::ParseError};
    } catch (const json::exception& e) {
        return JsonError{std::string("JSON error: ") + e.what()};
    } catch (...) {
        return JsonError{"Unknown error during deserialization"};
    }
}

template <typename T>
std::unique_ptr<JsonError> json_decode(const std::string& json_str, T* out) {
    if (!out) {
        return std::make_unique<JsonError>("json_decode:Output pointer cannot be null");
    }

    if (!json::accept(json_str)) {
        return std::make_unique<JsonError>("json_decode:Invalid JSON format");
    }

    try {
        json j = json::parse(json_str);
        j.get_to(*out);
        return nullptr;
    } catch (const json::type_error& e) {
        return std::make_unique<JsonError>(std::string("json_decode:Type error: ") + e.what());
    } catch (const json::out_of_range& e) {
        return std::make_unique<JsonError>(std::string("json_decode:Out of range: ") + e.what());
    } catch (const json::parse_error& e) {
        return std::make_unique<JsonError>(std::string("json_decode:Parse error: ") + e.what());
    } catch (const json::exception& e) {
        return std::make_unique<JsonError>(std::string("json_decode:JSON error: ") + e.what());
    } catch (...) {
        return std::make_unique<JsonError>("json_decode:Unknown error during deserialization");
    }
}

template <typename T>
SerializeResult json_encode(const T& obj, int indent = -1, char indent_char = ' ') {

    try {
        json j = obj;
        return j.dump(indent, indent_char);
    } catch (const json::exception& e) {
        return JsonError{std::string("JSON serialization error: ") + e.what()};
    }
}

#endif // RING_JSON_INCLUDE_H
