package main

import {
    fmt;
    debug;
}

global {
}

// TestDetail:测试可变参数
// TestDetail:可变参数为 double... 类型
fn main() {
    fmt::println_string("test case 1--------");
    func_variadic_parameter(0.0);

    fmt::println_string("\ntest case 2--------");
    func_variadic_parameter(0.0, 1.1);

    fmt::println_string("\ntest case 3--------");
    func_variadic_parameter(0.0, 1.1, 2.2);

    fmt::println_string("\ntest case 4--------");
    func_variadic_parameter(0.0, 1.1, 2.2, 3.3);
}


fn func_variadic_parameter(var double... array_value) {
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));

    var double double_value;
    for(double_value in range array_value) {
        fmt::println(double_value);
    }
}
