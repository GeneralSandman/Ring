//
// File:    var-default-value-002.ring
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

	var bool bool_value_1 = true;
	var bool bool_value_2, bool_value_3 = true, true;
	var bool bool_value_4, bool_value_5, bool_value_6 = true, true, true;

	fmt::println_bool(bool_value_1);
	fmt::println_bool(bool_value_2);
	fmt::println_bool(bool_value_3);
	fmt::println_bool(bool_value_4);
	fmt::println_bool(bool_value_5);
	fmt::println_bool(bool_value_6);
	debug::debug_assert(bool_value_1 == true);
	debug::debug_assert(bool_value_2 == true);
	debug::debug_assert(bool_value_3 == true);
	debug::debug_assert(bool_value_4 == true);
	debug::debug_assert(bool_value_5 == true);
	debug::debug_assert(bool_value_6 == true);

}
