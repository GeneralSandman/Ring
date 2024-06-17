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
    global_int64_array_0 = int64[]{0L, 1L, 2L, 
		3L, 4L, 5L, 
		6L, 7L, 8L, 
		9L, };

    fmt::println_string("test cast 1 ------------------------");
    var int i = 0;
    for(i = 0; i < len(global_int64_array_0); i++) {
        fmt::println_int64(global_int64_array_0[i]);
    }

    var int tmp;
    var int j;

    fmt::println_string("\ntest cast 2 ------------------------");
    for(i = 0; i+1 < len(global_int64_array_0); i+=2) {
        global_int64_array_0[i], global_int64_array_0[i+1] = global_int64_array_0[i+1], global_int64_array_0[i];
    }

    for(i = 0; i < len(global_int64_array_0); i++) {
        fmt::println_int64(global_int64_array_0[i]);
    }
}
