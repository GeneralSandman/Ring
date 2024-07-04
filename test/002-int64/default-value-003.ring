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
function main() {

	var int64 int64_value_1 = 1L;
	var int64 int64_value_2 = 0;

	fmt::println_int64(int64_value_1);
	fmt::println_int64(int64_value_2);
	debug::debug_assert(int64_value_1 == 1L);
	debug::debug_assert(int64_value_2 == 2L);

}
