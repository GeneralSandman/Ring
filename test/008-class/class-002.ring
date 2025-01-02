
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
        
    }
}

/*
fn Job::Init(var bool _Running, var int _JobID, var double _Score) {
    self.Running = _Running;
    self.JobID   = _JobID;
    self.Score   = _Score;
}
*/

/*
fn Job::PrintInfo() {
    fmt::println_bool(self.Running);
    fmt::println_int(self.JobID);
    fmt::println_double(self.Score);
}
*/

/*
fmt::println_string("\ntest case 1");
var bool    Running;
var int     JobID;
var double  Score;
fmt::println_bool(Running);
fmt::println_int(JobID);
fmt::println_double(Score);


fmt::println_string("\ntest case 2");
*/

global {
    var Job job_0;
}

fn main() {

    // fmt::println_bool(job_0.Running);
    // fmt::println_int(job_0.JobID);
    // fmt::println_double(job_0.Score);

    job_0.Running = true;
    job_0.JobID = 1;
    job_0.Score = 1.1;
    fmt::println_bool(job_0.Running);
    fmt::println_int(job_0.JobID);
    fmt::println_double(job_0.Score);

}