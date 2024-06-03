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
	var int64 int64_value;
	
	fmt::println_string("test case 1-----------");
	fmt::println_int64(int64_value);
	debug::debug_assert(int64_value == 0);

	fmt::println_string("\ntest case 2-----------");
	int64_value = 9223372036854775807;
	fmt::println_int64(int64_value);
	debug::debug_assert(int64_value == 9223372036854775807);

	fmt::println_string("\ntest case 3-----------");
	int64_value = -9223372036854775808;
	fmt::println_int64(int64_value);
	debug::debug_assert(int64_value == -9223372036854775808);



}