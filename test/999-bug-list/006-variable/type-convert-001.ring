package main

import {
	fmt;
	debug;
}

fn main() {



var bool bool_value;
var int int_value;
var double double_value;
var string string_value;

bool_value = false;
string_value = <string>bool_value;
fmt::println_string(string_value);

bool_value = true;
string_value = <string>bool_value;
fmt::println_string(string_value);

debug::assert(1==1);
debug::assert(1!=1);

}