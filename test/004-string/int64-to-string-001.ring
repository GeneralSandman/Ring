
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
	var int64    int64_value;
    var string   string_value;

    fmt::println_string("test cast 1 ------------------------");
	int64_value = 0L;
	fmt::println_int64(int64_value);
	string_value = to_string(int64_value);
	fmt::println_string(string_value);
	debug::assert(string_value == "0");

    fmt::println_string("\ntest cast 2 ------------------------");
	int64_value = 123L;
	fmt::println_int64(int64_value);
	string_value = to_string(int64_value);
	fmt::println_string(string_value);
	debug::assert(string_value == "123");

    fmt::println_string("\ntest cast 3 ------------------------");
	int64_value = 223L;
	fmt::println_int64(int64_value);
	string_value = to_string(int64_value);
	fmt::println_string(string_value);
	debug::assert(string_value == "223");

    fmt::println_string("\ntest cast 4 ------------------------");
	int64_value = 9870L;
	fmt::println_int64(int64_value);
	string_value = to_string(int64_value);
	fmt::println_string(string_value);
	debug::assert(string_value == "9870");

}