#include "json.hpp"
#include <iostream>
#include <nlohmann/json.hpp>

struct Address {
    std::string street;
    std::string number;
    std::string postcode;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Address, street, number, postcode);
};

struct Person {
    std::string          name;
    int                  age;
    std::vector<Address> addresses;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Person, name, age, addresses);
};


void json_decode_test_1() {

    std::string json_str = R"(
        {
            "name": "Jane Doe",
            "age": 25,
            "addresses":[
                {
                    "street":"jiangxia",
                    "number":"258",
                    "postcode":"54321"
                },
                {
                    "street":"wuchang",
                    "number":"369",
                    "postcode":"54321"
                }
            ]
        }
    )";

    // 使用示例
    auto result = json_decode<Person>(json_str);
    if (JsonError* err = std::get_if<JsonError>(&result)) {
        // 处理错误
        std::cerr << "Error (" << static_cast<int>(err->type) << "): " << err->message << "\n";
    } else {
        Person* person = std::get_if<Person>(&result);
        // 成功解析
        std::cout << person->name << "\n";
    }
}

void json_decode_test_2() {
    std::string json_str = R"(
        {
            "name": "Jane Doe",
            "age": 25,
            "addresses":[
                {
                    "street":"jiangxia",
                    "number":"258",
                    "postcode":"54321"
                },
                {
                    "street":"wuchang",
                    "number":"369",
                    "postcode":"54321"
                }
            ]
        }
    )";

    Person      person;

    auto        err = json_decode(json_str, &person);
    if (err != nullptr) {
        // 处理错误
        std::cerr << "Error (" << static_cast<int>(err->type) << "): " << err->message << "\n";
        return;
    }

    std::cout << person.name << "\n";
}

/*
int main() {
    json_decode_test_1();
    json_decode_test_2();
    return 0;
}
*/
