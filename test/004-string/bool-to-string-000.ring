
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

fn main() {
    var string string_value;

    fmt::println_string("test cast 1 ------------------------");
	fmt::println_bool(false);
	string_value = to_string(false);
	fmt::println_string(string_value);
	debug::assert(string_value == "false");

    fmt::println_string("\ntest cast 2 ------------------------");
	fmt::println_bool(true);
	string_value = to_string(true);
	fmt::println_string(string_value);
	debug::assert(string_value == "true");

    fmt::println_string("\ntest cast 3 ------------------------");
	fmt::println_bool(false);
	string_value = to_string(false);
	fmt::println_string(string_value);
	debug::assert(string_value == "false");

    fmt::println_string("\ntest cast 4 ------------------------");
	fmt::println_bool(true);
	string_value = to_string(true);
	fmt::println_string(string_value);
	debug::assert(string_value == "true");

}