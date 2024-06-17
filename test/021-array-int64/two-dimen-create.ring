package main

import {
    fmt;
    debug;
}

global {
    var int64[,] global_int64_array_0;
}

@main
function main() {
    global_int64_array_0 = new int64[2,4];

    debug::debug_assert(len(global_int64_array_0) == 2);
    debug::debug_assert(len(global_int64_array_0[0]) == 4);

}
