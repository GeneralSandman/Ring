package main

import {
    fmt;
    debug;
}

global {
    var int[] global_int_array_0;
}

fn main() {
    global_int_array_0 = int[]{0,1,2,3,4,5,6,7,8,9};

    fmt::println_string("test cast 1 ------------------------");
    var int i = 0;
    for(i = 0; i < len(global_int_array_0); i++) {
        fmt::println_int(global_int_array_0[i]);
    }

    var int tmp;
    var int j;

    fmt::println_string("\ntest cast 2 ------------------------");
    for(i = 0; i+1 < len(global_int_array_0); i+=2) {
        global_int_array_0[i], global_int_array_0[i+1] = global_int_array_0[i+1], global_int_array_0[i];
    }

    for(i = 0; i < len(global_int_array_0); i++) {
        fmt::println_int(global_int_array_0[i]);
    }
}
