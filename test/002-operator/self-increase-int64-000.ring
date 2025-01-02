package main

import {
	fmt;
	debug;
}

fn main() {


	var int64 local_int64_value_0;

	// -------
	local_int64_value_0 = 1L;
	fmt::println_int64(local_int64_value_0);
	debug::assert(local_int64_value_0 == 1L);

	local_int64_value_0++;
	fmt::println_int64(local_int64_value_0);
	debug::assert(local_int64_value_0 == 2L);

	local_int64_value_0++;
	fmt::println_int64(local_int64_value_0);
	debug::assert(local_int64_value_0 == 3L);

	local_int64_value_0++;
	fmt::println_int64(local_int64_value_0);
	debug::assert(local_int64_value_0 == 4L);

	fmt::println_string("");


	// -------
	local_int64_value_0 = 10L;
	fmt::println_int64(local_int64_value_0);
	debug::assert(local_int64_value_0 == 10L);

	local_int64_value_0--;
	fmt::println_int64(local_int64_value_0);
	debug::assert(local_int64_value_0 == 9L);

	local_int64_value_0--;
	fmt::println_int64(local_int64_value_0);
	debug::assert(local_int64_value_0 == 8L);

	local_int64_value_0--;
	fmt::println_int64(local_int64_value_0);
	debug::assert(local_int64_value_0 == 7L);

	fmt::println_string("");



}