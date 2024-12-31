package main

import {
	fmt;
	debug;
}

global {
	
}

@main
fn main() {
	var bool local_bool_value_1;
	
	fmt::println_string("test case 1");
	fmt::println_bool(local_bool_value_1);
	debug::assert(local_bool_value_1 == false);

	fmt::println_string("\ntest case 2");
	local_bool_value_1 = true;
	fmt::println_bool(local_bool_value_1);
	debug::assert(local_bool_value_1 == true);

	fmt::println_string("\ntest case 3");
	local_bool_value_1 = false;
	fmt::println_bool(local_bool_value_1);
	debug::assert(local_bool_value_1 == false);

	fmt::println_string("\ntest case 4");
	local_bool_value_1 = false;
	fmt::println_bool(local_bool_value_1);
	debug::assert(local_bool_value_1 == false);
}