package main

import {
	fmt;
	debug;
}


// TestDetail: 测试函数返回 bool 类型
@main
fn main() {
	fmt::println(return_1_bool_0());
	fmt::println(return_1_bool_1());

	fmt::println(return_2_bool_0());
	fmt::println(return_2_bool_1());

	fmt::println(return_3_bool_0());
	fmt::println(return_3_bool_1());

	fmt::println(return_4_bool_0());
	fmt::println(return_4_bool_1());

	fmt::println(return_5_bool_0());
	fmt::println(return_5_bool_1());

	fmt::println(return_6_bool_0());
	fmt::println(return_6_bool_1());

	fmt::println(return_7_bool_0());
	fmt::println(return_7_bool_1());

	fmt::println(return_8_bool_0());
	fmt::println(return_8_bool_1());


}




fn return_1_bool_0() -> (bool) {
	return false;
}
fn return_1_bool_1() -> (bool) {
	return true;
}



fn return_2_bool_0() -> (bool,bool) {
	return false, true;
}
fn return_2_bool_1() -> (bool,bool) {
	return true, false;
}



fn return_3_bool_0() -> (bool,bool,bool) {
	return false, true, false;
}
fn return_3_bool_1() -> (bool,bool,bool) {
	return true, false, true;
}



fn return_4_bool_0() -> (bool,bool,bool,bool) {
	return false, true, false, true;
}
fn return_4_bool_1() -> (bool,bool,bool,bool) {
	return true, false, true, false;
}



fn return_5_bool_0() -> (bool,bool,bool,bool,bool) {
	return false, true, false, true, false;
}
fn return_5_bool_1() -> (bool,bool,bool,bool,bool) {
	return true, false, true, false, true;
}



fn return_6_bool_0() -> (bool,bool,bool,bool,bool,bool) {
	return false, true, false, true, false, true;
}
fn return_6_bool_1() -> (bool,bool,bool,bool,bool,bool) {
	return true, false, true, false, true, false;
}



fn return_7_bool_0() -> (bool,bool,bool,bool,bool,bool,bool) {
	return false, true, false, true, false, true, false;
}
fn return_7_bool_1() -> (bool,bool,bool,bool,bool,bool,bool) {
	return true, false, true, false, true, false, true;
}



fn return_8_bool_0() -> (bool,bool,bool,bool,bool,bool,bool,bool) {
	return false, true, false, true, false, true, false, true;
}
fn return_8_bool_1() -> (bool,bool,bool,bool,bool,bool,bool,bool) {
	return true, false, true, false, true, false, true, false;
}