package main

import {
    fmt;
    debug;
}

global {
  var bool[] global_bool_array_0;

  var bool global_bool_value_0;
}

@main
function main() {

    fmt::println_string("test cast 1 ------------------------");
    global_bool_array_0 = new bool[200];

    fmt::println_bool(global_bool_array_0[199]);
    fmt::println_int(len(global_bool_array_0));
    fmt::println_int(capacity(global_bool_array_0));

    debug::assert(global_bool_array_0[199] == false);
    debug::assert(len(global_bool_array_0) == 200);
    debug::assert(capacity(global_bool_array_0) == 200);


    fmt::println_string("\ntest cast 2 ------------------------");
    global_bool_array_0[199] = true;
    global_bool_value_0 = pop(global_bool_array_0);

    fmt::println_bool(global_bool_value_0);
    fmt::println_int(len(global_bool_array_0));
    fmt::println_int(capacity(global_bool_array_0));

    debug::assert(global_bool_value_0 == true);
    debug::assert(len(global_bool_array_0) == 199);
    debug::assert(capacity(global_bool_array_0) == 200);


    fmt::println_string("\ntest cast 3 ------------------------");
    global_bool_array_0[198] = false;
    global_bool_value_0 = pop(global_bool_array_0);

    fmt::println_bool(global_bool_value_0);
    fmt::println_int(len(global_bool_array_0));
    fmt::println_int(capacity(global_bool_array_0));

    debug::assert(global_bool_value_0 == false);
    debug::assert(len(global_bool_array_0) == 198);
    debug::assert(capacity(global_bool_array_0) == 200);
}