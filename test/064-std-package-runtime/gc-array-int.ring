package main

import {
    fmt;
    debug;
    runtime;
}

global {
}

fn main() {

    var int[]   local_int_array_0;

    local_int_array_0 = new int[20];

    debug::assert(len(local_int_array_0) == 20);
    debug::assert(cap(local_int_array_0) == 24);
    fmt::println(runtime::heap_size());
    debug::assert(runtime::heap_size() == 96L);
    /*
    * 内存分布
    * int[24](垃圾)         占用 4*24 Byte
    * local_int_array_0    占用 4*24 16Byte
    */

    runtime::gc();


    debug::assert(len(local_int_array_0) == 20);
    debug::assert(cap(local_int_array_0) == 24);
    fmt::println(runtime::heap_size());
    debug::assert(runtime::heap_size() == 96L);
    /*
    * 内存分布
    * local_int_array_0    占用 4*24 16Byte
    */
}
