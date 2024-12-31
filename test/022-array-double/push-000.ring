package main

import {
    fmt;
    debug;
}

global {
  var double[] global_double_array_0;
}

@main
fn main() {

    fmt::println_string("test cast 1 ------------------------");
    global_double_array_0 = new double[200];
    fmt::println_int(len(global_double_array_0));
    fmt::println_int(capacity(global_double_array_0));
    debug::assert(len(global_double_array_0) == 200);
    debug::assert(capacity(global_double_array_0) == 200);


    fmt::println_string("\ntest cast 2 ------------------------");
    push(global_double_array_0, 3.456789);
    fmt::println_int(len(global_double_array_0));
    fmt::println_int(capacity(global_double_array_0));
    debug::assert(len(global_double_array_0) == 201);
    debug::assert(capacity(global_double_array_0) == 400);


    fmt::println_string("\ntest cast 3 ------------------------");
    debug::assert(global_double_array_0[0]   == 0.00);
    debug::assert(global_double_array_0[199] == 0.00);
    debug::assert(global_double_array_0[200] == 3.456789);
}