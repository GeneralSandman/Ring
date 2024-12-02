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
  var Job[] global_job_array_0;

  var Job global_job_value_0;
}

@main
function main() {

    global_job_value_0 = Job{
       Running: true,
       JobID: 200, 
       Score: 200.1
    };

    fmt::println_string("test cast 1 ------------------------");
    global_job_array_0 = new Job[200];
    fmt::println_int(len(global_job_array_0));
    fmt::println_int(capacity(global_job_array_0));
    debug::assert(len(global_job_array_0) == 200);
    debug::assert(capacity(global_job_array_0) == 200);


    fmt::println_string("\ntest cast 2 ------------------------");
    push(global_job_array_0, global_job_value_0);

    fmt::println_bool(global_job_array_0[200].Running);
    fmt::println_int(global_job_array_0[200].JobID);
    fmt::println_double(global_job_array_0[200].Score);
    debug::assert(global_job_array_0[200].Running == true);
    debug::assert(global_job_array_0[200].JobID   == 200);
    debug::assert(global_job_array_0[200].Score   == 200.1);

    fmt::println_int(len(global_job_array_0));
    fmt::println_int(capacity(global_job_array_0));
    debug::assert(len(global_job_array_0) == 201);
    debug::assert(capacity(global_job_array_0) == 400);


    fmt::println_string("\ntest cast 3 ------------------------");
    push(global_job_array_0, Job{
            Running: false,
            JobID: 201, 
            Score: 201.14
        });

    fmt::println_bool(global_job_array_0[201].Running);
    fmt::println_int(global_job_array_0[201].JobID);
    fmt::println_double(global_job_array_0[201].Score);
    debug::assert(global_job_array_0[201].Running == false);
    debug::assert(global_job_array_0[201].JobID   == 201);
    debug::assert(global_job_array_0[201].Score   == 201.14);

    fmt::println_int(len(global_job_array_0));
    fmt::println_int(capacity(global_job_array_0));
    debug::assert(len(global_job_array_0) == 202);
    debug::assert(capacity(global_job_array_0) == 400);

}