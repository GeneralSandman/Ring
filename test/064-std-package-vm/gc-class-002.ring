
//
// File:    string-003.ring
// Author:  zhenhuli - generalsandman@163.com
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
    var Job job_value_0;





    // fmt::println_int(vm::heap_size());
    // debug::debug_assert(vm::heap_size() == 21); // 1+4+8+8
    // vm::garbage_collect();
    // fmt::println_int(vm::heap_size());
    // debug::debug_assert(vm::heap_size() == 21); // 1+4+8+8



    job_value_0 = Job{
        Running: true,
        JobID:   1,
        Score:   1.0,
        Name:    "123456789_123456"
    };



    fmt::println_int(vm::heap_size());
    debug::debug_assert(vm::heap_size() == 58); // (1+4+8+8)*2 + 16
    vm::garbage_collect();
    fmt::println_int(vm::heap_size());
    debug::debug_assert(vm::heap_size() == 29); //  1+4+8+16


    debug::debug_assert(job_value_0.Running == true);
    debug::debug_assert(job_value_0.JobID == 1);
    debug::debug_assert(job_value_0.Score == 1.0);
    debug::debug_assert(job_value_0.Name == "123456789_123456");


}
