package main

import {
    fmt;
    debug;
}

global {
    var string[,,] global_string_array_0;
}

@main
function main() {
    global_string_array_0 = new string[2,2,2];

    fmt::println_string("test cast 1 ------------------------");
    fmt::println_string(global_string_array_0[0,0,0]);
    fmt::println_string(global_string_array_0[0,0,1]);

    fmt::println_string(global_string_array_0[0,1,0]);
    fmt::println_string(global_string_array_0[0,1,1]);


    fmt::println_string(global_string_array_0[1,0,0]);
    fmt::println_string(global_string_array_0[1,0,1]);

    fmt::println_string(global_string_array_0[1,1,0]);
    fmt::println_string(global_string_array_0[1,1,1]);



    fmt::println_string("test cast 2 ------------------------");
    global_string_array_0[0,0,0] = "true";
    global_string_array_0[0,0,1] = "false";

    global_string_array_0[0,1,0] = "true";
    global_string_array_0[0,1,1] = "false";


    global_string_array_0[1,0,0] = "true";
    global_string_array_0[1,0,1] = "false";

    global_string_array_0[1,1,0] = "true";
    global_string_array_0[1,1,1] = "false";



    fmt::println_string("test cast 3 ------------------------");
    fmt::println_string(global_string_array_0[0,0,0]);
    fmt::println_string(global_string_array_0[0,0,1]);

    fmt::println_string(global_string_array_0[0,1,0]);
    fmt::println_string(global_string_array_0[0,1,1]);


    fmt::println_string(global_string_array_0[1,0,0]);
    fmt::println_string(global_string_array_0[1,0,1]);

    fmt::println_string(global_string_array_0[1,1,0]);
    fmt::println_string(global_string_array_0[1,1,1]);


}
