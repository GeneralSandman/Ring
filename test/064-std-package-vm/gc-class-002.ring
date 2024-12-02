
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

typedef class Job {
    field bool    Running;
    field int     JobID;
    field double  Score;
    field string  Name;
}

// TestDetail: 测试 class-object 的GC算法

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
    var int64 init_heap_size = vm::heap_size() - 21L;
    // - 21 是因为 job_value_0 局部变量占用内存 21Byte, 需要算到本次的测试用例中



    var Job job_value_0;





    // fmt::println_int(vm::heap_size());
    // debug::assert(vm::heap_size() == 21); // 1+4+8+8
    // vm::garbage_collect();
    // fmt::println_int(vm::heap_size());
    // debug::assert(vm::heap_size() == 21); // 1+4+8+8



    job_value_0 = Job{
        Running: true,
        JobID:   1,
        Score:   1.0,
        Name:    "123456789_123456"
    };



    fmt::println_int64(vm::heap_size() - init_heap_size);
    debug::assert(vm::heap_size() - init_heap_size == 58L); // (1+4+8+8)*2 + 16
    vm::garbage_collect();
    fmt::println_int64(vm::heap_size() - init_heap_size);
    debug::assert(vm::heap_size() - init_heap_size == 29L); //  1+4+8+16


    debug::assert(job_value_0.Running == true);
    debug::assert(job_value_0.JobID == 1);
    debug::assert(job_value_0.Score == 1.0);
    debug::assert(job_value_0.Name == "123456789_123456");


}
