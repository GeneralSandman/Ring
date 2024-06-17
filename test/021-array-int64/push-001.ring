package main

import {
    fmt;
    debug;
}

global {
  var int64[] global_int64_array_0;
}

@main
function main() {
    var int64 int64_value;

    fmt::println_string("test cast 0 length&capacity------------------------");
    global_int64_array_0 = new int64[0];
    fmt::println_int(len(global_int64_array_0));
    fmt::println_int(capacity(global_int64_array_0));
    debug::debug_assert(len(global_int64_array_0) == 0);
    debug::debug_assert(capacity(global_int64_array_0) == 0);


    fmt::println_string("\ntest cast 1 length&capacity------------------------");
    push(global_int64_array_0, 123L);
    fmt::println_int(len(global_int64_array_0));
    fmt::println_int(capacity(global_int64_array_0));
    debug::debug_assert(len(global_int64_array_0) == 1);
    debug::debug_assert(capacity(global_int64_array_0) == 8);

    fmt::println_string("\ntest cast 2 length&capacity------------------------");
    push(global_int64_array_0, 123L);
    fmt::println_int(len(global_int64_array_0));
    fmt::println_int(capacity(global_int64_array_0));
    debug::debug_assert(len(global_int64_array_0) == 2);
    debug::debug_assert(capacity(global_int64_array_0) == 8);

    fmt::println_string("\ntest cast 3 length&capacity------------------------");
    push(global_int64_array_0, 123L);
    fmt::println_int(len(global_int64_array_0));
    fmt::println_int(capacity(global_int64_array_0));
    debug::debug_assert(len(global_int64_array_0) == 3);
    debug::debug_assert(capacity(global_int64_array_0) == 8);

    fmt::println_string("\ntest cast 4 length&capacity------------------------");
    push(global_int64_array_0, 123L);
    fmt::println_int(len(global_int64_array_0));
    fmt::println_int(capacity(global_int64_array_0));
    debug::debug_assert(len(global_int64_array_0) == 4);
    debug::debug_assert(capacity(global_int64_array_0) == 8);

    fmt::println_string("\ntest cast 5 length&capacity------------------------");
    push(global_int64_array_0, 123L);
    fmt::println_int(len(global_int64_array_0));
    fmt::println_int(capacity(global_int64_array_0));
    debug::debug_assert(len(global_int64_array_0) == 5);
    debug::debug_assert(capacity(global_int64_array_0) == 8);




    fmt::println_string("\ntest cast 6 value------------------------");
    debug::debug_assert(global_int64_array_0[0]  == 123L);
    debug::debug_assert(global_int64_array_0[1]  == 123L);
    debug::debug_assert(global_int64_array_0[2]  == 123L);
    debug::debug_assert(global_int64_array_0[3]  == 123L);
    debug::debug_assert(global_int64_array_0[4]  == 123L);


    fmt::println_string("\ntest cast 7 value------------------------");
    for(int64_value in range global_int64_array_0) {
        debug::debug_assert(int64_value  == 123L);
    }
}