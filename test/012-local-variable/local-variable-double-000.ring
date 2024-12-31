package main

import {
	fmt;
	debug;
}

global {
	
}

@main
fn main() {
	var double local_double_value_1;
	
	fmt::println_string("test case 1");
	fmt::println_double(local_double_value_1);
	debug::assert(local_double_value_1 == 0.0);


	fmt::println_string("\ntest case 2");
	local_double_value_1 = 2.0;
	fmt::println_double(local_double_value_1);
	debug::assert(local_double_value_1 == 2.0);

	fmt::println_string("\ntest case 3");
	local_double_value_1 = 65536.65536;
	fmt::println_double(local_double_value_1);
	debug::assert(local_double_value_1 == 65536.65536);

	fmt::println_string("\ntest case 4");
	local_double_value_1 = -65536.65536;
	fmt::println_double(local_double_value_1);
	debug::assert(local_double_value_1 == -65536.65536);

}
