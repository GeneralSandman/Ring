
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
	var int    int_value;
    var string string_value;

    fmt::println_string("test cast 1 ------------------------");
	int_value = 0;
	fmt::println_int(int_value);
	string_value = to_string(int_value);
	fmt::println_string(string_value);
	debug::assert(string_value == "0");

    fmt::println_string("\ntest cast 2 ------------------------");
	int_value = 123;
	fmt::println_int(int_value);
	string_value = to_string(int_value);
	fmt::println_string(string_value);
	debug::assert(string_value == "123");

    fmt::println_string("\ntest cast 3 ------------------------");
	int_value = 223;
	fmt::println_int(int_value);
	string_value = to_string(int_value);
	fmt::println_string(string_value);
	debug::assert(string_value == "223");

    fmt::println_string("\ntest cast 4 ------------------------");
	int_value = 9870;
	fmt::println_int(int_value);
	string_value = to_string(int_value);
	fmt::println_string(string_value);
	debug::assert(string_value == "9870");

}