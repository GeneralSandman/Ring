package main

import {
    fmt;
    debug;
}

global {
  var bool[] global_bool_array_0;
}

fn main() {
    var bool bool_value;

    fmt::println_string("test cast 0 length&capacity------------------------");
    global_bool_array_0 = new bool[0];
    fmt::println_int(len(global_bool_array_0));
    fmt::println_int(cap(global_bool_array_0));
    debug::assert(len(global_bool_array_0) == 0);
    debug::assert(cap(global_bool_array_0) == 0);


    fmt::println_string("\ntest cast 1 length&capacity------------------------");
    push(global_bool_array_0, true);
    fmt::println_int(len(global_bool_array_0));
    fmt::println_int(cap(global_bool_array_0));
    debug::assert(len(global_bool_array_0) == 1);
    debug::assert(cap(global_bool_array_0) == 8);

    fmt::println_string("\ntest cast 2 length&capacity------------------------");
    push(global_bool_array_0, true);
    fmt::println_int(len(global_bool_array_0));
    fmt::println_int(cap(global_bool_array_0));
    debug::assert(len(global_bool_array_0) == 2);
    debug::assert(cap(global_bool_array_0) == 8);

    fmt::println_string("\ntest cast 3 length&capacity------------------------");
    push(global_bool_array_0, true);
    fmt::println_int(len(global_bool_array_0));
    fmt::println_int(cap(global_bool_array_0));
    debug::assert(len(global_bool_array_0) == 3);
    debug::assert(cap(global_bool_array_0) == 8);

    fmt::println_string("\ntest cast 4 length&capacity------------------------");
    push(global_bool_array_0, true);
    fmt::println_int(len(global_bool_array_0));
    fmt::println_int(cap(global_bool_array_0));
    debug::assert(len(global_bool_array_0) == 4);
    debug::assert(cap(global_bool_array_0) == 8);

    fmt::println_string("\ntest cast 5 length&capacity------------------------");
    push(global_bool_array_0, true);
    fmt::println_int(len(global_bool_array_0));
    fmt::println_int(cap(global_bool_array_0));
    debug::assert(len(global_bool_array_0) == 5);
    debug::assert(cap(global_bool_array_0) == 8);




    fmt::println_string("\ntest cast 6 value------------------------");
    debug::assert(global_bool_array_0[0]  == true);
    debug::assert(global_bool_array_0[1]  == true);
    debug::assert(global_bool_array_0[2]  == true);
    debug::assert(global_bool_array_0[3]  == true);
    debug::assert(global_bool_array_0[4]  == true);


    fmt::println_string("\ntest cast 7 value------------------------");
    for(bool_value in range global_bool_array_0) {
        debug::assert(bool_value  == true);
    }
}