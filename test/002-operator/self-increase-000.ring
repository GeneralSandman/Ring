package main

import {
	fmt;
	debug;
}

@main
function main() {


var int int_value;

// -------
int_value = 1;
fmt::println_int(int_value);
debug::debug_assert(int_value == 1);

int_value++;
fmt::println_int(int_value);
debug::debug_assert(int_value == 2);

int_value++;
fmt::println_int(int_value);
debug::debug_assert(int_value == 3);

int_value++;
fmt::println_int(int_value);
debug::debug_assert(int_value == 4);

fmt::println_string("");


// -------
int_value = 1;
fmt::println_int(int_value);
debug::debug_assert(int_value == 1);

++int_value;
fmt::println_int(int_value);
debug::debug_assert(int_value == 2);

++int_value;
fmt::println_int(int_value);
debug::debug_assert(int_value == 3);

++int_value;
fmt::println_int(int_value);
debug::debug_assert(int_value == 4);

fmt::println_string("");


// -------
int_value = 10;
fmt::println_int(int_value);
debug::debug_assert(int_value == 10);

int_value--;
fmt::println_int(int_value);
debug::debug_assert(int_value == 9);

int_value--;
fmt::println_int(int_value);
debug::debug_assert(int_value == 8);

int_value--;
fmt::println_int(int_value);
debug::debug_assert(int_value == 7);

fmt::println_string("");

// -------
int_value = 10;
fmt::println_int(int_value);
debug::debug_assert(int_value == 10);

--int_value;
fmt::println_int(int_value);
debug::debug_assert(int_value == 9);

--int_value;
fmt::println_int(int_value);
debug::debug_assert(int_value == 8);

--int_value;
fmt::println_int(int_value);
debug::debug_assert(int_value == 7);

}