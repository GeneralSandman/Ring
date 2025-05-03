package main

import {
	fmt;
	debug;
	reflect;
	runtime;
}

// 默认空间 1+4+8+8+8=29
typedef Job1 = class {
	var bool    Bool;
	var int     Int;
	var int64   Int64;
	var double  Double;
	var string  String;
}


// TestDetail: 测试gc 回收 closure
fn main() {
	var FuncType local_func_var_0;

	local_func_var_0 = test0();

	runtime::gc();

	
	local_func_var_0();
	local_func_var_0();
	local_func_var_0();
	local_func_var_0();

}

typedef FuncType = fn();
typedef FuncType2 = fn() -> (FuncType);

fn test0() -> (FuncType) {
	var FuncType local_func_var_0;
	var FuncType2 local_func_var_2;

	local_func_var_2 = test0_return_closure();
	local_func_var_0 = local_func_var_2();
	runtime::gc();

	local_func_var_0();
	local_func_var_0();
	local_func_var_0();
	local_func_var_0();


	local_func_var_0 = local_func_var_2();
	runtime::gc();

	local_func_var_0();
	local_func_var_0();
	local_func_var_0();
	local_func_var_0();

	return local_func_var_0;
}



fn test0_return_closure() -> (FuncType2) {
	fmt::printf("test0_return_closure------------\n");

	var Job1 local_job1_value_0;

	return fn() -> (FuncType) {
		var Job1 local_job1_value_1;

		return fn() {
			local_job1_value_0.Int++;
			local_job1_value_1.Int = local_job1_value_1.Int + 2;

			fmt::printf("local_job1_value_0.Int = {}, local_job1_value_1.Int = {}\n", local_job1_value_0.Int, local_job1_value_1.Int);

		};
	};
}