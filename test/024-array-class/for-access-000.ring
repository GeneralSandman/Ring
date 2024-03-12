package main

import {
    fmt;
    debug;
}

typedef class Job {
    field bool    Running;
    field int     JobID;
    field double  Score;
}

global {
    var Job[] global_job_array_0;
}

// TestDetail: 数组中的元素为类
// TestDetail: 通过数组索引对数组元素的成员变量进行赋值
@main
function main() {
    global_job_array_0 = new Job[200];

    var int index = 0;
    for(index = 0; index < 200; index = index + 1) {

        if(global_job_array_0[index].Running != false) {
            fmt::println_string("global_job_array_0[index].Running != false");
        }
        if(global_job_array_0[index].JobID   != 0) {
            fmt::println_string("global_job_array_0[index].JobID   != 0");
        }
        if(global_job_array_0[index].Score   != 0.0) {
            fmt::println_string("global_job_array_0[index].Score   != 0.0");
        }

        global_job_array_0[index].Running = true;
        global_job_array_0[index].JobID   = 1;
        global_job_array_0[index].Score   = 2.34;
    }

    for(index = 0; index < 200; index = index + 1) {
        if(global_job_array_0[index].Running != true) {
            fmt::println_string("global_job_array_0[index].Running != true");
        }
        if(global_job_array_0[index].JobID   != 1) {
            fmt::println_string("global_job_array_0[index].JobID   != 1");
        }
        if(global_job_array_0[index].Score   != 2.34) {
            fmt::println_string("global_job_array_0[index].Score   != 2.34");
        }
    }

    debug::debug_assert(global_job_array_0[199].Running == true);
    debug::debug_assert(global_job_array_0[199].JobID   == 1);
    debug::debug_assert(global_job_array_0[199].Score   == 2.34);
}
