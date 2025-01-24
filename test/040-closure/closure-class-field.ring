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
	var FuncType local_func_value_0;



	fmt::printf("class's field is closure: pop field-------\n");
	// 通过字段初始化 field 类型为匿名函数变量
	// 测试 pop_field_closure
	local_job_value_0.StringField = "Hello1";
	local_job_value_0.FuncField = fn() {
		fmt::println("Hello1 from FuncField");
	};
	// 是指针，不太好测试
	// fmt::printf("local_job_value_0={}\n", local_job_value_0); // 输出：local_job_value_0={StringField:Hello1 FuncField:CLOSURE(0x7fa862a942d0)}
	local_func_value_0 = local_job_value_0.FuncField;
	local_func_value_0();



	
	fmt::printf("\nclass's field is closure: init literal-------\n");
	// 通过常量去初始化
	local_job_value_0 = Job {
		StringField: "Hello2",
		FuncField: fn() {
			fmt::println("Hello2 from FuncField");
		}
	};
	// 是指针，不太好测试
	// fmt::printf("local_job_value_0={}\n", local_job_value_0); // 输出：local_job_value_0={StringField:Hello2 FuncField:CLOSURE(0x7fa862a942a0)}
	local_func_value_0 = local_job_value_0.FuncField;
	local_func_value_0();


	// local_job_value_0.FuncField();
	// FIXME:
	// 这里会编译报错，因为在语法层面，认为 FuncField是个method，而不是个 field
	// 需要通过语义分析优化

}