package main

import {
    fmt;
    debug;
}

global {
}


typedef FuncType0 = fn();

// TestDetail:测试可变参数
// TestDetail:可变参数为 fn()... 类型
fn main() {
    var int64 co_id;


    fmt::println("test case 1--------");
    co_id = launch func_variadic_parameter(
        fn(){
            fmt::println("func 1,1");
        }
    );
    resume(co_id);
    resume(co_id);

    fmt::println("\ntest case 2--------");
    co_id = launch func_variadic_parameter(
        fn(){
            fmt::println("func 2,1");
        },
        fn(){
            fmt::println("func 2,2");
        }
    );
    resume(co_id);
    resume(co_id);
    resume(co_id);

    fmt::println("\ntest case 3--------");
    co_id = launch func_variadic_parameter(
        fn(){
            fmt::println("func 3,1");
        },
        fn(){
            fmt::println("func 3,2");
        },
        fn(){
            fmt::println("func 3,3");
        }
    );
    resume(co_id);
    resume(co_id);
    resume(co_id);
    resume(co_id);


    fmt::println("\ntest case 4--------");
    co_id = launch func_variadic_parameter(
        fn(){
            fmt::println("func 4,1");
        },
        fn(){
            fmt::println("func 4,2");
        },
        fn(){
            fmt::println("func 4,3");
        },
        fn(){
            fmt::println("func 4,4");
        }
    );
    resume(co_id);
    resume(co_id);
    resume(co_id);
    resume(co_id);
    resume(co_id);
}


fn func_variadic_parameter(var FuncType0... array_value) {
    fmt::println("func_variadic_parameter begin");

    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));

    var FuncType0 func_value;
    for(func_value in range array_value) {
        fmt::println("invoke func_value");
        func_value();
        yield();
    }

    fmt::println("func_variadic_parameter end");
}
