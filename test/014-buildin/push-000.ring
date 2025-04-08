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
	test_push_3();
}


fn test_push_1() {
	fmt::printf("test_push_1 ------------\n");
	var int[] local_int_array_0;

	// ----
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

	// ----
	push(local_int_array_0, 1);
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

	// ----
	push(local_int_array_0, 2);
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

	// ----
	push(local_int_array_0, 3);
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);
}

fn test_push_2() {
	fmt::printf("test_push_2 ------------\n");
	var int[,] local_int_array_0;

	// ----
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

	// ----
	push(local_int_array_0, int[]{1, 2, 3});
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

	// ----
	push(local_int_array_0, int[]{4, 5, 6});
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

	// ----
	push(local_int_array_0, int[]{7, 8, 9});
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

}


fn test_push_3() {
	fmt::printf("test_push_3 ------------\n");
	var int[,] local_int_array_0;

	// ----
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

	// ----
	var int[] tmp1 = int[]{1, 2, 3};
	push(local_int_array_0, tmp1);
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

	// ----
	var int[] tmp2 = int[]{4, 5, 6};
	push(local_int_array_0, tmp2);
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

	// ----
	var int[] tmp3 = int[]{4, 5, 6};
	push(local_int_array_0, tmp3);
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

}
