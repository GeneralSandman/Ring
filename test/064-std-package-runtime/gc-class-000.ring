
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

typedef Job = class {
    var bool    Running;
    var int     JobID;
    var double  Score;
    var string  Name;
}

// TestDetail: 测试 class-object 的GC算法

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
    var int64 init_heap_size = runtime::heap_size() - 21L;
    // - 21 是因为 job_value_0 局部变量占用内存 21Byte, 需要算到本次的测试用例中



    var Job job_value_0;

    fmt::println_int64(runtime::heap_size() - init_heap_size);
    debug::assert(runtime::heap_size() - init_heap_size == 21L); // 1+4+8+8
    runtime::gc();
    fmt::println_int64(runtime::heap_size() - init_heap_size);
    debug::assert(runtime::heap_size() - init_heap_size == 21L); // 1+4+8+8


    job_value_0.Name = "123456789_123456";
    
    fmt::println_int64(runtime::heap_size() - init_heap_size);
    debug::assert(runtime::heap_size() - init_heap_size == 37L); // 1+4+8+8 + 16
    runtime::gc();
    fmt::println_int64(runtime::heap_size() - init_heap_size);
    debug::assert(runtime::heap_size() - init_heap_size == 29L); // 1+4+8+16


}
