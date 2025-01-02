
package main

import {
	fmt;
	debug;
}


typedef class Job {
    var bool    Running;
    var int     JobID;
    var double  Score;
    var string  Name;

    fn PrintInfo() {
        fmt::println_string("invoke Job::PrintInfo");
        fmt::println_bool(self.Running);
        fmt::println_int(self.JobID);
        fmt::println_double(self.Score);
        fmt::println_string(self.Name);
    }
}

global {
    var Job job_0;
}

fn main() {

    fmt::println_string("\ntest case 1");
    job_0.PrintInfo();



    fmt::println_string("\ntest case 2");
    job_0 = Job{
        Running: true,
        JobID: 1, 
        Score: 1.1,
        Name:  "job_0_0"
    };
    job_0.PrintInfo();



    fmt::println_string("\ntest case 3");
    job_0 = Job{
        Running: true,
        JobID: 123, 
        Score: 123.123,
        Name:  "job_0_1"
    };
    job_0.PrintInfo();


    fmt::println_string("\ntest case 4");
    job_0 = Job{
        Running: false,
        JobID: 0, 
        Score: 0.0,
        Name:  "job_0_2"
    };
    job_0.PrintInfo();


}