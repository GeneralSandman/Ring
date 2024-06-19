package main

import {
	fmt;
	debug;
}

@main
function main() {

	fmt::println("test 1 ----------");
	fmt::println_int(0);
	fmt::println_int(1);
	fmt::println_int(10);
	fmt::println_int(2147483647);
	fmt::println_int(-0);
	fmt::println_int(-1);
	fmt::println_int(-10);
	fmt::println_int(-2147483647);
	fmt::println_int(-2147483648);
	fmt::println("test 1 ----------");

	fmt::println("test 2 ----------");
	fmt::println(0);
	fmt::println(1);
	fmt::println(10);
	fmt::println(2147483647);
	fmt::println(-0);
	fmt::println(-1);
	fmt::println(-10);
	fmt::println(-2147483647);
	fmt::println(-2147483648);
	fmt::println("test 2 ----------");

}