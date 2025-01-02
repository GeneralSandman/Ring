
package main

import {
	fmt;
	debug;
}

fn main() {

	var int int_value_1;
	var int int_value_2;
	var int tmp;

	int_value_1 = 1;
	int_value_2 = 2;
	debug::assert(int_value_1 == 1);
	debug::assert(int_value_2 == 2);
	fmt::println_int(int_value_1);
	fmt::println_int(int_value_2);


	fmt::println_string("\ntest case 1");
	tmp = int_value_1;
	int_value_1 = int_value_2;
	int_value_2 = tmp;
	debug::assert(int_value_1 == 2);
	debug::assert(int_value_2 == 1);
	fmt::println_int(int_value_1);
	fmt::println_int(int_value_2);



	fmt::println_string("\ntest case 2");
	int_value_1 = 4;
	int_value_2 = 5;

	int_value_1, int_value_2 = int_value_2, int_value_1;
	debug::assert(int_value_1 == 5);
	debug::assert(int_value_2 == 4);
	fmt::println_int(int_value_1);
	fmt::println_int(int_value_2);


}