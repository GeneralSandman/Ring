package main

import {
    fmt;
    debug;
}

global {
    var int64[!8] global_int64_array_0;
}

@main
function main() {
    var int a = 8;
    var int b = 7;
    var int c = 6;
    var int d = 5;
    var int e = 4;
    var int f = 3;
    var int g = 2;
    var int h = 1;

    global_int64_array_0 = new int[a,b,c,d,e,f,g,h];

    fmt::println_int(len(global_int64_array_0));
    fmt::println_int(len(global_int64_array_0[0]));
    fmt::println_int(len(global_int64_array_0[0,0]));
	fmt::println_int(len(global_int64_array_0[0,0,0]));
	fmt::println_int(len(global_int64_array_0[0,0,0,0]));
	fmt::println_int(len(global_int64_array_0[0,0,0,0,0]));
	fmt::println_int(len(global_int64_array_0[0,0,0,0,0,0]));
	fmt::println_int(len(global_int64_array_0[0,0,0,0,0,0,0]));
	   
	   
    debug::debug_assert(len(global_int64_array_0) == a);
    debug::debug_assert(len(global_int64_array_0[0]) == b);
    debug::debug_assert(len(global_int64_array_0[0,0]) == c);
    debug::debug_assert(len(global_int64_array_0[0,0,0]) == d);
    debug::debug_assert(len(global_int64_array_0[0,0,0,0]) == e);
    debug::debug_assert(len(global_int64_array_0[0,0,0,0,0]) == f);
    debug::debug_assert(len(global_int64_array_0[0,0,0,0,0,0]) == g);
    debug::debug_assert(len(global_int64_array_0[0,0,0,0,0,0,0]) == h);

}
