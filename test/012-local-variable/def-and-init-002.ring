package main

import {
	fmt;
	debug;
}

global {
	
}

typedef class Job1 {
    var bool    Bool;
    var int     Int;
	var int64   Int64;
    var double  Double;
    var string  String;
}


// TestDetail: 测试 bool/int/int64/double/string/class 类型变量的定义和初始化
// TestDetail: 均为局部变量
@main
fn main() {

	var bool   local_bool_value_0,   local_bool_value_1,   local_bool_value_2   = true, false, true;
	var int    local_int_value_0,    local_int_value_1,    local_int_value_2    = 1, 2, 3;
	var int64  local_int64_value_0,  local_int64_value_1,  local_int64_value_2  = 655367L, 655368L, 655369L;
	var double local_double_value_0, local_double_value_1, local_double_value_2 = 655367655367.0, 655367655367.123, 655367655367.456;
	var string local_string_value_0, local_string_value_1, local_string_value_2 = "ring-v0.2.14-release", "ring-v0.2.14-beta", "ring-v0.2.14-alpha";
	var Job1   local_job1_value_0,   local_job1_value_1,   local_job1_value_2   = 
		Job1{
			Bool:   true,
			Int:    1,
			Int64:  2L,
			Double: 3.0,
			String: "local_job1_value_0",
		},
		Job1{
			Bool:   false,
			Int:    11,
			Int64:  12L,
			Double: 13.0,
			String: "local_job1_value_1",
		},
		Job1{
			Bool:   true,
			Int:    21,
			Int64:  22L,
			Double: 23.0,
			String: "local_job1_value_2",
		};

	fmt::println(local_bool_value_0,   local_bool_value_1,   local_bool_value_2);
	fmt::println(local_int_value_0,    local_int_value_1,    local_int_value_2);
	fmt::println(local_int64_value_0,  local_int64_value_1,  local_int64_value_2);
	fmt::println(local_double_value_0, local_double_value_1, local_double_value_2);
	fmt::println(local_string_value_0, local_string_value_1, local_string_value_2);
	fmt::println(local_job1_value_0,   local_job1_value_1,   local_job1_value_2);

}