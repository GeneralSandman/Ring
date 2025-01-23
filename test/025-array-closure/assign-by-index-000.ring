package main

import {
    fmt;
    debug;
}

typedef fn() FuncType;

global {
    var FuncType[] global_func_array_0;
}

fn main() {
    var FuncType local_func_value_0;

    global_func_array_0 = new FuncType[5];


    fmt::println_string("test cast 1 ------------------------");
    var int index = 0;
    for(index = 0; index < 5; index = index + 1) {
        fmt::println(global_func_array_0[index]); // nil
    }


    fmt::println_string("\ntest cast 2 ------------------------");
    global_func_array_0[0] = fn() {
        fmt::printf("global_func_array_0 func item 0\n");
    };
    global_func_array_0[1] = fn() {
        fmt::printf("global_func_array_0 func item 1\n");
    };
    global_func_array_0[2] = fn() {
        fmt::printf("global_func_array_0 func item 2\n");
    };
    global_func_array_0[3] = fn() {
        fmt::printf("global_func_array_0 func item 3\n");
    };
    global_func_array_0[4] = fn() {
        fmt::printf("global_func_array_0 func item 4\n");
    };



    fmt::println_string("\ntest cast 3 ------------------------");
    // 这里会输出指针，不好自动化测试
    // fmt::println(global_func_array_0[0]);
    // fmt::println(global_func_array_0[1]);
    // fmt::println(global_func_array_0[2]);
    // fmt::println(global_func_array_0[3]);
    // fmt::println(global_func_array_0[4]);


    fmt::println_string("\ntest cast 4 ------------------------");
    // TODO: 这里还不支持 global_func_array_0[0]() 这种调用方式
    local_func_value_0 = global_func_array_0[0]; local_func_value_0();
    local_func_value_0 = global_func_array_0[1]; local_func_value_0();
    local_func_value_0 = global_func_array_0[2]; local_func_value_0();
    local_func_value_0 = global_func_array_0[3]; local_func_value_0();
    local_func_value_0 = global_func_array_0[4]; local_func_value_0();

}
