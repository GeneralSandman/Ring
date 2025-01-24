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

	// 通过字段初始化 field 类型为匿名函数变量
	// 测试 pop_field_closure
	local_job_value_0.StringField = "Hello1";
	local_job_value_0.FuncField = fn() {
		fmt::println("Hello1 from FuncField");
	};

	// 输出是指针，不太好测试
	// fmt::printf("local_job_value_0={}\n", local_job_value_0);
	// 输出：local_job_value_0={StringField:Hello1 FuncField:closure(0x131e96520)}


	// 通过常量去初始化
	local_job_value_0 = Job {
		StringField: "Hello2",
		FuncField: fn() {
			fmt::println("Hello2 from FuncField");
		}
	};
	// 输出是指针，不太好测试
	// fmt::printf("local_job_value_0={}\n", local_job_value_0);
	// 输出：local_job_value_0={StringField:Hello2 FuncField:closure(0x131e964a0)}


	// 像调用 method 一样调用 field
	local_job_value_0.FuncField();



	// 测试 push_field_closure
	// 将 field 赋值给一个临时变量，然后当成函数一样调用
	var FuncType local_func_value_0;
	local_func_value_0 = local_job_value_0.FuncField;
	local_func_value_0();
}