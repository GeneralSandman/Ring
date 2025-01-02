package main

import {
	fmt;
	debug;
}

global {
	var int64 global_int64_value_0;

}

fn main() {



	// -------
	global_int64_value_0 = 1L;
	fmt::println_int64(global_int64_value_0);
	debug::assert(global_int64_value_0 == 1L);

	global_int64_value_0++;
	fmt::println_int64(global_int64_value_0);
	debug::assert(global_int64_value_0 == 2L);

	global_int64_value_0++;
	fmt::println_int64(global_int64_value_0);
	debug::assert(global_int64_value_0 == 3L);

	global_int64_value_0++;
	fmt::println_int64(global_int64_value_0);
	debug::assert(global_int64_value_0 == 4L);

	fmt::println_string("");


	// -------
	global_int64_value_0 = 10L;
	fmt::println_int64(global_int64_value_0);
	debug::assert(global_int64_value_0 == 10L);

	global_int64_value_0--;
	fmt::println_int64(global_int64_value_0);
	debug::assert(global_int64_value_0 == 9L);

	global_int64_value_0--;
	fmt::println_int64(global_int64_value_0);
	debug::assert(global_int64_value_0 == 8L);

	global_int64_value_0--;
	fmt::println_int64(global_int64_value_0);
	debug::assert(global_int64_value_0 == 7L);

	fmt::println_string("");



}