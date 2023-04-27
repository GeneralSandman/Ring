package main

import {
	fmt;
	debug;
}

global {
	var bool global_bool_value_1 = true;
	var int  global_int_value_1 = 1;
	var double global_double_value_1 = 1.1;
	var string global_string_value_1 = "4";
}

@main
function main() {

	fmt::println_string("test case 1");
	// FIXME: 均存在 bug
	fmt::println_bool(global_bool_value_1);
	fmt::println_int(global_int_value_1);
	fmt::println_double(global_double_value_1);
	fmt::println_string(global_string_value_1);

	fmt::println_string("\ntest case 2");
	global_bool_value_1 = true;
	global_int_value_1 = 22;
	global_double_value_1 = 33.0;
	global_string_value_1 = "44";

	fmt::println_bool(global_bool_value_1);
	fmt::println_int(global_int_value_1);
	fmt::println_double(global_double_value_1);
	fmt::println_string(global_string_value_1);
}