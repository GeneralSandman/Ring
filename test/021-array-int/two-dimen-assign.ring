package main

import {
    fmt;
    debug;
}

global {
    var int[,] global_int_array_0;
}

@main
function main() {
    global_int_array_0 = new int[2,4];

    fmt::println_string("test cast 1 ------------------------");
    fmt::println_int(global_int_array_0[0,0]);
    fmt::println_int(global_int_array_0[0,1]);
    fmt::println_int(global_int_array_0[0,2]);
    fmt::println_int(global_int_array_0[0,3]);
    fmt::println_int(global_int_array_0[1,0]);
    fmt::println_int(global_int_array_0[1,1]);
    fmt::println_int(global_int_array_0[1,2]);
    fmt::println_int(global_int_array_0[1,3]);




    fmt::println_string("\ntest cast 2 ------------------------");
    global_int_array_0[0,0] = 0;
    global_int_array_0[0,1] = 1;
    global_int_array_0[0,2] = 2;
    global_int_array_0[0,3] = 3;
    global_int_array_0[1,0] = 4;
    global_int_array_0[1,1] = 5;
    global_int_array_0[1,2] = 6;
    global_int_array_0[1,3] = 7;

    fmt::println_int(global_int_array_0[0,0]);
    fmt::println_int(global_int_array_0[0,1]);
    fmt::println_int(global_int_array_0[0,2]);
    fmt::println_int(global_int_array_0[0,3]);
    fmt::println_int(global_int_array_0[1,0]);
    fmt::println_int(global_int_array_0[1,1]);
    fmt::println_int(global_int_array_0[1,2]);
    fmt::println_int(global_int_array_0[1,3]);



    fmt::println_string("\ntest cast 3 ------------------------");

    var int i = 0;
    var int j = 0;

    for(i = 0; i < 2; i = i+1) {
        for(j = 0; j < 4; j = j+1) {
            fmt::println_int(global_int_array_0[i, j]);
        }
    }



    fmt::println_string("\ntest cast 4 ------------------------");
    global_int_array_0[0,0] = 7;
    global_int_array_0[0,1] = 6;
    global_int_array_0[0,2] = 5;
    global_int_array_0[0,3] = 4;
    global_int_array_0[1,0] = 3;
    global_int_array_0[1,1] = 2;
    global_int_array_0[1,2] = 1;
    global_int_array_0[1,3] = 0;

    fmt::println_int(global_int_array_0[0,0]);
    fmt::println_int(global_int_array_0[0,1]);
    fmt::println_int(global_int_array_0[0,2]);
    fmt::println_int(global_int_array_0[0,3]);
    fmt::println_int(global_int_array_0[1,0]);
    fmt::println_int(global_int_array_0[1,1]);
    fmt::println_int(global_int_array_0[1,2]);
    fmt::println_int(global_int_array_0[1,3]);



    fmt::println_string("\ntest cast 5 ------------------------");

    var int i = 0;
    var int j = 0;

    for(i = 0; i < 2; i = i+1) {
        for(j = 0; j < 4; j = j+1) {
            fmt::println_int(global_int_array_0[i, j]);
        }
    }
}
