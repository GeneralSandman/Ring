package main

import {
	fmt;
	debug;
}

fn main() {

	fmt::println("test 1 ----------");
	fmt::println_int64(0L);
	fmt::println_int64(1L);
	fmt::println_int64(10L);
	fmt::println_int64(2147483647L);
	fmt::println_int64(9223372036854775807L);	
	fmt::println_int64(-0L);
	fmt::println_int64(-1L);
	fmt::println_int64(-10L);
	fmt::println_int64(-2147483647L);
	fmt::println_int64(-9223372036854775807L);
	fmt::println_int64(-9223372036854775808L);
	fmt::println("test 1 ----------");

	fmt::println("test 2 ----------");
	fmt::println(0L);
	fmt::println(1L);
	fmt::println(10L);
	fmt::println(2147483647L);
	fmt::println(9223372036854775807L);	
	fmt::println(-0L);
	fmt::println(-1L);
	fmt::println(-10L);
	fmt::println(-2147483647L);
	fmt::println(-9223372036854775807L);
	fmt::println(-9223372036854775808L);
	fmt::println("test 2 ----------");

}