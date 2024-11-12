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

typedef function() FuncType1;

typedef function() -> (FuncType1) FuncType2;


// TestDetail: 测试见的FreeValue , 不支持逃逸
@main
function main() {

	var FuncType2 func_type2_var;
	var FuncType1 func_type1_var;

	//  ----------------------
	fmt::printf("-------------\n");
	func_type2_var = use_closure();
	func_type1_var = func_type2_var();
	func_type1_var();
	func_type1_var();

	func_type1_var = func_type2_var();
	func_type1_var();
	func_type1_var();


	//  ----------------------
	fmt::printf("-------------\n");
	func_type2_var = use_closure();
	func_type1_var = func_type2_var();
	func_type1_var();
	func_type1_var();

	func_type1_var = func_type2_var();
	func_type1_var();
	func_type1_var();


}

function use_closure() -> (FuncType2) {

	var int level0_local_int_value_0;

	level0_local_int_value_0 = 1;
	fmt::printf("[new closure 1] level0_local_int_value_0={}\n", level0_local_int_value_0);

	return function() -> (FuncType1) {
		level0_local_int_value_0++;
		fmt::printf("[new closure 2] level0_local_int_value_0={}\n", level0_local_int_value_0);
		return function() {
			level0_local_int_value_0++;
			fmt::printf("[+closure] level0_local_int_value_0={}\n", level0_local_int_value_0);
		};
	};
}

