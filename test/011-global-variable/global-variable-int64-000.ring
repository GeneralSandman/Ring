package main

import {
	fmt;
	debug;
}

global {
	var int64  global_int64_value_1;
	
}

@main
function main() {
	
	fmt::println_string("test case 1");
	fmt::println_int64(global_int64_value_1);
	debug::assert(global_int64_value_1 == 0L);

	fmt::println_string("\ntest case 2");
	global_int64_value_1 = 1L;
	fmt::println_int64(global_int64_value_1);
	debug::assert(global_int64_value_1 == 1L);

	fmt::println_string("\ntest case 3");
	global_int64_value_1 = 3L;
	fmt::println_int64(global_int64_value_1);
	debug::assert(global_int64_value_1 == 3L);

	fmt::println_string("\ntest case 4");
	global_int64_value_1 = 1024L;
	fmt::println_int64(global_int64_value_1);
	debug::assert(global_int64_value_1 == 1024L);

	fmt::println_string("\ntest case 5");
	global_int64_value_1 = 65536L;
	fmt::println_int64(global_int64_value_1);
	debug::assert(global_int64_value_1 == 65536L);
}