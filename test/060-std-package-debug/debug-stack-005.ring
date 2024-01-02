
package main

import {
	fmt;
	debug;
}


typedef class Job {
    field bool    Running;
    field int     JobID;
    field double  Score;

    method PrintInfo(var bool Running, var int JobID, var double Score) {
        debug::print_call_stack();
    }
}

global {
    var Job job_0;
}

function PrintInfo(var bool Running, var int JobID, var double Score) {
    debug::print_call_stack();
}

@main
function main() {

    fmt::println_string("\ntest case 1");
    job_0.PrintInfo(true, 1, 1.1);

    
    fmt::println_string("\ntest case 2");
    PrintInfo(true, 1, 1.1);
}