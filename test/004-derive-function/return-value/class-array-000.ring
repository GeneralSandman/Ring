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

global {
	var Job1 global_job1_value_1 = Job1{
		Bool:    true,
        Int:     10,
        Int64:   100L,
        Double:  3.14,
        String:  "hello",
    };

	var Job1 global_job1_value_2 = Job1{
        Bool:    false,
        Int:     20,
		Int64:   200L,
        Double:  6.28,
        String:  "world",
    };
}


// TestDetail: 测试函数返回 job1 数组类型
@main
function main() {
	fmt::println(return_job1_array_1_0());
	fmt::println(return_job1_array_1_1());
	fmt::println(return_job1_array_1_2());
	fmt::println(return_job1_array_1_3());



	fmt::println(return_job1_array_2_0());
	fmt::println(return_job1_array_2_1());
	fmt::println(return_job1_array_2_2());
	fmt::println(return_job1_array_2_3());



	fmt::println(return_job1_array_8_0());
}




function return_job1_array_1_0() -> (Job1[]) {
	return Job1[]{global_job1_value_1};
}
function return_job1_array_1_1() -> (Job1[]) {
	return Job1[]{global_job1_value_2};
}
function return_job1_array_1_2() -> (Job1[]) {
	return Job1[]{global_job1_value_2, global_job1_value_1, global_job1_value_2, global_job1_value_1};
}
function return_job1_array_1_3() -> (Job1[]) {
	return Job1[]{global_job1_value_2, global_job1_value_1, global_job1_value_2, global_job1_value_1, global_job1_value_2};
}


function return_job1_array_2_0() -> (Job1[], Job1[]) {
	return Job1[]{global_job1_value_1}, Job1[]{global_job1_value_2};
}
function return_job1_array_2_1() -> (Job1[], Job1[]) {
	return Job1[]{global_job1_value_2}, Job1[]{global_job1_value_1};
}
function return_job1_array_2_2() -> (Job1[], Job1[]) {
	return Job1[]{global_job1_value_2, global_job1_value_1, global_job1_value_2, global_job1_value_1}, Job1[]{global_job1_value_2, global_job1_value_1, global_job1_value_2, global_job1_value_1};
}
function return_job1_array_2_3() -> (Job1[], Job1[]) {
	return Job1[]{global_job1_value_2, global_job1_value_1, global_job1_value_2, global_job1_value_1, global_job1_value_2}, Job1[]{global_job1_value_2, global_job1_value_1, global_job1_value_2, global_job1_value_1, global_job1_value_2};
}



function return_job1_array_8_0() -> (Job1[], Job1[], Job1[], Job1[], Job1[], Job1[], Job1[], Job1[]) {
	return Job1[]{global_job1_value_1}, Job1[]{global_job1_value_2}, Job1[]{global_job1_value_1}, Job1[]{global_job1_value_2}, Job1[]{global_job1_value_1}, Job1[]{global_job1_value_2}, Job1[]{global_job1_value_1}, Job1[]{global_job1_value_2};
}
