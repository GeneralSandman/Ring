
package main

import {
	fmt;
	debug;
}



fn increase_one(var int int_1) -> (int) {
    return int_1 + 1;
}

fn add_two(var int int_1, var int int_2) -> (int) {
    return int_1 + int_2;
}




@main
fn main() {

	var int int_value_1;


	fmt::println_string("\ntest case 1");
	int_value_1 = 5;
	debug::assert(int_value_1 == 5);

	int_value_1 = increase_one(4);
	debug::assert(int_value_1 == 5);

	int_value_1 = add_two(2, 3);
	debug::assert(int_value_1 == 5);


	int_value_1 = 5;
	int_value_1 += int_value_1;
	debug::assert(int_value_1 == 10);





	fmt::println_string("\ntest case 2");

	int_value_1 = 5;
	int_value_1 += increase_one(4);
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == 10);

	int_value_1 += increase_one(4);
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == 15);




	fmt::println_string("\ntest case 3");

	int_value_1 = 5;
	int_value_1 += add_two(13, 12);
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == 30);

	int_value_1 += add_two(13, 12);
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == 55);



}