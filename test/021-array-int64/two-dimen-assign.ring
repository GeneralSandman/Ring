package main

import {
    fmt;
    debug;
}

global {
    var int64[,] global_int64_array_0;
}

@main
function main() {
    global_int64_array_0 = new int64[2,4];

    fmt::println_string("test cast 1 ------------------------");
    fmt::println_int64(global_int64_array_0[0,0]);
    fmt::println_int64(global_int64_array_0[0,1]);
    fmt::println_int64(global_int64_array_0[0,2]);
    fmt::println_int64(global_int64_array_0[0,3]);
    fmt::println_int64(global_int64_array_0[1,0]);
    fmt::println_int64(global_int64_array_0[1,1]);
    fmt::println_int64(global_int64_array_0[1,2]);
    fmt::println_int64(global_int64_array_0[1,3]);




    fmt::println_string("\ntest cast 2 ------------------------");
    global_int64_array_0[0,0] = 0L;
    global_int64_array_0[0,1] = 1L;
    global_int64_array_0[0,2] = 2L;
    global_int64_array_0[0,3] = 3L;
    global_int64_array_0[1,0] = 4L;
    global_int64_array_0[1,1] = 5L;
    global_int64_array_0[1,2] = 6L;
    global_int64_array_0[1,3] = 7L;

    fmt::println_int64(global_int64_array_0[0,0]);
    fmt::println_int64(global_int64_array_0[0,1]);
    fmt::println_int64(global_int64_array_0[0,2]);
    fmt::println_int64(global_int64_array_0[0,3]);
    fmt::println_int64(global_int64_array_0[1,0]);
    fmt::println_int64(global_int64_array_0[1,1]);
    fmt::println_int64(global_int64_array_0[1,2]);
    fmt::println_int64(global_int64_array_0[1,3]);



    fmt::println_string("\ntest cast 3 ------------------------");

    var int i = 0;
    var int j = 0;

    for(i = 0; i < 2; i = i+1) {
        for(j = 0; j < 4; j = j+1) {
            fmt::println_int64(global_int64_array_0[i, j]);
        }
    }



    fmt::println_string("\ntest cast 4 ------------------------");
    global_int64_array_0[0,0] = 7L;
    global_int64_array_0[0,1] = 6L;
    global_int64_array_0[0,2] = 5L;
    global_int64_array_0[0,3] = 4L;
    global_int64_array_0[1,0] = 3L;
    global_int64_array_0[1,1] = 2L;
    global_int64_array_0[1,2] = 1L;
    global_int64_array_0[1,3] = 0L;

    fmt::println_int64(global_int64_array_0[0,0]);
    fmt::println_int64(global_int64_array_0[0,1]);
    fmt::println_int64(global_int64_array_0[0,2]);
    fmt::println_int64(global_int64_array_0[0,3]);
    fmt::println_int64(global_int64_array_0[1,0]);
    fmt::println_int64(global_int64_array_0[1,1]);
    fmt::println_int64(global_int64_array_0[1,2]);
    fmt::println_int64(global_int64_array_0[1,3]);



    fmt::println_string("\ntest cast 5 ------------------------");

    i = 0;
    j = 0;

    for(i = 0; i < 2; i = i+1) {
        for(j = 0; j < 4; j = j+1) {
            fmt::println_int64(global_int64_array_0[i, j]);
        }
    }
}
