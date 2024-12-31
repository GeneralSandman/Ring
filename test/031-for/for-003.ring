
package main

import {
	fmt;
	debug;
}

@main
fn main() {

	var int int_value;
	
	int_value = -1;
	
	debug::assert(int_value == -1);
	fmt::println_int(int_value);
	fmt::println_string("");
	
	for(int_value = 0;int_value < 20; int_value=int_value+1) {
		fmt::println_int(int_value);
		if(int_value > 10) {
			debug::assert(int_value > 10);
			fmt::println_string("int_value > 10");
			fmt::println_int(int_value);
			fmt::println_string("");
		}
	}
	
	fmt::println_string("");
	debug::assert(int_value == 20);
	fmt::println_int(int_value);

}
