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


// TestDetail: 测试 bool/int/int64/double/string/class 类型变量的定义和初始化
// TestDetail: 均为局部变量
fn main() {
	var bool   local_bool_value_0   = true;
	var int    local_int_value_0    = 123;
	var int64  local_int64_value_0  = 655367L;
	var double local_double_value_0 = 655367655367.123;
	var string local_string_value_0 = "ring-v0.2.14-beta";
	var Job1   local_job1_value_0   = Job1{
			Bool:   true,
			Int:    123,
			Int64:  655367L,
			Double: 655367655367.123,
			String: "local_job1_value_0",
		};
	
	fmt::println(local_bool_value_0);
	fmt::println(local_int_value_0);
	fmt::println(local_int64_value_0);
	fmt::println(local_double_value_0);
	fmt::println(local_string_value_0);
	fmt::println(local_job1_value_0);
}