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

	var int int_value_1 = 1;
	var int int_value_2, int_value_3 = 2, 3;
	var int int_value_4, int_value_5, int_value_6 = 4, 5, 6;

	fmt::println_int(int_value_1);
	fmt::println_int(int_value_2);
	fmt::println_int(int_value_3);
	fmt::println_int(int_value_4);
	fmt::println_int(int_value_5);
	fmt::println_int(int_value_6);
	debug::assert(int_value_1 == 1);
	debug::assert(int_value_2 == 2);
	debug::assert(int_value_3 == 3);
	debug::assert(int_value_4 == 4);
	debug::assert(int_value_5 == 5);
	debug::assert(int_value_6 == 6);

}
