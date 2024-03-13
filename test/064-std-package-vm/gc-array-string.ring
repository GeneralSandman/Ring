package main

import {
    fmt;
    debug;
}

global {
}

@main
function main() {
    var string[]   local_string_array_0;

    local_string_array_0 = new string[20];

    debug::debug_assert(len(local_string_array_0) == 20);
    debug::debug_assert(capacity(local_string_array_0) == 24);
    fmt::println(vm::heap_size());
    debug::debug_assert(vm::heap_size() == 320);


    vm::garbage_collect();


    debug::debug_assert(len(local_string_array_0) == 20);
    debug::debug_assert(capacity(local_string_array_0) == 24);
    fmt::println(vm::heap_size());
    debug::debug_assert(vm::heap_size() == 160);




    local_string_array_0[0] = "12345678";

    fmt::println(vm::heap_size());
    debug::debug_assert(vm::heap_size() == 176);

    vm::garbage_collect();

    fmt::println(vm::heap_size());
    debug::debug_assert(vm::heap_size() == 160);
}
