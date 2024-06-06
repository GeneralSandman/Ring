//
// File:    std-fmt-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	fmt;
}

typedef class Job1 {
    field bool    Bool;
    field int     Int;
	field int64   Int64;
    field double  Double;
    field string  String;

	field string[] StringArray;
	field Job2    Job2;
}

typedef class Job2 {
	field bool    Bool;
    field int     Int;
	field int64   Int64;
    field double  Double;
    field string  String;
}

global {

	var string[] global_string_array_0;

	var Job1 global_job1_value_0;


	var Job1[]   global_job1_array_0;
}

// TestDetail: 测试 fmt::println 函数
// TestDetail:  测试 打印数组 打印ClassObject
@main
function main() {



	fmt::println("test case 1 -------------");
	fmt::println(global_job1_value_0);



	fmt::println("\ntest case 1 -------------");
	global_string_array_0 = string[]{"1", "2", "3", "4", "5"};
	fmt::println(global_string_array_0);

	global_job1_array_0 = Job1[]{
	    Job1{
			Bool: true, 
			Int: 1, 
			Int64: 9223372036854775807,
			Double: 1.0, 
			String: "1",
			StringArray: string[]{"1", "2", "3", "4", "5"},
			Job2: Job2{
			    Bool: true, 
			    Int: 1, 
				Int64: 9223372036854775807,
				Double: 1.0, 
			    String: "1",
			},
		},
	    Job1{
			Bool: false, 
			Int: 2, 
			Int64: 9223372036854775807,
			Double: 2.0, 
			String: "2",
			StringArray: string[]{"1", "2", "3", "4", "5"},
			Job2: Job2{
			    Bool: false, 
			    Int: 2, 
				Int64: 9223372036854775807,
			    Double: 2.0, 
			    String: "2",
			},
		},
	};
	fmt::println(global_job1_array_0);

}