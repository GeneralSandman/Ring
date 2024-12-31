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
fn main() {
    fmt::println_string("test case 1--------");
    func_variadic_parameter(false, 0,   false);

    fmt::println_string("\ntest case 2--------");
    func_variadic_parameter(true, 1,    false, true);

    fmt::println_string("\ntest case 3--------");
    func_variadic_parameter(false, 2,   false, true, false);

    fmt::println_string("\ntest case 4--------");
    func_variadic_parameter(true, 3,    false, true, false, true);
}


fn func_variadic_parameter(var bool para_bool_value, var int para_int_value, var bool... array_value) {
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("capacity(array_value) = {}\n", capacity(array_value));

    fmt::printf("para_bool_value = {}\n", para_bool_value);
    fmt::printf("para_int_value  = {}\n", para_int_value);


    var bool bool_value;
    for(bool_value in range array_value) {
        fmt::println(bool_value);
    }
}
