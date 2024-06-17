package main

import {
    fmt;
    debug;
}

global {
  var int64[] global_int64_array_0;
}

@main
function main() {
	global_int64_array_0 = int64[]{0L, 1L, 2L, 
		3L, 4L, 5L, 
		6L, 7L, 8L, 
		9L, 10L, 11L, 
		12L, 13L, 14L};
	

	fmt::println_int64(global_int64_array_0[0]);
	fmt::println_int64(global_int64_array_0[1]);
	fmt::println_int64(global_int64_array_0[2]);
	fmt::println_int64(global_int64_array_0[3]);
	fmt::println_int64(global_int64_array_0[4]);
	fmt::println_int64(global_int64_array_0[5]);
	fmt::println_int64(global_int64_array_0[6]);
	fmt::println_int64(global_int64_array_0[7]);
	fmt::println_int64(global_int64_array_0[8]);
	fmt::println_int64(global_int64_array_0[9]);
	fmt::println_int64(global_int64_array_0[10]);
	fmt::println_int64(global_int64_array_0[11]);
	fmt::println_int64(global_int64_array_0[12]);
	fmt::println_int64(global_int64_array_0[13]);
	fmt::println_int64(global_int64_array_0[14]);

	debug::debug_assert(global_int64_array_0[0]  ==  0L);
	debug::debug_assert(global_int64_array_0[1]  ==  1L);
	debug::debug_assert(global_int64_array_0[2]  ==  2L);
	debug::debug_assert(global_int64_array_0[3]  ==  3L);
	debug::debug_assert(global_int64_array_0[4]  ==  4L);
	debug::debug_assert(global_int64_array_0[5]  ==  5L);
	debug::debug_assert(global_int64_array_0[6]  ==  6L);
	debug::debug_assert(global_int64_array_0[7]  ==  7L);
	debug::debug_assert(global_int64_array_0[8]  ==  8L);
	debug::debug_assert(global_int64_array_0[9]  ==  9L);
	debug::debug_assert(global_int64_array_0[10] == 10L);
	debug::debug_assert(global_int64_array_0[11] == 11L);
	debug::debug_assert(global_int64_array_0[12] == 12L);
	debug::debug_assert(global_int64_array_0[13] == 13L);
	debug::debug_assert(global_int64_array_0[14] == 14L);
}