package main

import {
    fmt;
    debug;
}

global {
    var int[] global_int_array_0;
}

@main
function main() {
    global_int_array_0 = new int[20];

    fmt::println_string("test cast 1 ------------------------");
    var int i = 0;
    var int j = 0;

    for(i = 0; i < len(global_int_array_0); i++) {
        for(j = i; j < len(global_int_array_0); j++) {
            global_int_array_0[j] = global_int_array_0[j] + 1;
            global_int_array_0[j]++;
        }
    }

    // printf
    for(i = 0; i < len(global_int_array_0); i++) {
        fmt::println_int(global_int_array_0[i]);
    }
}
