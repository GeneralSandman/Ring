package main

import {
	fmt;
	debug;
    vm;
}

typedef class Job {
    var bool    Running;
    var int     JobID;
    var double  Score;

    fn PrintInfo() {
        
    }
}

global {
}

@main
fn main() {
    var Job local_value_job_0;
    local_value_job_0.Running = true;
    local_value_job_0.JobID = 1;
    local_value_job_0.Score = 1.1;

    fmt::println_bool(local_value_job_0.Running);
    fmt::println_int(local_value_job_0.JobID);
    fmt::println_double(local_value_job_0.Score);
    debug::assert(local_value_job_0.Running == true);
    debug::assert(local_value_job_0.JobID == 1);
    debug::assert(local_value_job_0.Score == 1.1);

    // fmt::println_pointer(local_value_job_0);

    test(local_value_job_0);


    vm::garbage_collect();

    fmt::println_bool(local_value_job_0.Running);
    fmt::println_int(local_value_job_0.JobID);
    fmt::println_double(local_value_job_0.Score);
    debug::assert(local_value_job_0.Running == true);
    debug::assert(local_value_job_0.JobID == 1);
    debug::assert(local_value_job_0.Score == 1.1);

}

fn test(var Job job) {
    // fmt::println_pointer(job);

    fmt::println_bool(job.Running);
    fmt::println_int(job.JobID);
    fmt::println_double(job.Score);

    debug::assert(job.Running == true);
    debug::assert(job.JobID == 1);
    debug::assert(job.Score == 1.1);

}
