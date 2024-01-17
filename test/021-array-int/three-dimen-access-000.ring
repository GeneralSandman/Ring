package main

import {
    fmt;
    debug;
}

global {
    var int[,,] global_int_array_0;
}

@main
function main() {
    global_int_array_0 = new int[2,2,2];

    fmt::println_string("test cast 1 ------------------------");
    fmt::println_int(global_int_array_0[0,0,0]);
    fmt::println_int(global_int_array_0[0,0,1]);

    fmt::println_int(global_int_array_0[0,1,0]);
    fmt::println_int(global_int_array_0[0,1,1]);


    fmt::println_int(global_int_array_0[1,0,0]);
    fmt::println_int(global_int_array_0[1,0,1]);

    fmt::println_int(global_int_array_0[1,1,0]);
    fmt::println_int(global_int_array_0[1,1,1]);



    fmt::println_string("test cast 2 ------------------------");
    global_int_array_0[0,0,0] = 1;
    global_int_array_0[0,0,1] = 2;

    global_int_array_0[0,1,0] = 3;
    global_int_array_0[0,1,1] = 4;


    global_int_array_0[1,0,0] = 5;
    global_int_array_0[1,0,1] = 6;

    global_int_array_0[1,1,0] = 7;
    global_int_array_0[1,1,1] = 8;



    fmt::println_string("test cast 3 ------------------------");
    fmt::println_int(global_int_array_0[0,0,0]);
    fmt::println_int(global_int_array_0[0,0,1]);

    fmt::println_int(global_int_array_0[0,1,0]);
    fmt::println_int(global_int_array_0[0,1,1]);


    fmt::println_int(global_int_array_0[1,0,0]);
    fmt::println_int(global_int_array_0[1,0,1]);

    fmt::println_int(global_int_array_0[1,1,0]);
    fmt::println_int(global_int_array_0[1,1,1]);


}
