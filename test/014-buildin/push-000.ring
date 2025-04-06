package main

import {
    fmt;
    debug;
    runtime;
	reflect;
}


fn main() {
	test_push_1();
	test_push_2();
}


fn test_push_1() {
	var int[] local_int_array_0;

	// ----
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

	// ----
	push(local_int_array_0, 1);
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);
}

fn test_push_2() {
	// var int[,] local_int_array_0;
	var int[,] local_int_array_0 = int[,]{int[]{1}};
	var int[] local_int_array_tmp = int[]{234};

	// ----
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

	// ----
	push(local_int_array_0, local_int_array_tmp);
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);


}