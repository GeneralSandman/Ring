package main

import {
    fmt;
    debug;
}

global {
  var int64[] global_int64_array_0;
}

@main
fn main() {
	global_int64_array_0 = func_return_int64_array();
	
	fmt::println_string("\n=================func main\n");
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

	debug::assert(global_int64_array_0[0]  ==  0L);
	debug::assert(global_int64_array_0[1]  ==  1L);
	debug::assert(global_int64_array_0[2]  ==  2L);
	debug::assert(global_int64_array_0[3]  ==  3L);
	debug::assert(global_int64_array_0[4]  ==  4L);
	debug::assert(global_int64_array_0[5]  ==  5L);
	debug::assert(global_int64_array_0[6]  ==  6L);
	debug::assert(global_int64_array_0[7]  ==  7L);
	debug::assert(global_int64_array_0[8]  ==  8L);
	debug::assert(global_int64_array_0[9]  ==  9L);
	debug::assert(global_int64_array_0[10] == 10L);
	debug::assert(global_int64_array_0[11] == 11L);
	debug::assert(global_int64_array_0[12] == 12L);
	debug::assert(global_int64_array_0[13] == 13L);
	debug::assert(global_int64_array_0[14] == 14L);
}

fn func_return_int64_array() -> (int64[]) {
	var int64[] int64_array = int64[]{0L, 1L, 2L, 
		3L, 4L, 5L, 
		6L, 7L, 8L, 
		9L, 10L, 11L, 
		12L, 13L, 14L};
	
	fmt::println_string("=================func func_return_int64_array\n");
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

	return int64_array;
}