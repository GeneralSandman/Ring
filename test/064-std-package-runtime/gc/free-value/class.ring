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
fn test0() -> (FuncType) {
	var FuncType local_func_var_0;

	local_func_var_0 = test0_return_closure();

	runtime::gc();

	local_func_var_0();
	local_func_var_0();
	local_func_var_0();
	local_func_var_0();

	return local_func_var_0;
}

fn test0_return_closure() -> (FuncType) {
	fmt::printf("test0_return_closure------------\n");

	var Job1 local_job1_value_0;

	return fn() {
		local_job1_value_0.Int ++;
		// fmt::println_pointer(local_job1_value_0); // 每次 class 的指针都是一样的，这里不太好测试
		fmt::printf("local_job1_value_0.Int={}\n", local_job1_value_0.Int);
	};

}