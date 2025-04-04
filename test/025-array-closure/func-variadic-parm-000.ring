package main

import {
    fmt;
    debug;
}


typedef FuncType = fn();

global {
}

// TestDetail:测试可变参数
// TestDetail:可变参数为 Job... 类型
fn main() {
    fmt::println_string("test case 1--------");
    func_variadic_parameter(
        fn() {
            fmt::println_string("func_value 1");
        }
    );

    fmt::println_string("\ntest case 2--------");
    func_variadic_parameter(
        fn() {
            fmt::println_string("func_value 1");
        },
        fn() {
            fmt::println_string("func_value 2");
        }
    );


    fmt::println_string("\ntest case 3--------");
    func_variadic_parameter(
        fn() {
            fmt::println_string("func_value 1");
        },
        fn() {
            fmt::println_string("func_value 2");
        },
        fn() {
            fmt::println_string("func_value 3");
        }
    );


    fmt::println_string("\ntest case 4--------");
    func_variadic_parameter(
        fn() {
            fmt::println_string("func_value 1");
        },
        fn() {
            fmt::println_string("func_value 2");
        },
        fn() {
            fmt::println_string("func_value 3");
        },
        fn() {
            fmt::println_string("func_value 4");
        }
    );
}


fn func_variadic_parameter(var FuncType... func_array_value) {
    fmt::printf("len(func_array_value)      = {}\n", len(func_array_value));
    fmt::printf("cap(func_array_value) = {}\n", cap(func_array_value));

    var FuncType func_value;
    for(func_value in range func_array_value) {
        func_value();
    }
}
