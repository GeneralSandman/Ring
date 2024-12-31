package main

import {
	fmt;
	debug;
}

global {
	
}

@main
fn main() {
	var int64  local_int64_value_1;
	
	fmt::println_string("test case 1");
	fmt::println_int64(local_int64_value_1);
	debug::assert(local_int64_value_1 == 0L);

	fmt::println_string("\ntest case 2");
	local_int64_value_1 = 1L;
	fmt::println_int64(local_int64_value_1);
	debug::assert(local_int64_value_1 == 1L);

	fmt::println_string("\ntest case 3");
	local_int64_value_1 = 3L;
	fmt::println_int64(local_int64_value_1);
	debug::assert(local_int64_value_1 == 3L);

	fmt::println_string("\ntest case 4");
	local_int64_value_1 = 1024L;
	fmt::println_int64(local_int64_value_1);
	debug::assert(local_int64_value_1 == 1024L);

	fmt::println_string("\ntest case 5");
	local_int64_value_1 = 65536L;
	fmt::println_int64(local_int64_value_1);
	debug::assert(local_int64_value_1 == 65536L);
}