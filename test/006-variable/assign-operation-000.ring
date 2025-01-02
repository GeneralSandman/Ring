package main

import {
	fmt;
	debug;
}

fn main() {

	var int int_value = 1;

	// assign
	int_value = 2;
	fmt::println_int(int_value);


	// add-assign
	fmt::println_string("\ntest add-assign operation");
	int_value += 1;
	fmt::println_int(int_value);

	int_value += 2;
	fmt::println_int(int_value);

	int_value += 10;
	fmt::println_int(int_value);

	int_value += 1+2+3+4+5+6+7;
	fmt::println_int(int_value);



	// sub-assign
	fmt::println_string("\ntest sub-assign operation");
	int_value -= 1;
	fmt::println_int(int_value);

	int_value -= 1;
	fmt::println_int(int_value);

	int_value -= 4;
	fmt::println_int(int_value);

	int_value -= 4 - 1 - 1 -1 + 3;
	fmt::println_int(int_value);



	fmt::println_string("\ntest mul-assign operation");
	int_value *= 100;
	fmt::println_int(int_value);

	int_value *= 2;
	fmt::println_int(int_value);

	int_value *= 30;
	fmt::println_int(int_value);

	int_value *= 1 + 1;
	fmt::println_int(int_value);



	fmt::println_string("\ntest div-assign operation");
	int_value /= 5;
	fmt::println_int(int_value);

	int_value /= 4;
	fmt::println_int(int_value);

	int_value /= 3;
	fmt::println_int(int_value);

	int_value /= 3 + 1 + 2;
	fmt::println_int(int_value);



	fmt::println_string("\ntest mod-assign operation");
	int_value %= 60 - 1;
	fmt::println_int(int_value);

	int_value %= 10;
	fmt::println_int(int_value);

	int_value %= 2 + 1;
	fmt::println_int(int_value);

	int_value %= 1;
	fmt::println_int(int_value);

}
