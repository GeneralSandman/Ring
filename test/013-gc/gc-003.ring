
package main

import {
  fmt;
  debug;
  vm;
}

global {
  var string global_string_value_0;
}

@main
function main(var string[] args) {
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
    var int64 init_heap_size = vm::heap_size() - 8L;
    // -8 是因为 global_string_value_0 默认占用 8Byte, 需要算到本次测试用例中



    // --------- 测试 string 分配内存
    fmt::println_string(global_string_value_0);

    // assign string
    global_string_value_0 = "1234567890";
    fmt::println_string(global_string_value_0);
    fmt::println(vm::heap_size() - init_heap_size); 
    /*
    * 内存分布
    * global_string_value_0(垃圾)   占用 8Byte
    * global_string_value_0    新增内存 16Byte
    */

    // gc
    vm::garbage_collect();
    fmt::println_string(global_string_value_0);
    fmt::println(vm::heap_size() - init_heap_size);
    /*
    * 内存分布
    * global_string_value_0  新增内存 16Byte
    */

}
