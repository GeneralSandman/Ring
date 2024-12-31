
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
    }

    fn GetStatus() {
        fmt::println_string("invoke Job::GetStatus");
    }

    fn GetJobID() {
        fmt::println_string("invoke Job::GetJobID");
    }

    fn GetScore() {
        fmt::println_string("invoke Job::GetScore");
    }
}

global {
    
}

@main
fn main() {
    var Job job_0;
    var Job job_1;

    fmt::println_string("\ntest case 1");
    
    job_0.PrintInfo();
    job_0.GetStatus();
    job_0.GetJobID();
    job_0.GetScore();
    
    fmt::println_string("\ntest case 2");
    
    job_1.PrintInfo();
    job_1.GetStatus();
    job_1.GetJobID();
    job_1.GetScore();

}