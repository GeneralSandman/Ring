package main

import {
	fmt;
	debug;
}


// TestDetail: 测试函数返回 int 数组类型
@main
fn main() {
	fmt::println(return_int_array_1_0());
	fmt::println(return_int_array_1_1());
	fmt::println(return_int_array_1_2());
	fmt::println(return_int_array_1_3());



	fmt::println(return_int_array_2_0());
	fmt::println(return_int_array_2_1());
	fmt::println(return_int_array_2_2());
	fmt::println(return_int_array_2_3());



	fmt::println(return_int_array_8_0());
}




fn return_int_array_1_0() -> (int[]) {
	return int[]{0};
}
fn return_int_array_1_1() -> (int[]) {
	return int[]{1};
}
fn return_int_array_1_2() -> (int[]) {
	return int[]{1, 0, 1, 0};
}
fn return_int_array_1_3() -> (int[]) {
	return int[]{1, 0, 1, 0, 1};
}


fn return_int_array_2_0() -> (int[], int[]) {
	return int[]{0}, int[]{1};
}
fn return_int_array_2_1() -> (int[], int[]) {
	return int[]{1}, int[]{0};
}
fn return_int_array_2_2() -> (int[], int[]) {
	return int[]{1, 0, 1, 0}, int[]{1, 0, 1, 0};
}
fn return_int_array_2_3() -> (int[], int[]) {
	return int[]{1, 0, 1, 0, 1}, int[]{1, 0, 1, 0, 1};
}



fn return_int_array_8_0() -> (int[], int[], int[], int[], int[], int[], int[], int[]) {
	return int[]{0}, int[]{1}, int[]{0}, int[]{1}, int[]{0}, int[]{1}, int[]{0}, int[]{1};
}
