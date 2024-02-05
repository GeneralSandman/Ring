
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
    var Job job_0;
    var Job job_1;
}

// TestDetail: 自增运算符应用到 class中的field
// TestDetail: e.g. 

@main
function main() {


    fmt::println_string("\ntest case 1");
    fmt::println_bool(job_0.Running);
    fmt::println_int(job_0.JobID);
    fmt::println_double(job_0.Score);
    debug::debug_assert(job_0.Running == false);
    debug::debug_assert(job_0.JobID == 0);
    debug::debug_assert(job_0.Score == 0.0);

    fmt::println_string("\ntest case 2");
    job_0.JobID++;

    fmt::println_bool(job_0.Running);
    fmt::println_int(job_0.JobID);
    fmt::println_double(job_0.Score);
    debug::debug_assert(job_0.Running == false);
    debug::debug_assert(job_0.JobID == 1);
    debug::debug_assert(job_0.Score == 0.0);



    fmt::println_string("\ntest case 3");
    job_0.JobID++;

    fmt::println_bool(job_0.Running);
    fmt::println_int(job_0.JobID);
    fmt::println_double(job_0.Score);
    debug::debug_assert(job_0.Running == false);
    debug::debug_assert(job_0.JobID == 2);
    debug::debug_assert(job_0.Score == 0.0);



    fmt::println_string("\ntest case 4");
    job_0.JobID--;

    fmt::println_bool(job_0.Running);
    fmt::println_int(job_0.JobID);
    fmt::println_double(job_0.Score);
    debug::debug_assert(job_0.Running == false);
    debug::debug_assert(job_0.JobID == 1);
    debug::debug_assert(job_0.Score == 0.0);


    fmt::println_string("\ntest case 5");
    job_0.JobID--;

    fmt::println_bool(job_0.Running);
    fmt::println_int(job_0.JobID);
    fmt::println_double(job_0.Score);
    debug::debug_assert(job_0.Running == false);
    debug::debug_assert(job_0.JobID == 0);
    debug::debug_assert(job_0.Score == 0.0);


}