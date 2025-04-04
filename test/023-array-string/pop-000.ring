package main

import {
    fmt;
    debug;
}

global {
  var string[] global_string_array_0;

  var string global_string_value_0;
}

fn main() {

    fmt::println_string("test cast 1 ------------------------");
    global_string_array_0 = new string[200];

    fmt::println_string(global_string_array_0[199]);
    fmt::println_int(len(global_string_array_0));
    fmt::println_int(cap(global_string_array_0));

    debug::assert(global_string_array_0[199] == "");
    debug::assert(len(global_string_array_0) == 200);
    debug::assert(cap(global_string_array_0) == 200);


    fmt::println_string("\ntest cast 2 ------------------------");
    global_string_array_0[199] = "1.234567";
    global_string_value_0 = pop(global_string_array_0);

    fmt::println_string(global_string_value_0);
    fmt::println_int(len(global_string_array_0));
    fmt::println_int(cap(global_string_array_0));

    debug::assert(global_string_value_0 == "1.234567");
    debug::assert(len(global_string_array_0) == 199);
    debug::assert(cap(global_string_array_0) == 200);


    fmt::println_string("\ntest cast 3 ------------------------");
    global_string_array_0[198] = "22.34";
    global_string_value_0 = pop(global_string_array_0);

    fmt::println_string(global_string_value_0);
    fmt::println_int(len(global_string_array_0));
    fmt::println_int(cap(global_string_array_0));

    debug::assert(global_string_value_0 == "22.34");
    debug::assert(len(global_string_array_0) == 198);
    debug::assert(cap(global_string_array_0) == 200);
}