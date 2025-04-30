package main

import {
    fmt;
    debug;
    runtime;
	reflect;
}


// TestDetail: 测试一个函数 返回同一个 class的局部变量，是否会触发深度copy
fn main() {
	var Job1 local_job1_value_0, local_job1_value_1;

	local_job1_value_0, local_job1_value_1 = return_two_job();

	runtime::gc();

	fmt::printf("local_job1_value_0 = {}\n", local_job1_value_0);
	fmt::printf("local_job1_value_1 = {}\n", local_job1_value_1);

	local_job1_value_0.Int = 100;
	local_job1_value_1.Int = 200;

	fmt::printf("local_job1_value_0 = {}\n", local_job1_value_0);
	fmt::printf("local_job1_value_1 = {}\n", local_job1_value_1);

	
	debug::assert(local_job1_value_0.Int != local_job1_value_1.Int);
}



// 默认空间 1+4+8+8+8=29
typedef Job1 = class {
	var bool    Bool;
	var int     Int;
	var int64   Int64;
	var double  Double;
	var string  String;
}

fn return_two_job() -> (Job1, Job1) {
	var Job1 local_job1_value_0;

	local_job1_value_0 = Job1 {
		Bool: true,
		Int: 1,
		Int64: 2L,
		Double: 3.0,
		String: "hello",
	};

	return local_job1_value_0, local_job1_value_0;
}