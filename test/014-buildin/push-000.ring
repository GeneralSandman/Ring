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
	test_push_4();
	test_push_5();
}


// 一维数组 push 元素
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

// 二维数组 push 一维数组
// push 的 第二个参数 是 array-literal
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


// 二维数组 push 一维数组
// push 的 第二个参数 是变量
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
	var int[] tmp3 = int[]{7, 8, 9};
	push(local_int_array_0, tmp3);
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

}



// 三维数组 push 而维数组
// push 的 第二个参数 是 array-literal
fn test_push_4() {
	fmt::printf("test_push_4 ------------\n");
	var int[,,] local_int_array_0;

	// ----
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

	// ----
	push(local_int_array_0, int[,]{
		int[]{1, 2, 3},
		int[]{4, 5, 6},
		int[]{7, 8, 9},
	});
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

	// ----
	push(local_int_array_0, int[,]{
		int[]{10, 11, 12},
		int[]{13, 14, 15},
		int[]{16, 17, 18},
	});
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

	// ----
	push(local_int_array_0, int[,]{
		int[]{19, 20, 21},
		int[]{22, 23, 24},
		int[]{25, 26, 27},
	});
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

}

// 二维数组 push
// 第一个参数 为 数组index访问
fn test_push_5() {
	fmt::printf("test_push_5 ------------\n");

	var int[,] local_int_array_0 = int[,]{
		int[]{1, 2, 3},
		int[]{4, 5, 6},
		int[]{7, 8, 9},
	};



	push(local_int_array_0[0], 11);
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

	push(local_int_array_0[1], 11);
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

	push(local_int_array_0[2], 11);
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);

}