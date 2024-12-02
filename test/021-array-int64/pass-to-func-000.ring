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
	

	func_accept_int64_array(global_int64_array_0);
	
}

function func_accept_int64_array(var int64[] int64_array) {
	fmt::println_int64(int64_array[0]);
	fmt::println_int64(int64_array[1]);
	fmt::println_int64(int64_array[2]);
	fmt::println_int64(int64_array[3]);
	fmt::println_int64(int64_array[4]);
	fmt::println_int64(int64_array[5]);
	fmt::println_int64(int64_array[6]);
	fmt::println_int64(int64_array[7]);
	fmt::println_int64(int64_array[8]);
	fmt::println_int64(int64_array[9]);
	fmt::println_int64(int64_array[10]);
	fmt::println_int64(int64_array[11]);
	fmt::println_int64(int64_array[12]);
	fmt::println_int64(int64_array[13]);
	fmt::println_int64(int64_array[14]);

	debug::assert(int64_array[0]  ==  0L);
	debug::assert(int64_array[1]  ==  1L);
	debug::assert(int64_array[2]  ==  2L);
	debug::assert(int64_array[3]  ==  3L);
	debug::assert(int64_array[4]  ==  4L);
	debug::assert(int64_array[5]  ==  5L);
	debug::assert(int64_array[6]  ==  6L);
	debug::assert(int64_array[7]  ==  7L);
	debug::assert(int64_array[8]  ==  8L);
	debug::assert(int64_array[9]  ==  9L);
	debug::assert(int64_array[10] == 10L);
	debug::assert(int64_array[11] == 11L);
	debug::assert(int64_array[12] == 12L);
	debug::assert(int64_array[13] == 13L);
	debug::assert(int64_array[14] == 14L);
}