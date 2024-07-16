
//
// File:    string-003.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-10-20
//

package main

import {
	fmt;
	debug;
    vm;
}

// TestDetail: 测试string的GC算法

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
    var int init_heap_size = vm::heap_size() - 3*8;
    // - 3*8 是因为 string_value_0 string_value_1 string_value_2 每个变量默认分配 8Byte 内存



    var string string_value_0;
    var string string_value_1;
    var string string_value_2;

    string_value_0 = "123456789_123456";
    string_value_0 = "123456789_123456";
    string_value_0 = "123456789_123456";

    string_value_1 = "123456789_123456";


    
    debug::debug_assert(vm::heap_size() - init_heap_size == 88); // 8*3+16*4
    vm::garbage_collect();
    debug::debug_assert(vm::heap_size() - init_heap_size == 40); // 16 + 16 + 8


    string_value_2 = string_value_0 .. string_value_1;


    debug::debug_assert(vm::heap_size() - init_heap_size == 72); // 16 + 16 + 8 + 32
    vm::garbage_collect();
    debug::debug_assert(vm::heap_size() - init_heap_size == 64); // 16 + 16 + 32

}
