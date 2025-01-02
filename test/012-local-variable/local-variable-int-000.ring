package main

import {
	fmt;
	debug;
}

global {
	
}

fn main() {
	var int  local_int_value_1;
	
	fmt::println_string("test case 1");
	fmt::println_int(local_int_value_1);
	debug::assert(local_int_value_1 == 0);

	fmt::println_string("\ntest case 2");
	local_int_value_1 = 1;
	fmt::println_int(local_int_value_1);
	debug::assert(local_int_value_1 == 1);

	fmt::println_string("\ntest case 3");
	local_int_value_1 = 3;
	fmt::println_int(local_int_value_1);
	debug::assert(local_int_value_1 == 3);

	fmt::println_string("\ntest case 4");
	local_int_value_1 = 1024;
	fmt::println_int(local_int_value_1);
	debug::assert(local_int_value_1 == 1024);

	fmt::println_string("\ntest case 5");
	local_int_value_1 = 65536;
	fmt::println_int(local_int_value_1);
	debug::assert(local_int_value_1 == 65536);
}