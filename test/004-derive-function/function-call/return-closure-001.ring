package main

import {
	fmt;
	reflect;
	runtime;
}

typedef FuncTypeVoid2Void = fn();

typedef FuncTypeVoid2Fn = fn() -> (FuncTypeVoid2Void);

// TestDetail: 更复杂的函数返回匿名函数直接调用
// TestDetail: 类似于 return_closure()()();
fn main() {

	test0();

}

fn test0() {
	fmt::printf("\ntest0------------------\n");
	
	// 方法1
	var FuncTypeVoid2Fn local_func_var_0;
	var FuncTypeVoid2Void local_func_var_1;

	local_func_var_0 = return_closure_0();
	local_func_var_1 = local_func_var_0();
	local_func_var_1();
	// local_func_var();


	// 方法2 与 方法1 等价
	return_closure_0()()();
}
fn return_closure_0() -> (FuncTypeVoid2Fn) {
	fmt::printf("return_closure_0 level-0 build closure\n");
	return fn() -> (FuncTypeVoid2Void) {
		fmt::printf("return_closure_0 level-1 build closure\n");
		return fn() {
			fmt::printf("return_closure_0 level-2 closure block\n");
		};
	};
}
