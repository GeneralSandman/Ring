package main

import {
	fmt;
	debug;
}


// TestDetail: 测试函数返回 int64 数组类型
@main
function main() {
	fmt::println(return_int64_array_1_0());
	fmt::println(return_int64_array_1_1());
	fmt::println(return_int64_array_1_2());
	fmt::println(return_int64_array_1_3());



	fmt::println(return_int64_array_2_0());
	fmt::println(return_int64_array_2_1());
	fmt::println(return_int64_array_2_2());
	fmt::println(return_int64_array_2_3());



	fmt::println(return_int64_array_8_0());
}




function return_int64_array_1_0() -> (int64[]) {
	return int64[]{4567L};
}
function return_int64_array_1_1() -> (int64[]) {
	return int64[]{1234L};
}
function return_int64_array_1_2() -> (int64[]) {
	return int64[]{1234L, 4567L, 1234L, 4567L};
}
function return_int64_array_1_3() -> (int64[]) {
	return int64[]{1234L, 4567L, 1234L, 4567L, 1234L};
}


function return_int64_array_2_0() -> (int64[], int64[]) {
	return int64[]{4567L}, int64[]{1234L};
}
function return_int64_array_2_1() -> (int64[], int64[]) {
	return int64[]{1234L}, int64[]{4567L};
}
function return_int64_array_2_2() -> (int64[], int64[]) {
	return int64[]{1234L, 4567L, 1234L, 4567L}, int64[]{1234L, 4567L, 1234L, 4567L};
}
function return_int64_array_2_3() -> (int64[], int64[]) {
	return int64[]{1234L, 4567L, 1234L, 4567L, 1234L}, int64[]{1234L, 4567L, 1234L, 4567L, 1234L};
}



function return_int64_array_8_0() -> (int64[], int64[], int64[], int64[], int64[], int64[], int64[], int64[]) {
	return int64[]{4567L}, int64[]{1234L}, int64[]{4567L}, int64[]{1234L}, int64[]{4567L}, int64[]{1234L}, int64[]{4567L}, int64[]{1234L};
}
