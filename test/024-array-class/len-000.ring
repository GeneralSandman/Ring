package main

import {
    fmt;
    debug;
}

typedef Job = class {
    var bool    Running;
    var int     JobID;
    var double  Score;
}

global {
    var Job[] global_job_array_0;
}

fn main() {
    

    fmt::println_string("test cast 1 ------------------------");
    fmt::println_int(len(global_job_array_0));
    fmt::println_int(cap(global_job_array_0));
    debug::assert(len(global_job_array_0) == 0);
    debug::assert(cap(global_job_array_0) == 0);
  
  
    fmt::println_string("\ntest cast 2 ------------------------");
  
    global_job_array_0 = new Job[200];
  
    fmt::println_int(len(global_job_array_0));
    fmt::println_int(cap(global_job_array_0));
    debug::assert(len(global_job_array_0) == 200);
    debug::assert(cap(global_job_array_0) == 200);

}
