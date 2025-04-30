package main

import {
	fmt;
	debug;
	reflect;
	runtime;
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

	var int local_int_value_0;

	return fn() {
		local_int_value_0 ++;
		fmt::printf("local_int_value_0={}\n", local_int_value_0);
	};

}