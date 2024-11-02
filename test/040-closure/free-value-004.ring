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

typedef function() FuncType;


// TestDetail: 测试见的FreeValue , 不支持逃逸
@main
function main() {

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

function use_closure() -> (FuncType) {

	var int level0_local_int_value_0;

	level0_local_int_value_0 = 1;
	fmt::printf("[new closure] level0_local_int_value_0={}\n", level0_local_int_value_0);

	return function() {
		level0_local_int_value_0++;
		fmt::printf("[+closure] level0_local_int_value_0={}\n", level0_local_int_value_0);
	};
}


