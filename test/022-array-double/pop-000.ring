package main

import {
    fmt;
    debug;
}

global {
  var double[] global_double_array_0;

  var double global_double_value_0;
}

@main
function main() {

    fmt::println_string("test cast 1 ------------------------");
    global_double_array_0 = new double[200];

    fmt::println_double(global_double_array_0[199]);
    fmt::println_int(len(global_double_array_0));
    fmt::println_int(capacity(global_double_array_0));

    debug::debug_assert(global_double_array_0[199] == 0.0);
    debug::debug_assert(len(global_double_array_0) == 200);
    debug::debug_assert(capacity(global_double_array_0) == 200);


    fmt::println_string("\ntest cast 2 ------------------------");
    global_double_array_0[199] = 1.234567;
    global_double_value_0 = pop(global_double_array_0);

    fmt::println_double(global_double_value_0);
    fmt::println_int(len(global_double_array_0));
    fmt::println_int(capacity(global_double_array_0));

    debug::debug_assert(global_double_value_0 == 1.234567);
    debug::debug_assert(len(global_double_array_0) == 199);
    debug::debug_assert(capacity(global_double_array_0) == 200);


    fmt::println_string("\ntest cast 3 ------------------------");
    global_double_array_0[198] = 22.34;
    global_double_value_0 = pop(global_double_array_0);

    fmt::println_double(global_double_value_0);
    fmt::println_int(len(global_double_array_0));
    fmt::println_int(capacity(global_double_array_0));

    debug::debug_assert(global_double_value_0 == 22.34);
    debug::debug_assert(len(global_double_array_0) == 198);
    debug::debug_assert(capacity(global_double_array_0) == 200);
}