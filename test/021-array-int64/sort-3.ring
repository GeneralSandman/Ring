package main

import {
    fmt;
    debug;
}

global {
    var int64[] global_int64_array_0;
}

fn main() {
    global_int64_array_0 = new int64[20];

    fmt::println_string("test cast 1 ------------------------");
    var int i = 0;
    var int j = 0;

    for(i = 0; i < len(global_int64_array_0); i++) {
        for(j = i; j < len(global_int64_array_0); j++) {
            global_int64_array_0[j]++;
        }
    }

    // printf
    var int64 num = 1L;
    for(i = 0; i < len(global_int64_array_0); i++) {
        debug::assert(global_int64_array_0[i] == num);
        num++;
    }
}
