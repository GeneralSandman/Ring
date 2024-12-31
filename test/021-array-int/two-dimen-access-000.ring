package main

import {
    fmt;
    debug;
}

global {
    var int[,] global_int_array_0;
}

@main
fn main() {
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

}
