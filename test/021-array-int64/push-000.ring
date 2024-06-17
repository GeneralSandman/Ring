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

    fmt::println_string("test cast 1 ------------------------");
    global_int64_array_0 = new int64[200];
    fmt::println_int(len(global_int64_array_0));
    fmt::println_int(capacity(global_int64_array_0));
    debug::debug_assert(len(global_int64_array_0) == 200);
    debug::debug_assert(capacity(global_int64_array_0) == 200);


    fmt::println_string("\ntest cast 2 ------------------------");
    push(global_int64_array_0, 123L);
    fmt::println_int(len(global_int64_array_0));
    fmt::println_int(capacity(global_int64_array_0));
    debug::debug_assert(len(global_int64_array_0) == 201);
    debug::debug_assert(capacity(global_int64_array_0) == 400);


    fmt::println_string("\ntest cast 3 ------------------------");
    debug::debug_assert(global_int64_array_0[0]   == 0L);
    debug::debug_assert(global_int64_array_0[199] == 0L);
    debug::debug_assert(global_int64_array_0[200] == 123L);

}