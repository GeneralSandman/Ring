package main

import {
	fmt;
	reflect;
}

typedef fn() FuncType;


typedef class Job {
	var string StringField;
	var FuncType FuncField;
}

// TestDetail: class 中的field为匿名函数变量
fn main() {
	var Job local_job_value_0;

	// 通过字段初始化 field 类型为匿名函数变量
	// 测试 pop_field_closure
	local_job_value_0.StringField = "Hello1";
	local_job_value_0.FuncField = fn() {
		fmt::println("Hello1 from FuncField");
	};
	fmt::printf("local_job_value_0={}\n", local_job_value_0);


	// 通过常量去初始化
	local_job_value_0 = Job {
		StringField: "Hello2",
		FuncField: fn() {
			fmt::println("Hello2 from FuncField");
		}
	};
	fmt::printf("local_job_value_0={}\n", local_job_value_0);


	// local_job_value_0.FuncField();
	// FIXME:
	// 这里会编译报错，因为在语法层面，认为 FuncField是个method，而不是个 field
	// 需要通过语义分析优化


	// 测试 push_field_closure
	var FuncType local_func_value_0;
	local_func_value_0 = local_job_value_0.FuncField;
	local_func_value_0();
}