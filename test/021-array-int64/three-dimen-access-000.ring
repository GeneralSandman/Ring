package main

import {
    fmt;
    debug;
}

global {
    var int64[,,] global_int64_array_0;
}

@main
fn main() {
    global_int64_array_0 = new int64[2,2,2];

    fmt::println_string("test cast 1 ------------------------");
    fmt::println_int64(global_int64_array_0[0,0,0]);
    fmt::println_int64(global_int64_array_0[0,0,1]);

    fmt::println_int64(global_int64_array_0[0,1,0]);
    fmt::println_int64(global_int64_array_0[0,1,1]);


    fmt::println_int64(global_int64_array_0[1,0,0]);
    fmt::println_int64(global_int64_array_0[1,0,1]);

    fmt::println_int64(global_int64_array_0[1,1,0]);
    fmt::println_int64(global_int64_array_0[1,1,1]);



    fmt::println_string("test cast 2 ------------------------");
    global_int64_array_0[0,0,0] = 1L;
    global_int64_array_0[0,0,1] = 2L;

    global_int64_array_0[0,1,0] = 3L;
    global_int64_array_0[0,1,1] = 4L;


    global_int64_array_0[1,0,0] = 5L;
    global_int64_array_0[1,0,1] = 6L;

    global_int64_array_0[1,1,0] = 7L;
    global_int64_array_0[1,1,1] = 8L;



    fmt::println_string("test cast 3 ------------------------");
    fmt::println_int64(global_int64_array_0[0,0,0]);
    fmt::println_int64(global_int64_array_0[0,0,1]);

    fmt::println_int64(global_int64_array_0[0,1,0]);
    fmt::println_int64(global_int64_array_0[0,1,1]);


    fmt::println_int64(global_int64_array_0[1,0,0]);
    fmt::println_int64(global_int64_array_0[1,0,1]);

    fmt::println_int64(global_int64_array_0[1,1,0]);
    fmt::println_int64(global_int64_array_0[1,1,1]);


}
