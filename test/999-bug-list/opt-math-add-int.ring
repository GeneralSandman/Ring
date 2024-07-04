//
// File:    string-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
	debug;
}

// minus 符号
@main
function main() {
	var int local_int_value_0;

	local_int_value_0 = -1 + -1;
	fmt::println(local_int_value_0);
	debug::debug_assert(local_int_value_0 == -2);

	local_int_value_0 = -1 - 1;
	fmt::println(local_int_value_0);
	debug::debug_assert(local_int_value_0 == -2);

	local_int_value_0 = -2 * -2;
	fmt::println(local_int_value_0);
	debug::debug_assert(local_int_value_0 == 4);

	local_int_value_0 = -2 / -2;
	fmt::println(local_int_value_0);
	debug::debug_assert(local_int_value_0 == 1);

	local_int_value_0 = -3 % -2;
	fmt::println(local_int_value_0);
	debug::debug_assert(local_int_value_0 == -1);

	local_int_value_0 = 1+2+3+4+5+6+7+8+9+10+4*5+25/5 + 10%3 -3;
	fmt::println(local_int_value_0);
	debug::debug_assert(local_int_value_0 == 78);

}