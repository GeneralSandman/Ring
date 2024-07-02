package main

import {
	fmt;
	debug;
}


// TestDetail: 测试函数返回 bool 类型
@main
function main() {
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




function return_1_bool_0() -> (bool) {
	return false;
}
function return_1_bool_1() -> (bool) {
	return true;
}



function return_2_bool_0() -> (bool,bool) {
	return false, true;
}
function return_2_bool_1() -> (bool,bool) {
	return true, false;
}



function return_3_bool_0() -> (bool,bool,bool) {
	return false, true, false;
}
function return_3_bool_1() -> (bool,bool,bool) {
	return true, false, true;
}



function return_4_bool_0() -> (bool,bool,bool,bool) {
	return false, true, false, true;
}
function return_4_bool_1() -> (bool,bool,bool,bool) {
	return true, false, true, false;
}



function return_5_bool_0() -> (bool,bool,bool,bool,bool) {
	return false, true, false, true, false;
}
function return_5_bool_1() -> (bool,bool,bool,bool,bool) {
	return true, false, true, false, true;
}



function return_6_bool_0() -> (bool,bool,bool,bool,bool,bool) {
	return false, true, false, true, false, true;
}
function return_6_bool_1() -> (bool,bool,bool,bool,bool,bool) {
	return true, false, true, false, true, false;
}



function return_7_bool_0() -> (bool,bool,bool,bool,bool,bool,bool) {
	return false, true, false, true, false, true, false;
}
function return_7_bool_1() -> (bool,bool,bool,bool,bool,bool,bool) {
	return true, false, true, false, true, false, true;
}



function return_8_bool_0() -> (bool,bool,bool,bool,bool,bool,bool,bool) {
	return false, true, false, true, false, true, false, true;
}
function return_8_bool_1() -> (bool,bool,bool,bool,bool,bool,bool,bool) {
	return true, false, true, false, true, false, true, false;
}