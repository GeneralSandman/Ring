package main

import {
    fmt;
    debug;
}

global {
}

// TestDetail:测试可变参数
// TestDetail:可变参数为 bool... 类型
@main
function main() {
    fmt::println_string("test case 1--------");
    func_variadic_parameter(false);

    fmt::println_string("\ntest case 2--------");
    func_variadic_parameter(false, true);

    fmt::println_string("\ntest case 3--------");
    func_variadic_parameter(false, true, false);

    fmt::println_string("\ntest case 4--------");
    func_variadic_parameter(false, true, false, true);
}


function func_variadic_parameter(var bool... array_value) {
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("capacity(array_value) = {}\n", capacity(array_value));

    var bool bool_value;
    for(bool_value in range array_value) {
        fmt::println(bool_value);
    }
}
