package main

import {
	debug;
	fmt;
}

global {

}

fn main() {
	var bool[] local_bool_array_0 = bool[]{true, false, false, 
		true, false, false, 
		true, false, false, 
		true, false, false, 
		true, false, false,
		true, false, false,
		true, false, false,
		true, false, false,
		true, false, false,
		true, false, false};

	var int index;
	var bool value;
	
	fmt::println_string("test case for-range --------------------");
	for(value in range local_bool_array_0) {
		fmt::println_bool(value);
	}

	fmt::println_string("\ntest case for --------------------");
	for(index = 0; index<30; index++) {
		fmt::println_bool(local_bool_array_0[index]);
	}

	fmt::println_string("\ntest case for-range&for --------------------");
	index = 0;
	for(value in range local_bool_array_0) {
		debug::assert(value == local_bool_array_0[index]);
		index++;
	}

	fmt::println_string("\ntest case range-index --------------------");
	debug::assert(index == 30);
}