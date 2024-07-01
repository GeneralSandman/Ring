package main

import {
	debug;
	fmt;
}

global {

}

@main
function main() {
	var int64[] local_int_array_0 = int64[]{0L, 1L, 2L, 
		3L,  4L,  5L, 
		6L,  7L,  8L, 
		9L,  10L, 11L, 
		12L, 13L, 14L,
		15L, 16L, 17L,
		18L, 19L, 20L,
		21L, 22L, 23L,
		24L, 25L, 26L,
		27L, 28L, 29L};

	var int index;
	var int64 value;

	fmt::println_string("test case for-range --------------------");
	for(value in range local_int_array_0) {
		fmt::println_int64(value);
	}

	fmt::println_string("\ntest case for --------------------");
	for(index = 0; index<30; index++) {
		fmt::println_int64(local_int_array_0[index]);
	}

	fmt::println_string("\ntest case for-range&for --------------------");
	index = 0;
	for(value in range local_int_array_0) {
		debug::debug_assert(value == local_int_array_0[index]);
		index++;
	}

	fmt::println_string("\ntest case range-index --------------------");
	debug::debug_assert(index == 30);
}