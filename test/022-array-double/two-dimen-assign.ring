package main

import {
    fmt;
    debug;
}

global {
    var double[,] global_double_array_0;
}

@main
fn main() {
    global_double_array_0 = new double[2,4];

    fmt::println_string("test cast 1 ------------------------");
    fmt::println_double(global_double_array_0[0,0]);
    fmt::println_double(global_double_array_0[0,1]);
    fmt::println_double(global_double_array_0[0,2]);
    fmt::println_double(global_double_array_0[0,3]);
    fmt::println_double(global_double_array_0[1,0]);
    fmt::println_double(global_double_array_0[1,1]);
    fmt::println_double(global_double_array_0[1,2]);
    fmt::println_double(global_double_array_0[1,3]);




    fmt::println_string("\ntest cast 2 ------------------------");
    global_double_array_0[0,0] = 0.1;
    global_double_array_0[0,1] = 1.1;
    global_double_array_0[0,2] = 2.1;
    global_double_array_0[0,3] = 3.1;
    global_double_array_0[1,0] = 4.1;
    global_double_array_0[1,1] = 5.1;
    global_double_array_0[1,2] = 6.1;
    global_double_array_0[1,3] = 7.1;

    fmt::println_double(global_double_array_0[0,0]);
    fmt::println_double(global_double_array_0[0,1]);
    fmt::println_double(global_double_array_0[0,2]);
    fmt::println_double(global_double_array_0[0,3]);
    fmt::println_double(global_double_array_0[1,0]);
    fmt::println_double(global_double_array_0[1,1]);
    fmt::println_double(global_double_array_0[1,2]);
    fmt::println_double(global_double_array_0[1,3]);



    fmt::println_string("\ntest cast 3 ------------------------");

    var int i = 0;
    var int j = 0;

    for(i = 0; i < 2; i = i+1) {
        for(j = 0; j < 4; j = j+1) {
            fmt::println_double(global_double_array_0[i, j]);
        }
    }



    fmt::println_string("\ntest cast 4 ------------------------");
    global_double_array_0[0,0] = 0.2;
    global_double_array_0[0,1] = 1.2;
    global_double_array_0[0,2] = 2.2;
    global_double_array_0[0,3] = 3.2;
    global_double_array_0[1,0] = 4.2;
    global_double_array_0[1,1] = 5.2;
    global_double_array_0[1,2] = 6.2;
    global_double_array_0[1,3] = 7.2;

    fmt::println_double(global_double_array_0[0,0]);
    fmt::println_double(global_double_array_0[0,1]);
    fmt::println_double(global_double_array_0[0,2]);
    fmt::println_double(global_double_array_0[0,3]);
    fmt::println_double(global_double_array_0[1,0]);
    fmt::println_double(global_double_array_0[1,1]);
    fmt::println_double(global_double_array_0[1,2]);
    fmt::println_double(global_double_array_0[1,3]);



    fmt::println_string("\ntest cast 5 ------------------------");

    i = 0;
    j = 0;

    for(i = 0; i < 2; i = i+1) {
        for(j = 0; j < 4; j = j+1) {
            fmt::println_double(global_double_array_0[i, j]);
        }
    }
}
