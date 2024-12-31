package main

import {
    fmt;
    debug;
}

global {
  var string[] global_string_array_0;
}

@main
fn main() {

    fmt::println_string("test cast 1 ------------------------");
    global_string_array_0 = new string[200];
    fmt::println_int(len(global_string_array_0));
    fmt::println_int(capacity(global_string_array_0));
    debug::assert(len(global_string_array_0) == 200);
    debug::assert(capacity(global_string_array_0) == 200);


    fmt::println_string("\ntest cast 2 ------------------------");
    push(global_string_array_0, "3.456789");
    fmt::println_int(len(global_string_array_0));
    fmt::println_int(capacity(global_string_array_0));
    debug::assert(len(global_string_array_0) == 201);
    debug::assert(capacity(global_string_array_0) == 400);


    fmt::println_string("\ntest cast 3 ------------------------");
    debug::assert(global_string_array_0[0]   == "");
    debug::assert(global_string_array_0[199] == "");
    debug::assert(global_string_array_0[200] == "3.456789");
}