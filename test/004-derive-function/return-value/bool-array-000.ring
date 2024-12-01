package main

import {
	fmt;
	debug;
}


// TestDetail: 测试函数返回 bool 数组类型
@main
function main() {
	fmt::println(return_bool_array_1_0());
	fmt::println(return_bool_array_1_1());
	fmt::println(return_bool_array_1_2());
	fmt::println(return_bool_array_1_3());



	fmt::println(return_bool_array_2_0());
	fmt::println(return_bool_array_2_1());
	fmt::println(return_bool_array_2_2());
	fmt::println(return_bool_array_2_3());



	fmt::println(return_bool_array_8_0());
}




function return_bool_array_1_0() -> (bool[]) {
	return bool[]{false};
}
function return_bool_array_1_1() -> (bool[]) {
	return bool[]{true};
}
function return_bool_array_1_2() -> (bool[]) {
	return bool[]{true, false, true, false};
}
function return_bool_array_1_3() -> (bool[]) {
	return bool[]{true, false, true, false, true};
}


function return_bool_array_2_0() -> (bool[], bool[]) {
	return bool[]{false}, bool[]{true};
}
function return_bool_array_2_1() -> (bool[], bool[]) {
	return bool[]{true}, bool[]{false};
}
function return_bool_array_2_2() -> (bool[], bool[]) {
	return bool[]{true, false, true, false}, bool[]{true, false, true, false};
}
function return_bool_array_2_3() -> (bool[], bool[]) {
	return bool[]{true, false, true, false, true}, bool[]{true, false, true, false, true};
}



function return_bool_array_8_0() -> (bool[], bool[], bool[], bool[], bool[], bool[], bool[], bool[]) {
	return bool[]{false}, bool[]{true}, bool[]{false}, bool[]{true}, bool[]{false}, bool[]{true}, bool[]{false}, bool[]{true};
}
