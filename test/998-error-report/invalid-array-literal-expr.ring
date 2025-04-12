package main

import {
    fmt;
    debug;
    runtime;
	reflect;
}


fn main() {
	test_invalid_array_literal();
}

// fn test_not_define() {
// 	a[1];
// }

// fn test_not_array() {
// 	var int a;
// 	a[1];
// }

// fn test_invalid_dimension() {
// 	var int[] a;
// 	a[1,1];
// }

fn test_invalid_array_literal() {
	var int[] array = int[]{
		return_void(),
	};

	fmt::println(array);
}

fn return_int() -> (int) {
	return 1;
}

fn return_two_int() -> (int, int) {
	return 2, 3;
}

fn return_void() {
	return;
}