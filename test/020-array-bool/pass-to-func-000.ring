package main

import {
    fmt;
    debug;
}

global {
  var bool[] global_bool_array_0;
}

fn main() {
	global_bool_array_0 = bool[]{true, false, false, 
		true, false, false, 
		true, false, false, 
		true, false, false, 
		true, false, false};

	func_accept_bool_array(global_bool_array_0);
	
}

fn func_accept_bool_array(var bool[] bool_array) {
	fmt::println_bool(bool_array[0]);
	fmt::println_bool(bool_array[1]);
	fmt::println_bool(bool_array[2]);
	fmt::println_bool(bool_array[3]);
	fmt::println_bool(bool_array[4]);
	fmt::println_bool(bool_array[5]);
	fmt::println_bool(bool_array[6]);
	fmt::println_bool(bool_array[7]);
	fmt::println_bool(bool_array[8]);
	fmt::println_bool(bool_array[9]);
	fmt::println_bool(bool_array[10]);
	fmt::println_bool(bool_array[11]);
	fmt::println_bool(bool_array[12]);
	fmt::println_bool(bool_array[13]);
	fmt::println_bool(bool_array[14]);

	debug::assert(bool_array[0] == true);
	debug::assert(bool_array[1] == false);
	debug::assert(bool_array[2] == false);
	debug::assert(bool_array[3] == true);
	debug::assert(bool_array[4] == false);
	debug::assert(bool_array[5] == false);
	debug::assert(bool_array[6] == true);
	debug::assert(bool_array[7] == false);
	debug::assert(bool_array[8] == false);
	debug::assert(bool_array[9] == true);
	debug::assert(bool_array[10] == false);
	debug::assert(bool_array[11] == false);
	debug::assert(bool_array[12] == true);
	debug::assert(bool_array[13] == false);
	debug::assert(bool_array[14] == false);
}