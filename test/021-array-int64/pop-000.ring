package main

import {
    fmt;
    debug;
}

global {
  var int64[] global_int64_array_0;

  var int64 global_int64_value_0;
}

fn main() {

    fmt::println_string("test cast 1 ------------------------");
    global_int64_array_0 = new int64[200];

    fmt::println_int64(global_int64_array_0[199]);
    fmt::println_int(len(global_int64_array_0));
    fmt::println_int(cap(global_int64_array_0));

    debug::assert(global_int64_array_0[199] == 0L);
    debug::assert(len(global_int64_array_0) == 200);
    debug::assert(cap(global_int64_array_0) == 200);


    fmt::println_string("\ntest cast 2 ------------------------");
    global_int64_array_0[199] = 123L;
    global_int64_value_0 = pop(global_int64_array_0);

    fmt::println_int64(global_int64_value_0);
    fmt::println_int(len(global_int64_array_0));
    fmt::println_int(cap(global_int64_array_0));

    debug::assert(global_int64_value_0 == 123L);
    debug::assert(len(global_int64_array_0) == 199);
    debug::assert(cap(global_int64_array_0) == 200);


    fmt::println_string("\ntest cast 3 ------------------------");
    global_int64_array_0[198] = 666L;
    global_int64_value_0 = pop(global_int64_array_0);

    fmt::println_int64(global_int64_value_0);
    fmt::println_int(len(global_int64_array_0));
    fmt::println_int(cap(global_int64_array_0));

    debug::assert(global_int64_value_0 == 666L);
    debug::assert(len(global_int64_array_0) == 198);
    debug::assert(cap(global_int64_array_0) == 200);
}