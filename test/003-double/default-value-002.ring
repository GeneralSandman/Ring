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

	var double double_value_1 = 1.1;
	var double double_value_2, double_value_3 = 2.2, 3.3;
	var double double_value_4, double_value_5, double_value_6 = 4.4, 5.5, 6.6;

	fmt::println_double(double_value_1);
	fmt::println_double(double_value_2);
	fmt::println_double(double_value_3);
	fmt::println_double(double_value_4);
	fmt::println_double(double_value_5);
	fmt::println_double(double_value_6);
	debug::assert(double_value_1 == 1.1);
	debug::assert(double_value_2 == 2.2);
	debug::assert(double_value_3 == 3.3);
	debug::assert(double_value_4 == 4.4);
	debug::assert(double_value_5 == 5.5);
	debug::assert(double_value_6 == 6.6);

}
