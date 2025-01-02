package main

import {
	fmt;
	debug;
}

global {
	var int  global_int_value_1;
	
}

fn main() {
	
	fmt::println_string("test case 1");
	fmt::println_int(global_int_value_1);
	debug::assert(global_int_value_1 == 0);

	fmt::println_string("\ntest case 2");
	global_int_value_1 = 1;
	fmt::println_int(global_int_value_1);
	debug::assert(global_int_value_1 == 1);

	fmt::println_string("\ntest case 3");
	global_int_value_1 = 3;
	fmt::println_int(global_int_value_1);
	debug::assert(global_int_value_1 == 3);

	fmt::println_string("\ntest case 4");
	global_int_value_1 = 1024;
	fmt::println_int(global_int_value_1);
	debug::assert(global_int_value_1 == 1024);

	fmt::println_string("\ntest case 5");
	global_int_value_1 = 65536;
	fmt::println_int(global_int_value_1);
	debug::assert(global_int_value_1 == 65536);
}