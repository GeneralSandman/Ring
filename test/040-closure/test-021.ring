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
	test();
}


fn test() {
	var FuncType local_func_var;

	var int local_int_value_0;

	fn(var string string_var) {
		fmt::printf("invoke a closure local_int_value_0={}\n", local_int_value_0);
		fmt::printf("invoke a closure string_var={}\n", string_var);
	}("hello world");


	local_int_value_0 = 100;

	fn(var string string_var) {
		fmt::printf("invoke a closure local_int_value_0={}\n", local_int_value_0);
		fmt::printf("invoke a closure string_var={}\n", string_var);
	}("hello world");
	
}