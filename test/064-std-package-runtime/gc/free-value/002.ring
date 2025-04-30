package main

import {
	fmt;
	debug;
	reflect;
	runtime;
}


// TestDetail: 测试gc 回收 closure
fn main() {
	var FuncType local_func_var_0, local_func_var_1;

	local_func_var_0, local_func_var_1 = test0();

	runtime::gc();

	local_func_var_0();
	local_func_var_1();
	local_func_var_0();
	local_func_var_1();

}

typedef FuncType = fn();
fn test0() -> (FuncType, FuncType) {
	var FuncType local_func_var_0, local_func_var_1;

	local_func_var_0, local_func_var_1 = test0_return_closure();

	runtime::gc();

	local_func_var_0();
	local_func_var_1();
	local_func_var_0();
	local_func_var_1();

	return local_func_var_0, local_func_var_1;
}

fn test0_return_closure() -> (FuncType, FuncType) {
	fmt::printf("test0_return_closure------------\n");

	var int local_int_value_0;

	return fn() {
		local_int_value_0 ++;
		fmt::printf("local_int_value_0={}\n", local_int_value_0);
	}, fn() {
		local_int_value_0 ++;
		fmt::printf("local_int_value_0={}\n", local_int_value_0);
	};

}