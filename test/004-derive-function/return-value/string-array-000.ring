package main

import {
	fmt;
	debug;
}


// TestDetail: 测试函数返回 string 数组类型
@main
function main() {
	fmt::println(return_string_array_1_0());
	fmt::println(return_string_array_1_1());
	fmt::println(return_string_array_1_2());
	fmt::println(return_string_array_1_3());



	fmt::println(return_string_array_2_0());
	fmt::println(return_string_array_2_1());
	fmt::println(return_string_array_2_2());
	fmt::println(return_string_array_2_3());



	fmt::println(return_string_array_8_0());
}




function return_string_array_1_0() -> (string[]) {
	return string[]{"false"};
}
function return_string_array_1_1() -> (string[]) {
	return string[]{"true"};
}
function return_string_array_1_2() -> (string[]) {
	return string[]{"true", "false", "true", "false"};
}
function return_string_array_1_3() -> (string[]) {
	return string[]{"true", "false", "true", "false", "true"};
}


function return_string_array_2_0() -> (string[], string[]) {
	return string[]{"false"}, string[]{"true"};
}
function return_string_array_2_1() -> (string[], string[]) {
	return string[]{"true"}, string[]{"false"};
}
function return_string_array_2_2() -> (string[], string[]) {
	return string[]{"true", "false", "true", "false"}, string[]{"true", "false", "true", "false"};
}
function return_string_array_2_3() -> (string[], string[]) {
	return string[]{"true", "false", "true", "false", "true"}, string[]{"true", "false", "true", "false", "true"};
}



function return_string_array_8_0() -> (string[], string[], string[], string[], string[], string[], string[], string[]) {
	return string[]{"false"}, string[]{"true"}, string[]{"false"}, string[]{"true"}, string[]{"false"}, string[]{"true"}, string[]{"false"}, string[]{"true"};
}
