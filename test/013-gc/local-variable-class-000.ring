package main

import {
	fmt;
	debug;
    vm;
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
}

@main
function main() {
    var Job local_value_job_0;
    local_value_job_0.Running = true;
    local_value_job_0.JobID = 1;
    local_value_job_0.Score = 1.1;

    fmt::println_bool(local_value_job_0.Running);
    fmt::println_int(local_value_job_0.JobID);
    fmt::println_double(local_value_job_0.Score);
    debug::debug_assert(local_value_job_0.Running == true);
    debug::debug_assert(local_value_job_0.JobID == 1);
    debug::debug_assert(local_value_job_0.Score == 1.1);

    // fmt::println_pointer(local_value_job_0);

    test(local_value_job_0);


    vm::garbage_collect();

    fmt::println_bool(local_value_job_0.Running);
    fmt::println_int(local_value_job_0.JobID);
    fmt::println_double(local_value_job_0.Score);
    debug::debug_assert(local_value_job_0.Running == true);
    debug::debug_assert(local_value_job_0.JobID == 1);
    debug::debug_assert(local_value_job_0.Score == 1.1);

}

function test(var Job job) {
    // fmt::println_pointer(job);

    fmt::println_bool(job.Running);
    fmt::println_int(job.JobID);
    fmt::println_double(job.Score);

    debug::debug_assert(job.Running == true);
    debug::debug_assert(job.JobID == 1);
    debug::debug_assert(job.Score == 1.1);

}
