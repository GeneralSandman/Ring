package main

import {
    fmt;
    debug;
    runtime;
}



fn main() {
    test_array_string();
    runtime::gc();

    test_array_string_2();
    runtime::gc();
}



fn test_array_string() {
    var string[] tmp = new string[8];


    debug::assert(runtime::heap_size() == 64L);

    runtime::gc();

    debug::assert(runtime::heap_size() == 64L);
}

fn test_array_string_2() {
    new string[8];


    debug::assert(runtime::heap_size() == 64L);

    runtime::gc();

    debug::assert(runtime::heap_size() == 0L);
}
