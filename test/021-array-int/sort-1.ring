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
    global_int_array_0 = int[]{9,8,7,6,5,4,3,2,1,0};

    var int i = 0;
    for(;i < len(global_int_array_0); i++) {
        fmt::println_int(global_int_array_0[i]);
    }

    var int tmp;
    var int j;

    for(i=0; i+1 < len(global_int_array_0); i+=2) {
        global_int_array_0[i], global_int_array_0[i+1] = global_int_array_0[i+1], global_int_array_0[i];
    }

    i = 0;
    for(;i < len(global_int_array_0); i++) {
        fmt::println_int(global_int_array_0[i]);
    }
}
