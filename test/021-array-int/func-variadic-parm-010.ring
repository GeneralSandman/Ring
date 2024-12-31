package main

import {
    fmt;
    debug;
}

global {
}

// TestDetail:测试可变参数, 实现一个 sum函数
// TestDetail:可变参数为 int... 类型
@main
fn main() {
    var int sum;


    fmt::println_string("test case 1--------");
    sum = sum(1);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 1);


    fmt::println_string("\ntest case 2--------");
    sum = sum(1, 2);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 3);


    fmt::println_string("\ntest case 3--------");
    sum = sum(1, 2, 3);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 6);


    fmt::println_string("\ntest case 4--------");
    sum = sum(1, 2, 3, 4);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 10);


    fmt::println_string("\ntest case 5--------");
    sum = sum(1, 2, 3, 4, 5);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 15);

    fmt::println_string("\ntest case 6--------");
    sum = sum(1, 2, 3, 4, 5, 6);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 21);

    fmt::println_string("\ntest case 7--------");
    sum = sum(1, 2, 3, 4, 5, 6, 7);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 28);

    fmt::println_string("\ntest case 8--------");
    sum = sum(1, 2, 3, 4, 5, 6, 7, 8);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 36);

    fmt::println_string("\ntest case 9--------");
    sum = sum(1, 2, 3, 4, 5, 6, 7, 8, 9);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 45);


    fmt::println_string("\ntest case 10--------");
    sum = sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 55);

}


fn sum(var int... array_value) -> (int) {
    var int sum;
    var int int_value;

    for(int_value in range array_value) {
        sum += int_value;
    }

    return sum;
}
