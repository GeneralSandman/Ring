
package main

import {
	fmt;
	debug;
}

@main
function main() {

	fmt::println_string("\ntest case 1");
	var bool bool_value_0;
	var int  int_value_0;
	var double double_value_0;


	fmt::println_bool(bool_value_0);
	fmt::println_int(int_value_0);
	fmt::println_double(double_value_0);

	debug::debug_assert(bool_value_0 == false);
	debug::debug_assert(int_value_0 == 0);
	debug::debug_assert(double_value_0 == 0.0);





	fmt::println_string("\ntest case 2");
	var bool bool_value_1     = true;
	var int  int_value_1      = 1;
	var double double_value_1 = 1.23;


	fmt::println_bool(bool_value_1);
	fmt::println_int(int_value_1);
	fmt::println_double(double_value_1);

	debug::debug_assert(bool_value_1 == true);
	debug::debug_assert(int_value_1 == 1);
	debug::debug_assert(double_value_1 == 1.23);




	fmt::println_string("\ntest case 3");
	var bool bool_value_2     = true and true;
	var int  int_value_2      = 2147483647;
	var double double_value_2 = 2147483647.123;


	fmt::println_bool(bool_value_2);
	fmt::println_int(int_value_2);
	fmt::println_double(double_value_2);

	debug::debug_assert(bool_value_2 == true);
	debug::debug_assert(int_value_2 == 2147483647);
	debug::debug_assert(double_value_2 == 2147483647.123);
}