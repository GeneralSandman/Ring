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
    func_variadic_parameter(0L);

    fmt::println_string("\ntest case 2--------");
    func_variadic_parameter(0L, 1L);

    fmt::println_string("\ntest case 3--------");
    func_variadic_parameter(0L, 1L, 2L);

    fmt::println_string("\ntest case 4--------");
    func_variadic_parameter(0L, 1L, 2L, 3L);
}


fn func_variadic_parameter(var int64... array_value) {
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("capacity(array_value) = {}\n", capacity(array_value));

    var int64 int64_value;
    for(int64_value in range array_value) {
        fmt::println(int64_value);
    }
}
