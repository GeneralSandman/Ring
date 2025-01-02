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

	var double double_value_1;
	var double double_value_2, double_value_3;
	var double double_value_4, double_value_5, double_value_6;

	fmt::println_double(double_value_1);
	fmt::println_double(double_value_2);
	fmt::println_double(double_value_3);
	fmt::println_double(double_value_4);
	fmt::println_double(double_value_5);
	fmt::println_double(double_value_6);
	debug::assert(double_value_1 == 0.0);
	debug::assert(double_value_2 == 0.0);
	debug::assert(double_value_3 == 0.0);
	debug::assert(double_value_4 == 0.0);
	debug::assert(double_value_5 == 0.0);
	debug::assert(double_value_6 == 0.0);

}