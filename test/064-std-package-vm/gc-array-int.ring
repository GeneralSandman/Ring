package main

import {
    fmt;
    debug;
}

global {
}

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
    var int init_heap_size = vm::heap_size();
    //



    var int[]   local_int_array_0;

    local_int_array_0 = new int[20];

    debug::debug_assert(len(local_int_array_0) == 20);
    debug::debug_assert(capacity(local_int_array_0) == 24);
    fmt::println(vm::heap_size() - init_heap_size);
    debug::debug_assert(vm::heap_size() - init_heap_size == 192);
    /*
    * 内存分布
    * int[24](垃圾)         占用 4*24 Byte
    * local_int_array_0    占用 4*24 16Byte
    */

    vm::garbage_collect();


    debug::debug_assert(len(local_int_array_0) == 20);
    debug::debug_assert(capacity(local_int_array_0) == 24);
    fmt::println(vm::heap_size() - init_heap_size);
    debug::debug_assert(vm::heap_size() - init_heap_size == 96);
    /*
    * 内存分布
    * local_int_array_0    占用 4*24 16Byte
    */
}
