
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
	fmt::println_double(0.0);
	string_value = to_string(0.0);
	fmt::println_string(string_value);
	debug::assert(string_value == "0.000000");


    fmt::println_string("\ntest cast 2 ------------------------");
	fmt::println_double(3.1415);
	string_value = to_string(3.1415);
	fmt::println_string(string_value);
	debug::assert(string_value == "3.141500");


    fmt::println_string("\ntest cast 3 ------------------------");
	fmt::println_double(66.66);
	string_value = to_string(66.66);
	fmt::println_string(string_value);
	debug::assert(string_value == "66.660000");


    fmt::println_string("\ntest cast 4 ------------------------");
	fmt::println_double(12345.678);
	string_value = to_string(12345.678);
	fmt::println_string(string_value);
	debug::assert(string_value == "12345.678000");

}