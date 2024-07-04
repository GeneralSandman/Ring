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

	var string string_value_1;
	var string string_value_2, string_value_3;
	var string string_value_4, string_value_5, string_value_6;

	fmt::println_string(string_value_1);
	fmt::println_string(string_value_2);
	fmt::println_string(string_value_3);
	fmt::println_string(string_value_4);
	fmt::println_string(string_value_5);
	fmt::println_string(string_value_6);
	debug::debug_assert(string_value_1 == "");
	debug::debug_assert(string_value_2 == "");
	debug::debug_assert(string_value_3 == "");
	debug::debug_assert(string_value_4 == "");
	debug::debug_assert(string_value_5 == "");
	debug::debug_assert(string_value_6 == "");

}