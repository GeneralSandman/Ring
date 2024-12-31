package main

import {
    fmt;
    debug;
}

global {
    var int[] global_int_array_0;
}

@main
fn main() {
    global_int_array_0 = new int[20];

    fmt::println_string("test cast 1 ------------------------");
    var int i = 0;
    var int j = 0;

    for(i = 0; i < len(global_int_array_0); i++) {
        for(j = i; j < len(global_int_array_0); j++) {
            global_int_array_0[j]++;
        }
    }

    // printf
    var int num = 1;
    for(i = 0; i < len(global_int_array_0); i++) {
        debug::assert(global_int_array_0[i] == num);
        num++;
    }
}
