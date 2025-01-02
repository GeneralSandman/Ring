//
// File:    std-debug-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	os;
	debug;
	fmt;
}

typedef fn() FuncType;


// TestDetail: 测试见的FreeValue , 不支持逃逸
fn main() {

	var FuncType func_var;

	func_var = use_closure();
	func_var();
	func_var();
	func_var();

	func_var = use_closure();
	func_var();
	func_var();
	func_var();
	func_var();
	func_var();
	func_var();
}

fn use_closure() -> (FuncType) {

	var int level0_local_int_value_0;

	level0_local_int_value_0 = 1;
	fmt::printf("[new closure] level0_local_int_value_0={}\n", level0_local_int_value_0);

	return fn() {
		level0_local_int_value_0++;
		fmt::printf("[+closure] level0_local_int_value_0={}\n", level0_local_int_value_0);
	};
}


