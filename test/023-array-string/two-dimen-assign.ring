package main

import {
    fmt;
    debug;
}

global {
    var string[,] global_string_array_0;
}

@main
function main() {
    global_string_array_0 = new string[2,4];

    fmt::println_string("test cast 1 ------------------------");
    fmt::println_string(global_string_array_0[0,0]);
    fmt::println_string(global_string_array_0[0,1]);
    fmt::println_string(global_string_array_0[0,2]);
    fmt::println_string(global_string_array_0[0,3]);
    fmt::println_string(global_string_array_0[1,0]);
    fmt::println_string(global_string_array_0[1,1]);
    fmt::println_string(global_string_array_0[1,2]);
    fmt::println_string(global_string_array_0[1,3]);




    fmt::println_string("\ntest cast 2 ------------------------");
    global_string_array_0[0,0] = "000";
    global_string_array_0[0,1] = "111";
    global_string_array_0[0,2] = "222";
    global_string_array_0[0,3] = "333";
    global_string_array_0[1,0] = "444";
    global_string_array_0[1,1] = "555";
    global_string_array_0[1,2] = "666";
    global_string_array_0[1,3] = "777";

    fmt::println_string(global_string_array_0[0,0]);
    fmt::println_string(global_string_array_0[0,1]);
    fmt::println_string(global_string_array_0[0,2]);
    fmt::println_string(global_string_array_0[0,3]);
    fmt::println_string(global_string_array_0[1,0]);
    fmt::println_string(global_string_array_0[1,1]);
    fmt::println_string(global_string_array_0[1,2]);
    fmt::println_string(global_string_array_0[1,3]);



    fmt::println_string("\ntest cast 3 ------------------------");

    var int i = 0;
    var int j = 0;

    for(i = 0; i < 2; i = i+1) {
        for(j = 0; j < 4; j = j+1) {
            fmt::println_string(global_string_array_0[i, j]);
        }
    }



    fmt::println_string("\ntest cast 4 ------------------------");
    global_string_array_0[0,0] = "777";
    global_string_array_0[0,1] = "666";
    global_string_array_0[0,2] = "555";
    global_string_array_0[0,3] = "444";
    global_string_array_0[1,0] = "333";
    global_string_array_0[1,1] = "222";
    global_string_array_0[1,2] = "111";
    global_string_array_0[1,3] = "000";

    fmt::println_string(global_string_array_0[0,0]);
    fmt::println_string(global_string_array_0[0,1]);
    fmt::println_string(global_string_array_0[0,2]);
    fmt::println_string(global_string_array_0[0,3]);
    fmt::println_string(global_string_array_0[1,0]);
    fmt::println_string(global_string_array_0[1,1]);
    fmt::println_string(global_string_array_0[1,2]);
    fmt::println_string(global_string_array_0[1,3]);



    fmt::println_string("\ntest cast 5 ------------------------");

    var int i = 0;
    var int j = 0;

    for(i = 0; i < 2; i = i+1) {
        for(j = 0; j < 4; j = j+1) {
            fmt::println_string(global_string_array_0[i, j]);
        }
    }
}
