package main

import {
	fmt;
	debug;
}

@main
fn main() {

	fmt::println("test 1 ----------");
	fmt::println_double(0.0);
	fmt::println_double(1.0);
	fmt::println_double(10.0);
	fmt::println_double(2147483647.0);
	fmt::println_double(9223372036854775807.0);	
	fmt::println_double(-0.0);
	fmt::println_double(-1.0);
	fmt::println_double(-10.0);
	fmt::println_double(-2147483647.0);
	fmt::println_double(-9223372036854775807.0);
	fmt::println_double(-9223372036854775808.0);
	fmt::println("test 1 ----------");

	fmt::println("test 2 ----------");
	fmt::println(0.0);
	fmt::println(1.0);
	fmt::println(10.0);
	fmt::println(2147483647.0);
	fmt::println(9223372036854775807.0);	
	fmt::println(-0.0);
	fmt::println(-1.0);
	fmt::println(-10.0);
	fmt::println(-2147483647.0);
	fmt::println(-9223372036854775807.0);
	fmt::println(-9223372036854775808.0);
	fmt::println("test 2 ----------");

}