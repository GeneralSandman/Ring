
package main

import {
	fmt;
	debug;
}


typedef class Job {
    var bool    Running;
    var int     JobID;
    var double  Score;

    fn PrintInfo() {
        fmt::println_string("invoke Job::PrintInfo");
        fmt::println_bool(self.Running);
        fmt::println_int(self.JobID);
        fmt::println_double(self.Score);
    }
}

global {
    var Job job_0;
}

fn main() {
    job_0.PrintInfo();
}