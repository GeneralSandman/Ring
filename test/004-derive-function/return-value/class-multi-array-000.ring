package main

import {
	fmt;
	debug;
}


typedef class Job1 {
    var bool    Bool;
    var int     Int;
	var int64   Int64;
    var double  Double;
    var string  String;
}

global {
	var Job1 global_job1_value_0 = Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	};
	var Job1 global_job1_value_1 = Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	};
}


// TestDetail: derive函数传递class数组类型参数
// TestDetail: 分别传递1-8个class数组类型参数
fn main() {

	fmt::println(pass_1_job1_array_1());

	fmt::println(pass_1_job1_array_2());

	fmt::println(pass_1_job1_array_3());

	fmt::println(pass_1_job1_array_4());

}





fn pass_1_job1_array_1() -> (Job1[]) {
	return Job1[]{global_job1_value_0, global_job1_value_1};
}

fn pass_1_job1_array_2() -> (Job1[,]) {
	return Job1[,]{
		Job1[]{global_job1_value_0, global_job1_value_1},
		Job1[]{global_job1_value_0, global_job1_value_1},
	};
}

fn pass_1_job1_array_3() -> (Job1[,,]) {
	return Job1[,,]{
		Job1[,]{
			Job1[]{global_job1_value_0, global_job1_value_1},
			Job1[]{global_job1_value_0, global_job1_value_1},
		},
		Job1[,]{
			Job1[]{global_job1_value_0, global_job1_value_1},
			Job1[]{global_job1_value_0, global_job1_value_1},
		}
	};
}

fn pass_1_job1_array_4() -> (Job1[,,,]) {
	return Job1[,,,]{
		Job1[,,]{
			Job1[,]{
				Job1[]{global_job1_value_0, global_job1_value_1},
				Job1[]{global_job1_value_0, global_job1_value_1},
			},
			Job1[,]{
				Job1[]{global_job1_value_0, global_job1_value_1},
				Job1[]{global_job1_value_0, global_job1_value_1},
			}
		}
	};
}


