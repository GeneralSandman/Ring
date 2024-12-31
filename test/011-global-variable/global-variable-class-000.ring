package main

import {
	fmt;
	debug;
}

typedef class Job {
    var bool    Bool;
    var int     Int;
    var double  Double;

    fn PrintInfo() {
        
    }
}

global {
    var Job global_value_job_0;
}

@main
fn main() {

    fmt::println_string("test case 1");
    fmt::println_bool(global_value_job_0.Bool);
    fmt::println_int(global_value_job_0.Int);
    fmt::println_double(global_value_job_0.Double);
    debug::assert(global_value_job_0.Bool == false);
    debug::assert(global_value_job_0.Int == 0);
    debug::assert(global_value_job_0.Double == 0.0);

    fmt::println_string("\ntest case 2");
    global_value_job_0.Bool = true;
    global_value_job_0.Int = 1;
    global_value_job_0.Double = 1.1;
    fmt::println_bool(global_value_job_0.Bool);
    fmt::println_int(global_value_job_0.Int);
    fmt::println_double(global_value_job_0.Double);
    debug::assert(global_value_job_0.Bool == true);
    debug::assert(global_value_job_0.Int == 1);
    debug::assert(global_value_job_0.Double == 1.1);

}