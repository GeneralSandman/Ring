package main

import {
    fmt;
    debug;
}

global {
}

// TestDetail: 测试 数组动态分配所占用的内存大小是否正确
@main
function main() {
    var bool[]   local_bool_array_0;
    var int[]    local_int_array_0;
    var int64[]  local_int64_array_0;
    var double[] local_double_array_0;
    var string[] local_string_array_0;

    local_bool_array_0 = new bool[128]; // 128*1 *2 = 256
    fmt::println(vm::heap_size());
    debug::debug_assert(vm::heap_size() == 256);

    local_int_array_0 = new int[128]; // 128*4 *2 = 1024
    fmt::println(vm::heap_size());
    debug::debug_assert(vm::heap_size() == 256+1024);

    local_int64_array_0 = new int64[128]; // 128*8 *2 = 2048
    fmt::println(vm::heap_size());
    debug::debug_assert(vm::heap_size() == 256+1024+2048);

    local_double_array_0 = new double[128];// 128*8 *2 = 2048
    fmt::println(vm::heap_size());
    debug::debug_assert(vm::heap_size() == 256+1024+2048+2048);

    local_string_array_0 = new string[128];// 128*8 *2 = 2048
    fmt::println(vm::heap_size());
    debug::debug_assert(vm::heap_size() == 256+1024+2048+2048+2048);



    vm::garbage_collect();


    fmt::println(vm::heap_size());
    debug::debug_assert(vm::heap_size() == 256/2+1024/2+2048/2+2048/2+2048/2);
}
