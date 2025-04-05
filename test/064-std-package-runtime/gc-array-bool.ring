package main

import {
    fmt;
    debug;
    runtime;
}

global {
}

fn main() {

    var bool[]   local_bool_array_0;

    local_bool_array_0 = new bool[20];

    debug::assert(len(local_bool_array_0) == 20);
    debug::assert(cap(local_bool_array_0) == 24);
    fmt::println(runtime::heap_size());
    debug::assert(runtime::heap_size() == 24L);


    runtime::gc();


    debug::assert(len(local_bool_array_0) == 20);
    debug::assert(cap(local_bool_array_0) == 24);
    fmt::println(runtime::heap_size());
    debug::assert(runtime::heap_size() == 24L);
}
