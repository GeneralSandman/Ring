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

	var int64 int64_value_1;
	var int64 int64_value_2, int64_value_3;
	var int64 int64_value_4, int64_value_5, int64_value_6;

	fmt::println_int64(int64_value_1);
	fmt::println_int64(int64_value_2);
	fmt::println_int64(int64_value_3);
	fmt::println_int64(int64_value_4);
	fmt::println_int64(int64_value_5);
	fmt::println_int64(int64_value_6);
	debug::debug_assert(int64_value_1 == 0L);
	debug::debug_assert(int64_value_2 == 0L);
	debug::debug_assert(int64_value_3 == 0L);
	debug::debug_assert(int64_value_4 == 0L);
	debug::debug_assert(int64_value_5 == 0L);
	debug::debug_assert(int64_value_6 == 0L);

}