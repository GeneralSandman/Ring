//
// File:    string-001.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
	debug;
}

@main
function main() {


fmt::println_string("123" .. "345");
fmt::println_string("123" .. "345" .. "567");
fmt::println_string("123" .. "345" .. "567" .. "789");

fmt::println_string("");
fmt::println_string("-----------");

var string string_value;


fmt::println_string("\ntest case 1");
string_value = "123-";
fmt::println_string(string_value);
debug::debug_assert(string_value == "123-");



fmt::println_string("\ntest case 2");
string_value = "123" .. "345";
fmt::println_string(string_value);
debug::debug_assert(string_value == "123345");


fmt::println_string("\ntest case 3");
string_value = "123" .. "345" .. "567";
fmt::println_string(string_value);
debug::debug_assert(string_value == "123345567");


fmt::println_string("\ntest case 4");
string_value = "123" .. "345" .. "567" .. "789";
fmt::println_string(string_value);
debug::debug_assert(string_value == "123345567789");

}