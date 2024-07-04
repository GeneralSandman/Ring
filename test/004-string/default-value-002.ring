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

	var string string_value_1 = "1";
	var string string_value_2, string_value_3 = "2", "3";
	var string string_value_4, string_value_5, string_value_6 = "4", "5", "6";

	fmt::println_string(string_value_1);
	fmt::println_string(string_value_2);
	fmt::println_string(string_value_3);
	fmt::println_string(string_value_4);
	fmt::println_string(string_value_5);
	fmt::println_string(string_value_6);
	debug::debug_assert(string_value_1 == "1");
	debug::debug_assert(string_value_2 == "2");
	debug::debug_assert(string_value_3 == "3");
	debug::debug_assert(string_value_4 == "4");
	debug::debug_assert(string_value_5 == "5");
	debug::debug_assert(string_value_6 == "6");

}
