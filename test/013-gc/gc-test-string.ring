package main

import {
    fmt;
    debug;
    runtime;
}


fn main() {
	test_1();
}

fn test_0() {
	var string local_string_value_0 = "1";
	var string local_string_value_1 = "2";
	var string local_string_value_2 = "1" .. "2";

	fmt::println(local_string_value_0);
	fmt::println(local_string_value_1);
	fmt::println(local_string_value_2);
}

fn test_1() {
	var string local_string_value_0 = "12345678";
	runtime::gc();
}