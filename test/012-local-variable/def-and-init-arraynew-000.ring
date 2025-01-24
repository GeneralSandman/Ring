package main

import {
	fmt;
	debug;
}

global {

}

typedef Job1 = class {
    var bool    Bool;
    var int     Int;
	var int64   Int64;
    var double  Double;
    var string  String;
}


// TestDetail: 测试 bool[]/int[]/int64[]/double[]/string[]/class[] 类型变量的定义和初始化
// TestDetail: 均为全局变量
// TestDetail: 数组变量 使用 new 关键字初始化
fn main() {

	var bool[]   local_bool_array_0   = new bool[4];
	var int[]    local_int_array_0    = new int[4];
	var int64[]  local_int64_array_0  = new int64[4];
	var double[] local_double_array_0 = new double[4];
	var string[] local_string_array_0 = new string[4];
	var Job1[]   local_job1_array_0   = new Job1[4];

	fmt::println(local_bool_array_0);
	fmt::println(local_int_array_0);
	fmt::println(local_int64_array_0);
	fmt::println(local_double_array_0);
	fmt::println(local_string_array_0);
	fmt::println(local_job1_array_0);
}