
//
// File:    string-003.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-10-20
//

package main

import {
	fmt;
	debug;
    vm;
}

@main
function main() {
	var bool   bool_value;
    var string string_value;

    fmt::println_string("test cast 1 ------------------------");
	bool_value = false;
	fmt::println_bool(bool_value);
	string_value = to_string(bool_value);
	fmt::println_string(string_value);
	debug::debug_assert(string_value == "false");

    fmt::println_string("\ntest cast 2 ------------------------");
	bool_value = true;
	fmt::println_bool(bool_value);
	string_value = to_string(bool_value);
	fmt::println_string(string_value);
	debug::debug_assert(string_value == "true");

    fmt::println_string("\ntest cast 3 ------------------------");
	bool_value = false;
	fmt::println_bool(bool_value);
	string_value = to_string(bool_value);
	fmt::println_string(string_value);
	debug::debug_assert(string_value == "false");

    fmt::println_string("\ntest cast 4 ------------------------");
	bool_value = true;
	fmt::println_bool(bool_value);
	string_value = to_string(bool_value);
	fmt::println_string(string_value);
	debug::debug_assert(string_value == "true");

}