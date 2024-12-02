
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
}

@main
function main() {




    fmt::println_string("\ntest case 1");
    fmt::println_bool(job_0.Running);
    fmt::println_int(job_0.JobID);
    fmt::println_double(job_0.Score);
    debug::assert(job_0.Running == false);
    debug::assert(job_0.JobID == 0);
    debug::assert(job_0.Score == 0.0);





    job_0 = Job{
        Running: true,
        JobID: 1, 
        Score: 1.1
    };
    fmt::println_string("\ntest case 2");
    fmt::println_bool(job_0.Running);
    fmt::println_int(job_0.JobID);
    fmt::println_double(job_0.Score);
    debug::assert(job_0.Running == true);
    debug::assert(job_0.JobID == 1);
    debug::assert(job_0.Score == 1.1);




    job_0 = Job{
        Running: false,
        JobID: 2, 
        Score: 2.2
    };
    fmt::println_string("\ntest case 3");
    fmt::println_bool(job_0.Running);
    fmt::println_int(job_0.JobID);
    fmt::println_double(job_0.Score);
    debug::assert(job_0.Running == false);
    debug::assert(job_0.JobID == 2);
    debug::assert(job_0.Score == 2.2);


    job_0 = Job{
        Running: true,
        JobID: 3, 
        Score: 3.1415
    };
    fmt::println_string("\ntest case 3");
    fmt::println_bool(job_0.Running);
    fmt::println_int(job_0.JobID);
    fmt::println_double(job_0.Score);
    debug::assert(job_0.Running == true);
    debug::assert(job_0.JobID == 3);
    debug::assert(job_0.Score == 3.1415);
    
}
