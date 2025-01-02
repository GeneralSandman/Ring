package main

import {
    fmt;
    debug;
}

global {
  var int[] global_int_array_0;

  var int global_int_value_0;
}

fn main() {

    fmt::println_string("test cast 1 ------------------------");
    global_int_array_0 = new int[200];

    fmt::println_int(global_int_array_0[199]);
    fmt::println_int(len(global_int_array_0));
    fmt::println_int(capacity(global_int_array_0));

    debug::assert(global_int_array_0[199] == 0);
    debug::assert(len(global_int_array_0) == 200);
    debug::assert(capacity(global_int_array_0) == 200);


    fmt::println_string("\ntest cast 2 ------------------------");
    global_int_array_0[199] = 123;
    global_int_value_0 = pop(global_int_array_0);

    fmt::println_int(global_int_value_0);
    fmt::println_int(len(global_int_array_0));
    fmt::println_int(capacity(global_int_array_0));

    debug::assert(global_int_value_0 == 123);
    debug::assert(len(global_int_array_0) == 199);
    debug::assert(capacity(global_int_array_0) == 200);


    fmt::println_string("\ntest cast 3 ------------------------");
    global_int_array_0[198] = 666;
    global_int_value_0 = pop(global_int_array_0);

    fmt::println_int(global_int_value_0);
    fmt::println_int(len(global_int_array_0));
    fmt::println_int(capacity(global_int_array_0));

    debug::assert(global_int_value_0 == 666);
    debug::assert(len(global_int_array_0) == 198);
    debug::assert(capacity(global_int_array_0) == 200);
}