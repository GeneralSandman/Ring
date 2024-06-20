package main

import {
	fmt;
	debug;
}

@main
function main() {
	var int64 local_int64_value_0;

	fmt::println("test 1 ----------");
	local_int64_value_0 = 0L;
	fmt::println_int64(local_int64_value_0);

	local_int64_value_0 = 1L;
	fmt::println_int64(local_int64_value_0);

	local_int64_value_0 = 10L;
	fmt::println_int64(local_int64_value_0);

	local_int64_value_0 = 2147483647L;
	fmt::println_int64(local_int64_value_0);

	local_int64_value_0 = 9223372036854775807L;
	fmt::println_int64(local_int64_value_0);

	local_int64_value_0 = -0L;
	fmt::println_int64(local_int64_value_0);

	local_int64_value_0 = -1L;
	fmt::println_int64(local_int64_value_0);

	local_int64_value_0 = -10L;
	fmt::println_int64(local_int64_value_0);

	local_int64_value_0 = -2147483647L;
	fmt::println_int64(local_int64_value_0);

	local_int64_value_0 = -9223372036854775807L;
	fmt::println_int64(local_int64_value_0);

	local_int64_value_0 = -9223372036854775808L;
	fmt::println_int64(local_int64_value_0);
	fmt::println("test 1 ----------");



	
	fmt::println("test 2 ----------");
	local_int64_value_0 = 0L;
	fmt::println(local_int64_value_0);

	local_int64_value_0 = 1L;
	fmt::println(local_int64_value_0);

	local_int64_value_0 = 10L;
	fmt::println(local_int64_value_0);

	local_int64_value_0 = 2147483647L;
	fmt::println(local_int64_value_0);

	local_int64_value_0 = 9223372036854775807L;
	fmt::println(local_int64_value_0);

	local_int64_value_0 = -0L;
	fmt::println(local_int64_value_0);

	local_int64_value_0 = -1L;
	fmt::println(local_int64_value_0);

	local_int64_value_0 = -10L;
	fmt::println(local_int64_value_0);

	local_int64_value_0 = -2147483647L;
	fmt::println(local_int64_value_0);

	local_int64_value_0 = -9223372036854775807L;
	fmt::println(local_int64_value_0);
	
	local_int64_value_0 = -9223372036854775808L;
	fmt::println(local_int64_value_0);
	fmt::println("test 2 ----------");

}