
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
	var double double_value;
    var string string_value;

    fmt::println_string("test cast 1 ------------------------");
	double_value = 0.0;
	fmt::println_double(double_value);
	string_value = to_string(double_value);
	fmt::println_string(string_value);
	debug::debug_assert(string_value == "0.000000");


    fmt::println_string("\ntest cast 2 ------------------------");
	double_value = 3.1415;
	fmt::println_double(double_value);
	string_value = to_string(double_value);
	fmt::println_string(string_value);
	debug::debug_assert(string_value == "3.141500");


    fmt::println_string("\ntest cast 3 ------------------------");
	double_value = 66.66;
	fmt::println_double(double_value);
	string_value = to_string(double_value);
	fmt::println_string(string_value);
	debug::debug_assert(string_value == "66.660000");


    fmt::println_string("\ntest cast 4 ------------------------");
	double_value = 12345.678;
	fmt::println_double(double_value);
	string_value = to_string(double_value);
	fmt::println_string(string_value);
	debug::debug_assert(string_value == "12345.678000");

}