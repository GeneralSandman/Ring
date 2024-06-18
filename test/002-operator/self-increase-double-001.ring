package main

import {
	fmt;
	debug;
}

global {
	var double global_double_value_0;

}

@main
function main() {



	// -------
	global_double_value_0 = 1.0;
	fmt::println_double(global_double_value_0);
	debug::debug_assert(global_double_value_0 == 1.0);

	global_double_value_0++;
	fmt::println_double(global_double_value_0);
	debug::debug_assert(global_double_value_0 == 2.0);

	global_double_value_0++;
	fmt::println_double(global_double_value_0);
	debug::debug_assert(global_double_value_0 == 3.0);

	global_double_value_0++;
	fmt::println_double(global_double_value_0);
	debug::debug_assert(global_double_value_0 == 4.0);

	fmt::println_string("");


	// -------
	global_double_value_0 = 10.0;
	fmt::println_double(global_double_value_0);
	debug::debug_assert(global_double_value_0 == 10.0);

	global_double_value_0--;
	fmt::println_double(global_double_value_0);
	debug::debug_assert(global_double_value_0 == 9.0);

	global_double_value_0--;
	fmt::println_double(global_double_value_0);
	debug::debug_assert(global_double_value_0 == 8.0);

	global_double_value_0--;
	fmt::println_double(global_double_value_0);
	debug::debug_assert(global_double_value_0 == 7.0);

	fmt::println_string("");



}