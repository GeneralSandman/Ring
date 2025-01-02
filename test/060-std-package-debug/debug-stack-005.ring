
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
        debug::print_call_stack();
    }
}

global {
    var Job job_0;
}

fn PrintInfo(var bool Running, var int JobID, var double Score) {
    debug::print_call_stack();
}


fn main() {

    fmt::println_string("\ntest case 1");
    job_0.PrintInfo(true, 1, 1.1);

    
    fmt::println_string("\ntest case 2");
    PrintInfo(true, 1, 1.1);
}