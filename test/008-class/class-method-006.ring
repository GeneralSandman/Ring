
package main

import {
	fmt;
	debug;
}


typedef Job = class {
    var bool    Running;
    var int     JobID;
    var double  Score;

    fn PrintInfo() {
        fmt::println_string("invoke Job::PrintInfo");
        fmt::println_bool(self.Running);
        fmt::println_int(self.JobID);
        fmt::println_double(self.Score);

        self.Running = true;
        self.JobID   = 1;
        self.Score   = 1.1;

    }
}

global {
    var Job job_0;
}

fn main() {

    fmt::println_string("\ntest case 1");
    job_0.PrintInfo();



    fmt::println_string("\ntest case 2");
    job_0.PrintInfo();


    fmt::println_string("\ntest case 3");
    fmt::println_bool(job_0.Running);
    fmt::println_int(job_0.JobID);
    fmt::println_double(job_0.Score);

    debug::assert(job_0.Running  == true);
    debug::assert(job_0.JobID    == 1);
    debug::assert(job_0.Score    == 1.1);

}