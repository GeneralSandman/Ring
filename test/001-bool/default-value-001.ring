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

@main
function main() {

	var bool bool_value_1;
	var bool bool_value_2, bool_value_3;
	var bool bool_value_4, bool_value_5, bool_value_6;

	fmt::println_bool(bool_value_1);
	fmt::println_bool(bool_value_2);
	fmt::println_bool(bool_value_3);
	fmt::println_bool(bool_value_4);
	fmt::println_bool(bool_value_5);
	fmt::println_bool(bool_value_6);
	debug::debug_assert(bool_value_1 == false);
	debug::debug_assert(bool_value_2 == false);
	debug::debug_assert(bool_value_3 == false);
	debug::debug_assert(bool_value_4 == false);
	debug::debug_assert(bool_value_5 == false);
	debug::debug_assert(bool_value_6 == false);

}