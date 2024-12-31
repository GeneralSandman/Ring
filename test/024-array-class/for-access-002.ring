package main

import {
    fmt;
    debug;
}

typedef class Job {
    var bool    Running;
    var int     JobID;
    var double  Score;
}

global {
    var Job[] global_job_array_0;
}

@main
fn main() {
    var Job job_value;

    global_job_array_0 = new Job[30];

    var int index = 0;
    for(job_value in range global_job_array_0) {
        fmt::println_string("-----");
        
        fmt::println_bool(job_value.Running);
        fmt::println_int(job_value.JobID);
        fmt::println_double(job_value.Score);

        debug::assert(job_value.Running == false);
        debug::assert(job_value.JobID   == 0);
        debug::assert(job_value.Score   == 0.0);


        job_value.Running = true;
        job_value.JobID = 1;
        job_value.Score = 3.14;


        fmt::println_bool(job_value.Running);
        fmt::println_int(job_value.JobID);
        fmt::println_double(job_value.Score);

        debug::assert(job_value.Running == true);
        debug::assert(job_value.JobID   == 1);
        debug::assert(job_value.Score   == 3.14);

    }

}
