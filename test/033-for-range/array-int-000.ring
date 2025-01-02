package main

import {
	debug;
	fmt;
}

global {

}

fn main() {
	var int[] local_int_array_0 = int[]{0, 1, 2, 
		3, 4, 5, 
		6, 7, 8, 
		9, 10, 11, 
		12, 13, 14,
		15, 16, 17,
		18, 19, 20,
		21, 22, 23,
		24, 25, 26,
		27, 28, 29};

	var int index;
	var int value;

	fmt::println_string("test case for-range --------------------");
	for(value in range local_int_array_0) {
		fmt::println_int(value);
	}

	fmt::println_string("\ntest case for --------------------");
	for(index = 0; index<30; index++) {
		fmt::println_int(local_int_array_0[index]);
	}

	fmt::println_string("\ntest case for-range&for --------------------");
	index = 0;
	for(value in range local_int_array_0) {
		debug::assert(value == local_int_array_0[index]);
		index++;
	}

	fmt::println_string("\ntest case range-index --------------------");
	debug::assert(index == 30);
}