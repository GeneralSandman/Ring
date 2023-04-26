//
// File:    var-default-value-001.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-31
//

package main

import {
	fmt;
	debug;
}

@main
function main() {

	var bool bool_value_1;
	var bool bool_value_2, bool_value_3;
	var bool bool_value_4, bool_value_5, bool_value_6;

	fmt::println_string("\ntest case BOOL");
	fmt::println_bool(bool_value_1);
	fmt::println_bool(bool_value_2);
	fmt::println_bool(bool_value_3);
	fmt::println_bool(bool_value_4);
	fmt::println_bool(bool_value_5);
	fmt::println_bool(bool_value_6);
	debug::debug_assert(bool_value_1 == false);
	debug::debug_assert(bool_value_2 == false);
	debug::debug_assert(bool_value_3 == false);
	debug::debug_assert(bool_value_4 == false);
	debug::debug_assert(bool_value_5 == false);
	debug::debug_assert(bool_value_6 == false);








	var int int_value_1;
	var int int_value_2, int_value_3;
	var int int_value_4, int_value_5, int_value_6;

	fmt::println_string("\ntest case INT");
	fmt::println_int(int_value_1);
	fmt::println_int(int_value_2);
	fmt::println_int(int_value_3);
	fmt::println_int(int_value_4);
	fmt::println_int(int_value_5);
	fmt::println_int(int_value_6);
	debug::debug_assert(int_value_1 == 0);
	debug::debug_assert(int_value_2 == 0);
	debug::debug_assert(int_value_3 == 0);
	debug::debug_assert(int_value_4 == 0);
	debug::debug_assert(int_value_5 == 0);
	debug::debug_assert(int_value_6 == 0);






	var double double_value_1;
	var double double_value_2, double_value_3;
	var double double_value_4, double_value_5, double_value_6;

	fmt::println_string("\ntest case DOUBLE");
	fmt::println_double(double_value_1);
	fmt::println_double(double_value_2);
	fmt::println_double(double_value_3);
	fmt::println_double(double_value_4);
	fmt::println_double(double_value_5);
	fmt::println_double(double_value_6);
	debug::debug_assert(double_value_1 == 0.0);
	debug::debug_assert(double_value_2 == 0.0);
	debug::debug_assert(double_value_3 == 0.0);
	debug::debug_assert(double_value_4 == 0.0);
	debug::debug_assert(double_value_5 == 0.0);
	debug::debug_assert(double_value_6 == 0.0);



}