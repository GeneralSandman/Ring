//
// File:    int-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
	debug;
}

@main
function main() {
	var bool bool_value;
	fmt::println_bool(bool_value);
	debug::debug_assert(bool_value == false);


	var int int_value;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 0);


	var double double_value;
	fmt::println_double(double_value);
	debug::debug_assert(double_value == 0.0);
}