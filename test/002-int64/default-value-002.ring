//
// File:    var-default-value-002.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-05-31
//

package main

import {
	fmt;
	debug;
}

@main
fn main() {

	var int64 int64_value_1 = 1L;
	var int64 int64_value_2, int64_value_3 = 2L, 3L;
	var int64 int64_value_4, int64_value_5, int64_value_6 = 4L, 5L, 6L;

	fmt::println_int64(int64_value_1);
	fmt::println_int64(int64_value_2);
	fmt::println_int64(int64_value_3);
	fmt::println_int64(int64_value_4);
	fmt::println_int64(int64_value_5);
	fmt::println_int64(int64_value_6);
	debug::assert(int64_value_1 == 1L);
	debug::assert(int64_value_2 == 2L);
	debug::assert(int64_value_3 == 3L);
	debug::assert(int64_value_4 == 4L);
	debug::assert(int64_value_5 == 5L);
	debug::assert(int64_value_6 == 6L);

}
