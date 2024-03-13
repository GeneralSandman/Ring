package main

import {
    fmt;
    debug;
}

global {
}

@main
function main() {
    var bool[]   local_bool_array_0;

    local_bool_array_0 = new bool[20];

    debug::debug_assert(len(local_bool_array_0) == 20);
    debug::debug_assert(capacity(local_bool_array_0) == 24);
    fmt::println(vm::heap_size());
    debug::debug_assert(vm::heap_size() == 48);


    vm::garbage_collect();


    debug::debug_assert(len(local_bool_array_0) == 20);
    debug::debug_assert(capacity(local_bool_array_0) == 24);
    fmt::println(vm::heap_size());
    debug::debug_assert(vm::heap_size() == 24);
}
