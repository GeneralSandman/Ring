package main

import {
    fmt;
    debug;
}

global {
}

@main
function main() {
    var double[]   local_double_array_0;

    local_double_array_0 = new double[20];

    debug::debug_assert(len(local_double_array_0) == 20);
    debug::debug_assert(capacity(local_double_array_0) == 24);
    fmt::println(vm::heap_size());
    debug::debug_assert(vm::heap_size() == 384);


    vm::garbage_collect();


    debug::debug_assert(len(local_double_array_0) == 20);
    debug::debug_assert(capacity(local_double_array_0) == 24);
    fmt::println(vm::heap_size());
    debug::debug_assert(vm::heap_size() == 192);
}
