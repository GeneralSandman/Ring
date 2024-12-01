package main

import {
	fmt;
	debug;
}


typedef class Job1 {
    field bool    Bool;
    field int     Int;
	field int64   Int64;
    field double  Double;
    field string  String;
}


// TestDetail: derive函数传递class数组类型参数
// TestDetail: 分别传递1-8个class数组类型参数
@main
function main() {

	var Job1 local_job1_value_0;
	var Job1 local_job1_value_1;
	
	local_job1_value_0 = Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	};
	local_job1_value_1 = Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	};


	pass_1_job1_array_1(
		Job1[]{local_job1_value_0, local_job1_value_1}
	);

	pass_1_job1_array_2(
		Job1[,]{
			Job1[]{local_job1_value_0, local_job1_value_1},
			Job1[]{local_job1_value_0, local_job1_value_1},
		}
	);

	pass_1_job1_array_3(
		Job1[,,]{
			Job1[,]{
				Job1[]{local_job1_value_0, local_job1_value_1},
				Job1[]{local_job1_value_0, local_job1_value_1},
			},
			Job1[,]{
				Job1[]{local_job1_value_0, local_job1_value_1},
				Job1[]{local_job1_value_0, local_job1_value_1},
			}
		}
	);

	pass_1_job1_array_4(
		Job1[,,,]{
			Job1[,,]{
				Job1[,]{
					Job1[]{local_job1_value_0, local_job1_value_1},
					Job1[]{local_job1_value_0, local_job1_value_1},
				},
				Job1[,]{
					Job1[]{local_job1_value_0, local_job1_value_1},
					Job1[]{local_job1_value_0, local_job1_value_1},
				}
			}
		}
	);

}





function pass_1_job1_array_1(var Job1[] a) {
	fmt::println(a);
}

function pass_1_job1_array_2(var Job1[,] a) {
	fmt::println(a);
}

function pass_1_job1_array_3(var Job1[,,] a) {
	fmt::println(a);
}

function pass_1_job1_array_4(var Job1[,,,] a) {
	fmt::println(a);
}

