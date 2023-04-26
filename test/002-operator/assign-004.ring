
package main

import {
	fmt;
	debug;
}

@main
function main() {

	var bool bool_value_1 = true;
	var bool bool_value_2, bool_value_3 = true, true;
	var bool bool_value_4, bool_value_5, bool_value_6 = true, true, true;

	fmt::println_string("\ntest case BOOL");
	fmt::println_bool(bool_value_1);
	fmt::println_bool(bool_value_2);
	fmt::println_bool(bool_value_3);
	fmt::println_bool(bool_value_4);
	fmt::println_bool(bool_value_5);
	fmt::println_bool(bool_value_6);
	debug::debug_assert(bool_value_1 == true);
	debug::debug_assert(bool_value_2 == true);
	debug::debug_assert(bool_value_3 == true);
	debug::debug_assert(bool_value_4 == true);
	debug::debug_assert(bool_value_5 == true);
	debug::debug_assert(bool_value_6 == true);






	var int int_value_1 = 1;
	var int int_value_2, int_value_3 = 2, 3;
	var int int_value_4, int_value_5, int_value_6 = 4, 5, 6;

	fmt::println_string("\ntest case INT");
	fmt::println_int(int_value_1);
	fmt::println_int(int_value_2);
	fmt::println_int(int_value_3);
	fmt::println_int(int_value_4);
	fmt::println_int(int_value_5);
	fmt::println_int(int_value_6);
	debug::debug_assert(int_value_1 == 1);
	debug::debug_assert(int_value_2 == 2);
	debug::debug_assert(int_value_3 == 3);
	debug::debug_assert(int_value_4 == 4);
	debug::debug_assert(int_value_5 == 5);
	debug::debug_assert(int_value_6 == 6);






	var double double_value_1 = 1.1;
	var double double_value_2, double_value_3 = 2.2, 3.3;
	var double double_value_4, double_value_5, double_value_6 = 4.4, 5.5, 6.6;

	fmt::println_string("\ntest case DOUBLE");
	fmt::println_double(double_value_1);
	fmt::println_double(double_value_2);
	fmt::println_double(double_value_3);
	fmt::println_double(double_value_4);
	fmt::println_double(double_value_5);
	fmt::println_double(double_value_6);
	debug::debug_assert(double_value_1 == 1.1);
	debug::debug_assert(double_value_2 == 2.2);
	debug::debug_assert(double_value_3 == 3.3);
	debug::debug_assert(double_value_4 == 4.4);
	debug::debug_assert(double_value_5 == 5.5);
	debug::debug_assert(double_value_6 == 6.6);



}