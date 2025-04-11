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
fn main() {
    fmt::println_string("test case 1--------");
    func_variadic_parameter(false, 0, 0.0, "#0.0",    "1");

    fmt::println_string("\ntest case 2--------");
    func_variadic_parameter(true, 1, 1.1, "#1.1",     "1", "2");

    fmt::println_string("\ntest case 3--------");
    func_variadic_parameter(false, 2, 2.2, "#2.2",    "1", "2", "3");

    fmt::println_string("\ntest case 4--------");
    func_variadic_parameter(true, 3, 3.3, "#3.3",     "1", "2", "3", "4");
}


fn func_variadic_parameter(var bool para_bool_value, var int para_int_value, var double para_double_value, var string para_string_value, var string... array_value) {
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));

    fmt::printf("para_bool_value =   {}\n", para_bool_value);
    fmt::printf("para_int_value =    {}\n", para_int_value);
    fmt::printf("para_double_value = {}\n", para_double_value);
    fmt::printf("para_string_value = {}\n", para_string_value);

    var string string_value;
    for(string_value = range array_value) {
        fmt::println(string_value);
    }
}
