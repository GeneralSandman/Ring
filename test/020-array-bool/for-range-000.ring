package main

import {
    fmt;
    debug;
}

global {
    var bool[] global_bool_array_0;
}

@main
function main() {
    global_bool_array_0 = new bool[10];

    test_array(false, true, false, true);
}


function test_array(var bool... array_value) {
    var bool bool_value;
    for(bool_value in range array_value) {
        fmt::println(bool_value);
    }
}
