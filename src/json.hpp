#include <nlohmann/json.hpp>
#include <variant>
using json = nlohmann::json;

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
        return std::make_unique<JsonError>("Output pointer cannot be null");
    }

    if (!json::accept(json_str)) {
        return std::make_unique<JsonError>("Invalid JSON format");
    }

    try {
        json j = json::parse(json_str);
        j.get_to(*out);
        return nullptr;
    } catch (const json::type_error& e) {
        return std::make_unique<JsonError>(std::string("Type error: ") + e.what());
    } catch (const json::out_of_range& e) {
        return std::make_unique<JsonError>(std::string("Out of range: ") + e.what());
    } catch (const json::parse_error& e) {
        return std::make_unique<JsonError>(std::string("Parse error: ") + e.what());
    } catch (const json::exception& e) {
        return std::make_unique<JsonError>(std::string("JSON error: ") + e.what());
    } catch (...) {
        return std::make_unique<JsonError>("Unknown error during deserialization");
    }
}