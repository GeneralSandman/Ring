package main

import {
	fmt;
	debug;
}

global {
	var int global_int_value_0;

}

@main
function main() {



	// -------
	global_int_value_0 = 1;
	fmt::println_int(global_int_value_0);
	debug::debug_assert(global_int_value_0 == 1);

	global_int_value_0++;
	fmt::println_int(global_int_value_0);
	debug::debug_assert(global_int_value_0 == 2);

	global_int_value_0++;
	fmt::println_int(global_int_value_0);
	debug::debug_assert(global_int_value_0 == 3);

	global_int_value_0++;
	fmt::println_int(global_int_value_0);
	debug::debug_assert(global_int_value_0 == 4);

	fmt::println_string("");


	// -------
	global_int_value_0 = 10;
	fmt::println_int(global_int_value_0);
	debug::debug_assert(global_int_value_0 == 10);

	global_int_value_0--;
	fmt::println_int(global_int_value_0);
	debug::debug_assert(global_int_value_0 == 9);

	global_int_value_0--;
	fmt::println_int(global_int_value_0);
	debug::debug_assert(global_int_value_0 == 8);

	global_int_value_0--;
	fmt::println_int(global_int_value_0);
	debug::debug_assert(global_int_value_0 == 7);

	fmt::println_string("");



}