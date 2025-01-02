//
// File:    var-default-value-001.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-05-31
//

package main

import {
	fmt;
	debug;
}

fn main() {

	var int int_value_1;
	var int int_value_2, int_value_3;
	var int int_value_4, int_value_5, int_value_6;

	fmt::println_int(int_value_1);
	fmt::println_int(int_value_2);
	fmt::println_int(int_value_3);
	fmt::println_int(int_value_4);
	fmt::println_int(int_value_5);
	fmt::println_int(int_value_6);
	debug::assert(int_value_1 == 0);
	debug::assert(int_value_2 == 0);
	debug::assert(int_value_3 == 0);
	debug::assert(int_value_4 == 0);
	debug::assert(int_value_5 == 0);
	debug::assert(int_value_6 == 0);

}