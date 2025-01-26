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

	// 通过常量去初始化
	local_job_value_0 = Job {
		StringField: "Hello1",
		FuncField: fn() {
			var string local_string_value_0;
			local_string_value_0 = "xx";
			fmt::printf("Hello1 from FuncField, local_string_value_0={}\n", local_string_value_0);
		}
	};
	// 输出是指针，不太好测试
	// fmt::printf("local_job_value_0={}\n", local_job_value_0);
	// 输出：local_job_value_0={StringField:Hello2 FuncField:closure(0x131e964a0)}


	// 像调用 method 一样调用 field
	fmt::printf("local_job_value_0.StringField={}\n", local_job_value_0.StringField);
	local_job_value_0.FuncField();

	// class 赋值
	local_job_value_1 = local_job_value_0;

	fmt::printf("local_job_value_1.StringField={}\n", local_job_value_0.StringField);
	local_job_value_1.FuncField();

}