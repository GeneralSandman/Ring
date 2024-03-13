package main

import {
    fmt;
    debug;
}

global {
}

@main
function main() {
    var int[]   local_int_array_0;

    local_int_array_0 = new int[20];

    debug::debug_assert(len(local_int_array_0) == 20);
    debug::debug_assert(capacity(local_int_array_0) == 24);
    fmt::println(vm::heap_size());
    debug::debug_assert(vm::heap_size() == 192);


    vm::garbage_collect();


    debug::debug_assert(len(local_int_array_0) == 20);
    debug::debug_assert(capacity(local_int_array_0) == 24);
    fmt::println(vm::heap_size());
    debug::debug_assert(vm::heap_size() == 96); // 24*4
}
