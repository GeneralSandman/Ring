package main

import {
	fmt;
	debug;
}

global {
	
}

@main
function main() {
	var string local_string_value_1;
	
	fmt::println_string("test case 1");
	fmt::println_string(local_string_value_1);
	debug::debug_assert(local_string_value_1 == ""); // 13547 segmentation fault


	fmt::println_string("\ntest case 2");
	local_string_value_1 = "4";
	fmt::println_string(local_string_value_1);
	debug::debug_assert(local_string_value_1 == "4");

	fmt::println_string("\ntest case 3");
	local_string_value_1 = "hello world";
	fmt::println_string(local_string_value_1);
	debug::debug_assert(local_string_value_1 == "hello world");

	fmt::println_string("\ntest case 4");
	local_string_value_1 = "this is ring";
	fmt::println_string(local_string_value_1);
	debug::debug_assert(local_string_value_1 == "this is ring");
}