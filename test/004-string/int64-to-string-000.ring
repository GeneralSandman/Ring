
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
fn main() {
    var string string_value;

    fmt::println_string("test cast 1 ------------------------");
	fmt::println_int64(0L);
	string_value = to_string(0L);
	fmt::println_string(string_value);
	debug::assert(string_value == "0");

    fmt::println_string("\ntest cast 2 ------------------------");
	fmt::println_int64(123L);
	string_value = to_string(123L);
	fmt::println_string(string_value);
	debug::assert(string_value == "123");

    fmt::println_string("\ntest cast 3 ------------------------");
	fmt::println_int64(223L);
	string_value = to_string(223L);
	fmt::println_string(string_value);
	debug::assert(string_value == "223");

    fmt::println_string("\ntest cast 4 ------------------------");
	fmt::println_int64(9870L);
	string_value = to_string(9870L);
	fmt::println_string(string_value);
	debug::assert(string_value == "9870");

}