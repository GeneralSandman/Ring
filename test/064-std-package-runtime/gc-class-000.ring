
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

    var Job job_value_0;

    fmt::println_int64(runtime::heap_size());
    debug::assert(runtime::heap_size() == 21L); // 1+4+8+8
    runtime::gc();
    fmt::println_int64(runtime::heap_size());
    debug::assert(runtime::heap_size() == 21L); // 1+4+8+8


    job_value_0.Name = "123456789_123456";
    
    fmt::println_int64(runtime::heap_size());
    debug::assert(runtime::heap_size() == 21L); // 1+4+8+8
    runtime::gc();
    // job_value_0.Name 只占用常量、不占用动态区
    fmt::println_int64(runtime::heap_size());
    debug::assert(runtime::heap_size() == 13L); // 1+4+8


}
