package main

import {
    fmt;
    debug;
}

global {
}

// TestDetail:测试可变参数
// TestDetail:可变参数为 int... 类型
fn main() {
    fmt::println_string("test case 1--------");
    func_variadic_parameter(0);

    fmt::println_string("\ntest case 2--------");
    func_variadic_parameter(0, 1);

    fmt::println_string("\ntest case 3--------");
    func_variadic_parameter(0, 1, 2);

    fmt::println_string("\ntest case 4--------");
    func_variadic_parameter(0, 1, 2, 3);
}


fn func_variadic_parameter(var int... array_value) {
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));

    var int int_value;
    for(int_value = range array_value) {
        fmt::println(int_value);
    }
}
