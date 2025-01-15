package main

import {
	fmt;
	reflect;
}

typedef fn(string) -> (string) FuncType;


typedef class Job {
	var string StringField;
	var FuncType FuncField;

	fn MethodField(var bool bool_value) -> (bool) {
		fmt::printf("Hello1 from Job::MethodField, self.StringField={}, bool_value={}\n", self.StringField, bool_value);
		return bool_value;
	}
}

// TestDetail: class 中的field为匿名函数变量
fn main() {
	var bool local_bool_value_0 = false;
	var string local_string_value_0 = "";

	var Job local_job_value_0 = Job {
		StringField: "Hello2",
		FuncField: fn(var string string_value) -> (string) {
			fmt::printf("Hello2 from FuncField, string_value={}\n", string_value);
			return string_value;
		}
	};
	

	fmt::printf("--- test invoke method&field ----\n");
	local_bool_value_0   = local_job_value_0.MethodField(true);
	local_string_value_0 = local_job_value_0.FuncField("RING");

	fmt::printf("\n--- test return value of invoke method&field ----\n");
	fmt::printf("local_bool_value_0  ={}\n", local_bool_value_0);
	fmt::printf("local_string_value_0={}\n", local_string_value_0);



	var int64 co_id;
	fmt::printf("\n--- test launch method&field ----\n");
	co_id = launch local_job_value_0.MethodField(false);
	resume(co_id);
	co_id = launch local_job_value_0.FuncField("RING-beta");
	resume(co_id);
}