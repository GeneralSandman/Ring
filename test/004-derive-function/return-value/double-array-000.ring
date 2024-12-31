package main

import {
	fmt;
	debug;
}


// TestDetail: 测试函数返回 double 数组类型
@main
fn main() {
	fmt::println(return_double_array_1_0());
	fmt::println(return_double_array_1_1());
	fmt::println(return_double_array_1_2());
	fmt::println(return_double_array_1_3());



	fmt::println(return_double_array_2_0());
	fmt::println(return_double_array_2_1());
	fmt::println(return_double_array_2_2());
	fmt::println(return_double_array_2_3());



	fmt::println(return_double_array_8_0());
}




fn return_double_array_1_0() -> (double[]) {
	return double[]{0.0};
}
fn return_double_array_1_1() -> (double[]) {
	return double[]{1.1};
}
fn return_double_array_1_2() -> (double[]) {
	return double[]{1.1, 0.0, 1.1, 0.0};
}
fn return_double_array_1_3() -> (double[]) {
	return double[]{1.1, 0.0, 1.1, 0.0, 1.1};
}


fn return_double_array_2_0() -> (double[], double[]) {
	return double[]{0.0}, double[]{1.1};
}
fn return_double_array_2_1() -> (double[], double[]) {
	return double[]{1.1}, double[]{0.0};
}
fn return_double_array_2_2() -> (double[], double[]) {
	return double[]{1.1, 0.0, 1.1, 0.0}, double[]{1.1, 0.0, 1.1, 0.0};
}
fn return_double_array_2_3() -> (double[], double[]) {
	return double[]{1.1, 0.0, 1.1, 0.0, 1.1}, double[]{1.1, 0.0, 1.1, 0.0, 1.1};
}



fn return_double_array_8_0() -> (double[], double[], double[], double[], double[], double[], double[], double[]) {
	return double[]{0.0}, double[]{1.1}, double[]{0.0}, double[]{1.1}, double[]{0.0}, double[]{1.1}, double[]{0.0}, double[]{1.1};
}
