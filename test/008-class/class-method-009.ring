
package main

import {
	fmt;
	debug;
}


typedef class Job {
    var bool    Running;
    var int     JobID;
    var double  Score;

    fn PrintInfo(var bool Running, var int JobID, var double Score) {
        var bool   local_bool_value_0;
        var int    local_int_value_0;
        var double local_double_value_0;

        local_bool_value_0 = self.Running;
        local_int_value_0 = self.JobID;
        local_double_value_0 = self.Score;

        Running = self.Running;
        JobID = self.JobID;
        Score = self.Score;

        fmt::println_string("invoke Job::PrintInfo");

        fmt::println_string("");
        fmt::println_bool(self.Running);
        fmt::println_int(self.JobID);
        fmt::println_double(self.Score);

        fmt::println_string("");
        fmt::println_bool(local_bool_value_0);
        fmt::println_int(local_int_value_0);
        fmt::println_double(local_double_value_0);

        fmt::println_string("");
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

    
    fmt::println_string("\ntest case 2");
    job_0.Running = true;
    job_0.JobID   = 1;
    job_0.Score   = 1.1;
    job_0.PrintInfo(false, 2, 2.2);
}