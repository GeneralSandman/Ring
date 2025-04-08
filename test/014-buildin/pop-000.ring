package main

import {
    fmt;
    debug;
    runtime;
	reflect;
}


fn main() {
	test_pop_1();
	test_pop_2();
	test_pop_3();
	test_pop_4();
}


// test pass
fn test_pop_1() {
	fmt::printf("test_pop_1 ------------\n");
	var int[] local_int_array_0 = int[] {
		1, 2, 3
	};


	fmt::printf("pop value = {}\n", pop(local_int_array_0));
	fmt::printf("pop value = {}\n", pop(local_int_array_0));
	fmt::printf("pop value = {}\n", pop(local_int_array_0));

	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);
}

// test pass
fn test_pop_2() {
	fmt::printf("test_pop_2 ------------\n");
	var int[,] local_int_array_0 = int[,] {
		int[] {1, 2, 3},
		int[] {4, 5, 6},
		int[] {7, 8, 9},
	};


	fmt::printf("pop value = {}\n", pop(local_int_array_0));
	fmt::printf("pop value = {}\n", pop(local_int_array_0));
	fmt::printf("pop value = {}\n", pop(local_int_array_0));

	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);
}

// test pass
fn test_pop_3() {
	fmt::printf("test_pop_2 ------------\n");
	var int[,] local_int_array_0 = int[,] {
		int[] {1, 2, 3},
		int[] {4, 5, 6},
		int[] {7, 8, 9},
	};


	fmt::printf("pop value = {}\n", pop(local_int_array_0[2]));
	fmt::printf("pop value = {}\n", pop(local_int_array_0[2]));
	fmt::printf("pop value = {}\n", pop(local_int_array_0[2]));

	fmt::printf("pop value = {}\n", pop(local_int_array_0[1]));
	fmt::printf("pop value = {}\n", pop(local_int_array_0[1]));
	fmt::printf("pop value = {}\n", pop(local_int_array_0[1]));

	fmt::printf("pop value = {}\n", pop(local_int_array_0[0]));
	fmt::printf("pop value = {}\n", pop(local_int_array_0[0]));
	fmt::printf("pop value = {}\n", pop(local_int_array_0[0]));

	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);


}

fn test_pop_4() {
	fmt::printf("test_pop_4 ------------\n");
	var int[,] local_int_array_0 = int[,] {
		int[] {1, 2, 3},
		int[] {4, 5, 6},
		int[] {7, 8, 9},
	};

	fmt::printf("pop value = {}\n", pop(local_int_array_0[2]));
	fmt::printf("pop value = {}\n", pop(local_int_array_0));

	fmt::printf("typeof = {}\n", reflect::typeof(pop(local_int_array_0[1]))); // int
	fmt::printf("typeof = {}\n", reflect::typeof(pop(local_int_array_0))); // int[!1]

}