
//
// File:    string-003.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-10-20
//

package main

import {
	fmt;
	debug;
    runtime;
}

// TestDetail: 测试string的GC算法

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
     * 之后测试的时候，`runtime::heap_size() - init_heap_size` 即为刚刚分配的内存
    */
    runtime::gc();
    var int64 init_heap_size = runtime::heap_size() - 24L;
    // - 3*8 是因为 string_value_0 string_value_1 string_value_2 每个变量默认分配 8Byte 内存 总共24Bytes



    var string string_value_0;
    var string string_value_1;
    var string string_value_2;

    string_value_0 = "123456789_123456";
    string_value_0 = "123456789_123456";
    string_value_0 = "123456789_123456";

    string_value_1 = "123456789_123456";


    
    debug::assert(runtime::heap_size() - init_heap_size == 88L); // 8*3+16*4
    runtime::gc();
    debug::assert(runtime::heap_size() - init_heap_size == 40L); // 16 + 16 + 8


    string_value_2 = string_value_0 .. string_value_1;


    debug::assert(runtime::heap_size() - init_heap_size == 72L); // 16 + 16 + 8 + 32
    runtime::gc();
    debug::assert(runtime::heap_size() - init_heap_size == 64L); // 16 + 16 + 32

}
