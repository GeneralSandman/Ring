package main

import {
	fmt;
	debug;
}


// TestDetail: 测试函数返回 bool 类型
fn main() {
	fmt::println(return_1_int_0());
	fmt::println(return_1_int_1());

	fmt::println(return_2_int_0());
	fmt::println(return_2_int_1());

	fmt::println(return_3_int_0());
	fmt::println(return_3_int_1());

	fmt::println(return_4_int_0());
	fmt::println(return_4_int_1());

	fmt::println(return_5_int_0());
	fmt::println(return_5_int_1());

	fmt::println(return_6_int_0());
	fmt::println(return_6_int_1());

	fmt::println(return_7_int_0());
	fmt::println(return_7_int_1());

	fmt::println(return_8_int_0());
	fmt::println(return_8_int_1());


}




fn return_1_int_0() -> (int) {
	return 0;
}
fn return_1_int_1() -> (int) {
	return 1;
}



fn return_2_int_0() -> (int,int) {
	return 0, 1;
}
fn return_2_int_1() -> (int,int) {
	return 1, 0;
}



fn return_3_int_0() -> (int,int,int) {
	return 0, 1, 0;
}
fn return_3_int_1() -> (int,int,int) {
	return 1, 0, 1;
}



fn return_4_int_0() -> (int,int,int,int) {
	return 0, 1, 0, 1;
}
fn return_4_int_1() -> (int,int,int,int) {
	return 1, 0, 1, 0;
}



fn return_5_int_0() -> (int,int,int,int,int) {
	return 0, 1, 0, 1, 0;
}
fn return_5_int_1() -> (int,int,int,int,int) {
	return 1, 0, 1, 0, 1;
}



fn return_6_int_0() -> (int,int,int,int,int,int) {
	return 0, 1, 0, 1, 0, 1;
}
fn return_6_int_1() -> (int,int,int,int,int,int) {
	return 1, 0, 1, 0, 1, 0;
}



fn return_7_int_0() -> (int,int,int,int,int,int,int) {
	return 0, 1, 0, 1, 0, 1, 0;
}
fn return_7_int_1() -> (int,int,int,int,int,int,int) {
	return 1, 0, 1, 0, 1, 0, 1;
}



fn return_8_int_0() -> (int,int,int,int,int,int,int,int) {
	return 0, 1, 0, 1, 0, 1, 0, 1;
}
fn return_8_int_1() -> (int,int,int,int,int,int,int,int) {
	return 1, 0, 1, 0, 1, 0, 1, 0;
}