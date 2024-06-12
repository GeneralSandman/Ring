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

	int_value = -0;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 0);

	int_value = 0-0;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 0);


	fmt::println_string("");


	int_value = 1;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 1);

	int_value = -1;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == -1);

	int_value = 0-1;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == -1);


	fmt::println_string("");


	int_value = 2;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 2);

	int_value = -2;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == -2);

	int_value = 0-2;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == -2);


	fmt::println_string("");


	int_value = 2147483647;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 2147483647);

	int_value = -2147483647;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == -2147483647);

	int_value = 0-2147483647;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == -2147483647);


	fmt::println_string("");


	// TODO: 2147483648 在编译器认为是个 int64, 直接赋值给 int32 编译器会报错
	// int_value = 2147483648;
	// fmt::println_int(int_value);
	// debug::debug_assert(int_value == 2147483648);

	// TODO: 2147483648 在编译器认为是个 int64, 直接赋值给 int32 编译器会报错
	// int_value = -2147483648;
	// fmt::println_int(int_value);
	// debug::debug_assert(int_value == -2147483648);

	// TODO: 2147483648 在编译器认为是个 int64, 0 认为是 int32 , 编译器报错
	// int_value = 0-2147483648;
	// fmt::println_int(int_value);
	// debug::debug_assert(int_value == -2147483648);

}