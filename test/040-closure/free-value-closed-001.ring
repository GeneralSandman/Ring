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

typedef FuncType = fn();


// TestDetail: 测试见的FreeValue , 不支持逃逸
fn main() {
	var FuncType func_var;

	func_var = return_closure();

	fmt::printf("------------------ [main] ------------------\n");
	func_var();
	func_var();
	func_var();
	func_var();
}

fn return_closure() -> (FuncType) {
	fmt::printf("------------------ [return_closure] ------------------\n");

	var FuncType tmp;
	var int local_int_value_0 = 100;
	var int local_int_value_1 = 200;


	tmp = fn() {
		local_int_value_0 ++;
		local_int_value_1 += 2;

		fmt::printf("return_closure::[closure]::1 local_int_value_0 = {}\n", local_int_value_0);
		fmt::printf("return_closure::[closure]::1 local_int_value_1 = {}\n", local_int_value_1);
	};

	tmp();
	tmp();
	tmp();
	tmp();


	// 此时应该 close return_closure 被引用的所有 FreeValue，目的是让他逃逸
	return tmp;
}


