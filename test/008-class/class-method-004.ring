
package main

import {
	fmt;
	debug;
}


typedef class Job {
    field bool    Running;
    field int     JobID;
    field double  Score;

    method PrintInfo() {
        fmt::println_string("invoke Job::PrintInfo");
        fmt::println_bool(self.Running);
        fmt::println_int(self.JobID);
        fmt::println_double(self.Score);
    }
}

global {
    var Job job_0;
}

@main
function main() {
    job_0.PrintInfo();

    job_0.Running = true;

    job_0.PrintInfo();
}