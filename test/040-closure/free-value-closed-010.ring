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

typedef fn() FuncType1;

typedef fn() -> (FuncType1) FuncType2;


// TestDetail: 测试见的FreeValue , 不支持逃逸
fn main() {
	var FuncType2 func_var_2_0, func_var_2_1;
	var FuncType1 func_var_1_0, func_var_1_1;

	fmt::printf("------------------ [main] ------------------\n");
	func_var_2_0, func_var_2_1 = return_2_closure();

	fmt::printf("main:: 1\n");
	func_var_1_0 = func_var_2_0();
	func_var_1_1 = func_var_2_1();

	fmt::printf("main:: 2\n");
	func_var_1_0();
	func_var_1_1();

	
	

	fmt::printf("------------------ [main] ------------------\n");
	func_var_2_0, func_var_2_1 = return_2_closure();

	fmt::printf("main:: 1\n");
	func_var_1_0 = func_var_2_0();
	func_var_1_1 = func_var_2_1();

	fmt::printf("main:: 2\n");
	func_var_1_0();
	func_var_1_1();
}

fn return_2_closure() -> (FuncType2, FuncType2) {

	var int local_int_value_0 = 100;

	fmt::printf("invoke return_2_closure\n");

	return fn() -> (FuncType1) {

		fmt::printf("Closure-A\n");
		local_int_value_0 ++;
		fmt::printf("local_int_value_0 = {}\n", local_int_value_0);

		return fn() {
			fmt::printf("Closure-C\n");
			local_int_value_0 += 2;
			fmt::printf("local_int_value_0 = {}\n", local_int_value_0);
		};
	}, fn() -> (FuncType1) {

		fmt::printf("Closure-B\n");
		local_int_value_0 ++;
		fmt::printf("local_int_value_0 = {}\n", local_int_value_0);

		return fn() {
			fmt::printf("Closure-D\n");
			local_int_value_0 += 2;
			fmt::printf("local_int_value_0 = {}\n", local_int_value_0);
		};
	};

}


