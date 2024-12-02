
package main

import {
	fmt;
	debug;
}

@main
function main() {

	var int int_value;

	// -----------
	fmt::println_string("[Test Case 1]");

	for(int_value = 0; int_value < 10; int_value++) {
	    fmt::println_int(int_value);
	}

	debug::assert(int_value == 10);
	fmt::println_int(int_value);

	fmt::println_string("");


	// -----------
	fmt::println_string("[Test Case 2]");
	do(int_value = 0) {
	    fmt::println_int(int_value);
	}for(int_value<10; int_value++);

	debug::assert(int_value == 10);
	fmt::println_int(int_value);

}
