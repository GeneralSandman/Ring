package main

import {
    fmt;
    debug;
}

global {
    var double[,,] global_double_array_0;
}

fn main() {
    global_double_array_0 = new double[2,2,2];

    fmt::println_string("test cast 1 ------------------------");
    fmt::println_double(global_double_array_0[0,0,0]);
    fmt::println_double(global_double_array_0[0,0,1]);

    fmt::println_double(global_double_array_0[0,1,0]);
    fmt::println_double(global_double_array_0[0,1,1]);


    fmt::println_double(global_double_array_0[1,0,0]);
    fmt::println_double(global_double_array_0[1,0,1]);

    fmt::println_double(global_double_array_0[1,1,0]);
    fmt::println_double(global_double_array_0[1,1,1]);



    fmt::println_string("test cast 2 ------------------------");
    global_double_array_0[0,0,0] = 1.1;
    global_double_array_0[0,0,1] = 2.2;

    global_double_array_0[0,1,0] = 3.3;
    global_double_array_0[0,1,1] = 4.4;


    global_double_array_0[1,0,0] = 5.5;
    global_double_array_0[1,0,1] = 6.6;

    global_double_array_0[1,1,0] = 7.7;
    global_double_array_0[1,1,1] = 8.8;



    fmt::println_string("test cast 3 ------------------------");
    fmt::println_double(global_double_array_0[0,0,0]);
    fmt::println_double(global_double_array_0[0,0,1]);

    fmt::println_double(global_double_array_0[0,1,0]);
    fmt::println_double(global_double_array_0[0,1,1]);


    fmt::println_double(global_double_array_0[1,0,0]);
    fmt::println_double(global_double_array_0[1,0,1]);

    fmt::println_double(global_double_array_0[1,1,0]);
    fmt::println_double(global_double_array_0[1,1,1]);


}
