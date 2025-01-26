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

    fn PrintInfo() {
        
    }
}

global {
    var Job global_value_job_0;

}

fn main() {
    global_value_job_0.Running = true;
    global_value_job_0.JobID = 1;
    global_value_job_0.Score = 1.1;

    fmt::println_bool(global_value_job_0.Running);
    fmt::println_int(global_value_job_0.JobID);
    fmt::println_double(global_value_job_0.Score);
    debug::assert(global_value_job_0.Running == true);
    debug::assert(global_value_job_0.JobID == 1);
    debug::assert(global_value_job_0.Score == 1.1);


    test(global_value_job_0);


    runtime::gc();

    fmt::println_bool(global_value_job_0.Running);
    fmt::println_int(global_value_job_0.JobID);
    fmt::println_double(global_value_job_0.Score);
    debug::assert(global_value_job_0.Running == true);
    debug::assert(global_value_job_0.JobID == 1);
    debug::assert(global_value_job_0.Score == 1.1);

}

fn test(var Job job) {

    fmt::println_bool(job.Running);
    fmt::println_int(job.JobID);
    fmt::println_double(job.Score);
    debug::assert(job.Running == true);
    debug::assert(job.JobID == 1);
    debug::assert(job.Score == 1.1);
}
