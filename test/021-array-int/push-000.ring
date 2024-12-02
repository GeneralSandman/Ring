package main

import {
    fmt;
    debug;
}

global {
  var int[] global_int_array_0;
}

@main
function main() {

    fmt::println_string("test cast 1 ------------------------");
    global_int_array_0 = new int[200];
    fmt::println_int(len(global_int_array_0));
    fmt::println_int(capacity(global_int_array_0));
    debug::assert(len(global_int_array_0) == 200);
    debug::assert(capacity(global_int_array_0) == 200);


    fmt::println_string("\ntest cast 2 ------------------------");
    push(global_int_array_0, 123);
    fmt::println_int(len(global_int_array_0));
    fmt::println_int(capacity(global_int_array_0));
    debug::assert(len(global_int_array_0) == 201);
    debug::assert(capacity(global_int_array_0) == 400);


    fmt::println_string("\ntest cast 3 ------------------------");
    debug::assert(global_int_array_0[0]   == 0);
    debug::assert(global_int_array_0[199] == 0);
    debug::assert(global_int_array_0[200] == 123);

}