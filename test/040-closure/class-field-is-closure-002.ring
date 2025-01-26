package main

import {
	fmt;
	reflect;
}

typedef FuncType = fn();


typedef Job = class {
	var string StringField;
	var FuncType FuncField;
}

// TestDetail: class 中的field为匿名函数变量
fn main() {
	var Job local_job_value_0;
	var Job local_job_value_1;

	fmt::printf("-------------------\n");
	// 通过常量去初始化
	local_job_value_0 = Job {
		StringField: "Hello1",
		FuncField: return_closure(), // 产生一个新的闭包
	};

	// 像调用 method 一样调用 field
	fmt::printf("local_job_value_0.StringField={}\n", local_job_value_0.StringField);
	local_job_value_0.FuncField();
	local_job_value_0.FuncField();

	fmt::printf("\n-------------------\n");
	// class 赋值
	local_job_value_1 = local_job_value_0; // 闭包复用了，没有重新产生

	fmt::printf("local_job_value_1.StringField={}\n", local_job_value_0.StringField);
	local_job_value_1.FuncField();
	local_job_value_1.FuncField();


	fmt::printf("\n-------------------\n");

	// 通过常量去初始化
	local_job_value_0 = Job {
		StringField: "Hello1",
		FuncField: return_closure(), // 产生一个新的闭包
	};

	// 像调用 method 一样调用 field
	fmt::printf("local_job_value_0.StringField={}\n", local_job_value_0.StringField);
	local_job_value_0.FuncField();
	local_job_value_0.FuncField();

}

fn return_closure() -> (FuncType) {
	var int local_int_value_0;
	
	return fn() {
		fmt::printf("a closure local_int_value_0={}\n", local_int_value_0);
		local_int_value_0++;
	};
}