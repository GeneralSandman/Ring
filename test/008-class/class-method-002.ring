
package main

import {
	fmt;
	debug;
}



typedef class Job {
    field bool    Running;
    field int     JobID;
    field double  Score;

    @constructor
    method Job(var bool _Running, var int _JobID, var double _Score);

    method PrintInfo() {
        fmt::println_string("invoke Job::PrintInfo");
    }

    method GetStatus() {
        fmt::println_string("invoke Job::GetStatus");
    }

    method GetJobID() {
        fmt::println_string("invoke Job::GetJobID");
    }

    method GetScore() {
        fmt::println_string("invoke Job::GetScore");
    }
}

global {
    
}

@main
function main() {
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