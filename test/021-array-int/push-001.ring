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
    var int int_value;

    fmt::println_string("test cast 0 length&capacity------------------------");
    global_int_array_0 = new int[0];
    fmt::println_int(len(global_int_array_0));
    fmt::println_int(capacity(global_int_array_0));
    debug::assert(len(global_int_array_0) == 0);
    debug::assert(capacity(global_int_array_0) == 0);


    fmt::println_string("\ntest cast 1 length&capacity------------------------");
    push(global_int_array_0, 123);
    fmt::println_int(len(global_int_array_0));
    fmt::println_int(capacity(global_int_array_0));
    debug::assert(len(global_int_array_0) == 1);
    debug::assert(capacity(global_int_array_0) == 8);

    fmt::println_string("\ntest cast 2 length&capacity------------------------");
    push(global_int_array_0, 123);
    fmt::println_int(len(global_int_array_0));
    fmt::println_int(capacity(global_int_array_0));
    debug::assert(len(global_int_array_0) == 2);
    debug::assert(capacity(global_int_array_0) == 8);

    fmt::println_string("\ntest cast 3 length&capacity------------------------");
    push(global_int_array_0, 123);
    fmt::println_int(len(global_int_array_0));
    fmt::println_int(capacity(global_int_array_0));
    debug::assert(len(global_int_array_0) == 3);
    debug::assert(capacity(global_int_array_0) == 8);

    fmt::println_string("\ntest cast 4 length&capacity------------------------");
    push(global_int_array_0, 123);
    fmt::println_int(len(global_int_array_0));
    fmt::println_int(capacity(global_int_array_0));
    debug::assert(len(global_int_array_0) == 4);
    debug::assert(capacity(global_int_array_0) == 8);

    fmt::println_string("\ntest cast 5 length&capacity------------------------");
    push(global_int_array_0, 123);
    fmt::println_int(len(global_int_array_0));
    fmt::println_int(capacity(global_int_array_0));
    debug::assert(len(global_int_array_0) == 5);
    debug::assert(capacity(global_int_array_0) == 8);




    fmt::println_string("\ntest cast 6 value------------------------");
    debug::assert(global_int_array_0[0]  == 123);
    debug::assert(global_int_array_0[1]  == 123);
    debug::assert(global_int_array_0[2]  == 123);
    debug::assert(global_int_array_0[3]  == 123);
    debug::assert(global_int_array_0[4]  == 123);


    fmt::println_string("\ntest cast 7 value------------------------");
    for(int_value in range global_int_array_0) {
        debug::assert(int_value  == 123);
    }
}