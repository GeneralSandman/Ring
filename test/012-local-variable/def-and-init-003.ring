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

fn func_return_3_bool() -> (bool, bool, bool) {
	fmt::println("func_return_3_bool::start");
	return true, false, true;
}

fn func_return_3_int() -> (int, int, int) {
	fmt::println("func_return_3_int::start");
	return 1, 2, 3;
}

fn func_return_3_int64() -> (int64, int64, int64) {
	fmt::println("func_return_3_int64::start");
	return 655367L, 655368L, 655369L;
}

fn func_return_3_double() -> (double, double, double) {
	fmt::println("func_return_3_double::start");
	return 655367655367.0, 655367655367.123, 655367655367.456;
}

fn func_return_3_string() -> (string, string, string) {
	fmt::println("func_return_3_string::start");
	return "ring-v0.2.14-release", "ring-v0.2.14-beta", "ring-v0.2.14-alpha";
}

fn func_return_3_job1() -> (Job1, Job1, Job1) {
	fmt::println("func_return_3_job1::start");
	return Job1{
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
}


// TestDetail: 测试 bool/int/int64/double/string/class 类型变量的定义和初始化
// TestDetail: 均为局部变量
// TestDetail: 初始化表达式为函数调用
@main
fn main() {
	fmt::println("main::start");

	var bool   local_bool_value_0,   local_bool_value_1,   local_bool_value_2   = func_return_3_bool();
	var int    local_int_value_0,    local_int_value_1,    local_int_value_2    = func_return_3_int();
	var int64  local_int64_value_0,  local_int64_value_1,  local_int64_value_2  = func_return_3_int64();
	var double local_double_value_0, local_double_value_1, local_double_value_2 = func_return_3_double();
	var string local_string_value_0, local_string_value_1, local_string_value_2 = func_return_3_string();
	var Job1   local_job1_value_0,   local_job1_value_1,   local_job1_value_2   = func_return_3_job1();
	

	fmt::println(local_bool_value_0,   local_bool_value_1,   local_bool_value_2);
	fmt::println(local_int_value_0,    local_int_value_1,    local_int_value_2);
	fmt::println(local_int64_value_0,  local_int64_value_1,  local_int64_value_2);
	fmt::println(local_double_value_0, local_double_value_1, local_double_value_2);
	fmt::println(local_string_value_0, local_string_value_1, local_string_value_2);
	fmt::println(local_job1_value_0,   local_job1_value_1,   local_job1_value_2);

}