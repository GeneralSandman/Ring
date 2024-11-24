
package main

import {
    fmt;
    debug;
    vm;
}

global {
  var int int_value;
  var int[] int_array;

  var int64 heap_size;
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
    var int64 init_heap_size = vm::heap_size();
    //


  
    // before new
    heap_size = vm::heap_size();
    fmt::println(heap_size - init_heap_size);
    debug::debug_assert(heap_size - init_heap_size == 0L);

    int_array = new int[10];

    // after new
    heap_size = vm::heap_size();
    fmt::println(heap_size - init_heap_size);
    debug::debug_assert(heap_size - init_heap_size == 128L);

    int_array = new int[10];

    // after new
    heap_size = vm::heap_size();
    fmt::println(heap_size - init_heap_size);
    debug::debug_assert(heap_size - init_heap_size == 256L);


    // after gc
    vm::garbage_collect();
    heap_size = vm::heap_size();
    fmt::println(heap_size - init_heap_size);
    debug::debug_assert(heap_size - init_heap_size == 64L);
}
