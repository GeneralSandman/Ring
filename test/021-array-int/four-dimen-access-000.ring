package main

import {
    fmt;
    debug;
}

global {
    var int[,,,] global_int_array_0;
}

fn main() {
    global_int_array_0 = new int[1,2,3,4];

    fmt::println_string("test cast 1 ------------------------");
    fmt::println_int(len(global_int_array_0));
    fmt::println_int(len(global_int_array_0[0]));
    fmt::println_int(len(global_int_array_0[0,0]));
    fmt::println_int(len(global_int_array_0[0,0,0]));

    debug::assert(len(global_int_array_0) == 1);
    debug::assert(len(global_int_array_0[0]) == 2);
    debug::assert(len(global_int_array_0[0,0]) == 3);
    debug::assert(len(global_int_array_0[0,0,0]) == 4);


    fmt::println_string("test cast 2 ------------------------");
    fmt::println_int(capacity(global_int_array_0));
    fmt::println_int(capacity(global_int_array_0[0]));
    fmt::println_int(capacity(global_int_array_0[0,0]));
    fmt::println_int(capacity(global_int_array_0[0,0,0]));

    debug::assert(capacity(global_int_array_0) == 1);
    debug::assert(capacity(global_int_array_0[0]) == 2);
    debug::assert(capacity(global_int_array_0[0,0]) == 3);
    debug::assert(capacity(global_int_array_0[0,0,0]) == 8);
}
