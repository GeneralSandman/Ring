package main

import {
	fmt;
	debug;
}

global {
	var double global_double_value_1;
}

@main
function main() {
	
	fmt::println_string("test case 1");
	fmt::println_double(global_double_value_1);
	debug::assert(global_double_value_1 == 0.0);


	fmt::println_string("\ntest case 2");
	global_double_value_1 = 2.0;
	fmt::println_double(global_double_value_1);
	debug::assert(global_double_value_1 == 2.0);

	fmt::println_string("\ntest case 3");
	global_double_value_1 = 65536.65536;
	fmt::println_double(global_double_value_1);
	debug::assert(global_double_value_1 == 65536.65536);

	fmt::println_string("\ntest case 4");
	global_double_value_1 = -65536.0;
	fmt::println_double(global_double_value_1);
	debug::assert(global_double_value_1 == -65536.0);

}