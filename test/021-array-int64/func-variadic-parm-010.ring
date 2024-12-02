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
function main() {
    var int64 sum;


    fmt::println_string("test case 1--------");
    sum = sum(1L);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 1L);


    fmt::println_string("\ntest case 2--------");
    sum = sum(1L, 2L);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 3L);


    fmt::println_string("\ntest case 3--------");
    sum = sum(1L, 2L, 3L);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 6L);


    fmt::println_string("\ntest case 4--------");
    sum = sum(1L, 2L, 3L, 4L);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 10L);


    fmt::println_string("\ntest case 5--------");
    sum = sum(1L, 2L, 3L, 4L, 5L);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 15L);

    fmt::println_string("\ntest case 6--------");
    sum = sum(1L, 2L, 3L, 4L, 5L, 6L);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 21L);

    fmt::println_string("\ntest case 7--------");
    sum = sum(1L, 2L, 3L, 4L, 5L, 6L, 7L);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 28L);

    fmt::println_string("\ntest case 8--------");
    sum = sum(1L, 2L, 3L, 4L, 5L, 6L, 7L, 8L);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 36L);

    fmt::println_string("\ntest case 9--------");
    sum = sum(1L, 2L, 3L, 4L, 5L, 6L, 7L, 8L, 9L);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 45L);


    fmt::println_string("\ntest case 10--------");
    sum = sum(1L, 2L, 3L, 4L, 5L, 6L, 7L, 8L, 9L, 10L);
    fmt::printf("sum = {}\n", sum);
    debug::assert(sum == 55L);

}


function sum(var int64... array_value) -> (int64) {
    var int64 sum;
    var int64 int64_value;

    for(int64_value in range array_value) {
        sum += int64_value;
    }

    return sum;
}
