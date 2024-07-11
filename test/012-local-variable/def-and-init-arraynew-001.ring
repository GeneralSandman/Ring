package main

import {
	fmt;
	debug;
}

global {

}

typedef class Job1 {
    field bool    Bool;
    field int     Int;
	field int64   Int64;
    field double  Double;
    field string  String;
}


// TestDetail: 测试 bool[!2]/int[!2]/int64[!2]/double[!2]/string[!2]/class[!2] 类型变量的定义和初始化
// TestDetail: 均为全局变量
// TestDetail: 数组变量 使用 new 关键字初始化
@main
function main() {

	var bool[!2]   local_bool_array_0   = new bool[2,4];
	var int[!2]    local_int_array_0    = new int[2,4];
	var int64[!2]  local_int64_array_0  = new int64[2,4];
	var double[!2] local_double_array_0 = new double[2,4];
	var string[!2] local_string_array_0 = new string[2,4];
	var Job1[!2]   local_job1_array_0   = new Job1[2,4];

	fmt::println(local_bool_array_0);
	fmt::println(local_int_array_0);
	fmt::println(local_int64_array_0);
	fmt::println(local_double_array_0);
	fmt::println(local_string_array_0);
	fmt::println(local_job1_array_0);
}