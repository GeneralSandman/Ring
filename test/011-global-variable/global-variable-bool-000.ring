package main

import {
	fmt;
	debug;
}

global {
	var bool global_bool_value_1;
}

@main
fn main() {
	
	fmt::println_string("test case 1");
	fmt::println_bool(global_bool_value_1);
	debug::assert(global_bool_value_1 == false);

	fmt::println_string("\ntest case 2");
	global_bool_value_1 = true;
	fmt::println_bool(global_bool_value_1);
	debug::assert(global_bool_value_1 == true);

	fmt::println_string("\ntest case 3");
	global_bool_value_1 = false;
	fmt::println_bool(global_bool_value_1);
	debug::assert(global_bool_value_1 == false);

	fmt::println_string("\ntest case 4");
	global_bool_value_1 = false;
	fmt::println_bool(global_bool_value_1);
	debug::assert(global_bool_value_1 == false);
}