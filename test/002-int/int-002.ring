//
// File:    int-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
	debug;
}

@main
function main() {


	var int int_value;

	int_value = 0;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 0);

	int_value = 123456;
	fmt::println_int(int_value);
	debug::debug_assert(int_value != 123457);
	debug::debug_assert(int_value == 123456);


	fmt::println_string("");


	int_value = 123456+234234;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 357690);


	int_value = 123456-234234;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == -110778);


	int_value = 2342*2342;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 5484964);


	int_value = 2342/2342;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 1);


	fmt::println_string("");


	int_value = 234+2342*100;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 234434);


	int_value = 234+2342/100;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 257);


	int_value = 234+2342/100-100/1;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 157);


	int_value = 123456+123456*10-100*10+10010;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 1367026);


	fmt::println_string("");


	int_value = 1367026;

	int_value = int_value + 10;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 1367036);

	int_value = int_value - 10;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 1367026);


	int_value = int_value * 10;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 13670260);

	int_value = int_value / 10;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 1367026);

	int_value = int_value % 10;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 6);

	/*



	print(true);
	print("\n");

	print(false);
	print("\n");

	var bool result;
	result = true;
	print(result);
	print("\n");

	result = false;
	print(result);
	print("\n");

	result = true;
	print(result);
	print("\n");

	print("1234+234=", 1234+234, "\n");

	print(int_value, " ", result, " ", "string", "\n");

	*/

}