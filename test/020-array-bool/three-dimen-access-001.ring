package main

import {
    fmt;
    debug;
}

global {
    var bool[,,] global_bool_array_0;
}

fn main() {
    global_bool_array_0 = new bool[2,2,2];

    fmt::println_string("test cast 1 ------------------------");
    fmt::println_bool(global_bool_array_0[0,0,0]);
    fmt::println_bool(global_bool_array_0[0,0,1]);

    fmt::println_bool(global_bool_array_0[0,1,0]);
    fmt::println_bool(global_bool_array_0[0,1,1]);


    fmt::println_bool(global_bool_array_0[1,0,0]);
    fmt::println_bool(global_bool_array_0[1,0,1]);

    fmt::println_bool(global_bool_array_0[1,1,0]);
    fmt::println_bool(global_bool_array_0[1,1,1]);



    fmt::println_string("\ntest cast 2 ------------------------");

    var int i = 0;
    var int j = 0;
    var int k = 0;
    var int sum = 0;

    for(i = 0; i < 2; i = i+1) {
        for(j = 0; j < 2; j = j+1) {
            for(k = 0; k < 2; k = k+1) {
                fmt::println_bool(global_bool_array_0[i, j, k]);
                sum = sum + 1;
            }
        }
    }

    fmt::println_string("");
    fmt::println_int(sum);


}
