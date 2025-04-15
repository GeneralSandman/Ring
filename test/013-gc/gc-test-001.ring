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

    test_array_string_3();
    runtime::gc();
}



fn test_array_string() {
	fmt::printf("test_array_string ------------\n");
    var string[] tmp = new string[8];


    debug::assert(runtime::heap_size() == 64L);

    runtime::gc();

    debug::assert(runtime::heap_size() == 64L);
}

fn test_array_string_2() {
	fmt::printf("test_array_string_2 ------------\n");
    new string[8];


    debug::assert(runtime::heap_size() == 64L);

    runtime::gc();

    debug::assert(runtime::heap_size() == 0L);
}


fn test_array_string_3() {
	fmt::printf("test_array_string_3 ------------\n");
    var string[] tmp = new string[8];
    var string local_value_0;

    debug::assert(runtime::heap_size() == 72L); // 8*8 + 8

    // deep copy a string
    tmp[0] = local_value_0;
    debug::assert(runtime::heap_size() == 80L); // 8*8 + 8 + 8


    runtime::gc();

    debug::assert(runtime::heap_size() == 72L); // 8*8 + 8
}