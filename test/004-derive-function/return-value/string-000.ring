package main

import {
	fmt;
	debug;
}


// TestDetail: 测试函数返回 bool 类型
@main
function main() {
	fmt::println(return_1_string_0());
	fmt::println(return_1_string_1());

	fmt::println(return_2_string_0());
	fmt::println(return_2_string_1());

	fmt::println(return_3_string_0());
	fmt::println(return_3_string_1());

	fmt::println(return_4_string_0());
	fmt::println(return_4_string_1());

	fmt::println(return_5_string_0());
	fmt::println(return_5_string_1());

	fmt::println(return_6_string_0());
	fmt::println(return_6_string_1());

	fmt::println(return_7_string_0());
	fmt::println(return_7_string_1());

	fmt::println(return_8_string_0());
	fmt::println(return_8_string_1());


}




function return_1_string_0() -> (string) {
	return "0";
}
function return_1_string_1() -> (string) {
	return "1";
}



function return_2_string_0() -> (string,string) {
	return "0", "1";
}
function return_2_string_1() -> (string,string) {
	return "1", "0";
}



function return_3_string_0() -> (string,string,string) {
	return "0", "1", "0";
}
function return_3_string_1() -> (string,string,string) {
	return "1", "0", "1";
}



function return_4_string_0() -> (string,string,string,string) {
	return "0", "1", "0", "1";
}
function return_4_string_1() -> (string,string,string,string) {
	return "1", "0", "1", "0";
}



function return_5_string_0() -> (string,string,string,string,string) {
	return "0", "1", "0", "1", "0";
}
function return_5_string_1() -> (string,string,string,string,string) {
	return "1", "0", "1", "0", "1";
}



function return_6_string_0() -> (string,string,string,string,string,string) {
	return "0", "1", "0", "1", "0", "1";
}
function return_6_string_1() -> (string,string,string,string,string,string) {
	return "1", "0", "1", "0", "1", "0";
}



function return_7_string_0() -> (string,string,string,string,string,string,string) {
	return "0", "1", "0", "1", "0", "1", "0";
}
function return_7_string_1() -> (string,string,string,string,string,string,string) {
	return "1", "0", "1", "0", "1", "0", "1";
}



function return_8_string_0() -> (string,string,string,string,string,string,string,string) {
	return "0", "1", "0", "1", "0", "1", "0", "1";
}
function return_8_string_1() -> (string,string,string,string,string,string,string,string) {
	return "1", "0", "1", "0", "1", "0", "1", "0";
}