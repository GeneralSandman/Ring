
package main

import {
	fmt;
	debug;
}

@main
fn main() {

	var double double_value;


	// double_value = 1.1;
	// fmt::println_double(double_value);
	// debug::assert(double_value == 1.1);

	fmt::println_string("\ntest case");
	double_value = 1.1 + 2.2 + 3.3;
	fmt::println_double(double_value);
	debug::assert(double_value == 6.6);


	fmt::println_string("\ntest case");
	double_value = double_value + 1.1;
	fmt::println_double(double_value);
	debug::assert(7.700000 == double_value); // FIXME: bug

	fmt::println_string("\ntest case");
	double_value += 1.1;
	fmt::println_double(double_value);
	debug::assert(double_value == 8.8); // FIXME: bug


	fmt::println_string("\ntest case");
	double_value += 1.1 + 2.2;
	fmt::println_double(double_value);
	debug::assert(double_value == 12.1); 

}