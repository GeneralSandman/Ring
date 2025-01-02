package main

import {
	fmt;
	debug;
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

fn main() {
    var Job local_value_job_0;
    var Job local_value_job_1;


    fmt::println_string("test case 1");
    fmt::println_bool(local_value_job_0.Running);
    fmt::println_int(local_value_job_0.JobID);
    fmt::println_double(local_value_job_0.Score);
    debug::assert(local_value_job_0.Running == false);
    debug::assert(local_value_job_0.JobID == 0);
    debug::assert(local_value_job_0.Score == 0.0);

    fmt::println_string("\ntest case 2");
    local_value_job_0.Running = true;
    local_value_job_0.JobID = 1;
    local_value_job_0.Score = 1.1;
    fmt::println_bool(local_value_job_0.Running);
    fmt::println_int(local_value_job_0.JobID);
    fmt::println_double(local_value_job_0.Score);
    debug::assert(local_value_job_0.Running == true);
    debug::assert(local_value_job_0.JobID == 1);
    debug::assert(local_value_job_0.Score == 1.1);



    // ----------------------
    fmt::println_string("\ntest case 3");
    fmt::println_bool(local_value_job_1.Running);
    fmt::println_int(local_value_job_1.JobID);
    fmt::println_double(local_value_job_1.Score);
    debug::assert(local_value_job_1.Running == false);
    debug::assert(local_value_job_1.JobID == 0);
    debug::assert(local_value_job_1.Score == 0.0);

    fmt::println_string("\ntest case 4");
    local_value_job_1.Running = true;
    local_value_job_1.JobID = 123;
    local_value_job_1.Score = 123.123;
    fmt::println_bool(local_value_job_1.Running);
    fmt::println_int(local_value_job_1.JobID);
    fmt::println_double(local_value_job_1.Score);
    debug::assert(local_value_job_1.Running == true);
    debug::assert(local_value_job_1.JobID == 123);
    debug::assert(local_value_job_1.Score == 123.123);

}
