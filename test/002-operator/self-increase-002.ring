package main

import {
	fmt;
	debug;
}

@main
function main() {

var int int_value;
var int result;


int_value = 1;
result = 1;

debug::debug_assert(int_value == 1);
debug::debug_assert(result == 1);
fmt::println_string("");


int_value = 1;
result = 1;

result = int_value-1;
debug::debug_assert(int_value == 1);
debug::debug_assert(result == 0);
fmt::println_string("");


int_value = 1;
result = 1;

result = int_value--;
debug::debug_assert(int_value == 0);
debug::debug_assert(result == 1);
fmt::println_string("");


int_value = 1;
result = 1;

result = --int_value;
debug::debug_assert(int_value == 0);
debug::debug_assert(result == 0);
fmt::println_string("");


// ------------


int_value = 10;
result = 10;

result = int_value-1;
debug::debug_assert(int_value == 10);
debug::debug_assert(result == 9);
fmt::println_string("");



int_value = 10;
result = 10;

result = int_value++;
debug::debug_assert(int_value == 11);
debug::debug_assert(result == 10);
fmt::println_string("");


int_value = 10;
result = 10;

result = ++int_value;
debug::debug_assert(int_value == 11);
debug::debug_assert(result == 11);
fmt::println_string("");

}