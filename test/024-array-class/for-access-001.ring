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
    global_job_array_0 = new Job[200];

    var int index = 0;
    for(index = 0; index < len(global_job_array_0); index = index + 1) {
        fmt::println_bool(global_job_array_0[index].Running);
        fmt::println_int(global_job_array_0[index].JobID);
        fmt::println_double(global_job_array_0[index].Score);

        debug::assert(global_job_array_0[index].Running == false);
        debug::assert(global_job_array_0[index].JobID   == 0);
        debug::assert(global_job_array_0[index].Score   == 0.0);
    }
}
