package main

import {
	fmt;
	debug;
}

global {
	var bool[!2]   local_bool_array_0   = bool[!2]{
		bool[]{true, false, true, false},
		bool[]{true, false, true, false},
	};
	var int[!2]    local_int_array_0    = int[!2]{
		int[]{1, 2, 3, 4},
		int[]{1, 2, 3, 4},
	};
	var int64[!2]  local_int64_array_0  = int64[!2]{
		int64[]{1L, 2L, 3L, 4L},
		int64[]{1L, 2L, 3L, 4L},
	};
	var double[!2] local_double_array_0 = double[!2]{
		double[]{1.0, 2.0, 3.0, 4.0},
		double[]{1.0, 2.0, 3.0, 4.0},
	};
	var string[!2] local_string_array_0 = string[!2]{
		string[]{"a", "b", "c", "d"},
		string[]{"a", "b", "c", "d"},
	};
	var Job1[!2]   local_job1_array_0   = Job1[!2]{
		Job1[]{
			Job1{
				Bool:   true,
				Int:    0,
				Int64:  0L,
				Double: 0.0,
				String: "a",
			},
			Job1{
				Bool:   false,
				Int:    1,
				Int64:  1L,
				Double: 1.1,
				String: "b",
			},
		},
		Job1[]{
			Job1{
				Bool:   true,
				Int:    0,
				Int64:  0L,
				Double: 0.0,
				String: "a",
			},
			Job1{
				Bool:   false,
				Int:    1,
				Int64:  1L,
				Double: 1.1,
				String: "b",
			},
		}
	};
}

typedef Job1 = class {
    var bool    Bool;
    var int     Int;
	var int64   Int64;
    var double  Double;
    var string  String;
}


// TestDetail: 测试 bool[!2]/int[!2]/int64[!2]/double[!2]/string[!2]/class[!2] 类型变量的定义和初始化
// TestDetail: 均为全局变量
// TestDetail: 数组变量 通过数组常量初始化
fn main() {

	fmt::println(local_bool_array_0);
	fmt::println(local_int_array_0);
	fmt::println(local_int64_array_0);
	fmt::println(local_double_array_0);
	fmt::println(local_string_array_0);
	fmt::println(local_job1_array_0);
}