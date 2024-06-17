package main

import {
    fmt;
    debug;
}

global {
    var int64[,,,] global_int64_array_0;
}

@main
function main() {
    global_int64_array_0 = new int64[1,2,3,4];

    fmt::println_string("test cast 1 ------------------------");
    fmt::println_int(len(global_int64_array_0));
    fmt::println_int(len(global_int64_array_0[0]));
    fmt::println_int(len(global_int64_array_0[0,0]));
    fmt::println_int(len(global_int64_array_0[0,0,0]));

    debug::debug_assert(len(global_int64_array_0) == 1);
    debug::debug_assert(len(global_int64_array_0[0]) == 2);
    debug::debug_assert(len(global_int64_array_0[0,0]) == 3);
    debug::debug_assert(len(global_int64_array_0[0,0,0]) == 4);


    fmt::println_string("test cast 2 ------------------------");
    fmt::println_int(capacity(global_int64_array_0));
    fmt::println_int(capacity(global_int64_array_0[0]));
    fmt::println_int(capacity(global_int64_array_0[0,0]));
    fmt::println_int(capacity(global_int64_array_0[0,0,0]));

    debug::debug_assert(capacity(global_int64_array_0) == 1);
    debug::debug_assert(capacity(global_int64_array_0[0]) == 2);
    debug::debug_assert(capacity(global_int64_array_0[0,0]) == 3);
    debug::debug_assert(capacity(global_int64_array_0[0,0,0]) == 8);
}
