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
@main
fn main() {
	var FuncType func_var;

	fmt::printf("------------------ [main] ------------------\n");
	func_var = return_closure();
	func_var();
	func_var();
	func_var();
	func_var();

	fmt::printf("------------------ [main] ------------------\n");
	func_var = return_closure();
	func_var();
	func_var();
	func_var();
	func_var();
}

fn return_closure() -> (FuncType) {

	var int local_int_value_0 = 100;

	return fn() {
		local_int_value_0 ++;
		fmt::printf("return_closure::[closure]::1 local_int_value_0 = {}\n", local_int_value_0);
	};

}


