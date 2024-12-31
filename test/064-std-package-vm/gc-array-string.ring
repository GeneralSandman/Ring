package main

import {
    fmt;
    debug;
}

global {
}

@main
fn main() {
    /*
     * 该段代码的含义：
     * 1. main() 函数的完整签名为 `fn main(var string[] args){}`
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



    var string[]   local_string_array_0;

    local_string_array_0 = new string[20];

    debug::assert(len(local_string_array_0) == 20);
    debug::assert(capacity(local_string_array_0) == 24);
    fmt::println(vm::heap_size() - init_heap_size);
    debug::assert(vm::heap_size() - init_heap_size == 320L);


    vm::garbage_collect();


    debug::assert(len(local_string_array_0) == 20);
    debug::assert(capacity(local_string_array_0) == 24);
    fmt::println(vm::heap_size() - init_heap_size);
    debug::assert(vm::heap_size() - init_heap_size == 160L);




    local_string_array_0[0] = "12345678";

    fmt::println(vm::heap_size() - init_heap_size);
    debug::assert(vm::heap_size() - init_heap_size == 176L);

    vm::garbage_collect();

    fmt::println(vm::heap_size() - init_heap_size);
    debug::assert(vm::heap_size() - init_heap_size == 160L);
}
