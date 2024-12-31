package main

import {
	fmt;
	debug;
}


// TestDetail: 测试函数返回 bool 类型
@main
fn main() {
	fmt::println(return_1_int64_0());
	fmt::println(return_1_int64_1());

	fmt::println(return_2_int64_0());
	fmt::println(return_2_int64_1());

	fmt::println(return_3_int64_0());
	fmt::println(return_3_int64_1());

	fmt::println(return_4_int64_0());
	fmt::println(return_4_int64_1());

	fmt::println(return_5_int64_0());
	fmt::println(return_5_int64_1());

	fmt::println(return_6_int64_0());
	fmt::println(return_6_int64_1());

	fmt::println(return_7_int64_0());
	fmt::println(return_7_int64_1());

	fmt::println(return_8_int64_0());
	fmt::println(return_8_int64_1());


}




fn return_1_int64_0() -> (int64) {
	return 0L;
}
fn return_1_int64_1() -> (int64) {
	return 1L;
}



fn return_2_int64_0() -> (int64,int64) {
	return 0L, 1L;
}
fn return_2_int64_1() -> (int64,int64) {
	return 1L, 0L;
}



fn return_3_int64_0() -> (int64,int64,int64) {
	return 0L, 1L, 0L;
}
fn return_3_int64_1() -> (int64,int64,int64) {
	return 1L, 0L, 1L;
}



fn return_4_int64_0() -> (int64,int64,int64,int64) {
	return 0L, 1L, 0L, 1L;
}
fn return_4_int64_1() -> (int64,int64,int64,int64) {
	return 1L, 0L, 1L, 0L;
}



fn return_5_int64_0() -> (int64,int64,int64,int64,int64) {
	return 0L, 1L, 0L, 1L, 0L;
}
fn return_5_int64_1() -> (int64,int64,int64,int64,int64) {
	return 1L, 0L, 1L, 0L, 1L;
}



fn return_6_int64_0() -> (int64,int64,int64,int64,int64,int64) {
	return 0L, 1L, 0L, 1L, 0L, 1L;
}
fn return_6_int64_1() -> (int64,int64,int64,int64,int64,int64) {
	return 1L, 0L, 1L, 0L, 1L, 0L;
}



fn return_7_int64_0() -> (int64,int64,int64,int64,int64,int64,int64) {
	return 0L, 1L, 0L, 1L, 0L, 1L, 0L;
}
fn return_7_int64_1() -> (int64,int64,int64,int64,int64,int64,int64) {
	return 1L, 0L, 1L, 0L, 1L, 0L, 1L;
}



fn return_8_int64_0() -> (int64,int64,int64,int64,int64,int64,int64,int64) {
	return 0L, 1L, 0L, 1L, 0L, 1L, 0L, 1L;
}
fn return_8_int64_1() -> (int64,int64,int64,int64,int64,int64,int64,int64) {
	return 1L, 0L, 1L, 0L, 1L, 0L, 1L, 0L;
}