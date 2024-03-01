package main

import {
    fmt;
    debug;
}

typedef class Job1 {
    field bool    Bool;
    field int     Int;
    field double  Double;
    field string  String;
}

global {
  var Job1[] global_job1_array_0;
}

// TestDetail: 测试一维数组的初始化
// TestDetail: 一维数组的初始化
// TestDetail: 数组中的元素为 ClassObject
@main
function main() {
	global_job1_array_0 = Job1[]{
		Job1{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
		Job1{Bool: false, Int: 1, Double: 1.1, String: "1.1"},
		Job1{Bool: true,  Int: 2, Double: 2.2, String: "2.2"},
		Job1{Bool: false, Int: 3, Double: 3.3, String: "3.3"},
		Job1{Bool: true,  Int: 4, Double: 4.4, String: "4.4"},
		Job1{Bool: false, Int: 5, Double: 5.5, String: "5.5"},
		Job1{Bool: true,  Int: 6, Double: 6.6, String: "6.6"},
		Job1{Bool: false, Int: 7, Double: 7.7, String: "7.7"},
		Job1{Bool: true,  Int: 8, Double: 8.8, String: "8.8"},
		Job1{Bool: false, Int: 9, Double: 9.9, String: "9.9"}
	};

	debug::debug_assert(len(global_job1_array_0) == 10);

	debug::debug_assert(global_job1_array_0[0].Bool   == true);
	debug::debug_assert(global_job1_array_0[0].Int    == 0);
	debug::debug_assert(global_job1_array_0[0].Double == 0.0);
	debug::debug_assert(global_job1_array_0[0].String == "0.0");

	debug::debug_assert(global_job1_array_0[1].Bool   == false);
	debug::debug_assert(global_job1_array_0[1].Int    == 1);
	debug::debug_assert(global_job1_array_0[1].Double == 1.1);
	debug::debug_assert(global_job1_array_0[1].String == "1.1");

	debug::debug_assert(global_job1_array_0[2].Bool   == true);
	debug::debug_assert(global_job1_array_0[2].Int    == 2);
	debug::debug_assert(global_job1_array_0[2].Double == 2.2);
	debug::debug_assert(global_job1_array_0[2].String == "2.2");

	debug::debug_assert(global_job1_array_0[3].Bool   == false);
	debug::debug_assert(global_job1_array_0[3].Int    == 3);
	debug::debug_assert(global_job1_array_0[3].Double == 3.3);
	debug::debug_assert(global_job1_array_0[3].String == "3.3");

	debug::debug_assert(global_job1_array_0[9].Bool   == false);
	debug::debug_assert(global_job1_array_0[9].Int    == 9);
	debug::debug_assert(global_job1_array_0[9].Double == 9.9);
	debug::debug_assert(global_job1_array_0[9].String == "9.9");

	

	
}