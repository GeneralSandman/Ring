
package main

import {
	fmt;
	debug;
}

@main
function main() {

	var bool bool_value;
	var int int_value;
	var double double_value;
	var string string_value;

	bool_value = true;
	fmt::println_bool(true);
	fmt::println_bool(bool_value);

	int_value = 1;
	fmt::println_int(1);
	fmt::println_int(int_value);

	double_value = 1.1;
	fmt::println_double(1.1);
	fmt::println_double(double_value);

	string_value = "hello world";
	fmt::println_string("hello world");
	fmt::println_string(string_value);


	debug::debug_assert(true == true);
	debug::debug_assert(true != false);

	debug::debug_assert(1 == 1);
	debug::debug_assert(1 != 2);

	debug::debug_assert(1.1 == 1.1);
	debug::debug_assert(1.1 != 1.2);

	debug::debug_assert("hello world" == "hello world");
	debug::debug_assert("hello world" != "hello world!");


	// exit(0);


	// fmt::println_string("cant't execute this code");


}