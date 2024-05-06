package main

import {
    fmt;
    debug;
}

global {
}

// TestDetail:测试可变参数
// TestDetail:可变参数为 bool... 类型
// TestDetail: 同时参数中还有非可变参数
@main
function main() {
    fmt::println_string("test case 1--------");
    func_variadic_parameter(false,   false);

    fmt::println_string("\ntest case 2--------");
    func_variadic_parameter(true,    false, true);

    fmt::println_string("\ntest case 3--------");
    func_variadic_parameter(false,   false, true, false);

    fmt::println_string("\ntest case 4--------");
    func_variadic_parameter(true,    false, true, false, true);
}


function func_variadic_parameter(var bool para_bool_value, var bool... array_value) {
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("capacity(array_value) = {}\n", capacity(array_value));

    fmt::printf("para_bool_value = {}\n", para_bool_value);

    var bool bool_value;
    for(bool_value in range array_value) {
        fmt::println(bool_value);
    }
}
