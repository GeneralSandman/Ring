package main

import {
	fmt;
	debug;
}

global {
	var bool[]   global_bool_array_0   = new bool[4];
	var int[]    global_int_array_0    = new int[4];
	var int64[]  global_int64_array_0  = new int64[4];
	var double[] global_double_array_0 = new double[4];
	var string[] global_string_array_0 = new string[4];
	var Job1[]   global_job1_array_0   = new Job1[4];
}

typedef class Job1 {
    field bool    Bool;
    field int     Int;
	field int64   Int64;
    field double  Double;
    field string  String;
}


// TestDetail: 测试 bool[]/int[]/int64[]/double[]/string[]/class[] 类型变量的定义和初始化
// TestDetail: 均为全局变量
// TestDetail: 数组变量 使用 new 关键字初始化
@main
function main() {

	fmt::println(global_bool_array_0);
	fmt::println(global_int_array_0);
	fmt::println(global_int64_array_0);
	fmt::println(global_double_array_0);
	fmt::println(global_string_array_0);
	fmt::println(global_job1_array_0);
}