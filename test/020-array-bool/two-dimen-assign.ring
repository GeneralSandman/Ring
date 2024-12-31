package main

import {
    fmt;
    debug;
}

global {
    var bool[,] global_bool_array_0;
}

@main
fn main() {
    global_bool_array_0 = new bool[2,4];

    fmt::println_string("test cast 1 ------------------------");
    fmt::println_bool(global_bool_array_0[0,0]);
    fmt::println_bool(global_bool_array_0[0,1]);
    fmt::println_bool(global_bool_array_0[0,2]);
    fmt::println_bool(global_bool_array_0[0,3]);
    fmt::println_bool(global_bool_array_0[1,0]);
    fmt::println_bool(global_bool_array_0[1,1]);
    fmt::println_bool(global_bool_array_0[1,2]);
    fmt::println_bool(global_bool_array_0[1,3]);




    fmt::println_string("\ntest cast 2 ------------------------");
    global_bool_array_0[0,0] = true;
    global_bool_array_0[0,1] = true;
    global_bool_array_0[0,2] = true;
    global_bool_array_0[0,3] = true;
    global_bool_array_0[1,0] = true;
    global_bool_array_0[1,1] = true;
    global_bool_array_0[1,2] = true;
    global_bool_array_0[1,3] = true;

    fmt::println_bool(global_bool_array_0[0,0]);
    fmt::println_bool(global_bool_array_0[0,1]);
    fmt::println_bool(global_bool_array_0[0,2]);
    fmt::println_bool(global_bool_array_0[0,3]);
    fmt::println_bool(global_bool_array_0[1,0]);
    fmt::println_bool(global_bool_array_0[1,1]);
    fmt::println_bool(global_bool_array_0[1,2]);
    fmt::println_bool(global_bool_array_0[1,3]);



    fmt::println_string("\ntest cast 3 ------------------------");

    var int i = 0;
    var int j = 0;

    for(i = 0; i < 2; i = i+1) {
        for(j = 0; j < 4; j = j+1) {
            fmt::println_bool(global_bool_array_0[i, j]);
        }
    }



    fmt::println_string("\ntest cast 4 ------------------------");
    global_bool_array_0[0,0] = false;
    global_bool_array_0[0,1] = true;
    global_bool_array_0[0,2] = false;
    global_bool_array_0[0,3] = true;
    global_bool_array_0[1,0] = false;
    global_bool_array_0[1,1] = true;
    global_bool_array_0[1,2] = false;
    global_bool_array_0[1,3] = true;

    fmt::println_bool(global_bool_array_0[0,0]);
    fmt::println_bool(global_bool_array_0[0,1]);
    fmt::println_bool(global_bool_array_0[0,2]);
    fmt::println_bool(global_bool_array_0[0,3]);
    fmt::println_bool(global_bool_array_0[1,0]);
    fmt::println_bool(global_bool_array_0[1,1]);
    fmt::println_bool(global_bool_array_0[1,2]);
    fmt::println_bool(global_bool_array_0[1,3]);



    fmt::println_string("\ntest cast 5 ------------------------");

    i = 0;
    j = 0;

    for(i = 0; i < 2; i = i+1) {
        for(j = 0; j < 4; j = j+1) {
            fmt::println_bool(global_bool_array_0[i, j]);
        }
    }
}
