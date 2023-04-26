
package main

import {
	fmt;
	debug;
}



typedef class Job {
    field bool    Running;
    field int     JobID;
    field double  Score;

    @constructor
    method Job(var bool _Running, var int _JobID, var double _Score);

    method PrintInfo();
};

global {
var Job job_0;
var Job job_1;

}

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
    job_0.Running = true;
    job_0.JobID = 1;
    job_0.Score = 1.1;
    fmt::println_bool(job_0.Running);
    fmt::println_int(job_0.JobID);
    fmt::println_double(job_0.Score);
    debug::debug_assert(job_0.Running == true);
    debug::debug_assert(job_0.JobID == 1);
    debug::debug_assert(job_0.Score == 1.1);



    fmt::println_string("\ntest case 3");
    job_1.Running = true;
    job_1.JobID = 2;
    job_1.Score = 2.2;
    fmt::println_bool(job_1.Running);
    fmt::println_int(job_1.JobID);
    fmt::println_double(job_1.Score);
    debug::debug_assert(job_1.Running == true);
    debug::debug_assert(job_1.JobID == 2);
    debug::debug_assert(job_1.Score == 2.2);

    fmt::println_string("\ntest case 4");
    fmt::println_int(job_0.JobID + job_1.JobID);
    debug::debug_assert(job_0.JobID + job_1.JobID == 3);

    fmt::println_string("\ntest case 5");
    fmt::println_double(job_0.Score + job_1.Score);
    // debug::debug_assert(job_0.Score + job_1.Score == 3.300000);
    // 这里有bug

}