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
    /*
     * 该段代码的含义：
     * 1. main() 函数的完整签名为 `function main(var string[] args){}`
     * 2. args 也是一个动态内存分配的数组
     * 3. 在执行 main() 函数之前，args 已经被分配了内存
     * 4. 我们测试 gc，主要关注在main()函数内分片的内存
     * 5. 所以这里需要先进行一次 gc，将 args 分配的内存删除掉，方便在 main函数中测试显示分配的动态内存
     * 
     * init_heap_size 其实就是main()函数执行之前所有非垃圾内存
     * 之后测试的时候，`vm::heap_size() - init_heap_size` 即为刚刚分配的内存
    */
    vm::garbage_collect();
    var int64 init_heap_size = vm::heap_size();
    //



    var bool[]   local_bool_array_0;
    var int[]    local_int_array_0;
    var int64[]  local_int64_array_0;
    var double[] local_double_array_0;
    var string[] local_string_array_0;

    local_bool_array_0 = new bool[128]; // 128*1 *2 = 256
    fmt::println(vm::heap_size() - init_heap_size);
    debug::debug_assert(vm::heap_size() - init_heap_size == 256L);

    local_int_array_0 = new int[128]; // 128*4 *2 = 1024
    fmt::println(vm::heap_size() - init_heap_size);
    debug::debug_assert(vm::heap_size() - init_heap_size == to_int64(256+1024));

    local_int64_array_0 = new int64[128]; // 128*8 *2 = 2048
    fmt::println(vm::heap_size() - init_heap_size);
    debug::debug_assert(vm::heap_size() - init_heap_size == to_int64(256+1024+2048));

    local_double_array_0 = new double[128];// 128*8 *2 = 2048
    fmt::println(vm::heap_size() - init_heap_size);
    debug::debug_assert(vm::heap_size() - init_heap_size == to_int64(256+1024+2048+2048));

    local_string_array_0 = new string[128];// 128*8 *2 = 2048
    fmt::println(vm::heap_size() - init_heap_size);
    debug::debug_assert(vm::heap_size() - init_heap_size == to_int64(256+1024+2048+2048+2048));



    vm::garbage_collect();


    fmt::println(vm::heap_size() - init_heap_size);
    debug::debug_assert(vm::heap_size() - init_heap_size == to_int64(256/2+1024/2+2048/2+2048/2+2048/2));
}
