package main

import {
	fmt;
	debug;
}

typedef class Job {
    field bool    Bool;
    field int     Int;
    field double  Double;

    @constructor
    method Job(var bool _Bool, var int _Int, var double _Double) {
        
    }

    method PrintInfo() {
        
    }
}

global {
    var Job global_value_job_0;
}

@main
function main() {

    fmt::println_string("test case 1");
    fmt::println_bool(global_value_job_0.Bool);
    fmt::println_int(global_value_job_0.Int);
    fmt::println_double(global_value_job_0.Double);
    debug::debug_assert(global_value_job_0.Bool == false);
    debug::debug_assert(global_value_job_0.Int == 0);
    debug::debug_assert(global_value_job_0.Double == 0.0);

    fmt::println_string("\ntest case 2");
    global_value_job_0.Bool = true;
    global_value_job_0.Int = 1;
    global_value_job_0.Double = 1.1;
    fmt::println_bool(global_value_job_0.Bool);
    fmt::println_int(global_value_job_0.Int);
    fmt::println_double(global_value_job_0.Double);
    debug::debug_assert(global_value_job_0.Bool == true);
    debug::debug_assert(global_value_job_0.Int == 1);
    debug::debug_assert(global_value_job_0.Double == 1.1);

}