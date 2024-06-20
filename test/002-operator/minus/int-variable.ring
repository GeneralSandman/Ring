package main

import {
	fmt;
	debug;
}

@main
function main() {
	var int local_int_value_0;

	fmt::println("test 1 ----------");
	local_int_value_0 = 0;
	fmt::println_int(local_int_value_0);

	local_int_value_0 = 1;
	fmt::println_int(local_int_value_0);

	local_int_value_0 = 10;
	fmt::println_int(local_int_value_0);

	local_int_value_0 = 2147483647;
	fmt::println_int(local_int_value_0);

	local_int_value_0 = -0;
	fmt::println_int(local_int_value_0);

	local_int_value_0 = -1;
	fmt::println_int(local_int_value_0);

	local_int_value_0 = -10;
	fmt::println_int(local_int_value_0);

	local_int_value_0 = -2147483647;
	fmt::println_int(local_int_value_0);

	local_int_value_0 = -2147483648;
	fmt::println_int(local_int_value_0);
	fmt::println("test 1 ----------");



	fmt::println("test 2 ----------");
	local_int_value_0 = 0;
	fmt::println(local_int_value_0);

	local_int_value_0 = 1;
	fmt::println(local_int_value_0);

	local_int_value_0 = 10;
	fmt::println(local_int_value_0);

	local_int_value_0 = 2147483647;
	fmt::println(local_int_value_0);

	local_int_value_0 = -0;
	fmt::println(local_int_value_0);

	local_int_value_0 = -1;
	fmt::println(local_int_value_0);

	local_int_value_0 = -10;
	fmt::println(local_int_value_0);

	local_int_value_0 = -2147483647;
	fmt::println(local_int_value_0);
	
	local_int_value_0 = -2147483648;
	fmt::println(local_int_value_0);
	fmt::println("test 2 ----------");

}