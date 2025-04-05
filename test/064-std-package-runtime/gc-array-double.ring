package main

import {
    fmt;
    debug;
    runtime;
}

global {
}

fn main() {

    var double[]   local_double_array_0;

    local_double_array_0 = new double[20];

    debug::assert(len(local_double_array_0) == 20);
    debug::assert(cap(local_double_array_0) == 24);
    fmt::println(runtime::heap_size());
    debug::assert(runtime::heap_size() == 192L);


    runtime::gc();


    debug::assert(len(local_double_array_0) == 20);
    debug::assert(cap(local_double_array_0) == 24);
    fmt::println(runtime::heap_size());
    debug::assert(runtime::heap_size() == 192L);
}
