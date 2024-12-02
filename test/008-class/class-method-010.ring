// TestDetail: class method
// TestDetail: return value from invoke method

package main

import {
	fmt;
	debug;
}


typedef class Job {
    field bool    Running;
    field int     JobID;
    field double  Score;

    method Echo() -> (bool, int, double) {
        return self.Running, self.JobID, self.Score;
    }
}

global {
    var Job job_0;
}

@main
function main() {
    var bool   local_bool_value_0;
    var int    local_int_value_0;
    var double local_double_value_0;


    fmt::println_string("\ntest case 1");
    local_bool_value_0, local_int_value_0, local_double_value_0 = job_0.Echo();
    fmt::println_bool(local_bool_value_0);
    fmt::println_int(local_int_value_0);
    fmt::println_double(local_double_value_0);
    debug::assert(local_bool_value_0   == false);
    debug::assert(local_int_value_0    == 0);
    debug::assert(local_double_value_0 == 0.0);

    
    fmt::println_string("\ntest case 2");
    job_0.Running = true;
    job_0.JobID   = 1;
    job_0.Score   = 1.1;
    local_bool_value_0, local_int_value_0, local_double_value_0 = job_0.Echo();
    fmt::println_bool(local_bool_value_0);
    fmt::println_int(local_int_value_0);
    fmt::println_double(local_double_value_0);
    debug::assert(local_bool_value_0   == true);
    debug::assert(local_int_value_0    == 1);
    debug::assert(local_double_value_0 == 1.1);


    fmt::println_string("\ntest case 2");
    job_0 = Job{
        Running: true,
        JobID:   123, 
        Score:   567.890
    };
    local_bool_value_0, local_int_value_0, local_double_value_0 = job_0.Echo();
    fmt::println_bool(local_bool_value_0);
    fmt::println_int(local_int_value_0);
    fmt::println_double(local_double_value_0);
    debug::assert(local_bool_value_0   == true);
    debug::assert(local_int_value_0    == 123);
    debug::assert(local_double_value_0 == 567.89);
}