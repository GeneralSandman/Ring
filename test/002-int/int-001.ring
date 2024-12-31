//
// File:    int-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
	debug;
}

@main
fn main() {


	var int int_value;

	int_value = 0;
	fmt::println_int(int_value);
	debug::assert(int_value == 0);

	int_value = -0;
	fmt::println_int(int_value);
	debug::assert(int_value == 0);

	int_value = 0-0;
	fmt::println_int(int_value);
	debug::assert(int_value == 0);


	fmt::println_string("");


	int_value = 1;
	fmt::println_int(int_value);
	debug::assert(int_value == 1);

	int_value = -1;
	fmt::println_int(int_value);
	debug::assert(int_value == -1);

	int_value = 0-1;
	fmt::println_int(int_value);
	debug::assert(int_value == -1);


	fmt::println_string("");


	int_value = 2;
	fmt::println_int(int_value);
	debug::assert(int_value == 2);

	int_value = -2;
	fmt::println_int(int_value);
	debug::assert(int_value == -2);

	int_value = 0-2;
	fmt::println_int(int_value);
	debug::assert(int_value == -2);


	fmt::println_string("");


	int_value = 2147483647;
	fmt::println_int(int_value);
	debug::assert(int_value == 2147483647);

	int_value = -2147483647;
	fmt::println_int(int_value);
	debug::assert(int_value == -2147483647);

	int_value = 0-2147483647;
	fmt::println_int(int_value);
	debug::assert(int_value == -2147483647);


	fmt::println_string("");
	int_value = 2147483648;
	fmt::println_int(int_value);
	debug::assert(int_value == 2147483648);
	debug::assert(int_value == -2147483648);


	fmt::println_string("");
	int_value = -2147483648;
	fmt::println_int(int_value);
	debug::assert(int_value == 2147483648);
	debug::assert(int_value == -2147483648);


	fmt::println_string("");
	int_value = 0-2147483648;
	fmt::println_int(int_value);
	debug::assert(int_value == 2147483648);
	debug::assert(int_value == -2147483648);

}