package main

import {
    fmt;
    debug;
}

global {
  var double[] global_double_array_0;
}

fn main() {
    var double double_value;

    fmt::println_string("test cast 0 length&capacity------------------------");
    global_double_array_0 = new double[0];
    fmt::println_int(len(global_double_array_0));
    fmt::println_int(capacity(global_double_array_0));
    debug::assert(len(global_double_array_0) == 0);
    debug::assert(capacity(global_double_array_0) == 0);


    fmt::println_string("\ntest cast 1 length&capacity------------------------");
    push(global_double_array_0, 6.578);
    fmt::println_int(len(global_double_array_0));
    fmt::println_int(capacity(global_double_array_0));
    debug::assert(len(global_double_array_0) == 1);
    debug::assert(capacity(global_double_array_0) == 4);

    fmt::println_string("\ntest cast 2 length&capacity------------------------");
    push(global_double_array_0, 6.578);
    fmt::println_int(len(global_double_array_0));
    fmt::println_int(capacity(global_double_array_0));
    debug::assert(len(global_double_array_0) == 2);
    debug::assert(capacity(global_double_array_0) == 4);

    fmt::println_string("\ntest cast 3 length&capacity------------------------");
    push(global_double_array_0, 6.578);
    fmt::println_int(len(global_double_array_0));
    fmt::println_int(capacity(global_double_array_0));
    debug::assert(len(global_double_array_0) == 3);
    debug::assert(capacity(global_double_array_0) == 4);

    fmt::println_string("\ntest cast 4 length&capacity------------------------");
    push(global_double_array_0, 6.578);
    fmt::println_int(len(global_double_array_0));
    fmt::println_int(capacity(global_double_array_0));
    debug::assert(len(global_double_array_0) == 4);
    debug::assert(capacity(global_double_array_0) == 4);

    fmt::println_string("\ntest cast 5 length&capacity------------------------");
    push(global_double_array_0, 6.578);
    fmt::println_int(len(global_double_array_0));
    fmt::println_int(capacity(global_double_array_0));
    debug::assert(len(global_double_array_0) == 5);
    debug::assert(capacity(global_double_array_0) == 8);




    fmt::println_string("\ntest cast 6 value------------------------");
    debug::assert(global_double_array_0[0]  == 6.578);
    debug::assert(global_double_array_0[1]  == 6.578);
    debug::assert(global_double_array_0[2]  == 6.578);
    debug::assert(global_double_array_0[3]  == 6.578);
    debug::assert(global_double_array_0[4]  == 6.578);


    fmt::println_string("\ntest cast 7 value------------------------");
    for(double_value in range global_double_array_0) {
        debug::assert(double_value  == 6.578);
    }
}