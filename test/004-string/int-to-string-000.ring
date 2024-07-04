
//
// File:    string-003.ring
// Author:  GeneralSandman - generalsandman@163.com
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
    var string string_value;

    fmt::println_string("test cast 1 ------------------------");
	fmt::println_int(0);
	string_value = to_string(0);
	fmt::println_string(string_value);
	debug::debug_assert(string_value == "0");

    fmt::println_string("\ntest cast 2 ------------------------");
	fmt::println_int(123);
	string_value = to_string(123);
	fmt::println_string(string_value);
	debug::debug_assert(string_value == "123");

    fmt::println_string("\ntest cast 3 ------------------------");
	fmt::println_int(223);
	string_value = to_string(223);
	fmt::println_string(string_value);
	debug::debug_assert(string_value == "223");

    fmt::println_string("\ntest cast 4 ------------------------");
	fmt::println_int(9870);
	string_value = to_string(9870);
	fmt::println_string(string_value);
	debug::debug_assert(string_value == "9870");

}