
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

    fmt::println_string("\ntest case 1");
    job_0.PrintInfo();



    fmt::println_string("\ntest case 2");
    job_0 = Job{
        Running: true,
        JobID: 1, 
        Score: 1.1
    };
    job_0.PrintInfo();



    fmt::println_string("\ntest case 3");
    job_0 = Job{
        Running: true,
        JobID: 123, 
        Score: 123.123
    };
    job_0.PrintInfo();


    fmt::println_string("\ntest case 4");
    job_0 = Job{
        Running: false,
        JobID: 0, 
        Score: 0.0
    };
    job_0.PrintInfo();


}