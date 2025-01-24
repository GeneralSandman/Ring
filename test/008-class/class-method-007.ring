
package main

import {
	fmt;
	debug;
}


typedef Job = class {
    var bool    Running;
    var int     JobID;
    var double  Score;

    fn PrintInfo(var bool Running, var int JobID, var double Score) {
        fmt::println_string("invoke Job::PrintInfo");
        fmt::println_bool(self.Running);
        fmt::println_int(self.JobID);
        fmt::println_double(self.Score);

        fmt::println_bool(Running);
        fmt::println_int(JobID);
        fmt::println_double(Score);
    }
}

global {
    var Job job_0;
}

fn main() {

    fmt::println_string("\ntest case 1");
    job_0.PrintInfo(true, 1, 1.1);

    
    fmt::println_string("\ntest case 1");
    job_0.Running = true;
    job_0.JobID   = 1;
    job_0.Score   = 1.1;
    job_0.PrintInfo(false, 0, 0.0);
}