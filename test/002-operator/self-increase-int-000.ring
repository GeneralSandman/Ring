package main

import {
	fmt;
	debug;
}

@main
function main() {


	var int local_int_value_0;

	// -------
	local_int_value_0 = 1;
	fmt::println_int(local_int_value_0);
	debug::debug_assert(local_int_value_0 == 1);

	local_int_value_0++;
	fmt::println_int(local_int_value_0);
	debug::debug_assert(local_int_value_0 == 2);

	local_int_value_0++;
	fmt::println_int(local_int_value_0);
	debug::debug_assert(local_int_value_0 == 3);

	local_int_value_0++;
	fmt::println_int(local_int_value_0);
	debug::debug_assert(local_int_value_0 == 4);

	fmt::println_string("");


	// -------
	local_int_value_0 = 10;
	fmt::println_int(local_int_value_0);
	debug::debug_assert(local_int_value_0 == 10);

	local_int_value_0--;
	fmt::println_int(local_int_value_0);
	debug::debug_assert(local_int_value_0 == 9);

	local_int_value_0--;
	fmt::println_int(local_int_value_0);
	debug::debug_assert(local_int_value_0 == 8);

	local_int_value_0--;
	fmt::println_int(local_int_value_0);
	debug::debug_assert(local_int_value_0 == 7);

	fmt::println_string("");



}