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
}

global {
    var Job global_value_job_0;
}

@main
function main() {

    fmt::println_string("test case 1");
    fmt::println_bool(global_value_job_0.Running);
    fmt::println_int(global_value_job_0.JobID);
    fmt::println_double(global_value_job_0.Score);
    debug::debug_assert(global_value_job_0.Running == false);
    debug::debug_assert(global_value_job_0.JobID == 0);
    debug::debug_assert(global_value_job_0.Score == 0.0);

    fmt::println_string("\ntest case 2");
    global_value_job_0.Running = true;
    global_value_job_0.JobID = 1;
    global_value_job_0.Score = 1.1;
    fmt::println_bool(global_value_job_0.Running);
    fmt::println_int(global_value_job_0.JobID);
    fmt::println_double(global_value_job_0.Score);
    debug::debug_assert(global_value_job_0.Running == true);
    debug::debug_assert(global_value_job_0.JobID == 1);
    debug::debug_assert(global_value_job_0.Score == 1.1);

}