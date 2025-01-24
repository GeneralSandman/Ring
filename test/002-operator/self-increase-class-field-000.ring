
package main

import {
	fmt;
	debug;
}



typedef Job = class {
    var bool    Bool;
    var int     Int;
    var int64   Int64;
    var double  Double;
}

global {
    var Job global_job_value_0;
    var Job global_job_value_1;
}

// TestDetail: 自增运算符应用到 class中的field
// TestDetail: e.g. 

fn main() {


    fmt::println_string("\ntest case 0");
    fmt::println_bool(global_job_value_0.Bool);
    fmt::println_int(global_job_value_0.Int);
    fmt::println_int64(global_job_value_0.Int64);
    fmt::println_double(global_job_value_0.Double);
    debug::assert(global_job_value_0.Bool   == false);
    debug::assert(global_job_value_0.Int    == 0);
    debug::assert(global_job_value_0.Int64  == 0L);
    debug::assert(global_job_value_0.Double == 0.0);



    fmt::println_string("\ntest case 1-1");
    global_job_value_0.Int++;

    fmt::println_bool(global_job_value_0.Bool);
    fmt::println_int(global_job_value_0.Int);
    fmt::println_int64(global_job_value_0.Int64);
    fmt::println_double(global_job_value_0.Double);
    debug::assert(global_job_value_0.Bool   == false);
    debug::assert(global_job_value_0.Int    == 1);
    debug::assert(global_job_value_0.Int64  == 0L);
    debug::assert(global_job_value_0.Double == 0.0);



    fmt::println_string("\ntest case 1-2");
    global_job_value_0.Int++;
    global_job_value_0.Int64++;

    fmt::println_bool(global_job_value_0.Bool);
    fmt::println_int(global_job_value_0.Int);
    fmt::println_int64(global_job_value_0.Int64);
    fmt::println_double(global_job_value_0.Double);
    debug::assert(global_job_value_0.Bool   == false);
    debug::assert(global_job_value_0.Int    == 2);
    debug::assert(global_job_value_0.Int64  == 1L);
    debug::assert(global_job_value_0.Double == 0.0);



    fmt::println_string("\ntest case 1-3");
    global_job_value_0.Int++;
    global_job_value_0.Int64++;
    global_job_value_0.Double++;

    fmt::println_bool(global_job_value_0.Bool);
    fmt::println_int(global_job_value_0.Int);
    fmt::println_int64(global_job_value_0.Int64);
    fmt::println_double(global_job_value_0.Double);
    debug::assert(global_job_value_0.Bool   == false);
    debug::assert(global_job_value_0.Int    == 3);
    debug::assert(global_job_value_0.Int64  == 2L);
    debug::assert(global_job_value_0.Double == 1.0);





    fmt::println_string("\ntest case 2-1");
    global_job_value_0.Int--;

    fmt::println_bool(global_job_value_0.Bool);
    fmt::println_int(global_job_value_0.Int);
    fmt::println_int64(global_job_value_0.Int64);
    fmt::println_double(global_job_value_0.Double);
    debug::assert(global_job_value_0.Bool   == false);
    debug::assert(global_job_value_0.Int    == 2);
    debug::assert(global_job_value_0.Int64  == 2L);
    debug::assert(global_job_value_0.Double == 1.0);


    fmt::println_string("\ntest case 2-2");
    global_job_value_0.Int--;
    global_job_value_0.Int64--;

    fmt::println_bool(global_job_value_0.Bool);
    fmt::println_int(global_job_value_0.Int);
    fmt::println_int64(global_job_value_0.Int64);
    fmt::println_double(global_job_value_0.Double);
    debug::assert(global_job_value_0.Bool   == false);
    debug::assert(global_job_value_0.Int    == 1);
    debug::assert(global_job_value_0.Int64  == 1L);
    debug::assert(global_job_value_0.Double == 1.0);


    fmt::println_string("\ntest case 2-3");
    global_job_value_0.Int--;
    global_job_value_0.Int64--;
    global_job_value_0.Double--;

    fmt::println_bool(global_job_value_0.Bool);
    fmt::println_int(global_job_value_0.Int);
    fmt::println_int64(global_job_value_0.Int64);
    fmt::println_double(global_job_value_0.Double);
    debug::assert(global_job_value_0.Bool   == false);
    debug::assert(global_job_value_0.Int    == 0);
    debug::assert(global_job_value_0.Int64  == 0L);
    debug::assert(global_job_value_0.Double == 0.0);


}