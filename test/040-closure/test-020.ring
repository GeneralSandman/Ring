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


typedef FuncType = fn(string);


fn main() {
	var FuncType func_var;

	func_var = return_a_closure();

	func_var("hello world");
}


fn return_a_closure() -> (FuncType) {
	var FuncType local_func_var;

	var int local_int_value_0;

	local_func_var = fn(var string string_var) {
		fmt::printf("invoke a closure local_int_value_0={}\n", local_int_value_0);
		fmt::printf("invoke a closure string_var={}\n", string_var);
	};


	local_int_value_0 = 100;


	
	
	return local_func_var;
}