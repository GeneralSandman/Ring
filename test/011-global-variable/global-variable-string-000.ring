package main

import {
	fmt;
	debug;
}

global {
	var string global_string_value_1;
	
}

@main
function main() {
	
	fmt::println_string("test case 1");
	fmt::println_string(global_string_value_1);
	debug::debug_assert(global_string_value_1 == ""); // 13547 segmentation fault


	fmt::println_string("\ntest case 2");
	global_string_value_1 = "4";
	fmt::println_string(global_string_value_1);
	debug::debug_assert(global_string_value_1 == "4");

	fmt::println_string("\ntest case 3");
	global_string_value_1 = "hello world";
	fmt::println_string(global_string_value_1);
	debug::debug_assert(global_string_value_1 == "hello world");

	fmt::println_string("\ntest case 4");
	global_string_value_1 = "this is ring";
	fmt::println_string(global_string_value_1);
	debug::debug_assert(global_string_value_1 == "this is ring");

	fmt::println_string("\ntest case 5");
	global_string_value_1 = "";
	fmt::println_string(global_string_value_1);
	debug::debug_assert(global_string_value_1 == "");
}
