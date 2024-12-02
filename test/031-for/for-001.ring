
package main

import {
	fmt;
	debug;
}

@main
function main() {

	var int int_value;
	
	int_value = -1;
	
	debug::assert(int_value == -1);
	fmt::println_int(int_value);
	fmt::println_string("");
	
	for(; int_value < 10; int_value = int_value + 1) {
		fmt::println_int(int_value);
	}
	
	fmt::println_string("");
	debug::assert(int_value == 10);
	fmt::println_int(int_value);

}
