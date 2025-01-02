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

  var Job global_job_value_0;
}

fn main() {

    global_job_value_0 = Job{
       Running: true,
       JobID: 200, 
       Score: 200.1
    };

    fmt::println_string("test cast 1 ------------------------");
    global_job_array_0 = new Job[5];
    push(global_job_array_0, global_job_value_0);

    fmt::println_int(len(global_job_array_0));
    fmt::println_int(capacity(global_job_array_0));
    debug::assert(len(global_job_array_0) == 6);
    debug::assert(capacity(global_job_array_0) == 8);


    fmt::println_string("\ntest cast 2 ------------------------");
    global_job_value_0 = pop(global_job_array_0);

    fmt::println_bool(global_job_value_0.Running);
    fmt::println_int(global_job_value_0.JobID);
    fmt::println_double(global_job_value_0.Score);
    debug::assert(global_job_value_0.Running == true);
    debug::assert(global_job_value_0.JobID   == 200);
    debug::assert(global_job_value_0.Score   == 200.1);

    fmt::println_int(len(global_job_array_0));
    fmt::println_int(capacity(global_job_array_0));
    debug::assert(len(global_job_array_0) == 5);
    debug::assert(capacity(global_job_array_0) == 8);


    fmt::println_string("\ntest cast 3 ------------------------");
    push(global_job_array_0, Job{
            Running: false,
            JobID: 201, 
            Score: 201.14
        });


    global_job_value_0 = pop(global_job_array_0);

    fmt::println_bool(global_job_value_0.Running);
    fmt::println_int(global_job_value_0.JobID);
    fmt::println_double(global_job_value_0.Score);
    debug::assert(global_job_value_0.Running == false);
    debug::assert(global_job_value_0.JobID   == 201);
    debug::assert(global_job_value_0.Score   == 201.14);

    fmt::println_int(len(global_job_array_0));
    fmt::println_int(capacity(global_job_array_0));
    debug::assert(len(global_job_array_0) == 5);
    debug::assert(capacity(global_job_array_0) == 8);

}