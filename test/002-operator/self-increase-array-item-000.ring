
package main

import {
	fmt;
	debug;
}


global {

    var int[] global_int_array_0;
    var int64[] global_int64_array_0;
    var double[] global_double_array_0;
}

// TestDetail: 自增运算符应用到 class中的field
// TestDetail: e.g. 

@main
fn main() {

    global_int_array_0 = new int[10];
    global_int64_array_0 = new int64[10];
    global_double_array_0 = new double[10];


    fmt::println_string("\ntest case 0");
    global_int_array_0[0]++;
    global_int_array_0[9]++;
    global_int64_array_0[0]++;
    global_int64_array_0[9]++;
    global_double_array_0[0]++;
    global_double_array_0[9]++;

    debug::assert(global_int_array_0[0] == 1);
    debug::assert(global_int_array_0[9] == 1);
    debug::assert(global_int64_array_0[0] == 1L);
    debug::assert(global_int64_array_0[9] == 1L);
    debug::assert(global_double_array_0[0] == 1.0);
    debug::assert(global_double_array_0[9] == 1.0);


    fmt::println_string("\ntest case 1");
    global_int_array_0[0]--;
    global_int_array_0[9]--;
    global_int64_array_0[0]--;
    global_int64_array_0[9]--;
    global_double_array_0[0]--;
    global_double_array_0[9]--;

    debug::assert(global_int_array_0[0] == 0);
    debug::assert(global_int_array_0[9] == 0);
    debug::assert(global_int64_array_0[0] == 0L);
    debug::assert(global_int64_array_0[9] == 0L);
    debug::assert(global_double_array_0[0] == 0.0);
    debug::assert(global_double_array_0[9] == 0.0);


}