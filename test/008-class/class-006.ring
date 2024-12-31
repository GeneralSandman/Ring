
package main

import {
	fmt;
	debug;
}



typedef class Job {
    var bool    Running;
    var int     JobID;
    var double  Score;
    var string  Name;
}

global {
    var Job job_0;
}

@main
fn main() {

    fmt::println_string("\ntest case 1");
    fmt::println_bool(job_0.Running);
    fmt::println_int(job_0.JobID);
    fmt::println_double(job_0.Score);
    fmt::println_string(job_0.Name);
    debug::assert(job_0.Running == false);
    debug::assert(job_0.JobID   == 0);
    debug::assert(job_0.Score   == 0.0);
    debug::assert(job_0.Name    == "");



    fmt::println_string("\ntest case 2");
    job_0.Running = true;
    job_0.JobID = 1;
    job_0.Score = 1.1;
    job_0.Name = "hello-world";
    fmt::println_bool(job_0.Running);
    fmt::println_int(job_0.JobID);
    fmt::println_double(job_0.Score);
    fmt::println_string(job_0.Name);
    debug::assert(job_0.Running == true);
    debug::assert(job_0.JobID   == 1);
    debug::assert(job_0.Score   == 1.1);
    debug::assert(job_0.Name    == "hello-world");

    
    fmt::println_string("\ntest case 3");
    job_0 = Job{
        Running: true,
        JobID: 2, 
        Score: 23.45,
        Name: "1234567890"
    };
    fmt::println_bool(job_0.Running);
    fmt::println_int(job_0.JobID);
    fmt::println_double(job_0.Score);
    fmt::println_string(job_0.Name);
    debug::assert(job_0.Running == true);
    debug::assert(job_0.JobID   == 2);
    debug::assert(job_0.Score   == 23.45);
    debug::assert(job_0.Name    == "1234567890");


}