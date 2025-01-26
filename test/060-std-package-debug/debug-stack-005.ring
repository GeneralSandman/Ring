
package main

import {
	fmt;
	runtime;
}


typedef Job = class {
    var bool    Running;
    var int     JobID;
    var double  Score;

    fn PrintInfo(var bool Running, var int JobID, var double Score) {
        runtime::print_call_stack();
    }
}

global {
    var Job job_0;
}

fn PrintInfo(var bool Running, var int JobID, var double Score) {
    runtime::print_call_stack();
}


fn main() {

    fmt::println_string("\ntest case 1");
    job_0.PrintInfo(true, 1, 1.1);

    
    fmt::println_string("\ntest case 2");
    PrintInfo(true, 1, 1.1);
}