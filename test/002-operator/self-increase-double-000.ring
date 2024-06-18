package main

import {
	fmt;
	debug;
}

@main
function main() {


	var double local_double_value_0;

	// -------
	local_double_value_0 = 1.0;
	fmt::println_double(local_double_value_0);
	debug::debug_assert(local_double_value_0 == 1.0);

	local_double_value_0++;
	fmt::println_double(local_double_value_0);
	debug::debug_assert(local_double_value_0 == 2.0);

	local_double_value_0++;
	fmt::println_double(local_double_value_0);
	debug::debug_assert(local_double_value_0 == 3.0);

	local_double_value_0++;
	fmt::println_double(local_double_value_0);
	debug::debug_assert(local_double_value_0 == 4.0);

	fmt::println_string("");


	// -------
	local_double_value_0 = 10.0;
	fmt::println_double(local_double_value_0);
	debug::debug_assert(local_double_value_0 == 10.0);

	local_double_value_0--;
	fmt::println_double(local_double_value_0);
	debug::debug_assert(local_double_value_0 == 9.0);

	local_double_value_0--;
	fmt::println_double(local_double_value_0);
	debug::debug_assert(local_double_value_0 == 8.0);

	local_double_value_0--;
	fmt::println_double(local_double_value_0);
	debug::debug_assert(local_double_value_0 == 7.0);

	fmt::println_string("");



}